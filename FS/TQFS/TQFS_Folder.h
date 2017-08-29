/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TQFS_FOLDER_H_
#define _TQFS_FOLDER_H_

#include <Include.h>
#include <..\FS\TQFS\TQFS_File.h>

typedef struct 
{
	uint8  FileType;//�ļ�����
	uint8  PS_ST;//����
	uint32 FileStartAddr;//�ļ����λ��
}Folder_FileInfor;

typedef struct
{
	uint8  FileType;//�ļ�����
	uint8  PS_ST;//����
	uint32 linkAddr;//�ļ����λ��
	uint16 WriteFlag;//����־λΪ0xffff��־��λ��û������
}File_LinkInfor;

void TQFS_CreateRootFolder(void);
void Read_FolderInfor(TQFS_Open_File *Open_File,Folder_FileInfor *FFI);
void Write_FolderInfor(TQFS_Open_File *Open_File,Folder_FileInfor *FFI);

#endif
