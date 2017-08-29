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
		//IR_Send();
//		GPIO_SetIndex(0,0);
//		GPIO_SetIndex(1,0);
//		Tos_TaskDelay(100);
//		GPIO_SetIndex(0,1);
//		GPIO_SetIndex(1,1);
//		DeBug("左接近[0]%d",UIShowValue.ADC[0],0);
	//	DeBug("电压[1]%d",UIShowValue.ADC[0],0);
//		DeBug("右前方[2]%d",UIShowValue.ADC[2],0);
//		DeBug("右接近[3]%d",UIShowValue.ADC[3],0);
//		DeBug("中间[4]%d",UIShowValue.ADC[4],0);
//		DeBug("左边[5]%d",UIShowValue.ADC[5],0);
//		//if(Data[5]>3700)WS_Double();
	//	if(Data[4]<1800)Moto_Follow(-2000);
	}
}

void Task1(void *Tags)
{
	while(1)
	{
		Tos_TaskDelay(1000); 
		GPIO_SetIndex(0,0);
		GPIO_SetIndex(1,0);
		Tos_TaskDelay(10); 
		GPIO_SetIndex(0,1);
		GPIO_SetIndex(1,1);
		Tos_TaskDelay(100); 
		GPIO_SetIndex(0,0);
		GPIO_SetIndex(1,0);
		Tos_TaskDelay(10); 
		GPIO_SetIndex(0,1);
		GPIO_SetIndex(1,1); 
		
	}
}

uint8 GetKeyBoardValue()
{ 
	uint8 Value=0x00;
	if(GPIO_GetIndex(14))Value=Key_WkUp;
	if(GPIO_GetIndex(7))Value=Key_Enter;
	return Value;
}

