/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <..\USER\Prj_CAMERACTR\Moto.h>


void Motor_Ctrl(uint8 dir,uint16 num)
{
	uint16 i =0;
	MOTOR_EN(0); 
	if(dir != MOVE_DN)
	{
	 MOTOR_DIR(MOVE_UP);
	}
	else
	{
	 MOTOR_DIR(MOVE_DN);
	}
	for(i=0; i < num ;i++)
	{
	 MOTOR_PLUSE(0);
	 Tos_TaskDelay(PULSE_DELAY);
	 MOTOR_PLUSE(1);  
	 Tos_TaskDelay(PULSE_DELAY);
	}
	MOTOR_EN(1); 
}
