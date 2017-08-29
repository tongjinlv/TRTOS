/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/

#include <include.h>
#include <stm32f10x.h>
#include <usb_mass_storage.h>
#include <usb_driver.h>
#include <usb_bulkonly.h>
#include <usb_scsi.h>
#include <board_driver.h>

USB_EndpDef Endp1,Endp2;
uint8 USB_MASS_TASKID;



/*--------------------------------------------------------------------------------------
 Func: USB��׼�豸����
 Time: 2011-4-27
 Note: 
------------------------------------------------------------------------------------- */
const uint8 USB_MASS_DeviceDesc[] =
  {
    0x12,                       				//device_desc����
    USB_DESCRIPTOR_TYPE_DEVICE, 				//�豸��������
    0x00,                       				//bcdUSB-version	USB2.0
    0x02,
    0x00,                       				//�豸��
    0x00,                       				//�豸����
    0x00,                       				//�豸Э��
    32,					          				//��������	8/16/32/64	ENDP0
    0x83,                       				//����ID (0x0483)
    0x04,
    0x50,                       				//��ƷID = 0x5750
    0x57,
    0x00,                       				//�豸�汾
    0x02,
    1,                          				//�����ַ�������λ������
    2,                          				//��Ʒ�ַ�������λ������
    3,                          				//�豸�����ַ�����������
    0x01                        				//��������������
  };											


/*--------------------------------------------------------------------------------------
 Func: USB��׼�豸���ñ�
 Time: 2011-4-27
 Note: 
------------------------------------------------------------------------------------- */
const uint8 USB_MASS_ConfigDesc[] =
  {
    /*-------------------------��������----------------------------*/
	0x09, 										//���ñ���
    USB_DESCRIPTOR_TYPE_CONFIGURATION, 			//���ñ�����
    0x20,										//�����������ܳ���											  	    
    0x00,
    0x01,         								//�豸֧�ֵĽӿ���
    0x01,         								//������ѡ��ֵSet_Configuration()
    0x00,         								//�������ַ���������
    0xC0,         								//���ߵ�Դ���� D6/�Թ��� D5/�г̻��� D7->1
    0x32,         								//������ N*2 mA
    /*-------------------------�ӿ�����----------------------------*/
    0x09,         								//�ӿ���������
    USB_DESCRIPTOR_TYPE_INTERFACE,				//�ӿ�����������
    0x00,         								//�ӿڱ��
    0x00,         								//�ӿڱ��� SetInterface()
    0x02,         								//�ӿڰ����Ķ˵��� 0/control pipe
    0x08,        								//�ӿ����� 		HID: 0x03	MASS:0x08
    0x06,         								//�ӿ������� 	HID: 1=BOOT, 0=no boot
    0x50,         								//�ӿ�Э������ 	HID: 0=none, 1=keyboard, 2=mouse */
    4,											//�ӿ��ַ�����������
	/*-------------------------�˵�����----------------------------*/
    0x07,   									//�˵���������
    USB_DESCRIPTOR_TYPE_ENDPOINT,				//�˵�����������  										//
    0x81,   									//�˵㷽�򼰶˵��(IN)  B7|B[3:0]
    USB_ENDPOINT_TYPE_BULK,						//�˵�����[BULK]
    USB_MASS_ENDP_PACKETSIZE, 					//bulk in ������
    0x00,										//�˵���󻺳�����С
    0x00,   									//�˵��жϼ��
    
    0x07,   									//�˵���������
    USB_DESCRIPTOR_TYPE_ENDPOINT,				//�˵�����������  	
    0x02,   									//�˵㷽�򼰶˵��(OUT)  B7|B[3:0]
    USB_ENDPOINT_TYPE_BULK,						//�˵�����[BULK]
    USB_MASS_ENDP_PACKETSIZE,					//bulk out������
    0x00,										//�˵���󻺳�����С
    0x00     									//�˵��жϼ��
};


/*----------------------------------------------------------------------------------------
 Func: �ַ���������		/ * LangID = 0x0409: U.S. English * /
----------------------------------------------------------------------------------------*/
const uint8 USB_MASS_StringLangID[] =
{
    4,
    USB_DESCRIPTOR_TYPE_STRING,							  
    0x09,
    0x04												   
}; 

