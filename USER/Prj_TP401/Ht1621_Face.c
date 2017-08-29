/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_TP401\Ht1621_Face.h>
#include <Rtc_Driver.h>
UIShowStruct UIShowValue;
uint8 *Ht1621CharList="0123456789.- UPFTBOHCLN";
uint8 LCD_BUF[27];
/*U


					 ----BIT(4)----
					|              |
					|BIT(6)        |BIT(5)
					 ----BIT(7)----
					|              |
					|BIT(1)        |BIT(0)
  	DP	   ----BIT(2)----	
		BIT(3)
*/
/*D


					 ----BIT(2)----
					|              |
					|BIT(0)        |BIT(1)
					 ----BIT(7)----
					|              |
					|BIT(5)        |BIT(6)
  	DP	   ----BIT(4)----	
		BIT(3)
*/
/*D


					 ----BIT(2)----
					|              |
					|BIT(0)        |BIT(1)
					 ----BIT(7)----
					|              |
					|BIT(5)        |BIT(6)
  	DP	   ----BIT(4)----	
		BIT(3)
*/
const uint8 Ht1621CodeUpList[]={
	_XXX_XXX,//0
	__X____X,//1
	X_XX_XX_,//2
	X_XX_X_X,//3
	XXX____X,//4
	XX_X_X_X,//5
	XX_X_XXX,//6
	__XX___X,//7
	XXXX_XXX,//8
	XXXX_X_X,//9
	________,//.
	X_______,//-
	________,// 
	_XX__XXX,//U
	XXXX__X_,//P
	XX_X__X_,//F
	XX___XX_,//T
	XX___XXX,//B
	X____XXX,//O
	XXX___XX,//H
	_X_X_XX_,//C
	_X___XX_,//L
	_XXX__XX,//N
};
const uint8 Ht1621CodeDownList[]={
	_XXX_XXX,//0
	_X____X_,//1
	X_XX_XX_,//2
	XX_X_XX_,//3
	XX____XX,//4
	XX_X_X_X,//5
	XXXX_X_X,//6
	_X___XX_,//7
	XXXX_XXX,//8
	XX_X_XXX,//9
	________,//.
	X_______,//-      X__X_X_
	________,// 
	_XXX__XX,//U
	X_X__XXX,//P
	X_X__X_X,//F
	X_XX___X,//T
	XXXX___X,//B
	XXXX____,//O
	XXX___XX,//H
	__XX_X_X,//C
	__XX___X,//L
	_XX__XXX,//N
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
	Ht1621_WriteReg(Index, Data&0x0f);
	Ht1621_WriteReg(Index+1, Data>>4);
	LCD_BUF[Index/2]=Data;
}
void Ht1621_SHowUpString(uint8 *Str)
{
	uint8 fh=0,fe=0,i;
	uint8 *P=Str;
	BufferFill(&LCD_BUF[4],0x00,4);
	while(*P)
	{
		if(*P=='.')break;
		P++;
		fh++;
	}
	while(*P)
	{
		if(*P!='.')fe++;
		P++;
	}
	P=Str;
	if(fe==0|fh>4)
	{
		if(fh>4)for(i=0;i<5;i++)LCD_BUF[8-i]=Ht1621_GetCode(Str[i],Ht1621CodeUpList);
		else for(i=0;i<fh;i++)LCD_BUF[4+i]=Ht1621_GetCode(Str[fh-i],Ht1621CodeUpList);
	}else
	{
		LCD_BUF[4]=Ht1621_GetCode(Str[fh+fe],Ht1621CodeUpList);
		for(i=0;i<fh;i++)LCD_BUF[5+i]=Ht1621_GetCode(Str[fh-i-1],Ht1621CodeUpList);
		LCD_BUF[5]|=S3;
	}
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
	P=&Buf[0];i=6;
	for(i=0;i<4;i++){Ht1621_ShowASCII(6-(i*2),*P++);}
}
void Ht1621_SHowDownString(uint8 *Str)
{
	uint8 fh=0,fe=0,i;
	uint8 *P=Str;
	BufferFill(&LCD_BUF[0],0x00,4);
	while(*P)
	{
		if(*P=='.')break;
		P++;
		fh++;
	}
	while(*P)
	{
		if(*P!='.')fe++;
		P++;
	}
	P=Str;
	if(fe==0|fh>3)
	{
		if(fh>3)for(i=0;i<4;i++)LCD_BUF[i]=Ht1621_GetCode(Str[i],Ht1621CodeDownList);
		else for(i=0;i<fh;i++)LCD_BUF[4-i]=Ht1621_GetCode(Str[fh-i],Ht1621CodeDownList);
	}else
	{
		LCD_BUF[3]=Ht1621_GetCode(Str[fh+fe],Ht1621CodeDownList);
		for(i=0;i<fh;i++)LCD_BUF[2-i]=Ht1621_GetCode(Str[fh-i-1],Ht1621CodeDownList);
		LCD_BUF[2]|=S3;
	}
}
void Ht1621_DrawTime(uint8 Hour,uint8 Min)
{

	UIShowValue.DateTime.Year=16;
	LCD_BUF[14]=Ht1621CodeUpList[UIShowValue.DateTime.Year/10];
	LCD_BUF[15]=Ht1621CodeUpList[UIShowValue.DateTime.Year%10];

}
void Ht1621_SHowDownStr(uint8 *Str)
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
	Buf[1]=___XX_X_;
	for(i=0;i<4;i++){Ht1621_ShowASCII(10+(i*2),*P++);}
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

