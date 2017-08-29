/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Tools_Include.h>
#include <Driver_Include.h>
#include <App_Sensor.h>
#include <..\USER\Prj_TP502T\Sensor_Driver.h>
#include <..\USER\Prj_TP502T\App2.h>
#include <CPU.h>
#include <GPIO_Driver.h>
#include <FuncTask_Include.h>
#include <IAP_Driver.h>
#include <..\USER\Prj_Boot\BootLoader.h>
#include <..\Driver\SZZigBee_Driver.h>
#include <..\USER\Prj_Boot\BootLoader.c>
#include <..\Driver\SZZigBee_Driver.c>
#include <StandardModBus.h>


char *String_Ok="OK";
uint8 tem;
extern void BEEP_Double(void);
const char BoolString[2][6]={"False","True"};//���ܷ����ӳ���������δ֪����
const COM_MenuStruct MenuList[]={
	{"��������",(void *)&System_SaveConfig,VT_Task,Null},
	{"��ȡ����",(void *)&Task_LoadConfigs,VT_Task,Null},
	{"�����豸",(void *)&System_Reset,VT_Task,Null},
	{"����֪ͨ�绰[1]:%s",(void *)&UIShowValue.SaveValue.CallNumber[0][0],VT_Str,sizeof(UIShowValue.SaveValue.CallNumber[0])},
	{"����֪ͨ�绰[2]:%s",(void *)&UIShowValue.SaveValue.CallNumber[1][0],VT_Str,sizeof(UIShowValue.SaveValue.CallNumber[0])},
	{"����֪ͨ�绰[3]:%s",(void *)&UIShowValue.SaveValue.CallNumber[2][0],VT_Str,sizeof(UIShowValue.SaveValue.CallNumber[0])},
	{"��������ַ[1]:%s",(void *)&UIShowValue.SaveValue.DomainName[0][0],VT_Str,sizeof(UIShowValue.SaveValue.DomainName[0])},
	{"����˿ں�:%d",(void *)&UIShowValue.SaveValue.ServerPort[0],VT_Uint16,sizeof(UIShowValue.SaveValue.ServerPort[0])},
	{"��¼��(���к�):%s",(void *)&UIShowValue.SaveValue.LoginHead[0],VT_Str,sizeof(UIShowValue.SaveValue.LoginHead)},
	{"��ӡ��(�û���):%s",(void *)&UIShowValue.SaveValue.PrintfName[0],VT_Str,sizeof(UIShowValue.SaveValue.PrintfName)},
	{"��ӡ����(��ͷ):%s",(void *)&UIShowValue.SaveValue.PrintfTitle[0],VT_Str,sizeof(UIShowValue.SaveValue.PrintfTitle)},
	{"ͨ��[1]��������:%.2f��/%%",(void *)&UIShowValue.SaveValue.CH_Limit[0].Max,VT_Float,Null},
	{"ͨ��[1]��������:%.2f��/%%",(void *)&UIShowValue.SaveValue.CH_Limit[0].Min,VT_Float,Null},
	{"ͨ��[2]��������:%.2f��/%%",(void *)&UIShowValue.SaveValue.CH_Limit[1].Max,VT_Float,Null},
	{"ͨ��[2]��������:%.2f��/%%",(void *)&UIShowValue.SaveValue.CH_Limit[1].Min,VT_Float,Null},
	{"��ӡ������(Ĭ��1):%d",(void *)&UIShowValue.SaveValue.DeBugCFG,VT_Uint8,Null},
	{"�ϴ�����(��):%d",(void *)&UIShowValue.SaveValue.SendCycle,VT_Uint8,Null},
	{"�����ӳ�(��):%d",(void *)&UIShowValue.SaveValue.SendSMSDelay,VT_Uint8,Null},
	{"��¼����(��):%d",(void *)&UIShowValue.SaveValue.RecordCycle,VT_Uint8,Null},
	{"��ӡ����(��):%d",(void *)&UIShowValue.SaveValue.PrintfCycle,VT_Uint8,Null},
	{"TCP-JЭ��֧��(True):%s",(void *)&UIShowValue.SaveValue.WorkBit,VT_U32BIT,5},
	{"DTH11������(True):%s",(void *)&UIShowValue.SaveValue.WorkBit,VT_U32BIT,6},
	{"ͨ��[1]����:%.2f��/%%",(void *)&UIShowValue.SaveValue.CorrectValue[0],VT_Float,Null},
	{"ͨ��[2]����:%.2f��/%%",(void *)&UIShowValue.SaveValue.CorrectValue[1],VT_Float,Null},
	{"ͨ��[1]ʵʱ����:%.2f��/%%",(void *)&UIShowValue.CH_Value[0],VT_Float,Null},
	{"ͨ��[2]ʵʱ����:%.2f��/%%",(void *)&UIShowValue.CH_Value[1],VT_Float,Null},
	{"ͨ��[3]��ص�ѹ:%.2fV",(void *)&UIShowValue.CH_Value[2],VT_Float,Null},
	{"ͨ��[4]GPRS�ź�ǿ��:%dasu",(void *)&UIShowValue.RSSI,VT_Uint8,Null},
	{"��⵽SIM��:%s",(void *)&UIShowValue.RunFlag,VT_U32BIT,5},
	{"����ʱ��(True):%s",(void *)&UIShowValue.SaveValue.WorkBit,VT_U32BIT,8},
	{"�绰����(True):%s",(void *)&UIShowValue.SaveValue.WorkBit,VT_U32BIT,9},
	{"��ʷ��¼(True):%s",(void *)&UIShowValue.SaveValue.WorkBit,VT_U32BIT,10},
	{"��������(��):%d",(void *)&UIShowValue.SaveValue.SleepMin,VT_Uint8,Null},
	{"�豸����(Ĭ��0):%d",(void *)&UIShowValue.SaveValue.DeviceType,VT_Uint8,Null},
	{"������ʾ(False):%s",(void *)&UIShowValue.SaveValue.WorkBit,VT_U32BIT,11},
	{"���籨��(False):%s",(void *)&UIShowValue.SaveValue.WorkBit,VT_U32BIT,12},
	{"�˵�",Null,VT_End,Null},
};
uint8 Menu_OptionLength(const COM_MenuStruct *CurMenu)
{
	uint8 Length=0;
	const COM_MenuStruct *Menu=CurMenu;
	while(Menu->Type!=VT_End)
	{
		Menu++;
		Length++;
	}
	return Length;
}
/*******************************************************************************
Func:�˵����¼�
Date:2016-3-25
Note:
*******************************************************************************/

