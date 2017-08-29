/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _USART1_FACE_H_
#define _USART1_FACE_H_
#include <Include.h>

typedef enum
{
	FT_VoidFuncVoid=1,
	FT_VoidFuncUint8=2,
	FT_VoidFuncUint32=3,
	FT_VoidFuncInt=4,
	FT_VoidFuncUint=5,
	FT_VoidFuncCharP=5,
}FuncType;

typedef struct
{
	void *Task;
	FuncType Type;
	uintbus Note;
}TaskArrayStruct;


void Task_GetScreen(void *Tags);
void Usart_Terminal(void *Tags);
void Task_CAN_Slave(void *Tags);
void Task_CAN_Master(void *Tags);
void Task_Join(void *CurTask,FuncType Type,uintbus Note);//JoinTaskToArrary
void Task_Arrary(void *Tags);// 
void SEGTrun(uint8 *Buf);
#endif
