/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
void Exit_Init(FunctionalState En)
{
	NVIC_InitTypeDef NVIC_InitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;                                                                           
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   
  GPIO_Init(GPIOB, &GPIO_InitStructure);
   
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);
  EXTI_InitStructure.EXTI_Line = EXTI_Line2;                                       
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                          
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;                 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);        //设置优先级：抢先优先级0个，子优先级4位（16个）
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;        // 使能设置的外部中断通道请求

	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;     //将中断挂到PA1脚外部中断线1上
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;     //设置子优先级1
	NVIC_Init(&NVIC_InitStructure);                      //初始化
}
 void Exti_IOPort_Init(void)
{
        EXTI_InitTypeDef EXTI_InitStructure;
        NVIC_InitTypeDef NVIC_InitStructure;
        
		GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;                                                                           
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   
  GPIO_Init(GPIOB, &GPIO_InitStructure);
   
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);

        EXTI_InitStructure.EXTI_Line =EXTI_Line8;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
}
void EXTI9_5_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line8);
	EXTI_ClearFlag(EXTI_Line8);
	MCU_Reset();
}
void TOS_Sleep(uint8 Min)
{
	
	Date_Time DateTime;
	ISL1208_GetDateTime(&UIShowValue.DateTime);	
	ISL1208_GetDateTime(&DateTime);	
	if(Min==0xff)
	{

	}else
	{
		DateTime.Min+=Min;
		if(DateTime.Min>=59){DateTime.Hour++;DateTime.Min-=59;}
		if(DateTime.Hour>=24)DateTime.Hour=0;
	}
	ISL1208_SetAlarm(DateTime.Hour,DateTime.Min,DateTime.Sec,S2|S1|S0);
	DeBug("进入休眠%d %d %d",UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,UIShowValue.DateTime.Sec,6);
	DeBug("闹钟设置%d %d %d",DateTime.Hour,DateTime.Min,DateTime.Sec,6);
	Exit_Init(ENABLE);
	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);
	GPIO_DeInit(GPIOE);
