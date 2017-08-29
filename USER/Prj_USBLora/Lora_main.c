/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <Tos_Mema.h>
#include <GPIO_Driver.h>
#include <..\USER\Prj_USBLora\spi.c>
#include <SX1278_Driver.c>
#include <..\USER\Prj_USBLora\Lora_App.c>

void Task0(void *Tags)
{
	DeBug_OutSet(DeBug_USART2);
	DeBug_OutSet(Infor_All);
//	Printf_SysInfor();
	while(1)
	{
		Tos_TaskDelay(100);
		GPIO_SetIndex(0,1);
		Tos_TaskDelay(1000);
		GPIO_SetIndex(0,0);
		//
	}
}

const TaskInitList TaskList[]={
{Task0,Null,"Task0",2000},
{Task_Lora_zhuji,Null,"Task1",2000},
{Task_Lora_zhumb,Null,"Task1",2000},
//{Task_Lora_zhumb,Null,"Task1",2000},
//{Task_Lora_UartoLora,Null,"Task2",2000},
{Null},
};
//const TaskInitList TaskList[]={
//{Task0,Null,"Task0",2000},
//{Task_Lora_Jianting,Null,"Task1",2000},
//{Task_Lora_UartoLora,Null,"Task2",2000},
//{Null},
//};
const GPIO_InitStruct IO_Control_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_12},//【0】指示灯
	{0},
};
int main(void)
{
//	if(((uint32)SystemInit)>0x8007735)NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x5000);//BOOT 与非BOOT的区别
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_Usart(USART1);
	DeviceMount_Usart(USART2);
	DeviceMount_GPIO(IO_Control_List);
	Tos_ListCreate(TaskList);
	while(1);
}



