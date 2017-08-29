/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Text.h>
#include <Tos.h>
#include <STM32_CPU.h>
#include <DeBug.h>
#include <Tos_Mema.h>
uint32 guiNextTaskSp;              /* ��Ҫ���е������ջָ�� */
uint32* gpuiCurTaskSpAddr;         /* ��ŵ�ǰ���������ջָ��ĵ�ַ */
Tos_CPUInforStruct Tos_CPUInfor;				 /* ���OS������Ϣ */
uint8  Tos_TaskCurrent;
Tos_Tab *Tos_TaskTcb;
uint32 Tos_TaskStackIndex;

extern void SysTick_Set(void);
extern void BareDelay(uint32 i);
extern void MCU_Reset(void);
/********************************************************************************
Func:��ʼ�������
Date:2014-6-10
By:ͯ����
http://www.trtos.com/
Note:��ջ�ǵ�����
********************************************************************************/
uint32 Tos_TaskTcbInit(uint8* pucTaskStack, uint32 uiStackSize)
{
    uint8* pucStackBy4;
    pucStackBy4 = (uint8*)(((uint32)pucTaskStack + uiStackSize) & 0xFFFFFFFC);
    return(((uint32)pucStackBy4 - sizeof(Tos_Tab)) & STACKALIGNMASK);
}
/********************************************************************************
Func:��ʼ������ջ
Date:2014-6-10
By:ͯ����
http://www.trtos.com/
Note:
********************************************************************************/
uint32 Tos_TaskStackInit(uint32 pstrTcb, Tos_Task vfFuncPointer,uintbus Tags)
{
    uint32* puiSp;
    puiSp = (uint32*)pstrTcb; /* ��ȡ��ű����Ķ�ջָ�� */
    *(--puiSp) = (uint32)vfFuncPointer;    /* R14 */
    *(--puiSp) = pstrTcb;  /* R13 */
    *(--puiSp) = 0;                     /* R12 */
    *(--puiSp) = 0;                     /* R11 */
    *(--puiSp) = 0;                     /* R10 */
    *(--puiSp) = 0;                     /* R9 */
    *(--puiSp) = 0;                     /* R8 */
    *(--puiSp) = 0;                     /* R7 */
    *(--puiSp) = 0;                     /* R6 */
    *(--puiSp) = 0;                     /* R5 */
    *(--puiSp) = 0;                     /* R4 */
    *(--puiSp) = 0;                     /* R3 */
    *(--puiSp) = 0;                     /* R2 */
    *(--puiSp) = 0;                     /* R1 */
    *(--puiSp) =Tags;                   /* R0 */
    *(--puiSp) = MODE_USR;              /* XPSR */
    return (uint32)puiSp;
}

/********************************************************************************
Func:��������
Date:2014-6-10
By:ͯ����
http://www.trtos.com/
Note:ʹ��Ĭ�϶�ջ
********************************************************************************/
void Tos_TaskCreate(uint8 Id,void(*vfFuncPointer)(void *Tags),uintbus Tags,char *TaskName,uint32 StackSize)
{
	uint32 pstrTcb;
	uint8 *P;
	if(NullFunc == vfFuncPointer)return;
	if(Tos_TaskTcb[Id].Task_ST!=_TTS_Deleted)return;
	if(Tos_TaskTcb[Id].TaskStackSize==0)
	{
		P=Mema_Malloc(StackSize);
		Tos_TaskTcb[Id].TaskStackSize=StackSize;
		Tos_TaskTcb[Id].Task_SA=(uint32)P;
	}	
	pstrTcb = Tos_TaskTcbInit((uint8 *)Tos_TaskTcb[Id].Task_SA, Tos_TaskTcb[Id].TaskStackSize);//�ڴ�����
	Tos_TaskTcb[Id].Task_ST=_TTS_Run;
	Tos_TaskTcb[Id].vfFunc=vfFuncPointer;
	Tos_TaskTcb[Id].Task_Name=TaskName;
	Tos_TaskTcb[Id].TaskCurSp=Tos_TaskStackInit(pstrTcb, vfFuncPointer,Tags);//��ջ��ʼ���Ĵ���
}
/********************************************************************************
Func:������λ�½�����
Date:2014-11-3
By:ͯ����
http://www.trtos.com/
Note:
********************************************************************************/
BOOL Tos_TaskCreateFindID(void(*vfFuncPointer)(void *Tags),uintbus Tags,char *TaskName,uint32 StackSize)
{
	uint16 i=0;
	while(1)
	{
		if(Tos_TaskTcb[i].Task_ST==Null)break;
		if(Tos_TaskTcb[i].Task_ST==_TTS_Deleted)break;
		if(++i>=Tos_TaskTotal)return False;
	}
	Tos_TaskCreate(i,vfFuncPointer,Tags,TaskName,StackSize);
	return True;
}
/********************************************************************************
Func:��������
Date:2014-11-3
By:ͯ����
http://www.trtos.com/
Note:
********************************************************************************/
uint16 Tos_GetTaskIDByName(uint8 *Name)
{
	uint16 i=0;
	while(1)
	{
		if(CompareWithString(Name,(uint8 *)Tos_TaskTcb[i].Task_Name))return i;
		if(++i>=Tos_TaskTotal)return Tos_TaskNull;
	}
}
/********************************************************************************
Func:�����б��ʼ��
Date:2015-9-10
By:ͯ����
http://www.trtos.com/
Note:
********************************************************************************/
void Tos_ListCreate(const TaskInitList *TIL)
{
	Tos_Init();
	while(TIL->vfFuncPointer)
	{
		Tos_TaskCreateFindID(TIL->vfFuncPointer,(uintbus)TIL->Tags,TIL->TaskName,TIL->StackSize);
		TIL++;
	}
	Tos_Start();
}

