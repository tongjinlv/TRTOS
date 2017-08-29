/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <DeBug.h>
#include <Board_Driver.h>
/**************************************************************************************
 Func: ����JTAG������SWD����
 Time: 2015-9-02
 Ver.: V1.0
 Note;
**************************************************************************************/
void Remap_SWJ_JTAGDisable()
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
	while(1)
	{	DeBug_Get();
		DeBug("ErrorFile%s->Line%d",file,line,Infor_Infor);
		Tos_TaskDelay(1000);
	}
}
#endif
/**************************************************************************************
 Func: �˿��嵥��ʼ��
 Time: 2015-9-02
 Ver.: V1.0
 Note;
**************************************************************************************/
void GPIO_InitList(const GPIO_InitStruct *List)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	uint32_t RCC_APB2Periph_GPIOx; 
	while(List->GPIO_Speed)
	{
		switch((uintbus)List->GPIOx)
	{
		case (uintbus)GPIOA:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOA;break;
		case (uintbus)GPIOB:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOB;break;
		case (uintbus)GPIOC:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOC;break;
		case (uintbus)GPIOD:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOD;break;
		case (uintbus)GPIOE:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOE;break;
		case (uintbus)GPIOF:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOF;break;
	}
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Speed=(GPIOSpeed_TypeDef)List->GPIO_Speed;
	GPIO_InitStructure.GPIO_Pin=List->GPIO_Pin; 
	GPIO_InitStructure.GPIO_Mode=List->GPIO_Mode;
	GPIO_Init(List->GPIOx, &GPIO_InitStructure);
	List++;
	}
}
void SysTick_Set()
{
	SysTick_Config(Tos_Cpu_Freq/1000);
}
void BareDelay(uint32 i)
{
	uint32 m;
	while(i--)
	{
		m=72000000000/Tos_Cpu_Freq;
		while(m--);
	}
}
void Standby_Init()
{
	GPIO_InitTypeDef   GPIO_InitStructure;      
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);//ʹ�� GPIOA �͸��ù���ʱ��
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;    //PA.0
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ�� IO
	//ʹ���ⲿ�жϷ�ʽ
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); 
	//�ж��� 0 ���� GPIOA.0
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;  //���ð������е��ⲿ��·
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    //�����ⲿ�ж�ģ
	//ʽ:EXTI ��·Ϊ�ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;   //�����ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);  //  ��ʼ���ⲿ�ж�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ� 2 ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //�����ȼ� 2 ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ�� NVIC
	Sys_Enter_Standby();
	
}
void EXTI0_IRQHandler(void)
{                          
	
	EXTI_ClearITPendingBit(EXTI_Line0); //  ��� LINE10 �ϵ��жϱ�־λ   
	MCU_Reset();	
} 

void Sys_Standby(void)
{  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);  //ʹ�� PWR ����ʱ��
	PWR_WakeUpPinCmd(ENABLE);   //ʹ�ܻ��ѹܽŹ���
	PWR_BackupAccessCmd(ENABLE);
	//PWR_EnterSTANDBYMode();    //���������STANDBY��ģʽ       
	PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFE);
}
//ϵͳ�������ģʽ
void Sys_Enter_Standby(void)
{     
	RCC_APB2PeriphResetCmd(0X01FC,DISABLE);  //��λ���� IO ��
	Sys_Standby();
}
void MCU_Reset(void)
{
	__disable_fault_irq();      // STM32 ��λ  
	NVIC_SystemReset();
}
void IAP_ProgramHalfWord(uint32 Address, uint16 Data)
{
	FLASH_ProgramHalfWord(Address,Data);
}
void IAP_ErasePage(uint32 Page_Address)
{
	FLASH_ErasePage(Page_Address);
}
void IAP_Lock()
{
		FLASH_Lock();
}
void IWDG_Configuration(void)
{
 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); /* д��0x5555,�����������Ĵ���д�빦�� */
 IWDG_SetPrescaler(IWDG_Prescaler_256); /* ����ʱ�ӷ�Ƶ,40K/256=156HZ(6.4ms)*/
 IWDG_SetReload(0xff0);/* ι��ʱ�� 5s/6.4MS=781 .ע�ⲻ�ܴ���0xfff*/
 IWDG_ReloadCounter();/* ι��*/
 IWDG_Enable(); /* ʹ�ܹ���*/
}
void IWDG_Reload()
{
	IWDG_ReloadCounter();//ϵͳ��/ʹ�����߹��ܺ���Ҫ�ر�ϵͳ��
}
