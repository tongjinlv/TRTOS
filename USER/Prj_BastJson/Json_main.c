/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <Tos_Mema.h>
#include <Json.h>
#include <GPIO_Driver.h>
#include <FuncTask_Include.h>
#include <IIC_Driver.c>
#include <..\USER\Prj_Geek_Bast\IO_Driver.c>
#include <..\USB\STM32_USB-FS-Device_Driver\USB_FS_Device_Driver.c>
#include <..\USER\Prj_Geek_Bast\usb_desc.c>
#include <..\USER\Prj_Geek_Bast\hw_config.c>
#include <..\USER\Prj_Geek_Bast\usb_endp.c>
#include <..\USER\Prj_Geek_Bast\usb_istr.c>
#include <..\USER\Prj_Geek_Bast\usb_prop.c>
#include <..\USER\Prj_Geek_Bast\usb_pwr.c>
#include <..\Driver\Virtual_Usart.c>
#include <..\USER\Prj_BastJson\Json_Test.c>
#include <..\USER\Prj_BastJson\MPU6050_Driver.c>
void Task0(void *Tags)
{
	char zzzz[10]={0,0,0,0,0,0};
	uint8 k;
	Remap_SWJ_JTAGDisable();
	GPIO_SetAll(0xffff);
	while(1)
	{	
		GPIO_SetIndex(0,0);
		Tos_TaskDelay(40);
		GPIO_SetIndex(0,1);
		Tos_TaskDelay(100);
	  GPIO_SetIndex(1,0);
		Tos_TaskDelay(40);
		GPIO_SetIndex(1,1);
		Tos_TaskDelay(1000);
	}
}
void Task1(void *Tags)
{
	char zzzz[10]={0,0,0,0,0,0};
	uint8 k;
	Remap_SWJ_JTAGDisable();
	GPIO_SetAll(0xffff);
	while(1)
	{	
		
		DeBug("Task1adsffffffffffds 大洒洒水所所所",6);
		Tos_TaskDelay(1000);
	}
}
const TaskInitList TaskList[]={
{Task0,Null,"Task0",2000},
{TempGD20,Null,"Task0",2000},
{Task_VirtualCOM,Null,"VirtualUart",2000},
{Task3,Null,"Json",2000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_GetKeyVirtual,Null,"Key",2000},
{Null},
};

const GPIO_InitStruct LED_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_10},
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_11},
	{0},
};	
const GPIO_InitStruct GPIO_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_14},//D0时钟
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_15},//D1数据
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_2},//RES复位
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_3},//DC数据命令选择
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_15},//DC数据命令选择
	{0},
};

const GPIO_InitStruct GPIO_ListKey[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOC,GPIO_Pin_13},//D0时钟
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOB,GPIO_Pin_9},//D1数据
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOD,GPIO_Pin_2},//RES复位
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOC,GPIO_Pin_12},//DC数据命令选
	{0},
};
int main(void)
{
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_Usart(USART1);
	DeviceMount_GPIO(LED_List);
	Tos_ListCreate(TaskList);
	while(1);
}



