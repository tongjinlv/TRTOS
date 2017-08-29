/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _IO_DRIVER_H_
#define _IO_DRIVER_H_
#include <Include.h>


#define LED1_ON     GPIO_ResetBits(GPIOC,GPIO_Pin_0)
#define LED1_OFF    GPIO_SetBits(GPIOC,GPIO_Pin_0) 

#define LED2_ON     GPIO_ResetBits(GPIOC,GPIO_Pin_1)
#define LED2_OFF    GPIO_SetBits(GPIOC,GPIO_Pin_1) 

#define LED3_ON     GPIO_ResetBits(GPIOC,GPIO_Pin_2)
#define LED3_OFF    GPIO_SetBits(GPIOC,GPIO_Pin_2) 

#define LED4_ON     GPIO_ResetBits(GPIOC,GPIO_Pin_3)
#define LED4_OFF    GPIO_SetBits(GPIOC,GPIO_Pin_3) 

#define LED5_ON     GPIO_ResetBits(GPIOA,GPIO_Pin_15)
#define LED5_OFF    GPIO_SetBits(GPIOA,GPIO_Pin_15) 
void DeviceMount_Control(void);
void DeviceMount_Signel(void);
void KC_EXTI_Init(void);
void DeviceMount_CodeKey(void);
void Tos_TaskGetKeyCode(void);

#endif
