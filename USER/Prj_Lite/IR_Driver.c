/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/

void Exti_EnableIRQ(FunctionalState En)
 {
	 EXTI_ClearITPendingBit(EXTI_Line14);
	 if(En)
	 {
		 			EXTI->PR |= (1<<14);  //先清挂起寄存器
			EXTI->IMR |= (1<<14);//开放中断
	 }else
	 {
		 EXTI->IMR &=~(1<<14);
	 }
 }
 void Exti_IOPort_Init()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	GPIO_InitTypeDef GPIO_InitStructure;
	Exti_EnableIRQ(DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14;                                                                           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource14);
	EXTI_InitStructure.EXTI_Line =EXTI_Line14;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	Exti_EnableIRQ(ENABLE);
}

void EXTI15_10_IRQHandler(void)
{
	uint8 i=0;
	uint16 RedCount;
	uint32 RFData;
  EXTI_ClearITPendingBit(EXTI_Line14);
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14))return;
	Exti_EnableIRQ(DISABLE);
	RFData=0;
	while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)){RedCount++;if(RedCount>100000)goto Exit;}
	if(RedCount<4000){DeBug("IR_Error(%d)",RedCount,1);goto Exit;}
	RedCount=0;
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)){RedCount++;if(RedCount>100000)goto Exit;}
	if(RedCount<4000)goto Hear;
	for(i=2;i<34;i++)
	{
		RedCount=0;
		while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)){RedCount++;if(RedCount>5000)goto Exit;}
		RedCount=0;
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)){RedCount++;if(RedCount>3500)goto Exit;}
		RFData<<=1;
		if(RedCount>2000)RFData|=S0;
	}
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("Task_IR"),0,sizeof(RFData),&RFData);
Exit:
return;
Hear:
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("Task_IR"),1,sizeof(RFData),&RFData);
}
void IR_Moto(uint32 Tags)
{
	if(UIShowValue.SaveValue.RunSpend>90)UIShowValue.SaveValue.RunSpend=80;
	if(UIShowValue.SaveValue.RunSpend<40)UIShowValue.SaveValue.RunSpend=40;
	switch(Tags)
	{
//		case 1:Moto_AB(UIShowValue.SaveValue.RunSpend,0-UIShowValue.SaveValue.RunSpend);Tos_TaskDelay(60);Moto_AB(80,-80);Tos_TaskDelay(100); break;
//		case 2:Moto_AB(0-UIShowValue.SaveValue.RunSpend,UIShowValue.SaveValue.RunSpend);Tos_TaskDelay(60);Moto_AB(-80,80);Tos_TaskDelay(100); break;
//		case 3:Moto_AB(UIShowValue.SaveValue.RunSpend,UIShowValue.SaveValue.RunSpend);Tos_TaskDelay(60);Moto_AB(80,70);Tos_TaskDelay(500); break;
//		case 4:Moto_AB(0-UIShowValue.SaveValue.RunSpend,0-UIShowValue.SaveValue.RunSpend);Tos_TaskDelay(60);Moto_AB(-80,-80);Tos_TaskDelay(500); break;
//		case 5:Moto_AB(-70,-20);Tos_TaskDelay(500); break;
			case 1:Moto_AB(70,-70);break;
			case 2:Moto_AB(-70,70);break;
			case 3:Moto_AB(70,70);break;	
			case 4:Moto_AB(-70,-70);break;
			case 5:Moto_AB(70,70);break;
	}
//	if(UIShowValue.SaveValue.RunMode==2)Moto_AB(UIShowValue.SaveValue.RunSpend,UIShowValue.SaveValue.RunSpend-10);
//	else Moto_AB(0,0);
}


