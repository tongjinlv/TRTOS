/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_TP502T\QuectelM26.h>
#include <AT_Command.h>
#include <..\USER\Prj_TP502T\Auto_Register.h>
u8 QuectelM26_Init(void)
{
		uint8 sta;
    M26_POWER_OFF;
		UIShowValue.RunFlag&=~WRF_SIMConnected;
    Tos_TaskDelay(1100); 
		DeBug("GPRS�ϵ�",Infor_Warning);
    M26_POWER_ON;
    Tos_TaskDelay(1100); 
    M26_RESET_ON;
    Tos_TaskDelay(1100); 
		DeBug("GPRS����",Infor_Warning);
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
		UIShowValue.RunFlag|=WRF_SIMConnected;
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
/***************************************************************************************************
 * �� �� ��: QuectelM26_ConnectNet
 * ��������: ģ����������
 * ����˵��: ��
 * ���ú���: ��
 * ȫ�ֱ���: ��
 * �䡡����: ��
 * ��������: ������
***************************************************************************************************/
u8 QuectelM26_ConnectNet(void)
{
		uint8 R=0;
    if(!GPRS_CommandAck("AT+CSQ\r\n","!99",2000))R=1;
		UIShowValue.RSSI=QuectelM26_GetCSQ();
		DeBug("����ź�",Infor_Warning);
		DeBug("����ע��",Infor_Warning);
		if(!GPRS_CommandAck("AT+CREG?\r\n","0",1000));
		if(!GPRS_CommandAckCount("AT+CREG?\r\n","5",1000,2))DeBug("���ؿ�",Infor_Warning);else DeBug("��ؿ�",Infor_Warning);
		if(GPRS_CommandAckCount("AT+COPS?\r\n","MOBILE",1000,2)){DeBug("�й��ƶ�SIM��",Infor_Warning);UIShowValue.SIMType=ST_CHINA_MOBILE;}
		else if(GPRS_CommandAckCount("AT+COPS?\r\n","UNICOM",1000,2)){DeBug("�й���ͨSIM��",Infor_Warning);UIShowValue.SIMType=ST_CHINA_UNINET;}
		DeBug("ע��ɹ�",Infor_Warning);
		return R;
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
			else {QuectelM26Printf_Bytes("����:",USART_RX_Buffer[1],Length);return True;}
		}
	}
	return False;
}

u8 QuectelM26_SendData()
{
	uint8 Buf[500];
	uint8 LengthSize=2;
	uint8 c,c1;
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		Buf[i++]=0x32;//��Ϣ���ͣ�������Ϣ ��UDPͨ��QOS����һ��
		i+=LengthSize;
		Buf[i++]=0x00;//�汾
		Buf[i++]=0x10;//���ӱ�־
		i+=BufferCoppy(&UIShowValue.SaveValue.LoginHead[0],&Buf[i],sizeof(UIShowValue.SaveValue.LoginHead));
		Buf[i++]=0x00;//
		Buf[i++]=0x01;//dd
		i+=GetStringByFmt((char *)&Buf[i],"{\"sensorDatas\":[");
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[0]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[1]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[2]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",(float)UIShowValue.RSSI);
		i+=GetStringByFmt((char *)&Buf[i],"{\"lat\":%.7f,\"lng\":%.7f}",UIShowValue.GPS_Latitude,UIShowValue.GPS_Longitude);
		i+=GetStringByFmt((char *)&Buf[i],"]}");
		MQTT_LegnthToByte(i-LengthSize-1,&Buf[1]);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(!GPRS_AckDelay(">",2000))return 1;
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//��鷢�ͳɹ�
		GPRS_Printf(2000);
	}else
	{
		if(UIShowValue.CH_Value[0]>=0)c='+';else c='-';
		if(UIShowValue.CH_Value[1]>=0)c1='+';else c1='-';
		i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		if(UIShowValue.CH_Value[1]<UIShowValue.CH_Value[0])i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		if(UIShowValue.RunFlag&WRF_SensorCH1Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		else if(UIShowValue.RunFlag&WRF_SensorCH2Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		//i=GetStringByFmt((char *)&Buf[0],"#TP401G,%c%.1f,%c%.1f,20%02d,%02d,%02d,%02d:%02d:%02d \r\n",c,UIShowValue.CH_Value[0],c1,UIShowValue.CH_Value[1],UIShowValue.DateTime.Year,UIShowValue.DateTime.Mon,UIShowValue.DateTime.Day,UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,UIShowValue.DateTime.Sec);//����Ҫ���Э��
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		Tos_TaskDelay(1000);
		DeBug("��������:%s",&Buf[0],Infor_Warning);
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//��鷢�ͳɹ�
	}
	return 0;
}
u8 QuectelM26_SendHeartbeat()
{
	uint8 Buf[200];
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		Buf[i++]=0xc0;
		Buf[i++]=0x00;
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(!GPRS_AckDelay(">",2000))return 1;
		QuectelM26Printf_Bytes("����:",&Buf[0],i);
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//��鷢�ͳɹ�
		if(!GPRS_Printf(2000))return 0;
	}else
	{
		i=StringCoppy("0000",&Buf[0]);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		Tos_TaskDelay(1000);
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//��鷢�ͳɹ�
	}
	return 0;
}
u8 QuectelM26_SendCFG()
{
	uint8 Buf[200];
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		DeBug("����ΪMQTTЭ��",Infor_Warning);
		Tos_TaskDelay(3000);
		i=QuectelM26_CreateCFG(&Buf[0]);
		DeBug("��������[%d]",i,Infor_Warning);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(GPRS_AckDelay(">",2000))goto OK;
		if(GPRS_AckDelay(">",2000))goto OK;
		if(GPRS_AckDelay(">",2000))goto OK;
	OK:
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//��鷢�ͳɹ�
		GPRS_Printf(2000);
		return 0;
	}else 
	{
		DeBug("����ΪTCPЭ��",Infor_Warning);
		i+=BufferCoppy(&UIShowValue.SaveValue.LoginHead[0],&Buf[i],sizeof(UIShowValue.SaveValue.LoginHead));
	  USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		Tos_TaskDelay(1000);
		DeBug("��������:%s",&Buf[0],Infor_Warning);
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//��鷢�ͳɹ�
		return 0;
	}
}

