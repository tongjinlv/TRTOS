/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_AirCleaner\Ht1621_Face.h>
#include <Rtc_Driver.h>
 #include <GPIO_Driver.h>
UIShowStruct UIShowValue;
uint8 *Ht1621CharList="0123456789.- UPFTBOHCLN";
uint8 LCD_BUF[16];
/*U


					 ----BIT(3)----
					|              |
					|BIT(7)        |BIT(2)
					 ----BIT(6)----
					|              |
					|BIT(5)        |BIT(1)
  	DP	   ----BIT(0)----	
		BIT(4)
*/
/*D


					 ----BIT(7)----
					|              |
					|BIT(3)        |BIT(6)
					 ----BIT(2)----
					|              |
					|BIT(1)        |BIT(5)
  	DP	   ----BIT(4)----	
		BIT(0)
*/
const uint8 Ht1621CodeUpList[]={
_X_XXXXX,//0
_____XX_,//1
_XX_X_XX,//2
__X_XXXX,//3
__XX_XX_,//4
__XXXX_X,//5
_XXXXX_X,//6
_____XXX,//7
_XXXXXXX,//8
__XXXXXX,//9
________,//.
__X_____,//-
________,// 
_X_XXXX_,//U
_XXX__XX,//P
_XXX___X,//F
_XXXX___,//T
_XXXXX__,//B
_XX_XX__,//O
_XXX_XX_,//H
_X_XX__X,//C
_X_XX___,//L
_X_X_XXX,//N
};
const uint8 Ht1621CodeDownList[]={
_X_XXXXX,//0
_____XX_,//1
__XXXX_X,//2
__X_XXXX,//3
_XX__XX_,//4
_XX_X_XX,//5
_XXXX_XX,//6
____XXX_,//7
_XXXXXXX,//8
_XX_XXXX,//9
________,//.
__X_____,//-
________,// 
_X_X_XXX,//U
_XXXXX__,//P
_XXXX___,//F
_XXX___X,//T
_XXX__XX,//B
__XX__XX,//O
_XXX_XX_,//H
_X_XX__X,//C
_X_X___X,//L
_X_XXXX_,//N
};
const uint8 Ht1621CodeTime[]=
{
	X_X_XXXX,/*0*/
	_____XX_,/*1*/
	_XX_XX_X,/*2*/
	_X__XXXX,/*3*/
	XX___XX_,/*4*/
	XX__X_XX,/*5*/
	XXX_X_XX,/*6*/
	____XXX_,/*7*/
	XXX_XXXX,/*8*/
	XX__XXXX,/*9*/
};
uint8 SerachChear(uint8 Char,const uint8 *Code)
{
	uint8 i=0;
	while(*Code)
	{
		if(Char==*Code)return i;
		i++;
		Code++;
	}
	return i;
}
uint8 Ht1621_GetCode(uint8 Char,const uint8 *P)
{
	uint8 Data;
	Data=P[SerachChear(Char,Ht1621CharList)];
	return Data;
}
	
