/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#define STM32F10X_HD
#define  USART_TX_BUFFER_SIZE 300
#define  USART_RX_BUFFER_SIZE 300
#define  OSC_FREQ      ((uint32_t)8000000)
#define  Tos_TaskTotal            7      //����ش�С
#define  Tos_TaskStackDefSize     4000   //Ĭ�ϵ��������ջ��С    
#define  Tos_RootTaskStackSize    1000
#define  Tos_DeviceTotal         10     //�豸�ش�С
#define  Tos_TaskWatchDog        2000   //��������λʱ��
#define  Tos_Cpu_Freq						72000000	 //ϵͳ����Ƶ��
#define  Board_Name            "BOARD_TANK_Hand" 
#define  CPU_Model             "STM32F103VET6" 
#define  FLASH_PARAM_PAGE	     510
#define  CAN_DeviceTotal       10
#define IWDG_ENABLE 
#define COMPILE_MODE_DEBUG
#define CAN_ISTR_EN
//#define STM32F10X_HD
//#define  USART_TX_BUFFER_SIZE 300
//#define  USART_RX_BUFFER_SIZE 300
//#define  OSC_FREQ      ((uint32_t)8000000)
//#define TOS_MEMA_EN  //ʹ���ڴ涯̬����
//#define  Tos_TaskTotal            10      //����ش�С
//#ifdef TOS_MEMA_EN
//#define  Tos_TaskStackDefSize     1   //Ĭ�ϵ��������ջ��С
//#else 
//#define  Tos_TaskStackDefSize     2000   //Ĭ�ϵ��������ջ��С
//#endif
//#define  Tos_RootTaskStackSize    1000
//#define  Tos_DeviceTotal         10     //�豸�ش�С
//#define  Tos_TaskWatchDog        2000   //��������λʱ��
//#define  Tos_Cpu_Freq						72000000	 //ϵͳ����Ƶ��
//#define  Board_Name             "����" 
//#define  CPU_Model              "STM32F103VET6" 
//#define  FLASH_PARAM_PAGE	      510
//#define  USART_CH_SIZE 5
