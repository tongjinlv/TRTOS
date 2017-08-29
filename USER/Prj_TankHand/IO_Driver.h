/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _IO_DRIVER_H_
#define _IO_DRIVER_H_
#include <Include.h>

#define LAMP1_ON  GPIO_ResetBits(GPIOD,GPIO_Pin_10)
#define LAMP1_OFF GPIO_SetBits(GPIOD,GPIO_Pin_10) 
#define LAMP2_ON  GPIO_ResetBits(GPIOD,GPIO_Pin_11) 
#define LAMP2_OFF GPIO_SetBits(GPIOD,GPIO_Pin_11) 
#define LAMP3_ON  GPIO_ResetBits(GPIOD,GPIO_Pin_12) 
#define LAMP3_OFF GPIO_SetBits(GPIOD,GPIO_Pin_12) 
#define LAMP4_ON  GPIO_ResetBits(GPIOD,GPIO_Pin_13) 
#define LAMP4_OFF GPIO_SetBits(GPIOD,GPIO_Pin_13) 
#define LAMP5_ON  GPIO_ResetBits(GPIOD,GPIO_Pin_14) 
#define LAMP5_OFF GPIO_SetBits(GPIOD,GPIO_Pin_14) 
#define LAMP6_ON  GPIO_ResetBits(GPIOD,GPIO_Pin_15) 
#define LAMP6_OFF GPIO_SetBits(GPIOD,GPIO_Pin_15) 
#define LAMP7_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_6) 
#define LAMP7_OFF GPIO_SetBits(GPIOC,GPIO_Pin_6) 
#define LAMP8_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_7) 
#define LAMP8_OFF GPIO_SetBits(GPIOC,GPIO_Pin_7) 

#define LAMP9_ON  GPIO_ResetBits(GPIOE,GPIO_Pin_6) //�Ϲ�ͨ��
#define LAMP9_OFF GPIO_SetBits(GPIOE,GPIO_Pin_6) 
#define LAMP10_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_13)// ���ſ���λ
#define LAMP10_OFF GPIO_SetBits(GPIOC,GPIO_Pin_13) 
#define LAMP11_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_14) //���Źص�λ
#define LAMP11_OFF GPIO_SetBits(GPIOC,GPIO_Pin_14) 
#define LAMP12_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_15) //�ܷ��ֵ�λ
#define LAMP12_OFF GPIO_SetBits(GPIOC,GPIO_Pin_15) 
#define LAMP13_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_3) //ͨ��
#define LAMP13_OFF GPIO_SetBits(GPIOC,GPIO_Pin_3) 
#define LAMP14_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_2) //��Դ
#define LAMP14_OFF GPIO_SetBits(GPIOC,GPIO_Pin_2) 

#define LED1_ON  GPIO_ResetBits(GPIOD,GPIO_Pin_9)
#define LED1_OFF GPIO_SetBits(GPIOD,GPIO_Pin_9) 
#define LED2_ON  GPIO_ResetBits(GPIOD,GPIO_Pin_8)
#define LED2_OFF GPIO_SetBits(GPIOD,GPIO_Pin_8) 
#define LED3_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_15)
#define LED3_OFF GPIO_SetBits(GPIOB,GPIO_Pin_15) 
#define LED4_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_15)
#define LED4_OFF GPIO_SetBits(GPIOC,GPIO_Pin_15) 

#define SPK_OFF  GPIO_SetBits(GPIOD,GPIO_Pin_6)   
#define SPK_ON GPIO_ResetBits(GPIOD,GPIO_Pin_6)

#define POWER_DIS GPIO_ResetBits(GPIOB,GPIO_Pin_2)
#define POWER_EN GPIO_SetBits(GPIOB,GPIO_Pin_2)

void Lamp_OutBIT(void);
void Lamp_SetBIT(uint8 Bit);
void Lamp_ClrBIT(uint8 Bit);
void Lamp_SetUint32(uint32 Bit);
void Lamp_Test(uint8 i);

#endif
