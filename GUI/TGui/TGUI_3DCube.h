/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _COBE_H_
#define _COBE_H_
#include <Include.h>


typedef struct
{
	uint16 X;
	uint16 Y;
	uint16 Z;
	uint16 D;
}Coordinate_3D;
extern const Coordinate_3D C3D_Default;
void TGui_3DCobeTest(void);
void Disply3D(float xpos,float ypos,float zpos);

#endif
