/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <FuncTask_Include.h>
#include <..\USER\Prj_Boot\BootLoader.h>
#include <..\Driver\SZZigBee_Driver.h>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <..\USER\Prj_Boot\BootLoader.h>
#include <..\Driver\SZZigBee_Driver.h>
#include <Sensor_Driver.h>
#include <IAP_Driver.h>
#include <..\USER\Prj_Boot\BootLoader.c>
#include <..\Driver\SZZigBee_Driver.c>
#include <StandardModBus.h>


void Temp(void *Tags)
{
	
	Frist_CheckEnv();
	Load_EnvConfig();//加载环境变量
	while(1)
	{
		Tos_TaskDelay(200);
		WaitDownLoadCount--;	//BOOT停留计数
	 if(enValue.UpdateApp!=False)WaitDownLoadCount=10;//应用不完整不进去应用
	 if(WaitDownLoadCount==0)Application_Run(ApplicationAddress);//超时进入应用
		//USART_WriteLine(USART1,"Boot3.0 Load Start!");
	} 
}
const TaskInitList TaskList[]={
{DownLoad_Command,(void *)USART1,"Task0",8000},
//{DownLoad_Command,(void *)USART2,"Task1",8000},//任务使用串口1作为下载
{Temp,Null,"Task0",2000},//跳转任务
{Null},//任务表结束符
};
int main(void)
{	
	Mema_Init(&MemBuf[0]);//内存初始化
	DeviceList_Init();//设备列表初始化
	DeviceMount_Usart(USART1);//串口1挂载
	DeviceMount_Usart(USART2);//串口2挂载

	Tos_ListCreate(TaskList);//创建任务表任务
	while(1);
}