/********************************************************************************
Func:��������
Date:2014-6-10
By:ͯ����
http://www.trtos.com/
Note:ʹ��Ĭ�϶�ջ
********************************************************************************/
void Tos_TaskRun(uint8 Id)
{
	  if(Tos_TaskCurrent==Id)return;
    gpuiCurTaskSpAddr = &Tos_TaskTcb[Tos_TaskCurrent].TaskCurSp;
	  Tos_TaskCurrent=Id;
    guiNextTaskSp =Tos_TaskTcb[Tos_TaskCurrent].TaskCurSp;
    TOS_ContextSwitch();
}

/********************************************************************************
Func: �����л�
Time: 2014-1-31
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: ������������������л�
********************************************************************************/
void Tos_TaskSwitch(void)
{
	 uint8 i;
	Tos_TaskTcb[Tos_TaskTotal-1].Task_ST=_TTS_Run;//ϵͳ����������Ϊ��������
	for(i=0;i<Tos_TaskTotal;i++)
	{
		switch(Tos_TaskTcb[i].Task_ST)
		{
			case _TTS_Run:
				   if(Tos_TaskCurrent!=i)Tos_TaskRun(i);	 
					 return; 
			case _TTS_WaitDevice:
					if(Tos_Device_Tab[Tos_TaskTcb[i].Task_WDID].DeviceState==NotBusy)
						{
							Tos_TaskTcb[i].Task_ST=_TTS_DelayWait;
							Tos_Device_Tab[Tos_TaskTcb[i].Task_WDID].DeviceState=Ready;
						}
					 break;
			default:break;
		}
	}
}

/********************************************************************************
Func: ��
ʼ��Tos
Time: 2014-1-31
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note; ���ڳ�ʼ��ϵͳ����
********************************************************************************/
void Tos_Init(void)
{
	uint8 i;
	Tos_TaskTcb=Mema_Malloc(sizeof(Tos_Tab)*Tos_TaskTotal);
	Tos_CPUInfor.RunStatus=_TTS_Run;
	Tos_CPUInfor.Use_Ram=0;
	for(i=0;i<Tos_TaskTotal;i++)
	{
		Tos_TaskTcb[i].Task_ST=_TTS_Deleted;
		Tos_TaskTcb[i].Task_TQ=0;			//���񳬹���ʱ��ֱ�ӹ���
		Tos_TaskTcb[i].TaskCurSp=Null;
		Tos_TaskTcb[i].Task_SA=Null;
		Tos_TaskTcb[i].TaskStackSize=0;
	}
	Tos_TaskCurrent=Tos_TaskTotal-1; 
	Tos_TaskStackIndex=0;//�����ջ�ؼ�ʹ��ָ��
	Tos_Timer_P=0;
}
/********************************************************************************
Func: ��������Ҳ����Ϊ�ǿ�������
Time: 2014-6-13
Ver.: V4.0
http://www.trtos.com/
By:ͯ����
Note;
********************************************************************************/
void Tos_RootTask(void *Tags)
{
	
	Device_Init();//�豸��ʼ������ϵͳδ����ʱ�ᵼ�²��������쳣����fmsc
#ifdef IWDG_ENABLE
	IWDG_Configuration();
#endif
#ifdef APPLIC_ENABLE
	if(!AppLicense())return;//ע��
#endif
#ifdef DISCOPPY_ENABLE
	if(!App_DisCoppy())return;//����
#endif
	while(1)
	{
#ifdef IWDG_ENABLE
		IWDG_ReloadCounter();//ϵͳ��/ʹ�����߹��ܺ���Ҫ�ر�ϵͳ��
#endif
		Tos_TaskDelay(100);
		Tos_ScanTimer();
	}
}
/********************************************************************************
Func: ��������
Time: 2014-6-13
Ver.: V4.0
http://www.trtos.com/
By:ͯ����
Note;
********************************************************************************/
void Tos_TaskStart(uint8 Id)
{
    guiNextTaskSp = Tos_TaskTcb[Id].TaskCurSp;
    TOS_SwitchToTask();
}

