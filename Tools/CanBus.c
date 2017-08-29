/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <include.h>
#include <Tools_Include.h>
#include <Driver_Include.h>
#include <CanBus.h>
uint8 CANBUS_CFG_OffSet=FlashConfigNull;
CanBus_RxMessage CBRM_Msg[CAN_DeviceTotal];
CANBUS_DataInfor CBDataI[CAN_DataPoolTotal];
CanBus_DevInfor CBDevI;//Э��ջ������Ϣ
f32 TestValue=14.332;
/************************************************************* 
*��ַ����   �������������� ʹ�û���ID    ������ӻ�����ʹ����չID
*����ͨ������֡��ӻ��������ݴ��䣬ͨ��Զ��֡��ӻ�����Σ�ղ���
*�������˵�ַ�Ĵӻ����ϵ�󣬰�һ��ʱ���������������������������Լ��Ѿ��������ˣ������������������ط�goworkָ������ӻ����빤��״̬
*�������ӻ��������ݣ����ݵ�ַ�����ӻ���㲥��ַ���ӻ���������������ʱ����ַ��ȴ��Ҫ���Լ���ַ
��������  0xxxxx  0x0003   
�ӻ�����  0x0001~0xfffe   0x0003
*�������ݽӿ�     �����ṩ���ݶ����ӿ�Ϊ�ӻ��ṩ���ã�д��ӿ��������մ�Ŵӻ���������ʵʱ���� ������ʵʱ����  ��������ʹ����һ�����ݺ�Ը�����λ�ý�������
*�ӻ����ݽӿ�     �ӻ��ṩ�����ݶ����ӿڹ��������з���  �����а��� �������ɼ����ݻ��߱��ز���     д��ӿڰ���һЩ���Ʋ��������ָ��
*������չ���ְ���   �����������������ֱ�ӵĴ������� ��Щ�ӿڶ�����������������  
*************************************************************/

/*************************************************************
Func: ��ȡCANBUS��ͨ�ŵ�ַ
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  
*************************************************************/
void Load_CanBus_Addr()
{
	FLASH_ReadDatas(CANBUS_CFG_OffSet,&CBDevI.Addr,1);
}
/*************************************************************
Func: �������ݹ��ⲿ��������
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  
*************************************************************/
void Save_CanBus_Addr()
{
	FLASH_WriteDatas(CANBUS_CFG_OffSet,&CBDevI.Addr,1);
}

/*************************************************************
Func: �������ݹ��ⲿ��������
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  
*************************************************************/
void CANBUS_CBDataI_Init()
{
	uint16 i;
	for(i=0;i<CAN_DataPoolTotal;i++)
		{
			CBDataI[i].DataType=CBDT_NullData;
			CBDataI[i].Data_P=0;
		}
		CBDevI.CBDataI_Size=0;
}
/*************************************************************
Func: �������ݹ��ⲿ��������
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  
*************************************************************/
void CANBUS_JoinVoidValue(uintbus Data,CanBus_DataType Type)
{
	CBDataI[CBDevI.CBDataI_Size].DataType=Type;
	CBDataI[CBDevI.CBDataI_Size++].Data_P=Data;
}

/*************************************************************
Func: CANBUSЭ��ջ����
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  
*************************************************************/
void CANBUS_Create(BOOL HostTrue)
{
	FlashGetConfigRoom(&CANBUS_CFG_OffSet,1);//��ȡ���ã����ô�С1��uint16����
	CBDevI.HostTrue=HostTrue;
}
/*************************************************************
Func: CANBUSЭ��ջ����
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  
*************************************************************/
void CANBUS_Start()
{
	Load_CanBus_Addr();
	CAN1_Init();
	CAN1_Filter_Configs(CBDevI.Addr,CBDevI.HostTrue);
	CBDevI.WorkTrue=True;
}
/*************************************************************
Func: ����CANBUSЭ��ջ
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  �����˲������ַ������Ҫ��������
*************************************************************/
void CANBUS_ReStart()
{
	Load_CanBus_Addr();
	CAN1_Filter_Configs(CBDevI.Addr,CBDevI.HostTrue);
	CBDevI.WorkTrue=True;
}
/*************************************************************
Func: �������ӻ�����Ϣ
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  �Է�����ַ  �����ݰ�
*************************************************************/
BOOL CANBUS_SendMsg(uint16 Addr,CanBus_TxMessage *CBTM)
{
	uint16 TransmitMailbox=0,i=0;
	CanTxMsg  TxMessage;
	TxMessage.ExtId=Addr<<13;
	TxMessage.RTR=CAN_RTR_DATA;//��������֡
	TxMessage.IDE=CAN_ID_EXT;
	TxMessage.DLC=sizeof(CanBus_TxMessage);
	BufferCoppy(CBTM,&TxMessage.Data[0],sizeof(CanBus_TxMessage));
	TransmitMailbox=CAN_Transmit(CAN1,&TxMessage);
	while((CAN_TransmitStatus(CAN1,TransmitMailbox)!=CANTXOK)&&(i!=0xff)) 
	{
	i++;
		Tos_TaskDelay(1);
	}
	if(i==0xff)return False;
	else return True;
}

