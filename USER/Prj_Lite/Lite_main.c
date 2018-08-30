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

#include <..\USER\Prj_Lite\OLED_SSD1306_Driver.c>



void Task0(void *Tags)
{
	
	Remap_SWJ_JTAGDisable();
	DeBug_OutSet(DeBug_USART1);
	LCD_Init();
	while(1)
	{
		
		Tos_TaskDelay(100); 
    LCD_Clear(0x00);
		Tos_TaskDelay(100); 
    LCD_Show(bmp1);
	}
}
void Task1(void *Tags)
{
	while(1)
	{
		
		Tos_TaskDelay(100);
		GPIO_SetIndex(0,1);
		Tos_TaskDelay(100);
		GPIO_SetIndex(0,0);
	}
}

const TaskInitList TaskList[]={
{Task0,Null,"Task0",1000},
{Task1,Null,"Task1",1000},
{Null}, 
};

const GPIO_InitStruct IO_Control_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB, GPIO_Pin_8},
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA, GPIO_Pin_10},
	{0},
};

int main(void)
{
	//NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x5000);
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_Usart(USART1);
	DeviceMount_GPIO(IO_Control_List);
	DeviceMount_LCD();
	Tos_ListCreate(TaskList);
	while(1);
}


