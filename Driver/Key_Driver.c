/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Key_Driver.h>

uint8 KeyCode_Tos_TaskID=Tos_TaskNull;
/********************************************************************************
Func:��������
Date:2017-3-8
Note:�������Ϊ��ȡ���������
********************************************************************************/

void Task_KeyBoard(void *Tags)
{
	MGUI_KeyMsg KeyMsg;
	typedef uint8(*KeyBoardGetValue)(void);
	KeyBoardGetValue P;
	P=((KeyBoardGetValue)(Tags));
	Tos_TaskDelay(2000);
	while(1)
	{
		Tos_TaskDelay(10);
		KeyMsg.KeyValue=P();
		KeyMsg.KeyTime=0;
		if(KeyMsg.KeyValue!=0)
		{
			while(P())
			{
				Tos_TaskDelay(10);
				if(KeyMsg.KeyTime<50)KeyMsg.KeyTime++;
				if(KeyMsg.KeyTime>=50)
				{
					Tos_TaskDelay(100);
					KeyMsg.KeyType=Key_DownTimeOut;
					Tos_TaskPutQmsg(KeyCode_Tos_TaskID,0,sizeof(MGUI_KeyMsg),&KeyMsg);
				}
			}
			if(KeyMsg.KeyTime<50)
			{
				KeyMsg.KeyType=Key_OneClick;
				Tos_TaskPutQmsg(KeyCode_Tos_TaskID,0,sizeof(MGUI_KeyMsg),&KeyMsg);
			}
		}
	}	
}
/********************************************************************************
Func:��ȡ������Ϣ
Date:2017-3-8
Note:�������Ϊ��ʱʱ��0Ϊ���޵ȴ������ذ�����Ϣ
********************************************************************************/
MGUI_KeyMsg * MUI_GetKey(uint16 D)
{
	Tos_ArrayMessage *CurMsg;
	MGUI_KeyMsg *TaskMsg;	
	if(D)CurMsg=Tos_TaskGetQMsgDelay(D);
	else CurMsg=Tos_TaskGetQMsg();
	if(CurMsg)
	{
		TaskMsg=(MGUI_KeyMsg *)CurMsg->Qmsg_Addr;
		return TaskMsg;
	}
	return Null;
}
/********************************************************************************
Func:��������
Date:2017-3-8
Note:���ȡ�������������ָ��ò�������Ϣʼ�ձ����ִ�иú����������ȡ
********************************************************************************/
void Tos_TaskGetHandKey()
{
	KeyCode_Tos_TaskID=Tos_TaskCurrent;
}






