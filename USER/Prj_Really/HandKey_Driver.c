/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <include.h>
#include <Driver_Include.h>
#include <HandKey_Driver.h>
uint8 HandKey_Tos_TaskID;
uint16 CenterXADC,CenterYADC;
/********************************************************************************
Func:���̳�ʼ��
Date:2014-11-20
Note:
********************************************************************************/
void KeyBoard_Configuration()
{
	GPIO_InitTypeDef   GPIO_InitStructure;      
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);//ʹ�� GPIOA �͸��ù���ʱ��
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;    //PA.0
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ�� IO
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); //ʹ��PortC
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
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
		//Sys_Enter_Standby(); 
	MCU_Reset();	
} 
/********************************************************************************
Func:��ȡ���°���
Date:2014-11-20
Note:���ǿƼ�
********************************************************************************/
uint8 HandKey_GetValue()
{
	uint8 Value=0x00;

	return Value;
}


/********************************************************************************
Func:��ȡ��������
Date:2014-11-20
Note:
********************************************************************************/
void Task_GetHandKey(void *Tags)
{
  MGUI_KeyMsg KeyMsg;
	KeyBoard_Configuration();
	while(1)
	{
		Tos_TaskDelay(10);
		KeyMsg.KeyValue=HandKey_GetValue();
		KeyMsg.KeyType=Key_DownIng;
		if(KeyMsg.KeyValue)Tos_TaskPutQmsg(HandKey_Tos_TaskID,KeyBoard_Hand,sizeof(MGUI_KeyMsg),&KeyMsg);
	}
}
/********************************************************************************
Func:���̹���
Date:2014-11-20
Note:
********************************************************************************/
void Tos_TaskGetHandKey()
{
	HandKey_Tos_TaskID=Tos_TaskCurrent;
}
