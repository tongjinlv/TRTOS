/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
//#define STM32F10X_HD
#define  COM_HAS_THREE
#define  USART_TX_BUFFER_SIZE 30
#define  USART_RX_BUFFER_SIZE 30
#define  OSC_FREQ      ((uint32_t)8000000)
#define  MEMA_BUFFER_SIZE 14000
#define  Tos_TaskTotal            20      //����ش�С
#define  Tos_RootTaskStackSize    2000
#define  Tos_DeviceTotal         10     //�豸�ش�С
#define  Tos_TaskWatchDog        20000   //��������λʱ��
#define  Tos_Cpu_Freq						72000000	 //ϵͳ����Ƶ��
#define  Board_Name             "Insect" 
#define  CPU_Model              "STM32F103C8T6" 
#define  FLASH_PARAM_PAGE	      62
#define  USART_CH_SIZE 3
#define  COMPILE_MODE_DEBUG
#define IWDG_ENABLE 
#define DISCOPPY_ENABLE

