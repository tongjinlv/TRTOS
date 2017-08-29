/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Key_Driver.h>
#include <StandardModBus.h>
u8 Sensor_Init1(void)
{
	float t;
	UIShowValue.CountWay=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_DTH11)
	{
		DTH11_SetPort(GPIOC,GPIO_Pin_0);//056
		if(!DHT11_Read(&t,&t))UIShowValue.CountWay++;
		DTH11_SetPort(GPIOC,GPIO_Pin_5);//056
		if(!DHT11_Read(&t,&t))UIShowValue.CountWay++;
		DTH11_SetPort(GPIOC,GPIO_Pin_6);//056
		if(!DHT11_Read(&t,&t))UIShowValue.CountWay++;
		DeBug("传感器统计%d",UIShowValue.CountWay,Infor_Infor);
	}else
	{
			DS_SetPort(GPIOC,GPIO_Pin_0);
		if(!DS18B20_Init())UIShowValue.CountWay++;
			DS_SetPort(GPIOC,GPIO_Pin_5);
		if(!DS18B20_Init())UIShowValue.CountWay++;

	}
	return UIShowValue.CountWay;
} 
//其实可以实现单线混合读取，但是考虑到比较浪费CPU还是算了
uint8 DR_Read_Value(uint8 Way,float *Ch1,float *Ch2)
{
	static uint8 z[3];
			switch(Way)
	{
		case 0:DTH11_SetPort(GPIOC,GPIO_Pin_0);if(z[Way]>10)UIShowValue.RunFlag&=~(WRF_SensorCH1Connected);else UIShowValue.RunFlag|=(WRF_SensorCH1Connected);break;
		case 1:DTH11_SetPort(GPIOC,GPIO_Pin_5);if(z[Way]>10)UIShowValue.RunFlag&=~(WRF_SensorCH2Connected);else UIShowValue.RunFlag|=(WRF_SensorCH2Connected);break;
		case 2:DTH11_SetPort(GPIOC,GPIO_Pin_6);if(z[Way]>10)UIShowValue.RunFlag&=~(WRF_SensorCH3Connected);else UIShowValue.RunFlag|=(WRF_SensorCH3Connected);break;
		default:UIShowValue.CurWay=0;break;
	}
		if(DHT11_Read(Ch1,Ch2))
		{
			z[Way]++;
		}else z[Way]=0;
		return z[Way];
}

//其实可以实现单线混合读取，但是考虑到比较浪费CPU还是算了
void Temp_Read_Value(float *Ch1)
{
	uint8 u=0;
	static uint8 Buf[2];
		u=DS_Get_Temp(Ch1);
		if(u)
			{
				
			Buf[0]++;
			if(Buf[0]>10)UIShowValue.RunFlag&=~(WRF_SensorCH2Connected);
		}else {Buf[0]=0;UIShowValue.RunFlag|=(WRF_SensorCH2Connected);}
	
}


void TaskPlan_1(void *Tags)
{
	float CHValue[2];
	ADC1_Init((uintbus)&UIShowValue.ADC[0]);
	ISL1208_Init((void *)IO_ISL1208_P);
	Tos_TaskDelay(3000);
	Sensor_Init1();
	ISL1208_GetDateTime(&UIShowValue.DateTime);	
	DR_Read_Value(0,&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	DR_Read_Value(1,&UIShowValue.CH_Value[3],&UIShowValue.CH_Value[4]);
	DR_Read_Value(2,&UIShowValue.CH_Value[5],&UIShowValue.CH_Value[6]);
	UIShowValue.RecordCount=Get_PrintfRecordCount();
	while(1)
	{
		ISL1208_GetDateTime(&UIShowValue.DateTime);	
		Tos_TaskDelay(500);
		if(!DR_Read_Value(0,&CHValue[0],&CHValue[1]))
		{
			UIShowValue.CH_Value[0]=UIShowValue.SaveValue.CorrectValue[0]+CHValue[0];
			UIShowValue.CH_Value[1]=UIShowValue.SaveValue.CorrectValue[1]+CHValue[1];
		}
		if(!DR_Read_Value(1,&CHValue[0],&CHValue[1]))
		{
			UIShowValue.CH_Value[2]=UIShowValue.SaveValue.CorrectValue[2]+CHValue[0];
			UIShowValue.CH_Value[3]=UIShowValue.SaveValue.CorrectValue[3]+CHValue[1];
		}
		if(!DR_Read_Value(2,&CHValue[0],&CHValue[1]))
		{
			UIShowValue.CH_Value[4]=UIShowValue.SaveValue.CorrectValue[4]+CHValue[0];
			UIShowValue.CH_Value[5]=UIShowValue.SaveValue.CorrectValue[5]+CHValue[1];
		}
		Task_Plan();
		if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)Task_Record();
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4))UIShowValue.RunFlag|=WRF_USB_Connected;else UIShowValue.RunFlag&=~WRF_USB_Connected;
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5))UIShowValue.RunFlag|=WRF_EXP_Connected;else UIShowValue.RunFlag&=~WRF_EXP_Connected;//连接12v电池改这里
	}
}





