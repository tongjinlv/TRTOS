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
#include <..\USER\Prj_TP502T\App_Sensor.c>
#include <W25Q16_Driver.c>
#include <isl1208_driver.c>
#include <..\USER\Prj_TP502T\App1.h>
#include <..\USER\Prj_TP502T\GB2312_Unicode.c>
#include <..\USER\Prj_TP502T\ADC_Driver.c>
#include <..\USER\Prj_TP502T\GPS_Driver.c>
#include <AT_Command.c>
#include <..\USER\Prj_TP500New\QuectelM26BT.c>
#include <..\USER\Prj_TP502T\Auto_Register.c>
#include <..\USER\Prj_TP502T\App2.c>
#include <..\USER\Prj_TP500New\App1.c>
#include <GPIO_Driver.h>

const GPIO_InitStruct IO_Control_List[];
uint8 TaskLora_Tos_TaskID=Tos_TaskNull;

void EXTI1_IRQHandler(void)
{
	ISL1208_GPIO_Init();
  EXTI_ClearITPendingBit(EXTI_Line1);
	MCU_Reset();
}

void Task0(void *Tags)
{
	Task0_Init();
	UIShowValue.SysWorkMode=0;
	LED2_OFF;
	LED1_OFF;
	while(1)
	{
		if(UIShowValue.SysWorkMode<=3)
		{
				Tos_TaskDelay(1000);
				LED1_OFF;
				LED2_OFF;
			if(!(UIShowValue.RunFlag&WRF_BeepDisable))
			{
				if(UIShowValue.RunFlag&WRF_SensorCH1Connected)
				if(UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH1Min)){LED1_ON;BEEP_ON;Tos_TaskDelay(10);BEEP_OFF;LED1_OFF;}
				if(UIShowValue.RunFlag&WRF_SensorCH2Connected)
				if(UIShowValue.RunFlag&(WRF_CH2Max|WRF_CH2Min)){LED2_ON;BEEP_ON;Tos_TaskDelay(10);BEEP_OFF;LED2_OFF;}
				Tos_TaskDelay(1000);
			}else Tos_TaskDelay(100);
		}else
		
		{
			Tos_TaskDelay(100);
				LED2_ON;
				LED1_OFF;
				Tos_TaskDelay(100);
				LED1_ON;
				LED2_OFF;
		}
	}
 
}


void Task_Face(void *Tags)
{
	BEEP_ON;
	Tos_TaskDelay(1);
	BEEP_OFF;
	E3V3_ON;
	Tos_TaskDelay(100);
	HT1621_Init();
	Tos_TaskDelay(1000);
	while(1)
	{
		 switch(UIShowValue.SysWorkMode)
		{
			case 0:Ht1621_DrawHome();break;
			case 1:Ht1621_DrawLUX();break;
			case 2:Ht1621_DrawZFS();break;
			case 3:Ht1621_DrawIO();break;
			case 4:Ht1621_DrawSongbo();break;
			case 8:Ht1621_DrawUpDown(0);break;
			case 9:Ht1621_DrawUpDown(1);break;
			case 10:Ht1621_DrawUpDown(2);break;
			case 11:Ht1621_DrawUpDown(3);break;
			case 12:Ht1621_DrawUpDown(4);break;
			case 0xff:break;
		}
		Tos_TaskDelay(1000);
	}
}

