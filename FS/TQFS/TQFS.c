/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Tools_Include.h>
#include <TQFS.h>

/*
ע�⣺TQFS�����ļ���Ϣ���⣬��ͨ���ݴ洢������ҳΪ��λ�������ļ���Ϣ
		�ļ���Ϣ��ÿ�ֽڶ�Ӧһ��ҳ������ҳ��״̬��Ϣ
		TQFS����ļ��ṹû�й涨Ŀ¼�ṹ������ʹ����û��Ŀ¼�ṹ������£�Ҳ����
		���й���Ŀ¼�ṹ��û��Ŀ¼�ṹ������£�Ŀ¼��Ŀ¼�ļ��������ӵȶ������ļ�����ʽ���ڣ�
		��Ҫ����Ŀ¼���Ա����Ҫ��Ŀ¼�ļ������������ﴴ���ļ���Ŀ¼��


*/
Nand_UserInfor Nand_Infor;

/******************************************************************************
 Func: ��ȡ�ļ���Ϣ��ҳ��Spare����
 Time: 2014-7-23
 Ver.: V1.0
 Note:PageΪ���λ��
******************************************************************************/
BOOL Read_FileInfor(uint32 Page,File_Infor *FI)
{
	Page+=Nand_Infor.FileStartPage;
	Nand_ReadPage(Page,(uint8 *)FI,0,sizeof(File_Infor));
  return True;
}

/******************************************************************************
 Func: д���ļ���Ϣ��ҳ��Spare����
 Time: 2014-7-23
 Ver.: V1.0
 Note:PageΪ���λ��
******************************************************************************/
BOOL Write_FileInfor(uint32 Page,File_Infor *FI)
{
	Page+=Nand_Infor.FileStartPage;
	Nand_WritePage(Page,(uint8 *)FI,0,sizeof(File_Infor));
	return True;
}

