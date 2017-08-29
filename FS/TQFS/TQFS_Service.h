/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _TQFS_SERVICE_H_
#define _TQFS_SERVICE_H_
#include <Include.h>

uint32 TQFS_SearchFileByNameAndType(void *Name,uint8 Type);
uint32 TQFS_SearchFile(void *Name);
void TQFS_SearchEndPage(TQFS_Open_File *OpenFile);
void TQFS_SearchEndByte(TQFS_Open_File *OpenFile);
#endif
