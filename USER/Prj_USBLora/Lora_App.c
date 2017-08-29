/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <StandardModBus.h>


void Exit_Init(FunctionalState En)
{
	NVIC_InitTypeDef NVIC_InitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;                                                                           
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   
  GPIO_Init(GPIOB, &GPIO_InitStructure);
   
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);
  EXTI_InitStructure.EXTI_Line = EXTI_Line8;                                       
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                          
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;                 
  EXTI_InitStructure.EXTI_LineCmd = En;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn;                                  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                       
  NVIC_InitStructure.NVIC_IRQChannelCmd = En;                               
  NVIC_Init(&NVIC_InitStructure);
}

uint8 TaskLora_Tos_TaskID=Tos_TaskNull;

void EXTI9_5_IRQHandler(void)
{       
	uint8 Buf[1];	
  EXTI_ClearITPendingBit(EXTI_Line8); 
  Tos_TaskPutQmsg(TaskLora_Tos_TaskID,0,1,&Buf[0]);
}
void EXTI0_IRQHandler(void)
{
  uint8 Buf[1];	
  EXTI_ClearITPendingBit(EXTI_Line0); 
  Tos_TaskPutQmsg(TaskLora_Tos_TaskID,0,1,&Buf[0]);
}
BOOL Lora_Write(uint8 *Buf,uint8 Length)
{
	uint16 i=0;
	SX1276LoRa_TX_INIT(Length);
	SX1276_LoRaTxPacket(Buf,Length);
	while(!GPIO_ReadInputDataBit(Pin_Maps[6].GPIOx,Pin_Maps[6].GPIO_Pin)){Tos_TaskDelay(1);if(i++>2000)break;}
	SX1276_LoRaClearIrq(); 
	SX1276LoRa_RX_INIT();
	return (BOOL)(i>9);
}
uint8 Lora_Read(uint8 *Buf)
{
	uint16 i=0;
  while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)){Tos_TaskDelay(1);if(i++>2000)break;}
  if(i<10)return 0;
  i=SX1276_LoRaRxPacket(Buf);
  return i;
}
float GetTemp(uint8 *Buf)
{
  float Value;
  uint16 t;
  t=Buf[0];
  t<<=8;
  t+=Buf[1];
  Value=((double)t*125.0/65536-6);
  return Value;
}
float GetHmi(uint8 *Buf)
{
  float Value;
  uint16 t;
  t=Buf[0];
  t<<=8;
  t+=Buf[1];
  Value=((double)t*175.72/65536-46.85);
  return Value;
}

  void Task_Lora_Jianting(void *Tags)
{
	uint8 i=10;
	Tos_ArrayMessage *CurMsg,Msg[10];
	uint8 *PBuf,Buf[10][21];	
	for(i=0;i<10;i++)Msg[i].Qmsg_Addr=&Buf[i][0];
	Tos_TaskCreateQmsg(&Msg[0],10);
	TaskLora_Tos_TaskID=Tos_TaskCurrent;
	SpiInit();
	InitRFChip();
	while(i--)
	{
		i=ReadReg((u8)(REG_LR_VERSION>>8));
		if(i==0x12)break;
	}
	
	SX1276LoRa_RX_INIT();
	Exit_Init(ENABLE);
	while(1)
	{
		Tos_TaskDelay(1);
		 CurMsg=Tos_TaskGetQMsg();
		if(CurMsg)
		{
			PBuf=(uint8 *)(CurMsg->Qmsg_Addr);
			//USART_WriteDatas(USART2,PBuf,CurMsg->Qmsg_Size-1);
			DeBug("addr=%d,bat=%.1f,tmp=%.1f,hui=%.1f",PBuf[0],(float)PBuf[1]/10,GetTemp(&PBuf[2]),GetHmi(&PBuf[4]),0);
			Exit_Init(DISABLE);
			PBuf[1]=3;//30秒
			Lora_Write(&PBuf[0],2);
			Tos_TaskDelay(1);
			Exit_Init(ENABLE);
		}
	}
}
typedef struct 
{
	float Value[4*20];
	uint8 FailCount[20];
	uint8 BUf[2];
}DataToT3Struct;
DataToT3Struct T3Data;
  void Task_Lora_zhuji(void *Tags)
{
	uint8 i=3,Length;
	uint16 Addr=0x00;
	Tos_ArrayMessage *CurMsg,Msg[10];
	uint8 PBuf[100],Buf[10];	
	for(i=0;i<10;i++)Msg[i].Qmsg_Addr=&Buf[i];
	Tos_TaskCreateQmsg(&Msg[0],10);
	TaskLora_Tos_TaskID=Tos_TaskCurrent;
	SpiInit();
	InitRFChip();
	while(i--)
	{
		if(ReadReg((u8)(REG_LR_VERSION>>8))==0x12)break;
		DeBug("初始化失败",5);
	}
	SX1276LoRa_RX_INIT();
	Exit_Init(ENABLE);
	
	while(1)
	{
		Tos_TaskDelay(1);
		 CurMsg=Tos_TaskGetQMsg();
		if(CurMsg)
		{
			Length=SX1276_LoRaRxPacket(PBuf);
			if(MB_CheckCrc(PBuf,Length-1))
			{
				
			DeBug("addr=%d,rssi=%.1f,bat=%.1f,hui=%.1f,temp=%.1f",PBuf[0],(float)sx1276_7_8_LoRaReadRSSI(),(float)PBuf[1]/10,GetTemp(&PBuf[2]),GetHmi(&PBuf[4]),0);
			Addr=PBuf[0];
			if(Addr<20)
			{
			T3Data.FailCount[Addr]=0;
			Addr*=4;
			T3Data.Value[Addr++]=(float)sx1276_7_8_LoRaReadRSSI();
			T3Data.Value[Addr++]=(float)PBuf[1]/10;
			T3Data.Value[Addr++]=GetHmi(& PBuf[4]);
			T3Data.Value[Addr++]=GetTemp(&PBuf[2]);
			}
			Exit_Init(DISABLE);
			PBuf[1]=1;//30秒
			Lora_Write(&PBuf[0],2);
			Tos_TaskDelay(1);
			Exit_Init(ENABLE);
			//USART_WriteDatas(USART2,PBuf,CurMsg->Qmsg_Size-1);
			}
		}
	}
}
void Task_Lora_zhumb(void *Tags)
{
		uint8 ModBus[255]={0x01,0x03,0x00};
	uint8 i,m;
	uint16 Offset,Size;
  uint8 Length;
	while(1)
	{
		Tos_TaskDelay(1);
		ClearWithBuffer(USART_RX_Buffer[1],50);
		Length=USART_ReadDatas(USART2,Null,50,0);
		if(Length)if(MB_CheckCrc(USART_RX_Buffer[1],Length))
		{
			
			SwitchEndian(&USART_RX_Buffer[1][2],&Offset,2,0x21);
			SwitchEndian(&USART_RX_Buffer[1][4],&Size,2,0x21);
			i=0;
			ModBus[i++]=USART_RX_Buffer[1][0];
			ModBus[i++]=USART_RX_Buffer[1][1];
			ModBus[i++]=Size*2;
			for(m=0;m<(Size/2);m++)
			{
				i+=SwitchEndian(&T3Data.Value[m+(Offset/2)],&ModBus[i],4,0x4321);
			}
			i=MB_AppendCrc(&ModBus[0],i);
			USART_WriteDatas(USART2,ModBus,i);
		}
	}
}
void Task_Lora_UartoLora(void *Tags)
{
	uint8 Length;
	while(1)
	{
		Tos_TaskDelay(1);
		ClearWithBuffer(USART_RX_Buffer[1],50);
		Length=USART_ReadDatas(USART2,Null,50,0);
		if(Length)
		{
			Exit_Init(DISABLE);
			Lora_Write(USART_RX_Buffer[1],Length);
			Tos_TaskDelay(1);
			Exit_Init(ENABLE);
		}
	}
}
  void Task_Loratp401(void *Tags)
{

	uint8 i;
	uint8 SenBuf[21];
	Tos_ArrayMessage *CurMsg,Msg[10];
	uint8 *PBuf,Buf[10][21];	
	for(i=0;i<10;i++)Msg[i].Qmsg_Addr=&Buf[i][0];
	Tos_TaskCreateQmsg(&Msg[0],10);
	TaskLora_Tos_TaskID=Tos_TaskCurrent;
	SpiInit();
	InitRFChip();
	while(1)
	{
		i=ReadReg((u8)(REG_LR_VERSION>>8));
		if(i==0x12)break;
	}
	
	SX1276LoRa_RX_INIT();
	Exit_Init(ENABLE);
	while(1)
	{
		Tos_TaskDelay(100);
		if(USART_ReadDatas(USART2,Null,USART_RX_BUFFER_SIZE,1000))
		{
			SenBuf[0]=USART_RX_Buffer[1][0];
			Lora_Write(SenBuf,10);
		}
		CurMsg=Tos_TaskGetQMsg();
		if(CurMsg)
		{
		PBuf=(uint8 *)(CurMsg->Qmsg_Addr);
		USART_WriteDatas(USART2,PBuf,10);
		Tos_TaskDelay(1);
		}
	}
}


