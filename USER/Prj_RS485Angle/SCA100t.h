/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _SCA100T_H_
#define _SCA100T_H_
#include  <Include.h>

#define MEAS 0x00 //����ģʽ
#define RWTR 0x08 //��д�¶����ݼĴ���
#define STX  0x0E //xͨ���Լ�
#define STY  0x0F //Yͨ���Լ�
#define RDAX 0x10 //����ͨ�����ٶ�ֵ
#define RDAY 0x11 //����ͨ�����ٶ�ֵ
#define RDSR 0x0a //��ȡ״̬�Ĵ���

#define SCACLK_L    GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define SCACLK_H    GPIO_SetBits(GPIOB,GPIO_Pin_7) 

#define SCAOUT_L    GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define SCAOUT_H    GPIO_SetBits(GPIOB,GPIO_Pin_6) 
#define SCAOUT_D    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)

#define SCAIN_L     GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define SCAIN_H     GPIO_SetBits(GPIOB,GPIO_Pin_5) 

#define SCACS_L     GPIO_ResetBits(GPIOB,GPIO_Pin_4)
#define SCACS_H     GPIO_SetBits(GPIOB,GPIO_Pin_4) 


extern uint16 AngleXY[2];
void GPIO_SCA100T_Init(void);
uint16 SPI_GetX(void);
uint16 SPI_GetY( void );
void SCA_Init( void );
uint16 SPI_GetReg(uint8 Cmd,uint8 Length);
void Task_GetAngle(void *Tags);
#endif
