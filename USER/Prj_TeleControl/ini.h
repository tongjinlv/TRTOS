/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#define STM32F10X_MD
#define  USART_TX_BUFFER_SIZE 50
#define  USART_RX_BUFFER_SIZE 50
#define  OSC_FREQ      ((uint32_t)8000000)
#define TOS_MEMA_EN  //使能内存动态分配
#define  Tos_TaskTotal            10      //任务池大小
#ifdef TOS_MEMA_EN
#define  Tos_TaskStackDefSize     1   //默认单个任务堆栈大小
#else 
#define  Tos_TaskStackDefSize     2000   //默认单个任务堆栈大小
#endif
#define  Tos_RootTaskStackSize    1000
#define  Tos_DeviceTotal         10     //设备池大小
#define  Tos_TaskWatchDog        2000   //任务卡死复位时间
#define  Tos_Cpu_Freq						 72000000	 //系统工作频率
#define  Board_Name             "BOARD_CAMERACTR"
#define  CPU_Model              "STM32F103C8T6" 

#define  HSI_USER
//#define USART1_BaudRate 2400
#define  FLASH_PARAM_PAGE	     62
#define IWDG_ENABLE 
#define CAN_ISTR_EN
//#define COMPILE_MODE_DEBUG
