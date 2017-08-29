/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <AT_Command.h>
#include <include.h>
#include <Driver_Include.h>



BOOL GPRS_Ack(uint8 *Ack,uint16 Wating)
{
	uint8 i=1;
	uint8 Length;
	while(i--)
	{
		BufferFill(USART_RX_Buffer[1],0x00,USART_RX_BUFFER_SIZE);
		Length=USART_ReadDatas(USART2,Null,50,Wating);
		if(Length)
		{
			DeBug("����:%s\r\n",USART_RX_Buffer[1],Infor_Warning);
			if(Strstr((const char *)USART_RX_Buffer[1],(const char *)Ack))return True;
		}
	}
	return False;
}
BOOL GPRS_AckTwo(uint8 *Ack,uint8 *Ack1,uint16 Wating)
{
	uint8 i=1;
	uint8 Length;
	while(i--)
	{
		BufferFill(USART_RX_Buffer[1],0x00,USART_RX_BUFFER_SIZE);
		Length=USART_ReadDatas(USART2,Null,50,Wating);
		if(Length)
		{
			DeBug("����:%s\r\n",USART_RX_Buffer[1],Infor_Warning);
			if(Strstr((const char *)USART_RX_Buffer[1],(const char *)Ack))return True;
			if(Strstr((const char *)USART_RX_Buffer[1],(const char *)Ack1))return True;
		}
	}
	return False;
}
BOOL GPRS_WhileAck(uint8 *Ack,uint8 *Ack1,uint8 Sec)
{
	uint8 c;
	for(c=0;c<Sec;c++)
	{
		if(GPRS_AckTwo(Ack,Ack1,1000))return True;
	}
	return False;
}
BOOL GPRS_AckDelay(uint8 *Ack,uint16 Wating)
{
	uint8 i=1;
	uint8 Length;
	while(i--)
	{
		BufferFill(USART_RX_Buffer[1],0x00,USART_RX_BUFFER_SIZE);
		Length=USART_ReadDatas(USART2,Null,50,Wating);
		if(Length)
		{
			DeBug("����:%s\r\n",USART_RX_Buffer[1],Infor_Warning);
			if(strstr((const char *)USART_RX_Buffer[1],(const char *)Ack))return True;
			Tos_TaskDelay(1000);
		}
		Tos_TaskDelay(1000);
	}
	return False;
}
u8 GPRS_CloseNet(void)
{
	uint8 i=2,c;
	while(i--)
	{
	  USART_WriteLine(USART2,"AT+QICLOSE\r\n");
		Tos_TaskDelay(1000);
		for(c=0;c<3;c++)if(GPRS_CommandAck("AT+QISTATE\r\n","CLOSE",2000))goto OK;
	}
	return 1;
OK:
	DeBug("Socket�Ͽ�",Infor_Warning);
	UIShowValue.RunFlag&=~WRF_GPRS_Connected;
	return 0;
}
u8 GPRS_ToSleep(void)
{
	uint8 i=2,c;
	while(i--)
	{
		Tos_TaskDelay(1000);
		for(c=0;c<3;c++)if(GPRS_CommandAck("AT+QSCLK=1\r\n","OK",2000))goto OK;
	}
	return 1;
OK:
	DeBug("����˯��ʹ��",Infor_Warning);
	return 0;
}
u8 GPRS_Connect(char *Cmd)
{
	uint8 i=0;
R:
	if(i++>5)return 3;
	DeBug("���ӷ�����",Infor_Warning);
	UIShowValue.RunFlag&=~WRF_GPRS_Connected;
	if(GPRS_CheckIpTrue(Cmd)){if(!GPRS_CommandAck("AT+QIDNSIP=0\r\n","OK",1000))return 1;}
	else if(!GPRS_CommandAck("AT+QIDNSIP=1\r\n","OK",1000))return 1;
	Tos_TaskDelay(1000);
	USART_WriteLine(USART2,Cmd);
	if(!GPRS_WhileAck("CONNECT OK","ALREADY CONNECT",4))goto R;
	Tos_TaskDelay(2000);
	DeBug("���ӳɹ�",Infor_Warning);
	UIShowValue.RunFlag|=WRF_GPRS_Connected;
	return 0;
}
u8 QuectelM26_SendMsg(u8 *string)
{
	uint8 Num[20],Buf[400];
	StringCoppy("10086",&Num[0]);
	QuectelM26_InitSMS(1);
	GBKToUniCode(&Num[0],&Buf[0]);
	Buf[20]=0x00;
	USART_WriteLine(USART2,"AT+CMGS=\"%s\"\r\n",&Buf[0]);
	DeBug("���͵�[%s]",&Num[0],Infor_Warning);
	Tos_TaskDelay(1000);
	GBKToUniCode(&string[0],&Buf[0]);
	Buf[GetTextLength(string)*4]=0x00;
	USART_WriteLine(USART2,(char *)Buf);
	USART_WriteData(USART2,0x1a);                                        //��������
	GPRS_AckDelay("CMGS", 1000);                            //���ݷ���״̬
	Tos_TaskDelay(5000);
	return 0;
}

