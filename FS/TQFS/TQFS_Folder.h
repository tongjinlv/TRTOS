/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _TQFS_FOLDER_H_
#define _TQFS_FOLDER_H_

#include <Include.h>
#include <..\FS\TQFS\TQFS_File.h>

typedef struct 
{
	uint8  FileType;//文件类型
	uint8  PS_ST;//备用
	uint32 FileStartAddr;//文件存放位置
}Folder_FileInfor;

typedef struct
{
	uint8  FileType;//文件类型
	uint8  PS_ST;//备用
	uint32 linkAddr;//文件存放位置
	uint16 WriteFlag;//检查标志位为0xffff标志该位置没有内容
}File_LinkInfor;

void TQFS_CreateRootFolder(void);
void Read_FolderInfor(TQFS_Open_File *Open_File,Folder_FileInfor *FFI);
void Write_FolderInfor(TQFS_Open_File *Open_File,Folder_FileInfor *FFI);

#endif