uint8 COM_Menu_Enter(uint8 Index,uint8 *Buf)
{
	typedef   void 	(*FuncUint8)(uint8);
	const COM_MenuStruct *CurMenu;
	if(Index>=Menu_OptionLength(MenuList))return 0;
	CurMenu=&MenuList[Index];
	switch(CurMenu->Type)
	{
  		case VT_Task:if(CurMenu->Value)((Func)CurMenu->Value)();break;
//		case VT_TaskUint8:if(CurMenu->Value)((FuncUint8)CurMenu->Value)(CurMenu->Note);break;
		  case VT_Uint8:*(uint8 *)(CurMenu->Value)=GetStringToNumber(Buf);break;
  		case VT_Int8:*(int8 *)(CurMenu->Value)=GetStringToNumber(Buf);break;
  		case VT_Uint16:*(uint16 *)(CurMenu->Value)=GetStringToNumber(Buf);break;
			case VT_ROMUint32:*(uint32 *)(CurMenu->Value)=GetStringToNumber(Buf);break;
			case VT_Float:*(float *)(CurMenu->Value)=GetStringToNumber(Buf);break;
			case VT_U32BIT:if(Strstr((const char *)Buf,"T")>0)*(uint32 *)(CurMenu->Value)|=BIT(CurMenu->Note);else *(uint32 *)(CurMenu->Value)&=~BIT(CurMenu->Note);break;
			case VT_BOOL:if(Strstr((const char *)Buf,"T")>0)*(uint8 *)(CurMenu->Value)=True;else *(uint8 *)(CurMenu->Value)=False;break;
//		case VT_IP:*(uint32 *)(CurMenu->Value)=MUI_GetIP(*(uint32 *)(CurMenu->Value),IT_Num|IT_Dot);break;
//		case VT_Color:*(uint16 *)(CurMenu->Value)=MUI_GetColor(*(uint16 *)(CurMenu->Value),IT_Num|IT_Dot);break;
		case VT_Str:BufferCoppy(&Buf[0],(uint8 *)(CurMenu->Value),CurMenu->Note);break;
	}
	return 1;
}
void MUI_GetOptionString(char *Buf,const COM_MenuStruct *Menu)
{
	uint8 BufT[100];
	typedef   uint8 	(*Uint8Func)(void);
	if(Menu->Note){BufferCoppy((uint8 *)(Menu->Value),&BufT[0],Menu->Note);BufT[Menu->Note]=0x00;}
	else StringCoppy((uint8 *)(Menu->Value),&BufT[0]);
	switch(Menu->Type)
		{
			case VT_Menu:FmtToBuf(Buf,(char *)Menu->Option);break;
			case VT_Uint8:FmtToBuf(Buf,(char *)Menu->Option,*(uint8 *)(Menu->Value));break;
			case VT_Uint16:FmtToBuf(Buf,(char *)Menu->Option,*(uint16 *)(Menu->Value));break;
			case VT_Float:FmtToBuf(Buf,(char *)Menu->Option,*(float *)(Menu->Value));break;
			case VT_ROMUint8:FmtToBuf(Buf,(char *)Menu->Option,*(uint8 *)(Menu->Value));break;
			case VT_ROMStr:FmtToBuf(Buf,(char *)Menu->Option,(uint8 *)(Menu->Value));break;
			case VT_Str:FmtToBuf(Buf,(char *)Menu->Option,(uint8 *)(BufT));break;
			case VT_ROMUint32:FmtToBuf(Buf,(char *)Menu->Option,*(uint32 *)(Menu->Value));break;
		  case VT_Uint8Task:FmtToBuf(Buf,(char *)Menu->Option,((Uint8Func)Menu->Value)());break;
			case VT_BOOL:FmtToBuf(Buf,(char *)Menu->Option,BoolString[*(BOOL*)(Menu->Value)>0]);break;
			case VT_Int8:FmtToBuf(Buf,(char *)Menu->Option,*(int8 *)(Menu->Value));break;
			case VT_U32BIT:FmtToBuf(Buf,(char *)Menu->Option,BoolString[((*(uint32*)(Menu->Value))&BIT(Menu->Note))>0]);break;
			case VT_IP:FmtToBuf(Buf,(char *)Menu->Option,*(uint8 *)((uint32)Menu->Value+3),*(uint8 *)((uint32)Menu->Value+2),*(uint8 *)((uint32)Menu->Value+1),*(uint8 *)((uint32)Menu->Value));break;
			case VT_Color:FmtToBuf(Buf,(char *)Menu->Option,TFT_RGB(*(uint32 *)(Menu->Value)).R,TFT_RGB(*(uint32 *)(Menu->Value)).G,TFT_RGB(*(uint32 *)(Menu->Value)).B);break;
			default:FmtToBuf(Buf,(char *)Menu->Option);break;
		}
	
}

