/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef __B_LUX_V20_H
#define __B_LUX_V20_H
#include <Include.h>
#include <STM32_CPU.h>


//引脚定义



#define	B_LUX_Addr	  0x46 //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改

void IIC_WriteCmd(const GPIO_InitStruct *Pin_Maps,uint8 REG_Address);
uint32 IIC_Reads(const GPIO_InitStruct *Pin_Maps);
void B_LUX_Init(const GPIO_InitStruct *List);
uint32 B_LUX_GetLux(const GPIO_InitStruct *List);

#endif
