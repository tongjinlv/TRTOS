/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _TOS_MEMA_H_
#define _TOS_MEMA_H_
#include <Include.h>

typedef struct TOS_MEMA_Ptr
{
	struct TOS_MEMA_Ptr *NextPtr;
	uint32 Size;
}TOS_MEMA_Ptr;
extern uint8 MemBuf[MEMA_BUFFER_SIZE];
void Mema_Init(uint8 *Addr);
void *Mema_Malloc(uint16 Size);
void Mema_Free(void *Addr);
uint32 Mema_Count(void);
void *Mema_Extend(void *Addr,uint16 Size);
uint32 Mema_GetSize(void *Addr);
#endif
