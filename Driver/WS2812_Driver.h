/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _WS2812_DRIVER_H_
#define _WS2812_DRIVER_H_
#include <Include.h>




void WS_WriteDot(GPIO_TypeDef *GPIOx,uint16_t Port,uint32 *Color);
void WS_SendList(uint32 *D);
void WS_Set(uint32 A,uint32 B,uint32 C,uint32 D);
void WS_SetDot(uint8 Index,uint32 C);
void WS_ShadeBit(uint32 c,uint32 C,uint8 Bit);
void WS_SetColorBit(uint32 C,uint8 Bit);
#endif
