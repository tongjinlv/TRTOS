/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TOS_H_
#define _TOS_H_
#include <Include.h>

extern uint32 guiNextTaskSp;              /* ��Ҫ���е������ջָ�� */
extern uint32* gpuiCurTaskSpAddr;         /* ��ŵ�ǰ���������ջָ��ĵ�ַ */

#define STACKALIGNMASK      0xFFFFFFF8  /* ��ջ��������, cortex�ں�ʹ��8�ֽڶ��� */
#define MODE_USR            0x01000000/* THUMBָ�USR����ģʽ���� */

/***********************************************************
��Ϣ�ṹ�������������
***********************************************************/
typedef struct{
	uint8  Qmsg_Type;						//��Ϣ��ǩ
	uint8  Qmsg_Size;						//��Ϣ����
	void  *Qmsg_Addr;						//��Ϣ��ַ
}Tos_ArrayMessage;
/***********************************************************
CPU��Ϣ�ṹ�����ͱ�������
***********************************************************/
typedef struct{
	uint8  Userate_CPU;//CPU��ʹ����
	uint8  RunStatus;
	uint32 Use_Ram;//�ڴ��ʹ����
}Tos_CPUInforStruct;
/***********************************************************
����������Ϣ��ṹ����������
***********************************************************/
typedef struct{
	uint32 TaskCurSp;              //����ջָ��
	Tos_Task  vfFunc;
  uint16  Task_ST;        	        //�������б�־
	uint32  Task_MB;						      //��������
	uint32  Task_SP;									//�����ջ��ַ
	uint32  Task_TD;									//������ʱʱ��
	uint32  Task_TQ;                  //����ʱʱ��
	uint32  Task_SA;              //���񱻷��䵽��ջ��ƫ�Ƶ�ַ 
  uint16  TaskStackSize;
	uint8 Task_WDID;           //�ȴ��豸��ID
	uint8	Task_QL;						//������Ϣ���г���
	uint8	Task_QS;						//������Ϣ������ʼλ��
	uint8	Task_QE;						//������Ϣ������Ϣ����
	Tos_ArrayMessage * Task_QM;	
	char *Task_Name;
 }Tos_Tab;
typedef struct
{
	void(*vfFuncPointer)(void *Tags);
	void *Tags;
	char *TaskName;
	uint32 StackSize;
}TaskInitList;
/**********************************************************
���������״̬ö��
**********************************************************/
typedef enum Tos_TaskState
{
	_TTS_Deleted	 =S0,    //�����Ѿ�ɾ����δ���������߱�����
	_TTS_Run		   =S1,		//��������ִ�л�ȴ�����ִ��	
	_TTS_Stop		   =S2,		//�����Ѿ�ֹͣ�����Ȼ���Ա�ִ�У�����Ҫ�����л�			
	_TTS_Suspend	 =S3,		//�����˾���Ҫ�жϻ���������		
	_TTS_DelayWait =S4, 		//����ʱ����	
	_TTS_WaitDevice=S5,   //�ȴ��豸
	_TTS_Error     =S6,   //�������
}Tos_TaskState;

extern uint8  Tos_TaskCurrent;//��ǰ����ID
extern Tos_Tab *Tos_TaskTcb;//[Tos_TaskTotal];//�����б�
extern uint32 Tos_TaskMail;
extern Tos_CPUInforStruct Tos_CPUInfor;
extern void TOS_ContextSwitch(void);
extern void TOS_SwitchToTask(void);

void Tos_Init(void);
void Tos_Start(void);
void Tos_TaskDelay(uint32 DelayTime);
void Tos_TaskDelayHMSM(uint8 Hour,uint8 Min,uint8 Sec,uint16 MSec);
void Tos_TaskSwitch(void);
void Tos_TaskRun(uint8 Index);
BOOL Tos_TaskDelete(uint8 Index);
uint16 Tos_GetTaskIDByName(uint8 *Name);
BOOL Tos_TaskCreateFindID(void(*vfFuncPointer)(void *Tags),uintbus Tags,char *TaskName,uint32 StackSize);
void Tos_TaskTimeout(uint8 Index,uint32 Timeout);
void Tos_SetTimeout(uint32 Timeout);
uint16 Tos_TaskGetState(uint8 Index);
void Tos_WaitDev(uint8 DevID);
void Tos_TaskRecover(uint8 Index);
BOOL Tos_TaskResume(uint8 Index);
void Tos_TaskReCreate(uint8 Id,Tos_Task vfFuncPointer,uintbus Tags);
void Tos_TaskCreate(uint8 Id,Tos_Task vfFuncPointer,uintbus Tags,char *TaskName,uint32 StackSize);
void Tos_ListCreate(const TaskInitList *TIL);
void Tos_TaskStop(uint8 Index);
BOOL Tos_TaskSuspend(uint8 Index);
void Tos_SysTick(void);
void Tos_TaskCreateQmsg(Tos_ArrayMessage *MsgAddr,uint8 MsgLenth);
void Tos_TaskPutQmsg(uint8 Index,uint8 MsgType,uint16 MsgSize,void * Qmsg);
Tos_ArrayMessage *Tos_TaskGetQMsgDelay(uint16 D);
void Tos_TaskSmail(uint8 Index,uint32 Mail);
void Tos_TaskDeleteQmsg(void);
Tos_ArrayMessage *Tos_TaskGetQMsg(void);
#endif
