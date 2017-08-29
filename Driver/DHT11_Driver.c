/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <DHT11_Driver.h>

uint16  DHT11_PIN=GPIO_Pin_9;
GPIO_TypeDef *DHT11_GROUP=GPIOB;



void DTH11_SetPort(GPIO_TypeDef *GROUP,uint16 PIN)
{
	DHT11_GROUP=GROUP;
	DHT11_PIN=PIN;
}
void DHT11_DelayUs(uint16 D)
{
	uint16 i=0;
	while(D--)
	{
		i=7;//5~8������
		while(i--);
	}
}
void DHT11_DelayMs(uint16 n)
{
	uint16 i=0;
	while(n--)
	{
		i=12000;
		while(i--);
	}
}
void DHT11_PortIN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	//��������
	GPIO_Init(DHT11_GROUP,&GPIO_InitStructure);
}
void DHT11_PortOUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//�������
	GPIO_Init(DHT11_GROUP,&GPIO_InitStructure);
}

void DHT11_Rst(void)	   
{                 
	DHT11_PortOUT();
  GPIO_ResetBits(DHT11_GROUP,DHT11_PIN);
  DHT11_DelayMs(10);    	//��������18ms
  GPIO_SetBits(DHT11_GROUP,DHT11_PIN);
	DHT11_DelayUs(80);     	//��������20~40us
}
uint8 DHT11_Check(void) 	   
{   
	uint8 retry=0;
	DHT11_PortIN();//SET INPUT	 
    while (GPIO_ReadInputDataBit(DHT11_GROUP,DHT11_PIN)&&retry<100)//DHT11������40~80us    //����Tgo
	{
		retry++;
		DHT11_DelayUs(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!GPIO_ReadInputDataBit(DHT11_GROUP,DHT11_PIN)&&retry<100)//DHT11���ͺ���ٴ�����40~80us     //����Trel
	{
		retry++;
		DHT11_DelayUs(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
uint8 DHT11_Read_Bit(void) 			 
{
 	uint8 retry=0;
	while(GPIO_ReadInputDataBit(DHT11_GROUP,DHT11_PIN)&&retry<100)//�ȴ���Ϊ�͵�ƽ  //����Treh
	{
		retry++;
		DHT11_DelayUs(1);
	}
	retry=0;
	while(!GPIO_ReadInputDataBit(DHT11_GROUP,DHT11_PIN)&&retry<100)//�ȴ���ߵ�ƽ   //����TLOW
	{
		retry++;
		DHT11_DelayUs(1);
	}
	DHT11_DelayUs(/*40*/35);//�ȴ�40us
	if(GPIO_ReadInputDataBit(DHT11_GROUP,DHT11_PIN))return 1;
	else return 0;		   
}
uint8 DHT11_Read_Byte(void)    
{        
  uint8 i,dat;
  dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}
void DHT11_GetFloat(uint8 *Data,float *Temp)
{
	uint16 T16;
	float T;
	T16=Data[0];T16<<=8;T16|=Data[1];
	if(T16&0x8000)
	{
		T=(int)(((~T16)+1)|0x8000);	
		T/=10;
	}else 
	{
		T=T16;T/=10;
	}
	if((T>-1000)&(T<120))*Temp=T;
}
uint8 DHT11_Read(float *Temp,float *Humi)
{
	uint8 Data[5],i,c;
	DHT11_Rst();
	if(DHT11_Check()){return 1;}
	DIS_INT;
	for(i=0;i<5;i++)
	{
		Data[i]=DHT11_Read_Byte();
	}
	c=Data[0]+Data[1]+Data[2]+Data[3];
	if(Data[4]!=c){EN_INT;return 1;}
	if(Temp)DHT11_GetFloat(&Data[0],Humi);
	if(Humi)DHT11_GetFloat(&Data[2],Temp);
	EN_INT;
	return 0;
}
