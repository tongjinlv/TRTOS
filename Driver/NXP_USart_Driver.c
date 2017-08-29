/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Tools_Include.h>
#include <Tos_Mema.h>
#include <LPC177x_8x.H>
#include <NXP_Usart_Driver.h>
uint8 DeviceId_USART_TX[USART_DEF_CH_SIZE];
uint8 DeviceId_USART_RX[USART_DEF_CH_SIZE];
uint8  USART_TX_TaskID[USART_DEF_CH_SIZE];
uint8  USART_RX_TaskID[USART_DEF_CH_SIZE];
uint8  *USART_RX_Buffer[USART_DEF_CH_SIZE];
uint8  *USART_TX_Buffer[USART_DEF_CH_SIZE];
uint16 USART_RX_Count[USART_DEF_CH_SIZE];
uint16 USART_RX_Index[USART_DEF_CH_SIZE];
