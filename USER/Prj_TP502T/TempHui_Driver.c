/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <DHT11_Driver.c>
#include <DS18B20_Driver.c>

u8 Sensor_Init(void)
{
	uint8 Ds18B20CHOK=0x00;
	if(UIShowValue.SaveValue.WorkBit&WCB_DTH11)
	{
		DTH11_SetPort(GPIOB,GPIO_Pin_9);
		if(!DHT11_Read(Null,Null))Ds18B20CHOK+=2;
	}else
	{
			DS_SetPort(GPIOB,GPIO_Pin_9);
		if(!DS18B20_Init())Ds18B20CHOK++;
			DS_SetPort(GPIOB,GPIO_Pin_8);
		if(!DS18B20_Init())Ds18B20CHOK++;

	}
	return Ds18B20CHOK;
} 
//其实可以实现单线混合读取，但是考虑到比较浪费CPU还是算了
void DS_Read_Value(float *Ch1,float *Ch2)
{
	uint8 u=0;
	static uint8 Buf[2];
	if(UIShowValue.SaveValue.WorkBit&WCB_DTH11)
	{
		DTH11_SetPort(GPIOB,GPIO_Pin_9);
		if(DHT11_Read(Ch1,Ch2))
		{
			Buf[0]++;
			if(Buf[0]>10)UIShowValue.RunFlag&=~(WRF_SensorCH1Connected|WRF_SensorCH2Connected);
		}else {Buf[0]=0;UIShowValue.RunFlag|=(WRF_SensorCH1Connected|WRF_SensorCH2Connected);}
	}
	else
	{
		DS_SetPort(GPIOB,GPIO_Pin_9);
		u=DS_Get_Temp(Ch1);
		if(u)
		{
			Buf[0]++;
			if(Buf[0]>10)
			{
			DS18B20_Init();
			UIShowValue.RunFlag&=~WRF_SensorCH1Connected;
			}
		}else {Buf[0]=0;UIShowValue.RunFlag|=WRF_SensorCH1Connected;}
		DS_SetPort(GPIOB,GPIO_Pin_8);
		u=DS_Get_Temp(Ch2);
		if(u)
		{
			Buf[1]++;
			if(Buf[1]>10)
			{
			DS18B20_Init();
			UIShowValue.RunFlag&=~WRF_SensorCH2Connected;
			}
		}else {Buf[1]=0;UIShowValue.RunFlag|=WRF_SensorCH2Connected;}
	}
}
void IO_Read_Value(float *Ch1,float *Ch2)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	UIShowValue.RunFlag|=WRF_SensorCH1Connected|WRF_SensorCH2Connected;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	//推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8))*Ch1=1.0;else *Ch1=0.0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))*Ch1=1.0;else *Ch1=0.0;
	
}