BOOL GPRS_OldAck(uint8 *Ack)
{

	if(strstr((const char *)USART_RX_Buffer[1],(const char *)Ack))return True;
	return False;
}
BOOL GPRS_CommandAckCount(char *Send,uint8 *Ack,uint16 Wating,uint8 i)
{
	uint8 Length;
	while(i--)
	{
		USART_WriteLine(USART2,Send);
		BufferFill(USART_RX_Buffer[1],0x00,USART_RX_BUFFER_SIZE);
		Length=USART_ReadDatas(USART2,Null,50,Wating);
		if(Length)
		{
			 DeBug("����%s\r\n",USART_RX_Buffer[1],Infor_Warning);
			 if(Ack[0]=='!')
			 {
				 if(!strstr((const char *)USART_RX_Buffer[1],(const char *)&Ack[1]))return True;
			 }else 
			 if(strstr((const char *)USART_RX_Buffer[1],(const char *)Ack))return True;
			Tos_TaskDelay(1000);
		}
		Tos_TaskDelay(1000);
	}
	return False;
}
BOOL GPRS_CommandAck(char *Send,uint8 *Ack,uint16 Wating)
{
	DeBug("����%s\r\n",Send,Infor_Warning);
	return GPRS_CommandAckCount(Send,Ack,Wating,10);
}
uint8 QuectelM26_GetNumString(uint8 *Cmd,uint8 *Data,uint8 index)
{
	uint8 Length,i,c=0,t,has=0,z=0;
	USART_WriteLine(USART2,(char *)Cmd);
	BufferFill(USART_RX_Buffer[1],0x00,USART_RX_BUFFER_SIZE);
	Length=USART_ReadDatas(USART2,Null,50,1000);
	if(Length)
	{
		Data[0]=0;
		for(i=0;i<Length;i++)
		{
			t=USART_RX_Buffer[1][i];
			if((t>='0')&(t<='9')){if(index==z)Data[c++]=t;has=1;}
			else if(has){if(index==z)Data[c++]=0;has=0;z++;}
		}	
	}
	return c;
}
BOOL CheckCallNumber(uint8 *Buf)
{
	int i;
	for(i=0;i<11;i++)
	{
		if((Buf[i]>'9')|(Buf[i]<'0'))return False;
	}
	return True;
}
uint8 PDU_GetCenterNumber()
{
	uint8 Buf[30],l;
	l=QuectelM26_GetNumString("AT+CSCA?\r\n",Buf,0);
	if(l)
	{
		
		if(CheckCallNumber(&Buf[0]))
		{
			DeBug("�������ĺ���:[%s]",Buf,Infor_Warning);
			BufferCoppy(&Buf[2],&UIShowValue.SMSCenterNum[0],sizeof(UIShowValue.SMSCenterNum));
		}
	}
	return l;
}

