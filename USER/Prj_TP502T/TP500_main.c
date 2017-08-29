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
#include <..\USER\Prj_TP502T\isl1208_driver.h>
#include <IO_Driver.c>
#include <IIC_Driver.c>
#include <..\USER\Prj_TP502T\Ht1621_Driver.c>
#include <..\USER\Prj_TP500New\Ht1621_Face.c>
#include <..\USER\Prj_TP502T\TempHui_Driver.c>
#include <..\USER\Prj_TP502T\App_Sensor.c>
//#include <SZZigBee_Driver.c>
#include <W25Q16_Driver.c>
#include <..\USER\Prj_TP502T\isl1208_driver.c>
#include <..\USER\Prj_TP502T\App1.h>
#include <..\USER\Prj_TP502T\ADC_Driver.c>
#include <..\USER\Prj_TP502T\GPS_Driver.c>
#include <..\USER\Prj_TP502T\GB2312_Unicode.c>
#include <AT_Command.c>
#include <..\USER\Prj_TP502T\QuectelM26BT.c>
#include <..\USER\Prj_TP502T\Auto_Register.c>
#include <..\USER\Prj_TP502T\UpgradeByGPRS.c>
#include <..\USER\Prj_TP502T\App2.c>
#include <..\USER\Prj_TP502T\App1.c>
void EXTI2_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line2);
	MCU_Reset();
}
uint8 ReadIO()
{
	uint8 Data;
	IO_Read_Value(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
	Data=0;
	if(UIShowValue.CH_Value[0]>0)Data|=S0;
	if(UIShowValue.CH_Value[1]>0)Data|=S1;
	return Data;
}
void Task_CheckDoor(void *Tags)
{
	uint8 Data=0,OldData=0xff;
	while(1)
	{
		Data=ReadIO();
		Tos_TaskDelay(300);
		if(Data==ReadIO())
		if(Data!=OldData)
		{
			OldData=Data;
			Timer_KGM(Data);
			DeBug("门动作",Infor_Warning);
		}
		Tos_TaskDelay(300);
	}
}
void Task0(void *Tags)
{
	
	Task0_Init();
	E3V3_ON;
	while(1)
	{
				IO_Set(0,True);
				Tos_TaskDelay(1000);
				IO_Set(0,False);
				Tos_TaskDelay(100);
	}
}

const GPIO_InitStruct IO_ISL1208_List[]=
{
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOB,GPIO_Pin_11},//SDA
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_10},//SCL
	{0},
};
const GPIO_InitStruct IO_IO_List[]=
{
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_7},
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_6},
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_13},
	{GPIO_Speed_50MHz,GPIO_Mode_IPD,GPIOA,GPIO_Pin_0},
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_8|GPIO_Pin_9},
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_3|GPIO_Pin_2},
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOC,GPIO_Pin_1|GPIO_Pin_0},
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_1},
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_0},
	{0},
};
void Task_AutoReset(void *Tags)
{
	Tos_TaskDelay(1000*60*60*24);
	MCU_Reset();
}
const TaskInitList TaskList_putong[]={
{Task0,Null,"Task0",2000},
{Sensor_Command,USART1,"Sensor_Command",2000}, 
{TaskPlan,Null,"TaskPlan",2000},
{Task_M26,Null,"GPRS",6000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_AutoReset,Null,"Task_AutoReset",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList Taskkaiguanliang[]={
{Task0,Null,"Task0",2000},
{Sensor_Command,USART1,"Sensor_Command",2000}, 
{TaskPlan1,Null,"TaskPlan",2000},
{Task_M26KGL,Null,"GPRS",6000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList Taskkaiguanmen[]={
{Task0,Null,"Task0",2000},
{Sensor_Command,USART1,"Sensor_Command",2000}, 
{TaskPlan1,Null,"TaskPlan",2000},
{Task_M26KGM,Null,"GPRS",6000},
{Task_CheckDoor,Null,"CheckDoor",6000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};

const TaskInitList TaskCaiji[]={
{Task0,Null,"Task0",2000},
{Sensor_Command,USART1,"Sensor_Command",2000}, 
{TaskPlan3,Null,"TaskPlan",2000},
{Task_M26Caiji,Null,"GPRS",6000},
{Task_433ToValue,Null,"GPRS",2000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_AutoReset,Null,"Task_AutoReset",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList TaskList_Yanwu[]={
{Task0,Null,"Task0",2000},
{Sensor_Command,USART1,"Sensor_Command",2000}, 
{TaskPlan,Null,"TaskPlan",2000},
{Task_M26Caiji,Null,"GPRS",6000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_AutoReset,Null,"Task_AutoReset",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
int main(void)
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x5000); 
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();                                                                     
	DeviceMount_Usart(USART1);
	DeviceMount_Usart(USART2);
	//DeviceMount_Usart(USART3);
	DeviceMount_Usart(UART4);
	DeviceMount_ISL1208(IO_ISL1208_List);
	DeviceMount_IO(IO_IO_List);
	DeviceMount_W25Q16();
	Load_AppConfig(&UIShowValue.SaveValue,0);
	switch(UIShowValue.SaveValue.DeviceType)
	{
		case 0:Tos_ListCreate(TaskList_putong);break;
		case 1:Tos_ListCreate(Taskkaiguanliang);break;
		case 2:Tos_ListCreate(Taskkaiguanmen);break;
		case 3:Tos_ListCreate(TaskCaiji);break;
		case 4:Tos_ListCreate(TaskList_Yanwu);break;
	}
	Tos_ListCreate(TaskList_putong);
	while(1);
}




