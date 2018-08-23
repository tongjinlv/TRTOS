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
#include <Func_Face.h>
#include <IIC_Driver.c>
#include <Key_Driver.c>
#include <..\USER\Prj_Insect\App.h>
#include <..\USER\Prj_Insect\SHT2x.c>
#include <..\USER\Prj_Insect\ADC_Driver.c>
#include <..\USER\Prj_Insect\PWM_Driver.c>
#include <..\USER\Prj_Insect\Moto_Driver.c>
#include <..\USER\Prj_Insect\WS2812_Driver.c>
#include <..\USER\Prj_Insect\BEEP_Driver.c>
#include <..\USER\Prj_Insect\IR_Driver.c>
#include <..\USER\Prj_Insect\MPU6050_Driver.c>
#include <..\USER\Prj_Insect\App.c>
#include <..\USER\Prj_Insect\App1.c>
#include <..\USER\Prj_Insect\GIDE_Driver.c>
#include <COMenu.c>



void Task0(void *Tags)
{
	
	Remap_SWJ_JTAGDisable();
	DeBug_OutSet(DeBug_USART1);
	BOOL_LoadConfigs();
	while(1)
	{
		
		Tos_TaskDelay(1000);
	}
}


const TaskInitList TaskList[]={
{Task0,Null,"Task0",1000},
{Null}, 
};

const GPIO_InitStruct IO_Control_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_OD,GPIOB,GPIO_Pin_8},//【0】EYE1
	{GPIO_Speed_2MHz,GPIO_Mode_Out_OD,GPIOB,GPIO_Pin_3},//【1】EYE2
	{0},
};

int main(void)
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x5000);
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_Usart(USART1);
	DeviceMount_GPIO(IO_Control_List);
	DeviceMount_Moto();
	Tos_ListCreate(TaskList);
	while(1);
}


