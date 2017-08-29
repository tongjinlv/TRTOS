/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _STM32_CPU_H_
#define _STM32_CPU_H_
#include <Include.h>

#include <STM32LIB_Include.h>


typedef struct 
{
	uint8 GPIO_Speed;
	GPIOMode_TypeDef GPIO_Mode;
	GPIO_TypeDef *GPIOx;
	uint16 GPIO_Pin;
}GPIO_InitStruct;


void Standby_Init(BOOL Stop);
void GPIO_InitList(const GPIO_InitStruct *List);
void MCU_Reset(void);
void Remap_SWJ_JTAGDisable(void);
void IWDG_Configuration(void);
void Printf_SysInfor(void);
void IAP_ProgramHalfWord(uint32 Address, uint16 Data);
void IAP_ErasePage(uint32 Page_Address);
void IAP_Lock(void);
void IAP_Unlock(void);
uint8 GetCodeStr64(void *Buf);
#endif
