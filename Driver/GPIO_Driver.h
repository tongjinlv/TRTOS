/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _GPIO_DRIVER_H_
#define _GPIO_DRIVER_H_
#include <Include.h>
#include <STM32_CPU.h>
void DeviceMount_GPIO(const GPIO_InitStruct *List);
void GPIO_Set(const GPIO_InitStruct List,uint8 H);
BOOL GPIO_Get(const GPIO_InitStruct List);
void GPIO_SetIndex(uint8 i,uint8 H);
void GPIO_SetAll(uint32 D);
BOOL GPIO_Get(const GPIO_InitStruct List);
uint32 GPIO_GetAll(void);
BOOL GPIO_GetIndex(uint8 i);
void GPIO_Set_Mode(const GPIO_InitStruct Pin_Map,GPIOMode_TypeDef Mode);
void TIM1_Config(uint16 i);
void TIM1_SetPin(uint8 i,uint16 t);
#endif
