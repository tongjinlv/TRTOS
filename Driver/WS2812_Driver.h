/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
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
