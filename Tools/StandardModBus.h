/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _STANDARDMODBUS_H_
#define _STANDARDMODBUS_H_
#include <Include.h>
#include <Tools_Include.h>
/*
127~~~~~~~110~~~~~~~~~100~~~~~~~~72~~~~~~~~~65~~~~~~~~~~1
  ����������   �û���      ������    �û���				������
*/

typedef enum
{
	MBCC_ReadBits=0x01,//��������ɢֵ
	MBCC_ReadDisValue=0x02,//��������ɢֵ
	MBCC_ReadHoldReg=0x03,//��ȡ���ּĴ���ֵ
	MBCC_ReadInPutReg=0x04,//������Ĵ���
	MBCC_WriteBit=0x05,//д������Ȧ 0XFF00=1  0X0000=0
	MBCC_WriteByte=0x06,//д�����Ĵ���
	MBCC_WriteBytes=0x10,//д����Ĵ���
	MBCC_WRBytes=0x17,//��д����Ĵ���
	MBCC_WriteShield=0x16,//����д�Ĵ���
	MBCC_ReadFileRcord=0x14,//���ļ���¼
	MBCC_WriteFileRcord=0x15,//д�ļ���¼
	MBCC_ReadDevIDInfor=0x2B,//���豸ʶ����
}ModBusCmdCode;

typedef enum
{
	MBEC_NotError=0x00,
	MBEC_CmdCodeError=0x01,
	MBEC_DataLenthError=0x02,
	MBEC_CrcCheckError =0x03,
	MBEC_RegRangeError=0x04,
}ModBusErrorCode;


typedef enum
{
	MBWM_BroadCastEN=S0,//����㲥
	
}ModBusWorkMode;

typedef struct
{
	uint8 LoclAddr;//���ص�ַ
	uint8 WorkMode;//����ģʽ
	uint8 *RxBuf;
	uint16 RxBuf_Length;
	uint8 *TxBuf;
	uint16 TxBuf_Length;
	void *RunValue;//��������ַ
	uint16 RunValue_Length;
	void *CfgValue;//��������ַ
	uint16 CfgValue_Length;
	
}ModBus_Base;

typedef struct
{
	ModBus_Base *BaseInfor;//Э��������Ϣ
	uint8 CmdCode;//������
	
}ModBus_Infor;

#define MB_BroadCast 0xff





uint16 MB_AppendCrc(uint8 *Buf,uint16 Length);
BOOL MB_CheckCrc(uint8 *Buf,uint16 Length);



#endif
