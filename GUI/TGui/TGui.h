/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _TGUI_H_
#define _TGUI_H_
#include <include.h>

void TGUI_Init(void);
void TGUI_Window_MsgTask(void *Tags);
void TGUI_TaskTest(void *Tags);
void WGUI_Window_MsgTask(void *Tags);
#endif