void Task_GetCo2(void *Tags)
{
	uint8 Cmd[]={0xFE,0x03,0x00,0x00,0x00,0x01,0x90,0x05}; 
	uint8 Buf[100],Length;
	while(1)
	{
		USART_WriteLine(USART3,"#AAA,%03d,%.1f,%.1f,%.1f,#END\r\n",UIShowValue.SaveValue.ServerPort[0],UIShowValue.CH_Value[0],UIShowValue.CH_Value[1],UIShowValue.CH_Value[2]);
		DR_Read_Value(0,&UIShowValue.CH_Value[1],&UIShowValue.CH_Value[2]);
		Tos_TaskDelay(1000);
		GPIO_SetIndex(9,1);
		USART_WriteDatas(USART2,Cmd,sizeof(Cmd));
		Tos_TaskDelay(2);
		GPIO_SetIndex(9,0);
		Length=USART_ReadDatas(USART2,Buf,100,300);
		if(Length)
		{
			if(Length==7)
			{
				UIShowValue.RunFlag|=WRF_SensorCH1Connected;
				UIShowValue.CH_Value[0]=USART_RX_Buffer[1][3];
				UIShowValue.CH_Value[0]*=0xff;
				UIShowValue.CH_Value[0]+=USART_RX_Buffer[1][4];
			}
			GPIO_SetIndex(2,0);
		}
	}
}
void Task_GetLora(void *Tags)
{
	uint8 Length;
	while(1)
	{                                                        
		Tos_TaskDelay(2);
		Length=USART_ReadDatas(USART3,0,100,300);
		if(Length)
		{
				USART_WriteDatas(USART3,(uint8 *)&UIShowValue.CH_Value[0],4);
			//	Tos_TaskDelay(1);
				USART_WriteDatas(USART3,(uint8 *)&UIShowValue.CH_Value[1],4);
		}
	}
}

