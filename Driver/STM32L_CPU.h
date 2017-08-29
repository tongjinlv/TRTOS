/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _STM32_CPU_H_
#define _STM32_CPU_H_
#include <Include.h>

#include <STM32LIB_Include.h>

typedef enum
{ 
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDe;

typedef struct 
{
	GPIOSpeed_TypeDef GPIO_Speed;
	GPIOMode_TypeDe GPIO_Mode;
	GPIO_TypeDef *GPIOx;
	uint32_t GPIO_Pin;
}GPIO_ListStruct;

typedef struct 
{
	GPIO_TypeDef *GPIOx;
	uint32_t GPIO_Pin;  
	GPIOSpeed_TypeDef GPIO_Speed; 
	GPIOMode_TypeDef GPIO_Mode; 
	GPIOOType_TypeDef GPIO_OType;   
  GPIOPuPd_TypeDef GPIO_PuPd;
}GPIOL_ListStruct;

void Standby_Init(BOOL Stop);
void GPIO_InitList(const GPIO_ListStruct *List);
void MCU_Reset(void);
void Remap_SWJ_JTAGDisable(void);
void IWDG_Configuration(void);
#endif
