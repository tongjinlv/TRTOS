/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/

#include <include.h>
#include <usb_scsi.h>
#include <usb_driver.h>
#include <usb_bulkonly.h>
#include <usb_mass_storage.h>
#include <Text.h>

uint8 USB_Scsi_Buffer[20];																	 

Scsi_Cmd_TypeDef SCSI_CMD;

const uint8 USB_Scsi_Standard_CmdInquiry[]=
{
	0x00,0x80,0x02,0x02,0x20,0x00,0x00,0x00,
	'H', 'B', '-', 'Q', 'Y', 'K', 'J', ' ',
	'S', 'M', 'A', 'L', 'L', '-', 'C', 'O',
	'M', 'P', 'U', 'T', 'E', 'R', ' ', ' ',
	'1', '.', '0', ' '
};

const uint8 USB_Scsi_Evpd_CmdInquiry[] 	=	{0x00,0x00,0x00,0x00,0x00					};
const uint8 USB_Scsi_Mode_Sensor6[]		=	{0x03,0x00,0x00,0x00	  					};
const uint8 USB_Scsi_Mode_Sensor10[]	=	{0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00	};

/*-------------------------------------------------------------------------
 Func: SCSI�����
 Time: 2011-5-6
 Ver.: V1.0
 Note:
-------------------------------------------------------------------------*/
void USB_Scsi_SendPacket(uint8 Dtype,uint8 *wAddr,uint16 Length)
{
	DBW.Dtype=Dtype;	
	DBW.wAddr=wAddr;
	if(Length>DBW.Length)Length=DBW.Length;
	else DBW.Length=Length;
}


/*-------------------------------------------------------------------------
 Func: SCSI����ش洢����С
 Time: 2011-5-6
 Ver.: V1.0
 Note: return / packetsize in bytes
-------------------------------------------------------------------------*/
uint8 USB_Scsi_GetMemSize(uint8 SizeType)
{
	uint8  i;
	uint32 Size;
	
	//Size=WFS_MEM_LOG_VALIDBLOCK*WFS_MEM_BLOCK_SIZE/512;
	if(SizeType==SCSI_CMD_READ_FORMAT_CAPACITIES){		
		for(i=0;i<3;i++)USB_Scsi_Buffer[i]=0;
		USB_Scsi_Buffer[3]=0x08;
	  D32ToArray(&USB_Scsi_Buffer[4],Size,1);
		D32ToArray(&USB_Scsi_Buffer[8],512,1);
		USB_Scsi_Buffer[8]=0;										//for resevd
		i=12;
	}else if(SizeType==SCSI_CMD_READ_CAPACITY){		
		Size-=1;
		D32ToArray(&USB_Scsi_Buffer[0],Size,1);
		D32ToArray(&USB_Scsi_Buffer[4],512,1);		
		i=8;
	}
	return i;
}

/*-------------------------------------------------------------------------
 Func: SCSI����ش���״̬����
 Time: 2011-5-6
 Ver.: V1.0
 Note:
-------------------------------------------------------------------------*/
void USB_Scsi_RecordSense(uint8 SenseKey,uint8 AddSenseCode)
{
	uint8 i;
	for(i=0;i<18;i++)USB_Scsi_Buffer[i]=0;
	USB_Scsi_Buffer[0]=0x70;					//Error code
	USB_Scsi_Buffer[2]=SenseKey&0x0F;			//Sense Key
	USB_Scsi_Buffer[7]=0x0A;					//Add length
	USB_Scsi_Buffer[12]=AddSenseCode;			//ASC area
};

