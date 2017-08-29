/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _ADCFORTANKHAND_DRIVER_H_
#define _ADCFORTANKHAND_DRIVER_H_
#include <Include.h>

#define TANKHAND_ADC_CHN 3
#define TANKHAND_ADC_BUFSize  10 
extern volatile uint16  TANKHAND_ADC_Value[TANKHAND_ADC_BUFSize][TANKHAND_ADC_CHN]; 
void ADCForTankHand_Init(void);
uint16 ADCForTankHand_ReadFitel(uint8 CH);
void Task_ADCFitel(void *Tags);

#endif

