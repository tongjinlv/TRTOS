/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#define _STM32L1XX_
//#define STM32F10X_HD
#define  COM_HAS_THREE
#define  USART_TX_BUFFER_SIZE 300
#define  USART_RX_BUFFER_SIZE 300
#define  OSC_FREQ      ((uint32_t)8000000)
#define  MEMA_BUFFER_SIZE 8000
#define  Tos_TaskTotal            20      //����ش�С
#define  Tos_RootTaskStackSize    2000
#define  Tos_DeviceTotal         10     //�豸�ش�С
#define  Tos_TaskWatchDog        20000   //��������λʱ��
#define  Tos_Cpu_Freq						32000000	 //ϵͳ����Ƶ��
#define  Board_Name             "LORA" 
#define  CPU_Model              "STM32F103C8T6" 
#define  FLASH_PARAM_PAGE	      64
#define  USART_CH_SIZE 3
#define  COMPILE_MODE_DEBUG
//#define USART3_IRQ_EXT
//#define USART3_BaudRate 9600
//#define IWDG_ENABLE 
