/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#define STM32F10X_LD
#define  USART_TX_BUFFER_SIZE 100
#define  USART_RX_BUFFER_SIZE 100
#define  OSC_FREQ      ((uint32_t)6000000)
#define  Tos_TaskTotal            5     //����ش�С
#define  Tos_TaskStackDefSize     1200   //Ĭ�ϵ��������ջ��С    
#define  Tos_RootTaskStackSize    1000
#define  Tos_DeviceTotal         5     //�豸�ش�С
#define  Tos_TaskWatchDog        8000   //��������λʱ��
#define  Tos_Cpu_Freq						72000000	 //ϵͳ����Ƶ��
#define  Board_Name            "BOARD_REALLY" 
#define  CPU_Model             "STM32F103VET6" 
#define  FLASH_PARAM_PAGE	     62
#define  USART1_BaudRate       9600
#define  USART2_BaudRate       9600
#define  PDA_Buf_Size          100
#define IWDG_ENABLE 