u8 QuectelM26_SendTextMsg(u8 *string)
{
	uint8 Num[20],Buf[400],i=0,c=0;
R:
	if(i>2)
	{
		return c;
	}
	BufferCoppy(&UIShowValue.SaveValue.CallNumber[i++][0],&Num[0],sizeof(UIShowValue.SaveValue.CallNumber[0]));
	Num[sizeof(UIShowValue.SaveValue.CallNumber[0])]=0;
	if(!CheckCallNumber(&Num[0]))goto R;
	QuectelM26_InitSMS(1);
	GBKToUniCode(&Num[0],&Buf[0]);
	Buf[44]=0x00;
	USART_WriteLine(USART2,"AT+CMGS=\"%s\"\r\n",&Buf[0]);
	DeBug("���͵�[%s]",&Num[0],Infor_Warning);
	Tos_TaskDelay(1000);
	GBKToUniCode(&string[0],&Buf[0]);
	Buf[GetTextLength(string)*4]=0x00;
	USART_WriteLine(USART2,(char *)Buf);
	USART_WriteData(USART2,0x1a);                                        //��������
	GPRS_AckDelay("CMGS", 1000);                            //���ݷ���״̬
	c++;
	goto R;
}



void QuectelM26_Config()
{
	uint8 sta;
	sta=QuectelM26_SendCFG();
	if(sta)DeBug("��������֡ʧ��[%d]",sta,Infor_Warning);
	else DeBug("��������֡OK",Infor_Warning);
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
void Task_M26(void *Tags)
{
	uint8 sta,i,FailCount=0,RFailCount;
R:
	RFailCount=0;
	UIShowValue.RSSI=99;
	sta=QuectelM26_Init();
	if(sta)DeBug("ע������ʧ��[%d]",sta,Infor_Warning);
	Task_AutoReg(0);
	sta=QuectelM26_InitSMS(1);
	if(sta)DeBug("��ʼ������[%d]",sta,Infor_Warning);
	sta=QuectelM26_Connect();
	if(sta)DeBug("���ӷ�����[%d]",sta,Infor_Warning);
	PDU_GetCenterNumber();
	Tos_TaskDelay(1000);
	QuectelM26_Config();
	while(1)
	{
		sta=QuectelM26_SendData();
		if(sta){DeBug("��������ʧ��[%d]",sta,Infor_Warning);FailCount++;}
		else {DeBug("��������OK",Infor_Warning);FailCount=0;RFailCount=0;Tos_TaskDelay(9000);}
		for(i=0;i<(UIShowValue.SaveValue.SendCycle/20);i++)
		{
			sta=Task_SendMsg();
			if(sta)DeBug("���ŷ���[%d]/[%d]��",sta%10,3,Infor_Warning);
			Tos_TaskDelay(1000);
			UIShowValue.RSSI=QuectelM26_GetCSQ();
			QuectelM26_ShowSMS();//��ȡ����
			Tos_TaskDelay(18000);
			sta=QuectelM26_SendHeartbeat();
			if(sta){DeBug("��������ʧ��[%d]",sta,Infor_Warning);FailCount++;}
			else {DeBug("��������OK",Infor_Warning);RFailCount=0;FailCount=0;}
			if(FailCount>0){QuectelM26_Connect();FailCount=0;QuectelM26_Config();RFailCount++;}
		}
		if(RFailCount>3)goto R;
	}
}
