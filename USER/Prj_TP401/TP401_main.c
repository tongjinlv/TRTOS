/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <Tos_Mema.h>
#include <FuncTask_Include.h>
#include <isl1208_driver.h>
#include <IIC_Driver.c>
#include <GPIO_Driver.h>
#include <Key_Driver.c>
#include <..\USER\Prj_TP401\IO_Driver.c>
#include <..\USER\Prj_TP401\Ht1621_Driver.c>
#include <..\USER\Prj_TP401\Ht1621_Face.c>
#include <..\USER\Prj_TP401\TempHui_Driver.c>
#include <..\USER\Prj_TP401\App_Sensor.c>
#include <W25Q16_Driver.c>
#include <isl1208_driver.c>
#include <..\USER\Prj_TP401\App1.h>
#include <..\USER\Prj_TP401\ADC_Driver.c>
#include <..\USER\Prj_TP401\App2.c>
#include <..\USER\Prj_TP401\App.c>
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
	Remap_SWJ_JTAGDisable();
	Task0_Init();
	UIShowValue.SysWorkMode=0;
	GPIO_SetIndex(0,1);
	Tos_TaskDelay(4);
	GPIO_SetIndex(0,0);
	GPIO_SetIndex(3,1);
	while(1)
	{
		
		if((UIShowValue.RunFlag&WRF_CH1Max)|(UIShowValue.RunFlag&WRF_CH1Min)|(UIShowValue.RunFlag&WRF_CH2Max)|(UIShowValue.RunFlag&WRF_CH2Min))
		{
			Tos_TaskDelay(200);
			GPIO_SetIndex(1,1);
			GPIO_SetIndex(2,1);
			Tos_TaskDelay(200);
			GPIO_SetIndex(1,0);
			GPIO_SetIndex(2,0);
		}else 
		{
			Tos_TaskDelay(1);
			GPIO_SetIndex(1,1);
			GPIO_SetIndex(2,1);
			Tos_TaskDelay(1500);
			GPIO_SetIndex(1,0);
			GPIO_SetIndex(2,0);
		}
	}
}
void Task_LCD(void *Tags)
{
	while(1)
	{
		Tos_TaskDelay(1000);
		
//		Ht1621_ShowASCII(0,Ht1621CodeDownList[i]);

	//	Ht1621_SHowDownString(&Buf[0]);
	//	Ht1621_SHowUpString(&Buf[0]);
//		Ht1621_ShowASCII(6,S0<<i);
		LCD_BUF[0]|=S3;//�½���ͷ
		LCD_BUF[1]|=S3;//������ͷ
	//	LCD_BUF[2]|=S3;//��С����
		LCD_BUF[3]|=S3;//��ʪ�ȵ�λ
			LCD_BUF[4]|=S3;//���µ�λ
			LCD_BUF[8]|=S3;//������ͷ
			LCD_BUF[7]|=S3;//�Ͻ���ͷ
			//LCD_BUF[9]=0xff;//����ź�
		  LCD_BUF[9]|=S0;//��ر߿�
			LCD_BUF[9]|=S1;//���һ��
			LCD_BUF[9]|=S2;//��ض���
		  LCD_BUF[9]|=S3;//�������
			LCD_BUF[9]|=S4;//�ź�һ��
			LCD_BUF[9]|=S5;//�źŶ���
			LCD_BUF[9]|=S6;//�ź�����
			LCD_BUF[9]|=S7;//�ź��ĸ�
			//LCD_BUF[10]=0xff;//AB WIFI �״�
			LCD_BUF[10]|=S0;//wifi ����Ȧ
			LCD_BUF[10]|=S1;//B
			LCD_BUF[10]|=S2;//A
		//	LCD_BUF[10]|=S3;//�հ�
			LCD_BUF[10]|=S4;//�״�
			LCD_BUF[10]|=S5;//wifi ����
			LCD_BUF[10]|=S6;//wifi �κ���
			LCD_BUF[10]|=S7;//wifi ����Ȧ
			LCD_BUF[11]=0xff;//�����˼�1 
			LCD_BUF[12]=0xff;//�����˼�2
			//LCD_BUF[13]=0xff;//��һ�˼�3
//			LCD_BUF[14]=0xff;//��һ��
//			LCD_BUF[15]=0xff;//�¶��˼Ӻ��
//			LCD_BUF[16]=0xff;//������
//			LCD_BUF[17]=0xff;//���İ˼Ӻ��
//			LCD_BUF[18]=0xff;//��һ��
	}
}

