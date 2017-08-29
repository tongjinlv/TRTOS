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
#include <SX1278_Driver.c>
#include <..\USER\Prj_Geek_Bast\IO_Driver.c>
#include <..\USB\STM32_USB-FS-Device_Driver\USB_FS_Device_Driver.c>
#include <..\USER\Prj_Geek_Bast\usb_desc.c>
#include <..\USER\Prj_Geek_Bast\hw_config.c>
#include <..\USER\Prj_Geek_Bast\usb_endp.c>
#include <..\USER\Prj_Geek_Bast\usb_istr.c>
#include <..\USER\Prj_Geek_Bast\usb_prop.c>
#include <..\USER\Prj_Geek_Bast\usb_pwr.c>
#include <..\Driver\Virtual_Usart.c>
#include <..\USER\Prj_Geek_Bast\Explainer.c>
typedef struct Text
{
	struct Text *NextAddr;
	char  Line;
}Text;
void Task0(void *Tags)
{
	Remap_SWJ_JTAGDisable();
	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;
	Tos_TaskDelay(100);
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	while(1)
	{	
	Tos_TaskDelay(1000);
	LED5_ON;
	Tos_TaskDelay(100);
	LED5_OFF;
	}
}
Text *TT;

void Task1(void *Tags)
{
	Text *T;
	Set_System();
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
	while(1)
	{
		Tos_TaskDelay(1000);
		T=TT;
		while(T!=0)
		{
	//	DeBug(&T->Line,4);
		Bast_Export(&T->Line);
		T=T->NextAddr;
		}
	}
}

void Text_Join(Text **tt,uint8 *Str)
{
	Text *t=*tt,**oldT=tt;
	uint8 Length;
	Length=GetTextLength(Str);
	if((*oldT)==0)
	{
		(*oldT)=Mema_Malloc(Length+5);
		(*oldT)->NextAddr=0;
		StringCoppy(Str,&(*oldT)->Line);
		return;
	}
	while(t->NextAddr!=0)
	{
		t=t->NextAddr;
	}
	t->NextAddr=Mema_Malloc(Length+5);
	StringCoppy(Str,&t->NextAddr->Line);
	t->NextAddr->NextAddr=0;
}

void Usart_CallBack(void *Str,uint8 Length)
{
	VisualCOM_Writes(Str,Length);
}

void Task2(void *Tags)
{
	Set_System();
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
	DeBug_SetCallBack(Usart_CallBack);
	Text_Join(&TT,"task1\n");
	Text_Join(&TT,"port.cfg(pc0,out)\n");
	Text_Join(&TT,"loop\n");
	Text_Join(&TT,"{\n");
	Text_Join(&TT," delay.ms.1000\n");
	Text_Join(&TT," port.set(pc0,0)\n");
	Text_Join(&TT," delay.ms.1000\n");
	Text_Join(&TT," port.set(pc0,1)\n");
	Text_Join(&TT,"}\n");
	while(1)
	{
		
		Tos_TaskDelay(100);
	}
}
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  USB_Istr();
}

Text *TTT;
void Task3(void *Tags)
{
	Text *T;
	Text_Join(&TTT,"task1\n");
	Text_Join(&TTT,"port.cfg(pc1,out)\n");
	Text_Join(&TTT,"port.cfg(pc2,out)\n");
	Text_Join(&TTT,"port.cfg(pc3,out)\n");
	Text_Join(&TTT,"loop\n");
	Text_Join(&TTT,"{\n");
	Text_Join(&TTT," port.set(pc1,0)\n");
	Text_Join(&TTT," delay.ms.10\n");
	Text_Join(&TTT," port.set(pc1,1)\n");
	Text_Join(&TTT," port.set(pc2,1)\n");
	Text_Join(&TTT," delay.ms.1000\n");
	Text_Join(&TTT," port.set(pc2,0)\n");
	Text_Join(&TTT," port.set(pc3,0)\n");
	Text_Join(&TTT,"}\n");
	Tos_TaskDelay(10);
	

	
	while(1)
	{
		T=TTT;
		while(T!=0)
		{
		//DeBug(&T->Line,4);
		Bast_Export(&T->Line);
	  T=T->NextAddr;
		}
	}
}

int SysTime;
void Task4(void *Tags)
{
		uint8_t i;
	Tos_TaskDelay(5000);
	SpiInit();
	DeBug("Init",4);
	i=80;
	while(i--)
	{
		SPIWrite((uint16)i<<8+0xff);
		DeBug("Version=%02x ",SPIRead(i),4);
		Tos_TaskDelay(100);
	}
	while(1)
	{
		i=SPIRead(REG_LR_VERSION>>8);//获取SX1276 版本号 0X11(V1A版本 工程版）或者0X12（V1B 正式版）
		DeBug("Version=%02x ",i,4);
		if(i==0x12)break;
		if(i==0x36)break;
		Tos_TaskDelay(1000);
	}
	SX1276_Parameters_Select(0x12);
	while(1)
	{
	  SX1276_LoRaEntryTx();
    SX1276_LoRaTxPacket();
    Tos_TaskDelay(4000);
		DeBug("Send",4);
    SX1276_LoRaClearIrq(); //Clear irq
    SX1276_Standby(); //Entry Standby mode  
		Tos_TaskDelay(1000);
	}
}
const TaskInitList TaskList[]={
{Task0,Null,"Task0",2000},
{Task1,Null,"Task0",2000},
{Task2,Null,"Task0",2000},
{Task3,Null,"Task0",2000},
{Task4,Null,"Task0",2000},
{Task_Arrary,Null,"Task_Arrary",2000},
{Task_GetKeyVirtual,Null,"Key",2000},
{Null},
};
const GPIO_InitStruct IO_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_AF_OD,GPIOC,GPIO_Pin_0},//D0时钟
	{GPIO_Speed_2MHz,GPIO_Mode_AF_OD,GPIOC,GPIO_Pin_1},//D1数据
	{GPIO_Speed_2MHz,GPIO_Mode_AF_OD,GPIOC,GPIO_Pin_2},//RES复位
	{GPIO_Speed_2MHz,GPIO_Mode_AF_OD,GPIOC,GPIO_Pin_3},//DC数据命令选择
	{GPIO_Speed_2MHz,GPIO_Mode_AF_OD,GPIOA,GPIO_Pin_15},//CS片选
	{GPIO_Speed_2MHz,GPIO_Mode_AF_OD,GPIOC,GPIO_Pin_4},//CS片选
	{0},
};

int main(void)
{
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_IO(IO_List);
	Tos_ListCreate(TaskList);
	while(1);
}



