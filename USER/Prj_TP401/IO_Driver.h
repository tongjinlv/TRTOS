/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _IO_DRIVER_H_
#define _IO_DRIVER_H_
#include <Include.h>


#define LED1_ON     GPIO_ResetBits(GPIOB,GPIO_Pin_2)
#define LED1_OFF    GPIO_SetBits(GPIOB,GPIO_Pin_2) 

#define LED2_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define LED2_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_12)


#define BEEP_OFF    GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define BEEP_ON   GPIO_SetBits(GPIOB,GPIO_Pin_0)

#define E3V3_ON    GPIO_ResetBits(GPIOC,GPIO_Pin_9)
#define E3V3_OFF   GPIO_SetBits(GPIOC,GPIO_Pin_9)

#define GPRS_ON    GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define GPRS_OFF   GPIO_SetBits(GPIOC,GPIO_Pin_8)

#define GPS_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define GPS_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_1)

#define PWKEY_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define PWKEY_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define WKUP      GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define GPRS_VDDEXT GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)

void DeviceMount_IO(const GPIO_InitStruct *List);
void KC_EXTI_Init(void);
void DeviceMount_CodeKey(void);
void Tos_TaskGetKeyCode(void);

#endif
