/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_TP502T\GPS_Driver.h>							   								   
#include <string.h>
#include <math.h>
#include <STM32_CPU.h>
void Task_Gps(void *Tags)
{
	uint16 Length;
	uint8 *P;
	GPS_ON;
	while(1)
	{
		Length=USART_ReadDatas(USART3,Null,USART_RX_BUFFER_SIZE,1000);
		if(Length)
		{
			USART_RX_Buffer[2][50]=0;
			
			if(strstr((const char *)USART_RX_Buffer[2],"$GPRMC"))
			{
				if(strstr((const char *)USART_RX_Buffer[2],"A"))
				{
					P=(uint8 *)strstr((const char *)USART_RX_Buffer[2],"A");
					UIShowValue.GPS_Latitude=GetStringToNumber(P+2);
					//UIShowValue.GPS_Latitude=(uint32)(UIShowValue.GPS_Latitude/100)+(UIShowValue.GPS_Latitude-(uint32)(UIShowValue.GPS_Latitude/100)*100)/60;//服务器上做了修正就不需要在这里做
					P=(uint8 *)strstr((const char *)USART_RX_Buffer[2],"N");
					UIShowValue.GPS_Longitude=GetStringToNumber(P+2);
					//UIShowValue.GPS_Longitude=(uint32)(UIShowValue.GPS_Longitude/100)+(UIShowValue.GPS_Longitude-(uint32)(UIShowValue.GPS_Longitude/100)*100)/60;
					
					if(strstr((const char *)USART_RX_Buffer[2],"W"))UIShowValue.GPS_Latitude=0-UIShowValue.GPS_Latitude;
					if(strstr((const char *)USART_RX_Buffer[2],"S"))UIShowValue.GPS_Latitude=0-UIShowValue.GPS_Latitude;
					UIShowValue.RunFlag|=WRF_GPS_Connected;
					DeBug("经纬度:%.8f,%.7f",UIShowValue.GPS_Latitude,UIShowValue.GPS_Longitude,Infor_Warning);
					if(Abs(UIShowValue.GPS_Latitude)>100)
					if(Abs(UIShowValue.GPS_Longitude)>100)
					{
						GPS_OFF;
						Tos_TaskDelay(60000);
						GPS_ON;
					}
				}else UIShowValue.RunFlag&=~WRF_GPS_Connected;
			}
		}
		Tos_TaskDelay(3000);
	}
}
float TempFloatA[3];
void AS_Read_Value(float *Ch1,float *Ch2)
{

	*Ch1=TempFloatA[0];
	*Ch2=TempFloatA[1];
}
extern void USART_ConfigurationAll(USART_TypeDef* USARTx,uint32_t USART_BaudRate,uint8_t NVIC_IRQChannel);
void Task_Sensor(void *Tags)
{
	uint16 Length;
	uint8 z=0;
	uint8 Data[20];
	GPS_ON;
	USART_ConfigurationAll(USART3,19200,USART3_IRQn);
	while(1)
	{
		USART_WriteLine(USART3,"r\r\n");
		Length=USART_ReadDatas(USART3,Null,USART_RX_BUFFER_SIZE,1000);
		if(Length)
		{
			DeBug("R:%s",USART_RX_Buffer[2],Infor_Warning);
			USART_RX_Buffer[2][50]=0;
			
			FindFloatFromString(USART_RX_Buffer[2],Data,0);
			TempFloatA[0]=GetStringToNumber(Data);
			DeBug("R:%f",TempFloatA[0],Infor_Warning);
			FindFloatFromString(USART_RX_Buffer[2],Data,1);
			TempFloatA[1]=GetStringToNumber(Data);
			DeBug("R:%f",TempFloatA[1],Infor_Warning);
				FindFloatFromString(USART_RX_Buffer[2],Data,2);
			TempFloatA[2]=GetStringToNumber(Data);
			DeBug("R:%f",TempFloatA[2],Infor_Warning);
			UIShowValue.RunFlag|=WRF_SensorCH1Connected;
		 UIShowValue.RunFlag|=WRF_SensorCH2Connected;
			z=0;
		}else
		{
			z++;
			if(z>3)
			{
				UIShowValue.RunFlag&=~WRF_SensorCH1Connected;
				UIShowValue.RunFlag&=~WRF_SensorCH2Connected;
			}
		}
		Tos_TaskDelay(3000);
	}
}
#include <B_LUX_V20.c>
const GPIO_InitStruct IO_LUX_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_11},
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_10},
	{0},
}; 
void Task_SensorBLX(void *Tags)
{
	uint32 t;
	float Value;
	uint8 z=0;
//	uint8 Data[20];
	GPS_ON;
	UIShowValue.SysWorkMode=1;
	//USART_ConfigurationAll(USART3,9600,USART3_IRQn);
	B_LUX_Init(IO_LUX_List);//00 10 01///01 03 00 00 00 01
	while(1)
	{
		
		
		Tos_TaskDelay(1000);
		t=B_LUX_GetLux(IO_LUX_List);
		Value=t;
		DeBug("%d",(int)t,Infor_Warning);
		if(Value<70000)
		{
		 TempFloatA[0]=Value;
		 z=0;
  	 UIShowValue.RunFlag|=WRF_SensorCH1Connected;
		}else
		{
				z++;
			if(z>3)
			{
				UIShowValue.RunFlag&=~WRF_SensorCH1Connected;
	
			}
		}
	}
}
void Task_SensorFuShe(void *Tags)
{
	float Value;
	uint8 z=0,Length;
	uint8 SaveAddr[]={0x00,0x10,0x01,0xBD,0xC0};
  uint8 GetValue[]={0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0a};
	GPS_ON;
	UIShowValue.SysWorkMode=2;
	USART_ConfigurationAll(USART3,9600,USART3_IRQn);//00 10 01///01 03 00 00 00 01
	while(1)
	{
		USART_WriteDatas(USART3,SaveAddr,sizeof(SaveAddr));
		Length=USART_ReadDatas(USART3,Null,USART_RX_BUFFER_SIZE,1000);
		USART_WriteDatas(USART3,GetValue,sizeof(GetValue));
		Length=USART_ReadDatas(USART3,Null,USART_RX_BUFFER_SIZE,1000);
		if(Length)
		{
			Value=(int)USART_RX_Buffer[2][3]*0xff+USART_RX_Buffer[2][4];
			TempFloatA[0]=Value;
			DeBug("%d",(int)Value,Infor_Warning);
			z=0;
			UIShowValue.RunFlag|=WRF_SensorCH1Connected;
		}else 
		{
			z++;
			if(z>3)
			{
				UIShowValue.RunFlag&=~WRF_SensorCH1Connected;
			}
		}
		Tos_TaskDelay(1000);
	}
}