/*************************************************************
Func: ���豸��ַȫ�����
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  ���ȫ���豸��Ч
*************************************************************/
BOOL CANBUS_TXD_DeviceReset(uint16 Addr)
{
	BOOL R;
	CanBus_TxMessage CBTM;
	CBTM.Addr=Addr;
	CBTM.Order=CBO_DeviceReset;//�ָ�ָ��
	R=CANBUS_SendMsg(CanBus_Broadcast,&CBTM);
	return R;
}
/*************************************************************
Func: ���豸��ַȫ�����
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  ���ȫ���豸��Ч
*************************************************************/
void CANBUS_RXD_DeviceReset()
{
	CBDevI.Addr=CanBus_Broadcast;
	Save_CanBus_Addr();
	CANBUS_ReStart();
#ifdef COMPILE_MODE_DEBUG
	DeBug("Device Reset Default",Infor_Infor);
#endif
}
/*************************************************************
Func: Ϊ�豸���õ�ַ���Ѿ����úõĵ�ֱַ�Ӻ���
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note: �õ�ַ��Ϊ�豸����ĵ�ַ
*************************************************************/
BOOL CANBUS_TXD_DeviceSetAddr(uint16 Addr)
{
	BOOL R;
	CanBus_TxMessage CBTM;
	CBTM.Addr=CanBus_Broadcast;//ͨ���㲥��ַ�������õ�ַָ��
	CBTM.Order=CBO_DeviceSetAddr;
	CBTM.DataType=CBDT_Uint16Data;
	CBTM.Data[0]=Addr>>8;
	CBTM.Data[1]=Addr&0xff;
	R=CANBUS_SendMsg(CanBus_Broadcast,&CBTM);//���㲥��ַд
	return R;
}
/*************************************************************
Func: Ϊ�豸���õ�ַ���Ѿ����úõĵ�ֱַ�Ӻ���
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note: �õ�ַ��Ϊ�豸����ĵ�ַ
*************************************************************/
void CANBUS_RXD_DeviceSetAddr(CanBus_TxMessage *CBTM)
{
	Load_CanBus_Addr();
	if(CBDevI.Addr==CanBus_Broadcast)
	{
		CBDevI.Addr=CBTM->Data[0];
		CBDevI.Addr<<=8;
		CBDevI.Addr|=CBTM->Data[1];
		Save_CanBus_Addr();
		CANBUS_ReStart();
	}
}
/*************************************************************
Func: ����ָ���豸
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  AddrΪ�豸��ַ
*************************************************************/
BOOL CANBUS_TXD_DeviceStartWork(uint16 Addr)
{
	BOOL R;
	CanBus_TxMessage CBTM;
	CBTM.Addr=Addr;//ͨ���㲥��ַ�������õ�ַָ��
	CBTM.Order=CBO_DeviceStartWork;
	R=CANBUS_SendMsg(Addr,&CBTM);
	return R;
}
/*************************************************************
Func: ָֹͣ���豸
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  
*************************************************************/
BOOL CANBUS_TXD_DeviceStopWork(uint16 Addr)
{
	BOOL R;
	CanBus_TxMessage CBTM;
	CBTM.Addr=Addr;//ͨ���㲥��ַ�������õ�ַָ�� 
	CBTM.Order=CBO_DeviceStopWork;
	R=CANBUS_SendMsg(Addr,&CBTM);
	return R;
}
/*************************************************************
Func: ��ָ���ĵ�ַ����32λ��������
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  
*************************************************************/
BOOL CANBUS_TXD_DeviceSetU32Data(uint16 Addr,uint32 Data)
{
	BOOL R;
	CanBus_TxMessage CBTM;
	CBTM.Addr=Addr;
	CBTM.Order=CBO_DeviceSetData;
	CBTM.DataType=CBDT_Uint32Data;
	D32ToArray(&CBTM.Data[0],Data,0);
	R=CANBUS_SendMsg(Addr,&CBTM);
	return R;
}
/*************************************************************
Func: ����ָ�����ͷ������ݵ�ָ����ַ
Date:  2014-10-11
http://www.trtos.com/
By:ͯ����
Note:  
*************************************************************/
BOOL CANBUS_TXD_DeviceSetData(uint16 Addr,CanBus_DataType CBDT,uintbus Data)
{
	BOOL R;
	CanBus_TxMessage CBTM;
	CBTM.Addr=Addr;
	CBTM.Order=CBO_DeviceSetData;
	CBTM.DataType=CBDT;
	BufferCoppy((void *)Data,&CBTM.Data[0],4);
	R=CANBUS_SendMsg(Addr,&CBTM);
	return R;
}
BOOL CANBUS_RXD_DeviceSetData(CanBus_TxMessage *CBTM)
{
	BOOL R;
	uint8 i;
	BufferCoppy(&CBTM->Data[0],&i,2);
	if(i<CBDevI.CBDataI_Size)
	{
		if(CBTM->DataType==CBDataI[i].DataType)
		{
		BufferCoppy((void *)&CBTM->Data[0],(void *)CBDataI[i].Data_P,4);
		}else return False;
	}
	return R;
}
BOOL CANBUS_TXD_Object(uint16 Addr,CanBus_Order Order,CanBus_DataType CBDT,uintbus Data)
{
	BOOL R;
	CanBus_TxMessage CBTM;
	CBTM.Addr=Addr;
	CBTM.Order=Order;
	CBTM.DataType=CBDT;
	BufferCoppy((void *)Data,&CBTM.Data[0],4);
	R=CANBUS_SendMsg(Addr,&CBTM);
	return R;
}
BOOL CANBUS_TXD_DeviceGetData(uint16 Addr,uint16 Index)
{
	BOOL R;
	R=CANBUS_TXD_Object(Addr,CBO_DeviceGetData,CBDT_Uint16Data,(uintbus)&Index);
	return R;
}