/*******************************************************************************
Func:�˵���ش�
Date:2016-3-25
Note:
*******************************************************************************/
uint8 COM_Menu_Load(uint8 Index,uint8 *Menu)
{
	uint8 Length;
	if(Index>=Menu_OptionLength(MenuList))return 0;
	MUI_GetOptionString((char *)Menu,&MenuList[Index]);
	Length=GetTextLength(Menu);
	return Length;
}


void Sensor_Command(void *Tags)
{
	uint16 Length;
	uint8 Buf[200],DataStart;
	ModBus_Message ModBusMsg;
	USART_TypeDef *USARTx=(USART_TypeDef *)Tags;
	uint8 UsartCH=USART_GetIndex(USARTx);
	ModBus_Create(&ModBusMsg,0x01,0x05,WorkMode_Slave,MBCM_Crc);
	while(1)
	{
		GPIO_SetIndex(0,0);
		ClearWithBuffer(USART_RX_Buffer[UsartCH],50);
		Length=USART_ReadDatas(USARTx,Null,50,1000);
		if(Length)
		if(MB_CheckCrc(USART_RX_Buffer[UsartCH]),Length)
		{
			switch(USART_RX_Buffer[UsartCH][2])
			{
				case 0x4b:
			switch(USART_RX_Buffer[UsartCH][1])
			{
				case 0x03:
					 
					USART_TX_Buffer[UsartCH][0]=USART_RX_Buffer[UsartCH][0];
					USART_TX_Buffer[UsartCH][1]=USART_RX_Buffer[UsartCH][1];
					Length=COM_Menu_Load(USART_RX_Buffer[UsartCH][3],&USART_TX_Buffer[UsartCH][3]);
					USART_TX_Buffer[UsartCH][2]=Length;
					Length=MB_AppendCrc(USART_TX_Buffer[UsartCH],Length+3);
				break;
				case 0x0f:
					COM_Menu_Enter(USART_RX_Buffer[UsartCH][3],&USART_RX_Buffer[UsartCH][7]);
					USART_TX_Buffer[UsartCH][0]=USART_RX_Buffer[UsartCH][0];
					USART_TX_Buffer[UsartCH][1]=USART_RX_Buffer[UsartCH][1];
					Length=COM_Menu_Load(USART_RX_Buffer[UsartCH][3],&USART_TX_Buffer[UsartCH][3]);
					USART_TX_Buffer[UsartCH][2]=Length;
					Length=MB_AppendCrc(USART_TX_Buffer[UsartCH],Length+3);					
					break;
			}break;
			case 0x4c:
				
				Length=StringCoppy(&USART_RX_Buffer[UsartCH][7],USART_TX_Buffer[UsartCH]);
				Tos_TaskPutQmsg(Tos_GetTaskIDByName("GPRS"),0,Length,&USART_TX_Buffer[UsartCH][0]);
				Length=0;
				break;
			}
			 GPIO_SetIndex(0,1);
			USART_WriteDatas(USARTx,USART_TX_Buffer[UsartCH],Length);
			Tos_TaskDelay(2);
		}
	}
}
