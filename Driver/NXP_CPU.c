/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <DeBug.h>
#include <NXP_CPU.h>
#include "lpc177x_8x_systick.h"
/**************************************************************************************
 Func: 禁用JTAG仅适用SWD调试
 Time: 2015-9-02
 Ver.: V1.0
 Note;
**************************************************************************************/
void Remap_SWJ_JTAGDisable()
{

}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
	while(1)
	{	DeBug_Get();
		DeBug("ErrorFile%s->Line%d",file,line,Infor_Infor);
		Tos_TaskDelay(1000);
	}
}
#endif
/**************************************************************************************
 Func: 端口清单初始化
 Time: 2015-9-02
 Ver.: V1.0
 Note;
**************************************************************************************/

void SysTick_Set()
{
	SYSTICK_InternalInit(10);
	SYSTICK_IntCmd(ENABLE);
	SYSTICK_Cmd(ENABLE);
}
void BareDelay(uint32 i)
{
	uint32 m;
	while(i--)
	{
		m=72000000000/Tos_Cpu_Freq;
		while(m--);
	}
}
void Standby_Init()
{

	
}

void SysTick_Handler(void)
{

	SYSTICK_ClearCounterFlag();
	Tos_SysTick();

}
void Sys_Standby(void)
{  

}
//系统进入待机模式
void Sys_Enter_Standby(void)
{     

}
void MCU_Reset(void)
{
	__disable_fault_irq();      // STM32 软复位  
	NVIC_SystemReset();
}
void IAP_ProgramHalfWord(uint32 Address, uint16 Data)
{

}
void IAP_ErasePage(uint32 Page_Address)
{

}
void IAP_Lock()
{

}
void IAP_Unlock()
{

}

void IWDG_Configuration(void)
{

}
void IWDG_Reload()
{

}