/********************************************************************************
Func: ����tos����ϵͳ
Time: 2013-12-13
Ver.: V4.0
http://www.trtos.com/
By:ͯ����
Note;���������������ý�������������һ������
********************************************************************************/
void Tos_Start(void)
{	
	SysTick_Set();
	Tos_TaskCreate(Tos_TaskTotal-1,Tos_RootTask,Null,"TaskRoot",Tos_RootTaskStackSize);
  Tos_TaskStart(Tos_TaskTotal-1);

}



/********************************************************************************
Func: ��ȡ����ǰ״̬
Time: 2014-1-31
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note; ��������������ĵ�ǰ״̬
********************************************************************************/
uint16 Tos_TaskGetState(uint8 Index)
{
	if(Index>=Tos_TaskTotal)return 0;
	return Tos_TaskTcb[Index].Task_ST;	
}

/********************************************************************************
Func: ϵͳ��ʱ����
Time: 2014-1-31
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note; ���������������ӳ�ִ��			RT: ���ֽ�/ѹջ���� ���ֽ�/R4��ջ�е�λ��
********************************************************************************/
void Tos_TaskDelay(uint32 DelayTime)
{
	if(Tos_CPUInfor.RunStatus!=_TTS_Deleted)//ϵͳ����ʱ���õ���ϵͳ��ʱ
	{
	Tos_TaskTcb[Tos_TaskCurrent].Task_TQ=0;//TOSϵͳ���Ź���λ
	Tos_TaskTcb[Tos_TaskCurrent].Task_TD=DelayTime;																 
	Tos_TaskTcb[Tos_TaskCurrent].Task_ST=_TTS_DelayWait;
	Tos_TaskSwitch();		
	}else BareDelay(DelayTime);//��ϵͳû������֮ǰ�����������ʱ
}
/********************************************************************************
Func: ϵͳ��ʱ����
Time: 2014-1-31
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note; ��ʱʱ���ȱ
********************************************************************************/
void Tos_TaskDelayHMSM(uint8 Hour,uint8 Min,uint8 Sec,uint16 MSec)
{
	uint32 DelayTime;
	DelayTime=Hour;
	DelayTime*=60;
	DelayTime+=Min;
	DelayTime*=60;
	DelayTime+=Sec;
	DelayTime*=1000;
	DelayTime+=MSec;
	Tos_TaskDelay(DelayTime);
}
/********************************************************************************
Func: ����ʱ���ѹ���
Time: 2009-12-28
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: ������ΪĿ����������һ����ʱʱ��,Ŀ��������ָ��ʱ���ǿ�ƽ�������̬
********************************************************************************/
void Tos_TaskTimeout(uint8 Index,uint32 Timeout)
{
	if(Index>=Tos_TaskTotal)return;
	if(Tos_TaskTcb[Index].Task_ST==_TTS_Stop)return;//ֹͣ�������޷�����
	Tos_TaskTcb[Index].Task_TQ=0;//TOSϵͳ���Ź���λ
	Tos_TaskTcb[Index].Task_ST=_TTS_DelayWait;
	Tos_TaskTcb[Index].Task_TD=Timeout;
}