void Task_GPRSTime(void *Tags)
{
	
	while(1)
	{
		  
			Tos_TaskCreateFindID(Task_M26,Null,"GPRS",14000);
			Tos_TaskDelay(1000*60*1);
			Tos_TaskDelete(Tos_GetTaskIDByName("GPRS"));
			M26_POWER_OFF;
			Tos_TaskDelay(1000*60*60);
	}
}
void Task_AutoPrintf(void *Tags)
{
	uint8 TimeCount=0,OldHour;
	while(1)
	{
		if(OldHour!=UIShowValue.DateTime.Hour)
		{
		OldHour=UIShowValue.DateTime.Hour;
		if(TimeCount<UIShowValue.SaveValue.PrintfCycle)TimeCount++;
		}
		if(TimeCount>=UIShowValue.SaveValue.PrintfCycle)if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)
		{
			if(UIShowValue.RecordCount)
			{
				Task_PrintfLog();
				TimeCount=0;
				UIShowValue.RecordCount=0;
				W25Q16_Erase(0,sizeof(NandHistoryRecord)*0xff);
			}
		}
		Tos_TaskDelay(1000);
	}
}
void Task_AutoReset(void *Tags)
{
	Tos_TaskDelay(1000*60*30);
	MCU_Reset();
}
const TaskInitList TaskList_putong[]={
{Task0,Null,"Task0",2000},
{TaskFunc,Null,"TaskFunc",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_KeyBoard,Null,"Task_KeyBoard",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{TaskPlan,Null,"TaskPlan",2000},
{Task_M26,Null,"GPRS",14000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_Gps,Null,"Task_Gps",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList TaskList_adddiaodianbutton[]={
{Task0,Null,"Task0",2000},
{TaskFunc,Null,"TaskFunc",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_KeyBoard,Null,"Task_KeyBoard",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{TaskPlan,Null,"TaskPlan",2000},
{Task_M26diaodian,Null,"GPRS",14000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_Gps,Null,"Task_Gps",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList TaskList_zidongdayin[]={
{Task0,Null,"Task0",2000},
{TaskFunc,Null,"TaskFunc",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_KeyBoard,Null,"Task_KeyBoard",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{TaskPlan,Null,"TaskPlan",2000},
{Task_M26,Null,"GPRS",14000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_Gps,Null,"Task_Gps",2000},
{Task_AutoPrintf,Null,"Task_AutoPrintf",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList TaskList_dancidayin[]={
{Task0,Null,"Task0",2000},
{TaskFunc1,Null,"TaskFunc",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_KeyBoard,Null,"Task_KeyBoard",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{TaskPlan,Null,"TaskPlan",2000},
{Task_M26,Null,"GPRS",14000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_Gps,Null,"Task_Gps",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList TaskList_yuezongwenshidu[]={//岳总
{Task0,Null,"Task0",2000},
{TaskFunc,Null,"TaskFunc",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_KeyBoard,Null,"Task_KeyBoard",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{TaskPlan1,Null,"TaskPlan",2000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_Sensor,Null,"Task_Gps",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList TaskList_yuezongguangzhao[]={//岳总
{Task0,Null,"Task0",2000},
{TaskFunc,Null,"TaskFunc",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_KeyBoard,Null,"Task_KeyBoard",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{TaskPlan1,Null,"TaskPlan",2000},
{Task_M26,Null,"GPRS",14000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_SensorBLX,Null,"Task_Gps",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList TaskList_zongfushe[]={//岳总
{Task0,Null,"Task0",2000},
{TaskFunc,Null,"TaskFunc",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_KeyBoard,Null,"Task_KeyBoard",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{TaskPlan1,Null,"TaskPlan",2000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_SensorFuShe,Null,"Task_Gps",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList TaskList_kaiguanliang[]={
{Task0,Null,"Task0",2000},
{TaskFunc,Null,"TaskFunc",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_KeyBoard,Null,"Task_KeyBoard",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{TaskPlan2,Null,"TaskPlan",2000},
{Task_M26KGL,Null,"GPRS",14000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_SensorGPIO,Null,"Task_Gps",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList TaskList_liuliang[]={
{Task0,Null,"Task0",2000},
{TaskFunc,Null,"TaskFunc",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_KeyBoard,Null,"Task_KeyBoard",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{TaskPlan3,Null,"TaskPlan",2000},
{Task_M26LL,Null,"GPRS",14000},
{Task_Arrary,Null,"Task_Arrary",2000},
//{Task_Gps,Null,"Task_Gps",2000},
{Task_Liuliang,Null,"Task_Gps",2000},
{Task_AutoReset,Null,"Task_AutoReset",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList TaskList_http[]={
{Task0,Null,"Task0",2000},
{TaskFunc,Null,"TaskFunc",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_KeyBoard,Null,"Task_KeyBoard",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{TaskPlan,Null,"TaskPlan",2000},
{Task_M26HTTP,Null,"GPRS",14000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_Gps,Null,"Task_Gps",2000},
{Task_HistoryRecord,Null,"Task_HistoryRecord",2000},
{Null},
};
const GPIO_InitStruct IO_ISL1208_List[]=
{
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOC,GPIO_Pin_3},//SDA
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_2},//SCL
	{0},
}; 
const GPIO_InitStruct IO_Control_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_2|GPIO_Pin_12|GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_13},
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_9|GPIO_Pin_8},
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOC,GPIO_Pin_6|GPIO_Pin_7},
	{GPIO_Speed_50MHz,GPIO_Mode_IPD,GPIOA,GPIO_Pin_0},
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOA,GPIO_Pin_8}, 
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOC,GPIO_Pin_1|GPIO_Pin_0},
	{GPIO_Speed_50MHz,GPIO_Mode_IN_FLOATING,GPIOB,GPIO_Pin_4|GPIO_Pin_5},
	{0},
};

int main(void)
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x5000);
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_Uart(USART1,100,100);
	DeviceMount_Usart(USART2);
	DeviceMount_ISL1208(IO_ISL1208_List);
	DeviceMount_IO(IO_Control_List);
	DeviceMount_W25Q16();
	DeviceMount_HT1621();
	Load_AppConfig(&UIShowValue.SaveValue,0);
	switch(UIShowValue.SaveValue.DeviceType)
	{
		case 0:DeviceMount_Usart(USART3);Tos_ListCreate(TaskList_putong);break;
		case 1:DeviceMount_Usart(USART3);Tos_ListCreate(TaskList_zidongdayin);break;
		case 2:DeviceMount_Usart(USART3);Tos_ListCreate(TaskList_dancidayin);break;
		case 3:DeviceMount_Usart(USART3);Tos_ListCreate(TaskList_yuezongwenshidu);break;
		case 4:DeviceMount_Usart(USART3);Tos_ListCreate(TaskList_yuezongguangzhao);break;
		case 5:DeviceMount_Usart(USART3);Tos_ListCreate(TaskList_zongfushe);break;
		case 6:DeviceMount_Usart(USART3);Tos_ListCreate(TaskList_kaiguanliang);break;
		case 7:DeviceMount_Usart(UART4);Tos_ListCreate(TaskList_liuliang);break;
		case 8:DeviceMount_Usart(UART4);Tos_ListCreate(TaskList_http);break;
		case 9:DeviceMount_Usart(USART3);Tos_ListCreate(TaskList_adddiaodianbutton);break;
		default:DeviceMount_Usart(USART3);Tos_ListCreate(TaskList_putong);break;
	}
	Tos_ListCreate(TaskList_putong);//这里选个哪个子项目任务表，少不了各种修改
	while(1);
}



