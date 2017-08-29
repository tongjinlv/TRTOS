/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <FS_Include.h>
#include <TQFS_File.h>
#include <Tools_Include.h>
#include <stdlib.h>



/*******************************************************************************
Func:����ļ�����������Ϣ
Date:2014-7-27
Note:FileSize=0ʱΪ��ȷ���ļ�����
*******************************************************************************/
void TQFS_FileRoomInfor(File_Infor *FI,void *File,uint32 FileSize,uint8 FileVirtue)
{
	uint8 Buf[14];
	BufferFill(FI,0xff,sizeof(File_Infor));//���ò�������Ϊ���޸�״̬
	GetFileNameFormat(File,&Buf[0],Null);
	StringCoppy(&Buf[0],&FI->FileName[0]);
	GetFileNameFormat(File,Null,&Buf[0]);
	StringCoppy(&Buf[0],&FI->FileFormat[0]);
	FI->FileType=FT_ReadyRoom;//��������ļ�����
	BufferCoppy(&NowTime,&FI->CreateDate,sizeof(Date_Time));
	FI->Page_Status=FT_ReadyRoom;//ҳ������ʹ��
	if(FileSize)FI->FileSize=FileSize;
	FI->FileID=rand();//�ļ�ID��ʵ����������������뱣֤ͬһ���ļ���ID����ͬ
	FI->FileVirtue=FileVirtue;//�ɶ���д���ص�����	
}
/*******************************************************************************
Func:��ĳĳҳ�����ļ��ռ�
Date:2014-7-27
Note:PageΪ���λ�ü���Ϊ�ļ��洢����ҳΪ��һҳ
*******************************************************************************/
uint32 TQFS_CreateFileRoom(TQFS_Open_File *Open_File,uint32 Page,File_Infor *FI)
{
	FI->FileID=Page;
	FI->FileIndex=0;
	DeBug("Create Object File In Page[%d]",Page,Infor_Infor);
	Write_FileInfor(Page,FI);
	TQFS_SetCursor(Open_File,Page,0);
	return 0;
}
/*******************************************************************************
Func:���ö�д�����α�
Date:2014-7-27
Note:PageΪ���λ�ü���Ϊ�ļ��洢����ҳΪ��һҳ
*******************************************************************************/
void TQFS_SetCursor(TQFS_Open_File *Open_File,uint32 Page,uint16 Offset)
{
	Open_File->PageCursor=Page;
	Open_File->OffsetCursor=Offset;
}
/*******************************************************************************
Func:��ȡҳ������
Date:2014-7-27
Note:����״̬
*******************************************************************************/
TQFS_Error TQFS_ReadPageContext(TQFS_Open_File *Open_File,uint8 *rBuffer,uint16 Length)
{
	File_Infor TempFile;
	int OviLenth;
	uint16 Offset=0;
  OviLenth=(Open_File->OffsetCursor+Length);
	OviLenth-=NAND_PAGE_SIZE;//д���µĳ���
	if(OviLenth>=0)//��ǰҳ����
	{
		Nand_ReadPage(Nand_Infor.FileStartPage+Open_File->PageCursor,&rBuffer[Offset],Open_File->OffsetCursor+NAND_SPARE_SIZE,Length-OviLenth);
		Offset=Length-OviLenth;
		Open_File->OffsetCursor=0;
		Read_FileInfor(Open_File->PageCursor,&TempFile);
		if(TempFile.NextPageAddr==0xffffffff)return TE_NoNextPage;
		else{
			Open_File->PageCursor=TempFile.NextPageAddr;
			Length=OviLenth;
		}			
	}
		Nand_ReadPage(Nand_Infor.FileStartPage+Open_File->PageCursor,&rBuffer[Offset],Open_File->OffsetCursor+NAND_SPARE_SIZE,Length);
		Open_File->OffsetCursor+=Length;
	if(OviLenth>=0)return TE_NewPage;
	else return TE_CurrentPage;
}
/*******************************************************************************
Func:д���ݵ�ָ��ҳ
Date:2014-7-27
Note:���ظ�ҳд���ʣ����
*******************************************************************************/
TQFS_Error TQFS_WritePageContext(TQFS_Open_File *Open_File,uint8 *Buffer,uint16 Length)
{
	File_Infor TempFile;
	int OviLenth;
	uint16 Offset=0;
  OviLenth=(Open_File->OffsetCursor+Length);
	OviLenth-=NAND_PAGE_SIZE;//д���µĳ���
	if(OviLenth>=0)//��ǰҳ����
	{
		Nand_WritePage(Nand_Infor.FileStartPage+Open_File->PageCursor,&Buffer[Offset],Open_File->OffsetCursor+NAND_SPARE_SIZE,Length-OviLenth);
		Offset=Length-OviLenth;
		Open_File->OffsetCursor=0;
		Read_FileInfor(Open_File->PageCursor,&TempFile);
		TempFile.NextPageAddr=TQFS_FindKeyPageMark(FT_NotUsed,FT_FileCenter);
		DeBug("TempFile.NextPageAddrTempFile.NextPageAddr%x",TempFile.NextPageAddr,Infor_Infor);
		if(TempFile.NextPageAddr==0xffffffff)
		{
			DeBug("Page after use All",Infor_Infor);
			return TE_NoNextPage;
		}
		TempFile.Page_Status=PS_UsedFully;//���ҳ��ʹ����
		Write_FileInfor(Open_File->PageCursor,&TempFile);//�ڵ�ǰҳд����ҳ��ַ
		Open_File->PageCursor=TempFile.NextPageAddr;
	  TempFile.Page_Status=PS_NotFully;
		TempFile.PreviousPageAddr=Open_File->PageCursor;
		TempFile.NextPageAddr=0xffffffff;
		TempFile.FileIndex++;
		Write_FileInfor(Open_File->PageCursor,&TempFile);//�ڵ�ǰҳд����ҳ��ַ
		Length=OviLenth;		
	}
		Nand_WritePage(Nand_Infor.FileStartPage+Open_File->PageCursor,&Buffer[Offset],Open_File->OffsetCursor+NAND_SPARE_SIZE,Length);
		Open_File->OffsetCursor+=Length;
	if(OviLenth>=0)return TE_NewPage;
	else return TE_CurrentPage;
}

