/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#define STM32F10X_LD
#define  USART_TX_BUFFER_SIZE 1000
#define  USART_RX_BUFFER_SIZE 300
#define  OSC_FREQ      ((uint32_t)6000000)
#define  Tos_TaskTotal            7      //����ش�С
#define  Tos_TaskStackDefSize     4000   //Ĭ�ϵ��������ջ��С    
#define  Tos_RootTaskStackSize    1000
#define  Tos_DeviceTotal         10     //�豸�ش�С
#define  Tos_TaskWatchDog        2000   //��������λʱ��
#define  Tos_Cpu_Freq						72000000	 //ϵͳ����Ƶ��
#define  Board_Name            "BOARD_CORE1_0" 
#define  CPU_Model             "STM32F103ZET6" 
#define  FLASH_PARAM_PAGE	     510
#define  CAN_DeviceTotal       100
#define IWDG_ENABLE 