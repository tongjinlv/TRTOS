/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
 #include <GPIO_Driver.h>
 void Exti_EnableIRQ(FunctionalState En)
 {
	 EXTI_ClearITPendingBit(EXTI_Line6);
	 if(En)
	 {
		 			EXTI->PR |= (1<<6);  //先清挂起寄存器
			EXTI->IMR |= (1<<6);//开放中断
	 }else
	 {
		 EXTI->IMR &=~(1<<6);
	 }
 }
 
 void Exti_IOPort_Init()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	GPIO_InitTypeDef GPIO_InitStructure;
	Exti_EnableIRQ(DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6;                                                                           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line =EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	Exti_EnableIRQ(ENABLE);
}

void EXTI9_5_IRQHandler(void)
{
  uint8 i=0;
	uint16 RedCount;
	uint32 RFData;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6))
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
		return ;
	}
	Exti_EnableIRQ(DISABLE);
	RFData=0;
	while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)){RedCount++;if(RedCount>100000)goto Exit;}
	if(RedCount<4000){return;}
	RedCount=0;
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)){RedCount++;if(RedCount>100000)goto Exit;}
	if(RedCount<4000)goto Hear;
	for(i=2;i<34;i++)
	{
		RedCount=0;
		while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)){RedCount++;if(RedCount>5000)goto Exit;}
		RedCount=0;
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)){RedCount++;if(RedCount>3500)goto Exit;}
		RFData<<=1;
		if(RedCount>2000)RFData|=S0;
	}
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("Task_IR"),0,sizeof(RFData),&RFData);
Exit:
return;
Hear:
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("Task_IR"),1,sizeof(RFData),&RFData);

}
extern void SetBlow(uint8 I);
void Task_IR(void *Tags)
{
	uint8 i;
	uint32 Buf[10],*RF;
	uint8 *P;
	Tos_ArrayMessage *CurMsg,Msg[1];
	for(i=0;i<1;i++)Msg[i].Qmsg_Addr=&Buf[0];
	Tos_TaskCreateQmsg(&Msg[0],1);
	Exti_IOPort_Init();
	while(1)
	{
		CurMsg=Tos_TaskGetQMsgDelay(10);
		if(UIShowValue.SysWorkMode&WCB_Open)
		if(CurMsg)
		{
			switch(CurMsg->Qmsg_Type)
			{
				case 0x00:
				if(P[1]==32){if(GPIO_GetIndex(1)){UIShowValue.SysWorkMode|=WCB_Start;GPIO_SetIndex(1,0);}
				else 
								{
									
											GPIO_SetIndex(1,1);
											UIShowValue.SysWorkMode&=~WCB_Start;
											Beep_DD(1000,330,2);
											GPIO_SetIndex(3,1);
								};
								P[1]=0;
							}
				break;
			}
			if(UIShowValue.SysWorkMode&WCB_Start)
			switch(CurMsg->Qmsg_Type)
			{
		case 0x00:
			P=(uint8 *)CurMsg->Qmsg_Addr;
			if(P[0]==(uint8)~P[1])if(P[2]==(uint8)~P[3])DeBug("Key=%d,Code=%x,RFData=%x",P[1],P[3],*RF,0);
		GPIO_SetIndex(6,1);
			Beep_DD(1000,600,1);
			Exti_EnableIRQ(ENABLE);
			if(P[3]==0x80)
			switch(P[1])
			{
				case 192:UIShowValue.SaveValue.BlowerNum=0;DeBug("设置风扇%d",UIShowValue.SaveValue.BlowerNum,5);SetBlow(UIShowValue.SaveValue.BlowerNum);break;
				case 224:UIShowValue.SaveValue.BlowerNum=1;DeBug("设置风扇%d",UIShowValue.SaveValue.BlowerNum,5);SetBlow(UIShowValue.SaveValue.BlowerNum);break;
				case 96:UIShowValue.SaveValue.BlowerNum=2;DeBug("设置风扇%d",UIShowValue.SaveValue.BlowerNum,5);SetBlow(UIShowValue.SaveValue.BlowerNum);break;
				case 16:UIShowValue.SaveValue.BlowerNum=3;DeBug("设置风扇%d",UIShowValue.SaveValue.BlowerNum,5);SetBlow(UIShowValue.SaveValue.BlowerNum);break;
				case 160:UIShowValue.SaveValue.BlowerNum=4;DeBug("设置风扇%d",UIShowValue.SaveValue.BlowerNum,5);SetBlow(UIShowValue.SaveValue.BlowerNum);break;
				case 80:UIShowValue.SaveValue.BlowerNum=4;DeBug("设置风扇%d",UIShowValue.SaveValue.BlowerNum,5);SetBlow(UIShowValue.SaveValue.BlowerNum);break;
				case 144:UIShowValue.SaveValue.LampNum++;if(UIShowValue.SaveValue.LampNum>1)UIShowValue.SaveValue.LampNum=0;DeBug("设置灯亮度%d",UIShowValue.SaveValue.LampNum,5);
				
				GPIO_SetIndex(3,UIShowValue.SaveValue.LampNum);
				break;
				case 208:
					if(UIShowValue.ShowFlag&WSB_OpenAirCleaner)UIShowValue.ShowFlag&=~WSB_OpenAirCleaner;else UIShowValue.ShowFlag|=WSB_OpenAirCleaner;
					if(UIShowValue.ShowFlag&WSB_OpenAirCleaner)GPIO_SetIndex(7,1);else GPIO_SetIndex(7,0);
					break;
				case 32:if(GPIO_GetIndex(1)){UIShowValue.SysWorkMode|=WCB_Start;GPIO_SetIndex(1,0);}else {GPIO_SetIndex(1,1);UIShowValue.SysWorkMode&=~WCB_Start;}break;
				case 0x80:	GPIO_SetIndex(0,1);GPIO_SetIndex(2,0);Tos_TaskDelay(800);GPIO_SetIndex(0,0);break;
				case 0x40:	GPIO_SetIndex(0,0);GPIO_SetIndex(2,1);Tos_TaskDelay(800);GPIO_SetIndex(2,0);break;
			}
			break;
			}
			
		}
		Exti_EnableIRQ(ENABLE);
		Tos_TaskDelay(30);
	}
}
