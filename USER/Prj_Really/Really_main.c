/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <..\USER\Prj_Really\HandKey_Driver.c>
#include <Really_GUI.c>
#include <App_Really.c>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <Really_Driver.h>
#include <Really_GUI.h>
#include <FuncTask_Include.h>
#include <HandKey_Driver.h>
#include <App_Really.h>
/****************************************************************************
Date:2014-11-12
Func:主任务
Note:
****************************************************************************/
void Task0(void *Tags)
{
	LCD_ON;
	WIRE_ON;
	while(1)
	{
		LED_ON;
		Tos_TaskDelay(100);
		LED_OFF;
		Tos_TaskDelay(100);
		SleepCount++;
		if(SleepCount>100)Standby_Init();
	}
}
/****************************************************************************
Date:2014-11-12
Func:程序入口
Note:新增了入口参数
****************************************************************************/
int main(void)
{
	DeviceList_Init();
	Device_Init();
	Tos_Init();
 	Tos_TaskCreate(0,Task0,Null,"Task1",500);
	Tos_TaskCreate(1,Really_Task,Null,"Task2",2000);
	Tos_TaskCreate(2,Task_GetHandKey,Null,"Task2",500);
	Tos_TaskCreate(3,Task_GetPDA,Null,"Task_GetPDA",1000);
	Tos_Start();
	while(1);
}

