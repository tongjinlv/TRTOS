/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <Tos_Mema.h>
#include <FuncTask_Include.h>
#include <isl1208_driver.h>
#include <IIC_Driver.c>
#include <..\USER\Prj_TP500New\IO_Driver.c>
#include <..\USER\Prj_TP500New\Ht1621_Driver.c>
#include <..\USER\Prj_TP500New\Ht1621_Face.c>
#include <..\USER\Prj_TP502T\TempHui_Driver.c>
#include <..\USER\Prj_MiniDTU\App_Sensor.c>
#include <W25Q16_Driver.c>
#include <isl1208_driver.c>
#include <..\USER\Prj_TP502T\App1.h>
#include <..\USER\Prj_TP502T\GB2312_Unicode.c>
#include <..\USER\Prj_TP502T\ADC_Driver.c>
#include <..\USER\Prj_TP502T\GPS_Driver.c>
#include <AT_Command.c>
#include <..\USER\Prj_MiniDTU\QuectelM26BT.c>
#include <..\USER\Prj_TP502T\Auto_Register.c>
#include <..\USER\Prj_TP502T\App2.c>
#include <..\USER\Prj_TP500New\App1.c>
#include <..\USER\Prj_MiniDTU\App.c>
#include <GPIO_Driver.h>

const GPIO_InitStruct IO_Control_List[];
uint8 TaskLora_Tos_TaskID=Tos_TaskNull;

void Task0(void *Tags)
{
	Task0_MiniDTUInit();
	UIShowValue.SysWorkMode=0;
	while(1)
	{

		Tos_TaskDelay(1000);
	//	DeBug("dddddddddddddddddd",6);
		USART_WriteLine(USART3,"dddddddddddddddddd");
	}
}


const TaskInitList TaskList_putong[]={
{Task0,Null,"Task0",2000},
{Task_M26HTTPJSON,Null,"GPRS",14000},
{Sensor_Command,USART1,"SCOM",2000},
{Sensor_Command,USART3,"SCOM",2000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Null},
};

const TaskInitList TaskList_touchuan[]={
{Task0,Null,"Task0",2000},
{Task_M26Transmission,Null,"GPRS",14000},
{UsartToGPRS,Null,"UsartToGPRS",2000},
//{Sensor_Command,USART1,"SCOM",2000},
//{Sensor_Command,USART3,"SCOM",2000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Null},
};
const GPIO_InitStruct IO_Control_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_12},//【0】RX485高发送使能
	//{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_5},//【0】RX485高发送使能
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_7},//【1】GPRS_POWERON电源未用
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_12},//【2】POWERKEY
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOB,GPIO_Pin_7},//【3】VDD_EXT
	{0},
};
int main(void)
{
	//NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x5000);
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_Uart(USART1,100,100);
	DeviceMount_Usart(USART2);
	DeviceMount_Usart(USART3);
	DeviceMount_GPIO(IO_Control_List);
	Load_AppConfig(&UIShowValue.SaveValue,0);
	UIShowValue.SaveValue.DeviceType=1;
	switch(UIShowValue.SaveValue.DeviceType)
	{
		case 0:Tos_ListCreate(TaskList_putong);break;
		case 1:Tos_ListCreate(TaskList_touchuan);break;
		default:Tos_ListCreate(TaskList_putong);break;
	}
	while(1);
}



