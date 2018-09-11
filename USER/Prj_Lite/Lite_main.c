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

#include <..\USER\Prj_Lite\Image.c>
#include <..\USER\Prj_Lite\Image_Bat.c>
#include <..\USER\Prj_Lite\Image_Action.c>
#include <..\USER\Prj_Lite\LCD_IPS_Driver.c>


//#include <..\USER\Prj_Lite\OLED_SSD1306_Driver.c>



void Task0(void *Tags)
{
	
	Remap_SWJ_JTAGDisable();
	LCD_Init();
//	Tos_TaskDelay(1);
	Lcd_Clear(0xff);
	//Lcd_DrawBMP(0,0,gImage_Temp);
	while(1)
	{
		
	//	
		
		Lcd_DrawBMP(0,33,gImage_centerbar);
		Lcd_DrawBMP(0,33,gImage_centerbar);
		
		
		Tos_TaskDelay(5000); 
	}
}
void Task1(void *Tags)
{
	while(1)
	{
		Tos_TaskDelay(2);
		GPIO_SetIndex(0,1);
		Tos_TaskDelay(100);
		GPIO_SetIndex(0,0);
	}
}
void Task2(void *Tags)
{
	while(1)
	{
		Lcd_DrawBMP(130,2,gImage_bat1);
		Tos_TaskDelay(200);
		Lcd_DrawBMP(130,2,gImage_bat2);
		Tos_TaskDelay(300);
		Lcd_DrawBMP(130,2,gImage_bat3);
		Tos_TaskDelay(300);
		Lcd_DrawBMP(130,2,gImage_bat4);
		Tos_TaskDelay(300);
		Lcd_DrawBMP(130,2,gImage_bat5);
		Tos_TaskDelay(300);
		Lcd_DrawBMP(130,2,gImage_bat6);
		Tos_TaskDelay(300);
	}
}
void Task3(void *Tags)
{
	uint8_t z;
	while(1)
	{
		for(z=0;z<133;z++)
		{
			Tos_TaskDelay(10);
			Lcd_DrawBMP(z,27,gImage_topbar);
		}
		for(z=133;z>0;z--)
		{
			Tos_TaskDelay(10);
			Lcd_DrawBMP(z,27,gImage_topbar);
		}
	}
}
void Task4(void *Tags)
{
	uint8_t z;
	Tos_TaskDelay(700);
	while(1)
	{
		
		Lcd_DrawBMP(0,45,gImage_block1);
		for(z=0;z<150;z++)
		{
			Tos_TaskDelay(4);
			Lcd_DrawBMP(z,39,gImage_buttonbar);
			if(z==12)Tos_TaskDelay(700);
			if(z==(12+1*30))Tos_TaskDelay(700);
			if(z==(12+2*30))Tos_TaskDelay(700);
			if(z==(12+3*30))Tos_TaskDelay(700);
			if(z==(12+4*30))Tos_TaskDelay(700);
		}
		Lcd_DrawBMP(0,45,gImage_block2);
		for(z=150;z>0;z--)
		{
			Tos_TaskDelay(4);
			Lcd_DrawBMP(z,39,gImage_buttonbar);
			if(z==12)Tos_TaskDelay(700);
			if(z==(12+1*30))Tos_TaskDelay(700);
			if(z==(12+2*30))Tos_TaskDelay(700);
			if(z==(12+3*30))Tos_TaskDelay(700);
			if(z==(12+4*30))Tos_TaskDelay(700);
		}
	}
}
void Task5(void *Tags)
{
	uint8_t z;
	while(1)
	{
		Tos_TaskDelay(100);
		Lcd_DrawBMP(0,0,gImage_gear1);
		Tos_TaskDelay(100);
		Lcd_DrawBMP(0,0,gImage_gear3);
	}
}
const TaskInitList TaskList[]={
{Task0,Null,"Task0",1000},
{Task1,Null,"Task1",1000},
{Task2,Null,"Task2",1000},
{Task3,Null,"Task3",1000},
{Task4,Null,"Task4",1000},
{Task5,Null,"Task5",1000},
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
	DeviceMount_GPIO(IO_Control_List);
	DeviceMount_LCD();
	Tos_ListCreate(TaskList);
	while(1);
}


