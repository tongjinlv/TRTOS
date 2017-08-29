/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_Insect\GIDE_Driver.h>
#include <STM32_CPU.h>

void GIDE_Beep(void *Tags)
{
	uint16 *P1,*P2,*P3;
	P1=(uint16 *)Tags;
	P2=(uint16 *)((uintbus)Tags+2);
	P3=(uint16 *)((uintbus)Tags+4);
	//DeBug("GIDE_Beep(%d,%d,%d)",*P1,*P2,*P3,5);
	Beep_A2BT(*P1,*P2,*P3);
}
void GIDE_Moto(void *Tags)
{
	char *P1,*P2;
	P1=(char *)Tags;
	P2=(char *)((uintbus)Tags+1);
	Moto_A(*P1);
	Moto_B(*P2);
	//DeBug("GIDE_Moto(%d,%d)",*P1,*P2,5);
}
void GIDE_Eye(void *Tags)
{
	uint8 *P1;
	uint32 P22;
	P1=(uint8 *)Tags;
	//DeBug("GIDE_Eye(%d,%d,%d,%d)",P1[0],P1[1],P1[2],P1[3],5);
	P22=P1[1];
	P22<<=8;
	P22|=P1[2];
	P22<<=8;
	P22|=P1[3];
	switch(P1[0])
	{
		case 1:WS_SetDot(2,P22);WS_SetDot(3,P22);break;
		case 2:WS_SetDot(1,P22);break;
		case 3:WS_SetDot(0,P22);break;
	}
}
void GIDE_Lamp(void *Tags)
{
	uint8 *P1;
	P1=(uint8 *)Tags;
	GPIO_SetIndex(0,!(*P1&S0));
	GPIO_SetIndex(1,!(*P1&S1));
	//DeBug("GIDE_Lamp(%d)",P1[0],5);
}
void GIDE_Delay(void *Tags)
{
	uint32 *P1;
	P1=(uint32 *)Tags;
	Tos_TaskDelay(*P1);
	//DeBug("GIDE_Delay(%d)",*P1,5);
}
void GIDE_Exp(void *Tags)
{
	uint8 *P1;
	uint16 *P2;
	P1=(uint8 *)Tags;
	P2=(uint16 *)((uintbus)Tags+1);
	//DeBug("GIDE_Exp(%d,%d)",*P1,*P2,5);
}
void Task_Exp1(void *Tags)
{
	uint16 P[2],i,Length;
	uint8 *Buf;
	*(uint32 *)&P[0]=(uint32)Tags;
	i=0;
	Length=P[0]-P[1];
	Buf=(uint8 *)((uint32)P[1]+SRAM_BASE);
	while(1)
	{
		Tos_TaskDelay(1);
		if(i>=Length)i=0;
		if(Buf[i]==5)
		{
			i+=GIDEList[Buf[i]].Length;
		}else
		{
			((Tos_Task)(GIDEList[Buf[i]].Value))(&Buf[i+1]);
			i+=GIDEList[Buf[i]].Length;
		}
	}
}
void Task_Export(void *Tags)
{
	uint8 *Buf=(uint8 *)Tags;
	uint16 P[2];
	uint16 i=2;
	uint16 BaseOffset;
	BaseOffset=(uint32)Tags-SRAM_BASE;
	P[0]=BaseOffset+2;P[1]=BaseOffset+2;
	while(1)
	{
		Tos_TaskDelay(1);
		
		if(i>=*(uint16 *)Buf){P[1]=P[0];P[0]=BaseOffset+i;DeBug("E %s,%d,%d",GIDEList[Buf[P[1]-BaseOffset]].Option,P[1]-BaseOffset,P[0]-BaseOffset,6);i=2;Tos_TaskCreateFindID(Task_Exp1,(uintbus)*(uint32 *)&P[0],"Task_GIDE",500);return; }
		if(Buf[i]==5)
			{
				P[1]=P[0];
				P[0]=i+BaseOffset;
				if(P[1]<P[0])
				{
					
					Tos_TaskCreateFindID(Task_Exp1,(uintbus)*(uint32 *)&P[0],"Task_GIDE",500);//堆栈可以获取尾随参数
					DeBug("C %s,%d,%d",GIDEList[Buf[P[1]-BaseOffset]].Option,P[1]-BaseOffset,P[0]-BaseOffset,6);
				}
				
			}
		i+=GIDEList[Buf[i]].Length;
	}
}

