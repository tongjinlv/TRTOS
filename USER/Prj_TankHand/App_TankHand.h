/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _APP_TANKHAND_H_
#define _APP_TANKHAND_H_
#include <Include.h>
#include <..\USER\Prj_TankHand\Oled_GUI.h>

typedef struct
{
	uint8 Brightness;//����
	uint8 TimeSleep;//˯��ʱ�䣨���ӣ�
	uint8 TankAddr;
	uint8 BusAddr;
	uint8 CenterAddr;
	float PassWord;
	uint8 PassKey;
	int LicCount;
	uint8 Null;//�������ֽ�����
}App_SaveValue;
typedef enum
{
	HWM_Stop=0,
	HWM_Set=1,
	HWM_ChargeIn=2,
	HWM_ChargeOut=3,
	HWM_Runing=4,
}HandWorkMode;
typedef struct 
{
	float Voltage;//��ѹ
	float Pot1Weight;//����1����
	float Pot2Weight;//����2����
	int8 HandSpeedX;//�ֱ��ٶ�X��//���λ��������
	int8 HandSpeedY;//�ֱ��ٶ�Y��//���λ��������
	App_SaveValue SValue;//�������
	uint8 SaveOffSet;
	uint32 LAMPDAT;
	char *LicStatus;
	HandWorkMode WorkFlag;
	uint8 LinkCount;
	uint8 HeartBeat;
	uint8 *Status;
}App_RunValue;

extern const OLED_MenuStruct MenuHome[8];
extern const OLED_MenuStruct Menu0x1000[7];
extern const OLED_MenuStruct Menu0x1100[7];
extern const OLED_MenuStruct Menu0x1300[7];

extern App_RunValue Run_Value;
extern void TestFunc(void);
extern void Draw_Home(void);
extern void TaskFor_Oled(void *Tags);
extern void TaskFor_Work(void *Tags);
void TaskFor_SetWork(void *Tags);
BOOL Send_Command(uint8 Com,uint8 Count,BOOL ErrorShowTrue);

#endif
