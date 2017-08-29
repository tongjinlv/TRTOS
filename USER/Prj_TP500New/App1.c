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

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;                                                                           
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   
  GPIO_Init(GPIOC, &GPIO_InitStructure);
   
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;                                       
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                          
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;                 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);        //设置优先级：抢先优先级0个，子优先级4位（16个）
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;        // 使能设置的外部中断通道请求

	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;     //将中断挂到PA1脚外部中断线1上
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;     //设置子优先级1
	NVIC_Init(&NVIC_InitStructure);                      //初始化
}
void GPIO_Set_ShowOnly()
{     
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;            
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	E3V3_ON;
}

void TOS_Sleep(uint8 Min)
{
	
	Date_Time DateTime;
	ISL1208_GetDateTime(&UIShowValue.DateTime);	
	ISL1208_GetDateTime(&DateTime);	
	DateTime.Min+=Min;
	if(DateTime.Min>=59){DateTime.Hour++;DateTime.Min-=59;}
	if(DateTime.Hour>=24)DateTime.Hour=0;
	ISL1208_SetAlarm(DateTime.Hour,DateTime.Min,DateTime.Sec,S2|S1|S0);
	DeBug("进入休眠%d %d %d",UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,UIShowValue.DateTime.Sec,6);
	DeBug("闹钟设置%d %d %d",DateTime.Hour,DateTime.Min,DateTime.Sec,6);
	Exit_Init(ENABLE);
	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);
	GPIO_DeInit(GPIOE);
	E3V3_OFF;
	if(UIShowValue.SaveValue.WorkBit&WCB_SleepShow)GPIO_Set_ShowOnly();
	Standby_Init(False);//岳总这里为假
}
void TaskFunc(void *Tags)
{
	uint8 i;
	Tos_ArrayMessage Msg[2];
	MGUI_KeyMsg *KeyMsg,KeyMsgBuf[2];	
	Tos_TaskGetHandKey();
  for(i=0;i<2;i++)Msg[i].Qmsg_Addr=&KeyMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],2);
	i=0;
	if(UIShowValue.SysWorkMode==0xff)
	while(1)
	{
		Ht1621_DrawMenu(i);
		Tos_TaskDelay(10);
		KeyMsg=MUI_GetKey(0);
		if(KeyMsg)
		{
			if(KeyMsg->KeyValue==Key_Printf)break;
			if(KeyMsg->KeyValue==Key_UpDown)i++;
			if(i>4)i=0;
		}
	}
	UIShowValue.SysWorkMode=i;
	while(1)
	{
		Tos_TaskDelay(10);
		KeyMsg=MUI_GetKey(0);
		if(KeyMsg)
		{
			if(KeyMsg->KeyValue==Key_Printf)if(KeyMsg->KeyType==Key_OneClick)
			{
				if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)Task_PrintfLog();
				else {if(UIShowValue.RunFlag&WRF_BeepDisable)UIShowValue.RunFlag&=~WRF_BeepDisable;else UIShowValue.RunFlag|=WRF_BeepDisable;}
			}
			if(KeyMsg->KeyValue==Key_Printf)if(KeyMsg->KeyType==Key_DownTimeOut)
			{
				if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)UIShowValue.SaveValue.WorkBit&=~WCB_RecordEN;else UIShowValue.SaveValue.WorkBit|=WCB_RecordEN;
				BEEP_Double();
				UIShowValue.RecordCount=0;
			  W25Q16_Erase(0,sizeof(NandHistoryRecord)*0xff);
				Task_SaveConfigs();
			}
			if(KeyMsg->KeyValue==Key_UpDown)if(KeyMsg->KeyType==Key_OneClick)
			{
				if(UIShowValue.RunFlag&WRF_BeepDisable)UIShowValue.RunFlag&=~WRF_BeepDisable;else UIShowValue.RunFlag|=WRF_BeepDisable;
			}
			if(KeyMsg->KeyValue==Key_WkUp)if(KeyMsg->KeyType==Key_DownTimeOut)
			{
				Exit_Init(DISABLE);
				ISL1208_SetAlarm(0,0,0,0);
				BEEP_Double();
				GPIO_DeInit(GPIOA);
				GPIO_DeInit(GPIOB);
				GPIO_DeInit(GPIOC);
				GPIO_DeInit(GPIOD);
				GPIO_DeInit(GPIOE);
				Standby_Init(True);
			}
			if(KeyMsg->KeyValue==Key_UpDown)if(KeyMsg->KeyType==Key_DownTimeOut)
			{
				BEEP_Double();
				UIShowValue.SysWorkMode=8;
				while(1)
				{
					Ht1621_DrawUpDown(UIShowValue.SysWorkMode-8);
					Tos_TaskDelay(10);
					KeyMsg=MUI_GetKey(0);
					if(KeyMsg)
					{
						if(KeyMsg->KeyValue==Key_UpDown)if(KeyMsg->KeyType==Key_OneClick)
						{
							UIShowValue.SysWorkMode++;
							if(UIShowValue.SysWorkMode>12)UIShowValue.SysWorkMode=8;
						}
						if(KeyMsg->KeyValue==Key_UpDown)if(KeyMsg->KeyType==Key_DownTimeOut)
							{
						  BEEP_Double();
							UIShowValue.SysWorkMode=0;
							break;
							}
						if(KeyMsg->KeyValue==Key_Printf)if(KeyMsg->KeyType==Key_OneClick)
							{
						  BEEP_Double();
							UIShowValue.SysWorkMode=0;
							break;
							}
					}
				}
			}
				
		}
	}
}
void TaskFunc1(void *Tags)
{
	uint8 i;
	Tos_ArrayMessage Msg[2];
	MGUI_KeyMsg *KeyMsg,KeyMsgBuf[2];	
	Tos_TaskGetHandKey();
  for(i=0;i<2;i++)Msg[i].Qmsg_Addr=&KeyMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],2);
	i=0;
	if(UIShowValue.SysWorkMode==0xff)
	while(1)
	{
		Ht1621_DrawMenu(i);
		Tos_TaskDelay(10);
		KeyMsg=MUI_GetKey(0);
		if(KeyMsg)
		{
			if(KeyMsg->KeyValue==Key_Printf)break;
			if(KeyMsg->KeyValue==Key_UpDown)i++;
			if(i>4)i=0;
		}
	}
	UIShowValue.SysWorkMode=i;
	while(1)
	{
		Tos_TaskDelay(10);
		KeyMsg=MUI_GetKey(0);
		if(KeyMsg)
		{
			if(KeyMsg->KeyValue==Key_Printf)if(KeyMsg->KeyType==Key_OneClick)
			{
				if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)Task_PrintfLog();
				else {Task_PrintfCurOnlyOne();}
			}
			if(KeyMsg->KeyValue==Key_Printf)if(KeyMsg->KeyType==Key_DownTimeOut)
			{
				if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)UIShowValue.SaveValue.WorkBit&=~WCB_RecordEN;else UIShowValue.SaveValue.WorkBit|=WCB_RecordEN;
				BEEP_Double();
				UIShowValue.RecordCount=0;
			  W25Q16_Erase(0,sizeof(NandHistoryRecord)*0xff);
				Task_SaveConfigs();
			}
			if(KeyMsg->KeyValue==Key_UpDown)if(KeyMsg->KeyType==Key_OneClick)
			{
				if(UIShowValue.RunFlag&WRF_BeepDisable)UIShowValue.RunFlag&=~WRF_BeepDisable;else UIShowValue.RunFlag|=WRF_BeepDisable;
			}
			if(KeyMsg->KeyValue==Key_WkUp)if(KeyMsg->KeyType==Key_DownTimeOut)
			{
				Exit_Init(DISABLE);
				ISL1208_SetAlarm(0,0,0,0);
				BEEP_Double();
				GPIO_DeInit(GPIOA);
				GPIO_DeInit(GPIOB);
				GPIO_DeInit(GPIOC);
				GPIO_DeInit(GPIOD);
				GPIO_DeInit(GPIOE);
				Standby_Init(True);
			}
			if(KeyMsg->KeyValue==Key_UpDown)if(KeyMsg->KeyType==Key_DownTimeOut)
			{
				BEEP_Double();
				UIShowValue.SysWorkMode=8;
				while(1)
				{
					Ht1621_DrawUpDown(UIShowValue.SysWorkMode-8);
					Tos_TaskDelay(10);
					KeyMsg=MUI_GetKey(0);
					if(KeyMsg)
					{
						if(KeyMsg->KeyValue==Key_UpDown)if(KeyMsg->KeyType==Key_OneClick)
						{
							UIShowValue.SysWorkMode++;
							if(UIShowValue.SysWorkMode>12)UIShowValue.SysWorkMode=8;
						}
						if(KeyMsg->KeyValue==Key_UpDown)if(KeyMsg->KeyType==Key_DownTimeOut)
							{
						  BEEP_Double();
							UIShowValue.SysWorkMode=0;
							break;
							}
						if(KeyMsg->KeyValue==Key_Printf)if(KeyMsg->KeyType==Key_OneClick)
							{
						  BEEP_Double();
							UIShowValue.SysWorkMode=0;
							break;
							}
					}
				}
			}
				
		}
	}
}
void CheckError(float *Value1,float *Value2)
{
	static uint32 Pool1,Pool2;
	uint16 TV1,TV2;
	static uint8 PoolIndex1,PoolIndex2;
	TV1=(uint16)(*Value1*10);
	TV2=(uint16)(*Value2*10);
	TV1=FlowPoolFilter(&Pool1,TV1,&PoolIndex1,6);
	TV2=FlowPoolFilter(&Pool2,TV2,&PoolIndex2,6);
	
	if(UIShowValue.RunFlag&WRF_SensorCH1Connected)if(Abs(TV1-(*Value1*10))>1000)*Value1=(float)TV1/10;
	if(UIShowValue.RunFlag&WRF_SensorCH2Connected)if(Abs(TV2-(*Value2*10))>1000)*Value2=(float)TV2/10;
}
void FitelValue(float *Value1,float *Value2)
{
	static uint32 Pool1,Pool2;
	uint16 TV1,TV2;
	static uint8 PoolIndex1,PoolIndex2;
	TV1=(uint16)((*Value1+50)*10);
	TV2=(uint16)((*Value2+50)*10);
	TV1=FlowPoolFilter(&Pool1,TV1,&PoolIndex1,30);
	TV2=FlowPoolFilter(&Pool2,TV2,&PoolIndex2,30);
	*Value1=(float)TV1/10-50;
	*Value2=(float)TV2/10-50;
	//if(UIShowValue.RunFlag&WRF_SensorCH1Connected)if(Abs(TV1-(*Value1*10))>1000)*Value1=(float)TV1/10;
	//if(UIShowValue.RunFlag&WRF_SensorCH2Connected)if(Abs(TV2-(*Value2*10))>1000)*Value2=(float)TV2/10;
}
void TaskPlan(void *Tags)
{
	static float CHValue[2];
	ADC1_Init((uintbus)&UIShowValue.ADC[0]);
	ISL1208_Init((void *)IO_ISL1208_P);
	Sensor_Init();
	Tos_TaskDelay(3000);
	ISL1208_GetDateTime(&UIShowValue.DateTime);	
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	UIShowValue.RecordCount=Get_PrintfRecordCount();
	
	while(1)
	{
		ISL1208_GetDateTime(&UIShowValue.DateTime);	
		Tos_TaskDelay(500);
		DS_Read_Value(&CHValue[0],&CHValue[1]);
		//FitelValue(&CHValue[0],&CHValue[1]);
		UIShowValue.CH_Value[0]=UIShowValue.SaveValue.CorrectValue[0]+CHValue[0];
		UIShowValue.CH_Value[1]=UIShowValue.SaveValue.CorrectValue[1]+CHValue[1];
		if(0)UIShowValue.CH_Value[1]=UIShowValue.SaveValue.CorrectValue[1]+CHValue[1]+(CHValue[0]-(int)CHValue[0]);//高湿度加跳变
		if(0)
		{
			if(UIShowValue.CH_Value[0]>=UIShowValue.SaveValue.CH_Limit[0].Max)UIShowValue.CH_Value[0]=(UIShowValue.SaveValue.CH_Limit[0].Max*0.98+UIShowValue.CH_Value[0]*0.01);
			if(UIShowValue.CH_Value[0]<=UIShowValue.SaveValue.CH_Limit[0].Min)UIShowValue.CH_Value[0]=(UIShowValue.SaveValue.CH_Limit[0].Min+UIShowValue.CH_Value[0]*0.01);
			if(UIShowValue.CH_Value[1]>=UIShowValue.SaveValue.CH_Limit[1].Max)UIShowValue.CH_Value[1]=(UIShowValue.SaveValue.CH_Limit[1].Max*0.98+UIShowValue.CH_Value[1]*0.01);
			if(UIShowValue.CH_Value[1]<=UIShowValue.SaveValue.CH_Limit[1].Min)UIShowValue.CH_Value[1]=(UIShowValue.SaveValue.CH_Limit[1].Min+UIShowValue.CH_Value[1]*0.01);
		}
		Task_Plan();
		if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)Task_Record();
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4))UIShowValue.RunFlag|=WRF_USB_Connected;else UIShowValue.RunFlag&=~WRF_USB_Connected;
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5))UIShowValue.RunFlag|=WRF_EXP_Connected;else UIShowValue.RunFlag&=~WRF_EXP_Connected;//连接12v电池改这里
	}
}
void TaskPlan1(void *Tags)
{
	static float CHValue[2];
	ADC1_Init((uintbus)&UIShowValue.ADC[0]);
	ISL1208_Init((void *)IO_ISL1208_P);
	Sensor_Init();
	Tos_TaskDelay(3000);
	ISL1208_GetDateTime(&UIShowValue.DateTime);	
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	UIShowValue.RecordCount=Get_PrintfRecordCount();
	while(1)
	{
		ISL1208_GetDateTime(&UIShowValue.DateTime);	
		Tos_TaskDelay(500);
		AS_Read_Value(&CHValue[0],&CHValue[1]);
		UIShowValue.CH_Value[0]=UIShowValue.SaveValue.CorrectValue[0]*CHValue[0];
		UIShowValue.CH_Value[1]=UIShowValue.SaveValue.CorrectValue[1]*CHValue[1];
		if(0)UIShowValue.CH_Value[1]=UIShowValue.SaveValue.CorrectValue[1]+CHValue[1]+(CHValue[0]-(int)CHValue[0]);//高湿度加跳变
		if(0)//压缩范围的
		{
			if(UIShowValue.CH_Value[0]>=UIShowValue.SaveValue.CH_Limit[0].Max)UIShowValue.CH_Value[0]=(UIShowValue.SaveValue.CH_Limit[0].Max*0.98+UIShowValue.CH_Value[0]*0.01);
			if(UIShowValue.CH_Value[0]<=UIShowValue.SaveValue.CH_Limit[0].Min)UIShowValue.CH_Value[0]=(UIShowValue.SaveValue.CH_Limit[0].Min+UIShowValue.CH_Value[0]*0.01);
			if(UIShowValue.CH_Value[1]>=UIShowValue.SaveValue.CH_Limit[1].Max)UIShowValue.CH_Value[1]=(UIShowValue.SaveValue.CH_Limit[1].Max*0.98+UIShowValue.CH_Value[1]*0.01);
			if(UIShowValue.CH_Value[1]<=UIShowValue.SaveValue.CH_Limit[1].Min)UIShowValue.CH_Value[1]=(UIShowValue.SaveValue.CH_Limit[1].Min+UIShowValue.CH_Value[1]*0.01);
		}
		Task_Plan();
		if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)Task_Record();
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4))UIShowValue.RunFlag|=WRF_USB_Connected;else UIShowValue.RunFlag&=~WRF_USB_Connected;
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5))UIShowValue.RunFlag|=WRF_EXP_Connected;else UIShowValue.RunFlag&=~WRF_EXP_Connected;
	}
}
void TaskPlan2(void *Tags)
{
	static float CHValue[2];
	ADC1_Init((uintbus)&UIShowValue.ADC[0]);
	ISL1208_Init((void *)IO_ISL1208_P);
	Sensor_Init();
	Tos_TaskDelay(3000);
	ISL1208_GetDateTime(&UIShowValue.DateTime);	
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	UIShowValue.RecordCount=Get_PrintfRecordCount();
	while(1)
	{
		ISL1208_GetDateTime(&UIShowValue.DateTime);	
		Tos_TaskDelay(500);
		IO_Read_Value(&CHValue[0],&CHValue[1]);
		UIShowValue.CH_Value[0]=!CHValue[0];
		UIShowValue.CH_Value[1]=!CHValue[1];
		Task_Plan();
		if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)Task_Record();
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4))UIShowValue.RunFlag|=WRF_USB_Connected;else UIShowValue.RunFlag&=~WRF_USB_Connected;
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5))UIShowValue.RunFlag|=WRF_EXP_Connected;else UIShowValue.RunFlag&=~WRF_EXP_Connected;
	}
}
void TaskPlan3(void *Tags)
{
	ADC1_Init((uintbus)&UIShowValue.ADC[0]);
	ISL1208_Init((void *)IO_ISL1208_P);
	Sensor_Init();
	Tos_TaskDelay(3000);
	ISL1208_GetDateTime(&UIShowValue.DateTime);	
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	DS_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	UIShowValue.RecordCount=Get_PrintfRecordCount();
	while(1)
	{
		ISL1208_GetDateTime(&UIShowValue.DateTime);	
		Tos_TaskDelay(500);
		Task_Plan();
		if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)Task_Record();
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4))UIShowValue.RunFlag|=WRF_USB_Connected;else UIShowValue.RunFlag&=~WRF_USB_Connected;
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5))UIShowValue.RunFlag|=WRF_EXP_Connected;else UIShowValue.RunFlag&=~WRF_EXP_Connected;//连接12v电池改这里
	}
}
void TaskBigShow()
{
	BEEP_ON;
	LED1_ON;
	LED2_ON;
	Tos_TaskDelay(100);
	BEEP_OFF;
	LED1_OFF;
	LED2_OFF;
	Tos_TaskDelay(100);
	BEEP_ON;
	LED1_ON;
	LED2_ON;
	Tos_TaskDelay(100);
	BEEP_OFF;
	LED1_OFF;
	LED2_OFF;
}