/*-------------------------------------------------------------------------
 Func: SCSI�������
 Time: 2011-5-6
 Ver.: V1.0
 Note:
-------------------------------------------------------------------------*/
uint8 USB_ScsiDecode(uint8 *Buffer)
{
	uint8 i,R=USB_RESULT_SUCCESS;		
	SCSI_CMD.Opcode	=Buffer[0];								//��ȡ������
	SCSI_CMD.LUN	=Buffer[1]>>5;							//��ȡ���								 
	SCSI_CMD.LBA	=D32FromArray(Buffer+2,1);			//��ȡ�߼���ַ
	SCSI_CMD.Len16	=D16FromArray(Buffer+7,1);			//��ȡ16λ����
	SCSI_CMD.Len32	=D32FromArray(Buffer+6,1);			//��ȡ32λ����	
	switch(SCSI_CMD.Opcode){				
		case SCSI_CMD_MODE_SELECT:			R=USB_RESULT_UNSUPPORT;	break;	//����Host���ⲿ�豸���ò���
		case SCSI_CMD_SEND_DIAGNOSTIC:		R=USB_RESULT_UNSUPPORT;	break;	//�̼��Լ�
		case SCSI_CMD_VERIFY:				R=USB_RESULT_UNSUPPORT;	break;	//����У��
		case SCSI_CMD_ALLOW_MEDIUM_REMOVAL:	R=USB_RESULT_RETURNCSW;	break;	//Success
		case SCSI_CMD_TEST_UNIT_READY:		R=USB_RESULT_RETURNCSW;	break;	//ֱ�ӷ���Ready		
		case SCSI_CMD_START_STOP_UNIT:		R=USB_RESULT_RETURNCSW;	break;	//success ��ʼ��ֹͣ
		case SCSI_CMD_INQUIRY:			
			i=Buffer[1]&0x01;
			if(i)USB_Scsi_SendPacket(0,(uint8 *)USB_Scsi_Evpd_CmdInquiry,5);
			else USB_Scsi_SendPacket(0,(uint8 *)USB_Scsi_Standard_CmdInquiry,36);
			break;		
		case SCSI_CMD_MODE_SENSE6: 								//��host����֧�ֵĲ���
			//SCSI_CMD.Length=SCSI_CMD.Len16;																
			USB_Scsi_SendPacket(0,(uint8 *)USB_Scsi_Mode_Sensor6,4);	
			break;
		case SCSI_CMD_MODE_SENSE10:
			//SCSI_CMD.Length=SCSI_CMD.Len16;
			USB_Scsi_SendPacket(0,(uint8 *)USB_Scsi_Mode_Sensor10,8);
			break;	
		case SCSI_CMD_REQUEST_SENSE:									//�����豸����������ִ�н������״̬����
			//SCSI_CMD.Length=Buffer[4];
			USB_Scsi_SendPacket(0,USB_Scsi_Buffer,18);		
			break;											
		case SCSI_CMD_READ_CAPACITY:
			//SCSI_CMD.Length=8;
			i=USB_Scsi_GetMemSize(SCSI_CMD_READ_CAPACITY);
			USB_Scsi_SendPacket(0,USB_Scsi_Buffer,i);
			break;
		case SCSI_CMD_READ_FORMAT_CAPACITIES:					//��ȡ��ʽ��������Ϣ
			//SCSI_CMD.Length=12;//SCSI_CMD.Len16;			
			i=USB_Scsi_GetMemSize(SCSI_CMD_READ_FORMAT_CAPACITIES);
			USB_Scsi_SendPacket(0,USB_Scsi_Buffer,i);
			break;
		case SCSI_CMD_FORMAT_UNIT:								//�ͼ���ʽ��		
			break;	
		case SCSI_CMD_READ10:
			Tos_TaskSmail(USB_MASS_TASKID,SCSI_CMD_READ10);
			Tos_TaskRecover(USB_MASS_TASKID);
			R=USB_RESULT_NOTREADY;
			break;
		case SCSI_CMD_WRITE10:
			Tos_TaskSmail(USB_MASS_TASKID,SCSI_CMD_WRITE10|0x8000);
			Tos_TaskRecover(USB_MASS_TASKID);
			R=USB_RESULT_NOTREADY;
			break;
		default:  R=USB_RESULT_UNSUPPORT;
	}
	return R;
}
