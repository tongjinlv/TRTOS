/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _AT_COMMAND_H_
#define _AT_COMMAND_H_

#include <include.h>

BOOL GPRS_Ack(uint8 *Ack,uint16 Wating);
BOOL GPRS_CommandAck(char *Send,uint8 *Ack,uint16 Wating);
u8  QuectelM26_InitSMS(uint8 Mode);
void QuectelM26Printf_Bytes(uint8 *Msg,uint8 *Bytes,uint16 Length);
uint8 QuectelM26_GetValue(uint8 *Cmd,uint8 *Data);
uint8 QuectelM26_GetCSQ(void);
BOOL GPRS_PrintfString(uint16 Wating);
uint8  QuectelM26_ReadShow(uint8 *Cmd);
void Task_SendHttp(uint8 *Msg);
#endif
