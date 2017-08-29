/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <Tos_Mema.h>
#include <STM32L_CPU.h>
#include <GPIOL_Driver.h>
#include <Func_Face.h>
#include <..\USER\Prj_InsectV2\ADC_Driver.c>
#include <..\USER\Prj_InsectV2\PWM_Driver.c>
#include <..\USER\Prj_InsectV2\Moto_Driver.c>
#include <..\USER\Prj_InsectV2\WS2812_Driver.c>
//#include <..\USER\Prj_InsectV2\GD20_Driver.c>
//#include <..\USER\Prj_InsectV2\WKUP_Driver.c>
#include <..\USER\Prj_InsectV2\BEEP_Driver.c>
//#include <..\USER\Prj_InsectV2\IR_Driver.c>


//void BEEP()
//{
//	Beep_Test();
//}

//void Task0(void *Tags)
//{
//	
//	uint16 Data[7],i;
//	Remap_SWJ_JTAGDisable();
//	DeBug_OutSet(DeBug_USART1);
//	ADC1_Init((uintbus)&Data);
//	PwmTimeInt();
//	Moto_Follow(0);
//	GPIO_SetIndex(5,0);//关蜂鸣器
//	GPIO_SetIndex(2,0);//接近激励
//	GPIO_SetIndex(3,0);//接近激励
//	GPIO_SetIndex(6,1);//POW1
//	GPIO_SetIndex(7,1);//POW1
//	GPIO_SetIndex(0,1);//关EYE
//	GPIO_SetIndex(1,1);//关EYE
//	//WS_Double();
//	WS2812_Close();
//	while(1)
//	{
//		Tos_TaskDelay(500);
////		GPIO_SetIndex(0,0);
////		GPIO_SetIndex(1,0);
////		Tos_TaskDelay(100);
////		GPIO_SetIndex(0,1);
////		GPIO_SetIndex(1,1);
//	//	WS2812_Open();
//		DeBug("左接近[0]%d",Data[0],0);
//		DeBug("电压[1]%d",Data[1],0);
//		DeBug("右前方[2]%d",Data[2],0);
//		DeBug("右接近[3]%d",Data[3],0);
//		DeBug("中间[4]%d",Data[4],0);
//		DeBug("左边[5]%d",Data[5],0);
//		//if(Data[5]>3700)WS_Double();
//	//	if(Data[4]<1800)Moto_Follow(-2000);
//	}
//}

//void Task1(void *Tags)
//{
//	Beep_ON();
//	while(1)
//	{
//		GPIO_SetIndex(0,1);
//		GPIO_SetIndex(1,0);
//		Tos_TaskDelay(100);
//		GPIO_SetIndex(0,0);
//		GPIO_SetIndex(1,1);
//		Tos_TaskDelay(100);
//		
//		if(GPIO_GetIndex(14))
//		{
//			Beep_OFF();
//			GPIO_SetIndex(0,1);//关EYE
//			GPIO_SetIndex(1,1);//关EYE
//			Tos_TaskDelay(1000);
//			Standby_Init(True);
//		}
//		
//		
//	}
//}
////MMA8451Q_Init();



//void Task2(void *Tags)
//{
//	PwmTimeInt();
//	Moto_A(1,0);
//	Moto_B(1,0);
//	TestStart();
//	Moto.Begin();
//	while(1)
//	{
//		Moto_Right(200);
//		Tos_TaskDelay(100);
//		Moto_Right(-200);
//		Tos_TaskDelay(100);
//		Moto_Right(200);
//		Moto_Right(-200);
//		Moto_Follow(1000);
//		Moto_Right(-200);
//		Moto_Follow(1000);
//		Moto_Right(-200);
//		Moto_Follow(1000);
//		Moto_Right(-200);
//		Moto_Follow(-1000);
//		
//		Moto_Right(-100);
//		Moto_Follow(2000);
//		Moto_Right(-100);
//		Moto_Follow(2000);
//		Moto_Right(-100);
//		Moto_Follow(-2000);
//		WS_Double();
//	}
//}
//void Task_Power(void *Tags)
//{
//	Beep_ON();
//	while(1)
//	{
//		Tos_TaskDelay(1000);
//			if(GPIO_GetIndex(14))
//		{
//			Beep_OFF();
//			GPIO_SetIndex(0,1);//关EYE
//			GPIO_SetIndex(1,1);//关EYE
//			Tos_TaskDelay(1000);
//			Standby_Init(True);
//		}
//	}
//}
//const TaskInitList TaskList[]={
//{Task0,Null,"Task0",2000},
//{Task2,Null,"Task0",2000},
//{Task_IR,Null,"Task_IR",2000},
//{Task_Arrary,(void *)1,"Task0",2000},
//{Task_Power,Null,"Task0",2000},
//{Null},
//};
const GPIO_ListStruct IO_Control_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_OD,GPIOB,GPIO_Pin_8},//【0】EYE2
	{GPIO_Speed_2MHz,GPIO_Mode_Out_OD,GPIOB,GPIO_Pin_3},//【1】EYE2
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_15},//【2】接近驱动1
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_9},//【3】接近驱动2
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOC,GPIO_Pin_14},//【4】红外接收
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_13},//【5】蜂鸣器
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_0},//【6】POW1
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_1},//【7】POW2
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_6},//【8】BPWM
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_7},//【9】APWM
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_4},//【10】BIN1
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_5},//【11】AIN1
	{GPIO_Speed_40MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_15},//【12】WS1
	{GPIO_Speed_40MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_12},//【13】WS2
	{GPIO_Speed_40MHz,GPIO_Mode_IPD,GPIOA,GPIO_Pin_0},//【14】WKUP
	{GPIO_Speed_40MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_11},//【15】IR
	{GPIO_Speed_400KHz},
};

void Task_P(void *Tags)
{
	uint8 Buf[10];
	DeBug_OutSet(DeBug_USART1);
	while(1)
	{
		Tos_TaskDelay(1);
		USART_ReadDatas(USART1,Buf,10,0);
		DeBug((char *)Buf);
	}
}
void Task_Task0(void *Tags)
{
		uint16 Data[7];
	uint32 Cmd[4];
	GPIO_SetIndex(6,1);
	ADC1_Init((uintbus)&Data);
	//Beep_OFF();
	Pwm_Init();
	Moto_AB(-40,30);
	GPIO_SetIndex(1,1);
	while(1)
	{
		Tos_TaskDelay(1);
		GPIO_SetIndex(0,1);
		Tos_TaskDelay(1000);
		GPIO_SetIndex(0,0);
		DeBug("左接近[0]%d",Data[0],0);
		DeBug("电压[1]%d",Data[1],0);
		DeBug("右前方[2]%d",Data[2],0);
		DeBug("右接近[3]%d",Data[3],0);
		DeBug("中间[4]%d",Data[4],0);
		DeBug("左边[5]%d",Data[5],0);
		WS_Double();
		Cmd[0]=0x000000000;
		//WS2812_Write(Cmd);
	}
}
const TaskInitList TaskList[]={
{Task_Task0,Null,"Task0",2000},
{Task_P,Null,"Task0",2000},
{Null},
};
int main(void)
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x5000);//BOOT 与非BOOT的区别
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_Usart(USART1);
	DeviceMount_GPIO(IO_Control_List);
	Tos_ListCreate(TaskList);
	while(1);
}

