/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
/***************************************************************************************************
	* Copyright (c) 2016, Biohermes
	* All rights reserved.
	* �ļ����ƣ� QuectelM26.c
	* ժ Ҫ��    M26ģ��
	* ��ǰ�汾�� V1.0, �׽�, 2016-01-05
	* ���ļ�¼�� ��
***************************************************************************************************/
#include <..\USER\Prj_TP500New\QuectelM26.h>
#include <AT_Command.h>

u8 QuectelM26_Init(void)
{
		uint8 sta;
    M26_POWER_OFF;
    Tos_TaskDelay(1100); 
		DeBug("ϵͳ�ϵ�",Infor_Warning);
    M26_POWER_ON;
    Tos_TaskDelay(1100); 
    M26_RESET_ON;
    Tos_TaskDelay(1100); 
		DeBug("����",Infor_Warning);
    M26_RESET_OFF;
    Tos_TaskDelay(1000);
		if(GPRS_VDDEXT==1)DeBug("�����ɹ�",Infor_Warning);
		else return 1;
	  Tos_TaskDelay(14000);
		if(!GPRS_CommandAck("AT\r\n","OK",1000))return 2;
		DeBug("ATָ��ִ�гɹ�",Infor_Warning);
    Tos_TaskDelay(1000);
		if(!GPRS_CommandAck("ATE0\r\n","OK",2000))return 3;
		DeBug("���ò�����",Infor_Warning);
	  if(!GPRS_CommandAck("AT+CPIN?\r\n","OK",1000))return 4;
		DeBug("�鿴�Ƿ���PIN",Infor_Warning);
    sta=QuectelM26_ConnectNet();                                      //��������
		if(sta)DeBug("������ʧ��[%d]",sta,Infor_Warning);
		else DeBug("��������ɹ�",Infor_Warning);
    return M26_OK;
}

u8 QuectelM26_Connect()
{
	char Buf[100];
	FmtToBuf(&Buf[0],"AT+QIOPEN=\"TCP\",\"%s\",%d\r\n",&UIShowValue.SaveValue.DomainName[0][0],UIShowValue.SaveValue.ServerPort[0]);
	DeBug("���ӵ�:%s",&Buf[0],Infor_Warning);
	return GPRS_Connect(&Buf[0]);
}

u8 QuectelM26_ConnectNet(void)
{
    if(!GPRS_CommandAck("AT+CSQ\r\n","!99",1000))return 1;
		UIShowValue.RSSI=QuectelM26_GetCSQ();
		DeBug("����ź�",Infor_Warning);
		DeBug("����ע��",Infor_Warning);
		if(!GPRS_CommandAck("AT+CREG?\r\n","0",1000));
		if(!GPRS_CommandAckCount("AT+CREG?\r\n","5",1000,2))DeBug("���ؿ�",Infor_Warning);else DeBug("��ؿ�",Infor_Warning);
		if(GPRS_CommandAckCount("AT+COPS?\r\n","MOBILE",1000,2)){DeBug("�й��ƶ�SIM��",Infor_Warning);UIShowValue.SIMType=ST_CHINA_MOBILE;}
		else if(GPRS_CommandAckCount("AT+COPS?\r\n","UNICOM",1000,2)){DeBug("�й���ͨSIM��",Infor_Warning);UIShowValue.SIMType=ST_CHINA_UNINET;}
		DeBug("ע��ɹ�",Infor_Warning);
		return 0;
}

u8 QuectelM26_CreateCFG(u8 *Buf)
{
	uint16 i=0;
	Buf[i++]=0x10;//��Ϣ���ͣ�������Ϣ ��UDPͨ��QOS����һ��
	Buf[i++]=0xff;//���ݳ��ȣ�������127���ֽ�һ��ֻ��Ҫһ���ֽڱ�ʾ
	Buf[i++]=0x00;//�汾
	Buf[i++]=0x04;//���ӱ�־
	i+=BufferCoppy("MQTT",&Buf[i],4);
	Buf[i++]=0x04;//Э��汾
	Buf[i++]=0x02;//���ӱ�־
	Buf[i++]=0x00;//
	Buf[i++]=0x3c;//���ֻ����
	Buf[i++]=0x00;//
	Buf[i++]=0x10;//����
	i+=BufferCoppy(&UIShowValue.SaveValue.LoginHead[0],&Buf[i],sizeof(UIShowValue.SaveValue.LoginHead));
	Buf[1]=i-2;
	return i;
}

BOOL GPRS_Printf(uint16 Wating)//��ӡ���յ�������
{
	uint8 i=1;
	uint8 Length;
	while(i--)
	{
		BufferFill(USART_RX_Buffer[1],0x00,USART_RX_BUFFER_SIZE);
		Length=USART_ReadDatas(USART2,Null,50,Wating);
		if(Length)
		{
			if(strstr((const char *)USART_RX_Buffer[1],"CLOSED")){DeBug("���ӱ��ر�",Infor_Warning);return False;}
			else {QuectelM26Printf_Bytes("R:",USART_RX_Buffer[1],Length);return True;}
		}
	}
	return False;
}

