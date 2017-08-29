/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _ADC_DRIVER_H_
#define _ADC_DRIVER_H_

#include <Include.h>

extern __IO uint16 ADC1_ConvertedValue;
void ADC1_Init(uintbus Addr);

#endif
