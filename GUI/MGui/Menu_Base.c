/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <..\MGUI\Menu_Base.h>

MUI_MenuValue *MenuValue;
App_Value Run_Value;
const char *BoolString[2]={"False","True "};//不能放在子程序里，会出现未知错误

void MUI_Fill_Bar(uint16 x1, uint16 y1, uint16 x2, uint16 y2,uint16 Max,uint16 Rate)
{
   uint16 W,H;
   uint16 attr=P_TGui_Style->F_Color,i=0;
   W=x2-x1;
   H=y2-y1;
   if(W>H)
   while(1)
    {
       if((i++)>(W*Rate/Max))attr=P_TGui_Style->B_Color;
       TGui_Draw_Line(x1,y1,x1,y2,attr);
       if(x1++>=x2)break; 
    } 
}   
void MUI_Waiting(char *Title,uint8 D)
{
	uint8 i;
	MUI_ReSetTitle(Title);
	for(i=0;i<30;i++)
	{
	MUI_SetDrawClear(False);
	MUI_Fill_Bar(MenuValue->StartX+1,(MenuValue->EndY-MenuValue->StartY)/2+MenuValue->StartY,MenuValue->EndX-2,(MenuValue->EndY-MenuValue->StartY)/2+MenuValue->StartY+10,30,i);
	TGUI_Set_Font(Run_Value.MenuCFG.MenuFont);
	TGUI_Set_Region(0,(MenuValue->EndY-MenuValue->StartY)/2+MenuValue->StartY+10,MenuValue->EndX*i/30+40,MenuValue->EndY,Align_CenterTop);
	MUI_SetDrawClear(False);
	//Printf("%d%% ",(uint8)((float)i*100/30));
	Tos_TaskDelay(D);
	MUI_SetDrawClear(True);
	//Printf("%d%% ",(uint8)((float)i*100/30));
	}
	TGUI_Fill_Rectangle(MenuValue->StartX+1,(MenuValue->EndY-MenuValue->StartY)/2+MenuValue->StartY,MenuValue->EndX-2,(MenuValue->EndY-MenuValue->StartY)/2+MenuValue->StartY+10,Tos_GetStyleHandle()->B_Color);
	MenuValue->DrawMode=Draw_All;
	MUI_Draw(MenuValue->CurMenu);
}
uint8 MUI_OptionLength(const MUI_MenuStruct *CurMenu)
{
	uint8 Length=0;
	const MUI_MenuStruct *Menu=CurMenu;
	while(Menu->Type!=VT_End)
	{
		Menu++;
		Length++;
	}
	return Length;
}
const MUI_MenuStruct *MUI_GetCurMenuInfor()
{
	const MUI_MenuStruct *Menu=MenuValue->CurMenu;
	uint8 Length=MUI_OptionLength(MenuValue->CurMenu);
	return (Menu+Length);
}
uint8 MUI_GetKey(uint16 D)
{
	Tos_ArrayMessage *CurMsg;
	MGUI_KeyMsg *CurKeyMsg;
	if(D)CurMsg=Tos_TaskGetQMsgDelay(D);
	else CurMsg=Tos_TaskGetQMsg();
	if(CurMsg)
	{
		CurKeyMsg=(MGUI_KeyMsg *)CurMsg->Qmsg_Addr;
		return CurKeyMsg->KeyValue;
	}
	return Null;
}
uint8 Index_Uchar(char *Msg,uint8 Key)
{
    uint8 Index=0;
    while(1)
    {         
        if(Msg[Index]==Key)return Index; 
        if(Msg[Index]==0)return 0;
        Index++;
    }
}
uint8 Index_Word(char *Msg,char *Key,uint8 Length)
{
	uint8 Index=0;
	while(Length--)
	{         
			if(Msg[Index]<0x80)if(Msg[Index]==*(uint8 *)Key)return Index;
			if(Msg[Index]>=0x80){if(*(uint16 *)&Msg[Index]==*(uint16 *)Key)return Index;}
			Index++;
	}
	return 0xff;
}
void Key_GetASCII(uint8 KeyValue,uint8 *Data,uint8 InType)
{
  uint8 Index,Length;
	char CodeBuf[200];
	BufferFill(&CodeBuf[0],0,sizeof(CodeBuf));
	if(InType&IT_Dot)StringEndingAppend(".",&CodeBuf[0]);
	if(InType&IT_Minus)StringEndingAppend("-",&CodeBuf[0]);
	if(InType&IT_Num)StringEndingAppend("0123456789",&CodeBuf[0]);
	if(InType&IT_ASCIIS)StringEndingAppend("abcdefghijklmnopqrstuvwxyz",&CodeBuf[0]);
	if(InType&IT_ASCIIB)StringEndingAppend("ABCDEFGHIJKLMNOPQRSTUVWXYZ",&CodeBuf[0]);
	if(InType&IT_CurCLiB)StringEndingAppend((void *)(Tos_GetFontHandle()->P_CIndex),&CodeBuf[0]);
	if(InType&IT_End)StringEndingAppend("\r\n",&CodeBuf[0]);
	StringEndingAppend("\n",&CodeBuf[0]);
	Length=GetTextLength(&CodeBuf[0]);
   if(KeyValue==Key_Up)
   {
       Index=Index_Uchar(CodeBuf,*Data);
				Index++;
       if(Index>=(Length-1))Index=0;       
       *Data=CodeBuf[Index];
	 }
	  if(KeyValue==Key_Down)
   {
       Index=Index_Uchar(CodeBuf,*Data);
		   if(Index==0)Index=(Length-1);
       Index--;
       *Data=CodeBuf[Index];
	 }
}
void Key_GetWord(uint8 KeyValue,char *D,uint8 InType)
{
  uint8 Index,Length;
	char CodeBuf[200],*Data=D;
	BufferFill(&CodeBuf[0],0,sizeof(CodeBuf));
	if(InType&IT_Dot)StringEndingAppend(".",&CodeBuf[0]);
	if(InType&IT_Minus)StringEndingAppend("-",&CodeBuf[0]);
	if(InType&IT_Num)StringEndingAppend("0123456789",&CodeBuf[0]);
	if(InType&IT_ASCIIS)StringEndingAppend("abcdefghijklmnopqrstuvwxyz",&CodeBuf[0]);
	if(InType&IT_ASCIIB)StringEndingAppend("ABCDEFGHIJKLMNOPQRSTUVWXYZ",&CodeBuf[0]);
	if(InType&IT_CurCLiB)StringEndingAppend((void *)(Tos_GetFontHandle()->P_CIndex),&CodeBuf[0]);
	Length=GetTextLength(&CodeBuf[0]);
	Length++;
	Index=Index_Word(CodeBuf,Data,Length);
	if(Index==0xff)Index=0;
	 if(KeyValue==Key_Up)
   {
		  if(CodeBuf[Index]<0x80)Index++;else Index+=2;if(Index>=Length)Index=0;
       if(CodeBuf[Index]<0x80){*Data=CodeBuf[Index];}else {*(uint16 *)Data=*(uint16 *)&CodeBuf[Index];}
	 }
	  if(KeyValue==Key_Down)
   {
		   if(CodeBuf[Index-2]<0x80)Index--;else Index-=2;if(Index==0xff)Index=(Length);
       if(CodeBuf[Index]<0x80){*Data=CodeBuf[Index];}else {*(uint16 *)Data=*(uint16 *)&CodeBuf[Index];} 
	 }
	 Index=Index_Word(CodeBuf,Data,Length);
	 if(Index==0xff)Index=0;
}
void MUI_ReSetTitle(char *Title)
{
	
	MenuValue->DrawMode|=Draw_Menu;
	MenuValue->Title=Title;
  MUI_Draw(Null);
}
void Printf_Data(uint8 *Buf,uint8 Length,uint8 Cursor)
{
    uint8 i;
    uint16 x;
    uint8 Buf1[2];
    TGUI_Set_Font(Run_Value.MenuCFG.MsgFont);
    x=(MenuValue->EndX-Tos_GetFontHandle()->SizeEW*Length)/2;
    for(i=1;(i<Length-1);i++)
    {
        TGUI_Set_Region(x+i*Tos_GetFontHandle()->SizeEW,0,x+(i+1)*Tos_GetFontHandle()->SizeEW,MenuValue->EndY,Align_LeftCenter);
        Buf1[0]=Buf[i-1];
        Buf1[1]=0;
        if(i==Cursor)Tos_GetStyleHandle()->SelectTrue=True;
        else Tos_GetStyleHandle()->SelectTrue=False;
        Printf((char *)&Buf1[0]);
    }
		TGUI_Set_Region(0,0,MenuValue->EndX-2,MenuValue->EndY,Align_LeftCenter);
		if(Cursor==0)Tos_GetStyleHandle()->SelectTrue=True;
        else Tos_GetStyleHandle()->SelectTrue=False;
		 Printf("No");
		TGUI_Set_Region(0,0,MenuValue->EndX-2,MenuValue->EndY,Align_RightCenter);
		if(Cursor==(Length-1))Tos_GetStyleHandle()->SelectTrue=True;
        else Tos_GetStyleHandle()->SelectTrue=False;
		 Printf("Yes");
		
}
void Printf_String(uint8 *Buf,uint16 Length,uint8 Size,uint8 Cursor)
{
    uint8 i,n=1,End=False;
    uint16 x;
    uint8 Buf1[3];
    TGUI_Set_Font(Run_Value.MenuCFG.MsgFont);
    x=(MenuValue->EndX-Tos_GetFontHandle()->SizeEW*Length)/2;
    for(i=1;(i<Size-1);)
    {
			if(n==Cursor)Tos_GetStyleHandle()->SelectTrue=True;
        else Tos_GetStyleHandle()->SelectTrue=False;
        TGUI_Set_Region(x+i*Tos_GetFontHandle()->SizeEW,0,x+(i+1)*Tos_GetFontHandle()->SizeEW,MenuValue->EndY,Align_LeftCenter);
        if(Buf[i-1]>0x80){Buf1[0]=Buf[i-1];Buf1[1]=Buf[i];Buf1[2]=0;i+=2;n++;}
        else {Buf1[0]=Buf[i-1];Buf1[1]=0;i+=1;n++;}
				if(Buf1[0]==0)End=True;
				if(End==True){Buf1[0]=' ';Buf1[1]=0;}
        Printf((char *)&Buf1[0]);
    }
		TGUI_Set_Region(0,0,MenuValue->EndX-2,MenuValue->EndY,Align_LeftCenter);
		if(Cursor==0)Tos_GetStyleHandle()->SelectTrue=True;
        else Tos_GetStyleHandle()->SelectTrue=False;
		 Printf("No");
		TGUI_Set_Region(0,0,MenuValue->EndX-2,MenuValue->EndY,Align_RightCenter);
		if(Cursor==(Size-1))Tos_GetStyleHandle()->SelectTrue=True;
        else Tos_GetStyleHandle()->SelectTrue=False;
		 Printf("Yes");
		Tos_GetStyleHandle()->SelectTrue=False;
}
char *GetVoidWord(uint8 *Buf,uint8 Index)
{
	char *P=(char *)Buf;
	while(Index--)
	{
		if(*P>0x80)P+=2;
		else P++;
	}
	return P;
}
uint8 MUI_GetWordLength(uint8 *Str)
{
	uint8 i=0;
	while(*Str)
	{
		if(*Str>=0x80)Str++;
		Str++;
		i++;
	}
	return i;
}
void MUI_GetString(uint8 *Str,uint8 Length,uint8 Type)
{
	uint8 Buf[18],KeyData,Index=0;
	uint8 Size;
	MUI_ReSetTitle("PutIn");
	BufferFill(&Buf[0],0x00,sizeof(Buf));
	StringCoppy(Str,&Buf[0]);
	while(1)
	{
		MUI_SetDrawClear(False);
		Size=Length+2;//MUI_GetWordLength(&Buf[0])+3;
		if(Buf[Length]>0x80)Buf[Length]='-';
		if(Buf[Length-1]<0x80)Buf[Length]=0;
		Printf_String(&Buf[0],Length,Size,Index);
		KeyData=MUI_GetKey(0);
		if(KeyData==Key_Left)if(Index)Index--;
		if(KeyData==Key_Right)if(Index<(Size-1))Index++;
		if(Index==(Size-1))if(KeyData==Key_Up|KeyData==Key_Down){StringCoppy(&Buf[0],Str);break;}
		if(Index==0)if(KeyData==Key_Up|KeyData==Key_Down)break;
		if(Index<Size) Key_GetWord(KeyData,GetVoidWord(&Buf[0],Index-1),Type);
		Buf[Size-1]=0;
	}
	MUI_SetDrawClear(True);
	Printf_String(&Buf[0],Length,Size,Index);
}
uint32 MUI_GetIP(uint32 Value,uint8 InType)
{
	uint8 Buf[18],KeyData,Index=0;
	uint8 Size=16;
	MUI_ReSetTitle("PutIn");
	BufferFill(&Buf[0],0,sizeof(Buf));
	GetStringByFmt((char *)&Buf[0],"%03d.%03d.%03d.%03d",((uint8 *)(&Value))[3],((uint8 *)(&Value))[2],((uint8 *)(&Value))[1],((uint8 *)(&Value))[0]);
	while(1)
	{
		MUI_SetDrawClear(False);
		Printf_Data(&Buf[0],Size+1,Index);
		KeyData=MUI_GetKey(0);
		if(KeyData==Key_Left)if(Index)Index--;
		if(KeyData==Key_Right)if(Index<Size)Index++;
		if(Index==Size)if(KeyData==Key_Up|KeyData==Key_Down){Value=StringToIPUint32(&Buf[0]);break;}
		if(Index==0)if(KeyData==Key_Up|KeyData==Key_Down)break;
		if(Index<Size)Key_GetASCII(KeyData,&Buf[Index-1],InType);
		Buf[Size-1]=0;
	}
	MUI_SetDrawClear(True);
	Printf_Data(&Buf[0],Size+1,1);
	return Value;
}