u8 QuectelM26_SendData()
{
	uint8 Buf[500];
	uint8 LengthSize=2;
	uint16 i=0;
	Buf[i++]=0x32;//��Ϣ���ͣ�������Ϣ ��UDPͨ��QOS����һ��
	i+=LengthSize;
	Buf[i++]=0x00;//�汾
	Buf[i++]=0x10;//���ӱ�־
	i+=BufferCoppy(&UIShowValue.SaveValue.LoginHead[0],&Buf[i],sizeof(UIShowValue.SaveValue.LoginHead));
	Buf[i++]=0x00;//
	Buf[i++]=0x01;//dd
	UIShowValue.CH_Value[0]+=0.4;
	i+=GetStringByFmt((char *)&Buf[i],"{\"sensorDatas\":[");
	i+=GetStringByFmt((char *)&Buf[i],"{\"value\":+%.2f},",UIShowValue.CH_Value[0]);
	i+=GetStringByFmt((char *)&Buf[i],"{\"value\":+%.2f},",UIShowValue.CH_Value[1]);
	i+=GetStringByFmt((char *)&Buf[i],"{\"value\":+%.2f},",UIShowValue.CH_Value[2]);
	i+=GetStringByFmt((char *)&Buf[i],"{\"value\":+%.2f},",(float)UIShowValue.RSSI);
	i+=GetStringByFmt((char *)&Buf[i],"{\"lat\":%.7f,\"lng\":%.7f}",UIShowValue.GPS_Latitude,UIShowValue.GPS_Longitude);
	i+=GetStringByFmt((char *)&Buf[i],"]}");
	MQTT_LegnthToByte(i-LengthSize-1,&Buf[1]);
//	USART_WriteDatas(USART1,&Buf[0],i);
	USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
	if(!GPRS_AckDelay(">",2000))return 1;
	USART_WriteDatas(USART2,&Buf[0],i);
	if(!GPRS_AckDelay("SEND OK",1000))return 2;//��鷢�ͳɹ�
	GPRS_Printf(2000);
	return 0;
}
u8 QuectelM26_SendHeartbeat()
{
	uint8 Buf[200];
	uint16 i=0;
	Buf[i++]=0xc0;
	Buf[i++]=0x00;
	USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
	if(!GPRS_AckDelay(">",2000))return 1;
	USART_WriteDatas(USART2,&Buf[0],i);
	if(!GPRS_AckDelay("SEND OK",1000))return 2;//��鷢�ͳɹ�
	if(!GPRS_Printf(2000))return 0;
	return 0;
}
u8 QuectelM26_SendCFG()
{
	uint8 Buf[200];
	uint16 i=0;
	Tos_TaskDelay(3000);
	i=QuectelM26_CreateCFG(&Buf[0]);
	USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
	if(GPRS_AckDelay(">",2000))goto OK;
	if(GPRS_AckDelay(">",2000))goto OK;
	if(GPRS_AckDelay(">",2000))goto OK;
OK:
	USART_WriteDatas(USART2,&Buf[0],i);
	if(!GPRS_AckDelay("SEND OK",1000))return 2;//��鷢�ͳɹ�
	GPRS_Printf(2000);
	return 0;
}

