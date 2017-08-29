/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef __SPI_ENC28J60_H
#define __SPI_ENC28J60_H

#include "stm32f10x.h"


void SPI_Enc28j60_Init(void);
unsigned char	SPI1_ReadWrite(unsigned char writedat);

#endif /* __SPI_ENC28J60_H */
