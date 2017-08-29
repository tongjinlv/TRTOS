/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _MOTO_H_
#define _MOTO_H_
#include <Include.h>


#define   PULSE_DELAY      2

#define   PLUSE_STEP_NUM   20

#define  MOVE_UP 0
#define  MOVE_DN  1

void Motor_Ctrl(uint8 dir,uint16 num);

#endif
