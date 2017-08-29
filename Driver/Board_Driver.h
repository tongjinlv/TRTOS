/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _BOARD_DRIVER_H_
#define _BOARD_DRIVER_H_

#include <Include.h>



void Sys_Standby(void);
void BareDelay(uint32 i);
void MCU_Reset(void);
void Sys_Enter_Standby(void);

void assert_failed(uint8_t* file, uint32_t line);
void Remap_SWJ_JTAGDisable(void);
void GPIO_InitList(const GPIO_InitStruct *List);
void IWDG_Configuration(void);
void IWDG_Reload(void);
void Standby_Init(void);
void SysTick_Set(void);
void IAP_ProgramHalfWord(uint32 Address, uint16 Data);
void IAP_ErasePage(uint32 Page_Address);
void IAP_Lock(void);
#endif
