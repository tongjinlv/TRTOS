/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Tools_Include.h>
#include <FS_Include.h>

/*******************************************************************************
Func:������Ŀ¼
Date:2014-8-4
Note:
*******************************************************************************/
void TQFS_CreateRootFolder()
{
	uint32 i;
	File_Infor TempFile;
	TQFS_Open_File Open_File;
  if(TQFS_SearchFileByNameAndType("Root",FT_RootDirHead)==0xffffffff)
	{
	DeBug("File Create Succeed",Infor_Infor);
	i=TQFS_FindKeyPageMark(FT_NotUsed,FT_RootDirHead);
	TQFS_SetCursor(&Open_File,i,0);
	TQFS_FileRoomInfor(&TempFile,"Root.Dir",0,ReadOnly|WriteOnly);
	TQFS_CreateFileRoom(&Open_File,i,&TempFile);
	}else DeBug("File Already Exists",Infor_Infor);
}
/******************************************************************************
 Func: ��ȡ�ļ�����Ϣ��ҳ����������
 Time: 2014-7-23
 Ver.: V1.0
 Note:PageΪ���λ��
******************************************************************************/
void Read_FolderInfor(TQFS_Open_File *Open_File,Folder_FileInfor *FFI)
{
	;
	Nand_ReadPage(Open_File->PageCursor+Nand_Infor.FileStartPage,(uint8 *)FFI,Open_File->OffsetCursor,sizeof(Folder_FileInfor));
}
/******************************************************************************
 Func: ��ȡ�ļ�����Ϣ��ҳ����������
 Time: 2014-7-23
 Ver.: V1.0
 Note:PageΪ���λ��
******************************************************************************/
void Write_FolderInfor(TQFS_Open_File *Open_File,Folder_FileInfor *FFI)
{
	Nand_WritePage(Open_File->PageCursor+Nand_Infor.FileStartPage,(uint8 *)FFI,Open_File->OffsetCursor,sizeof(Folder_FileInfor));
}

void TQFS_FolderWriteFile(TQFS_Open_File *Open_File,Folder_FileInfor *Folder_File)
{
	
}
