/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#define STM32F10X_LD
#define  USART_TX_BUFFER_SIZE 50
#define  USART_RX_BUFFER_SIZE 50
#define  OSC_FREQ      ((uint32_t)8000000)
#define  Tos_TaskTotal            5      //����ش�С
#define  Tos_TaskStackDefSize     2000   //Ĭ�ϵ��������ջ��С 
#define  Tos_RootTaskStackSize    400
#define  Tos_DeviceTotal         10     //�豸�ش�С
#define  Tos_TaskWatchDog        11000   //��������λʱ��
#define  Tos_Cpu_Freq						 72000000	 //ϵͳ����Ƶ��
#define  Board_Name             "BOARD_CAMERAMOTR"
#define  CPU_Model              "STM32F103C8T6" 
#define  FLASH_PARAM_PAGE	     250
//#define IWDG_ENABLE 
#define COMPILE_MODE_DEBUG
#define USE_FULL_ASSERT
#define SYSCLK_FREQ_72MHz
