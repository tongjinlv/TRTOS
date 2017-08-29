/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_
#include <Include.h>


typedef  void (*SPI_Func)(BOOL Level);

typedef struct
{
	void (*MOSI)(BOOL Level);
	void (*SCLK)(BOOL Level);
	void (*CE)(BOOL Level);
	void (*CSN)(BOOL Level);
	BOOL (*IRQ)(void);
	BOOL (*MISO)(void);
	uint16 Delay;
}SPI_PublicStruct;

void SPI_Delay(uint16 i);
uint8 SPI_WR(const SPI_PublicStruct *SPI,uint8 Data);
uint8 SPI_WriteReg(const SPI_PublicStruct *SPI,uint8 reg,uint8 dat);
uint8 SPI_ReadReg(const SPI_PublicStruct *SPI,uint8 reg,uint8 dat);
uint8 SPI_ReadBuf(const SPI_PublicStruct *SPI,uint8 reg,uint8 *pBuf,uint8 Length);
uint8 SPI_WriteBuf(const SPI_PublicStruct *SPI,uint8 reg ,uint8 *pBuf,uint8 Length);

#endif
