/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Tools_Include.h>
#include <Driver_Include.h>
#include <App_Sensor.h>
#include <COMenu.h>
#include <..\USER\Prj_Insect\App.h>
#include <CPU.h>

char *String_Ok="OK";

extern void BEEP_Double(void);
const char BoolString[2][6]={"False","True"};//不能放在子程序里，会出现未知错误

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
Func:菜单项事件
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
Func:菜单项回传
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
		ClearWithBuffer(USART_RX_Buffer[0],50);
		Length=USART_ReadDatas(USARTx,Null,50,0);
		Length=ModBus_Expend(USART_RX_Buffer[0],Length,&ModBusMsg);
		DataStart=Length;
		if(ModBusMsg.ErrorFlag==ModBus_Ok)
		{
			switch(ModBusMsg.MsgFlag)
			{
				case SCFF_GetProgTime:
						 Length=StringCoppy(__DATE__" - "__TIME__,&Buf[0]);
						 break;
				case SCFF_GetLibVersion:
						 FmtToBuf((char *)&Buf[0],"V %d.%d.%d n",__STM32F10X_STDPERIPH_VERSION_MAIN,__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);
						 Length=10;
						 break;
				case SCFF_GoToBootLoader:
					   System_Reset();
						 break;
				case SCFF_GetSensorTest:
					   Length=StringCoppy("Hello",&Buf[0]);
						 break;
				case SCFF_GetCPUModel:
						 Length=StringCoppy(CPU_Model,&Buf[0]);
					   break;

				case SCFF_SetDeBugMode:
						 DeBug_SetType(USART_RX_Buffer[0][DataStart]);
						 Length=StringCoppy(String_Ok,&Buf[0]);
						 break;
				case SCFF_COMMenuList:
						 switch(USART_RX_Buffer[0][DataStart])
										{
											case 0x01:COM_Menu_Enter(USART_RX_Buffer[0][DataStart+1],&USART_RX_Buffer[0][DataStart+2]);
													 Length=COM_Menu_Load(USART_RX_Buffer[0][DataStart+1],&Buf[0]);											
														break;
											case 0x02:Length=COM_Menu_Load(USART_RX_Buffer[0][DataStart+1],&Buf[0]);break;
											default:break;
										}
						 break;
				case SCFF_UpdateBootLoader:
#ifdef EN_DOWNLOADBOOT					
						DownLoad_BootLoader(Tags);
#endif
						break;
				default: Length=StringCoppy("Null",&Buf[0]);
						 break;
			}
			if(Length!=0xffff)
			{
				ModBus_Create(&ModBusMsg,USART_RX_Buffer[0][2],0x05,WorkMode_Slave,MBCM_Crc);
				Length=ModBus_CreateMsg(USART_TX_Buffer[0],&ModBusMsg,0x01,0x01,0x01,&Buf[0],Length);
				USART_WriteDatas(USART1,USART_TX_Buffer[0],Length);
			}
		
		}else if(ModBusMsg.ErrorFlag==ModBus_Broad)
		{
			
		}
		else if(ModBusMsg.ErrorFlag==ModBus_FlagError)
		{
			DeBug("%s",USART_RX_Buffer[0],Infor_Error);
		}else DeBug("%d",ModBusMsg.ErrorFlag,Infor_Infor);
	}
}