u8 QuectelM26_SendTextMsg(u8 *string)
{
	u8 ret;
	uint8 Buf[20];
	BufferCoppy(&UIShowValue.SaveValue.CallNumber[0][0],&Buf[0],sizeof(UIShowValue.SaveValue.CallNumber[0]));
	Buf[sizeof(UIShowValue.SaveValue.CallNumber[0])]=0;
	if(GetTextLength(&Buf[0])<11)return 2;
	QuectelM26_InitSMS(1);
	USART_WriteLine(USART2,"AT+CMGS=\"%s\"\r\n",&Buf[0]);
	DeBug("Buf[%s]",&Buf[0],Infor_Warning);
	if(!GPRS_AckDelay(">",2000))return 1;
	USART_WriteLine(USART2,(char *)string);
	USART_WriteData(USART2,0x1a);                                        //��������
	GPRS_AckDelay("CMGS", 1000);                            //���ݷ���״̬
	return ret;
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
u8 PDU_CreateMsg(uint8 *Buf,uint8 *SNum,uint8 *PDUMsg,uint8 MsgLength)
{
	uint8 i=0;
	i+=BufferCoppy("089168",&Buf[i],6);
	if(UIShowValue.SIMType==ST_CHINA_MOBILE)
	{	
		i+=PDU_NumSwitch("13800100500",&Buf[i]);
	}else i+=PDU_NumSwitch("13010112500",&Buf[i]);
	i+=BufferCoppy("011000D9168",&Buf[i],11);
	i+=PDU_NumSwitch(SNum,&Buf[i]);
	i+=BufferCoppy("70008B0",&Buf[i],7);
	//Buf[i++]=MsgLength/10+'0';
	//Buf[i++]=MsgLength%10+'0';
	i+=GetStringByFmt((char*)&Buf[i],"%02X",MsgLength);
	i+=BufferCoppy(PDUMsg,&Buf[i],MsgLength*2);
	DeBug("Buf[%s]",&Buf[0],Infor_Warning);
	return i;
}
u8 QuectelM26_SendPDUMsg(u8 *string)
{
	u8 ret;
	QuectelM26_InitSMS(0);
	ret=GetTextLength(&string[0])/2-9;
	USART_WriteLine(USART2,"AT+CMGS=%d\r\n",ret);
	USART_WriteLine(USART1,"AT+CMGS=%d\r\n",ret);
	if(!GPRS_AckDelay(">",2000))return 1;
	USART_WriteLine(USART2,(char *)string);
	USART_WriteData(USART2,0x1a);                                        //��������
	GPRS_AckDelay("CMGS", 1000);                            //���ݷ���״̬
	return ret;
}

void QuectelM26_Config()
{
	uint8 sta;
	sta=QuectelM26_SendCFG();
	if(sta)DeBug("��������֡ʧ��[%d]",sta,Infor_Warning);
	else DeBug("��������֡�ɹ�",Infor_Warning);
}
void Task_SendMsg()
{
	char Buf[100];
	static uint32 OLDFlag=0xffffffff;
	uint32 ThisBit;
	ThisBit=UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH1Min|WRF_CH2Max|WRF_CH2Min);
	if(ThisBit!=OLDFlag)if(OLDFlag!=0xffffffff)
	{
		GetStringByFmt(&Buf[0],"CH1=%.2f,CH2:%.2f",UIShowValue.CH_Value[0],UIShowValue.CH_Value[1]);
		if(UIShowValue.RunFlag&WRF_CH1Max)GetStringByFmt(&Buf[0],"CH1=%.2f,MAX:%.2f",UIShowValue.CH_Value[0],UIShowValue.SaveValue.CH_Limit[0].Max);
		if(UIShowValue.RunFlag&WRF_CH2Max)GetStringByFmt(&Buf[0],"CH2=%.2f,MAX:%.2f",UIShowValue.CH_Value[1],UIShowValue.SaveValue.CH_Limit[1].Max);
		if(UIShowValue.RunFlag&WRF_CH1Min)GetStringByFmt(&Buf[0],"CH1=%.2f,Min:%.2f",UIShowValue.CH_Value[0],UIShowValue.SaveValue.CH_Limit[0].Min);
		if(UIShowValue.RunFlag&WRF_CH2Min)GetStringByFmt(&Buf[0],"CH2=%.2f,Min:%.2f",UIShowValue.CH_Value[1],UIShowValue.SaveValue.CH_Limit[1].Min);
		QuectelM26_SendTextMsg((uint8*)&Buf[0]);
		DeBug("���Ͷ���[%s]",(char *)Buf,Infor_Warning);
		Tos_TaskDelay(5000);
	}
	OLDFlag=UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH1Min|WRF_CH2Max|WRF_CH2Min);
}
void Task_M26(void *Tags)
{
	uint8 Buf[200];
	uint8 sta,i,FailCount=0,RFailCount;
R:
	RFailCount=0;
	UIShowValue.RSSI=99;
	sta=QuectelM26_Init();
	if(sta)DeBug("ע������ʧ��[%d]",sta,Infor_Error);
	sta=QuectelM26_InitSMS(1);
	if(sta)DeBug("��ʼ������[%d]",sta,Infor_Warning);
	sta=QuectelM26_Connect();
	if(sta)DeBug("���ӷ�����[%d]",sta,Infor_Warning);
	Tos_TaskDelay(1000);
	QuectelM26_Config();
		//QuectelM26_SendTextMsg("fdddddddddddddddddddddddd");
	PDU_CreateMsg(&Buf[0],"13267216247","4E0D77E59053",6);
	QuectelM26_SendPDUMsg(&Buf[0]);
	while(1)
	{
		sta=QuectelM26_SendData();
		if(sta){DeBug("��������ʧ��[%d]",sta,Infor_Warning);FailCount++;}
		else {DeBug("��������OK",Infor_Warning);FailCount=0;RFailCount=0;}
		for(i=0;i<5;i++)
		{
			Task_SendMsg();
			UIShowValue.RSSI=QuectelM26_GetCSQ();
			//QuectelM26_ReadShow("AT+CMGL=\"ALL\"\r\n");��ȡ����
			//QuectelM26_ReadShow("AT+COPS?\r\n");
			sta=QuectelM26_SendHeartbeat();
			if(sta){DeBug("��������ʧ��[%d]",sta,Infor_Warning);FailCount++;}
			else {DeBug("��������OK",Infor_Warning);RFailCount=0;FailCount=0;}
			if(FailCount>0){QuectelM26_Connect();FailCount=0;QuectelM26_Config();RFailCount++;}
			Tos_TaskDelay(20000);
		}
		if(RFailCount>5)goto R;
	}
}
