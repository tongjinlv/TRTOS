/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _IO_DRIVER_H_
#define _IO_DRIVER_H_
#include <Include.h>


#define LED1_ON     GPIO_ResetBits(GPIOB,GPIO_Pin_2)
#define LED1_OFF    GPIO_SetBits(GPIOB,GPIO_Pin_2) 
#define LED2_ON     GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define LED2_OFF    GPIO_SetBits(GPIOB,GPIO_Pin_10) 
#define LED3_ON     GPIO_ResetBits(GPIOB,GPIO_Pin_11)
#define LED3_OFF    GPIO_SetBits(GPIOB,GPIO_Pin_11) 

#define RS485_ON    GPIO_ResetBits(GPIOA,GPIO_Pin_8) 
#define RS485_OFF   GPIO_SetBits(GPIOA,GPIO_Pin_8) 

#define EN_ON     GPIO_ResetBits(GPIOA,GPIO_Pin_6)
#define EN_OFF    GPIO_SetBits(GPIOA,GPIO_Pin_6) 
#define DIR_ON    GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define DIR_OFF   GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define PUL_ON    GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define PUL_OFF   GPIO_SetBits(GPIOA,GPIO_Pin_4)


#define  MOTOR_EN(x)        (x?GPIO_SetBits(GPIOA, GPIO_Pin_6):GPIO_ResetBits(GPIOA, GPIO_Pin_6))
#define  MOTOR_DIR(x)       (x?GPIO_SetBits(GPIOA, GPIO_Pin_5):GPIO_ResetBits(GPIOA, GPIO_Pin_5))
#define  MOTOR_PLUSE(x)     (x?GPIO_SetBits(GPIOA, GPIO_Pin_4):GPIO_ResetBits(GPIOA, GPIO_Pin_4))    

void DeviceMount_Control(void);
void DeviceMount_Signel(void);
void KC_EXTI_Init(void);
void DeviceMount_CodeKey(void);
void Tos_TaskGetKeyCode(void);

#endif