void Ht1621_DrawDateTime(Date_Time DateTime)
{
	static BOOL ShowDot;
	LCD_BUF[14]=Ht1621CodeUpList[DateTime.Year/10];
	LCD_BUF[15]=Ht1621CodeUpList[DateTime.Year%10];
	LCD_BUF[15]|=S3;
	LCD_BUF[16]=Ht1621CodeUpList[DateTime.Mon/10];
	LCD_BUF[17]=Ht1621CodeUpList[DateTime.Mon%10];
	LCD_BUF[17]|=S3;
	LCD_BUF[18]=Ht1621CodeUpList[DateTime.Day/10];
	LCD_BUF[19]=Ht1621CodeUpList[DateTime.Day%10];
	
	LCD_BUF[20]=Ht1621CodeUpList[DateTime.Hour/10];
	LCD_BUF[21]=Ht1621CodeUpList[DateTime.Hour%10];
	LCD_BUF[21]|=S3;
	LCD_BUF[22]=Ht1621CodeUpList[DateTime.Min/10];
	LCD_BUF[23]=Ht1621CodeUpList[DateTime.Min%10];
	if(ShowDot)LCD_BUF[23]|=S3;
	ShowDot=(BOOL)!ShowDot;
	LCD_BUF[24]=Ht1621CodeUpList[DateTime.Sec/10];
	LCD_BUF[25]=Ht1621CodeUpList[DateTime.Sec%10];
}
void Ht1621DrawID(uint8 *Data)
{
	
	uint8 i;
	for(i=0;i<3;i++)LCD_BUF[11+i]=Ht1621_GetCode(Data[2-i],Ht1621CodeDownList);
	
}
void Ht1621DrawWay()
{
	switch(UIShowValue.CurWay)
	{
		case 0:LCD_BUF[11]|=BIT(3);break;
		case 1:LCD_BUF[12]|=BIT(3);break;
		case 2:LCD_BUF[13]|=BIT(3);break;
		default:UIShowValue.CurWay=0;break;
	}
}
void Ht1621_DrawBase()
{
	uint8 i=0;
	for(i=0;i<27;i++)
	{
	Ht1621_WriteReg(i*2, LCD_BUF[i]&0x0f);
	Ht1621_WriteReg(i*2+1, LCD_BUF[i]>>4);
	}
}

