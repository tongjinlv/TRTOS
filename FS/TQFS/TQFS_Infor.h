/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _TQFS_INFOR_
#define _TQFS_INFOR_
#include <Include.h>


void Printf_FileInfor(File_Infor *FI);
void Printf_ObjectFileList(uint8 Key,uint16 Page);
void Printf_FilePageCount(uint32 StartPage);


#endif
