/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef HT1621_FACE_H_
#define HT1621_FACE_H_
#include <Include.h>
#include <AppConfig.h>
#include <Text.h>
#define CH_LENGTH 3
typedef enum
{
	WCB_ConnectIp1EN=S1,//连接ip1使能
	WCB_ConnectIp2EN=S2,//连接Ip2使能
	WCB_SendMsgNum1EN=S3,//发送短信到号码1使能
	WCB_SendMsgNum2EN=S4,//发送短信到号码2使能
	WCB_MQTTEN=S5,
	WCB_DTH11=S6,
	WCB_RecordEN=S7,//打印记录使能
	WCB_Update=S8,//时间更新
	WCB_RingAlarm=S9,//电话报警
	WCB_HistoryRecord=S10,//历史记录功能
	WCB_SleepShow=S11,//休眠显示
	WCB_PowerAlarm=S12,//休眠显示
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
	uint8 UnitFlag;//单位标志
	uint32 RunFlag;//运行标志
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
	HSF_LCelsiusF=BIT(1),//华氏度℉
	HSF_LLight=BIT(2),//灯
	HSF_LPercentage=BIT(3),//百分号
	HSF_LCelsiusC=BIT(4),//℃
	HSF_HPM2_5ppm=BIT(5),//pm2.5
	HSF_HCelsiusF=BIT(6),//华氏度℉
	HSF_HCelsiusC=BIT(7),//℃
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