//Mode=0 PDU Mode=1 Text
u8  QuectelM26_InitSMS(uint8 Mode)
{
    Tos_TaskDelay(1000);
		if(!GPRS_CommandAck("AT+CPMS=\"MT\",\"MT\",\"MT\"\r\n","CPMS",1000))return 1;
    if(Mode==0)
		{
			if(!GPRS_CommandAck("AT+CMGF=0\r\n","OK",1000))return 2;
			if(!GPRS_CommandAck("AT+CSCS=\"UCS2\"\r\n","OK",1000))return 4;
		}
    if(Mode==1)
		{
			if(!GPRS_CommandAck("AT+CMGF=1\r\n","OK",1000))return 3;
			if(!GPRS_CommandAck("AT+CSCS=\"UCS2\"\r\n","OK",1000))return 4;
		}
		
		if(!GPRS_CommandAck("AT+CSMP=17,167,0,8\r\n","OK",1000))return 5;
	  //if(!GPRS_CommandAck("AT+CSMP=49,167,0,0\r\n","OK",1000))return 5;
		if(!GPRS_CommandAck("AT+CNMI=2,1,0,0,0\r\n","OK",1000))return 6;
    return 0;
}
void QuectelM26Printf_Bytes(uint8 *Msg,uint8 *Bytes,uint16 Length)
{
	uint16 i;
	DeBug("%s",Msg,Infor_Warning);
	for(i=0;i<Length;i++)DeBug("Buf[%d]=0x%x",i,Bytes[i],Infor_Warning);
}
uint8 QuectelM26_GetValue(uint8 *Cmd,uint8 *Data)
{
	uint8 Length,i,c=0,t,has=0;
	USART_WriteLine(USART2,(char *)Cmd);
	BufferFill(USART_RX_Buffer[1],0x00,USART_RX_BUFFER_SIZE);
	Length=USART_ReadDatas(USART2,Null,50,1000);
	if(Length)
	{
		Data[0]=0;
		for(i=0;i<Length;i++)
		{
			t=USART_RX_Buffer[1][i];
			if((t>='0')&(t<='9')){Data[c]*=10;Data[c]+=t-'0';has=1;}
			else if(has){c++;Data[c]=0;has=0;}
		}
		
	}
	return c;
}

uint8 QuectelM26_GetCSQ()
{
	uint8 Buf[3];
	QuectelM26_GetValue("AT+CSQ\r\n",&Buf[0]);
	DeBug("�ź�ǿ��:%d",Buf[0],Infor_Warning);
	return Buf[0];
}
BOOL GPRS_PrintfString(uint16 Wating)//��ӡ���յ�������
{
	uint8 i=1;
	uint8 Length;
	while(i--)
	{
		
		Length=USART_ReadDatas(USART2,Null,USART_RX_BUFFER_SIZE,Wating);
		if(Length)
		{
			DeBug("R:%s",USART_RX_Buffer[1],Infor_Warning);return True;
		}
	}
	return False;
}
uint8 PDU_NumSwitch(uint8 *Num,uint8 *Buf)
{
	uint8 i=0;
	for(i=0;i<6;i++)
	{
		Buf[i*2+1]=Num[i*2];
		Buf[i*2]=Num[i*2+1];
	}
	i--;i*=2;
	Buf[i++]='F';
	return i;
}

