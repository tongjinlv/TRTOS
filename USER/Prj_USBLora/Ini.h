/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#define  COM_HAS_THREE
#define  USART_TX_BUFFER_SIZE 300
#define  USART_RX_BUFFER_SIZE 300
#define  OSC_FREQ      ((uint32_t)8000000)
#define  MEMA_BUFFER_SIZE 13000
#define  Tos_TaskTotal            20      //����ش�С
#define  Tos_RootTaskStackSize    2000
#define  Tos_DeviceTotal         10     //�豸�ش�С
#define  Tos_TaskWatchDog        20000   //��������λʱ��
#define  Tos_Cpu_Freq						72000000	 //ϵͳ����Ƶ��
#define  Board_Name             "LORA Center" 
#define  CPU_Model              "STM32F103C8T6" 
#define  FLASH_PARAM_PAGE	      62
#define  COMPILE_MODE_DEBUG
#define USART3_BaudRate 9600
//#define USART2_BaudRate 9600
#define IWDG_ENABLE 
#define DISCOPPY_ENABLE
#define IWDG_ENABLE 
#define SYSTEM_TICK 1000
#define NEW_VERSION
#ifdef NEW_VERSION
#define  HSI_USER
#endif