/********************************************************************************
Func: ����ʱ����
Time: 2009-12-31
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: �����ý���������ʱ����,�κ�������ָ���ĳ�ʱʱ��֮����ϵͳǿ�ƻ���
 	   ��ʱʱ�䰴ϵͳ���ļ�,��Ϊ0ʱ��ʾ�޳�ʱ
	   �ӳ�ʱʱ���趨��������Ч,��ʱʱ����߿ɾ�ȷ��һ��ϵͳ����
	   һ�γ�ʱ�趨ֻ�ܹ���ǰʱ���,���ε�����̬��ʱ��ȡ��,��;��������̬����ʱ����
********************************************************************************/
void Tos_SetTimeout(uint32 Timeout)
{
	Tos_TaskTimeout(Tos_TaskCurrent,Timeout);
}
/**************************************************************************************
Func: �ȴ��豸
Time: 2014-6-18
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note;
**************************************************************************************/
void Tos_WaitDev(uint8 DevID)
{
	Tos_TaskTcb[Tos_TaskCurrent].Task_WDID=DevID;
	Tos_TaskTcb[Tos_TaskCurrent].Task_ST=_TTS_WaitDevice;
	Tos_TaskSwitch();
}
/********************************************************************************
Func: �������������Ĳ���ִ��̬ת������״̬
Time: 2014-1-31
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note;
********************************************************************************/
void Tos_TaskRecover(uint8 Index)
{
	if(Index>=Tos_TaskTotal)return;
	if(Tos_TaskTcb[Index].Task_ST==_TTS_Deleted)return;//ɾ���������޷�����
	Tos_TaskTcb[Index].Task_ST=_TTS_DelayWait;
}
/********************************************************************************
Func: �������ȴ��жϻ�����������
Time: 2014-11-09
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note;�������ж���
********************************************************************************/
BOOL Tos_TaskSuspend(uint8 Index)
{
	if(Index>=Tos_TaskTotal)return False;
	if(Tos_TaskTcb[Index].Task_ST==_TTS_Deleted)return False;//ɾ���������޷�����
	if(Tos_TaskTcb[Index].Task_ST==_TTS_Stop)return False;//ֹͣ�������޷�����
	if(Tos_TaskTcb[Index].Task_ST==_TTS_Suspend)return False;//�޷��ظ�����
	Tos_TaskTcb[Index].Task_ST=_TTS_Suspend; 
	Tos_TaskTcb[Index].Task_TD=0; 
	Tos_TaskSwitch();
	return True;
}
/********************************************************************************
Func: �����ֹͣ״̬�ָ�
Time: 2014-1-31
Ver.: V4.0  
 By:ͯ����
http://www.trtos.com/
Note: �������������������л�//�ر�Ҫ�����������ж��ﲻ�ܵ���
********************************************************************************/
BOOL Tos_TaskResume(uint8 Index)
{	
	if(Index>=Tos_TaskTotal)return False;
	if(Tos_TaskTcb[Index].Task_ST==_TTS_Deleted)return False;//ɾ���������޷��ָ�
	if(Tos_TaskTcb[Index].Task_ST==_TTS_DelayWait)return False;
	if(Tos_TaskTcb[Index].Task_ST==_TTS_Run)return False;
	Tos_TaskTcb[Index].Task_ST=_TTS_Run; 
	Tos_TaskSwitch();
	return True;
}
/********************************************************************************
Func: �������ֹͣ״̬
Time: 2014-1-31
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: �������������������л�
********************************************************************************/
void Tos_TaskStop(uint8 Index)
{	
	if(Index>=Tos_TaskTotal)return;
	if(Tos_TaskTcb[Index].Task_ST==_TTS_Deleted)return;//ɾ���������޷�ֹͣ
	Tos_TaskTcb[Index].Task_ST=_TTS_Stop; 
	Tos_TaskTcb[Index].Task_TD=0; 
	Tos_TaskSwitch();
}
/********************************************************************************
Func: ϵͳ����ɾ��
Time: 2009-12-12
Ver.: V4.0
http://www.trtos.com/
By:ͯ����
Note; ������ʹ���ȼ��ߵ������ܽ���ǰ���ȼ�������������ɾ��
********************************************************************************/
BOOL Tos_TaskDelete(uint8 Index) 
{
	if(Index>=Tos_TaskTotal)return False;
	if(Tos_TaskTcb[Index].Task_ST==_TTS_Deleted)return False;
	Tos_TaskTcb[Index].Task_Name=Null;			
	Tos_TaskTcb[Index].Task_TQ=0;								 
	Tos_TaskTcb[Index].Task_TD=0;								 		
	Tos_TaskTcb[Index].Task_ST=_TTS_Deleted; 										//��������״̬	
	Mema_Free((uint8 *)Tos_TaskTcb[Index].Task_SA);
	Tos_TaskTcb[Index].TaskStackSize=0;
	Tos_TaskSwitch();													//�л�����
	return True;
}
/********************************************************************************
Func: ϵͳ���Ķ�ʱ������
Time: 2009-12-12
Ver.: V4.0
 By:ͯ����
http://www.trtos.com/
Note:���������Ŷ�
********************************************************************************/
void Tos_TaskReady()
{
	uint8 i;
	for(i=0;i<Tos_TaskTotal;i++)
	{
		switch(Tos_TaskTcb[i].Task_ST)
		{
			case _TTS_Run:
				   Tos_TaskTcb[i].Task_TQ++;//������������̬ȴ��û���������л����г�ʱ������ϵͳ��λ
						if(Tos_TaskTcb[i].Task_TQ>Tos_TaskWatchDog)Tos_CPUInfor.RunStatus=_TTS_Error;
					 break; //֮ǰ��Return������break��CPUʹ�����½�4%
			case _TTS_DelayWait:
					 Tos_TaskTcb[i].Task_TQ=0;
					 if(Tos_TaskTcb[i].Task_TD==0)Tos_TaskTcb[i].Task_ST=_TTS_Run;
			     else Tos_TaskTcb[i].Task_TD--;
					 break;
			default:break;
		}
	}
}
/********************************************************************************
Func: ����CPU��ʹ����
Time: 20014-5-25
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note; ���Խ����޸Ļ�ȡ���������CPUʹ����
********************************************************************************/
void Tos_ComputeCPURate()
{
	static uint8 Count,i;
	static uint32 Pool;
	static uint8 Use;
	if(Tos_TaskTotal-1!=Tos_TaskCurrent)Use++;//���㵥������CPUʹ����ֱ��������id
	Count++;
	if(Count>100){Count=0;Tos_CPUInfor.Userate_CPU=FlowPoolFilter(&Pool,Use,&i,20);Use=0;}
}
/********************************************************************************
Func: ϵͳ���Ĵ���
Time: 20014-2-2
Ver.: V4.0
http://www.trtos.com/
By:ͯ����
Note; ����������ϵͳ�����ж�
********************************************************************************/
void Tos_SysTick()
 {
	  Tos_ComputeCPURate();//��ʱ��ɨ��
		Tos_TaskReady();//�������
	 	if(Tos_CPUInfor.RunStatus==_TTS_Error){DeBug( "TOS TimeOut Reset" ,Infor_Infor);MCU_Reset();}//ϵͳ���������г�ʱ�Զ���λ
		if(Tos_Timer_P)Tos_TimerReady();//��Լһ����һ��
 }
 

