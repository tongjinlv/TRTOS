/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/

#ifndef _TOS_TIMER_H_
#define _TOS_TIMER_H_

#include <Include.h>

typedef enum
{
	TTF_START=S0,
	TTF_RUN=S1,
	TTF_FOREVER=0xffff,
}TOS_TIMER_FLAG;

typedef struct 
{
	uint8 Year;
	uint8 Mon;
	uint8 Day;
	uint8 Week;
	uint8 Hour;
	uint8 Min;
	uint8 Sec;
}Date_Time;
typedef struct 
{
	uint8 Year;
	uint8 Mon;
	uint8 Day;
}Date;

typedef struct _Tos_Timer
{
	struct _Tos_Timer *NextTimer;			//ָ����һ����ʱ��
	uint16 Interval;							//��ʱ��ʱ����
	uint16 Lifecycle;						//��ʱ���������� 0xFFFF ��������
	uint16 Counter;							//������,�������ڼ���
	uint8 Flags;							//��ʱ����־ B7/Run B6/sta B[5:0]/task_ID
	Func  Function;							//��������
}Tos_Timer;	

extern Tos_Timer *Tos_Timer_P;
void Tos_TimerReady(void);
void Tos_InitTimer(void);
extern Tos_Timer* Tos_CreateTimer(uint16 Interval,uint16 Lifecycle,Func Function);
void Tos_ScanTimer(void);
void Tos_ExecuteTimer(void);
BOOL Tos_DeleteTimer(Tos_Timer *Timer);

#endif																								
