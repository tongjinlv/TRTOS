/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Tos_Timer.h>

Tos_Timer *Tos_Timer_P;
/********************************************************************************
Func: ������ʱ��
Time: 2016-06-14
Ver.: V1.0
http://www.trtos.com/
Note; Interval:��ʱ�������λs����Lifecycle:�������ڡ�Function:���ܺ���
********************************************************************************/
Tos_Timer* Tos_CreateTimer(uint16 Interval,uint16 Lifecycle,Func Function)
{
	Tos_Timer *P;
	if(Tos_Timer_P==Null)
		{
			Tos_Timer_P=Mema_Malloc(sizeof(Tos_Timer));
			P=Tos_Timer_P;
			P->Interval=1000;
			P->Counter=0;
			P->Lifecycle=TTF_FOREVER;
			P->Function=Tos_ExecuteTimer;
			P->Flags=TTF_START;
			P->NextTimer=0;
		}
	P=Tos_Timer_P;
	while(P->NextTimer)
	{
		P=P->NextTimer;
	}
	P->NextTimer=Mema_Malloc(sizeof(Tos_Timer));
	P=P->NextTimer;
	P->Interval=Interval;
	P->Counter=0;
	P->Lifecycle=Lifecycle;
	P->Function=Function;
	P->Flags=TTF_START;
	P->NextTimer=0;
	return P;
}
/********************************************************************************
Func: ɾ����ʱ��
Time: 2016-06-14
Ver.: V1.0
http://www.trtos.com/
Note; 
********************************************************************************/
BOOL Tos_DeleteTimer(Tos_Timer *Timer)
{
	Tos_Timer *P;
	if(!Tos_Timer_P)return False;
	P=Tos_Timer_P;
	if((P==Timer)||(P->NextTimer==0))
	{
		Mema_Free(Timer);
		P=Null;
		return True;
	}
	while(P->NextTimer)
	{
		if(P->NextTimer==Timer)
		{
			if(P->NextTimer->NextTimer!=0)P->NextTimer=P->NextTimer->NextTimer;
			else P->NextTimer=0;
			Mema_Free(Timer);
		}
		P=P->NextTimer;
	}
	return True;
}
/********************************************************************************
Func: ɨ����������Ҫִ�о�ִ��
Time: 2016-06-14
Ver.: V1.0
http://www.trtos.com/
Note; 
********************************************************************************/
void Tos_ScanTimer()
{
	Tos_Timer *P;
	P=Tos_Timer_P;
	if(!P)return;
	while(P->NextTimer)
	{
		P=P->NextTimer;
		if(P->Flags&TTF_START)if(P->Flags&TTF_RUN)
		{
			P->Function();
			P->Flags&=~TTF_RUN;
		}
	}
}
/********************************************************************************
Func: ��ʱ����ʱ����
Time: 2016-06-14
Ver.: V1.0
http://www.trtos.com/
Note; 
********************************************************************************/
void Tos_ExecuteTimer()
{
	Tos_Timer *P;
	P=Tos_Timer_P;
	if(!P)return;
	while(P->NextTimer)
	{
		P=P->NextTimer;
		if((P->Flags&TTF_START)&(P->Lifecycle>0))
		{
			
			if(!(P->Flags&TTF_RUN))
			{
				P->Counter++;
				if(P->Counter>=P->Interval)
				{
				P->Flags|=TTF_RUN;
				P->Counter=0;
				if(P->Lifecycle!=TTF_FOREVER)P->Lifecycle--;
				}
			}
		}
	}
}
/********************************************************************************
Func: ��ʱ���������
Time: 2016-06-14
Ver.: V1.0
http://www.trtos.com/
Note; 
********************************************************************************/
void Tos_TimerReady()
{
	if(!Tos_Timer_P)return;
	if(Tos_Timer_P)if(Tos_Timer_P->Flags&TTF_START)
	{
		if(Tos_Timer_P->Counter>=Tos_Timer_P->Interval)
		{
			Tos_Timer_P->Function();
			Tos_Timer_P->Counter=0;
		}
		Tos_Timer_P->Counter++;
	}
}



