/*----------------------------------------------------------------------------------------
 Func: �����ַ���������
----------------------------------------------------------------------------------------*/
const uint8 USB_MASS_StringVendor[] =
{	    
	34, 										/* Size of Vendor string */
    USB_DESCRIPTOR_TYPE_STRING,  				/* bDescriptorType*/
    /*HUBEI-QYKJ@2011*/
    'H', 0, 'U', 0, '-', 0, 'B', 0, 'E', 0, 'I', 0, '-', 0, 'Q', 0,
    'Y', 0, 'K', 0, 'J', 0, '@', 0, '2', 0, '0', 0, '1', 0, '1', 0
};

/*----------------------------------------------------------------------------------------
 Func: ��Ʒ�ַ���������
----------------------------------------------------------------------------------------*/
const uint8 USB_MASS_StringProduct[] =
{
	34,          						/* bLength */
    USB_DESCRIPTOR_TYPE_STRING,         /* bDescriptorType */
	/*HUBEI-QYKJ-TTS-USB*/
    'H', 0, 'B', 0, '-', 0, 'Q', 0,	'Y', 0, 'K', 0, 'J', 0, '-', 0, 
	'T', 0, 'T', 0, 'S', 0, '-', 0, 'U', 0, 'S', 0, 'B', 0, ' ', 0
};

/*----------------------------------------------------------------------------------------
 Func: �����ַ���
----------------------------------------------------------------------------------------*/
const uint8 USB_MASS_StringSerial[] =
{
    15,									//�ַ�������
	USB_DESCRIPTOR_TYPE_STRING,        	//������		   //0200310
    '0', 0, '2', 0, '0', 0,'0', 0,'3', 0, '1', 0, '0', 0
};

/*----------------------------------------------------------------------------------------
 Func: �ӿ��ַ���������
----------------------------------------------------------------------------------------*/
const uint8 USB_MASS_StringInterface[] =
{	    
	18, 										/* Size of Vendor string */
    USB_DESCRIPTOR_TYPE_STRING,  				/* bDescriptorType*/
    /*QYKJMASS*/
    'Q', 0, 'Y', 0, 'K', 0, 'J', 0, 'M', 0, 'A', 0, 'S', 0, 'S', 0,
};




/*-------------------------------------------------------------------------
 Func: ʵ��Mass Storage��ClassSpecial->Setup
 Time: 2011-5-6
 Ver.: V1.0
 Note:
-------------------------------------------------------------------------*/
uint8 USB_Mass_Storage_Setup()
{
	uint8 R;
	if(USB_REQ.wLength==0){
		if(USB_REQ.bRequest==b_REQUEST_MASS_STORAGE_RESET){
			USB_SendPacket(0,&USB_Endp0,&R,0);
			return USB_RESULT_SUCCESS;
		
		}else return USB_RESULT_UNSUPPORT; 
	
	}else{
		if(USB_REQ.bRequest==b_REQUEST_GET_MAX_LUN){
			R=USB_MASS_STORAGE_MAX_LUN;
		 	USB_SendPacket(0,&USB_Endp0,&R,0);
			return USB_RESULT_SUCCESS;
		
		}else return USB_RESULT_UNSUPPORT; 	
	}
}

/*-------------------------------------------------------------------------
 Func: ʵ��Mass Storage��ENDP_IN			   
 Time: 2011-5-6
 Ver.: V1.0
 Note:
-------------------------------------------------------------------------*/
void USB_Mass_Storage_DataIn()
{
	uint8 R;
	switch(USB_BOT_STAGE){
		case USB_BOT_STAGE_SETUP:			
			if(Endp1.wAddr>0){
				R=USB_SendPacket(1,&Endp1,Endp1.wAddr,Endp1.wLength);			//���ͺ�������
				CSW.DataResidue-=R;
			}else{				
				R=USB_SendPacket(1,&Endp1,(uint8 *)(&CSW),13);					//����CSW
				USB_BOT_STAGE=USB_BOT_STAGE_STATUS;
				USB_SetTxRxMode(2,USB_EPR_STAT_TX_DIS|USB_EPR_STAT_RX_VALID);				
				break;
			}
			
			break;
		case USB_BOT_STAGE_DATAIN:
			if(Endp1.wAddr>0){				
				R=USB_SendPacket(1,&Endp1,Endp1.wAddr,Endp1.wLength);			//���ͺ�������
				CSW.DataResidue-=R;
			}else{
				Tos_TaskSmail(USB_MASS_TASKID,SCSI_CMD_READ10);
				Tos_TaskRecover(USB_MASS_TASKID);
			}
			//USB_SetTxRxMode(2,USB_EPR_STAT_TX_DIS|USB_EPR_STAT_RX_VALID);
			break;		
		case USB_BOT_STAGE_STATUS:									
			USB_SetTxRxMode(2,USB_EPR_STAT_TX_DIS|USB_EPR_STAT_RX_VALID);
			break;					
	}
}