/********************************************************************************
Func: ��ȡ��Ϣ
Time: 2014-1-31
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: �������������͹�������Ϣ
********************************************************************************/
Tos_ArrayMessage *Tos_TaskGetQMsg(void) 
{
	Tos_ArrayMessage *_CurMsg;	
	Tos_Tab *Tos_Addr;
	Tos_Addr=&Tos_TaskTcb[Tos_TaskCurrent];
	if(Tos_Addr->Task_QM==0)return 0;	
	if(Tos_Addr->Task_QE==0)Tos_TaskStop(Tos_TaskCurrent);		
	if(Tos_Addr->Task_QE==0)return 0;	
	_CurMsg = Tos_Addr->Task_QM + Tos_Addr->Task_QS;
	Tos_Addr->Task_QS=(Tos_Addr->Task_QS+1)%Tos_Addr->Task_QL;
	Tos_Addr->Task_QE--;	
	return _CurMsg;
}
/********************************************************************************
Func: ��ȡ��Ϣ
Time: 2014-1-31
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: ������ʽ������Ϣ
********************************************************************************/
Tos_ArrayMessage *Tos_TaskGetQMsgDelay(uint16 D) 
{
	Tos_ArrayMessage *_CurMsg;	
	Tos_Tab *Tos_Addr;
	Tos_Addr=&Tos_TaskTcb[Tos_TaskCurrent];
	if(Tos_Addr->Task_QM==0)return 0;	
	if(Tos_Addr->Task_QE==0)Tos_TaskDelay(D);		
	if(Tos_Addr->Task_QE==0)return 0;	
	_CurMsg = Tos_Addr->Task_QM + Tos_Addr->Task_QS;
	Tos_Addr->Task_QS=(Tos_Addr->Task_QS+1)%Tos_Addr->Task_QL;
	Tos_Addr->Task_QE--;	
	return _CurMsg;
}
 /********************************************************************************
Func: ����������Ϣ����
Time: 2014-2-4
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: 
********************************************************************************/
void Tos_TaskCreateQmsg(Tos_ArrayMessage *MsgAddr,uint8 MsgLenth)
{
	Tos_TaskTcb[Tos_TaskCurrent].Task_QM=MsgAddr;
	Tos_TaskTcb[Tos_TaskCurrent].Task_QL=MsgLenth;
	Tos_TaskTcb[Tos_TaskCurrent].Task_QS=0;
	Tos_TaskTcb[Tos_TaskCurrent].Task_QE=0;
}
/********************************************************************************
Func: ɾ��������Ϣ����
Time: 2009-12-28
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: 
********************************************************************************/
void Tos_TaskDeleteQmsg(void)
{
 	Tos_TaskTcb[Tos_TaskCurrent].Task_QM=0;
	Tos_TaskTcb[Tos_TaskCurrent].Task_QL=0;
	Tos_TaskTcb[Tos_TaskCurrent].Task_QS=0;
	Tos_TaskTcb[Tos_TaskCurrent].Task_QE=0;
}
/********************************************************************************
Func: ϵͳ����,���ݹ���
Time: 2009-12-28
Ver.: V1.0
 By:ͯ����
http://www.trtos.com/
Note: ��������ϵͳ����β��д������Ϣ
       Index/��Ϣ���	MsgType/��Ϣ����	MsgMark/��Ϣ���	MsgSize/��Ϣ����   *Qmsg/��Ϣ��ַ
	   ��������Ϣ��������,����Ϣ���ܾ�д��,��Ϣ����ʧ
********************************************************************************/

