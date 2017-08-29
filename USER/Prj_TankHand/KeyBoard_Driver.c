/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <include.h>
#include <Driver_Include.h>
#include <HandKey_Driver.h>
#include <ComKeyBoard.h>
uint8 HandKey_Tos_TaskID;
uint16 CenterXADC,CenterYADC;
KeyWorkMode KeyMode;
/********************************************************************************
Func:���̳�ʼ��
Date:2014-11-20
Note:
********************************************************************************/
void KeyBoard_Configuration()
{
#if defined(BOARD_TANK_Hand)
	GPIO_InitTypeDef   GPIO_InitStructure;      
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);//ʹ�� GPIOA �͸��ù���ʱ��
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;    //PA.0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//PB2Ϊ���Զ˿�ʹ�þͲ����Ե���
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ�� IO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//ʹ�� GPIOA �͸��ù���ʱ��
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;    //PA.0
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;//��������
	GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ�� IO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//ʹ�� GPIOA �͸��ù���ʱ��
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_14|GPIO_Pin_15;    //PA.0
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;//��������
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //��ʼ�� IO
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);
	#else
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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE , ENABLE); 
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOE, &GPIO_InitStructure);
#endif
	
}
void SetKey_WorkMode(KeyWorkMode Mode)
{
	KeyMode=Mode;
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
#if defined(BOARD_TANK_Hand)
	//if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)==0){Value=Key_Enter;}//�ϰ��ӵ�����˿������ص��Կڲ���ʹ��
  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0){Value=Key_Left;}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0){Value=Key_Right;}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0){Value=Key_Up;}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)==0){Value=Key_Down;}
  if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)==0){Value=Key_A;}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)==0){Value=Key_B;}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)==0){Value=Key_C;}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)==0){Value=Key_D;}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)==0){Value=Key_E;}
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)==0){Value=Key_1;}
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)==0){Value=Key_2;}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0){Value=Key_3;}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1){Value=Key_4;}
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0){Value=Key_5;}
	
	
#else
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0){Value|=Key_Left;}//Sys_Standby();
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0)Value|=Key_Up;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0)Value|=Key_Right;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)Value|=Key_Down;
#endif
	return Value;
}
extern uint16 ADCForTankHand_ReadFitel(uint8 CH);

