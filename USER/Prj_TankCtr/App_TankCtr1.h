/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _APP_TANKCTR_H_
#define _APP_TANKCTR_H_
#include <Include.h>

#define SENSOR_CH_SIZE    2
#define SENSOR_CTR_COUNT  14
#define SENSOR_CROSS_SIZE 2


typedef struct
{
	uint16 ADC;
	float  Sensor;
}SENSOR_CROSS_TYPE;

enum 
{
	OC_Start=1,//ң������
	OC_Stop=2,//ң��ֹͣ
	OC_UpDoorOpen=3,//�Ϸ��ſ�
	OC_UpDoorClose=4,//�Ϸ��Ź�
	OC_DownDoorOpen=5,//�·��ſ�
	OC_DownDoorClose=6,//�·��Ź�
	OC_TankPowerON=7,//�����ϵ�
	OC_TankPowerOFF=8,//���ӵ���
	OC_TankForward1=9,//ǰ��һ��
	OC_TankForward2=10,//ǰ������
  OC_TankForward3=11,//ǰ������
	OC_TankBack1=12,//����һ��
	OC_TankBack2=13,//���˶���
	OC_TankBack3=14,//��������
	OC_TankResetFrq=15,//��λ��Ƶ��
	OC_TankLock=16,//��ͣ
	OC_TankUnlock=17,//�����ͣ
	OC_Relieve=18,//ǿ�ƽ��
	OC_UnRelieve=19,//���ǿ�ƽ��
	OC_HandReset=20,
	OC_TankForward1R=21,//ǰ��һ��
	OC_TankForward2R=22,//ǰ������
  OC_TankForward3R=23,//ǰ������
	OC_TankBack1R=24,//����һ��
	OC_TankBack2R=25,//���˶���
	OC_TankBack3R=26,//��������
}OperatingCommand;

enum 
{
	WSA_TankPowerOn=S0,//�����ϵ�
	WSA_SensorG1Ok=S1,//����һ
	WSA_SensorG2Ok=S2,//������
	WSA_SensorG3Ok=S3,//������
	WSA_SensorG4Ok=S4,//������
	WSA_SensorR1Ok=S5,//����
	WSA_FastStop=S6,//��ͣ
	WSA_SysPowerOn=S7,//ϵͳ�ϵ�
	WSA_SysError=S8,//ϵͳ����
	WSA_TapOpenRealy=S9,//���ſ���λ
	WSA_TapCloseRealy=S10,//���Źص�λ
	WSA_SealedInPlace=S11,//�ܷ⵽λ
	WSA_Relieve=S12,//ǿ�ƽ��
	WSA_Tank1Place=S13,//����1��λ
	WSA_Tank2Place=S14,//����2��λ
	WSA_IfTankRunDownTrue=S15,//��������������Ϊ��
	WSA_TankPowerCheckRealy=S16,//��������������Ϊ��
}WorkStatusALL;
typedef struct 
{
	uint32 AllStatus;//0
	uint16 ADC_Value[SENSOR_CH_SIZE];//1
	float  SensorValue[SENSOR_CH_SIZE];//2
	uint32 CTR_DATABIT;//4
	uint32 SIG_DATABIT;//8
	uint16 AD6x[4];//12
	uint8 ADCChnenel;
	SENSOR_CROSS_TYPE CROSS_DATA[SENSOR_CROSS_SIZE][SENSOR_CH_SIZE];
}DevRun_ValueStruct;
typedef struct
{
	uint32 AllStatus;
	uint32 SIG_Value;
	uint32 CTR_Value;
	uint16 MasterAddr;
}TankRun_ValueStruct;
extern DevRun_ValueStruct DevRun_Value;
extern TankRun_ValueStruct TankRun_Value;
void App_CtrButton(void *Tags);
void App_SetButtonDelay(uint8 i);
void Task_CanRead(void *Tags);

#endif