uint32 MUI_GetColor(uint32 Value,uint8 InType)
{
	uint8 Buf[18],KeyData,Index=0;
	uint8 Size=12;
	MUI_ReSetTitle("PutIn");
	BufferFill(&Buf[0],0,sizeof(Buf));
	GetStringByFmt((char *)&Buf[0],"%03d.%03d.%03d",TFT_RGB(Value).R,TFT_RGB(Value).G,TFT_RGB(Value).B);
	while(1)
	{
		MUI_SetDrawClear(False);
		Printf_Data(&Buf[0],Size+1,Index);
		KeyData=MUI_GetKey(0);
		if(KeyData==Key_Left)if(Index)Index--;
		if(KeyData==Key_Right)if(Index<Size)Index++;
		if(Index==Size)if(KeyData==Key_Up|KeyData==Key_Down){Buf[11]=0;Value=ALL_TFT(StringToIPUint32(&Buf[0]));break;}
		if(Index==0)if(KeyData==Key_Up|KeyData==Key_Down)break;
		if(Index<Size)Key_GetASCII(KeyData,&Buf[Index-1],InType);
		Buf[Size-1]=0;
	}
	MUI_SetDrawClear(True);
	Printf_Data(&Buf[0],Size+1,1);
	return Value;
}
float MUI_GetValue(float Value,uint8 Size,uint8 InType)
{
	uint8 Buf[10],KeyData,Index=0;
	Size++;
	MUI_ReSetTitle("PutIn");
	BufferFill(&Buf[0],0,sizeof(Buf));
	GetStringByFmt((char *)&Buf[0],"%.3f",Value);
	while(1)
	{
		MUI_SetDrawClear(False);
		Printf_Data(&Buf[0],Size+1,Index);
		KeyData=MUI_GetKey(0);
		if(KeyData==Key_Left)if(Index)Index--;
		if(KeyData==Key_Right)if(Index<Size)Index++;
		if(Index==Size)if(KeyData==Key_Up|KeyData==Key_Down){Value=GetStringToNumber(&Buf[0]);break;}
		if(Index==0)if(KeyData==Key_Up|KeyData==Key_Down)break;
		if(Index<Size)Key_GetASCII(KeyData,&Buf[Index-1],InType);
		Buf[Size-1]=0;
	}
	MUI_SetDrawClear(True);
	Printf_Data(&Buf[0],Size+1,1);
	return Value;
}
/*******************************************************************************
Func:消息对话框
Date:2014-10-9
Note:消息
*******************************************************************************/
BOOL Printf_Infor(char *Msg,uint16 Delay)
{
	MUI_ReSetTitle("Infor");
	TGUI_Set_Font(Run_Value.MenuCFG.MsgFont);
	TGUI_Set_Region(0,0,MenuValue->EndX,MenuValue->EndY,Align_CenterCenter);
	MUI_SetDrawClear(False);
	Printf((char *)Msg);
	Tos_TaskDelay(Delay);
	MUI_SetDrawClear(True);
	Printf((char *)Msg);
	MenuValue->DrawMode=Draw_All;
	MUI_Draw(MenuValue->CurMenu);
	return True;
}
BOOL PrintfVoid(char *fmt,...)
{
	va_list ap;
	char String[50];
	va_start(ap,fmt);
	vsprintf(String,fmt,ap);
	Printf_Infor(String,1000);
	va_end(ap);
	return True;
}

