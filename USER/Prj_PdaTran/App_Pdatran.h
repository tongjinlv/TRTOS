/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _APP_PDATRAN_H_
#define _APP_PDATRAN_H_
#include <Include.h>
#ifdef BOARD_PDATRAN

typedef enum
{
	
	PMFF_SetAddr=0,
	PMFF_GetAddr=1,
	PMFF_GetUint16=2,
	PMFF_GetUint8=3,
	PMFF_GetBuf=4,
	PMFF_SetBuf=5,
	PMFF_TestCmd=6,
}PDA_Modbus_FrameFlag;
extern uint8 PDA_Buf[PDA_Buf_Size];
extern uint8 Pda_Status;
void Task_PdaTran(void *Tags);
void Task_PdaGetDev(void *Tags);

#endif
#endif