void Task_Moto(void *Tags)
{
	while(1)
	{
		switch(UIShowValue.SaveValue.RunMode)
		{
			case 0:DeBug("radom=%d",RandomADC(80,-80),Infor_Warning);
						Moto_AB(RandomADC(80,-80),RandomADC(80,-80));
						Tos_TaskDelay(1000);
						Moto_Stop();
			break;
			case 1:WS_Double();Tos_TaskDelay(1000);break;
			case 2:Tos_TaskDelay(1000);WS_SetDot(0,0xff0000);WS_SetDot(1,0xff);break;
			case 3:Moto_AB(80,75);
					Tos_TaskDelay(1000);
					Moto_AB(80,40);
					Tos_TaskDelay(300);
					Moto_AB(40,80);
					Tos_TaskDelay(300);
					Moto_AB(80,75);
					Tos_TaskDelay(1000);
					Moto_AB(80,40);
					Tos_TaskDelay(300);
					Moto_AB(-80,-75);
					Tos_TaskDelay(1000);
					Moto_AB(40,80);
					Tos_TaskDelay(300);
					WS_SetDot(0,0xff00ff);
					WS_SetDot(1,0xffff00);break;
			case 4:Tos_TaskDelay(1000);WS_SetDot(0,0xff);WS_SetDot(1,0xff00);break;
			default:UIShowValue.SaveValue.RunMode=0;Tos_TaskDelay(1000);break;
		}
	}
}
void Task_Power(void *Tags)
{
	uint8 i;
	Tos_ArrayMessage Msg[5];
	MGUI_KeyMsg *TaskMsg,TaskMsgBuf[5];    
	for(i=0;i<5;i++)Msg[i].Qmsg_Addr=&TaskMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],5);
	Tos_TaskGetHandKey();
	//Beep_ON();
	TestStart();
	GPIO_SetIndex(7,0);//复用按钮输入
	while(1)
	{
		  TaskMsg=MUI_GetKey(0);
			if(TaskMsg)
			{
				 DeBug("KeyType=%d,Value=%d",TaskMsg->KeyType,TaskMsg->KeyValue,2);
				 if(TaskMsg->KeyValue==Key_Enter)if(TaskMsg->KeyType==Key_DownTimeOut)
				 {
					WS_SetColorBit(0xffffff,S0|S1|S2|S3);
					Beep_OFF();
					WS_SetColorBit(0x0,S0|S1|S2|S3);
					Tos_TaskDelay(1000);
					while(1)
					{
					GPIO_SetIndex(6,0);
					}
				 }
				 if(TaskMsg->KeyValue==Key_Enter)if(TaskMsg->KeyType==Key_OneClick)
				 {
					 UIShowValue.SaveValue.RunMode++;
					 WS_ShadeBit(0xff0000,0x00,S2|S3);
					 System_SaveConfig();
					 Moto_AB(0,0);
				 }
				 if(TaskMsg->KeyValue==Key_WkUp)if(TaskMsg->KeyType==Key_OneClick)
				 {
					 RandomEYE();//眼睛随机渐变亮
				 }
				 if(TaskMsg->KeyValue==Key_WkUp)if(TaskMsg->KeyType==Key_DownTimeOut)
				 {
					 WS_ShadeBit(0x000000,0xff,S2|S3);
					 WS_ShadeBit(0xff,0x000000,S2|S3);
				 }
			}
				
	
	}
}
void Task_Power1(void *Tags)
{
	uint8 i;
	Tos_ArrayMessage Msg[5];
	MGUI_KeyMsg *TaskMsg,TaskMsgBuf[5];    
	for(i=0;i<5;i++)Msg[i].Qmsg_Addr=&TaskMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],5);
	Tos_TaskGetHandKey();
	GPIO_SetIndex(7,0);//复用按钮输入
	
	while(1)
	{
		  TaskMsg=MUI_GetKey(0);
			if(TaskMsg)
			{
				DeBug("%d,%d",TaskMsg->KeyType,TaskMsg->KeyValue,2);
				 if(TaskMsg->KeyValue==Key_Enter)if(TaskMsg->KeyType==Key_DownTimeOut)
				 {
					WS_SetColorBit(0xffffff,S0|S1|S2|S3);
					Beep_OFF();
					WS_SetColorBit(0x0,S0|S1|S2|S3);
					Tos_TaskDelay(1000);
					while(1)
					{
					GPIO_SetIndex(6,0);
					}
				 }
			}
				
	
	}
}
const TaskInitList TaskList[]={
{Task0,Null,"Task0",1000},
{Task1,Null,"Light",1000},
{Task_Moto,Null,"Task_Moto",1000},
{Task_Gyro,&UIShowValue.Gyro,"Task_Gyro",1000},
{TempHmi,Null,"Task_TempHmi",1000},
{Task_KeyBoard,GetKeyBoardValue,"Task_KeyBoard",1000},
{Task_IR,Null,"Task_IR",1000},
//{Sensor_Command,USART1,"Sensor_Command",1000},
{Task_Arrary,(void *)1,"Task_Arrary",1000},
{Task_Power,Null,"Task_Power",1000},
{Null}, 
};
const TaskInitList TaskList1[]={
{Task_GIDE,USART1,"Task0",1000},
//{Task1,Null,"Task0",1000},
{Task_KeyBoard,GetKeyBoardValue,"Task_KeyBoard",500},
{Task_Read,&UIShowValue.Gyro,"Task_Gyro",1000},
{Task_Arrary,(void *)1,"Task_Arrary",500},
{Task_Power1,Null,"Task_Power",500},
{Null}, 
};
const TaskInitList TaskList_App1[]={
{Task0,Null,"Task0",1000},
//{Task1,Null,"Light",1000},
{Task_KeyBoard,GetKeyBoardValue,"Task_KeyBoard",1000},
//{Task_IR,Null,"Task_IR",1000},
//{Sensor_Command,USART1,"Sensor_Command",1000},
{Task_Arrary,(void *)1,"Task_Arrary",1000},
{Task_Power_App1,Null,"Task_Power",1000},
{Task_Power_App2,Null,"Task_Power",1000},
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
	{GPIO_Speed_50MHz,GPIO_Mode_IPD,GPIOA,GPIO_Pin_2},//【16】掉电监测
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
	Tos_ListCreate(TaskList1);
	while(1);
}


