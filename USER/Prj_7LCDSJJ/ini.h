/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#define STM32F10X_HD
#define  USART_TX_BUFFER_SIZE 300
#define  USART_RX_BUFFER_SIZE 1000
#define  OSC_FREQ      ((uint32_t)8000000)
#define  Tos_TaskTotal            8      //����ش�С
#define  Tos_TaskStackDefSize     4000   //Ĭ�ϵ��������ջ��С    
#define  Tos_RootTaskStackSize    1000
#define  Tos_DeviceTotal         16     //�豸�ش�С
#define  Tos_TaskWatchDog        2000   //��������λʱ��
#define  Tos_Cpu_Freq						72000000	 //ϵͳ����Ƶ��
#define  Board_Name            "��������������ʶ��" 
#define  CPU_Model             "STM32F103VET6" 
#define  FLASH_PARAM_PAGE	     510
#define  CAN_DeviceTotal       16
//#define  USART1_BaudRate     9600
#define IWDG_ENABLE 
#define COMPILE_MODE_DEBUG
#define APPTIMEREXECUTE_ENABLE //��������ִ�ж�ʱ��ɨ��
