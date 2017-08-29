/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/

#include <include.h>
#include <..\USB\USB_Include.h>
#include <Text.h>

BulkOnly_CBW_TypeDef CBW;				//CBW�鶨��
BulkOnly_CSW_TypeDef CSW;				//CSW�鶨��
BulkOnly_DBW_TypeDef DBW;				//DBW�鶨��

uint8 USB_BOT_STAGE;					//Bulkonly״̬

/*-------------------------------------------------------------------------
 Func: ʵ��CBW��Ľ���
 Time: 2011-5-6
 Ver.: V1.0
 Note:
-------------------------------------------------------------------------*/
uint8 USB_BulkOnly_CBWDecode(uint8 *Buffer)
{
	uint8 R;
	CBW.Signalture			=D32FromArray(Buffer,0);				//����С�˸�ʽ��32λ����
	CBW.Tag					=D32FromArray(Buffer+4,0);				//
	CBW.DataTransferLength	=D32FromArray(Buffer+8,0);
	CBW.Flags				=*(Buffer+12);
	CBW.Lun					=*(Buffer+13);
	CBW.CBLength			=*(Buffer+14);
	BufferCoppy(Buffer+15,CBW.CB,CBW.CBLength);
	DBW.Length				=CBW.DataTransferLength;					//Ĭ�Ϸ������ݳ���
	R=USB_ScsiDecode(CBW.CB);										   	//����command block��
	CSW.Signalture			=USB_BOT_CSW_SIGNALTURE;
	CSW.Tag					=CBW.Tag;
	CSW.DataResidue			=CBW.DataTransferLength;		
	if(R==USB_RESULT_SUCCESS){
		CSW.Status=USB_BOT_CSW_STATUS_PASSED;
		CSW.DataResidue -= DBW.Length;
	}else if(R==USB_RESULT_RETURNCSW){
		CSW.Status=USB_BOT_CSW_STATUS_PASSED;
		CSW.DataResidue -= DBW.Length;	 	
	}else if(R==USB_RESULT_UNSUPPORT){
		CSW.Status=USB_BOT_CSW_STATUS_FAILED;
	}else if(R==USB_RESULT_NOTREADY){
		CSW.Status=USB_BOT_CSW_STATUS_PASSED;
	}
	return R;
}


/*-------------------------------------------------------------------------
 Func: ʵ��CSW��Ľ���
 Time: 2011-5-6
 Ver.: V1.0
 Note:
-------------------------------------------------------------------------*/
void USB_BulkOnly_CSWDecode(uint8 *Buffer)
{
	CSW.Signalture			=D32FromArray(Buffer,0);				//����С�˸�ʽ��32λ����
	CSW.Tag					=D32FromArray(Buffer+4,0);				//
	CSW.DataResidue			=D32FromArray(Buffer+8,0);
	CSW.Status				=*(Buffer+12);
}													   

/*-------------------------------------------------------------------------
 Func: ʵ��CBW���Ĵ��PAI
 Time: 2011-5-6
 Ver.: V1.0
 Note:
-------------------------------------------------------------------------*/
void USB_BulkOnly_CSWEncode(uint8 *Buffer)
{
	D32ToArray(Buffer,CSW.Signalture,0);
	D32ToArray(Buffer+4,CSW.Tag,0);
	D32ToArray(Buffer+8,CSW.DataResidue,0);
	*(Buffer+12)=CSW.Status;													  
}