void Ht1621_DrawMenu(uint8 i)
{
	uint8 n;
	for(n=0;n<16;n++)
	{
		LCD_BUF[n]=0x00;
	}
	Ht1621_SHowUpString("BOOT");
	switch(i)
	{
		case 0:Ht1621_SHowDownString("TP-0");break;
		case 1:Ht1621_SHowDownString("0C-1");break;
		case 2:Ht1621_SHowDownString("UC-2");break;
		case 3:Ht1621_SHowDownString("UP-3");break;
		case 4:Ht1621_SHowDownString("0P-3");break;
		default:Ht1621_SHowDownString("TP-0");break;
	}
	
	Ht1621_DrawBase();
}
void Ht1621_DrawHome()
{
	uint8 Buf[10];
	static uint8 i=0;
	BufferFill(LCD_BUF,0x00,sizeof(LCD_BUF));
	Ht1621_DrawDateTime(UIShowValue.DateTime);
	
	
	switch(UIShowValue.CurWay)
	{
		case 0:if(UIShowValue.RunFlag&WRF_SensorCH1Connected)
			{
				FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.CH_Value[0+UIShowValue.CurWay*2]);
				StringTrim(&Buf[0]);
				Ht1621_SHowUpString(&Buf[0]);
				FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.CH_Value[1+UIShowValue.CurWay*2]);
				StringTrim(&Buf[0]);
				Ht1621_SHowDownString(&Buf[0]);
			}else {Ht1621_SHowUpString("-----");Ht1621_SHowDownString("-----");}
		break;
		case 1:if(UIShowValue.RunFlag&WRF_SensorCH2Connected)
			{
				FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.CH_Value[0+UIShowValue.CurWay*2]);
				StringTrim(&Buf[0]);
				Ht1621_SHowUpString(&Buf[0]);
				FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.CH_Value[1+UIShowValue.CurWay*2]);
				StringTrim(&Buf[0]);
				Ht1621_SHowDownString(&Buf[0]);
			}else {Ht1621_SHowUpString("-----");Ht1621_SHowDownString("-----");}
		break;
		case 2:if(UIShowValue.RunFlag&WRF_SensorCH3Connected)
			{
				FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.CH_Value[0+UIShowValue.CurWay*2]);
				StringTrim(&Buf[0]);
				Ht1621_SHowUpString(&Buf[0]);
				FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.CH_Value[1+UIShowValue.CurWay*2]);
				StringTrim(&Buf[0]);
				Ht1621_SHowDownString(&Buf[0]);
			}else {Ht1621_SHowUpString("-----");Ht1621_SHowDownString("-----");}
		break;
	}
	LCD_BUF[4]|=S3;
	LCD_BUF[3]|=S3;
	FmtToBuf((char*)&Buf[0],"%03d  ",UIShowValue.SaveValue.ServerPort[0]);
	Ht1621DrawID(&Buf[0]);
	LCD_BUF[9]=S0;
	if(UIShowValue.RunFlag&WRF_EXP_Connected)
	{
		if(i>1)LCD_BUF[9]|=S3;
		if(i>2)LCD_BUF[9]|=S3|S2;
		if(i>3)LCD_BUF[9]|=S1|S2|S3;
		if(i++>3)i=1;
	}
	else
	{
		if(UIShowValue.CH_Value[2]>3.5)LCD_BUF[9]|=S2;
		if(UIShowValue.CH_Value[2]>3.7)LCD_BUF[9]|=S1;
		if(UIShowValue.CH_Value[2]>4.0)LCD_BUF[9]|=S3;
	}
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>0)LCD_BUF[9]|=S4;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>10)LCD_BUF[9]|=S5;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>20)LCD_BUF[9]|=S6;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>30)LCD_BUF[9]|=S7;
	if(UIShowValue.RunFlag&WRF_GPRS_Connected)LCD_BUF[14]|=S6;
	if(UIShowValue.RunFlag&(WRF_CH1Max))LCD_BUF[8]|=S3;
	if(UIShowValue.RunFlag&(WRF_CH1Min))LCD_BUF[7]|=S3;
	if(UIShowValue.RunFlag&(WRF_CH2Max))LCD_BUF[1]|=S3;
	if(UIShowValue.RunFlag&(WRF_CH2Min))LCD_BUF[0]|=S3;
	if(UIShowValue.RunFlag&WRF_BeepDisable)LCD_BUF[10]|=S4;
	Ht1621DrawWay();
	Ht1621_DrawBase();
}
void Ht1621_DrawMaxMin(uint8 i)
{
	uint8 Buf[10];
	BufferFill(LCD_BUF,0x00,sizeof(LCD_BUF));
	//Ht1621_DrawDateTime(UIShowValue.DateTime);
	switch(i)
	{
		case 1:FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.SaveValue.CH_Limit[0+UIShowValue.CurWay*2].Max);StringTrim(&Buf[0]);Ht1621_SHowUpString(&Buf[0]);LCD_BUF[4]|=S3;LCD_BUF[8]|=S3;break;
		case 2:FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.SaveValue.CH_Limit[0+UIShowValue.CurWay*2].Min);StringTrim(&Buf[0]);Ht1621_SHowUpString(&Buf[0]);LCD_BUF[4]|=S3;LCD_BUF[7]|=S3;break;
		case 3:FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.SaveValue.CH_Limit[1+UIShowValue.CurWay*2].Max);StringTrim(&Buf[0]);Ht1621_SHowDownString(&Buf[0]);LCD_BUF[3]|=S3;LCD_BUF[1]|=S3;break;
		case 4:FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.SaveValue.CH_Limit[1+UIShowValue.CurWay*2].Min);StringTrim(&Buf[0]);Ht1621_SHowDownString(&Buf[0]);LCD_BUF[3]|=S3;LCD_BUF[0]|=S3;break;
		case 5:FmtToBuf((char*)&Buf[0],"%03d  ",UIShowValue.SaveValue.ServerPort[0]);Ht1621DrawID(&Buf[0]);break;
	}
	Ht1621_DrawBase();
}
void Ht1621_DrawHold(uint8 i)
{
	uint8 Buf[10];
	BufferFill(LCD_BUF,0x00,sizeof(LCD_BUF));
	//Ht1621_DrawDateTime(UIShowValue.DateTime);
	switch(i)
	{
		case 1:FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.CH_Hold[0+UIShowValue.CurWay*2].Max);StringTrim(&Buf[0]);Ht1621_SHowUpString(&Buf[0]);LCD_BUF[4]|=S3;LCD_BUF[8]|=S3;
					 FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.CH_Hold[1+UIShowValue.CurWay*2].Max);StringTrim(&Buf[0]);Ht1621_SHowDownString(&Buf[0]);LCD_BUF[3]|=S3;LCD_BUF[1]|=S3;
		break;
		case 2:FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.CH_Hold[0+UIShowValue.CurWay*2].Min);StringTrim(&Buf[0]);Ht1621_SHowUpString(&Buf[0]);LCD_BUF[4]|=S3;LCD_BUF[7]|=S3;
					 FmtToBuf((char*)&Buf[0],"%.1f  ",UIShowValue.CH_Hold[1+UIShowValue.CurWay*2].Min);StringTrim(&Buf[0]);Ht1621_SHowDownString(&Buf[0]);LCD_BUF[3]|=S3;LCD_BUF[0]|=S3; 
		break;
	}
	Ht1621_DrawBase();
}
void Ht1621_DrawLUX()
{
	uint8 Buf[10];
	float ShowValue;
	static uint8 i=0;
	UIShowValue.UnitFlag=0;
	ShowValue=(int)UIShowValue.CH_Value[0];
	if(UIShowValue.CH_Value[0]>1000)ShowValue=(int)UIShowValue.CH_Value[0]/10+0.1;
	if(UIShowValue.CH_Value[0]>10000)ShowValue=(int)UIShowValue.CH_Value[0]/100+0.2;
	if(UIShowValue.CH_Value[0]>100000)ShowValue=(int)UIShowValue.CH_Value[0]/1000+0.3;
	Ht1621_DrawTime(UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min);
	FmtToBuf((char*)&Buf[0],"%.2f  ",ShowValue);
	if(UIShowValue.RunFlag&WRF_SensorCH1Connected)
	{
		Ht1621_SHowUpString(&Buf[0]);
		//UIShowValue.UnitFlag|=HSF_HCelsiusC;
	}else
	{
		Ht1621_SHowUpString("----");
		//UIShowValue.UnitFlag|=HSF_HCelsiusC;
	}
	FmtToBuf((char*)&Buf[0],"%.2f  ",UIShowValue.CH_Value[1]);
	if(UIShowValue.RunFlag&WRF_SensorCH2Connected)
	{
		//if(UIShowValue.SaveValue.WorkBit&WCB_DTH11)UIShowValue.UnitFlag|=HSF_LPercentage;
		//else UIShowValue.UnitFlag|=HSF_LCelsiusC;
		Ht1621_SHowDownString(&Buf[0]);
	}else
	{
		//if(UIShowValue.SaveValue.WorkBit&WCB_DTH11)UIShowValue.UnitFlag|=HSF_LPercentage;
		//else UIShowValue.UnitFlag|=HSF_LCelsiusC;
		Ht1621_SHowDownStr("-LU-");
	}
	LCD_BUF[4]|=S1;//通道一铃显示
	LCD_BUF[6]|=S0;//通道二铃显示
	LCD_BUF[15]=UIShowValue.UnitFlag;
	LCD_BUF[9]=S0;
	if(UIShowValue.RunFlag&WRF_EXP_Connected)
	{
		if(i>1)LCD_BUF[9]|=S2;
		if(i>2)LCD_BUF[9]|=S2|S1;
		if(i>3)LCD_BUF[9]|=S1|S2|S3;
		if(i++>3)i=1;
	}
	else
	{
		if(UIShowValue.CH_Value[2]>3.5)LCD_BUF[9]|=S2;
		if(UIShowValue.CH_Value[2]>3.7)LCD_BUF[9]|=S1;
		if(UIShowValue.CH_Value[2]>4.0)LCD_BUF[9]|=S3;
	}
	if(UIShowValue.RunFlag&WRF_EXP_Connected)LCD_BUF[9]|=S4;
	if(UIShowValue.RunFlag&WRF_USB_Connected)LCD_BUF[14]=S4;else LCD_BUF[14]&=~S4;
	//if(UIShowValue.CH_Value[2]>4.1)LCD_BUF[9]|=S4;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>0)LCD_BUF[4]|=S4;else LCD_BUF[4]&=~S4;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>10)LCD_BUF[4]|=S5;else LCD_BUF[4]&=~S5;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>20)LCD_BUF[4]|=S6;else LCD_BUF[4]&=~S6;
	if(UIShowValue.RunFlag&WRF_GPRS_Connected)LCD_BUF[14]|=S6;else LCD_BUF[14]&=~S6;
	if(UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH1Min))LCD_BUF[4]|=S0;else LCD_BUF[4]&=~S0;//通道一报警
	if(UIShowValue.RunFlag&(WRF_CH2Max|WRF_CH2Min))LCD_BUF[5]|=S0;else LCD_BUF[5]&=~S0;//通道二报警
	if(UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH2Max))LCD_BUF[14]|=S7;else LCD_BUF[14]&=~S7;//上限报警
	if(UIShowValue.RunFlag&(WRF_CH1Min|WRF_CH2Min))LCD_BUF[14]|=S5;else LCD_BUF[14]&=~S5;//上限报警
	if(UIShowValue.RunFlag&WRF_GPS_Connected)LCD_BUF[4]|=S2;else LCD_BUF[4]&=~S2;
	//LCD_BUF[14]=S2;MEM
	//LCD_BUF[14]=S0;存储
	//LCD_BUF[14]=S4;USB