/*******************************************************************************
Func:确认对话框
Date:2014-10-9
Note:是
*******************************************************************************/
BOOL Printf_Yes(char *Msg)
{
	uint8 KeyData;
	MUI_ReSetTitle(Msg);
	TGUI_Set_Font(Run_Value.MenuCFG.MsgFont);
	while(1)
	{
			MUI_SetDrawClear(False);
			TGUI_Set_Region(0,0,MenuValue->EndX,MenuValue->EndY,Align_CenterCenter);
			Tos_GetStyleHandle()->SelectTrue=True;
			Printf("Ok");
			KeyData=MUI_GetKey(0);
			if(KeyData==Key_Up)break;
			if(KeyData==Key_Down)break;
	}
	MUI_SetDrawClear(True);
	TGUI_Set_Region(0,0,MenuValue->EndX,MenuValue->EndY,Align_CenterCenter);
	Tos_GetStyleHandle()->SelectTrue=False;
	Printf("Ok");
  return True;  
}
/*******************************************************************************
Func:询问对话框
Date:2014-10-9
Note:是否
*******************************************************************************/
BOOL Printf_YesOrNo(char *Msg)
{
  uint8 i=0,KeyData,Ov=False;
	MUI_ReSetTitle(Msg);
	TGUI_Set_Font(Run_Value.MenuCFG.MsgFont);
	while(1)
	{
			MUI_SetDrawClear(Ov);
			TGUI_Set_Region(MenuValue->EndX*1/4,0,MenuValue->EndX*3/4,MenuValue->EndY,Align_LeftCenter);
			Tos_GetStyleHandle()->SelectTrue=(BOOL)i;
			Printf("Ok");
			TGUI_Set_Region(MenuValue->EndX*1/4,0,MenuValue->EndX*3/4,MenuValue->EndY,Align_RightCenter);
			Tos_GetStyleHandle()->SelectTrue=(BOOL)!i;
			Printf("No");
			if(Ov)break;
			if(!Ov)KeyData=MUI_GetKey(0);
			if(KeyData==Key_Up)Ov=True;
			if(KeyData==Key_Down)Ov=True;
			if(KeyData==Key_Left)i=1;
			if(KeyData==Key_Right)i=0;
	}
	Tos_GetStyleHandle()->SelectTrue=False;
  return (BOOL)i; 
}
void MUI_Enter(const MUI_MenuStruct *CurMenu)
{
	typedef   void 	(*FuncUint8)(uint8);
	switch(CurMenu->Type)
	{
		case VT_Menu:MenuValue->OldMenu=MenuValue->CurMenu;
			if(CurMenu->Note>MenuValue->Index){MenuValue->Index=CurMenu->Note;MenuValue->DeepRecord[MenuValue->Index]=0;}
		  else MenuValue->Index=CurMenu->Note;MenuValue->CurMenu=(const MUI_MenuStruct*)CurMenu->Value;MenuValue->DrawMode|=Draw_Menu;break;
		case VT_Task:if(CurMenu->Value)((Func)CurMenu->Value)();break;
		case VT_TaskUint8:if(CurMenu->Value)((FuncUint8)CurMenu->Value)(CurMenu->Note);break;
		case VT_Uint8:*(uint8 *)(CurMenu->Value)=MUI_GetValue(*(uint8 *)(CurMenu->Value),CurMenu->Note,IT_Num);break;
		case VT_Int8:*(int8 *)(CurMenu->Value)=MUI_GetValue(*(int8 *)(CurMenu->Value),CurMenu->Note,IT_Minus|IT_Num);break;
		case VT_Uint16:*(uint16 *)(CurMenu->Value)=MUI_GetValue(*(uint16 *)(CurMenu->Value),CurMenu->Note,IT_Num);break;
		case VT_Float:*(float *)(CurMenu->Value)=MUI_GetValue(*(float *)(CurMenu->Value),CurMenu->Note,IT_Minus|IT_Num|IT_Dot);break;
		case VT_BOOL:*(uint8 *)(CurMenu->Value)=!(BOOL)*(uint8 *)(CurMenu->Value);break;
		case VT_IP:*(uint32 *)(CurMenu->Value)=MUI_GetIP(*(uint32 *)(CurMenu->Value),IT_Num|IT_Dot);break;
		case VT_Color:*(uint16 *)(CurMenu->Value)=MUI_GetColor(*(uint16 *)(CurMenu->Value),IT_Num|IT_Dot);break;
		case VT_Str:MUI_GetString((uint8 *)(CurMenu->Value),CurMenu->Note,IT_Num|IT_ASCIIB|IT_CurCLiB|IT_Dot|IT_Minus);break;
	}
}
void MUI_Title(char *Title)
{
	if(!Title)return;
	LCD_Draw_LineX(MenuValue->StartX,MenuValue->StartY,MenuValue->EndX,Run_Value.MenuCFG.K_Color);
	TGUI_Draw_Rectangle(0,0,MenuValue->EndX,MenuValue->EndY,Run_Value.MenuCFG.K_Color);
	TGUI_Set_Font(Run_Value.MenuCFG.TitleFont);
	TGUI_Set_Region(0,0,MenuValue->EndX,MenuValue->StartY,Align_CenterCenter);
	Printf(Title);
}
void MUI_SetDrawClear(uint8 En)
{
	if(En==0)TGUI_Set_Color(Run_Value.MenuCFG.F_Color,Run_Value.MenuCFG.S_Color,Run_Value.MenuCFG.B_Color,Run_Value.MenuCFG.A_Color);
	if(En==1)TGUI_Set_Color(Run_Value.MenuCFG.B_Color,Run_Value.MenuCFG.B_Color,Run_Value.MenuCFG.B_Color,Run_Value.MenuCFG.A_Color);
}
void MUI_GetOptionString(char *Buf,const MUI_MenuStruct *Menu)
{
	typedef   uint8 	(*Uint8Func)(void);
	switch(Menu->Type)
		{
			case VT_Menu:FmtToBuf(Buf,(char *)Menu->Option);break;
			case VT_Uint8:FmtToBuf(Buf,(char *)Menu->Option,*(uint8 *)(Menu->Value));break;
			case VT_Uint16:FmtToBuf(Buf,(char *)Menu->Option,*(uint16 *)(Menu->Value));break;
			case VT_Float:FmtToBuf(Buf,(char *)Menu->Option,*(float *)(Menu->Value));break;
			case VT_ROMUint8:FmtToBuf(Buf,(char *)Menu->Option,*(uint8 *)(Menu->Value));break;
			case VT_ROMStr:FmtToBuf(Buf,(char *)Menu->Option,(uint8 *)(Menu->Value));break;
			case VT_Str:FmtToBuf(Buf,(char *)Menu->Option,(uint8 *)(Menu->Value));break;
			case VT_ROMUint32:FmtToBuf(Buf,(char *)Menu->Option,*(uint32 *)(Menu->Value));break;
		  case VT_Uint8Task:FmtToBuf(Buf,(char *)Menu->Option,((Uint8Func)Menu->Value)());break;
			case VT_BOOL:FmtToBuf(Buf,(char *)Menu->Option,BoolString[*(BOOL*)(Menu->Value)]);break;
			case VT_Int8:FmtToBuf(Buf,(char *)Menu->Option,*(int8 *)(Menu->Value));break;
			case VT_IP:FmtToBuf(Buf,(char *)Menu->Option,*(uint8 *)((uint32)Menu->Value+3),*(uint8 *)((uint32)Menu->Value+2),*(uint8 *)((uint32)Menu->Value+1),*(uint8 *)((uint32)Menu->Value));break;
			case VT_Color:FmtToBuf(Buf,(char *)Menu->Option,TFT_RGB(*(uint32 *)(Menu->Value)).R,TFT_RGB(*(uint32 *)(Menu->Value)).G,TFT_RGB(*(uint32 *)(Menu->Value)).B);break;
			default:FmtToBuf(Buf,(char *)Menu->Option);break;
		}
	
}
void MUI_DrawMenu(const MUI_MenuStruct *CurMenu)
{
	uint8 i;
	static uint8 Oldi=0;
	char Buf[100];
	typedef   uint8 	(*Uint8Func)(void);
	const MUI_MenuStruct *Menu=CurMenu;
	if(!Menu)return;
	TGUI_Set_Font(Run_Value.MenuCFG.MenuFont);  
	TGUI_Set_Region(MenuValue->StartX,MenuValue->StartY,MenuValue->EndX,MenuValue->EndY,Align_LeftTop);
	i=MenuValue->DeepRecord[MenuValue->Index]/MenuValue->RowCount;
	Menu+=(i*MenuValue->RowCount);
	if(i!=Oldi)
	{
		TGUI_Fill_Rectangle(MenuValue->StartX+1,MenuValue->StartY+1,MenuValue->EndX-2,MenuValue->EndY-2,Tos_GetStyleHandle()->B_Color);
		Oldi=i;
	}
	i=1;
	while(Menu->Type!=VT_End)
	{
		if((MenuValue->CurMenu+MenuValue->DeepRecord[MenuValue->Index])==Menu)Tos_GetStyleHandle()->SelectTrue=True;
		else Tos_GetStyleHandle()->SelectTrue=False;
		MUI_GetOptionString(&Buf[0],Menu);
		Printf(&Buf[0]);
		if(++i>MenuValue->RowCount)break;
		Menu++;
		Tos_GetStyleHandle()->SY+=Tos_GetFontHandle()->SizeEH;
	}
	Tos_GetStyleHandle()->SelectTrue=False;
}
void MUI_Draw(const MUI_MenuStruct *CurMenu)
{
	if(MenuValue->DrawMode==Draw_All)TGUI_Clear_Show();
	TGUI_DefaultStyle();
	if(MenuValue->Title!=MenuValue->OldTitle){MUI_SetDrawClear(True);MUI_Title(MenuValue->OldTitle);MUI_SetDrawClear(False);MUI_Title(MenuValue->Title);MenuValue->OldTitle=MenuValue->Title;MenuValue->DrawMode&=~Draw_Title;}
	if(MenuValue->DrawMode&Draw_Title){MUI_SetDrawClear(False);MUI_Title(MenuValue->Title);MenuValue->DrawMode&=~Draw_Title;}
  if(CurMenu!=MenuValue->OldMenu){MUI_SetDrawClear(True);MUI_DrawMenu(MenuValue->OldMenu);MUI_SetDrawClear(False);MUI_DrawMenu(CurMenu);MenuValue->OldMenu=CurMenu;MenuValue->DrawMode&=~Draw_Menu;}
	else if(MenuValue->DrawMode&Draw_Menu){MUI_SetDrawClear(False);MUI_DrawMenu(MenuValue->CurMenu);MenuValue->DrawMode&=~Draw_Menu;}
	if(MenuValue->DrawMode&Draw_Value){MUI_SetDrawClear(False);MUI_DrawMenu(MenuValue->CurMenu);MenuValue->DrawMode&=~Draw_Value;}
}
