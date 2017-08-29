/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _SENSOR_H_
#define _SENSOR_H_
#include <Include.h>


typedef enum
{
	
	SCFF_GetSensorTest=0,
	SCFF_GetSensorModel=1,//��ȡ�������ͺ�
	SCFF_GetSensorNumber=2,//��ȡ���������
	SCFF_GetSensorName=3,//��ȡ����������
	SCFF_GetSensorNote=4,//��ȡ��������ע
	SCFF_GetBSD=5,//��ȡ������Ϣ
	SCFF_GetCPUModel=6,//��ȡcpu�ͺ�
	SCFF_GetCPUID=7,//��ȡcpuID
	SCFF_GetCANSpeed=8,//��ȡCANͨ������
	SCFF_GetSensorADC=9,//��ȡ�Ƕ�ģ��ֵ
	SCFF_GetSensorValue=10,//��ȡ�Ƕ�ֵ
	SCFF_SetSensorMax=11,//У׼��Ƕ�
	SCFF_SetSensorMin=12,//У׼С�Ƕ�
	SCFF_InDeBug=13,//�������ģʽ
	SCFF_OutDeBug=14,//�˳�����ģʽ
	SCFF_GetCANGroup=15,//��ȡcanͨ����
	SCFF_GetCANStdId=16,//��ȡcanͨ�ų�Ա��ַ
	SCFF_SetCANGroup=17,//����canͨ����
	SCFF_SetCANStdId=18,//����canͨ�ų�Ա��ַ
	SCFF_SetCTRBIT=19,//���ü̵�����λ
	SCFF_ClrCTRBIT=20,//����̵�����λ
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
	SCFF_UpdateBootLoader=80,//����BOOT
}Sensor_Command_FrameFlag;


extern  char *String_Hello;
extern  char *String_Ok_ADC;
extern  char *String_Ok;
extern  char *String_Error;
extern  char *String_Wating;


#if  defined(BOARD_TANK_Ctr)
#define SensorModel "CX-5410"
#define SensorDefNumber "00000000"
#define SensorName "Remote Control Module"
#define SensorDefNote "-Upper"

#elif defined(BOARD_SENSOR)

	#ifdef SENSOR_TYPE_ANGLE
	#define SensorModel "SC-A-CAN/A-5V"
	#define SensorDefNumber "00000000"
	#define SensorName "Angle Sensor"
	#define SensorDefNote "NB"
	#endif
	#ifdef SENSOR_TYPE_COMPASS
	#include <App_Compass.h>
	#define SensorModel "SC-C-CAN/A-5V"
	#define SensorDefNumber "00000000"
	#define SensorName "Compass Sensor"
	#define SensorDefNote "NB"
	#endif
	#ifdef SENSOR_TYPE_0_20MV_TO_CAN
	#include <App_CAN_0_20mV.h>
	#define SensorModel "SC-G-CAN-5V"
	#define SensorDefNumber "00000000"
	#define SensorName "CAN 0-20mv Sensor"
	#define SensorDefNote "NB"
	#endif
	#ifdef SENSOR_TYPE_CXYG
	#define SensorModel "CX-YG-G"
	#define SensorDefNumber "00000000"
	#define SensorName "CAN 0-20mv Sensor"
	#define SensorDefNote "NB"
	#endif
	#else
	#define SensorModel "Null"
	#define SensorDefNumber "Null"
	#define SensorName "Null"
	#define SensorDefNote "Null"
	#endif

#endif