void GIDE_Close(void *Tags)
{
	uint32 *P1;
	P1=(uint32 *)Tags;
	DeBug("GIDE_Close(%d)",*P1,5);
	Tos_TaskDelay(*P1);
	Tos_TaskDelete(Tos_TaskCurrent);
}
void GIDE_OFF(void *Tags)
{
	uint32 *P1;
	P1=(uint32 *)Tags;
	DeBug("GIDE_OFF(%d)",*P1,5);
	Tos_TaskDelay(*P1);
	while(1)
	{
		GPIO_SetIndex(6,0);
	}
}

void ECHO_RamUsage(void *Tags)
{
	DeBug("RamUsage[%d]",Mema_Count(),5);
}
void ECHO_CpuUsage(void *Tags)
{
	
	DeBug("CpuUsage[%d]",Tos_CPUInfor.Userate_CPU,5);
}
void ECHO_Temp(void *Tags)
{
	uint8 Buf[15];
	HHT21_Read(IIC_Maps,Buf);
	DeBug("Temp[%.2f℃]",GetTemp(&Buf[3]),1);
}
void ECHO_Humidity(void *Tags)
{
	uint8 Buf[15];
	HHT21_Read(IIC_Maps,Buf);
	DeBug("Humidity[%.2f%%]",GetHmi(&Buf[0]),1);
}
void ECHO_ADC(void *Tags)
{
	uint8 Buf[15];
	uint8 Index;
  FindIntFromString(Tags,Buf,0);
	Index=GetStringToNumber(Buf);
	if(Index>=(sizeof(UIShowValue.ADC)/sizeof(UIShowValue.ADC[0])))
	{
		DeBug("ADC[Error]",1);
		return;
	}
	DeBug("ADC[%d][%d]",Index,UIShowValue.ADC[Index],1);
}
const ECHO_Struct EchoList[]={
	{"[RamUsage]",(void *)&ECHO_RamUsage},
	{"[CpuUsage]",(void *)&ECHO_CpuUsage},
	{"[Humidity]",(void *)&ECHO_Humidity},
	{"[Temp]",(void *)&ECHO_Temp},
	{"[ADC]",(void *)&ECHO_ADC},
	{"End",Null},
};
void GIDE_Echo(void *Tags)
{
	uint8 *P1=(uint8 *)Tags;
	const ECHO_Struct *P=EchoList;
	while(P->Value)
	{
		if(Strstr((const char *)P1,P->Option))
		{
			((Tos_Task)(P->Value))((void*)P1);
			return;
		}
		P++;
	}
	DeBug("Echo(%s)",P1,5);
}