void Task_Face(void *Tags)
{
	uint8 i;
	GPIO_SetIndex(0,1);
	Tos_TaskDelay(1);
	GPIO_SetIndex(0,0);
	GPIO_SetIndex(11,0);//3V3ʹ��
	Tos_TaskDelay(100);
	HT1621_Init();
	for(i=0;i<54;i++)Ht1621_WriteReg(i, 0xff);//ȫ��
	Tos_TaskDelay(1000);
	for(i=0;i<54;i++)Ht1621_WriteReg(i, 0x0);//ȫ��
	i=0;
	BufferFill(&LCD_BUF[0],0x00,sizeof(LCD_BUF));
	while(1)
	{
		 switch(UIShowValue.SysWorkMode)
		{
			case 0:Ht1621_DrawHome();break;
			case 1:Ht1621_DrawMaxMin(1);break;
			case 2:Ht1621_DrawMaxMin(2);break;
			case 3:Ht1621_DrawMaxMin(3);break;
			case 4:Ht1621_DrawMaxMin(4);break;
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

uint8 HandKey_GetValue()
{
	uint8 Value=0x00;
	uint16 Temp;
	Temp=GPIO_GetAll();
  if(!(Temp&S4)){Value=Key_Up;}
	if(!(Temp&S5)){Value=Key_Down;}
	if(!(Temp&S6)){Value=Key_Right;}
	if(!(Temp&S7)){Value=Key_Enter;}
	if((Temp&S8)){Value=Key_WkUp;}
	return Value;
}

const TaskInitList TaskList_putong[]={
{Task0,Null,"Task0",2000},
//{Task_LCD,Null,"Task0",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_Action,Null,"Task_Action",2000},
{Task_SendZB,Null,"Task_Action",2000},
{Task_KeyBoard,HandKey_GetValue,"Task_KeyBoard",2000},
{TaskPlan_1,Null,"Task_Face",2000},
{Task_Arrary,(void *)2,"Task_Arrary",2000},
{Task_HistoryRecord1,Null,"Task_HistoryRecord",2000},
{Null},
};
const TaskInitList TaskList_liulinag[]={
{Task0,Null,"Task0",2000},
{Task_LCD,Null,"Task0",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_GetLora,Null,"Task_GetLora",2000},
{Task_Getsupersong,Null,"Task_Arrary",2000},
{Task_Arrary,(void *)2,"Task_Arrary",2000},
{Null},
};
const TaskInitList TaskList_touchuan[]={
{Task0,Null,"Task0",2000},
{Task_LCD,Null,"Task0",2000},
//{Sensor_Command,USART1,"Sensor_Command",2000},
{Task_ZBTo485,USART1,"Task_GetLora",2000},
{Task_ZBTo485,USART2,"Task_GetLora",2000},
{Task_485ToZB,Null,"Task_Arrary",2000},
{Task_Arrary,(void *)2,"Task_Arrary",2000},
{Null},
};
const TaskInitList TaskList_zidongdayin[]={
{Task0,Null,"Task0",2000},
//{TaskFunc,Null,"TaskFunc",2000},
{Task_Face,Null,"Task_Face",2000},
{Task_KeyBoard,Null,"Task_KeyBoard",2000},
{Sensor_Command,USART1,"Sensor_Command",2000},
//{TaskPlan,Null,"TaskPlan",2000},
{Task_Arrary,Null,"Task_Arrary",2000},
//{Task_Gps,Null,"Task_Gps",2000},
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
const GPIO_InitStruct IO_TP401_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_0},//��0��������
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_11},//��1����ߵ�
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_12},//��2���ұߵ�
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_1},//��3������
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOC,GPIO_Pin_7},//��4������A
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOC,GPIO_Pin_8},//��5������B
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOB,GPIO_Pin_14},//��6������C
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOB,GPIO_Pin_15},//��7������D
	{GPIO_Speed_2MHz,GPIO_Mode_IPD,GPIOA,GPIO_Pin_0},//��8������WKUP
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_7},//��9��UR485TXEN�ɰ汾
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_13},//��10��UR485TXEN�°汾
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_9},//��11��3V3En
//	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_6},//��12��������
	{0},
};
int main(void)
{
	//NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x5000);
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_Usart(USART1);
	DeviceMount_Usart(USART2);
	DeviceMount_Usart(USART3);
	DeviceMount_ISL1208(IO_ISL1208_List);
	DeviceMount_W25Q16();
	DeviceMount_HT1621();
	DeviceMount_GPIO(IO_TP401_List);
	Load_AppConfig(&UIShowValue.SaveValue,0);
	switch(UIShowValue.SaveValue.DeviceType)
	{
		case 0:Tos_ListCreate(TaskList_putong);break;
		case 1:Tos_ListCreate(TaskList_zidongdayin);break;
		case 2:Tos_ListCreate(TaskList_liulinag);break;
		case 3:Tos_ListCreate(TaskList_touchuan);break;
		

	}
	Tos_ListCreate(TaskList_putong);
	while(1);
}




