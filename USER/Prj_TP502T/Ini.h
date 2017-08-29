/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#define STM32F10X_HD
#define  USART_TX_BUFFER_SIZE 300
#define  USART_RX_BUFFER_SIZE 300
#define  OSC_FREQ      ((uint32_t)8000000)
#define  MEMA_BUFFER_SIZE 40000
#define  Tos_TaskTotal            20      //任务池大小
#define  Tos_RootTaskStackSize    2000
#define  Tos_DeviceTotal         10     //设备池大小
#define  Tos_TaskWatchDog        20000   //任务卡死复位时间
#define  Tos_Cpu_Freq						72000000	 //系统工作频率
#define  Board_Name             "TP502-T" 
#define  CPU_Model              "STM32L151RBT6" 
#define  FLASH_PARAM_PAGE	      254
#define  USART_CH_SIZE 5
#define  COMPILE_MODE_DEBUG
//#define USART3_IRQ_EXT
#define Printf_Title "双温"
#define USART3_BaudRate 9600
#define IWDG_ENABLE 
#define __ENT_KEY__ "35"