Exti_IOPort_Init();
	Standby_Init(False);
}
void Task_Plan3()
{
	static uint8 i=0,c=0,b=0;
	static uint32 Pool;
	uint16 T;
	T=FlowPoolFilter(&Pool,UIShowValue.ADC[0],&b,10);
	//UIShowValue.CH_Value[2]=T*2.5/2048;
	c++;
	if(c>20)
	{
		c--;
		if(UIShowValue.CH_Value[0]>UIShowValue.CH_Hold[0].Max)UIShowValue.CH_Hold[0].Max=UIShowValue.CH_Value[0];
		if(UIShowValue.CH_Value[1]>UIShowValue.CH_Hold[1].Max)UIShowValue.CH_Hold[1].Max=UIShowValue.CH_Value[1];
		if(UIShowValue.CH_Value[0]<UIShowValue.CH_Hold[0].Min)UIShowValue.CH_Hold[0].Min=UIShowValue.CH_Value[0];
		if(UIShowValue.CH_Value[1]<UIShowValue.CH_Hold[1].Min)UIShowValue.CH_Hold[1].Min=UIShowValue.CH_Value[1];
	}
	if(UIShowValue.RunFlag&WRF_SensorCH1Connected)
	{
	if(UIShowValue.CH_Value[0]>=UIShowValue.SaveValue.CH_Limit[0].Max)UIShowValue.RunFlag|=WRF_CH1Max;else UIShowValue.RunFlag&=~WRF_CH1Max;
	if(UIShowValue.CH_Value[0]<=UIShowValue.SaveValue.CH_Limit[0].Min)UIShowValue.RunFlag|=WRF_CH1Min;else UIShowValue.RunFlag&=~WRF_CH1Min;
	}
	if(UIShowValue.RunFlag&WRF_SensorCH2Connected)
	{
	if(UIShowValue.CH_Value[1]>=UIShowValue.SaveValue.CH_Limit[1].Max)UIShowValue.RunFlag|=WRF_CH2Max;else UIShowValue.RunFlag&=~WRF_CH2Max;
	if(UIShowValue.CH_Value[1]<=UIShowValue.SaveValue.CH_Limit[1].Min)UIShowValue.RunFlag|=WRF_CH2Min;else UIShowValue.RunFlag&=~WRF_CH2Min;
	}
	if(UIShowValue.CH_Value[2]<3.3)i++;
	else i=0;
}
void TaskPlan(void *Tags)
{
	static float CHValue[2];
	ADC1_Init((uintbus)&UIShowValue.ADC[0]);
	Sensor_Init();
	ISL1208_Init((void *)IO_ISL1208_P);
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	Tos_TaskDelay(1000);
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	UIShowValue.RecordCount=Get_PrintfRecordCount();
	while(1)
	{
		ISL1208_GetDateTime(&UIShowValue.DateTime);	
		//DeBug("20%02d-%02d-%02d %02d:%02d",UIShowValue.DateTime.Year,UIShowValue.DateTime.Mon,UIShowValue.DateTime.Day,UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,0);
		Tos_TaskDelay(500);
		DS_Read_Value(&CHValue[0],&CHValue[1]);
		UIShowValue.CH_Value[0]=UIShowValue.SaveValue.CorrectValue[0]+CHValue[0];
		UIShowValue.CH_Value[1]=UIShowValue.SaveValue.CorrectValue[1]+CHValue[1];
		if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)Task_Record();
		Task_Plan();
	}
}
float GetTemp(uint8 *Buf)
{
  float Value;
  uint16 t;
	if(Buf[0]==0)if(Buf[1]==0)return 0;
  t=Buf[0];
  t*=0xff;
  t|=Buf[1];
  t &= ~0x0003;     
  Value= -46.85 + 175.72/65536 *(float)t; 
  return Value;
}
float GetHmi(uint8 *Buf)
{
  float Value;
  uint16 t;
	if(Buf[0]==0)if(Buf[1]==0)return 0;
  t=Buf[0];
  t*=0xff;
  t|=Buf[1];
  t &= ~0x0003;       
  Value = -6.0 + 125.0/65536 * (float)t; 
  return Value;
}
void Read_433Value(uint8 i,float *V1,float *V2)
{
	if(i==USART_RX_Buffer[3][1])
	{
	*V1=GetTemp(&USART_RX_Buffer[3][2]);
	*V2=GetHmi(&USART_RX_Buffer[3][4]);
	}
	if(i==USART_RX_Buffer[3][1])
	{
		*V1=GetTemp(&USART_RX_Buffer[3][2]);
		*V2=GetHmi(&USART_RX_Buffer[3][4]);
	}
}
void TaskPlan3(void *Tags)
{
	static float CHValue[2];
	ADC1_Init((uintbus)&UIShowValue.ADC[0]);
	Sensor_Init();
	ISL1208_Init((void *)IO_ISL1208_P);
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	Tos_TaskDelay(1000);
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	UIShowValue.RecordCount=Get_PrintfRecordCount();
	while(1)
	{
		ISL1208_GetDateTime(&UIShowValue.DateTime);	
		//DeBug("20%02d-%02d-%02d %02d:%02d",UIShowValue.DateTime.Year,UIShowValue.DateTime.Mon,UIShowValue.DateTime.Day,UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,0);
		Tos_TaskDelay(500);
		Read_433Value(1,&CHValue[0],&CHValue[1]);
		Read_433Value(2,&UIShowValue.GPS_Longitude,&UIShowValue.GPS_Latitude);
		UIShowValue.CH_Value[0]=UIShowValue.SaveValue.CorrectValue[0]+CHValue[0];
		UIShowValue.CH_Value[1]=UIShowValue.SaveValue.CorrectValue[1]+CHValue[1];
		if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)Task_Record();
		Task_Plan();
	}
}
void TaskPlan1(void *Tags)
{
	ADC1_Init((uintbus)&UIShowValue.ADC[0]);
	Sensor_Init();
	ISL1208_Init((void *)IO_ISL1208_P);
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	Tos_TaskDelay(1000);
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	UIShowValue.RecordCount=Get_PrintfRecordCount();
	while(1)
	{
		ISL1208_GetDateTime(&UIShowValue.DateTime);	
		//DeBug("20%02d-%02d-%02d %02d:%02d",UIShowValue.DateTime.Year,UIShowValue.DateTime.Mon,UIShowValue.DateTime.Day,UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,0);
		Tos_TaskDelay(500);

		if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)Task_Record();
		Task_Plan();
	}
}

void TaskBigShow()
{
	uint8 i=30;
	while(i--)
	{
	IO_Set(1,False);
	IO_Set(0,False);
	Tos_TaskDelay(100);
	IO_Set(1,True);
	IO_Set(0,True);
	Tos_TaskDelay(100);
	}
}
void Task_433ToValue(void *Tags)
{
	uint8 Length,Addr,z;
	BufferFill(USART_RX_Buffer[3],0x00,20);
	while(1)
	{                                                        
		Tos_TaskDelay(2);
		Length=USART_ReadDatas(UART4,0,100,0);
		if(Length)
		{
				Printf_Bytes(USART_RX_Buffer[3],Length);
				UIShowValue.CH_Value[2]=(float)USART_RX_Buffer[3][7]/100+2;
		}
	}
}
