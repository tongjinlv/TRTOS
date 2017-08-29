/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _GPIO_DRIVER_H_
#define _GPIO_DRIVER_H_
#include <Include.h>
#include <STM32L_CPU.h>
void DeviceMount_GPIO(const GPIO_ListStruct *List);
void GPIO_Set(const GPIO_ListStruct List,uint8 H);
BOOL GPIO_Get(const GPIO_ListStruct List);
void GPIO_SetIndex(uint8 i,uint8 H);
void GPIO_SetAll(uint32 D);
BOOL GPIO_Get(const GPIO_ListStruct List);
uint32 GPIO_GetAll(void);
BOOL GPIO_GetIndex(uint8 i);
void GPIO_Set_Mode(const GPIO_ListStruct Pin_Map,GPIOMode_TypeDef Mode);

#endif
