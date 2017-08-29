/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Key_Driver.h>

uint8 KeyCode_Tos_TaskID=Tos_TaskNull;
/********************************************************************************
Func:键盘任务
Date:2017-3-8
Note:传入参数为获取按键码调用
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
Func:获取按键消息
Date:2017-3-8
Note:传入参数为延时时间0为无限等待，返回按键消息
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
Func:按键钩子
Date:2017-3-8
Note:想获取按键的任务可以指向该操作，消息始终被最后执行该函数的任务获取
********************************************************************************/
void Tos_TaskGetHandKey()
{
	KeyCode_Tos_TaskID=Tos_TaskCurrent;
}