//	LCD_BUF[14]=S5;//MIN
//	LCD_BUF[14]=S7;//MAX
	if(UIShowValue.RecordCount==0xff)LCD_BUF[13]|=S6;else LCD_BUF[13]&=~S6;
	if(UIShowValue.RunFlag&WRF_BeepDisable)LCD_BUF[13]&=~S5;else LCD_BUF[13]|=S5;
	if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)LCD_BUF[14]|=S3|S1;else LCD_BUF[14]&=~(S3|S1);
	Ht1621_DrawBase();
}
void Ht1621_DrawZFS()
{
	uint8 Buf[10];
	float ShowValue;
	static uint8 i=0;
	UIShowValue.UnitFlag=0;
	ShowValue=(int)UIShowValue.CH_Value[0];
	if(UIShowValue.CH_Value[0]>1000)ShowValue=(int)UIShowValue.CH_Value[0]/10+0.1;
	if(UIShowValue.CH_Value[0]>10000)ShowValue=(int)UIShowValue.CH_Value[0]/100+0.2;
	if(UIShowValue.CH_Value[0]>100000)ShowValue=(int)UIShowValue.CH_Value[0]/1000+0.3;
	Ht1621_DrawTime(UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min);
	FmtToBuf((char*)&Buf[0],"%.2f  ",ShowValue);
	if(UIShowValue.RunFlag&WRF_SensorCH1Connected)
	{
		Ht1621_SHowUpString(&Buf[0]);
		//UIShowValue.UnitFlag|=HSF_HCelsiusC;
	}else
	{
		Ht1621_SHowUpString("----");
		//UIShowValue.UnitFlag|=HSF_HCelsiusC;
	}
	FmtToBuf((char*)&Buf[0],"%.2f  ",UIShowValue.CH_Value[1]);
	if(UIShowValue.RunFlag&WRF_SensorCH2Connected)
	{
		//if(UIShowValue.SaveValue.WorkBit&WCB_DTH11)UIShowValue.UnitFlag|=HSF_LPercentage;
		//else UIShowValue.UnitFlag|=HSF_LCelsiusC;
		Ht1621_SHowDownString(&Buf[0]);
	}else
	{
		//if(UIShowValue.SaveValue.WorkBit&WCB_DTH11)UIShowValue.UnitFlag|=HSF_LPercentage;
		//else UIShowValue.UnitFlag|=HSF_LCelsiusC;
		Ht1621_SHowDownStr1("-G2-");
	}
	LCD_BUF[4]|=S1;//通道一铃显示
	LCD_BUF[6]|=S0;//通道二铃显示
	LCD_BUF[15]=UIShowValue.UnitFlag;
	LCD_BUF[9]=S0;
	if(UIShowValue.RunFlag&WRF_EXP_Connected)
	{
		if(i>1)LCD_BUF[9]|=S2;
		if(i>2)LCD_BUF[9]|=S2|S1;
		if(i>3)LCD_BUF[9]|=S1|S2|S3;
		if(i++>3)i=1;
	}
	else
	{
		if(UIShowValue.CH_Value[2]>3.5)LCD_BUF[9]|=S2;
		if(UIShowValue.CH_Value[2]>3.7)LCD_BUF[9]|=S1;
		if(UIShowValue.CH_Value[2]>4.0)LCD_BUF[9]|=S3;
	}
	if(UIShowValue.RunFlag&WRF_EXP_Connected)LCD_BUF[9]|=S4;
	if(UIShowValue.RunFlag&WRF_USB_Connected)LCD_BUF[14]=S4;else LCD_BUF[14]&=~S4;
	//if(UIShowValue.CH_Value[2]>4.1)LCD_BUF[9]|=S4;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>0)LCD_BUF[4]|=S4;else LCD_BUF[4]&=~S4;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>10)LCD_BUF[4]|=S5;else LCD_BUF[4]&=~S5;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>20)LCD_BUF[4]|=S6;else LCD_BUF[4]&=~S6;
	if(UIShowValue.RunFlag&WRF_GPRS_Connected)LCD_BUF[14]|=S6;else LCD_BUF[14]&=~S6;
	if(UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH1Min))LCD_BUF[4]|=S0;else LCD_BUF[4]&=~S0;//通道一报警
	if(UIShowValue.RunFlag&(WRF_CH2Max|WRF_CH2Min))LCD_BUF[5]|=S0;else LCD_BUF[5]&=~S0;//通道二报警
	if(UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH2Max))LCD_BUF[14]|=S7;else LCD_BUF[14]&=~S7;//上限报警
	if(UIShowValue.RunFlag&(WRF_CH1Min|WRF_CH2Min))LCD_BUF[14]|=S5;else LCD_BUF[14]&=~S5;//上限报警
	if(UIShowValue.RunFlag&WRF_GPS_Connected)LCD_BUF[4]|=S2;else LCD_BUF[4]&=~S2;
	//LCD_BUF[14]=S2;MEM
	//LCD_BUF[14]=S0;存储
	//LCD_BUF[14]=S4;USB
