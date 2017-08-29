/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _HANDKEY_DRIVER_H_
#define _HANDKEY_DRIVER_H_
#include <include.h>


#define HANDPOWER_ON  GPIO_ResetBits(GPIOE,GPIO_Pin_5) 
#define HANDPOWER_OFF GPIO_SetBits(GPIOE,GPIO_Pin_5) 


typedef enum KeyWorkMode
{
	KWM_Null=0,
	KWM_NotBarWhile=S0,//û���ֱ�������Ӧ
	KWM_NotBar=S1,//û���ֱ�
	KWM_NotHandWhile=S2,//û�а���������Ӧ
}KeyWorkMode;

void KeyBoard_Configuration(void);

uint8 HandKey_GetValue(void);
void Tos_TaskGetHandKey(void);
void Task_GetHandKey(void *Tags);
void Standby_Init(void);
void AutoCorrect_TankHand(void);
void SetKey_WorkMode(KeyWorkMode Mode);
#endif
