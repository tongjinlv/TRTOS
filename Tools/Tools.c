/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Tools.h>

//uint8 Get_OnlyOneID(uint8 *Buf)
//{  
//	uint8 temp[12];
//	u32 temp0,temp1,temp2;
//	temp0=*(__IO u32*)(0x1FFFF7E8);    //产品唯一身份标识寄存器（96位）
//	temp1=*(__IO u32*)(0x1FFFF7EC);
//	temp2=*(__IO u32*)(0x1FFFF7F0);
//	temp[0] = (u8)(temp0 & 0x000000FF);
//	temp[1] = (u8)((temp0 & 0x0000FF00)>>8);
//	temp[2] = (u8)((temp0 & 0x00FF0000)>>16);
//	temp[3] = (u8)((temp0 & 0xFF000000)>>24);
//	temp[4] = (u8)(temp1 & 0x000000FF);
//	temp[5] = (u8)((temp1 & 0x0000FF00)>>8);
//	temp[6] = (u8)((temp1 & 0x00FF0000)>>16);
//	temp[7] = (u8)((temp1 & 0xFF000000)>>24);
//	temp[8] = (u8)(temp2 & 0x000000FF);
//	temp[9] = (u8)((temp2 & 0x0000FF00)>>8);
//	temp[10] = (u8)((temp2 & 0x00FF0000)>>16);
//	temp[11] = (u8)((temp2 & 0xFF000000)>>24);
//	FmtToBuf((char *)&Buf[0],"%2x",temp[1]);
//	return 12;
//}
