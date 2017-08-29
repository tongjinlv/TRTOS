/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _CAN2_DRIVER_H_
#define _CAN2_DRIVER_H_

#include <include.h>

void _CAN1_GPIO_Init(void);
void _CAN1_Init(void);
void _CAN_SendMsg(uint8 *Buf,uint8 Length);
void _CAN2_NVIC_Init(void);

#endif

