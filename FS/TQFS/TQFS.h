/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TQFS_H_
#define _TQFS_H_
#include <Define.h>
#include <Nand_Flash.h>
#include <Tos_Timer.h>

enum Page_Status
{
	PS_NotUsed=0xff,//ҳδ��ʹ��
	PS_CanUse=0xfe, //ҳ����ʹ��
	PS_BeUse=0xfc,  //ҳ������ʹ��
	PS_NotFully=0xf8,//ҳδʹ����ȫ
	PS_UsedFully=0xf0,//ҳ��ʹ����
	PS_Delete=0xe0, //ҳɾ��
	PS_Dis=0xc0,    //ҳ������
	PS_Bad=0x00     //ҳ����
};
enum FileType{
	FT_NotUsed=0xff,//ҳδ��ʹ��
	FT_ReadyRoom=0x7f,//δ���峤�ȵķ����ļ��洢��
	FT_File=0x1f,//�ļ����͵�δ���峤�ȴ洢��
	FT_FileHead=0x1e,//�ļ���
	FT_FileCenter=0x1c,//�ļ���
	FT_FileEnd=0x18,//�ļ�β��
	FT_Folde=0x2f,//�ļ������͵�δ���峤�ȴ洢��
	FT_FolderHead=0x2e,//�ļ���ͷ��־
	FT_FolderCenter=0x2c,//�ļ����м��־
	FT_FolderEnd=0x28,//�ļ���β��־
	FT_Link=0x3f,//�������͵�δ���峤�ȴ洢��
	FT_LinkHead=0x3e,//�����ļ�ͷ��־
	FT_LinkCenter=0x3c,//�����ļ��м��־
	FT_LinkEnd=0x38,//�����ļ�β��־
	FT_RootDir=0x4f,//·���ļ���־
	FT_RootDirHead=0x4e,//���ļ�ͷ��־
	FT_RootDirCenter=0x4c,//���ļ��м��־
	FT_RootDirEnd=0x48,//���ļ�β��־
	FT_Delete=0x08,//�ļ���ɾ����־
	FT_Tab=0x6f,//�ļ�ҳ���������Tab���־
	FT_Bad=0x00     //ҳ�𻵱�־
};

typedef struct
{
	uint32 FT_NotUsed;
	uint32 FT_CanUse;
	uint16 FT_Bad;
	uint16 FT_FolderHead;
	uint16 FT_FileHead;
	uint16 FT_LinkHead;
	uint16 FT_RootDirHead;
	uint16 FT_Other; 
	uint16 TabInBlock;
	uint32 FileStartPage;
}Nand_UserInfor; 


typedef struct
{
	uint8  FileType;//��ҳ��������
	uint8  Page_Status;//������Ϊҳ����Ҫ��λ��
	uint8  PS_ST;//ҳ״̬��ʱδʹ��
	uint8  FileName[14];//�ļ�������Ϊ14���ֽ�
	uint8  FileFormat[6];//�ļ���ʽ
	uint8  FileVirtue;//�ļ�����
	Date_Time CreateDate;//�ļ�����ʱ��
	Date_Time ReBuildDate;//�ļ��޸�ʱ��
	uint32 PreviousPageAddr;//�ļ���һҳ�ĵ�ַ
	uint32 NextPageAddr;//�ļ���һҳ�ĵ�ַ
	uint32 FileSize;//���ļ�����
	uint16 FileIndex;//�ļ�������ҳΪ�ڼ�ҳ
	uint16 DataLegnth;//��ǰҳ��Ч���ݳ���
	uint32 FileID;//�ļ�ID�����ļ�ͷ����ҳ�����λ��
	uint16 SpareCrc;//Spare����У��ֵ
	uint16 PageCrc;//Page��������У��ֵ
}File_Infor;//ҳͷ�ṹ����Spare��

extern Nand_UserInfor Nand_Infor;
BOOL Read_FileInfor(uint32 Page,File_Infor *FI);
BOOL Write_FileInfor(uint32 Page,File_Infor *FI);
uint16 TQFS_FormatNand(void);
uint16 TQFS_FindTabAddr(void);
uint32 TQFS_FindFirstUsingPage(uint32 StartPage);
void Nand_InforCollect(Nand_UserInfor *NUI);
void TQFS_Init(void);
uint32 TQFS_FindKeyPageMark(uint8 Key,uint8 Mark);
uint8 TQFS_FindAllKey(uint8 Key,uint32 *AddrBuf,uint8 BufLength,uint16 Page);
uint32 TQFS_FindFristTypeKey(uint8 Key);
uint32 TQFS_FindFristTypeName(uint8 Key,uint8 *Name);
#endif
