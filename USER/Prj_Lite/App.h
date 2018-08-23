/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _APP_H_
#define _APP_H_
#include <Include.h>
#include <..\USER\Prj_Insect\MPU6050_Driver.h>
#include <WS2812_Driver.h>

typedef struct
{
	ConfigHeadStruct CH;
	uint8 RunMode;
	uint8 RunSpend;
}AppSaveValue;
typedef struct
{
	AppSaveValue SaveValue;
	uint32 RunFlag;
	uint16 ADC[8];
	GYRODataStruct Gyro;
	uint32 WSReg[4];//�ĸ�RGB�ƵļĴ���
	uint8 KeyValue;
	float TempValue;
	float HumidityValue;
}UIShowStruct;

extern UIShowStruct UIShowValue;

void CreateTask(void(*vfFuncPointer)(void *Tags));
void RandomLight(uint32 A,uint32 B);
int RandomADC(int Max,int Min);
void RandomEYE(void);
#endif
