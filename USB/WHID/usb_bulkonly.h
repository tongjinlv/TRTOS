/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/

#ifndef _TTS_USB_BULKONLY_H_
#define _TTS_USB_BULKONLY_H_

#include <include.h>


#define USB_BOT_CSW_STATUS_PASSED		0x00
#define USB_BOT_CSW_STATUS_FAILED		0x01
#define USB_BOT_CSW_STATUS_ERROR		0x02

#define USB_BOT_CBW_SIGNALTURE			0x43425355
#define USB_BOT_CSW_SIGNALTURE			0x53425355

#define USB_BOT_STAGE_IDLE				0x00			//��ʼ���н׶�
#define USB_BOT_STAGE_SETUP				0x01			//���ý׶�
#define USB_BOT_STAGE_DATAIN			0x02			//��������׶�
#define USB_BOT_STAGE_DATAOUT			0x03			//��������׶�
#define USB_BOT_STAGE_STATUS			0x04			//״̬�׶�




typedef struct
{
	uint32 Signalture;					//CBW��ǩ 0x43425355
	uint32 Tag;							//ƥ����,ƥ��CSW
	uint32 DataTransferLength;			//���ݴ��䳤��
	uint8  Flags;						//B7 0/host->dev 1/dev->host
	uint8  Lun;							//�߼����
	uint8  CBLength;					//commd block����
	uint8  CB[16];						//������	
}BulkOnly_CBW_TypeDef;

typedef struct							 
{
	uint32 Signalture;					//CSW��ǩ,0x53425355
	uint32 Tag;						   	//ƥ����,ƥ��CBW
	uint32 DataResidue;					//����ָʾ
	uint8  Status;						//����״̬
}BulkOnly_CSW_TypeDef;

typedef struct		  	
{							
	uint8  Dtype;						//DBW->Data block wraper, Dtype:��������
	uint8  *wAddr;						//�������ݻ�����
	uint16 Length;						//�������ݳ���
}BulkOnly_DBW_TypeDef;

extern BulkOnly_CBW_TypeDef CBW;				//CBW�鶨��
extern BulkOnly_CSW_TypeDef CSW;				//CSW�鶨��
extern BulkOnly_DBW_TypeDef DBW;				//DBW�鶨��
extern uint8 USB_BOT_STAGE;

/*-------------------------------------------------------------------------
 Func: ʵ��CBW��Ľ���
-------------------------------------------------------------------------*/
uint8 USB_BulkOnly_CBWDecode(uint8 *Buffer);

/*-------------------------------------------------------------------------
 Func: ʵ��CSW��Ľ���
-------------------------------------------------------------------------*/
void USB_BulkOnly_CSWDecode(uint8 *Buffer);  

/*-------------------------------------------------------------------------
 Func: ʵ��CBW���Ĵ��
-------------------------------------------------------------------------*/
void USB_BulkOnly_CSWEncode(uint8 *Buffer);




#endif

