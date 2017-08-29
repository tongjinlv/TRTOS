/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_
#include <Include.h>

#define USART_DEF_CH_SIZE  5


extern uint8 DeviceId_USART_TX[USART_DEF_CH_SIZE];//=DeviceNull;
extern uint8 DeviceId_USART_RX[USART_DEF_CH_SIZE];//=DeviceNull;
extern uint8  USART_TX_TaskID[USART_DEF_CH_SIZE];//=Tos_TaskTotal;
extern uint8  USART_RX_TaskID[USART_DEF_CH_SIZE];//=Tos_TaskTotal;
extern uint8  *USART_RX_Buffer[USART_DEF_CH_SIZE];
extern uint8  *USART_TX_Buffer[USART_DEF_CH_SIZE];
extern uint16 USART_RX_Count[USART_DEF_CH_SIZE];//=Null;
extern uint16 USART_RX_Index[USART_DEF_CH_SIZE];
uint16 USART_WriteLine(USART_TypeDef* USARTx,char *fmt,...);
void USART_WriteData(USART_TypeDef* USARTx,uint16 Data);
USART_TypeDef* USART_GetTypeDef(uint8 Index);
uint8 USART_GetIndex(USART_TypeDef* USARTx);
void DeviceMount_Usart(USART_TypeDef* USARTx);
void USART_Configuration(uint8 UsartCH);
void USART_WriteDatas(USART_TypeDef* USARTx,u8* Data,u16 Length);
uint16 USART_ReadDatas(USART_TypeDef* USARTx,uint8 *Buf,uint16 Length,uint32 TimeOut);
uint16 USART_GetRXBufSize(USART_TypeDef* USARTx);
uint16 USART_GetTXBufSize(USART_TypeDef* USARTx);
void DeviceMount_Uart(USART_TypeDef* USARTx,uint16 RxBufSize,uint16 TxBufSize);
#endif
