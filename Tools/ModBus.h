/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/

#ifndef _MODBUS_H_
#define _MODBUS_H_

#include <Include.h>

#define ModBus_StartFlag 0x7e
#define ModBus_EndFlag   0x7f

#define ModBus_Broadcast 0xff


typedef enum
{
	ModBus_Ok=0,
	ModBus_SizeError=1,//���ݳ��ȴ���
	ModBus_CheakError=2,//У�鲻ͨ��
	ModBus_MsgError=3,//δ֪����
	ModBus_DataOver=4, //�������ݲ�����
	ModBus_FlagError=5,//��ʼ������־����
	ModBus_AddrError=6,//��ַ����
	ModBus_Broad=6,//Ϊ�㲥��Ϣ����Ȼ�㲥��Ϣ�϶�����Ч��������
}ModBus_Status;
typedef enum
{
	MBCM_Crc=1,
	MBCM_Xor=2
}ModBus_CheackMode;
typedef enum
{
	WorkMode_Master=0,//����ģʽ
	WorkMode_Slave=1,//�ӻ�ģʽ
}MasterSlaveMode;
typedef struct
{
   uint8 StartFlag;//��ʼ��ʶ�����ܽ������ݸı䣩  
   uint8 MasterAddr;//�豸��ַ�����ܽ������ݸı�)
   uint8 SlaveAddr;//������ַ(���ܽ������ݸı�)
   uint8 MsgFlag;//��Ϣ��ʶ
   uint8 MsgNum;//��Ϣ��ˮ�ţ�ͨ�����)
   uint16 MsgLength;//��Ϣ����
   uint8 DataFlag;//���ݱ�ʶ
   uint16 DataLength;//���ݳ���
   uint8 EndFlag;//���ݰ������������ܽ������ݸı�)
	 uint8 CheakMode;//��������(���ܽ������ݸı�)
	 uint8 ErrorFlag;//���ݴ�����λ��
	 uint8 WorkMode;//modbusЭ�鹤��ģʽ
}ModBus_Message;
BOOL MyCom_CheckCrc(uint8 *Buf);
uint16 MyCom_AppendCrc(uint8 *Buf,uint16 Length);
uint8 MyCom_SendMsg(uint8 *Buf,uint16 OnlyAddr,uint8 Cmd,uint8 *Data,uint8 DataLegnth);
uint16 Load_ModBus_Addr(void);
void Save_ModBus_Addr(uint16 Addr);
void ModBus_Create(ModBus_Message *ModBusMsg,uint8 MasterAddr,uint8 SlaveAddr,MasterSlaveMode WorkMode,uint8 CheakMode);
uint16 ModBus_CreateMsg(string Buf,ModBus_Message *ModBusMsg,uint8 MsgFlag,uint8 MsgNum,uint8 DataFlag,uint8 *Data,uint16 DataLength);
uint16 ModBus_Expend(string Buf,uint16 Length,ModBus_Message *ModBusMsg);
void ModBus_Clear(ModBus_Message *ModBusMsg);

#endif
