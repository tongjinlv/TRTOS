/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef HT1621_FACE_H_
#define HT1621_FACE_H_
#include <Include.h>
#include <AppConfig.h>
#include <Text.h>
#define CH_LENGTH 3
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
	WCB_PowerAlarm=S12,//������ʾ
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
	uint8 CallNumber[3][11];
	uint8 LoginHead[16];
	uint8 PrintfName[20];
	uint8 PrintfTitle[20];
	uint8 DomainName[2][16]; 
	uint16 ServerPort[2];
	uint32 WorkBit;
	uint8 DeBugCFG;
	uint8 SendCycle;
	uint8 RecordCycle;
	uint8 PrintfCycle;
	uint8 SendSMSDelay;
	float CorrectValue[CH_LENGTH];
	uint8 SleepMin;
	uint8 DeviceType;
}AppSaveValue;
typedef struct
{
	float CH_Value[CH_LENGTH];
	uint8 UnitFlag;//��λ��־
	uint32 RunFlag;//���б�־
	AppSaveValue SaveValue;
	Date_Time DateTime;
  uint16 ADC[1];
	uint8 RSSI;
	uint8 SIMType;
	uint8 UpgradePogress;
	uint8 SysWorkMode;
	uint8 RecordCount;
	float GPS_Longitude;
	float GPS_Latitude;
	uint8 SMSCenterNum[11];
	MaxMin CH_Hold[CH_LENGTH];
}UIShowStruct;
typedef enum
{
	ST_CHINA_MOBILE=S1,
	ST_CHINA_UNINET=S2,
}SIMType;
typedef enum
{
	HSF_LCelsiusF=BIT(1),//���϶ȨH
	HSF_LLight=BIT(2),//��
	HSF_LPercentage=BIT(3),//�ٷֺ�
	HSF_LCelsiusC=BIT(4),//��
	HSF_HPM2_5ppm=BIT(5),//pm2.5
	HSF_HCelsiusF=BIT(6),//���϶ȨH
	HSF_HCelsiusC=BIT(7),//��
}HtShowFlag;
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
	WRF_EXP_Connected=S11
}WorkRamFlag;
#endif

