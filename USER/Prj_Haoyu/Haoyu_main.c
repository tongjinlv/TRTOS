/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
void Task0(void *Tags)
{

	while(1)
	{
		Tos_TaskDelay(100);
	}
}
void Task1(void *Tags)
{

	while(1)
	{
		Tos_TaskDelay(100);
	}
}
const TaskInitList TaskList[]={
{Task0,Null,"Task0",2000},
{Task1,Null,"Task0",2000},
{Null},
};

int main(void)
{
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	Tos_ListCreate(TaskList);
	while(1);
}



