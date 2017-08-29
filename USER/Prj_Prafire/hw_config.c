/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
/******************** (C) COPYRIGHT 2011 ����Ƕ��ʽ���������� ********************
 * �ļ���  ��hw_configs.c
 * ����    ��USB���ú�����
 *          
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�-------------------------------
 *          | PE3-USB-MODE	 (PE3Ϊ��ͨI/O) |
 *          | PA11-USBDM(D-)								|
 *          | PA12-USBDP(D+)								|
 *           -------------------------------
 *
 * ��汾  ��ST3.0.0
 *
 * ����    ��fire  QQ: 313303034 
 * ����    ��firestm32.blog.chinaunix.net
**********************************************************************************/
#include "stm32f10x.h"
#include <..\USB\UPan\usb_library\inc\hw_config.h>
#include <..\USB\UPan\usb_library\inc\usb_lib.h>

/*
 * ��������Set_USBClock
 * ����  ������USBʱ��(48M)
 * ����  ����
 * ���  ����
 */
void Set_USBClock(void)
{
   /* USBCLK = PLLCLK */
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

  /* Enable USB clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*
 * ��������Enter_LowPowerMode
 * ����  ��Power-off system clocks and power while entering suspend mode(��ʱΪ��)
 * ����  ����
 * ���  ����
 */
void Enter_LowPowerMode(void)
{
}

/*
 * ��������Leave_LowPowerMode
 * ����  ��Restores system clocks and power while exiting suspend mode(��ʱΪ��)
 * ����  ����
 * ���  ����
 */
void Leave_LowPowerMode(void)
{
}

/*
 * ��������USB_Interrupts_Config
 * ����  ������USB�ж�
 * ����  ����
 * ���  ����
 */
void USB_Interrupts_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM
  /* Set the Vector Table base location at 0x20000000 */
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH */
  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*
 * ��������USB_Cable_Config
 * ����  ��Software Connection/Disconnection of USB Cable
 * ����  ��-NewState: new state
 * ���  ����
 */
void USB_Cable_Config (FunctionalState NewState)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

  /* PE3 ��� 0 ʱ D+ ���������蹤����ȫ��ģʽ */ 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	   /* ��©��� */
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	 
  if (NewState != DISABLE)
  {
    GPIO_ResetBits(GPIOE, GPIO_Pin_3);		             /* USBȫ��ģʽ */
  }
  else
  {
    GPIO_SetBits(GPIOE, GPIO_Pin_3);			             /* ��ͨģʽ */
  }
}


/******************* (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� *****END OF FILE****/
