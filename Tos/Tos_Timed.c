/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Tos_Timed.h>
Tos_Timed Timed_SystemTimer;


uint8 Timed_Create(Tos_Timed *NewTimer,uint16 Interval,uint16 Lifecycle,Func Function)
{
	uint8 ID=1;
	Tos_Timed *CurTimer=&Timed_SystemTimer;
	if(CurTimer->Flags>0){										//��ϵͳ��ʱ����δ��ʼ��
		while(CurTimer->NextTimer){				  				//����Timer����β���Ŀ�ȱλ��
			CurTimer=CurTimer->NextTimer;
			if(ID>0){											//��δ�ҵ�
				if(CurTimer->ID!=ID){							//������С��δ�õ���ID��
					NewTimer->ID=ID;
					ID=0;
				}else ID++;
			}
		}
		if(ID>0)NewTimer->ID=ID;
		NewTimer->Flags=Tos_TaskCurrent;
		CurTimer->NextTimer=NewTimer;		
	}else{
		NewTimer=CurTimer;
		NewTimer->ID=0;
		NewTimer->Flags=Tos_TaskCurrent;
	}
	NewTimer->Interval=Interval;
	NewTimer->Lifecycle=Lifecycle;
	NewTimer->Counter=0;
	NewTimer->Function=Function;	
	NewTimer->NextTimer=0;	
	return NewTimer->ID;	
}
/*--------------------------------------------------------------------------------------------------------------
Func: ����ʱ��
Time: 2011-5-26
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: ɨ�趨ʱ������
--------------------------------------------------------------------------------------------------------------*/
void Tos_TimedScan(void)
{
	Tos_Timed *CurTimer=&Timed_SystemTimer;
	while(CurTimer->NextTimer)
	{
		CurTimer=CurTimer->NextTimer;
		if(CurTimer->Flags&TOS_TIMER_FLAG_START)
		{
			 if(CurTimer->Lifecycle>0){											//ɨ�����������Ķ�ʱ��
				if(CurTimer->Counter<CurTimer->Interval)CurTimer->Counter++;	//�Ƿ�ʱʱ�䵽
				else{
					if(CurTimer->Lifecycle<0xFF)CurTimer->Lifecycle--;			//������������				
					if(CurTimer->Lifecycle>0x00)CurTimer->Counter=0;			//����������,����0��������������
					CurTimer->Flags|=TOS_TIMER_FLAG_RUN;						//ʱ�䵽��,��Ҫִ�ж�ʱ����
				}
				}
		}
	}
}
/*--------------------------------------------------------------------------------
Func: ���Ҷ�ʱ��
Time: 2014-5-26
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: 
--------------------------------------------------------------------------------*/
Tos_Timed *Tos_TimedFind(uint8 TimerID)
{
	Tos_Timed *CurTimer=&Timed_SystemTimer;
	while(CurTimer->NextTimer){				  					//����Timer����β���Ŀ�ȱλ��
		CurTimer=CurTimer->NextTimer;
		if(CurTimer->ID==TimerID){								//���ҵ�Ŀ�궨ʱ��			
			return CurTimer;
		}
	}
	return 0;
}
/********************************************************************************
Func: ��ʱ������
Time: 2014-8-3
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note; 
********************************************************************************/
uint8 Tos_TimedCount()
{
	uint8 i=1;//ϵͳ��ʱ��һ��
	Tos_Timed *CurTimer=&Timed_SystemTimer;
	while(CurTimer->NextTimer)
	{
		CurTimer=CurTimer->NextTimer;
		i++;
	}
	return i;
}
/*--------------------------------------------------------------------------------
Func: �޸�Tos��ʱ��
Time: 2014-5-26
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: ��Tos_Timer�������޸�ָ���Ķ�ʱ��
--------------------------------------------------------------------------------*/
uint8 Tos_TimedAlter(uint8 TimerID,uint16 Interval,uint16 Lifecycle,Func Function)
{
	Tos_Timed *CurTimer=Tos_TimedFind(TimerID);
	if(CurTimer>0){
		CurTimer->Interval=Interval;
		CurTimer->Lifecycle=Lifecycle;
		CurTimer->Counter=0;									//��ʱ����װ
		CurTimer->Function=Function;
		return TimerID;
	}
	return 0;			
}
/*--------------------------------------------------------------------------------
Func: ɾ��Tos��ʱ��
Time: 2014-5-26
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: ��Tos_Timer������ɾ����ʱ��
--------------------------------------------------------------------------------*/
uint8 Tos_TimedDelete(uint8 TimerID)
{
	Tos_Timed *CurTimer=&Timed_SystemTimer;
	while(CurTimer->NextTimer){				  					//����Timer����β���Ŀ�ȱλ��
		if(CurTimer->NextTimer->ID==TimerID){					//���ҵ�Ŀ�궨ʱ��
			CurTimer->NextTimer->Lifecycle=0;					//��ʱ����������
			CurTimer->NextTimer=CurTimer->NextTimer->NextTimer;	//������ʱ��������ɾ��
			return TimerID;
		}
		CurTimer=CurTimer->NextTimer;
	}
	return 0;			
}


/*--------------------------------------------------------------------------------
Func: ϵͳ��ʱ������
Time: 2014-5-26
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: ɨ�趨ʱ�������о�������
--------------------------------------------------------------------------------*/
void Tos_TimedExecute(void)
{
	Tos_Timed *CurTimer=&Timed_SystemTimer;
	while(CurTimer->NextTimer){
		if(CurTimer->NextTimer->Flags&TOS_TIMER_FLAG_START){
			if(CurTimer->NextTimer->Flags&TOS_TIMER_FLAG_RUN){
				CurTimer->NextTimer->Function();									//ִ�ж�ʱ����
				CurTimer->NextTimer->Flags&=~TOS_TIMER_FLAG_RUN;
				if(CurTimer->NextTimer->Lifecycle==0){
					Tos_TimerDelete(CurTimer->NextTimer->ID);
				}else{
					CurTimer=CurTimer->NextTimer;				
				}
			}else{
				CurTimer=CurTimer->NextTimer;
			}
		}else{
			CurTimer=CurTimer->NextTimer;
		}
	}
}








