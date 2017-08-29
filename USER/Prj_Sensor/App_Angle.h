/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _APP_ANGLE_H_
#define _APP_ANGLE_H_
#include <Sensor.h>
#ifdef   SENSOR_TYPE_ANGLE

#define ANGLE_CROSS_SIZE  2

typedef struct
{
	int32 ADC;
	float  Angle;
}ANGLE_CROSS_TYPE;

void Angle_Command(void *Tags);

#endif
#endif
