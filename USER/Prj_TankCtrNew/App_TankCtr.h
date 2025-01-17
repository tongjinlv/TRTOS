/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _APP_TANKCTR_H_
#define _APP_TANKCTR_H_
#include <Include.h>
#include <AppConfig.h>
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
	OC_Start=1,//遥控启动
	OC_Stop=2,//遥控停止
	OC_UpDoorOpen=3,//上阀门开
	OC_UpDoorClose=4,//上阀门关
	OC_DownDoorOpen=5,//下阀门开
	OC_DownDoorClose=6,//下阀门关
	OC_TankPowerON=7,//罐子上电
	OC_TankPowerOFF=8,//罐子掉电
	OC_TankForward1=9,//前进一速
	OC_TankForward2=10,//前进二速
  OC_TankForward3=11,//前进三速
	OC_TankBack1=12,//后退一速
	OC_TankBack2=13,//后退二速
	OC_TankBack3=14,//后退三速
	OC_TankResetFrq=15,//复位变频器
	OC_TankLock=16,//急停
	OC_TankUnlock=17,//解除急停
	OC_Relieve=18,//强制解除
	OC_UnRelieve=19,//解除强制解除
	OC_HandReset=20,
	OC_TankForward1R=21,//前进一速
	OC_TankForward2R=22,//前进二速
  OC_TankForward3R=23,//前进三速
	OC_TankBack1R=24,//后退一速
	OC_TankBack2R=25,//后退二速
	OC_TankBack3R=26,//后退三速
	OC_TankForwardDot=27,//前进点动
	OC_TankBackDot=28,//后退点动
	OC_CtrDrain=29,//放料
}OperatingCommand;

enum 
{
	WSA_TankPowerOn=S0,//罐子上电
	WSA_SensorG1Ok=S1,//重量一
	WSA_SensorG2Ok=S2,//重量二
	WSA_SensorG3Ok=S3,//重量三
	WSA_SensorG4Ok=S4,//重量四
	WSA_SensorR1Ok=S5,//距离
	WSA_FastStop=S6,//急停
	WSA_SysPowerOn=S7,//系统上电
	WSA_SysError=S8,//系统故障变频器故障
	WSA_TapOpenRealy=S9,//阀门开到位
	WSA_TapCloseRealy=S10,//阀门关到位
	WSA_SealedInPlace=S11,//密封到位
	WSA_Relieve=S12,//强制解除
	WSA_Tank1Place=S13,//罐子1就位
	WSA_Tank2Place=S14,//罐子2就位
	WSA_BusRun=S15,//车子运行态
	WSA_TankPowerCheckRealy=S16,//罐控制电源就绪
  WSA_SensorIOTOK=S17,//IO采集CAN
	WSA_SensorTankOK=S18,//罐控制器
	WSA_DownLoadOver=S19,//下料完成
}WorkStatusALL;
typedef struct 
{
	uint32 AllStatus;//0
	uint16 ADC_Value[SENSOR_CH_SIZE];//1
	float  SensorValue[SENSOR_CH_SIZE];//2
	uint32 Host_Ctr_Data;//4
	uint32 Host_Sig_Data;//8
	uint16 AD6x[4];//12
	uint8 FullWeight;
	SENSOR_CROSS_TYPE CROSS_DATA[SENSOR_CROSS_SIZE][SENSOR_CH_SIZE];
}DevRun_ValueStruct;


typedef struct
{
	ConfigHeadStruct CHS;
	uint8 Addr;
	uint8 Cmd;
	uint8 WaterID;
	uint8 Note;
	float Distance;
	float Weight;
	uint32 AllStatus;
}RS485WriteStruct;
typedef struct
{
	ConfigHeadStruct CHS;
	uint8 Addr;
	uint8 Cmd;
	uint8 WaterID;
	uint8 Note;
	uint32 AllStatus;
}RS485ReadStruct;
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
