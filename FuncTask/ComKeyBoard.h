/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _COMKEYBOARD_H_
#define _COMKEYBOARD_H_

#include <Include.h>
#include <Key_Driver.h>
void Task_GetKeyBoard(void *Tags);
void Tos_TaskGetKeyBoard(void);
void Task_GetKeyBoardZigbee(void *Tags);
#endif
