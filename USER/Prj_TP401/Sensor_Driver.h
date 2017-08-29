/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _SENSOR_H_
#define _SENSOR_H_
#include <Include.h>


typedef enum
{
    VT_End=0x00,//û���κ�����
    VT_Menu=0x01,//�˵���
    VT_Task=0x02,
    VT_Value=0x03,
    VT_Float=0x04,
    VT_Uint16=0x05,
    VT_Int8=0x06,
    VT_TaskF32=0x07,
    VT_ROMFloat=0x08,
    VT_ROMUint32=0x09,
    VT_ROMUint16=0x0a,
    VT_Uint8=0x0b,
    VT_ROMUint8=0x0c,
    VT_ROMStr=0x0d,
    VT_ROMInt8=0x0e,
    VT_ROMInt16=0x0f,
    VT_Uint16Bool=0x10,
    VT_EEPFloat=0x011,
    VT_EEPUint8=0x12,  
    VT_ROMEEPUint8=0x13,
    VT_EEPUint8Task=0x14,
		VT_PageAct=0x15,
		VT_TaskUint8=0x16,
		VT_Uint8Task=0x17,
		VT_BOOL=0x18,
		VT_Null=0x19,
		VT_Str=0x1a,
		VT_IP=0x1b,
		VT_Color=0x1c,
		VT_U32BIT=0x1d
}Value_Type;//��λΪС����λ��

typedef struct 
{
  const char *Option;
	void *Value;
  uint8 Type;
	uint8 Note;//�˵�����Note=�˵����
}COM_MenuStruct;

typedef enum
{
	
	SCFF_GetSensorTest=0,
	SCFF_GetSensorModel=1,//��ȡ�������ͺ�
	SCFF_GetSensorNumber=2,//��ȡ���������
	SCFF_GetSensorName=3,//��ȡ����������
	SCFF_GetSensorNote=4,//��ȡ��������ע
	SCFF_GetCPUModel=5,//��ȡcpu�ͺ�
	SCFF_GetHandVersion=6,//Ӳ���汾
	SCFF_GetSoftVersion=7,//����汾
	SCFF_GetSystemInfor=8,//ϵͳ��Ϣ
	SCFF_GetLibVersion=9,//��ȡ�̼���汾
	SCFF_GetProgTime=10,//��ȡ��¼ʱ��
	SCFF_GetFlashSize=11,//��ȡflash��С
	SCFF_SetCTRUINT32=21,//һ�������ü̵���
	SCFF_GetSIGUINT32=22,//��ȡ����IO
 	SCFF_ButtonClick=23,//��ť�¼�
	SCFF_SetWriteAddr=24,//д��дƫ�Ƶ�ַ
	SCFF_WriteBuffer=25,//д������
	SCFF_SetChnenel = 26,//д�����ͨ��
	SCFF_CorrectWeight=27,//У׼����
	SCFF_ClearWeight=28,//��������
	SCFF_CorrectRange=29,//У׼����
	SCFF_ClearRange=30,//�������
	SCFF_ButtonOver=31,//ֹͣ����ť
	SCFF_GetAllSensorValue=32,//��ȡ���д�����ֵ	
	SCFF_GetStructOffSet=33,//��ȡ�ṹ��ƫ��ֵ
	SCFF_SetStructOffSet=34,//���ýṹ��ƫ��ֵ
	SCFF_RefurBishGet=35,//��������
	SCFF_RefurBishSet=36,//�ϴ�����
	SCFF_SetSaveValue=37,//�������
	SCFF_TankSIGUINT32=38,//���ӷ��������ź�
	SCFF_TankSetCTRUINT32=39,//���Ӽ̵�������U32
	SCFF_RefurBishSet1=40,//�ϴ�����
	SCFF_GoToBootLoader=41,//��������ģʽ
	SCFF_GotoApplication=42,//���г���
	SCFF_Cheack1024Byte=43,//У��1024�ֽ�
	SCFF_Write1024Byte=44,//д��1024�ֽ�
	SCFF_Read64Byte=45,//д��64�ֽ�
	SCFF_Read1024Byte=46,//д��1024�ֽ�
	SCFF_EraseFlase=47,//����flash
	SCFF_SendCenterRoom=48,
	SCFF_SendSkyBus=49,
	SCFF_SetReadValue=50,//��ȡ�ָ�����
	SCFF_SetFullWeight=51,//���ö����
	SCFF_SetReg=52,//д�Ĵ���
	SCFF_SetAlarmList=53,//��������
	SCFF_GetAlarmList=54,//��������
	SCFF_SetIpPortList=55,//����IP�˿�
	SCFF_GetIpPortList=56,//����IP�˿�
	SCFF_SetCallList=57,//���õ绰�嵥
	SCFF_GetCallList=58,//��ȡ�绰�嵥
	SCFF_GetSensorADC=59,//��ȡ�Ƕ�ģ��ֵ
	SCFF_GetSensorValue=60,//��ȡ�Ƕ�ֵ
	SCFF_SetSensorMax=61,//У׼��Ƕ�
	SCFF_SetSensorMin=62,//У׼С�Ƕ�
	SCFF_InDeBug=63,//�������ģʽ
	SCFF_OutDeBug=64,//�˳�����ģʽ
	SCFF_GetCANGroup=65,//��ȡcanͨ����
	SCFF_GetCANStdId=66,//��ȡcanͨ�ų�Ա��ַ
	SCFF_SetCANGroup=67,//����canͨ����
	SCFF_SetCANStdId=68,//����canͨ�ų�Ա��ַ
	SCFF_SetCTRBIT=69,//���ü̵�����λ
	SCFF_ClrCTRBIT=70,//����̵�����λ
	SCFF_GetLoginHead=71,//��ȡ��½ͷ
	SCFF_SetLoginHead=72,//���õ�½ͷ
	SCFF_GetHeartBeat=73,//��ȡ������
	SCFF_SetHeartBeat=74,//����������
	SCFF_COMMenuList=75,//���ڲ˵�
	SCFF_SetDeBugMode=76,//���õ���ģʽ
	SCFF_SetDateTime=77,//����ʱ��
	SCFF_PrintHistory=78,//�����ʷ��¼
	SCFF_CleanHistory=79,//�����ʷ��¼
	SCFF_UpdateBootLoader=80,//����BOOT

}Sensor_Command_FrameFlag;


extern  char *String_Hello;
extern  char *String_Ok_ADC;
extern  char *String_Ok;
extern  char *String_Error;
extern  char *String_Wating;

#define SensorModel "TP500V2"
#define SensorHandVersion "V 2.10"
#define SensorSoftVersion "V 6.12"

#define SensorName "RTU-TP"
#define SensorDefNote "NB"
#endif
