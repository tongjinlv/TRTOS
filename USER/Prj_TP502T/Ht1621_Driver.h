/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _HT1621_DRIVER_H_
#define _HT1621_DRIVER_H_
#include <Include.h>

#define HT1621_CS     GPIO_Pin_7//GPIO_Pin_4
#define HT1621_WR    GPIO_Pin_6 //GPIO_Pin_1
#define HT1621_DAT   GPIO_Pin_5/*GPIO_Pin_0*///GPIO_Pin_7

void Ht1621Wr_Data(u8 Data, u8 cnt);
void Ht1621Wr_Cmd(u8 Cmd);
void Ht1621_WriteReg(u8 Addr, u8 Data);
void Ht1621_WriteRegs(u8 SPaddr, u8* SpData, u8 Len);
void HT1621_Init(void);
void DeviceMount_HT1621(void);
#endif
