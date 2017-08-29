/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
uint16 Bufg[35];
 void Exti_IOPort_Init(FunctionalState En)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14;                                                                           
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource14);

	EXTI_InitStructure.EXTI_Line =EXTI_Line14;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = En;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = En;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler(void)
{
	uint8 i=0;
	uint16 Temp[2];
	uint16 RedCount;
	uint32 RFData;
  EXTI_ClearITPendingBit(EXTI_Line14);
	Temp[0]=0;Temp[1]=0;
	Exti_IOPort_Init(DISABLE);
	RFData=0;
	while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)){RedCount++;if(RedCount>100000)goto Exit;}
	if(RedCount<4000)goto Exit;
	Bufg[0]=RedCount;
	RedCount=0;
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)){RedCount++;if(RedCount>100000)goto Exit;}
	if(RedCount<4000)goto Hear;
	Bufg[1]=RedCount;
	for(i=2;i<34;i++)
	{
		RedCount=0;
		while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)){RedCount++;if(RedCount>5000)goto Exit;}
		RedCount=0;
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)){RedCount++;if(RedCount>3500)goto Exit;}
		RFData<<=1;
		if(RedCount>2600)RFData|=S0;
		Bufg[i]=RedCount;
	}
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("Task_IR"),0,sizeof(RFData),&RFData);
Exit:
return;
Hear:
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("Task_IR"),1,sizeof(RFData),&RFData);
}
void Task_IR(void *Tags)
{
	uint8 i,TR;
	uint32 Buf[10],*RF;
	uint8 *P;
	Tos_ArrayMessage *CurMsg,Msg[1];
	for(i=0;i<1;i++)Msg[i].Qmsg_Addr=&Buf[0];
	Tos_TaskCreateQmsg(&Msg[0],1);
	Exti_IOPort_Init(ENABLE);
	PwmTimeInt();
	while(1)
	{
		CurMsg=Tos_TaskGetQMsgDelay(10);
		if(CurMsg)
		{
			switch(CurMsg->Qmsg_Type)
			{
				case 0:
				RF=(uint32 *)CurMsg->Qmsg_Addr;
				P=(uint8 *)CurMsg->Qmsg_Addr;
				if(P[0]==(uint8)~P[1])if(P[2]==(uint8)~P[3])
				DeBug("Key=%d",P[1],0);
				DeBug("Code=%x",P[3],0);
				DeBug("RFData=%x",*RF,0);
				Beep_DD(500,200,1);
				TR=P[1];
				switch(P[1])
				{
					case 16:Task_Join(Moto_Right,FT_VoidFuncInt,-100);break;
					case 90:Task_Join(Moto_Right,FT_VoidFuncInt,100);break;
					case 24:Task_Join(Moto_Follow,FT_VoidFuncInt,300);break;
					case 74:Task_Join(Moto_Follow,FT_VoidFuncInt,-300);break;
					case 162:WS_Double();break;
				}
				break;
				case 1:
				DeBug("Hear",0);
				Beep_A2B(300,500);
				switch(TR)
				{
					case 16:Task_Join(Moto_Right,FT_VoidFuncInt,-100);break;
					case 90:Task_Join(Moto_Right,FT_VoidFuncInt,100);break;
					case 24:Task_Join(Moto_Follow,FT_VoidFuncInt,300);break;
					case 74:Task_Join(Moto_Follow,FT_VoidFuncInt,-300);break;
				}
				break;
			}
			Exti_IOPort_Init(ENABLE);
		}
		Exti_IOPort_Init(ENABLE);
		//Tos_TaskDelay(300);
	}
}
