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
#include <COMenu.c>



void Task0(void *Tags)
{
	
	Remap_SWJ_JTAGDisable();
	DeBug_OutSet(DeBug_USART1);
	ADC1_Init((uintbus)&UIShowValue.ADC);
	GPIO_SetIndex(5,0);//关蜂鸣器
	GPIO_SetIndex(2,1);//接近激励
	GPIO_SetIndex(3,1);//接近激励
	GPIO_SetIndex(6,1);//POW1
	GPIO_SetIndex(0,1);//关EYE
	GPIO_SetIndex(1,1);//关EYE
	GPIO_SetIndex(15,0);//IR红外发射
	Printf_SysInfor();//打印系统信息
	WS_SetColorBit(0x0000,S0|S1|S2|S3);
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
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_15},//【2】接近驱动1
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_15},//【3】接近驱动2
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOC,GPIO_Pin_14},//【4】红外接收 
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_13},//【5】蜂鸣器
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_0},//【6】POW1
	{GPIO_Speed_2MHz,GPIO_Mode_IPD,GPIOB,GPIO_Pin_1},//【7】POW2
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_6},//【8】BPWM
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_7},//【9】APWM
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_4},//【10】BIN1
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_5},//【11】AIN1
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_15},//【12】WS1
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_12},//【13】WS2
	{GPIO_Speed_50MHz,GPIO_Mode_IPD,GPIOA,GPIO_Pin_0},//【14】WKUP
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_11},//【15】IR
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

