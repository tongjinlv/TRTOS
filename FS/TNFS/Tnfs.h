/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TNFS_H_
#define _TNFS_H_
#include <Include.h>


//void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)

typedef void *(*FuncWR)(uint32 Addr,uint8 *Data,uint16 Length);

typedef enum
{
	FT_Document=1,
	FT_Folder=2,
}FileType;
typedef struct
{
	uint16 PageSize;
	uint16 Note;
	uint32 BaseAddr;
	FuncWR Write;
	FuncWR Read;
}Tnfs_InitStruct; 


typedef struct
{
	FileType FT;
	uint8 Name[24];
	uint8 Version;
	uint32 Date;
	uint32 Length;//�ļ����ݳ��Ȱ���������������ļ���Ϣ����
	uint32 NextPage;
}Tnfs_FileHead;

#endif