void Ht1621_ShowASCII(uint8 Index,uint8 Data)
{
	LCD_BUF[Index]|=Data&0xf0;
	LCD_BUF[Index+1]|=Data&0x0f;
}
void Ht1621_SHowUpString(uint8 *Str)
{
		uint8 i=0;
	uint8 Buf[8];
	uint8 *P=Str;
	BufferFill(&Buf[0],0x00,sizeof(Buf));
	while(*P)
	{

			Buf[i]=Ht1621_GetCode(*P,Ht1621CodeUpList);
			i++;
			P++;
		if(i>3)break;
	}
	P=&Buf[0];
	for(i=0;i<4;i++)LCD_BUF[3+9-i]|=*P++;
}
void Ht1621_SHowUpStr(uint8 *Str)
{
	uint8 i=0;
	uint8 Buf[8];
	uint8 *P=Str;
	BufferFill(&Buf[0],0x00,sizeof(Buf));
	while(*P)
	{

			Buf[i]=Ht1621_GetCode(*P,Ht1621CodeUpList);
			i++;
			P++;
		if(i>3)break;
	}
	P=&Buf[0];
	for(i=0;i<4;i++)LCD_BUF[3+9-i]|=*P++;
}
void Ht1621_SHowDownString(uint8 *Str)
{
	uint8 i=0;
	uint8 Buf[8];
	uint8 *P=Str;
	BufferFill(&Buf[0],0x00,sizeof(Buf));
	while(*P)
	{
			Buf[i]|=Ht1621_GetCode(*P,Ht1621CodeDownList);
			i++;
			P++;
		if(i>7)break;
	}
	P=&Buf[0];
	for(i=0;i<7;i++){Ht1621_ShowASCII(1+i,*P++);}
}
void Ht1621_SHowDownStr(uint8 *Str)
{
		uint8 i=0;
	uint8 Buf[8];
	uint8 *P=Str;
	BufferFill(&Buf[0],0x00,sizeof(Buf));
	while(*P)
	{
			Buf[i]|=Ht1621_GetCode(*P,Ht1621CodeDownList);
			i++;
			P++;
		if(i>7)break;
	}
	P=&Buf[0];
	for(i=0;i<7;i++){Ht1621_ShowASCII(1+i,*P++);}
}
void Ht1621_SHowDownStr1(uint8 *Str)
{
		uint8 i=0;
	uint8 Buf[8];
	uint8 *P=Str;
	BufferFill(&Buf[0],0x00,sizeof(Buf));
	while(*P)
	{
			Buf[i]=Ht1621_GetCode(*P,Ht1621CodeDownList);
			i++;
			P++;
	}
	P=&Buf[0];
	Buf[1]=X_XXX_X_;
	for(i=0;i<4;i++){Ht1621_ShowASCII(10+(i*2),*P++);}
}
void Ht1621_DrawTime(uint8 Hour,uint8 Min)
{
	uint8 H;
	static BOOL ShowDot;
	uint8 Buf[4];
	Buf[0]=Ht1621CodeTime[Min%10];
	Buf[1]=Ht1621CodeTime[Min/10];
	Buf[2]=Ht1621CodeTime[Hour%10];
	H=Hour/10;
	if(H==0)Buf[3]=0x00;else if(H==1)Buf[3]=0x06;else Buf[3]=0x0c;
	if(ShowDot)Buf[0]|=0x10;
	ShowDot=(BOOL)!ShowDot;
	Buf[3]|=0x80;//钟图标
	Buf[3]|=0x10;//横线图标
	Ht1621_ShowASCII(20,Buf[0]);
	Ht1621_ShowASCII(22,Buf[1]);
	Ht1621_ShowASCII(24,Buf[2]);
	Ht1621_ShowASCII(26,Buf[3]);
}
void Ht1621_DrawBase()
{
	uint8 i=0;
	for(i=0;i<16;i++)
	{
	Ht1621_WriteReg(i*2, LCD_BUF[i]&0x0f);
	Ht1621_WriteReg(i*2+1, LCD_BUF[i]>>4);
	}
	BufferFill(LCD_BUF,0x00,sizeof(LCD_BUF));
}
void SetValue(uint8 i)
{
	LCD_BUF[14]|=S1;
	if(i>=1)LCD_BUF[14]|=S2;
	if(i>=2)LCD_BUF[13]|=S4;
	if(i>=3)LCD_BUF[13]|=S5;
	if(i>=4)LCD_BUF[13]|=S6;
	if(i>=5)LCD_BUF[13]|=S7;
	if(i>=6)LCD_BUF[13]|=S3;
	if(i>=7)LCD_BUF[13]|=S2;
	if(i>=8)LCD_BUF[13]|=S1;
	if(i>=9)LCD_BUF[13]|=S0;
}
void Beep(uint8 i)
{
	while(i--)
	{
		Tos_TaskDelay(100);
		GPIO_SetIndex(4,1);
		Tos_TaskDelay(100);
		GPIO_SetIndex(4,0);
	}
}
void Ht1621_DrawHome(void *Tags)
{
	char Buf[10];
	static uint8 i=0;
	while(1)
	{
		Tos_TaskDelay(100);
		if(UIShowValue.SysWorkMode&WCB_Start)if(UIShowValue.SysWorkMode&WCB_Open)
		{
		switch(UIShowValue.SaveValue.BlowerNum)
		{
			case 0:
					LCD_BUF[0]|=S5;LCD_BUF[1]|=S3;LCD_BUF[1]|=S0;
					LCD_BUF[0]|=S0;
				break;
			case 1:
					if(i++>15)i=0;
					if(i>(15/2)){LCD_BUF[0]|=S5;LCD_BUF[1]|=S3;LCD_BUF[1]|=S0;}
					else {LCD_BUF[0]|=S6;LCD_BUF[0]|=S4;LCD_BUF[1]|=S1;}
					LCD_BUF[0]|=S1;
					break;
			case 2:
					if(i++>7)i=0;
					if(i>(7/2)){LCD_BUF[0]|=S5;LCD_BUF[1]|=S3;LCD_BUF[1]|=S0;}
					else {LCD_BUF[0]|=S6;LCD_BUF[0]|=S4;LCD_BUF[1]|=S1;}
					LCD_BUF[0]|=S2;
					break;
			case 3:
					if(i++>2)i=0;
					if(i>(2/2)){LCD_BUF[0]|=S5;LCD_BUF[1]|=S3;LCD_BUF[1]|=S0;}
					else {LCD_BUF[0]|=S6;LCD_BUF[0]|=S4;LCD_BUF[1]|=S1;}
					LCD_BUF[0]|=S3;
					break;
			case 4:
						switch(i)
						{
							case 0:LCD_BUF[0]|=S6;LCD_BUF[1]|=S0;i++;break;
							case 1:LCD_BUF[0]|=S6;LCD_BUF[1]|=S0;i++;break;
							case 2:LCD_BUF[0]|=S4;LCD_BUF[1]|=S3;i++;break;
							case 3:LCD_BUF[0]|=S4;LCD_BUF[1]|=S3;i++;break;
							case 4:LCD_BUF[0]|=S5;LCD_BUF[1]|=S1;i++;break;
							case 5:LCD_BUF[0]|=S5;LCD_BUF[1]|=S1;i=0;break;
							default:i=0;
						}
					LCD_BUF[0]|=S7;
					break;
		}
		LCD_BUF[3]|=S7;
		
		if((!UIShowValue.DateTime.Hour)&(UIShowValue.DateTime.Min==15))LCD_BUF[4]|=S7;else LCD_BUF[2]|=S7;
		GetStringByFmt(&Buf[0],"%02d%02d%02d%d",UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,UIShowValue.DateTime.Sec,UIShowValue.SaveValue.LampNum);
		
		
		
		LCD_BUF[8]|=S4;
		SetValue(UIShowValue.SaveValue.CleanNum);
	  if(UIShowValue.ShowFlag&WSB_ExpAlarm)LCD_BUF[8]|=S6;
		if(UIShowValue.ShowFlag&WSB_OpenAirCleaner)LCD_BUF[8]|=S5;
		if(UIShowValue.DateTime.Day++>10)UIShowValue.DateTime.Day=0;
		if(UIShowValue.DateTime.Day>4)LCD_BUF[5]|=S7;
		if(UIShowValue.DateTime.Day%5>2)
		{
			
			switch(UIShowValue.SetSelect)
			{
				case 1:BufferFill(&Buf[0],' ',2);break;
				case 2:BufferFill(&Buf[2],' ',2);break;
				case 3:BufferFill(&Buf[4],' ',2);break;
			}
		}
		Ht1621_SHowDownString((uint8 *)Buf);
		
		
		GetStringByFmt(&Buf[0],"%04d",UIShowValue.PM25_Value);
		Ht1621_SHowUpStr((uint8 *)Buf);
		if(UIShowValue.DateTime.Year++>10)
		{
			UIShowValue.DateTime.Year=0;
			if(UIShowValue.DateTime.Sec>0)UIShowValue.DateTime.Sec--;
			else 
			{
				
				if(UIShowValue.DateTime.Min>0){UIShowValue.DateTime.Min--;UIShowValue.DateTime.Sec=59;}
				else 
				{
					if(UIShowValue.DateTime.Hour>0){UIShowValue.DateTime.Hour--;UIShowValue.DateTime.Min=59;}
				}
			}
		}
		if(UIShowValue.DateTime.Hour==0)if(UIShowValue.DateTime.Min==0)if(UIShowValue.DateTime.Sec==0)
		{
			if(UIShowValue.SysWorkMode&WCB_Open)Beep(3);
			UIShowValue.SysWorkMode&=~WCB_Open;

		}
		LCD_BUF[1]|=S7;
		LCD_BUF[10]|=S7;
		LCD_BUF[6]|=S7;
		LCD_BUF[14]|=S0;
		LCD_BUF[7]|=S7;
	}
	if(UIShowValue.ShowFlag&WSB_Ug)LCD_BUF[9]|=S7;
	if(UIShowValue.ShowFlag&WSB_PM25)LCD_BUF[11]|=S7;
	if(UIShowValue.ShowFlag&WSB_API)LCD_BUF[12]|=S7;
		Ht1621_DrawBase();
	}
}
