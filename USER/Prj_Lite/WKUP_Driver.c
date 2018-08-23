/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
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
  void Sys_Standby1(void) //�ڻ��ѳ�ʼ���е���
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);//ʹ�� GPIOA �͸��ù���ʱ��
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;    //PA.0
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ�� IO

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

	if(Check_up() == 0)   //ϵͳ��ʼ��������û�а��°�����������ϵͳֱ�ӽ����˴���ģʽ�ˣ����������˳���û���κη�Ӧ������Ҫ��Ϊ�Ļ��ѣ�������֪��˯�����ѡ���
	{
		Sys_Standby1();         //�������ģʽ
	}      
 }

void Sys_Enter_Standby1(void)//���жϺ�������ã�������λ��Ȼ��������ģʽ
{				 
	 RCC_APB2PeriphResetCmd(0X01FC,DISABLE);	 //������ֻ�Ǹ�λ��IO�ڡ�������0x01fc����ô���ġ�������뿴RCC_APB2RSTR(��ͼ)
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