//	LCD_BUF[14]=S5;//MIN
//	LCD_BUF[14]=S7;//MAX
	if(UIShowValue.RecordCount==0xff)LCD_BUF[13]|=S6;else LCD_BUF[13]&=~S6;
	if(UIShowValue.RunFlag&WRF_BeepDisable)LCD_BUF[13]&=~S5;else LCD_BUF[13]|=S5;
	if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)LCD_BUF[14]|=S3|S1;else LCD_BUF[14]&=~(S3|S1);
	Ht1621_DrawBase();
}
void Ht1621_DrawIO()
{
	uint8 Buf[10];
	static uint8 i=0;
	UIShowValue.UnitFlag=0;
	Ht1621_DrawTime(UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min);
	FmtToBuf((char*)&Buf[0],"%.2f  ",UIShowValue.CH_Value[0]);

	if(UIShowValue.CH_Value[0]>0)Ht1621_SHowUpString("-0FF");
	else Ht1621_SHowUpString("-0N-");

	if(UIShowValue.CH_Value[1]>0)Ht1621_SHowDownString("-0FF");
	else Ht1621_SHowDownString("-0N-");
	LCD_BUF[4]|=S1;//通道一铃显示
	LCD_BUF[6]|=S0;//通道二铃显示
	LCD_BUF[15]=UIShowValue.UnitFlag;
	LCD_BUF[9]=S0;
	if(UIShowValue.RunFlag&WRF_EXP_Connected)
	{
		if(i>1)LCD_BUF[9]|=S2;
		if(i>2)LCD_BUF[9]|=S2|S1;
		if(i>3)LCD_BUF[9]|=S1|S2|S3;
		if(i++>3)i=1;
	}
	else
	{
		if(UIShowValue.CH_Value[2]>3.5)LCD_BUF[9]|=S2;
		if(UIShowValue.CH_Value[2]>3.7)LCD_BUF[9]|=S1;
		if(UIShowValue.CH_Value[2]>4.0)LCD_BUF[9]|=S3;
	}
	if(UIShowValue.RunFlag&WRF_EXP_Connected)LCD_BUF[9]|=S4;
	if(UIShowValue.RunFlag&WRF_USB_Connected)LCD_BUF[14]=S4;else LCD_BUF[14]&=~S4;
	//if(UIShowValue.CH_Value[2]>4.1)LCD_BUF[9]|=S4;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>0)LCD_BUF[4]|=S4;else LCD_BUF[4]&=~S4;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>10)LCD_BUF[4]|=S5;else LCD_BUF[4]&=~S5;
	if(UIShowValue.RSSI<99&UIShowValue.RSSI>20)LCD_BUF[4]|=S6;else LCD_BUF[4]&=~S6;
	if(UIShowValue.RunFlag&WRF_GPRS_Connected)LCD_BUF[14]|=S6;else LCD_BUF[14]&=~S6;
	if(UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH1Min))LCD_BUF[4]|=S0;else LCD_BUF[4]&=~S0;//通道一报警
	if(UIShowValue.RunFlag&(WRF_CH2Max|WRF_CH2Min))LCD_BUF[5]|=S0;else LCD_BUF[5]&=~S0;//通道二报警
	if(UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH2Max))LCD_BUF[14]|=S7;else LCD_BUF[14]&=~S7;//上限报警
	if(UIShowValue.RunFlag&(WRF_CH1Min|WRF_CH2Min))LCD_BUF[14]|=S5;else LCD_BUF[14]&=~S5;//上限报警
	if(UIShowValue.RunFlag&WRF_GPS_Connected)LCD_BUF[4]|=S2;else LCD_BUF[4]&=~S2;
	//LCD_BUF[14]=S2;MEM
	//LCD_BUF[14]=S0;存储
	//LCD_BUF[14]=S4;USB