void Tos_TaskPutQmsg(uint8 Index,uint8 MsgType,uint16 MsgSize,void * Qmsg)
{
	uint8 NextPt;
	Tos_Tab *Tos_Addr;
	Tos_ArrayMessage *_CurMsg;
	if(Index>=Tos_TaskTotal)return;
	Tos_Addr=&Tos_TaskTcb[Index];							//ȡĿ��������ƿ�
	if(Tos_Addr->Task_QM==0)return ;
	if(Tos_Addr->Task_QE<Tos_Addr->Task_QL){										//������Ϣ�����Ƿ�����
		NextPt=(Tos_Addr->Task_QS+Tos_Addr->Task_QE)%(Tos_Addr->Task_QL);	//������һ����Ϣ��ַƫ����
		if(NextPt>=Tos_Addr->Task_QL)return;
		_CurMsg=Tos_Addr->Task_QM+NextPt;											//ȡ��һ����Ϣ��ַ
		_CurMsg->Qmsg_Type =MsgType;
		BufferCoppy(Qmsg,(void *)_CurMsg->Qmsg_Addr,MsgSize);
		_CurMsg->Qmsg_Size =MsgSize;
		Tos_Addr->Task_QE++;
		}
	Tos_TaskRecover(Index);
}
/********************************************************************************
Func: �������ʼ�
Time: 2013-11-13
http://www.trtos.com/
By:ͯ����
Note; ���������ʼ����͵��Է�������
********************************************************************************/
void Tos_TaskSmail(uint8 Index,uint32 Mail)
{
	uint8 i;
	if(Index==0xff)for(i=0;i<Tos_TaskTotal;i++)Tos_TaskTcb[Index].Task_MB=Mail;
	else Tos_TaskTcb[Index].Task_MB=Mail;//ȡĿ��������ƿ�
}
/********************************************************************************
Func: ������ʼ�
Time: 2013-11-13
http://www.trtos.com/
By:ͯ����
Note; ������������
********************************************************************************/
uint32 Tos_TaskQmail()
{
	return Tos_TaskTcb[Tos_TaskCurrent].Task_MB;//ȡĿ��������ƿ�
}
