
void Moto_AB1(char a,char b)
{
	if(a>0)
		{
			GPIO_SetIndex(9,1);
				GPIO_SetIndex(11,0);
		}else
		if(a<0)
		{
			GPIO_SetIndex(9,1);
				GPIO_SetIndex(11,1);
		}else
		{
			GPIO_SetIndex(9,0);
				GPIO_SetIndex(11,0);
		}
		if(b>0)
		{
				GPIO_SetIndex(8,1);
				GPIO_SetIndex(10,1);
		}else
		if(b<0)
		{
			GPIO_SetIndex(8,1);
				GPIO_SetIndex(10,0);
		}else
		{
			GPIO_SetIndex(8,0);
				GPIO_SetIndex(10,1);
		}
}
void Delay1(uint32 i)
{
	i=0x3fff;
	while(i--);
}
void Task_Power_App2(void *Tags)
{
		uint8  CCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};   //逆时钟旋转相序表
uint8 CW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    //正时钟旋转相序表
uint8 i;
	while(1)
	{
			Moto_AB1(0,100);
		Delay1(1);
			Moto_AB1(100,100);
		Delay1(1);
			Moto_AB1(100,0);
		Delay1(1);
			Moto_AB1(-100,-100);
		Delay1(1);
		Moto_AB1(0,-100);
		Delay1(1);
		Moto_AB1(-100,-100);
		Delay1(1);
		Moto_AB1(-100,0);
		Delay1(1);
		Moto_AB1(-100,100);
		Delay1(1);
		Moto_AB1(100,100);
		//	GPIO_SetIndex(8,1);
		//		GPIO_SetIndex(10,1);
	//	GPIO_SetIndex(9,1);
	//			GPIO_SetIndex(11,0);
			Tos_TaskDelay(1);
	}
}
void Task_Power_App1(void *Tags)
{
	uint8 i;
	Tos_ArrayMessage Msg[5];
	MGUI_KeyMsg *TaskMsg,TaskMsgBuf[5];    
	for(i=0;i<5;i++)Msg[i].Qmsg_Addr=&TaskMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],5);
	Tos_TaskGetHandKey();
	GPIO_SetIndex(7,0);//复用按钮输入
	Beep_ON();
	while(1)
	{
		  TaskMsg=MUI_GetKey(0);
			if(TaskMsg)
			{
				DeBug("%d,%d",TaskMsg->KeyType,TaskMsg->KeyValue,2);
				 if(TaskMsg->KeyValue==Key_Enter)if(TaskMsg->KeyType==Key_DownTimeOut)
				 {
					WS_SetColorBit(0xffffff,S0|S1|S2|S3);
					Beep_OFF();
					WS_SetColorBit(0x0,S0|S1|S2|S3);
					Tos_TaskDelay(1000);
					while(1)
					{
					GPIO_SetIndex(6,0);
					}
				 }
			}
				
	
	}
}
void Task_App1(void *Tags)
{
	while(1)
	{
		Tos_TaskDelay(1000); 
		GPIO_SetIndex(0,0);
		GPIO_SetIndex(1,0);
		Tos_TaskDelay(10); 
		GPIO_SetIndex(0,1);
		GPIO_SetIndex(1,1);
		Tos_TaskDelay(100); 
		GPIO_SetIndex(0,0);
		GPIO_SetIndex(1,0);
		Tos_TaskDelay(10); 
		GPIO_SetIndex(0,1);
		GPIO_SetIndex(1,1); 
		DeBug("dddd",4);
	}
}
