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
#include <..\USER\Prj_AirCleaner\Ht1621_Driver.c>
#include <..\USER\Prj_AirCleaner\Ht1621_Face.c>
#include <W25Q16_Driver.c>
#include <isl1208_driver.c>
#include <..\USER\Prj_TP502T\App1.h>
#include <..\USER\Prj_AirCleaner\Beep.c>
#include <..\USER\Prj_AirCleaner\ADC_Driver.c>
#include <..\USER\Prj_AirCleaner\IR_Driver.c>
#include <..\USER\Prj_AirCleaner\QTC188R_Driver.c>
#include <..\USER\Prj_AirCleaner\App.c>
#include <GPIO_Driver.h>

const GPIO_InitStruct IO_Control_List[];
uint8 TaskLora_Tos_TaskID=Tos_TaskNull;


const uint8 SEGC1reateCode[][2]={
	{0,4},
	{1,1},
	{2,0},
	{3,7},
	{4,3},
	{5,6},
	{6,2},
	{7,5},
	};

void Task0(void *Tags)
{
	
	ADC1_Init((uintbus)&UIShowValue.ADC[0]);
	Task0_MiniDTUInit();
	UIShowValue.SysWorkMode=0;
	GPIO_SetIndex(1,0);
	UIShowValue.DateTime.Hour=0;
		UIShowValue.DateTime.Min=0;
		UIShowValue.DateTime.Sec=10;
	UIShowValue.SysWorkMode|=WCB_Start;
	UIShowValue.SysWorkMode|=WCB_Open;
	Remap_SWJ_JTAGDisable();
	UIShowValue.ShowFlag|=WSB_Ug;
		//UIShowValue.ShowFlag|=WSB_ExpAlarm|WSB_OpenAirCleaner;
		UIShowValue.SaveValue.LampNum=0;
		UIShowValue.SaveValue.BlowerNum=4;
		UIShowValue.SaveValue.CleanNum=4;
	UIShowValue.SaveValue.BlowerNum=4;
	UIShowValue.GPRSFailCount=0;
	GPIO_SetIndex(6,0);//按键灯
	GPIO_SetIndex(7,0);//净化器开1
	GPIO_SetIndex(4,1);
Tos_TaskDelay(20);
	
	GPIO_SetIndex(4,0);
	Tos_TaskDelay(100);
	GPIO_SetIndex(4,1);
Tos_TaskDelay(100);
	GPIO_SetIndex(4,0);
	GPIO_SetIndex(0,0);
	GPIO_SetIndex(2,0);
	GPIO_SetIndex(3,0);
	Beep_ON();
	while(1)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	{
	
		Tos_TaskDelay(100);
		GPIO_SetIndex(5,1);
		UIShowValue.PM25_Value=Opera_WhithADC(GetFiter(),700,0,4096,8000,9000);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
		UIShowValue.SaveValue.CleanNum=Opera_WhithADC(UIShowValue.PM25_Value,0,0,8000,9,9);
		GPIO_SetIndex(5,0);
		
	}
}

const TaskInitList TaskList_putong[]={
{Task0,Null,"Task0",2000},                                                                                                                                                                                                
//{Sensor_Command,USART1,"SCOM",2000},
{TaskRead,USART3,"SCOM",2000},
{TaskWrite,USART3,"SCOM",2000},
{Task1_Uart4LCD,USART2,"SCOM",2000},
{Ht1621_DrawHome,Null,"SCOM",2000},
{Task_IR,Null,"Task_IR",2000},
{Task_Plan,Null,"Task_Plan",2000},
{Task_VKey,Null,"Task_VKey",2000},
{Task_Arrary,Null,"Task_Arrary",2000}, 
{0},
};
const GPIO_InitStruct IO_Control_List[]=
{
		{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_8},//【0】FG升
		{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_1},//【1】LED背光
		{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_9},//【2】VSP降有问题                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
		{GPIO_Speed_2MHz,GPIO_Mode_Out_OD,GPIOA,GPIO_Pin_10},//【3】GY照明
		{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_7},//【4】蜂鸣器高电平通电
		{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_12},//【5】TXLEDPM2.5激励
		{GPIO_Speed_2MHz,GPIO_Mode_Out_OD,GPIOB,GPIO_Pin_14},//【6】LED按键灯
		{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_5},//【7】净化器
		{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_12},//【8】中速
		{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_4},//【9】高速
		{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_11},//【10】低速
		{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_9},//【11】蜂鸣器高电平通电
	{0},
};
int main(void)
{
	//NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x5000);
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_Uart(USART1,100,100);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
	DeviceMount_Usart(UART4);
	DeviceMount_HT1621();
	DeviceMount_Usart(USART3);
	DeviceMount_Usart(USART2);
	DeviceMount_GPIO(IO_Control_List);
	Load_AppConfig(&UIShowValue.SaveValue,0);
	UIShowValue.SaveValue.DeviceType=0;
	switch(UIShowValue.SaveValue.DeviceType)
	{
		case 0:Tos_ListCreate(TaskList_putong);break;
		default:DeviceMount_Usart(USART3);Tos_ListCreate(TaskList_putong);break;
	}
	while(1);
}
