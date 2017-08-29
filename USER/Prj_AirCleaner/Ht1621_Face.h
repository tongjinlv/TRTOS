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
	WCB_Start=S0,
	WCB_Open=S1,
}WorkConfigBit;

typedef enum
{
	WSB_ExpAlarm=S0,//异常报警
	WSB_OpenAirCleaner=S1,//异常报警
	WSB_Ug=S2,//微克显示
	WSB_PM25=S3,//PM2.5
	WSB_API=S4,
}WorkShowBit;
typedef struct
{
	ConfigHeadStruct CH;

	uint32 WorkBit;
	uint8 DeBugCFG;
	uint8 BlowerNum;
	uint8 CleanNum;
	uint8 LampNum;
	uint8 DeviceType;
}AppSaveValue;
typedef struct
{
	uint32 ShowFlag;//单位标志
	uint32 RunFlag;//运行标志
	AppSaveValue SaveValue;
	Date_Time DateTime;
	uint8 SysWorkMode;
	uint8 SetSelect;
	uint8 RecordCount;
	uint16 PM25_Value;
	uint16 LostSetTime;
	uint8 GPRSFailCount;
	uint16 ADC[1];
}UIShowStruct;

#endif