//	LCD_BUF[14]=S5;//MIN
//	LCD_BUF[14]=S7;//MAX
	if(UIShowValue.RecordCount==0xff)LCD_BUF[13]|=S6;else LCD_BUF[13]&=~S6;
	if(UIShowValue.RunFlag&WRF_BeepDisable)LCD_BUF[13]&=~S5;else LCD_BUF[13]|=S5;
	if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)LCD_BUF[14]|=S3|S1;else LCD_BUF[14]&=~(S3|S1);
	Ht1621_DrawBase();
}
void Ht1621_DrawUpDown(uint8 i)
{
	uint8 BufH[10],BufL[10];
	uint8 n;
	for(n=0;n<16;n++)
	{
		LCD_BUF[n]=0x00;
	}
	switch(i)
	{
		case 0:
			FmtToBuf((char*)&BufH[0],"%.2f  ",UIShowValue.CH_Hold[0].Max);
			FmtToBuf((char*)&BufL[0],"%.2f  ",UIShowValue.CH_Hold[0].Min);
			Ht1621_SHowUpString(&BufH[0]);
			Ht1621_SHowDownString(&BufL[0]);
			LCD_BUF[4]|=S1;//通道一铃显示
			LCD_BUF[14]=S5|S7;//MAXMIN
			break;
		case 1:
			FmtToBuf((char*)&BufH[0],"%.2f  ",UIShowValue.CH_Hold[1].Max);
			FmtToBuf((char*)&BufL[0],"%.2f  ",UIShowValue.CH_Hold[1].Min);
			Ht1621_SHowUpString(&BufH[0]);
			Ht1621_SHowDownString(&BufL[0]);
			LCD_BUF[6]|=S0;//通道二铃显示
			LCD_BUF[14]=S5|S7;//MAXMIN
			break;
		case 2:
			FmtToBuf((char*)&BufH[0],"%.2f  ",UIShowValue.SaveValue.CH_Limit[0].Max);
			FmtToBuf((char*)&BufL[0],"%.2f  ",UIShowValue.SaveValue.CH_Limit[0].Min);
			Ht1621_SHowUpString(&BufH[0]);
			Ht1621_SHowDownString(&BufL[0]);
			LCD_BUF[4]|=S1;//通道一铃显示
			LCD_BUF[4]|=S0;
			break;
		case 3:
			//UIShowValue.UnitFlag=HSF_LPercentage;
			FmtToBuf((char*)&BufH[0],"%.2f ",UIShowValue.SaveValue.CH_Limit[1].Max);
			FmtToBuf((char*)&BufL[0],"%.2f ",UIShowValue.SaveValue.CH_Limit[1].Min);
			Ht1621_SHowUpString(&BufH[0]);
			Ht1621_SHowDownString(&BufL[0]);
			LCD_BUF[6]|=S0;//通道二铃显示
			LCD_BUF[5]|=S0;
			break;
		case 4:
			FmtToBuf((char*)&BufH[0],"   ");
			FmtToBuf((char*)&BufL[0],"%03d   ",UIShowValue.RecordCount);
			Ht1621_SHowUpString(&BufH[0]);
			Ht1621_SHowDownString(&BufL[0]);
			UIShowValue.UnitFlag=0;
			LCD_BUF[14]|=S3|S1;
			break;
	}
	
	LCD_BUF[15]=0;
	Ht1621_DrawTime(UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min);
	Ht1621_DrawBase();
}
