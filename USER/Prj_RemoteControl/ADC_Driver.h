/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _ADCLOCAL_DRIVER_H_
#define _ADCLOCAL_DRIVER_H_
#include <Include.h>


#define ADC_CHN 3
#define ADC_BUFSize  10 
extern uint16 ADCBuffer[3];
extern volatile uint16  ADC_Value[ADC_BUFSize][ADC_CHN]; 

void Task_ADCFitel(void *Tags);

#endif

