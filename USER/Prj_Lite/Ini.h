/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
//#define STM32F10X_HD
#define  COM_HAS_THREE
#define  USART_TX_BUFFER_SIZE 30
#define  USART_RX_BUFFER_SIZE 30
#define  OSC_FREQ      ((uint32_t)8000000)
#define  MEMA_BUFFER_SIZE 14000
#define  Tos_TaskTotal            20      //任务池大小
#define  Tos_RootTaskStackSize    2000
#define  Tos_DeviceTotal         10     //设备池大小
#define  Tos_TaskWatchDog        20000   //任务卡死复位时间
#define  Tos_Cpu_Freq						72000000	 //系统工作频率
#define  Board_Name             "Insect" 
#define  CPU_Model              "STM32F103C8T6" 
#define  FLASH_PARAM_PAGE	      62
#define  USART_CH_SIZE 3
#define  COMPILE_MODE_DEBUG
#define IWDG_ENABLE 
#define DISCOPPY_ENABLE