/******************************************************************************
 Func: дҳ��ӳ���ǵ�TAB
 Time: 2014-7-23
 Ver.: V1.0
 Note:
******************************************************************************/
void TQFS_MarkPageInTab(uint32 Block,uint8 *Mark)
{
	uint32 TabPage,TabOffset;
	if(NAND_ZONE_SIZE>Nand_Infor.TabInBlock)
	{
		Block-=(Nand_Infor.TabInBlock+1);//ƫ�����ݿ鵽���λ��0
		Block*=NAND_BLOCK_SIZE;
		TabPage=Block/NAND_PAGE_SIZE;
		TabOffset=Block%NAND_PAGE_SIZE;
		Nand_WritePage(TabPage,&Mark[0],TabOffset+NAND_SPARE_SIZE,NAND_BLOCK_SIZE);
	}
}
/******************************************************************************
 Func: Ѱ�ҵ�һ���հ�����ҳ�����Tab���λ
 Time: 2014-7-23
 Ver.: V1.0
 Note:���ػ�ҳ�����������ҳSpare�ĵ�һ���ֽ�
******************************************************************************/
uint32 TQFS_FindKeyPageMark(uint8 Key,uint8 Mark)
{
	uint32 m,n,j;
	uint8 Buf[NAND_BLOCK_SIZE];
	for(n=0;n<NAND_BLOCK_SIZE;n++)//ҳ��
	{
		for(m=0;m<(NAND_PAGE_SIZE/NAND_BLOCK_SIZE);m++)//ҳ���ж��ٸ�64�ֽ�
		{
			Nand_ReadPage(Nand_Infor.TabInBlock*NAND_BLOCK_SIZE+n,&Buf[0],NAND_SPARE_SIZE+m*NAND_BLOCK_SIZE,NAND_BLOCK_SIZE);
			j=SerchKeyFromBytes(&Buf[0],Key,NAND_BLOCK_SIZE);
			if(j!=0xffff)
			{
				Buf[j]=Mark;
				Nand_WritePage(Nand_Infor.TabInBlock*NAND_BLOCK_SIZE+n,&Buf[0],NAND_SPARE_SIZE+m*NAND_BLOCK_SIZE,NAND_BLOCK_SIZE);
				return (n*NAND_PAGE_SIZE+m*NAND_BLOCK_SIZE+j);
			}
		}
	}	
	return 0xffffffff;
}
/******************************************************************************
 Func: ��TABλ��ѡ�Źؼ��ֲ��Ҽ�¼�ؼ��ֶ�Ӧ����ҳ��ҳλ��
 Time: 2014-7-23
 Ver.: V1.0
 Note:���ط��ϼ�¼����
******************************************************************************/
uint8 _TQFS_FindAllKey(uint8 Key,uint32 *AddrBuf,uint8 BufLength)
{
	uint32 m,n,j;
	uint8 i=0;
	uint8 Buf[NAND_BLOCK_SIZE];
	for(n=0;n<NAND_BLOCK_SIZE;n++)//ҳ��
	{
		for(m=0;m<(NAND_PAGE_SIZE/NAND_BLOCK_SIZE);m++)//ҳ���ж��ٸ�64�ֽ�
		{
			Nand_ReadPage(Nand_Infor.TabInBlock*NAND_BLOCK_SIZE+n,&Buf[0],NAND_SPARE_SIZE+m*NAND_BLOCK_SIZE,NAND_BLOCK_SIZE);
			for(j=0;j<NAND_BLOCK_SIZE;j++)if(Buf[j]==Key)AddrBuf[i++]=(n*NAND_PAGE_SIZE+m*NAND_BLOCK_SIZE+j);
			if(i>=BufLength)return i;
		}
	}	
	return i;
}
/******************************************************************************
 Func: ��TABλ��ѡ�Źؼ��ֲ��Ҽ�¼�ؼ��ִ浽AddrBuf����Է�ҳ��ʽ
 Time: 2014-7-23
 Ver.: V1.0
 Note:���ط��ϼ�¼����
******************************************************************************/
uint8 TQFS_FindAllKey(uint8 Key,uint32 *AddrBuf,uint8 BufLength,uint16 Page)
{

	uint32 m,n;
	uint8 i=0;
	uint8 Count=0;
	uint16 Start,End;
	Start=Page*BufLength;
	End=BufLength*(Page+1);
	Tos_TaskGetDev(DeviceId_NANDFLASH,0);
	for(m=0;m<NAND_BLOCK_SIZE;m++)
	{
		NAND_CMD=0x00;
		Nand_WriteAddr(Nand_Infor.TabInBlock*NAND_BLOCK_SIZE+m,NAND_SPARE_SIZE);
		NAND_CMD=0x30;
		Tos_TaskDelay(1);
		for(n=0;n<NAND_PAGE_SIZE;n++)
		{
			if(NAND_DAT8==Key)
			{
				if(i>=Start&&i<End)if(AddrBuf)AddrBuf[Count++]=(m*NAND_PAGE_SIZE+n);
				if(i>=End)break;
				if(Count>=BufLength)break;
				i++;
			}
		}
	}
	Tos_TaskDropDev(DeviceId_NANDFLASH);
	return Count;
}
/******************************************************************************
 Func: Ѱ��TAB���׸��������͵�ҳ��ƫ��λ��
 Time: 2014-7-23
 Ver.: V1.0
 Note:
******************************************************************************/
uint32 TQFS_FindFristTypeKey(uint8 Key)
{

	uint32 m,n;
	Tos_TaskGetDev(DeviceId_NANDFLASH,0);
	for(m=0;m<NAND_BLOCK_SIZE;m++)
	{
		NAND_CMD=0x00;
		Nand_WriteAddr(Nand_Infor.TabInBlock*NAND_BLOCK_SIZE+m,NAND_SPARE_SIZE);
		NAND_CMD=0x30;
		Tos_TaskDelay(1);
		for(n=0;n<NAND_PAGE_SIZE;n++)
		{
			if(NAND_DAT8==Key)
			{
				Tos_TaskDropDev(DeviceId_NANDFLASH);
				return (m*NAND_PAGE_SIZE+n);
			}
		}
	}
	Tos_TaskDropDev(DeviceId_NANDFLASH);
	return 0xffffffff;
}
uint32 TQFS_FindFristTypeName(uint8 Key,uint8 *Name)
{

	uint32 m,n;
//	File_Infor FI;
	Tos_TaskGetDev(DeviceId_NANDFLASH,0);
	for(m=0;m<NAND_BLOCK_SIZE;m++)
	{
		NAND_CMD=0x00;
		Nand_WriteAddr(Nand_Infor.TabInBlock*NAND_BLOCK_SIZE+m,NAND_SPARE_SIZE);
		NAND_CMD=0x30;
		Tos_TaskDelay(1);
		for(n=0;n<NAND_PAGE_SIZE;n++)
		{
			if(NAND_DAT8==Key)
			{
// 				Read_FileInfor(m*NAND_PAGE_SIZE+n,&FI);
// 				if(CompareWithString(FI.FileName,Name))
// 				{
// 					DeBug("FileName=%s",FI.FileName,Infor_Infor);
// 				Tos_TaskDropDev(DeviceId_TQFS);
				return (m*NAND_PAGE_SIZE+n);
// 				}
// 				NAND_CMD=0x00;
// 				Nand_WriteAddr(Nand_Infor.TabInBlock*NAND_BLOCK_SIZE+m,NAND_SPARE_SIZE+n);
// 				NAND_CMD=0x30;
// 				Tos_TaskDelay(1);
			}
		}
	}
	Tos_TaskDropDev(DeviceId_NANDFLASH);
	return 0xffffffff;
}
/******************************************************************************
 Func: ��ʽ��NandFlash 
 Time: 2014-7-23
 Ver.: V1.0
 Note:���ػ�ҳ�����������ҳSpare�ĵ�һ���ֽ�
******************************************************************************/
uint16 TQFS_FormatNand()
{
	uint32 m,n;
	uint8  Buf[NAND_BLOCK_SIZE];
	uint16 Bad_Count=0;//�ܻ���ҳ
	uint16 BlockBad_Count;//�黵��ҳ
	
	if(!Tos_Device_Tab[DeviceId_NANDFLASH].Init)
	{
		DeBug("You Must Be Run NandInit",Infor_Error);
		return 0xffff;
	}
	TQFS_Init();
	Nand_Infor.TabInBlock=0xffff;
	for(m=0;m<NAND_ZONE_SIZE;m++)
	{
		BlockBad_Count=0;
		Nand_EraseBlock(m);
		for(n=0;n<NAND_BLOCK_SIZE;n++)
		{
			if(Cheak_BadPage(NAND_BLOCK_SIZE*m+n)==0xffff)Buf[n]=FT_NotUsed;
			else {Buf[n]=FT_Bad;BlockBad_Count++;Bad_Count++;}
		}
		TQFS_MarkPageInTab(m,&Buf[0]);
		if(Nand_Infor.TabInBlock==0xffff&&!BlockBad_Count)Nand_Infor.TabInBlock=m;//��¼�׸����õĿ鵱��ϵͳҳӳ���
		DeBug("Block[%d]Find[%d]BadPage",m,BlockBad_Count,Infor_Infor);
	}
	DeBug("DeviceFind[%d]BadPage",m,Bad_Count,Infor_Infor);
	return Bad_Count;
}
/******************************************************************************
 Func: �ڿ���Ѱ��Tab��λ��
 Time: 2014-7-23
 Ver.: V1.0
 Note:����Tab���ڿ��ƫ��λ��
******************************************************************************/
uint16 TQFS_FindTabAddr()
{
	uint8 Buf[2];
	uint32 i;
	for(i=0;i<NAND_ZONE_SIZE;i++)
	{
		Nand_ReadPage(i*NAND_BLOCK_SIZE,&Buf[0],0,2);
		if(Buf[0]==0xff)return i;
	}
	return 0xffff;
}
/******************************************************************************
 Func: NandFlash��Ϣ�ռ�
 Time: 2014-7-23
 Ver.: V1.0
 Note:Nand��ʹ�����
******************************************************************************/
void Nand_InforCollect(Nand_UserInfor *NUI)
{

	uint32 m,n;
	Tos_TaskGetDev(DeviceId_NANDFLASH,0);
	for(m=0;m<NAND_BLOCK_SIZE;m++)
	{
		NAND_CMD=0x00;
		Nand_WriteAddr(Nand_Infor.TabInBlock*NAND_BLOCK_SIZE+m,NAND_SPARE_SIZE);
		NAND_CMD=0x30;
		Tos_TaskDelay(1);
		for(n=0;n<NAND_PAGE_SIZE;n++)
		{
			switch(NAND_DAT8)
			{
				case FT_NotUsed:NUI->FT_NotUsed++;break;
				case FT_Bad:NUI->FT_Bad++;break;
				case FT_FolderHead:NUI->FT_FolderHead++;break;
				case FT_FileHead:NUI->FT_FileHead++;break;
				case FT_LinkHead:NUI->FT_LinkHead++;break;
				case FT_RootDirHead:NUI->FT_RootDirHead++;break;
				default :NUI->FT_Other++;break;
			}
		}
	}
	Tos_TaskDropDev(DeviceId_NANDFLASH);
}
/******************************************************************************
 Func: TQFS��ʼ��
 Time: 2014��Ϧ
 Ver.: V1.0
 Note:
******************************************************************************/
void TQFS_Init()
{
 	Nand_Infor.TabInBlock=TQFS_FindTabAddr();
 	Nand_Infor.FileStartPage=Nand_Infor.TabInBlock+1;//����Tab��ռ�õ�һ����
 	Nand_Infor.FileStartPage*=NAND_BLOCK_SIZE;//�ļ���ʼҳ
 	Nand_InforCollect(&Nand_Infor);
}