typedef struct{
	uint8 Addr;
	short int Data[10];
}TP16BuS;
TP16BuS TB[10];
uint8 FindFNumFromString(uint8 *Buf,uint8 *Data,uint8 index)
{
	uint8 Length,i,c=0,t,has=0,z=0,m;
	Length=GetTextLength(Buf);
	if(Length)
	{
		Data[0]=0;
		for(i=0;i<Length;i++)
		{
			t=Buf[i];
			if(((t>='0')&(t<='9'))|(t=='.')|(t=='-')){if(index==z)if(t!='.')Data[c++]=t;has=1;}
			else if(has){if(index==z)Data[c++]=0;has=0;z++;}
		}	
	}
	return c;
}
void Task_ZBTo485(void *Tags)
{
	uint8 Length,Addr,Size,i=0,z;
	uint8 Buf[100];
	USART_TypeDef *USARTx=(USART_TypeDef *)Tags;
	uint8 UsartCH=USART_GetIndex(USARTx);
	while(1)
	{                                        
		Tos_TaskDelay(2);
		GPIO_SetIndex(10,0);
		Length=USART_ReadDatas(USARTx,0,100,0);
		if(Length)
		{
				i=0;
				Addr=USART_RX_Buffer[UsartCH][0];
				Size=USART_RX_Buffer[UsartCH][5];
				Buf[i++]=Addr;
				Buf[i++]=USART_RX_Buffer[1][1];
				Buf[i++]=Size*2;
				for(z=0;z<Size;z++)
				{
					i+=SwitchEndian(&TB[Addr].Data[z],&Buf[i],2,0x21);
				}
				i=MB_AppendCrc(Buf,i);
				GPIO_SetIndex(10,1);
				USART_WriteDatas(USARTx,Buf,i);
				Tos_TaskDelay(2);
		}
	}
}
void Task_485ToZB(void *Tags)
{
	uint8 Length,Addr,z;
	uint8 Buf[20];
	float Data;
	GPIO_SetIndex(11,0);
	GPIO_SetIndex(10,0);
	while(1)
	{                                                        
		Tos_TaskDelay(2);
		Length=USART_ReadDatas(USART3,0,100,0);
		if(Length)
		{
				
				Length=FindFNumFromString(USART_RX_Buffer[2],Buf,0);
				Addr=GetStringToNumber(Buf);
				if(Addr<10)
				for(z=0;z<8;z++)
				{
					Length=FindFNumFromString(USART_RX_Buffer[2],Buf,z+1);
					Data=GetStringToNumber(Buf);
					TB[Addr].Data[z]=Data;
					DeBug("%d %d",z,TB[Addr].Data[z],6);
				}
		}
	}
}
void Task_Getsupersong(void *Tags)
{
	uint8 Cmd[]={0x01,0x03,0x00,0x18,0x00,0x04,0x95,0xCE }; 
	uint8 Length;
	uint32 aaa;
	MB_AppendCrc(&Cmd[0],6);
GPIO_SetIndex(11,0);
	DS_SetPort(GPIOC,GPIO_Pin_6);
	DS18B20_Init();
	while(1)
	{
		USART_WriteLine(USART1,"#AAA,%.1f,%.1f,#END\r\n",UIShowValue.CH_Value[0],UIShowValue.CH_Value[1]);
		Temp_Read_Value(&UIShowValue.CH_Value[1]);
		Tos_TaskDelay(1000);
		GPIO_SetIndex(10,1);
		MB_AppendCrc(&Cmd[0],6);
		USART_WriteDatas(USART2,Cmd,sizeof(Cmd));                                                           
		Tos_TaskDelay(2);
		GPIO_SetIndex(10,0);
		Length=USART_ReadDatas(USART2,0,100,300);
		if(Length)
		{
			if(Length==13)
			{
				UIShowValue.RunFlag|=WRF_SensorCH1Connected;
				aaa=D32FromArray(&USART_RX_Buffer[1][7],2);
				UIShowValue.CH_Value[0]=D32FromArray(&USART_RX_Buffer[1][3],2);
				UIShowValue.CH_Value[0]+=*((float *)&aaa);
			}
			GPIO_SetIndex(2,0);
		}
	}
}