void Task_SensorGPIO(void *Tags)
{

	UIShowValue.SysWorkMode=3;
	while(1)
	{
		
		Tos_TaskDelay(1000);
	}
}
float LiuliangBuf[25];
void CheckLiuliangBuf()
{
	uint8 i;
	for(i=0;i<25;i++)
	{
		if(LiuliangBuf[i]>99999.99)LiuliangBuf[i]=0;
		if(LiuliangBuf[i]<-99999.99)LiuliangBuf[i]=0;
	}
}
void Task_Liuliang(void *Tags)
{
	uint8 z=0,Length;
	uint8 SaveAddr[]={0x01};
	GPIO_ResetBits(GPIOC,GPIO_Pin_10);
	GPS_ON;
	UIShowValue.SysWorkMode=4;
	Tos_TaskDelay(1000);
	 GPIO_SetBits(GPIOC,GPIO_Pin_10);
	while(1)
	{
		if(SaveAddr[0]>6)SaveAddr[0]=1;
		if(SaveAddr[0]==0)SaveAddr[0]=1;
		USART_WriteDatas(UART4,SaveAddr,sizeof(SaveAddr));
		Tos_TaskDelay(10*SaveAddr[0]);
		USART_WriteDatas(UART4,SaveAddr,sizeof(SaveAddr));
		DeBug("请求地址[%d]",SaveAddr[0],Infor_Warning);
		UIShowValue.CH_Value[1]=SaveAddr[0];
		UIShowValue.RunFlag|=WRF_SensorCH2Connected;
		UIShowValue.RunFlag&=~WRF_SensorCH1Connected;
		Length=USART_ReadDatas(UART4,Null,USART_RX_BUFFER_SIZE,5000);
		if(Length)
		{
			if(USART_RX_Buffer[3][0]>0&USART_RX_Buffer[3][0]<6)
			{
				DeBug("[%d]流量:%.2f",USART_RX_Buffer[3][0],*(float *)&USART_RX_Buffer[3][1],Infor_Warning);
				DeBug("[%d]温度:%.2f",USART_RX_Buffer[3][0],*(float *)&USART_RX_Buffer[3][5],Infor_Warning);
				LiuliangBuf[USART_RX_Buffer[3][0]*2]=*(float *)&USART_RX_Buffer[3][1];
				LiuliangBuf[USART_RX_Buffer[3][0]*2+1]=*(float *)&USART_RX_Buffer[3][5];
				UIShowValue.CH_Value[0]=*(float *)&USART_RX_Buffer[3][1];
			}else 
			if(USART_RX_Buffer[3][0]==0x06)
			{
				LiuliangBuf[USART_RX_Buffer[3][0]*2]=((float)Bcd_Decimal(USART_RX_Buffer[3][3]))*100;
				LiuliangBuf[USART_RX_Buffer[3][0]*2]+=((float)Bcd_Decimal(USART_RX_Buffer[3][2]));
				LiuliangBuf[USART_RX_Buffer[3][0]*2]+=((float)Bcd_Decimal(USART_RX_Buffer[3][1]))/100;
				LiuliangBuf[USART_RX_Buffer[3][0]*2+1]=((float)Bcd_Decimal(USART_RX_Buffer[3][6]));
				LiuliangBuf[USART_RX_Buffer[3][0]*2+1]+=((float)Bcd_Decimal(USART_RX_Buffer[3][5]))/100;
				LiuliangBuf[USART_RX_Buffer[3][0]*2+2]=((float)Bcd_Decimal(USART_RX_Buffer[3][8]));
				LiuliangBuf[USART_RX_Buffer[3][0]*2+2]+=((float)Bcd_Decimal(USART_RX_Buffer[3][7]))/100;
				DeBug("[%d]流量:%.2f",USART_RX_Buffer[3][0],LiuliangBuf[USART_RX_Buffer[3][0]*2],0);
				DeBug("[%d]温度:%.2f",USART_RX_Buffer[3][0],LiuliangBuf[USART_RX_Buffer[3][0]*2+1],Infor_Warning);
				DeBug("[%d]温度:%.2f",USART_RX_Buffer[3][0],LiuliangBuf[USART_RX_Buffer[3][0]*2+2],Infor_Warning);
				UIShowValue.CH_Value[0]=LiuliangBuf[USART_RX_Buffer[3][0]*2];
			}else DeBug("错误地址",Infor_Warning);
			
			UIShowValue.CH_Value[1]=USART_RX_Buffer[3][0];//*(float *)&USART_RX_Buffer[3][5];
			z=0;
			UIShowValue.RunFlag|=WRF_SensorCH1Connected;
			Tos_TaskDelay(1500);
			SaveAddr[0]++;
			CheckLiuliangBuf();
		}else 
		{
			z++;
			if(z>5)
			{
				SaveAddr[0]++;
				z=0;
				UIShowValue.RunFlag&=~WRF_SensorCH1Connected;
			//	UIShowValue.RunFlag&=~WRF_SensorCH2Connected;
			}
		}
		Tos_TaskDelay(1000);
	}
}