void Task_LoraS(void *Tags)
{  
	uint8 i;
	uint8 SenBuf[21];
	Tos_ArrayMessage *CurMsg,Msg[10];
	uint8 *PBuf,Buf[10][21];	
	for(i=0;i<10;i++)Msg[i].Qmsg_Addr=&Buf[i][0];
	Tos_TaskCreateQmsg(&Msg[0],10);
	TaskLora_Tos_TaskID=Tos_TaskCurrent;
	SpiInit();
	InitRFChip();
	while(1)
	{
		i=ReadReg((u8)(REG_LR_VERSION>>8));
		if(i==0x12)break;
	}
	
	SX1276LoRa_RX_INIT();
	Exit_Init(ENABLE);
	while(1)
	{
		SenBuf[0]=4;
		Tos_TaskDelay(10000);
		Lora_Write(SenBuf,5);
		CurMsg=Tos_TaskGetQMsg();
		if(CurMsg)
		{
		PBuf=(uint8 *)(CurMsg->Qmsg_Addr);
		Exit_Init(DISABLE);
		Lora_Write(PBuf,6);
		Tos_TaskDelay(1);
		Exit_Init(ENABLE);
		}
	}
}
void Task_ModBus(void *Tags)
{
	uint8 i,Addr=0x01;
	uint8 SenBuf[21]={0x01,0x03,0x00,0x01,0x00,0x02};
	Tos_ArrayMessage *CurMsg,Msg[10];
	uint8 *PBuf,Buf[10][21];	
	for(i=0;i<10;i++)Msg[i].Qmsg_Addr=&Buf[i][0];
	Tos_TaskCreateQmsg(&Msg[0],10);
	TaskLora_Tos_TaskID=Tos_TaskCurrent;
	SpiInit();
	InitRFChip();
	while(1)
	{
		i=ReadReg((u8)(REG_LR_VERSION>>8));
		if(i==0x12)break;
	}
	
	SX1276LoRa_RX_INIT();
	Exit_Init(ENABLE);
	while(1)
	{
		SenBuf[0]=4;
		Tos_TaskDelay(100);
		SenBuf[0]=Addr++;
		if(Addr>0x04)Addr=0x01;
		i=MB_AppendCrc(SenBuf,6);
		Lora_Write(SenBuf,i);
		CurMsg=Tos_TaskGetQMsgDelay(2000);
		if(CurMsg)
		{
		PBuf=(uint8 *)(CurMsg->Qmsg_Addr);
		Exit_Init(DISABLE);
		Lora_Write(PBuf,5);
		Tos_TaskDelay(1);
		Exit_Init(ENABLE);
		}
	}
}