uint16 PDU_CreateMsg(uint8 *Buf,uint8 *SNum,uint8 *PDUMsg,uint16 MsgLength)
{
	uint16 i=0;
	i+=BufferCoppy("089168",&Buf[i],6);
	i+=PDU_NumSwitch(&UIShowValue.SMSCenterNum[0],&Buf[i]);
	i+=BufferCoppy("011000D9168",&Buf[i],11);
	i+=PDU_NumSwitch(SNum,&Buf[i]);
	i+=BufferCoppy("70008B0",&Buf[i],7);
	i+=GetStringByFmt((char*)&Buf[i],"%02X",MsgLength);
	i+=BufferCoppy(PDUMsg,&Buf[i],MsgLength*2);
	return i;
}
uint16 QuectelM26_SendPDUMsg(u8 *string)
{
	uint16 ret;uint16 i;
	uint8 Buf[500],Buf1[400],Num[12];
	if(!CheckCallNumber(&UIShowValue.SaveValue.CallNumber[0][0]))return 1;
	BufferCoppy(&UIShowValue.SaveValue.CallNumber[0][0],&Num[0],sizeof(UIShowValue.SaveValue.CallNumber[0]));
	Num[11]=0;
	i=GBKToUniCode(string,Buf1);
	PDU_CreateMsg(&Buf[0],Num,Buf1,i/2);
	QuectelM26_InitSMS(0);
	ret=GetTextLength(&Buf[0])/2-9;
	USART_WriteLine(USART2,"AT+CMGS=%d\r\n",ret);
	DeBug("AT+CMGS=%d\r\n",ret,Infor_Warning);
	if(!GPRS_AckDelay(">",2000))return 1;
	USART_WriteLine(USART2,(char *)Buf);
	USART_WriteData(USART2,0x1a);                                        //��������
	GPRS_AckDelay("CMGS", 1000);                            //���ݷ���״̬
	return 0;
}
uint8  QuectelM26_ReadShow(uint8 *Cmd)
{
	uint8 Length;
	BufferFill(USART_RX_Buffer[1],0x00,USART_RX_BUFFER_SIZE);
	USART_WriteLine(USART2,(char *)Cmd);
	Length=USART_ReadDatas(USART2,Null,USART_RX_BUFFER_SIZE,1000);
	if(Length)
	{
		DeBug("�����ŷ���:%s",USART_RX_Buffer[1],Infor_Warning);
		return Length;
	}
	return 0;
}
u8 QuectelM26_SendTextMsg(u8 *string);
void MSG_Delete()
{
	DeBug("ɾ����Ϣ",Infor_Warning);//Ҫ��ɾ��Ϣ�ٶ������꣬�ٴη���Ϣ��ɾ����
	USART_WriteLine(USART2,"AT+CMGD=1,4\r\n");//ɾ��
	GPRS_Ack("OK",1000);
}
void QuectelM26_ShowSMS()
{
	uint8 Buf[300],*P,l;
	GetStringByFmt((char *)&Buf[0],"AT+CMGR=%d\r\n",1);
	l=QuectelM26_ReadShow(&Buf[0]);
	P=(uint8 *)Strstr((const char *)USART_RX_Buffer[1],"\",\"");
	FindHexFromString(P,&Buf[0],0);
	StrToGBK(&Buf[0],&Buf[0]);
	if(l<15){	DeBug("��������Ϣ",Infor_Warning);return;}
	DeBug("Num:%s",&Buf[0],Infor_Warning);
	if(GetTextLength(&Buf[0])<11){MSG_Delete();DeBug("�����˷���ֱ��ɾ",Infor_Warning);return;}
	P=(uint8 *)Strstr((const char *)P,"0043004D0044003A");
	FindHexFromString(P,&Buf[0],0);
	StrToGBK(&Buf[0],&Buf[0]);
	DeBug("Msg:%s",&Buf[0],Infor_Warning);
	if(Strstr((const char*)&Buf[0],"01"))
	{
		MSG_Delete();
		GetStringByFmt((char *)&Buf[0],"CH1=%.2f,CH2=%.2f",UIShowValue.CH_Value[0],UIShowValue.CH_Value[1]);
		QuectelM26_SendTextMsg(&Buf[0]);return;
	}
	if(Strstr((const char*)&Buf[0],"02"))
	{
		MSG_Delete();
		MCU_Reset();
	}
	if(Strstr((const char*)&Buf[0],"03"))
	{
		MSG_Delete();
		l=GetStringByFmt((char *)&Buf[0],"%s","�ݲ�֧��[03]ָ��");Buf[l]=0;
		QuectelM26_SendTextMsg(&Buf[0]);return;
	}
	if(Strstr((const char*)&Buf[0],"04"))
	{
		MSG_Delete();
		l=GetStringByFmt((char *)&Buf[0],"%s","�ݲ�֧��[04]ָ��");Buf[l]=0;
		QuectelM26_SendTextMsg(&Buf[0]);return;
	}
	if(Strstr((const char*)&Buf[0],"05"))
	{
		MSG_Delete();
		l=GetStringByFmt((char *)&Buf[0],"%s","�ݲ�֧��[05]ָ��");Buf[l]=0;
		QuectelM26_SendTextMsg(&Buf[0]);return;
	}
	MSG_Delete();
	QuectelM26_SendTextMsg("CMD:01(ң��),CMD:02(����),����:����");

}

	uint8 Task_SendMsg()
{
	uint8 i=0,c=0;
	char Buf[200];
	static uint8 OLDFlag=0xff,z=0;
	uint8 ThisBit;
	ThisBit=UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH1Min|WRF_CH2Max|WRF_CH2Min);
	DeBug("Count=%d,CH1=%.2f,CH2:%.2f",z,UIShowValue.CH_Value[0],UIShowValue.CH_Value[1],Infor_Warning);
	if(OLDFlag==0xff)OLDFlag=ThisBit;
	if(ThisBit!=OLDFlag)
	{
		z++;
		if(z>UIShowValue.SaveValue.SendSMSDelay)
		{
		c=StringCoppy(&UIShowValue.SaveValue.PrintfTitle[0],&Buf[0]);
		i=GetStringByFmt(&Buf[c],"�ָ�CH1=%.2f,CH2:%.2f",UIShowValue.CH_Value[0],UIShowValue.CH_Value[1]);
		if(UIShowValue.RunFlag&WRF_CH1Max)i=GetStringByFmt(&Buf[c],"����CH1=%.2f,MAX:%.2f",UIShowValue.CH_Value[0],UIShowValue.SaveValue.CH_Limit[0].Max);
		if(UIShowValue.RunFlag&WRF_CH1Min)i=GetStringByFmt(&Buf[c],"����CH1=%.2f,Min:%.2f",UIShowValue.CH_Value[0],UIShowValue.SaveValue.CH_Limit[0].Min);
		if(UIShowValue.RunFlag&WRF_CH2Max)i=GetStringByFmt(&Buf[c],"����CH2=%.2f,MAX:%.2f",UIShowValue.CH_Value[1],UIShowValue.SaveValue.CH_Limit[1].Max);
		if(UIShowValue.RunFlag&WRF_CH2Min)i=GetStringByFmt(&Buf[c],"����CH2=%.2f,Min:%.2f",UIShowValue.CH_Value[1],UIShowValue.SaveValue.CH_Limit[1].Min);
		i+=c;
		if(i%2==1)i+=GetStringByFmt(&Buf[i]," ");
		DeBug("��������[%d]:%s",i,&Buf[0],Infor_Warning);
		i=QuectelM26_SendTextMsg((uint8*)&Buf[0]);
		Tos_TaskDelay(5000);
		OLDFlag=ThisBit;
		}
	}
	if(ThisBit==OLDFlag)z=0;
	return i;
}
	uint8 Task_SendWhileMsg()
{
	uint8 i=0,c=0;
	char Buf[200];
	static uint16 z=0;
	uint8 ThisBit;
	ThisBit=UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH1Min|WRF_CH2Max|WRF_CH2Min);
	DeBug("Count=%d,CH1=%.2f,CH2:%.2f",z,UIShowValue.CH_Value[0],UIShowValue.CH_Value[1],Infor_Warning);
	if(ThisBit>0)
	{
		z++;
		if(z%50==UIShowValue.SaveValue.SendSMSDelay)
		{
		c=StringCoppy(&UIShowValue.SaveValue.PrintfTitle[0],&Buf[0]);
		i=GetStringByFmt(&Buf[c],"�ָ�CH1=%.2f,CH2:%.2f",UIShowValue.CH_Value[0],UIShowValue.CH_Value[1]);
		if(UIShowValue.RunFlag&WRF_CH1Max)i=GetStringByFmt(&Buf[c],"����CH1=%.2f,MAX:%.2f",UIShowValue.CH_Value[0],UIShowValue.SaveValue.CH_Limit[0].Max);
		if(UIShowValue.RunFlag&WRF_CH1Min)i=GetStringByFmt(&Buf[c],"����CH1=%.2f,Min:%.2f",UIShowValue.CH_Value[0],UIShowValue.SaveValue.CH_Limit[0].Min);
		if(UIShowValue.RunFlag&WRF_CH2Max)i=GetStringByFmt(&Buf[c],"����CH2=%.2f,MAX:%.2f",UIShowValue.CH_Value[1],UIShowValue.SaveValue.CH_Limit[1].Max);
		if(UIShowValue.RunFlag&WRF_CH2Min)i=GetStringByFmt(&Buf[c],"����CH2=%.2f,Min:%.2f",UIShowValue.CH_Value[1],UIShowValue.SaveValue.CH_Limit[1].Min);
		i+=c;
		if(i%2==1)i+=GetStringByFmt(&Buf[i]," ");
		DeBug("��������[%d]:%s",i,&Buf[0],Infor_Warning);
		i=QuectelM26_SendTextMsg((uint8*)&Buf[0]);
		Tos_TaskDelay(5000);
		}
	}else z=0;
	return i;
}

void Task_SendHttp(uint8 *Msg)
{
	//if(!GPRS_CommandAck("AT+SAPBR=1,1\r\n","OK",1000))return;
	if(!GPRS_CommandAck("AT+HTTPINIT\r\n","OK",1000))return;
	if(!GPRS_CommandAck("AT+HTTPPARA=\"CID\",1\r\n","OK",1000))return;
	if(!GPRS_CommandAck("AT+HTTPPARA=\"URL\",\"http://larriesun.com/?id=5&statu=1&time=10\"\r\n","OK",1000))return;
	if(!GPRS_CommandAck("AT+HTTPACTION=0\r\n","OK",1000))return;
	GPRS_PrintfString(3000);
	
}