void AutoCorrect_TankHand()
{
	CenterYADC=ADCForTankHand_ReadFitel(0);
	CenterXADC=ADCForTankHand_ReadFitel(1);
}
int8 GetXYSpeed(uint8 KeyValue)
{
	uint8 i;
	int8 Value=0;
	uint16 CenterValue;
	uint16 RockerBarSpase=300;
	uint16 Temp;
	if(KeyValue==Key_X){Temp=ADCForTankHand_ReadFitel(1);CenterValue=CenterXADC;}
	if(KeyValue==Key_Y){Temp=ADCForTankHand_ReadFitel(0);CenterValue=CenterYADC;}
	for(i=0;i<5;i++)
	{
		if(Temp>(CenterValue+i*RockerBarSpase))Value=0-i;
	}
	for(i=0;i<5;i++)
	{
		if(Temp<(CenterValue-i*RockerBarSpase))Value=i;
	}
		return Value;
}
BOOL HandKey_GetRockerBar(MGUI_KeyMsg *KeyMsg)
{
	BOOL OK=False;
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0){KeyMsg->KeyValue=Key_X;OK=True;}
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0){KeyMsg->KeyValue=Key_Y;OK=True;}
	KeyMsg->KeyTime=0;
	if(OK){Tos_TaskDelay(100);KeyMsg->KeyTime=GetXYSpeed(KeyMsg->KeyValue);}
	return OK;
}
extern void ADCForTankHand_Init(void);
/********************************************************************************
Func:��ȡ��������
Date:2014-11-20
Note:
********************************************************************************/
void Task_GetHandKey(void *Tags)
{
	uint16 Count1=0,Count2;
	uint8 Old_Key;
	int8 Old_Time;
	MGUI_KeyMsg KeyMsg;
	KeyBoard_Configuration();
	ADCForTankHand_Init();
	Tos_TaskDelay(200);//�ȴ�XY��ģ�����ȶ�
	AutoCorrect_TankHand();//�Զ�У׼��ֵ  
	while(1)
	{
		Tos_TaskDelay(10);
		KeyMsg.KeyValue=HandKey_GetValue();
		if(KeyMsg.KeyValue!=0)
		{
			Count1++;
			Tos_TaskDelay(100);
			KeyMsg.KeyType=KeyBoard_Hand;
			if(Old_Key!=KeyMsg.KeyValue)
			{
				if(KeyMsg.KeyValue)Tos_TaskPutQmsg(HandKey_Tos_TaskID,KeyBoard_Hand,sizeof(MGUI_KeyMsg),&KeyMsg);
			}
			if(Count1>5)Tos_TaskPutQmsg(HandKey_Tos_TaskID,KeyBoard_Hand,sizeof(MGUI_KeyMsg),&KeyMsg);
		}else Count1=0;
		
		KeyMsg.KeyTime=0;
		if(HandKey_GetRockerBar(&KeyMsg))
		{
			Count2++;
			KeyMsg.KeyType=KeyBoard_RockerBar;
			if(Old_Time!=KeyMsg.KeyTime)
			{
				if(KeyMsg.KeyTime!=0)Tos_TaskPutQmsg(HandKey_Tos_TaskID,KeyBoard_Hand,sizeof(MGUI_KeyMsg),&KeyMsg);
			}else 
			{
				if(!(KeyMode&KWM_NotBarWhile))if(Count2>5)Tos_TaskPutQmsg(HandKey_Tos_TaskID,KeyBoard_Hand,sizeof(MGUI_KeyMsg),&KeyMsg);
			}
		}else Count2=0;
		Old_Time=KeyMsg.KeyTime;
		Old_Key=KeyMsg.KeyValue;
		KeyMsg.KeyType=Key_DownIng;
	}
}
void _Task_GetHandKey(void *Tags)
{
	uint16 Count=0;
	uint8 Old_Key;
	int8 Old_Time;
	MGUI_KeyMsg KeyMsg;
	KeyBoard_Configuration();
	ADCForTankHand_Init();
	Tos_TaskDelay(200);//�ȴ�XY��ģ�����ȶ�
	AutoCorrect_TankHand();//�Զ�У׼��ֵ  
	while(1)
	{
		Tos_TaskDelay(10);
		KeyMsg.KeyValue=HandKey_GetValue();
		if(KeyMsg.KeyValue!=0){KeyMsg.KeyType=KeyBoard_Hand;if(Old_Key!=KeyMsg.KeyValue)if(KeyMsg.KeyValue)Tos_TaskPutQmsg(HandKey_Tos_TaskID,KeyBoard_Hand,sizeof(MGUI_KeyMsg),&KeyMsg);}
		
		
		
		KeyMsg.KeyTime=0;
		if(HandKey_GetRockerBar(&KeyMsg))
		{
			Count++;
			KeyMsg.KeyType=KeyBoard_RockerBar;
			if(Old_Time!=KeyMsg.KeyTime)
			{
				if(KeyMsg.KeyTime!=0)Tos_TaskPutQmsg(HandKey_Tos_TaskID,KeyBoard_Hand,sizeof(MGUI_KeyMsg),&KeyMsg);
			}else if(Count>10)Tos_TaskPutQmsg(HandKey_Tos_TaskID,KeyBoard_Hand,sizeof(MGUI_KeyMsg),&KeyMsg);
		}else Count=0;
		Old_Time=KeyMsg.KeyTime;
		Old_Key=KeyMsg.KeyValue;
		KeyMsg.KeyType=Key_DownIng;
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
