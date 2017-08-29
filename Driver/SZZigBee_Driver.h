/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _SZZIGBEE_DRIVER_H_
#define _SZZIGBEE_DRIVER_H_
#include <Include.h>

BOOL ZigBee_CheckCrc(uint8 *Buf);
uint8 ZigBee_SendMsg(uint8 *Buf,uint16 OnlyAddr,uint8 Cmd,uint8 *Data,uint16 DataLegnth);


#endif
