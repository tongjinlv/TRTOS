/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef HT1621_FACE_H_
#define HT1621_FACE_H_
#include <Include.h>
#include <AppConfig.h>
#include <Text.h>
#define CH_LENGTH 6
typedef enum
{
	WCB_ConnectIp1EN=S1,//����ip1ʹ��
	WCB_ConnectIp2EN=S2,//����Ip2ʹ��
	WCB_SendMsgNum1EN=S3,//���Ͷ��ŵ�����1ʹ��
	WCB_SendMsgNum2EN=S4,//���Ͷ��ŵ�����2ʹ��
	WCB_MQTTEN=S5,
	WCB_DTH11=S6,
	WCB_RecordEN=S7,//��ӡ��¼ʹ��
	WCB_Update=S8,//ʱ�����
	WCB_RingAlarm=S9,//�绰����
	WCB_HistoryRecord=S10,//��ʷ��¼����
	WCB_SleepShow=S11,//������ʾ
}WorkConfigBit;
typedef struct
{
	float Max;
	float Min;
}MaxMin;
typedef struct
{
	ConfigHeadStruct CH;
	MaxMin CH_Limit[CH_LENGTH];
	uint16 ServerPort[2];
	uint32 WorkBit;
	uint8 DeBugCFG;
	uint8 SendCycle;
	uint8 RecordCycle;
	uint8 PrintfCycle;
	float CorrectValue[CH_LENGTH];
	uint8 SleepMin;
	uint8 DeviceType;
}AppSaveValue;
typedef struct
{
	float CH_Value[CH_LENGTH+1];//���һ����ص�ѹ
	uint8 UnitFlag;//��λ��־
	uint32 RunFlag;//���б�־
	AppSaveValue SaveValue;
	Date_Time DateTime;
	uint8 CurWay;//��ǰ��ʾ·��
	uint8 CountWay;//��ǰ��ʾ·��
  uint16 ADC[3];
	uint8 RSSI;
	uint8 SIMType;
	uint8 UpgradePogress;
	uint8 SysWorkMode;
	uint8 RecordCount;
	MaxMin CH_Hold[CH_LENGTH];
}UIShowStruct;


typedef enum
{
	WRF_CH1Max=S0,
	WRF_CH1Min=S1,
	WRF_CH2Max=S2,
	WRF_CH2Min=S3,
	WRF_GPRS_Connected=S4,
	WRF_SIMConnected=S5,
	WRF_BeepDisable=S6,
	WRF_GPS_Connected=S7,
	WRF_SensorCH1Connected=S8,
	WRF_SensorCH2Connected=S9,
	WRF_USB_Connected=S10,
	WRF_EXP_Connected=S11,
	WRF_SensorCH3Connected=S12,
}WorkRamFlag;
#endif