void Task_RedomRgb(void *Tags)
{
	RandomLight(RandomADC(0xffffff,0xff),RandomADC(0xffffff,0xff));
	Tos_TaskDelete(Tos_TaskCurrent);
}
void Task_IR(void *Tags)
{
	uint8 i,TR;
	uint32 Buf[10],*RF;
	uint8 *P;
	Tos_ArrayMessage *CurMsg,Msg[1];
	for(i=0;i<1;i++)Msg[i].Qmsg_Addr=&Buf[0];
	Tos_TaskCreateQmsg(&Msg[0],1);
	Exti_IOPort_Init();
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
				DeBug("Key=%d,Code=%x,RFData=%x",P[1],P[3],*RF,0);
				Beep_DD(500,200,1);
				TR=P[1];
				switch(P[1])
				{
					case 16:Task_Join(IR_Moto,FT_VoidFuncUint32,1);break;
					case 90:Task_Join(IR_Moto,FT_VoidFuncUint32,2);break;
					case 24:Task_Join(IR_Moto,FT_VoidFuncUint32,3);break;
					case 74:Task_Join(IR_Moto,FT_VoidFuncUint32,4);break;
					case 48:Task_Join(IR_Moto,FT_VoidFuncUint32,5);break;
					case 162:WS_Double();UIShowValue.SaveValue.RunMode--;DeBug("Set Mode=%d",UIShowValue.SaveValue.RunMode,0);break;
					case 98:WS_ShadeBit(0x0ffff,0x000000,S2|S3);break;
					case 226:WS_Double();UIShowValue.SaveValue.RunMode++;DeBug("Set Mode=%d",UIShowValue.SaveValue.RunMode,0);break;
					case 144:Task_Join(RandomEYE,FT_VoidFuncVoid,0);break;
					case 56:Moto_AB(0,0);break;
					case 34:WS_Double();UIShowValue.SaveValue.RunSpend-=10;DeBug("Set Speed=%d",UIShowValue.SaveValue.RunSpend,0);Moto_AB(UIShowValue.SaveValue.RunSpend,UIShowValue.SaveValue.RunSpend);break;
					case 2:WS_Double();UIShowValue.SaveValue.RunSpend+=10;DeBug("Set Speed=%d",UIShowValue.SaveValue.RunSpend,0);Moto_AB(UIShowValue.SaveValue.RunSpend,UIShowValue.SaveValue.RunSpend);break;
					case 194:WS_ShadeBit(0xffffff,0x000000,S2|S3);while(1)GPIO_SetIndex(6,0);
				}
				break;
				case 1:
				
				Beep_A2B(300,500);
				switch(TR)
				{
					case 16:Task_Join(IR_Moto,FT_VoidFuncUint32,1);break;
					case 90:Task_Join(IR_Moto,FT_VoidFuncUint32,2);break;
					case 24:Task_Join(IR_Moto,FT_VoidFuncUint32,3);break;
					case 74:Task_Join(IR_Moto,FT_VoidFuncUint32,4);break;
					case 48:Task_Join(IR_Moto,FT_VoidFuncUint32,5);break;
					case 162:WS_Double();UIShowValue.SaveValue.RunMode--;DeBug("Set Mode=%d",UIShowValue.SaveValue.RunMode,0);break;
					case 98:WS_ShadeBit(0x0ffff,0x000000,S2|S3);break;
					case 226:WS_Double();UIShowValue.SaveValue.RunMode++;DeBug("Set Mode=%d",UIShowValue.SaveValue.RunMode,0);break;
					case 144:Task_Join(RandomEYE,FT_VoidFuncVoid,0);break;
					case 56:Moto_AB(0,0);break;
					case 34:WS_Double();UIShowValue.SaveValue.RunSpend-=10;DeBug("Set Speed=%d",UIShowValue.SaveValue.RunSpend,0);Moto_AB(UIShowValue.SaveValue.RunSpend,UIShowValue.SaveValue.RunSpend);break;
					case 2:WS_Double();UIShowValue.SaveValue.RunSpend+=10;DeBug("Set Speed=%d",UIShowValue.SaveValue.RunSpend,0);Moto_AB(UIShowValue.SaveValue.RunSpend,UIShowValue.SaveValue.RunSpend);break;
				}
				break;
			}
			Exti_EnableIRQ(ENABLE);
		}
		Exti_EnableIRQ(ENABLE);
		Tos_TaskDelay(300);
	}
}
void IR_SendH(BOOL H,uint32 D)
{
	uint8 z;
	while(D--)
	{
		GPIO_SetIndex(15,1);
		for(z=0;z<19;z++);
		GPIO_SetIndex(15,0);
		for(z=0;z<163;z++);
	}
}
void IR_Send()
{
	IR_SendH(True,0xffff);
}
