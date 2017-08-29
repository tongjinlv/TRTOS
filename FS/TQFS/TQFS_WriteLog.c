/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <include.h>
#include <FS_Include.h>
#include <Tools_include.h>
#include <TQFS_WriteLog.h>
TQFS_Open_File DeBug_OpenFile;


/****************************************************************************
Date:2014-5-12
Func:д��־�ļ���ʼ��
Note:
****************************************************************************/
void WriteLog_Init()
{
	File_Infor FI;
	uint32 i;
	TQFS_FileRoomInfor(&FI,"DeBugFile.txt",0,ReadOnly|WriteOnly);//�����ļ�������Ϣ
	i=TQFS_FindKeyPageMark(FT_NotUsed,FT_FileHead);//Ѱ�ҿ�������
 	TQFS_CreateFileRoom(&DeBug_OpenFile,i,&FI);	//д�ļ�ͷ
 	TQFS_SetCursor(&DeBug_OpenFile,i,0);//���ù��
}
/****************************************************************************
Date:2014-5-12
Func:д��־�ļ�
Note:
****************************************************************************/
void DeBug_WriteLog(void *String)
{
	TQFS_WritePageContext(&DeBug_OpenFile,String,GetTextLength(String));//׷�����ݵ���־β��
	DeBug("WriteLog:%s",String,Infor_Infor);//����ӡд�����־��Ϣ�����Խӿ�
}
