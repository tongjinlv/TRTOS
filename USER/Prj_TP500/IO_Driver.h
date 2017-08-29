/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _IO_DRIVER_H_
#define _IO_DRIVER_H_
#include <Include.h>


#define LED1_ON     GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define LED1_OFF    GPIO_SetBits(GPIOB,GPIO_Pin_6) 

#define LED2_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define LED2_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define LED3_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define LED3_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_0)

#define BEEP_OFF    GPIO_ResetBits(GPIOC,GPIO_Pin_3)
#define BEEP_ON   GPIO_SetBits(GPIOC,GPIO_Pin_3)

typedef enum
{
	Key_Printf=0x01,
	Key_UpDown=0x02,
}KeyCode;
void DeviceMount_Control(void);
void DeviceMount_Signel(void);
void KC_EXTI_Init(void);
void DeviceMount_CodeKey(void);
void Tos_TaskGetKeyCode(void);

#endif