/*-------------------------------------------------------------------------
 Func: ʵ��Mass Storage��ENDP_IN			   
 Time: 2011-5-6
 Ver.: V1.0
 Note:
-------------------------------------------------------------------------*/
void USB_Mass_Storage_DataOut()
{
	uint8  Buffer[100];		
	uint16 R;
	switch(USB_BOT_STAGE){
		case USB_BOT_STAGE_STATUS:
			USB_BOT_STAGE=USB_BOT_STAGE_SETUP;
			R=USB_ReadBuffer(2,Buffer,100);
			R=USB_BulkOnly_CBWDecode(Buffer);					//����CBW��
			if(R==USB_RESULT_SUCCESS){
				USB_SendPacket(1,&Endp1,DBW.wAddr,DBW.Length); 	//�з�������Ҫ����
			}else if(R==USB_RESULT_RETURNCSW){
				USB_BOT_STAGE=USB_BOT_STAGE_STATUS;
				USB_SendPacket(1,&Endp1,(uint8 *)(&CSW),13);	//ֱ�ӷ���״̬,�����׶�								
				USB_SetTxRxMode(2,USB_EPR_STAT_TX_DIS|USB_EPR_STAT_RX_VALID);
			}else if(R==USB_RESULT_NOTREADY){
			}
			break;
		case USB_BOT_STAGE_DATAOUT:
			if(Endp2.rLength>0){
				R=USB_RecvPacket(2,&Endp2,Endp2.rAddr,Endp2.rLength);
				CSW.DataResidue-=R;
				if(R==0){					
					Tos_TaskSmail(USB_MASS_TASKID,SCSI_CMD_WRITE10);
					Tos_TaskRecover(USB_MASS_TASKID);	
				}else{
					USB_SetTxRxMode(2,USB_EPR_STAT_TX_DIS|USB_EPR_STAT_RX_VALID);
				}
			}else USB_SetTxRxMode(2,USB_EPR_STAT_TX_DIS|USB_EPR_STAT_RX_VALID);
			break;
		case USB_BOT_STAGE_DATAIN:
			USB_BOT_STAGE=USB_BOT_STAGE_STATUS;
			R=USB_ReadBuffer(1,(uint8 *)(&CSW),13);
			USB_SetTxRxMode(2,USB_EPR_STAT_TX_DIS|USB_EPR_STAT_RX_VALID);
			break;
		default: 	break; 	
	}
}


void USB_Mass_EndpoingConfig(void)
{
	USB_ConfigEndp(1,USB_MASS_ENDP_PACKETSIZE,USB_EPR_TYPE_BULK|USB_EPR_STAT_TX_VALID|USB_EPR_STAT_RX_DIS);	  	//IN		
	USB_ConfigEndp(2,USB_MASS_ENDP_PACKETSIZE,USB_EPR_TYPE_BULK|USB_EPR_STAT_TX_DIS|USB_EPR_STAT_RX_VALID);		//OUT
}


/*-------------------------------------------------------------------------
 Func: ʵ��Mass Storage�ĳ�ʼ��
 Time: 2011-5-6
 Ver.: V1.0
 Note:
-------------------------------------------------------------------------*/
void USB_Mass_Storage_Init(void)
{
	USB_DeviceDesc			=USB_MASS_DeviceDesc;
	USB_ConfigDesc			=USB_MASS_ConfigDesc;
	USB_ReportDesc			=0;
	USB_StringDesc[0]		=USB_MASS_StringLangID;
	USB_StringDesc[1]		=USB_MASS_StringVendor;
	USB_StringDesc[2]		=USB_MASS_StringProduct;
	USB_StringDesc[3]		=USB_MASS_StringSerial;
	USB_StringDesc[4]		=USB_MASS_StringInterface;
	USB_EndpointConfig 		=USB_Mass_EndpoingConfig;
	USB_ClassSpecial_Request=USB_Mass_Storage_Setup;	 	//�ض����û�SETUP
	USB_ENDP_DATA_OUT[2]	=USB_Mass_Storage_DataOut;		//�ض���Mass ����˵�
	USB_ENDP_DATA_IN[1]		=USB_Mass_Storage_DataIn;		//�ض���Mass ����˵�	
	USB_BOT_STAGE=USB_BOT_STAGE_STATUS;
}

