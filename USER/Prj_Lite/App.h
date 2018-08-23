/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
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
	uint32 WSReg[4];//四个RGB灯的寄存器
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
