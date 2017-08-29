/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TOS_TIMED_TIMED_H_
#define _TOS_TIMED_TIMED_H_
#include <Include.h>

#define TIMEDTASKS_FLAG_START				0x40
#define TIMEDTASKS_TIMER_FLAG_RUN				0x80
#define TIMEDTASKS_TIMER_LIFE_FOREVER			0xFFFF


/*---------------------��ʱ���ṹ----------------------------*/
//����ʱ���̶���100ms��ʱ��������
//���ʱʱ��Ϊ25.5S
typedef struct Tos_Timed
{
	uint8 ID;								//��ʱ��ID��
	struct Tos_Timed *NextTimer;			//ָ����һ����ʱ��
	uint8 Interval;							//��ʱ��ʱ����
	uint8 Lifecycle;						//��ʱ���������� 0xFFFF ��������
	uint8 Counter;							//������,�������ڼ���
	uint8 Flags;							//��ʱ����־ B7/Run B6/sta B[5:0]/task_ID
	Func  Function;							//��������
}Tos_Timed;	


uint8 Timed_Create(Tos_Timed *NewTimer,uint16 Interval,uint16 Lifecycle,Func Function);
void Tos_TimedScan(void);
Tos_Timed *Tos_TimedFind(uint8 TimerID);
uint8 Tos_TimedCount(void);
uint8 Tos_TimedAlter(uint8 TimerID,uint16 Interval,uint16 Lifecycle,Func Function);
uint8 Tos_TimedDelete(uint8 TimerID);
void Tos_TimedExecute(void);

#endif																								