void SPEAK_ON(BOOL ON)
{
	if(ON)BEEP_ON;else BEEP_OFF;
}
void BEEP()
{
	BEEP_ON;
	Tos_TaskDelay(3);
	BEEP_OFF;
}
void Task_Action(void *Tags)
{
	BOOL SetEn=False;
	uint8 i;
	Tos_ArrayMessage Msg[1];
	MGUI_KeyMsg *TaskMsg,TaskMsgBuf[1];	
	for(i=0;i<1;i++)Msg[i].Qmsg_Addr=&TaskMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],1);
	Tos_TaskGetHandKey();
	while(1)
	{
		Tos_TaskDelay(3);
		TaskMsg=MUI_GetKey(0);
		if(TaskMsg)
		{
			 DeBug("%d,%d",TaskMsg->KeyType,TaskMsg->KeyValue,2);
			BEEP();
			if(TaskMsg->KeyValue==Key_Enter)
			{
				SetEn=True;
				UIShowValue.SysWorkMode++;
			}
			if(TaskMsg->KeyValue==Key_Right){SetEn=False;Task_LoadConfigs();}
			
			
			
			if(TaskMsg->KeyValue==Key_WkUp)if(TaskMsg->KeyType==Key_OneClick){SetEn=False;System_SaveConfig();}
			if(TaskMsg->KeyValue==Key_WkUp)if(TaskMsg->KeyType==Key_DownTimeOut)
			{
				ISL1208_SetAlarm(0,0,0,0);
				BEEP_Double();
				GPIO_DeInit(GPIOA);
				GPIO_DeInit(GPIOB);
				GPIO_DeInit(GPIOC);
				GPIO_DeInit(GPIOD);
				GPIO_DeInit(GPIOE);
				Standby_Init(True);
			}

		if(SetEn)
		{
			
			switch(UIShowValue.SysWorkMode)
			{
				case 1:
				if(TaskMsg->KeyValue==Key_Up)if(TaskMsg->KeyType==Key_OneClick)UIShowValue.SaveValue.CH_Limit[0+UIShowValue.CurWay*2].Max+=0.1;
				if(TaskMsg->KeyValue==Key_Up)if(TaskMsg->KeyType==Key_DownTimeOut)UIShowValue.SaveValue.CH_Limit[0+UIShowValue.CurWay*2].Max+=1;
				if(TaskMsg->KeyValue==Key_Down)if(TaskMsg->KeyType==Key_OneClick)UIShowValue.SaveValue.CH_Limit[0+UIShowValue.CurWay*2].Max-=0.1;
				if(TaskMsg->KeyValue==Key_Down)if(TaskMsg->KeyType==Key_DownTimeOut)UIShowValue.SaveValue.CH_Limit[0+UIShowValue.CurWay*2].Max-=1;
				break;
				case 2:
				if(TaskMsg->KeyValue==Key_Up)if(TaskMsg->KeyType==Key_OneClick)UIShowValue.SaveValue.CH_Limit[0+UIShowValue.CurWay*2].Min+=0.1;
				if(TaskMsg->KeyValue==Key_Up)if(TaskMsg->KeyType==Key_DownTimeOut)UIShowValue.SaveValue.CH_Limit[0+UIShowValue.CurWay*2].Min+=1;
				if(TaskMsg->KeyValue==Key_Down)if(TaskMsg->KeyType==Key_OneClick)UIShowValue.SaveValue.CH_Limit[0+UIShowValue.CurWay*2].Min-=0.1;
				if(TaskMsg->KeyValue==Key_Down)if(TaskMsg->KeyType==Key_DownTimeOut)UIShowValue.SaveValue.CH_Limit[0+UIShowValue.CurWay*2].Min-=1;
				break;
				case 3:
				if(TaskMsg->KeyValue==Key_Up)if(TaskMsg->KeyType==Key_OneClick)UIShowValue.SaveValue.CH_Limit[1+UIShowValue.CurWay*2].Max+=0.1;
				if(TaskMsg->KeyValue==Key_Up)if(TaskMsg->KeyType==Key_DownTimeOut)UIShowValue.SaveValue.CH_Limit[1+UIShowValue.CurWay*2].Max+=1;
				if(TaskMsg->KeyValue==Key_Down)if(TaskMsg->KeyType==Key_OneClick)UIShowValue.SaveValue.CH_Limit[1+UIShowValue.CurWay*2].Max-=0.1;
				if(TaskMsg->KeyValue==Key_Down)if(TaskMsg->KeyType==Key_DownTimeOut)UIShowValue.SaveValue.CH_Limit[1+UIShowValue.CurWay*2].Max-=1;
				break;
				case 4:
				if(TaskMsg->KeyValue==Key_Up)if(TaskMsg->KeyType==Key_OneClick)UIShowValue.SaveValue.CH_Limit[1+UIShowValue.CurWay*2].Min+=0.1;
				if(TaskMsg->KeyValue==Key_Up)if(TaskMsg->KeyType==Key_DownTimeOut)UIShowValue.SaveValue.CH_Limit[1+UIShowValue.CurWay*2].Min+=1;
				if(TaskMsg->KeyValue==Key_Down)if(TaskMsg->KeyType==Key_OneClick)UIShowValue.SaveValue.CH_Limit[1+UIShowValue.CurWay*2].Min-=0.1;
				if(TaskMsg->KeyValue==Key_Down)if(TaskMsg->KeyType==Key_DownTimeOut)UIShowValue.SaveValue.CH_Limit[1+UIShowValue.CurWay*2].Min-=1;
				break;
				case 5:
				if(TaskMsg->KeyValue==Key_Up)if(TaskMsg->KeyType==Key_OneClick)UIShowValue.SaveValue.ServerPort[0]+=1;
				if(TaskMsg->KeyValue==Key_Up)if(TaskMsg->KeyType==Key_DownTimeOut)UIShowValue.SaveValue.ServerPort[0]+=10;
				if(TaskMsg->KeyValue==Key_Down)if(TaskMsg->KeyType==Key_OneClick)UIShowValue.SaveValue.ServerPort[0]-=1;
				if(TaskMsg->KeyValue==Key_Down)if(TaskMsg->KeyType==Key_DownTimeOut)UIShowValue.SaveValue.ServerPort[0]-=10;
				break;
				default:UIShowValue.SysWorkMode=1;
			}
			Ht1621_DrawMaxMin(UIShowValue.SysWorkMode);
			
		}else
		{
			if(TaskMsg->KeyValue==Key_Up)if(TaskMsg->KeyType==Key_DownTimeOut){UIShowValue.SysWorkMode=0xff;Ht1621_DrawHold(1);Tos_TaskDelay(1000);}
			if(TaskMsg->KeyValue==Key_Down)if(TaskMsg->KeyType==Key_DownTimeOut){UIShowValue.SysWorkMode=0xff;Ht1621_DrawHold(2);Tos_TaskDelay(1000);}
			
			if(TaskMsg->KeyValue==Key_Down)UIShowValue.CurWay--;
			if(UIShowValue.CurWay>2)UIShowValue.CurWay=2;
			if(TaskMsg->KeyValue==Key_Up)UIShowValue.CurWay++;
			if(UIShowValue.CurWay>=UIShowValue.CountWay)UIShowValue.CurWay=0;
			UIShowValue.SysWorkMode=0;
		}
			
		}
	}
}
void Timer_Broken1()
{
	uint8 i=5,m,c=3;
	int16 t;
	uint8 Buf[30]={0x55,0x00,0x0b,0x02,0x80,0x1a,0x2b,0x3c,0x4d,0x5e,0x15,0x03};
	GetCodeStr64(&Buf[i]);i+=5;
	Buf[i++]=0x15;//通道类型
	Buf[i++]=c;//通道数
	for(m=0;m<c;m++)
	{
		switch(m)
					{
						case 0:if(UIShowValue.RunFlag&WRF_SensorCH1Connected)
						{
								t=UIShowValue.CH_Value[m*2]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
								t=UIShowValue.CH_Value[m*2+1]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
						}else
						{
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
						}
						break;
						case 1:if(UIShowValue.RunFlag&WRF_SensorCH2Connected)
						{
								t=UIShowValue.CH_Value[m*2]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
								t=UIShowValue.CH_Value[m*2+1]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
						}else
						{
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
						}
						break;
						case 2:if(UIShowValue.RunFlag&WRF_SensorCH3Connected)
						{
								t=UIShowValue.CH_Value[m*2]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
								t=UIShowValue.CH_Value[m*2+1]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
						}else
						{
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
						}
						break;
					}
	}
	Buf[i++]=UIShowValue.RSSI;
	Buf[i++]=UIShowValue.CH_Value[6]*10;
	Buf[i++]=UIShowValue.SaveValue.ServerPort[0];
	i=MB_AppendCrc(&Buf[0],i);
	USART_WriteDatas(USART3,Buf,i);
}
void Task_SendZB(void *Tags)
{
	uint8 Buf[30],m,c=3,i;
	uint8 Length;
	int16 t;
	Tos_CreateTimer(UIShowValue.SaveValue.SendCycle,0xffff,Timer_Broken1);
	while(1)
	{
		
		GPIO_SetIndex(10,0);
		Tos_TaskDelay(3);
		Length=USART_ReadDatas(USART2,0,100,0);
		if(Length)
		{
			if((UIShowValue.SaveValue.ServerPort[0]==USART_RX_Buffer[1][0])|(USART_RX_Buffer[1][0]==0xff))
			{
				i=0;
				Buf[i++]=UIShowValue.SaveValue.ServerPort[0];
				Buf[i++]=0x03;
				Buf[i++]=USART_RX_Buffer[1][5]*2;
				for(m=0;m<c;m++)
				{
					switch(m)
					{
						case 0:if(UIShowValue.RunFlag&WRF_SensorCH1Connected)
						{
								t=UIShowValue.CH_Value[m*2]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
								t=UIShowValue.CH_Value[m*2+1]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
						}else
						{
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
						}
						break;
						case 1:if(UIShowValue.RunFlag&WRF_SensorCH2Connected)
						{
								t=UIShowValue.CH_Value[m*2]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
								t=UIShowValue.CH_Value[m*2+1]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
						}else
						{
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
						}
						break;
						case 2:if(UIShowValue.RunFlag&WRF_SensorCH3Connected)
						{
								t=UIShowValue.CH_Value[m*2]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
								t=UIShowValue.CH_Value[m*2+1]*10;
								i+=SetWordToBytes(&Buf[i],t,1);//温度
						}else
						{
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
								i+=SetWordToBytes(&Buf[i],19999,1);//温度
						}
						break;
					}
				
				}
				Buf[i++]=UIShowValue.RSSI;
				Buf[i++]=UIShowValue.CH_Value[6]*10;
				Buf[i++]=UIShowValue.SaveValue.ServerPort[0];
				i=Buf[2]+3;
				i=MB_AppendCrc(&Buf[0],i);
				GPIO_SetIndex(10,1);
				USART_WriteDatas(USART2,Buf,i); 
				Tos_TaskDelay(2);			
			}
		}
		
	}
}