void GIDE_Keys(void *Tags)
{
	uint8 *P1=(uint8 *)Tags;
	switch(P1[0])
	{
		case 1:
			while(!GPIO_GetIndex(7))Tos_TaskDelay(10);
			while(GPIO_GetIndex(7))Tos_TaskDelay(10);
			break;
		case 2:
			while(!GPIO_GetIndex(14))Tos_TaskDelay(10);
			while(GPIO_GetIndex(14))Tos_TaskDelay(10);
			break;
	}
	DeBug("Key(%d)Break",P1[0],5);
}
const GIDE_Struct GIDEList[]={
	{"Beep",(void *)&GIDE_Beep,7,Null},
	{"Moto",(void *)&GIDE_Moto,3,Null},
	{"Eye",(void *)&GIDE_Eye,5,Null},
	{"Delay",(void *)&GIDE_Delay,5,Null},
	{"Lamp",(void *)&GIDE_Lamp,2,Null},
	{"Task",(void *)&Task_Exp1,4,Null},
	{"Close",(void *)&GIDE_Close,5,Null},
	{"OFF",(void *)&GIDE_OFF,5,Null},
	{"Echo",(void *)&GIDE_Echo,12,Null},
	{"Keys",(void *)&GIDE_Keys,2,Null},
	{"End",Null,Null,Null},
};
uint16 GIDE_Export(uint8 *Buf,uint8 *Str)
{
	uint16 i=0,ii=0,l;
	uint8 Data[20];
	float F;
	const GIDE_Struct *P=GIDEList;
	while(P->Value)
	{
		if(Strstr((const char *)Str,P->Option))
		{
			i=0;
			Buf[i++]=ii;
			switch(Buf[0])
			{
				case 0://Beep
					FindIntFromString(Str,Data,0);
					F=GetStringToNumber(Data);
					i+=SetWordToBytes(&Buf[i],F,0);
					FindIntFromString(Str,Data,1);
					F=GetStringToNumber(Data);
					i+=SetWordToBytes(&Buf[i],F,0);
					FindIntFromString(Str,Data,2);
					F=GetStringToNumber(Data);
					i+=SetWordToBytes(&Buf[i],F,0);
					break;
				case 1://Moto
					FindIntFromString(Str,Data,0);
					F=GetStringToNumber(Data);
					Buf[i++]=(char)F;
					FindIntFromString(Str,Data,1);
					F=GetStringToNumber(Data);
					Buf[i++]=(char)F;
					break;
				case 2://Eye
					FindIntFromString(Str,Data,0);
					F=GetStringToNumber(Data);
					Buf[i++]=(uint8)F;
					FindIntFromString(Str,Data,1);
					F=GetStringToNumber(Data);
					Buf[i++]=(uint8)F;
					FindIntFromString(Str,Data,2);
					F=GetStringToNumber(Data);
					Buf[i++]=(uint8)F;
					FindIntFromString(Str,Data,3);
					F=GetStringToNumber(Data);
					Buf[i++]=(uint8)F;
					break;
					case 3://Delay
					FindIntFromString(Str,Data,0);
					F=GetStringToNumber(Data);
					i+=D32ToArray(&Buf[i],F,0);
					break;
					case 4://Lamp
					Buf[i]=0;
					FindIntFromString(Str,Data,0);
					F=GetStringToNumber(Data);
					if(F>0)Buf[i]|=S0;
					FindIntFromString(Str,Data,1);
					F=GetStringToNumber(Data);
					if(F>0)Buf[i]|=S1;
					i++;
					break;
					case 5://Task
					FindIntFromString(Str,Data,0);
					F=GetStringToNumber(Data);
					Buf[i++]=(uint8)F;
					FindIntFromString(Str,Data,1);
					F=GetStringToNumber(Data);
					i+=SetWordToBytes(&Buf[i],F,0);
					break;
					case 6://Close
					FindIntFromString(Str,Data,0);
					F=GetStringToNumber(Data);
					i+=D32ToArray(&Buf[i],F,0);
					break;
					case 7://OFF
					FindIntFromString(Str,Data,0);
					F=GetStringToNumber(Data);
					i+=D32ToArray(&Buf[i],F,0);
					break;
					case 8://Echo
					l=FindStrFromString(Str,Data,0);
					if(l>(P->Length-2))l=P->Length-2;
					Data[l]=0;
					i+=StringCoppy(Data,&Buf[i]);
					i=P->Length;
					break;
					case 9://Keys
					FindIntFromString(Str,Data,0);
					F=GetStringToNumber(Data);
					Buf[i++]=(uint8)F;
					break;
			}
			DeBug("Return.Ok=%d,%d,%d",ii,i,P->Length,0);
			if(i==P->Length)return P->Length;
			else break;
		}
		ii++;
		P++;
	}
	DeBug("Return.Fail=%d",0xff,0);
	return 0;
}
//i 相对flash偏移位置  Data数据 Length长度char宽度
void GIDE_WriteFlash(uint32 i,uint8 *Data,uint32 Length)
{
	#define SmallPageSize 512
	uint16 *P;
	P=(uint16 *)Data;
	IAP_Unlock();
	Length/=2;
	while(Length--)IAP_ProgramHalfWord(GIDE_ADDR_BASE+i++*2,*P++);
	IAP_Lock();
}
void GIDE_Save(uint8 *Buf)
{
	#define SmallPageSize 512
	uint32 Size;
	uint16 i,c=0;
	Size=Mema_GetSize(Buf);
	IAP_Unlock();
	c=Size/SmallPageSize;
	if(Size%SmallPageSize)c++;
	for(i=0;i<c;i++)IAP_ErasePage(GIDE_ADDR_BASE+SmallPageSize*i);
	DeBug("Erase Done!",6);
	IAP_Lock();
	*(uint16 *)&Buf[Size-2]=Tools_GetCRC16(Buf,Size-2);
	GIDE_WriteFlash(0,Buf,Size);
	DeBug("Write Done Crc=%x!",*(uint16 *)&Buf[Size-2],6);
	
}
BOOL GIDE_Load(uint8 *Buf)
{
	uint32 Size,S;
	uint16 i=0;
	uint16 *P;
	P=(uint16 *)Buf;
	Size=Mema_GetSize(Buf);
	S=Size/2;
	BufferFill(&Buf[0],0x00,Size);
	while(S--)*P++=*(uint16 *)(GIDE_ADDR_BASE+i++*2);
	i=Tools_GetCRC16(Buf,Size-2);
	DeBug("Load Done Crc=%x/%x!",i,*(uint16 *)&Buf[Size-2],6);
	if(i==*(uint16 *)&Buf[Size-2])return True;
	return False;
}
uint8 GetKeyBoardVal1ue()
{ 
	uint8 Value=0x00;
	if(GPIO_GetIndex(14))Value=Key_WkUp;
	if(GPIO_GetIndex(7))Value=Key_Enter;
	return Value;
}
void GIDE_CloseAll()
{
	GPIO_SetIndex(0,1);
	GPIO_SetIndex(1,1);
	WS_SetDot(0,0);
	WS_SetDot(1,0);
	WS_SetDot(2,0);
	WS_SetDot(3,0);
	Moto_A(0);
	Moto_B(0);
}
void Task_GIDE(void *Tags)
{
	#define GIDE_BUF_LENGTH 4000
	uint16 Length;
	uint32 i=0;
	uint8 *Buf;
	uint8 PD[20];
	USART_TypeDef *USARTx=(USART_TypeDef *)Tags;
	uint8 UsartCH=USART_GetIndex(USARTx);
	Remap_SWJ_JTAGDisable();
	DeBug_OutSet(DeBug_USART1);
	DeBug_SetType(0xff);
	ADC1_Init((uintbus)&UIShowValue.ADC);
	GPIO_SetIndex(5,0);//关蜂鸣器
	GPIO_SetIndex(2,1);//接近激励
	GPIO_SetIndex(3,1);//接近激励
	GPIO_SetIndex(6,1);//POW1
	GPIO_SetIndex(0,1);//关EYE
	GPIO_SetIndex(1,1);//关EYE
	GPIO_SetIndex(15,0);//IR红外发射
	Printf_SysInfor();//打印系统信息
	WS_SetColorBit(0x0000,S0|S1|S2|S3);
	//BOOL_LoadConfigs();
	Buf=Mema_Malloc(GIDE_BUF_LENGTH);
	//Beep_ON();
	TestStart();
	if(GIDE_Load(Buf))Task_Export((void *)&Buf[0]);
	while(1)
	{
		ClearWithBuffer(USART_RX_Buffer[0],USART_RX_BUFFER_SIZE);
		Length=USART_ReadDatas(USARTx,Null,USART_RX_BUFFER_SIZE,5000);
		if(Length)
		{
			
			if(Strstr((const char *)USART_RX_Buffer[0],"Find"))
			{
				Length=GetCodeStr64(PD);
				DeBug("GID=%s",PD,0);
			}
			else if(Strstr((const char *)USART_RX_Buffer[0],"Start"))
			{
				GIDE_CloseAll();
				DeBug_SetType(1);
				i=2;
				DeBug("Return.StartOk",0);
				while(Tos_TaskDelete(Tos_GetTaskIDByName("Task_GIDE")));	
				BufferFill(&Buf[0],0x00,Mema_GetSize(Buf));
			}
			else if(Strstr((const char *)USART_RX_Buffer[0],"End"))
			{
				*(uint16 *)&Buf[0]=i;
				DeBug("Return.EndOk",0);
				Task_Export((void *)&Buf[0]);
				GIDE_Save(Buf);
				DeBug_SetType(0xff);
			}
			else 
			{
				if(i<(GIDE_BUF_LENGTH-20))
					i+=GIDE_Export(&Buf[i],USART_RX_Buffer[0]);
				else DeBug("Return.SizeOut%d/%d",i,GIDE_BUF_LENGTH,6);
			}
		}else
		{
			DeBug("Return.TimeOut%d",*(uint16 *)&Buf[0],6);
		}
	}
}
void Task_Read(void *Tags)
{
	uint8 Buf[10];
	GYRODataStruct *P=(GYRODataStruct *)Tags;
  GPIO_InitList(MPU_IIC_List);
	InitMPU6050(MPU_IIC_List);
	SHT21Init(IIC_Maps);
	while(1)
	{
		Tos_TaskDelay(100);
		GetAngle(P);
		P->Temperature=(float)GetData(MPU_IIC_List,TEMP_OUT_H)/10;
		//DeBug("X=[%.1f]Y=[%.1f] Z=%.1f T=%.1f",P->Angle,P->Angley,P->Yaw,P->Temperature,0);
		HHT21_Read(IIC_Maps,Buf);
	//	UIShowValue.TempValue=GetHmi(&Buf[0]);
	//	UIShowValue.HumidityValue=GetTemp(&Buf[3]);
	}
}


