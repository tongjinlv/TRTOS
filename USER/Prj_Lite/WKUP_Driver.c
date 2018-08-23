/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
void delay_ms(uint16 z)
{
	uint16 i;
	while(z--)for(i=0;i<1000;i++);
}
u8 Check_up(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
}
  void Sys_Standby1(void) //在唤醒初始化中调用
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	PWR_WakeUpPinCmd(ENABLE);
	PWR_EnterSTANDBYMode();		  
}
void Wkup_Init(void)
 {   
	GPIO_InitTypeDef   GPIO_InitStructure;      
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);//使能 GPIOA 和复用功能时钟
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;    //PA.0
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;//上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化 IO

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

	EXTI_InitStructure.EXTI_Line = EXTI_Line0; //PA0        
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;   
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
	NVIC_Init(&NVIC_InitStructure);   

	if(Check_up() == 0)   //系统初始化后由于没有按下按键、、所以系统直接进入了待机模式了，所以下载了程序没有任何反应、、需要人为的唤醒：死猪，就知道睡，快醒、、
	{
		Sys_Standby1();         //进入待机模式
	}      
 }

void Sys_Enter_Standby1(void)//在中断函数里调用，用来复位，然后进入待机模式
{				 
	 RCC_APB2PeriphResetCmd(0X01FC,DISABLE);	 //在这里只是复位了IO口、、至于0x01fc是怎么来的、、大家请看RCC_APB2RSTR(下图)
	 Sys_Standby1();
}
void EXTI0_IRQHandler2(void)
{                                                          
		EXTI_ClearITPendingBit(EXTI_Line0); 
	 // if(Check_up())
		{          
				Sys_Enter_Standby1();  
		}
}