/*-------------------------------------------------------------------------
 Func: USB�������ݴ�������
 Time: 2011-5-10
 Ver.: V1.0
 Note: ��USB���ݴ����ַ����ж������ռ��ʱ�䳤
-------------------------------------------------------------------------*/
void USB_MassStorage_Task(void *Tags)
{		
	uint8  i,Buffer[2048];									//����һ����ҳ�Ļ�����
	uint16 T,Length;
	Tos_TaskDelay(500);
	SystemUSB_Config(1);
	USB_Init();
	USB_Mass_Storage_Init();									//��ʼ��
	USB_MASS_TASKID	=Tos_TaskCurrent;							//ȡ��ǰ����ID
	USB_CONNECT_FULLSPEED
	while(1){
		//Tos_TaskSuspend();
		switch(Tos_TaskMail){
			//case (SCSI_CMD_READ10|0x8000):				
			//	break;
			case SCSI_CMD_READ10:
				if(SCSI_CMD.Len16>0){
					/*					
					if(SCSI_CMD.LBA&0x03){	T=(SCSI_CMD.LBA|0x03)-SCSI_CMD.LBA+1;}					
					else				 {	T=4;}
					if(SCSI_CMD.Len16<T)T=SCSI_CMD.Len16;
					Length=T<<9;
					*/
				//	WFS_ReadMem_Sectors(SCSI_CMD.LUN,SCSI_CMD.LBA,Buffer,0,512);
					i=USB_SendPacket(1,&Endp1,Buffer,512);
					CSW.DataResidue-=i;
					SCSI_CMD.Len16--;
					SCSI_CMD.LBA++;
					USB_BOT_STAGE=USB_BOT_STAGE_DATAIN;					
				}else{				
					USB_SendPacket(1,&Endp1,(uint8 *)(&CSW),13);					//����CSW					
					USB_BOT_STAGE=USB_BOT_STAGE_STATUS;					
				}									
				USB_SetTxRxMode(2,USB_EPR_STAT_TX_DIS|USB_EPR_STAT_RX_VALID);												 								
				break;
			case (SCSI_CMD_WRITE10|0x8000):				
				if(SCSI_CMD.LBA&0x07){	T=(SCSI_CMD.LBA|0x07)-SCSI_CMD.LBA+1;}
				else				 {	T=8;}
				if(SCSI_CMD.Len16<T)T=SCSI_CMD.Len16;
				Length=T<<9;
				Endp2.rAddr=0;
				USB_RecvPacket(2,&Endp2,Buffer,Length);
				USB_BOT_STAGE=USB_BOT_STAGE_DATAOUT;
				USB_SetTxRxMode(2,USB_EPR_STAT_TX_DIS|USB_EPR_STAT_RX_VALID);
				break;
			case SCSI_CMD_WRITE10:				
				if(SCSI_CMD.Len16>0){
				//	WFS_WriteMem_Sectors(SCSI_CMD.LUN,SCSI_CMD.LBA,Buffer,0,Endp2.rOffset);
					SCSI_CMD.Len16-=(Endp2.rOffset>>9);
					SCSI_CMD.LBA+=(Endp2.rOffset>>9);
					USB_BOT_STAGE=USB_BOT_STAGE_DATAOUT;
				}
				if(SCSI_CMD.Len16>0){					
					if(SCSI_CMD.Len16<8)T=SCSI_CMD.Len16;
					else				T=8;
					Length=T<<9;
					USB_RecvPacket(2,&Endp2,Buffer,Length);
				}else{					
					USB_BOT_STAGE=USB_BOT_STAGE_STATUS;				
					USB_SendPacket(1,&Endp1,(uint8 *)(&CSW),13);					//����CSW
				}
				USB_SetTxRxMode(2,USB_EPR_STAT_TX_DIS|USB_EPR_STAT_RX_VALID);				
				break;		
		}
	}
}



