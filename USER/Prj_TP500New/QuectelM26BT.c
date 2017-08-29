/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_TP502T\QuectelM26.h>
#include <AT_Command.h>
#include <..\USER\Prj_TP502T\Auto_Register.h>

void GPIO_Set_PWR(uint8 OUT)
{     
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	if(OUT) GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;            
	else GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;            
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	if(OUT)M26_POWER_ON;
	else M26_POWER_OFF;
}
extern void TOS_Sleep(uint8 Min);
u8 QuectelM26_Init(void)
{
		uint8 sta;
    GPIO_Set_PWR(0);
		UIShowValue.RunFlag&=~WRF_SIMConnected;
		DeBug("GPRS上电",Infor_Warning);
		Tos_TaskDelay(300); 
    GPIO_Set_PWR(1);
    Tos_TaskDelay(1000); 
    M26_RESET_ON;
    Tos_TaskDelay(1100); 
		DeBug("GPRS开机",Infor_Warning);
    M26_RESET_OFF;
    Tos_TaskDelay(1000);
		if(GPRS_VDDEXT==1)DeBug("开机成功",Infor_Warning);
		else {DeBug("模块开机失败",Infor_Warning);GPIO_Set_PWR(0);if(UIShowValue.SaveValue.SleepMin)TOS_Sleep(UIShowValue.SaveValue.SleepMin);while(1)Tos_TaskDelay(1100);}
	  Tos_TaskDelay(4000);
		if(!GPRS_CommandAck("AT\r\n","OK",1000))return 2;
		DeBug("AT指令执行成功",Infor_Warning);
    Tos_TaskDelay(1000);
		if(!GPRS_CommandAck("ATE0\r\n","OK",2000))return 3;
		DeBug("设置不回显",Infor_Warning);
	  if(!GPRS_CommandAck("AT+CPIN?\r\n","OK",1000))return 4;
		UIShowValue.RunFlag|=WRF_SIMConnected;
		DeBug("查看是否有PIN",Infor_Warning);
    sta=QuectelM26_ConnectNet();                                      //连接网络
		if(sta)DeBug("连接网失败[%d]",sta,Infor_Warning);
		else DeBug("连接网络成功",Infor_Warning);
    return M26_OK;
}
BOOL GPRS_Printf(uint16 Wating)//打印接收到的数据
{
	uint8 i=1;
	uint8 Length;
	while(i--)
	{
		BufferFill(USART_RX_Buffer[1],0x00,USART_RX_BUFFER_SIZE);
		Length=USART_ReadDatas(USART2,Null,50,Wating);
		if(Length)
		{
			if(strstr((const char *)USART_RX_Buffer[1],"CLOSED")){DeBug("连接被关闭",Infor_Warning);return False;}
			else {QuectelM26Printf_Bytes("接收:",USART_RX_Buffer[1],Length);return True;}
		}
	}
	return False;
}
u8 QuectelM26_Connect()
{
	char Buf[100];
	FmtToBuf(&Buf[0],"AT+QIOPEN=\"TCP\",\"%s\",%d\r\n",&UIShowValue.SaveValue.DomainName[0][0],UIShowValue.SaveValue.ServerPort[0]);
	DeBug("连接到:%s",&Buf[0],Infor_Warning);
	return GPRS_Connect(&Buf[0]);
}
u8 QuectelM26_Http()
{
	char Buf[200];
	FmtToBuf(&Buf[0],"http://www.tlink.io/tlink_interface/api/device/createDataPonit.htm\r\n");
	DeBug("连接到:%s",&Buf[0],Infor_Warning);
	if(!GPRS_CommandAck("AT+QIFGCNT=0\r\n","OK",1000))return 2;
	if(!GPRS_CommandAck("AT+QICSGP=1,\"CMNET\"\r\n","OK",1000))return 2;
	if(!GPRS_CommandAck("AT+QIREGAPP\r\n","OK",1000))return 2;
	if(!GPRS_CommandAck("AT+QIACT\r\n","OK",1000))return 2;
	if(!GPRS_CommandAck("AT+QHTTPURL=13,30\r\n","CONNECT",1000))return 2;
	GPRS_Printf(2000);
	if(!GPRS_CommandAck("http://atool.org","OK",1000))return 2;
	GPRS_Printf(2000);
	//if(!GPRS_CommandAck("AT+QHTTPPOST=5,2,10\r\n","CONNECT",1000))return 2;
	//GPRS_Printf(2000);
	//USART_WriteLine(USART2,"ddddd",5);
	//DeBug("发送:%s","ddddd",Infor_Warning);
	//GPRS_Printf(2000);
	if(!GPRS_CommandAck("AT+QHTTPGET=60\r\n","OK",1500))return 2;	
	if(!GPRS_CommandAck("AT+QHTTPREAD=30\r\n","CONNECT",1500))return 2;	
	GPRS_Printf(2000);
	if(!GPRS_CommandAck("AT+QIDEACT\r\n","OK",500))return 2;
	return 0;
}
/***************************************************************************************************
 * 函 数 名: QuectelM26_ConnectNet
 * 功能描述: 模块连接网络
 * 函数说明: 无
 * 调用函数: 无
 * 全局变量: 无
 * 输　　入: 无
 * 返　　回: 处理结果
***************************************************************************************************/
u8 QuectelM26_ConnectNet(void)
{
    if(!GPRS_CommandAck("AT+CSQ\r\n","!99",1000))return 1;
		UIShowValue.RSSI=QuectelM26_GetCSQ();
		DeBug("检查信号",Infor_Warning);
		DeBug("正在注册",Infor_Warning);
		if(!GPRS_CommandAck("AT+CREG?\r\n","0",1000));
		if(!GPRS_CommandAckCount("AT+CREG?\r\n","5",1000,2))DeBug("本地卡",Infor_Warning);else DeBug("外地卡",Infor_Warning);
		if(GPRS_CommandAckCount("AT+COPS?\r\n","MOBILE",1000,2)){DeBug("中国移动SIM卡",Infor_Warning);UIShowValue.SIMType=ST_CHINA_MOBILE;}
		else if(GPRS_CommandAckCount("AT+COPS?\r\n","UNICOM",1000,2)){DeBug("中国联通SIM卡",Infor_Warning);UIShowValue.SIMType=ST_CHINA_UNINET;}
		DeBug("注册成功",Infor_Warning);
		return 0;
}



u8 QuectelM26_CreateCFG(u8 *Buf)
{
	uint16 i=0;
	Buf[i++]=0x10;//消息类型：发布消息 非UDP通信QOS至少一次
	Buf[i++]=0xff;//数据长度，当大于127个字节一下只需要一个字节表示
	Buf[i++]=0x00;//版本
	Buf[i++]=0x04;//连接标志
	i+=BufferCoppy("MQTT",&Buf[i],4);
	Buf[i++]=0x04;//协议版本
	Buf[i++]=0x02;//连接标志
	Buf[i++]=0x00;//
	Buf[i++]=0x3c;//保持活动周期
	Buf[i++]=0x00;//
	Buf[i++]=0x10;//长度
	i+=BufferCoppy(&UIShowValue.SaveValue.LoginHead[0],&Buf[i],sizeof(UIShowValue.SaveValue.LoginHead));
	Buf[1]=i-2;
	return i;
}



u8 QuectelM26_SendData()
{
	uint8 Buf[500];
	uint8 c,c1;
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		i+=GetStringByFmt((char *)&Buf[i],"{\"sensorDatas\":[");
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[0]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[1]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[2]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",(float)UIShowValue.RSSI);
		i+=GetStringByFmt((char *)&Buf[i],"{\"lat\":%.7f,\"lng\":%.7f}",UIShowValue.GPS_Latitude,UIShowValue.GPS_Longitude);
		i+=GetStringByFmt((char *)&Buf[i],"]}");
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(!GPRS_AckDelay(">",2000))return 1;
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
		GPRS_Printf(2000);
	}else
	{
		if(UIShowValue.CH_Value[0]>=0)c='+';else c='-';
		if(UIShowValue.CH_Value[1]>=0)c1='+';else c1='-';
		i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		if(UIShowValue.CH_Value[1]<UIShowValue.CH_Value[0])i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		if(UIShowValue.RunFlag&WRF_SensorCH1Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		else if(UIShowValue.RunFlag&WRF_SensorCH2Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		//i=GetStringByFmt((char *)&Buf[0],"#TP401G,%c%.1f,%c%.1f,20%02d,%02d,%02d,%02d:%02d:%02d \r\n",c,UIShowValue.CH_Value[0],c1,UIShowValue.CH_Value[1],UIShowValue.DateTime.Year,UIShowValue.DateTime.Mon,UIShowValue.DateTime.Day,UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,UIShowValue.DateTime.Sec);//三和要求的协议
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		Tos_TaskDelay(1000);
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
	}
	return 0;
}
uint8 FindStringFromString(uint8 *Buf,uint8 *Data)
{
	uint8 Length,i,c=0,t,has=0,z=0;
	Length=GetTextLength(Buf);
	if(Length)
	{
		Data[0]=0;
		for(i=0;i<Length;i++)
		{
			t=Buf[i];
			if(t==':')z=1;
			if(z)
			{
				if(t=='"'){if(has)goto Over;else has=1;}
				else {if(has)Data[c++]=t;}
			}
		}	
	}
Over:
	Data[c++]=0x00;
	return c;
}

uint16 TCP_JGetString(uint8 *Buf,char *Str)
{
	uint16 i=0;
	uint8 Data[20];
	i+=GetStringByFmt((char *)&Buf[i],"{");
	i+=GetStringByFmt((char *)&Buf[i],"\"method\":\"3\",");
	i+=GetStringByFmt((char *)&Buf[i],"\"ent_key\":\""__ENT_KEY__"\",");
	BufferCoppy(&UIShowValue.SaveValue.LoginHead[0],Data,sizeof(UIShowValue.SaveValue.LoginHead));
	Data[sizeof(UIShowValue.SaveValue.LoginHead)]=0;
	i+=GetStringByFmt((char *)&Buf[i],"\"device_no\":\"%s\",",Data);
	i+=GetStringByFmt((char *)&Buf[i],"\"query_column\":\"%s\"",Str);
	i+=GetStringByFmt((char *)&Buf[i],"}");
	return i;
}
uint16 TCP_JGetStringDelete(uint8 *Buf,char *Str)
{
	uint16 i=0;
	uint8 Data[20];
	i+=GetStringByFmt((char *)&Buf[i],"{");
	i+=GetStringByFmt((char *)&Buf[i],"\"method\":\"4\",");
	i+=GetStringByFmt((char *)&Buf[i],"\"ent_key\":\""__ENT_KEY__"\",");
	BufferCoppy(&UIShowValue.SaveValue.LoginHead[0],Data,sizeof(UIShowValue.SaveValue.LoginHead));
	Data[sizeof(UIShowValue.SaveValue.LoginHead)]=0;
	i+=GetStringByFmt((char *)&Buf[i],"\"device_no\":\"%s\",",Data);
	i+=GetStringByFmt((char *)&Buf[i],"%s",Str);
	i+=GetStringByFmt((char *)&Buf[i],"}");
	return i;
}
uint8 TCP_JGetConfig()
{
	uint8 *P,Buf[20];
	float Data;
	P=(uint8 *)Strstr((const char *)USART_RX_Buffer[1],"flag");
	if(P)
	{
		FindNumFromString(P,&Buf[0],0);
		Data=GetStringToNumber(&Buf[0]);
		if(Data>0)return 0;
	}else return 0;
	P=(uint8 *)Strstr((const char *)USART_RX_Buffer[1],"edit");
	if(P)
	{
		FindNumFromString(P,&Buf[0],0);
		Data=GetStringToNumber(&Buf[0]);
		if(Data==1)return 1;//编辑完成
		else return 0;//未编辑
	}
	P=(uint8 *)Strstr((const char *)USART_RX_Buffer[1],"alarm_mobile");
	if(P)
	{
		FindNumFromString(P,&Buf[0],0);
		BufferCoppy(&Buf[0],UIShowValue.SaveValue.CallNumber[0],sizeof(UIShowValue.SaveValue.CallNumber[0]));
		FindNumFromString(P,&Buf[0],1);
		BufferCoppy(&Buf[0],UIShowValue.SaveValue.CallNumber[1],sizeof(UIShowValue.SaveValue.CallNumber[0]));
		FindNumFromString(P,&Buf[0],2);
		BufferCoppy(&Buf[0],UIShowValue.SaveValue.CallNumber[2],sizeof(UIShowValue.SaveValue.CallNumber[0]));
		Task_SaveConfigs();
		return 2;
	}
	P=(uint8 *)Strstr((const char *)USART_RX_Buffer[1],"alarm_value");
	if(P)
	{
		FindFloatFromString(P,&Buf[0],0);
		DeBug("Min%s",Buf,Infor_Warning);
		Data=GetStringToNumber(&Buf[0]);
		UIShowValue.SaveValue.CH_Limit[0].Min=Data;
		FindFloatFromString(P,&Buf[0],1);
		DeBug("Max%s",Buf,Infor_Warning);
		Data=GetStringToNumber(&Buf[0]);
		UIShowValue.SaveValue.CH_Limit[0].Max=Data;
		FindFloatFromString(P,&Buf[0],2);
		DeBug("Min%s",Buf,Infor_Warning);
		Data=GetStringToNumber(&Buf[0]);
		UIShowValue.SaveValue.CH_Limit[1].Min=Data;
		FindFloatFromString(P,&Buf[0],3);
		DeBug("Max%s",Buf,Infor_Warning);
		Data=GetStringToNumber(&Buf[0]);
		UIShowValue.SaveValue.CH_Limit[1].Max=Data;
		Task_SaveConfigs();
		return 3;
	} 
	P=(uint8 *)Strstr((const char *)USART_RX_Buffer[1],"user_group");
	if(P)
	{
		FindStringFromString(P,&Buf[0]);
		DeBug("user_group:%s",Buf,Infor_Warning);
		StringCoppy(&Buf[0],&UIShowValue.SaveValue.PrintfName[0]);
		Task_SaveConfigs();
		return 4;
	}
	P=(uint8 *)Strstr((const char *)USART_RX_Buffer[1],"forscene");
	if(P)
	{
		FindStringFromString(P,&Buf[0]);
		DeBug("forscene:%s",Buf,Infor_Warning);
		StringCoppy(&Buf[0],&UIShowValue.SaveValue.PrintfTitle[0]);
		Task_SaveConfigs();
		return 99;
	}
	DeBug("配置%f",Data,Infor_Warning);
	return 0;
}

u8 QuectelM26_SendHeartbeat()
{
	uint8 Buf[200];
	uint16 i=0;
	uint8 r=0;
R:
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		if(r==0)i=TCP_JGetString(&Buf[0],"edit");
		if(r==1)i=TCP_JGetString(&Buf[0],"alarm_mobile");
		if(r==2)i=TCP_JGetString(&Buf[0],"alarm_value");
		if(r==3)i=TCP_JGetString(&Buf[0],"user_group");
		if(r==4)i=TCP_JGetString(&Buf[0],"forscene");
		if(r==99)i=TCP_JGetStringDelete(&Buf[0],"\"edit\":\"0\"");
		DeBug("发送:%s",&Buf[0],Infor_Warning);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(!GPRS_AckDelay(">",2000))return 1;
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
		if(!GPRS_PrintfString(2000))return 0;
		r=TCP_JGetConfig();
		if(r)goto R;
	}else
	{
		return QuectelM26_SendData();//检查发送成功
	}
	return 0;
}
u8 QuectelM26_SendCFG()
{
	uint8 Buf[200];
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		DeBug("配置为J-TCP协议",Infor_Warning);
		Tos_TaskDelay(100);
		i+=BufferCoppy(&UIShowValue.SaveValue.LoginHead[0],&Buf[i],sizeof(UIShowValue.SaveValue.LoginHead));
		DeBug("发送配置[%d]",i,Infor_Warning);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(GPRS_AckDelay(">",2000))goto OK;
		if(GPRS_AckDelay(">",2000))goto OK;
		if(GPRS_AckDelay(">",2000))goto OK;
	OK:
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
		GPRS_Printf(100);
		return 0;
	}else 
	{
		DeBug("配置为TCP协议",Infor_Warning);
		i+=BufferCoppy(&UIShowValue.SaveValue.LoginHead[0],&Buf[i],sizeof(UIShowValue.SaveValue.LoginHead));
	  USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		Tos_TaskDelay(100);
		DeBug("发送配置:%s",&Buf[0],Infor_Warning);
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
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
	DeBug("发送到[%s]",&Num[0],Infor_Warning);
	Tos_TaskDelay(1000);
	GBKToUniCode(&string[0],&Buf[0]);
	Buf[GetTextLength(string)*4]=0x00;
	USART_WriteLine(USART2,(char *)Buf);
	USART_WriteData(USART2,0x1a);                                        //发送数据
	GPRS_AckDelay("CMGS", 1000);                            //数据发送状态
	c++;
	goto R;
}



void QuectelM26_Config()
{
	uint8 sta;
	sta=QuectelM26_SendCFG();
	if(sta)DeBug("发送配置帧失败[%d]",sta,Infor_Warning);
	else DeBug("发送配置帧OK",Infor_Warning);
	Tos_TaskDelay(100);
}
uint8 Task_SendMsgBT()
{
	uint8 i=0,c=0;
	char Buf[200];
	static uint8 z=0;
	uint8 ThisBit;
	if(UIShowValue.RunFlag&WRF_BeepDisable)
	{
		DeBug("跳过报警检查",Infor_Warning);
		return 0;
	}
	ThisBit=UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH1Min|WRF_CH2Max|WRF_CH2Min);
	DeBug("ThisBit=%d,Count=%d,CH1=%.2f,CH2:%.2f",ThisBit,z,UIShowValue.CH_Value[0],UIShowValue.CH_Value[1],Infor_Warning);
	if(ThisBit>0)
	{
		z++;
		if(z>UIShowValue.SaveValue.SendSMSDelay)
		{
		if(UIShowValue.SaveValue.WorkBit&WCB_RingAlarm)//电话报警
		{
				DeBug("拨打电话",Infor_Warning);
			  BufferCoppy(&UIShowValue.SaveValue.CallNumber[i++][0],&Buf[0],sizeof(UIShowValue.SaveValue.CallNumber[0]));
				Buf[sizeof(UIShowValue.SaveValue.CallNumber[0])]=0;
				USART_WriteLine(USART2,"ATD%s;\r\n",&Buf[0]);
				DeBug("ATD%s;\r\n",&Buf[0],Infor_Warning);
				GPRS_Printf(2000);
				Tos_TaskDelay(20000);
				USART_WriteLine(USART2,"ATH\r\n");
				GPRS_Printf(2000);
				DeBug("挂机",Infor_Warning);
				
		}else
		{
			c=StringCoppy(&UIShowValue.SaveValue.PrintfTitle[0],&Buf[0]);
			i=GetStringByFmt(&Buf[c],"恢复CH1=%.2f,CH2:%.2f",UIShowValue.CH_Value[0],UIShowValue.CH_Value[1]);
			if(UIShowValue.RunFlag&WRF_CH1Max)i=GetStringByFmt(&Buf[c],"触发CH1=%.2f,MAX:%.2f",UIShowValue.CH_Value[0],UIShowValue.SaveValue.CH_Limit[0].Max);
			if(UIShowValue.RunFlag&WRF_CH1Min)i=GetStringByFmt(&Buf[c],"触发CH1=%.2f,Min:%.2f",UIShowValue.CH_Value[0],UIShowValue.SaveValue.CH_Limit[0].Min);
			if(UIShowValue.RunFlag&WRF_CH2Max)i=GetStringByFmt(&Buf[c],"触发CH2=%.2f,MAX:%.2f",UIShowValue.CH_Value[1],UIShowValue.SaveValue.CH_Limit[1].Max);
			if(UIShowValue.RunFlag&WRF_CH2Min)i=GetStringByFmt(&Buf[c],"触发CH2=%.2f,Min:%.2f",UIShowValue.CH_Value[1],UIShowValue.SaveValue.CH_Limit[1].Min);
			i+=c;
			if(i%2==1)i+=GetStringByFmt(&Buf[i]," ");
			DeBug("短信内容[%d]:%s",i,&Buf[0],Infor_Warning);
			i=QuectelM26_SendTextMsg((uint8*)&Buf[0]);
		}
		Tos_TaskDelay(5000);
		z=0;
		}
	}else z=0;
	return i;
}
uint8 Task_PowerFailMsg()
{
	static uint8 One=1;
	char Buf[200];
	uint8 c;
	if(One)
	{
		DeBug("掉电[%d]",(UIShowValue.RunFlag&WRF_EXP_Connected),Infor_Warning);
		if(!(UIShowValue.RunFlag&WRF_EXP_Connected))
		{
			  c=StringCoppy(&UIShowValue.SaveValue.PrintfTitle[0],&Buf[0]);
				c+=GetStringByFmt(&Buf[c],"%s","掉电报警");
				if(c%2==1)c+=GetStringByFmt(&Buf[c]," ");
				Buf[c]=0;
				DeBug("短信内容[%d]:%s",c,&Buf[0],Infor_Warning);
				c=QuectelM26_SendTextMsg((uint8*)&Buf[0]);
				One=0;
			return c;
		}
	}
	return 0;
}
extern u8 Regdit_SendInfor(void);
void _Task_M26(void *Tags)
{
	uint8 sta,i,FailCount=0,RFailCount;
R:
	RFailCount=0;
	UIShowValue.RSSI=99;
	sta=QuectelM26_Init();
	if(sta)DeBug("注册网络失败[%d]",sta,Infor_Warning);
	else Task_AutoReg(0);
	sta=QuectelM26_InitSMS(1);
	if(sta)DeBug("初始化短信[%d]",sta,Infor_Warning);
	sta=QuectelM26_Connect();
	if(sta)DeBug("连接服务器[%d]",sta,Infor_Warning);
	PDU_GetCenterNumber();
	Regdit_SendInfor();
	QuectelM26_Config();
	while(1)
	{
		sta=QuectelM26_SendData();
		if(sta){DeBug("发送数据失败[%d]",sta,Infor_Warning);FailCount++;}
		else {DeBug("发送数据OK",Infor_Warning);FailCount=0;RFailCount=0;Tos_TaskDelay(9000);}
		for(i=0;i<(UIShowValue.SaveValue.SendCycle/20+1);i++)
		{
			sta=Task_SendMsgBT();
			if(sta)DeBug("短信发给[%d]/[%d]人",sta%10,3,Infor_Warning);
			Tos_TaskDelay(1000);
			UIShowValue.RSSI=QuectelM26_GetCSQ();
			QuectelM26_ShowSMS();//获取短信
			Tos_TaskDelay(18000);
			sta=QuectelM26_SendHeartbeat();
			if(sta){DeBug("发送心跳失败[%d]",sta,Infor_Warning);FailCount++;}
			else {DeBug("发送心跳OK",Infor_Warning);RFailCount=0;FailCount=0;}
		}
		if(FailCount>0){QuectelM26_Connect();FailCount=0;QuectelM26_Config();RFailCount++;}
		if(RFailCount>3)goto R;
	}
}
u8 QuectelM26_SendHR1(HistoryRecord *HR)
{
	uint8 Buf[500];
	uint8 c,c1;
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		i+=GetStringByFmt((char *)&Buf[i],"{\"sensorDatas\":[");
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[0]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[1]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[2]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",(float)UIShowValue.RSSI);
		if(UIShowValue.RunFlag&WRF_USB_Connected)i+=GetStringByFmt((char *)&Buf[i],"{\"switcher\":1},");
		else {i+=GetStringByFmt((char *)&Buf[i],"{\"switcher\":0},");}
		i+=GetStringByFmt((char *)&Buf[i],"{\"lat\":%.7f,\"lng\":%.7f}",UIShowValue.GPS_Latitude,UIShowValue.GPS_Longitude);
		//i+=GetStringByFmt((char *)&Buf[i],"{\"timestamp\":\"20%02d-%02d-%02d %02d:%02d:%02d\"}",HR->DT.Year,HR->DT.Mon,HR->DT.Day,HR->DT.Hour,HR->DT.Min,HR->DT.Sec);
		i+=GetStringByFmt((char *)&Buf[i],"]}");
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(!GPRS_AckDelay(">",2000))return 1;
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
		GPRS_Printf(2000);
	}else
	{
		if(UIShowValue.CH_Value[0]>=0)c='+';else c='-';
		if(UIShowValue.CH_Value[1]>=0)c1='+';else c1='-';
		i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		if(UIShowValue.CH_Value[1]<UIShowValue.CH_Value[0])i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		if(UIShowValue.RunFlag&WRF_SensorCH1Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		else if(UIShowValue.RunFlag&WRF_SensorCH2Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		//i=GetStringByFmt((char *)&Buf[0],"#TP401G,%c%.1f,%c%.1f,20%02d,%02d,%02d,%02d:%02d:%02d \r\n",c,UIShowValue.CH_Value[0],c1,UIShowValue.CH_Value[1],UIShowValue.DateTime.Year,UIShowValue.DateTime.Mon,UIShowValue.DateTime.Day,UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,UIShowValue.DateTime.Sec);//三和要求的协议
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		Tos_TaskDelay(1000);
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
	}
	return 0;
}
//{"sensorData":[{"value":22.33},{"value":44.6}]}


u8 QuectelM26_SendHR(HistoryRecord *HR)
{
	uint8 Buf[500];
	uint8 c,c1;
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		i+=GetStringByFmt((char *)&Buf[i],"{\"sensorDatas\":[");
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[0]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[1]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[2]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",(float)UIShowValue.RSSI);
		i+=GetStringByFmt((char *)&Buf[i],"{\"lat\":%.7f,\"lng\":%.7f}",UIShowValue.GPS_Latitude,UIShowValue.GPS_Longitude);
		//i+=GetStringByFmt((char *)&Buf[i],"{\"timestamp\":\"20%02d-%02d-%02d %02d:%02d:%02d\"}",HR->DT.Year,HR->DT.Mon,HR->DT.Day,HR->DT.Hour,HR->DT.Min,HR->DT.Sec);
		i+=GetStringByFmt((char *)&Buf[i],"]}");
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(!GPRS_AckDelay(">",2000))return 1;
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
		GPRS_Printf(2000);
	}else
	{
		if(UIShowValue.CH_Value[0]>=0)c='+';else c='-';
		if(UIShowValue.CH_Value[1]>=0)c1='+';else c1='-';
		i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		if(UIShowValue.CH_Value[1]<UIShowValue.CH_Value[0])i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		if(UIShowValue.RunFlag&WRF_SensorCH1Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		else if(UIShowValue.RunFlag&WRF_SensorCH2Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		//i=GetStringByFmt((char *)&Buf[0],"#TP401G,%c%.1f,%c%.1f,20%02d,%02d,%02d,%02d:%02d:%02d \r\n",c,UIShowValue.CH_Value[0],c1,UIShowValue.CH_Value[1],UIShowValue.DateTime.Year,UIShowValue.DateTime.Mon,UIShowValue.DateTime.Day,UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,UIShowValue.DateTime.Sec);//三和要求的协议
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		Tos_TaskDelay(1000);
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
	}
	return 0;
}
u8 QuectelM26_SendHTTP(HistoryRecord *HR)
{
	uint8 Buf[300],Data[100];
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		
	//	i+=GetStringByFmt((char *)&Data[i],"20%02d-%02d-%02d %02d:%02d:%02d;",HR->DT.Year,HR->DT.Mon,HR->DT.Day,HR->DT.Hour,HR->DT.Min,HR->DT.Sec);
		i+=GetStringByFmt((char *)&Data[i],"%.1f,%.1f,%.1f,%.0f",HR->CH_Value[0],HR->CH_Value[1],HR->CH_Value[2],(float)UIShowValue.RSSI);
		i=0;
		UIShowValue.SaveValue.LoginHead[sizeof(UIShowValue.SaveValue.LoginHead)-1]=0;
		i+=GetStringByFmt((char *)&Buf[i],"POST /php/api.php?id=%s HTTP/1.1\n",UIShowValue.SaveValue.LoginHead);
		i+=GetStringByFmt((char *)&Buf[i],"Content-Type: application/x-www-form-urlencoded\n");
		i+=GetStringByFmt((char *)&Buf[i],"Host: %s\n",&UIShowValue.SaveValue.DomainName[0][0]);
		i+=GetStringByFmt((char *)&Buf[i],"Content-Length: %d\n",GetTextLength(&Data[0])+2);
		i+=GetStringByFmt((char *)&Buf[i],"Expect: 100-continue\n");
		i+=GetStringByFmt((char *)&Buf[i],"Connection: Keep-Alive\r\n\r\n");
		i+=GetStringByFmt((char *)&Buf[i],"%s\r\n",&Data[0]);
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(!GPRS_AckDelay(">",2000))return 1;
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
		if(!GPRS_AckDelay("OK",6000))return 3;//检查发送成功
	}
	return 0;
}
u8 QuectelM26_SendHTTP_(HistoryRecord *HR)
{
	uint8 Buf[500],Data[300];
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		i+=GetStringByFmt((char *)&Data[i],"data={\"key\":\"fc09d310d72b5e2b14b7990b61ad70733e6d03cbf778f2dd00d9fc3ea4b5da825cfe4ca244b8362b36c3adc5b21b142c\",");
    i+=GetStringByFmt((char *)&Data[i],"\"data\":[{");
		i+=GetStringByFmt((char *)&Data[i],"\"deviceNo\":\"%s\",","010101");
		i+=GetStringByFmt((char *)&Data[i],"\"temperature\":%.1f,",UIShowValue.CH_Value[0]);
		i+=GetStringByFmt((char *)&Data[i],"\"humidity\":\%.1f",UIShowValue.CH_Value[1]);
		i+=GetStringByFmt((char *)&Data[i],"}]}");
		
		i=0;
		i+=GetStringByFmt((char *)&Buf[i],"POST /hfcmsm/api.action?action=postEnvironmentData HTTP/1.1\n");
		i+=GetStringByFmt((char *)&Buf[i],"Content-Type: application/x-www-form-urlencoded\n");
		i+=GetStringByFmt((char *)&Buf[i],"Host: %s\n",&UIShowValue.SaveValue.DomainName[0][0]);
		i+=GetStringByFmt((char *)&Buf[i],"Content-Length: %d\n",GetTextLength(&Data[0]));
		i+=GetStringByFmt((char *)&Buf[i],"Expect: 100-continue\n");
		i+=GetStringByFmt((char *)&Buf[i],"Connection: Keep-Alive\r\n\r\n");
		i+=GetStringByFmt((char *)&Buf[i],"%s\r\n",&Data[0]);
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(!GPRS_AckDelay(">",2000))return 1;
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
		GPRS_Printf(4000);
		USART_WriteDatas(USART1,USART_RX_Buffer[1],USART_RX_Count[1]);
	}
	return 0;
}
extern float LiuliangBuf[25];
u8 QuectelM26_SendLL(uint8 Addr)
{
	uint8 Buf[500];
	uint8 c,c1;
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		i+=GetStringByFmt((char *)&Buf[i],"{\"sensorDatas\":[");
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",(float)UIShowValue.RSSI);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[2+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[3+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[4+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[5+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[6+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[7+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[8+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[9+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[10+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[11+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[12+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",LiuliangBuf[13+Addr]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f}",LiuliangBuf[14+Addr]);
		//i+=GetStringByFmt((char *)&Buf[i],"{\"timestamp\":\"20%02d-%02d-%02d %02d:%02d:%02d\"}",HR->DT.Year,HR->DT.Mon,HR->DT.Day,HR->DT.Hour,HR->DT.Min,HR->DT.Sec);
		i+=GetStringByFmt((char *)&Buf[i],"]}");
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(!GPRS_AckDelay(">",2000))return 1;
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
		GPRS_Printf(2000);
	}else
	{
		if(UIShowValue.CH_Value[0]>=0)c='+';else c='-';
		if(UIShowValue.CH_Value[1]>=0)c1='+';else c1='-';
		i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		if(UIShowValue.CH_Value[1]<UIShowValue.CH_Value[0])i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		if(UIShowValue.RunFlag&WRF_SensorCH1Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		else if(UIShowValue.RunFlag&WRF_SensorCH2Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		//i=GetStringByFmt((char *)&Buf[0],"#TP401G,%c%.1f,%c%.1f,20%02d,%02d,%02d,%02d:%02d:%02d \r\n",c,UIShowValue.CH_Value[0],c1,UIShowValue.CH_Value[1],UIShowValue.DateTime.Year,UIShowValue.DateTime.Mon,UIShowValue.DateTime.Day,UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,UIShowValue.DateTime.Sec);//三和要求的协议
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		Tos_TaskDelay(1000);
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
	}
	return 0;
}
u8 QuectelM26_SendHRKGL(HistoryRecord *HR)
{
	uint8 Buf[500];
	uint8 c,c1;
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		i+=GetStringByFmt((char *)&Buf[i],"{\"sensorDatas\":[");
		i+=GetStringByFmt((char *)&Buf[i],"{\"switcher\":%.0f},",UIShowValue.CH_Value[0]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"switcher\":%.0f},",UIShowValue.CH_Value[1]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[2]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",(float)UIShowValue.RSSI);
		i+=GetStringByFmt((char *)&Buf[i],"{\"lat\":%.7f,\"lng\":%.7f}",UIShowValue.GPS_Latitude,UIShowValue.GPS_Longitude);
		//i+=GetStringByFmt((char *)&Buf[i],"{\"timestamp\":\"20%02d-%02d-%02d %02d:%02d:%02d\"}",HR->DT.Year,HR->DT.Mon,HR->DT.Day,HR->DT.Hour,HR->DT.Min,HR->DT.Sec);
		i+=GetStringByFmt((char *)&Buf[i],"]}");
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(!GPRS_AckDelay(">",2000))return 1;
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
		GPRS_Printf(2000);
	}else
	{
		if(UIShowValue.CH_Value[0]>=0)c='+';else c='-';
		if(UIShowValue.CH_Value[1]>=0)c1='+';else c1='-';
		i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		if(UIShowValue.CH_Value[1]<UIShowValue.CH_Value[0])i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		if(UIShowValue.RunFlag&WRF_SensorCH1Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		else if(UIShowValue.RunFlag&WRF_SensorCH2Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		//i=GetStringByFmt((char *)&Buf[0],"#TP401G,%c%.1f,%c%.1f,20%02d,%02d,%02d,%02d:%02d:%02d \r\n",c,UIShowValue.CH_Value[0],c1,UIShowValue.CH_Value[1],UIShowValue.DateTime.Year,UIShowValue.DateTime.Mon,UIShowValue.DateTime.Day,UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,UIShowValue.DateTime.Sec);//三和要求的协议
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		Tos_TaskDelay(1000);
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
	}
	return 0;
}
u8 QuectelM26_SendHRKGM(uint8 Data)
{
	uint8 Buf[500];
	uint8 c,c1;
	uint16 i=0;
	if(UIShowValue.SaveValue.WorkBit&WCB_MQTTEN)
	{
		i+=GetStringByFmt((char *)&Buf[i],"{\"sensorDatas\":[");
		i+=GetStringByFmt((char *)&Buf[i],"{\"switcher\":%d},",(BOOL)Data&S0);
		i+=GetStringByFmt((char *)&Buf[i],"{\"switcher\":%d},",(BOOL)Data&S1);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f},",UIShowValue.CH_Value[2]);
		i+=GetStringByFmt((char *)&Buf[i],"{\"value\":%.2f}",(float)UIShowValue.RSSI);

		//i+=GetStringByFmt((char *)&Buf[i],"{\"timestamp\":\"20%02d-%02d-%02d %02d:%02d:%02d\"}",HR->DT.Year,HR->DT.Mon,HR->DT.Day,HR->DT.Hour,HR->DT.Min,HR->DT.Sec);
		i+=GetStringByFmt((char *)&Buf[i],"]}");
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		if(!GPRS_AckDelay(">",2000))return 1;
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
		GPRS_Printf(2000);
	}else
	{
		if(UIShowValue.CH_Value[0]>=0)c='+';else c='-';
		if(UIShowValue.CH_Value[1]>=0)c1='+';else c1='-';
		i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		if(UIShowValue.CH_Value[1]<UIShowValue.CH_Value[0])i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		if(UIShowValue.RunFlag&WRF_SensorCH1Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c,UIShowValue.CH_Value[0]);
		else if(UIShowValue.RunFlag&WRF_SensorCH2Connected)i=GetStringByFmt((char *)&Buf[0],"#TP300,%c0%.1f,0.00\r\n",c1,UIShowValue.CH_Value[1]);
		//i=GetStringByFmt((char *)&Buf[0],"#TP401G,%c%.1f,%c%.1f,20%02d,%02d,%02d,%02d:%02d:%02d \r\n",c,UIShowValue.CH_Value[0],c1,UIShowValue.CH_Value[1],UIShowValue.DateTime.Year,UIShowValue.DateTime.Mon,UIShowValue.DateTime.Day,UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,UIShowValue.DateTime.Sec);//三和要求的协议
		USART_WriteLine(USART2,"AT+QISEND=%d\r\n",i);
		Tos_TaskDelay(1000);
		DeBug("发送数据:%s",&Buf[0],Infor_Warning);
		USART_WriteDatas(USART2,&Buf[0],i);
		if(!GPRS_AckDelay("SEND OK",1000))return 2;//检查发送成功
	}
	return 0;
}
void Timer_Broken0()
{
	HistoryRecord HR;
//	BufferCoppy(&UIShowValue.DateTime,&HR.DT,sizeof(UIShowValue.DateTime));
//	BufferCoppy(&UIShowValue.CH_Value,&HR.CH_Value,sizeof(UIShowValue.CH_Value));
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("GPRS"),0,sizeof(HistoryRecord),&HR);
}
void Timer_BrokenPin()
{
	HistoryRecord HR;
	BufferCoppy(&UIShowValue.DateTime,&HR.DT,sizeof(UIShowValue.DateTime));
	BufferCoppy(&UIShowValue.CH_Value,&HR.CH_Value,sizeof(UIShowValue.CH_Value));
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("GPRS"),0,sizeof(HistoryRecord),&HR);
}
void Timer_Broken1()
{
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("GPRS"),1,Null,Null);
}
void Timer_Broken2()
{
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("GPRS"),2,Null,Null);
}
void Timer_Broken3()
{
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("GPRS"),3,Null,Null);
}
extern void TOS_Sleep(uint8 Min);
extern void Task_RecordNow(void);

void Task_M26(void *Tags)
{
	uint8 sta,i,FailCount=0,RFailCount;
//	HistoryRecord HR;
	Tos_ArrayMessage *CurMsg,Msg[3];
	HistoryRecord *TaskMsg,TaskMsgBuf[3];	
	for(i=0;i<3;i++)Msg[i].Qmsg_Addr=&TaskMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],3);
R:
	RFailCount=0;
	UIShowValue.RSSI=99;
	sta=QuectelM26_Init();
	if(sta){DeBug("注册网络失败[%d] ",sta,Infor_Warning);GPIO_Set_PWR(0);if(UIShowValue.SaveValue.SleepMin){Task_RecordNow();TOS_Sleep(UIShowValue.SaveValue.SleepMin);}while(1)Tos_TaskDelay(1000);}
	else Task_AutoReg(0);
	sta=QuectelM26_InitSMS(1);
	if(sta)DeBug("初始化短信[%d]",sta,Infor_Warning);
	sta=QuectelM26_Connect();
	if(sta)DeBug("连接服务器[%d]",sta,Infor_Warning);
	PDU_GetCenterNumber();
	Regdit_SendInfor();
	QuectelM26_Config();
	Tos_CreateTimer(UIShowValue.SaveValue.SendCycle,0xffff,Timer_Broken0);
	Tos_CreateTimer(28,0xffff,Timer_Broken1);
	Tos_CreateTimer(28,0xffff,Timer_Broken2);
	Tos_CreateTimer(28,0xffff,Timer_Broken3);
	Timer_Broken0();
	Tos_TaskDelay(3000);
	while(1)
	{
		CurMsg=Tos_TaskGetQMsgDelay(100);
		if(CurMsg)
		{
			switch(CurMsg->Qmsg_Type)
			{
				case 0:
					DeBug("准备发送数据",Infor_Warning);
					Tos_TaskDelay(1000);
					TaskMsg=(HistoryRecord *)CurMsg->Qmsg_Addr;
					sta=QuectelM26_SendHR(TaskMsg);
					if(sta)
								{
									DeBug("发送数据失败[%d]",sta,Infor_Warning);FailCount++;
									//BufferCoppy(&UIShowValue.DateTime,&HR.DT,sizeof(UIShowValue.DateTime));
									//BufferCoppy(&UIShowValue.CH_Value,&HR.CH_Value,sizeof(UIShowValue.CH_Value));
									//Tos_TaskPutQmsg(Tos_GetTaskIDByName("GPRS"),0,sizeof(HistoryRecord),&HR);
								}
					else {
											DeBug("发送数据OK",Infor_Warning);
											FailCount=0;RFailCount=0;
											if(USART_RX_Buffer[1][0]==0x30)if(USART_RX_Buffer[1][1]==0x30)if(UIShowValue.SaveValue.SleepMin)TOS_Sleep(UIShowValue.SaveValue.SleepMin);
											Tos_TaskDelay(3000);
							  }
					break;
				case 1:
					sta=QuectelM26_SendHeartbeat();
					if(sta){DeBug("发送心跳失败[%d]",sta,Infor_Warning);FailCount++;}
					else {DeBug("发送心跳OK",Infor_Warning);RFailCount=0;FailCount=0;}
					break;
				case 2:
					sta=Task_SendMsgBT();
					if(sta)DeBug("短信发给[%d]/[%d]人",sta%10,3,Infor_Warning);
				if(UIShowValue.SaveValue.WorkBit&WCB_PowerAlarm)
					{
						sta=Task_PowerFailMsg();
						if(sta)DeBug("短信发给[%d]/[%d]人",sta%10,3,Infor_Warning);
					}
					break;
				case 3:
					UIShowValue.RSSI=QuectelM26_GetCSQ();
					QuectelM26_ShowSMS();//获取短信
					break;
			}
			
		}
		
		Tos_TaskDelay(100);
		if(FailCount>0){Tos_TaskDelay(2000);QuectelM26_Connect();FailCount=0;QuectelM26_Config();RFailCount++;}
		if(RFailCount>3)goto R;
	}
}
void Task_M26diaodian(void *Tags)
{
	uint8 sta,i,FailCount=0,RFailCount;
//	HistoryRecord HR;
	Tos_ArrayMessage *CurMsg,Msg[3];
	HistoryRecord *TaskMsg,TaskMsgBuf[3];	
	for(i=0;i<3;i++)Msg[i].Qmsg_Addr=&TaskMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],3);
R:
	RFailCount=0;
	UIShowValue.RSSI=99;
	sta=QuectelM26_Init();
	if(sta){DeBug("注册网络失败[%d] ",sta,Infor_Warning);GPIO_Set_PWR(0);if(UIShowValue.SaveValue.SleepMin){Task_RecordNow();TOS_Sleep(UIShowValue.SaveValue.SleepMin);}while(1)Tos_TaskDelay(1000);}
	else Task_AutoReg(0);
	sta=QuectelM26_InitSMS(1);
	if(sta)DeBug("初始化短信[%d]",sta,Infor_Warning);
	sta=QuectelM26_Connect();
	if(sta)DeBug("连接服务器[%d]",sta,Infor_Warning);
	PDU_GetCenterNumber();
	Regdit_SendInfor();
	QuectelM26_Config();
	Tos_CreateTimer(UIShowValue.SaveValue.SendCycle,0xffff,Timer_Broken0);
	Tos_CreateTimer(28,0xffff,Timer_Broken1);
	Tos_CreateTimer(28,0xffff,Timer_Broken2);
	Tos_CreateTimer(28,0xffff,Timer_Broken3);
	Timer_Broken0();
	Tos_TaskDelay(3000);
	while(1)
	{
		CurMsg=Tos_TaskGetQMsgDelay(100);
		if(CurMsg)
		{
			switch(CurMsg->Qmsg_Type)
			{
				case 0:
					DeBug("准备发送数据",Infor_Warning);
					Tos_TaskDelay(1000);
					TaskMsg=(HistoryRecord *)CurMsg->Qmsg_Addr;
					sta=QuectelM26_SendHR1(TaskMsg);
					if(sta)
								{
									DeBug("发送数据失败[%d]",sta,Infor_Warning);FailCount++;
									//BufferCoppy(&UIShowValue.DateTime,&HR.DT,sizeof(UIShowValue.DateTime));
									//BufferCoppy(&UIShowValue.CH_Value,&HR.CH_Value,sizeof(UIShowValue.CH_Value));
									//Tos_TaskPutQmsg(Tos_GetTaskIDByName("GPRS"),0,sizeof(HistoryRecord),&HR);
								}
					else {
											DeBug("发送数据OK",Infor_Warning);
											FailCount=0;RFailCount=0;
											if(USART_RX_Buffer[1][0]==0x30)if(USART_RX_Buffer[1][1]==0x30)if(UIShowValue.SaveValue.SleepMin)TOS_Sleep(UIShowValue.SaveValue.SleepMin);
											Tos_TaskDelay(3000);
							  }
					break;
				case 1:
					sta=QuectelM26_SendHeartbeat();
					if(sta){DeBug("发送心跳失败[%d]",sta,Infor_Warning);FailCount++;}
					else {DeBug("发送心跳OK",Infor_Warning);RFailCount=0;FailCount=0;}
					break;
				case 2:
					sta=Task_SendMsgBT();
					if(sta)DeBug("短信发给[%d]/[%d]人",sta%10,3,Infor_Warning);
				if(UIShowValue.SaveValue.WorkBit&WCB_PowerAlarm)
					{
						sta=Task_PowerFailMsg();
						if(sta)DeBug("短信发给[%d]/[%d]人",sta%10,3,Infor_Warning);
					}
					break;
				case 3:
					UIShowValue.RSSI=QuectelM26_GetCSQ();
					QuectelM26_ShowSMS();//获取短信
					break;
			}
			
		}
		
		Tos_TaskDelay(100);
		if(FailCount>0){Tos_TaskDelay(2000);QuectelM26_Connect();FailCount=0;QuectelM26_Config();RFailCount++;}
		if(RFailCount>3)goto R;
	}
}
void Task_M26HTTP(void *Tags)
{
	uint8 sta,i,FailCount=0,RFailCount;
	HistoryRecord HR;
	Tos_ArrayMessage *CurMsg,Msg[3];
	HistoryRecord *TaskMsg,TaskMsgBuf[3];	
	for(i=0;i<3;i++)Msg[i].Qmsg_Addr=&TaskMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],3);
R:
	RFailCount=0;
	UIShowValue.RSSI=99;
	sta=QuectelM26_Init();
	if(sta){DeBug("注册网络失败[%d] ",sta,Infor_Warning);GPIO_Set_PWR(0);if(UIShowValue.SaveValue.SleepMin){Task_RecordNow();TOS_Sleep(UIShowValue.SaveValue.SleepMin);}while(1)Tos_TaskDelay(1000);}
	else Task_AutoReg(0);
	sta=QuectelM26_InitSMS(1);
	if(sta)DeBug("初始化短信[%d]",sta,Infor_Warning);
	PDU_GetCenterNumber();
	Tos_CreateTimer(UIShowValue.SaveValue.SendCycle,0xffff,Timer_Broken0);
	Timer_Broken0();
	Tos_TaskDelay(3000);
	while(1)
	{
		CurMsg=Tos_TaskGetQMsgDelay(100);
		if(CurMsg)
		{
			switch(CurMsg->Qmsg_Type)
			{
				case 0:
					DeBug("准备发送数据",Infor_Warning);
					Tos_TaskDelay(1000);
					TaskMsg=(HistoryRecord *)CurMsg->Qmsg_Addr;
					sta=QuectelM26_Connect();
					if(sta)DeBug("连接服务器[%d]",sta,Infor_Warning);
					BufferCoppy(&UIShowValue.DateTime,&HR.DT,sizeof(UIShowValue.DateTime));
					BufferCoppy(&UIShowValue.CH_Value,&HR.CH_Value,sizeof(UIShowValue.CH_Value));
					sta=QuectelM26_SendHTTP(&HR);
					if(sta)
								{
									//BufferCoppy(TaskMsg,&HR,sizeof(HistoryRecord));
									//Tos_TaskPutQmsg(Tos_GetTaskIDByName("GPRS"),0,sizeof(HistoryRecord),&HR);
									DeBug("发送失败,重新发送[%d]",sta,Infor_Warning);
									sta=QuectelM26_SendHTTP(&HR);
									if(sta)DeBug("发送数据失败[%d]",sta,Infor_Warning);
									if(sta<2)FailCount++;
								}
					else {
											
											DeBug("发送数据OK",Infor_Warning);
											GPRS_CloseNet();
											FailCount=0;RFailCount=0;
							  }
					break;
			}
			
		}
		
		Tos_TaskDelay(100);
		if(FailCount>0){Tos_TaskDelay(2000);QuectelM26_Connect();FailCount=0;RFailCount++;}
		if(RFailCount>3)goto R;
	}
}
void Task_M26LL(void *Tags)
{
	uint8 sta,i,FailCount=0,RFailCount;
//	HistoryRecord HR;
	Tos_ArrayMessage *CurMsg,Msg[3];
	HistoryRecord *TaskMsg,TaskMsgBuf[3];	
	for(i=0;i<3;i++)Msg[i].Qmsg_Addr=&TaskMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],3);
R:
	RFailCount=0;
	UIShowValue.RSSI=99;
	sta=QuectelM26_Init();
	if(sta){DeBug("注册网络失败[%d] ",sta,Infor_Warning);Tos_TaskDelay(10000);goto R;}
	else Task_AutoReg(0);
	sta=QuectelM26_InitSMS(1);
	if(sta)DeBug("初始化短信[%d]",sta,Infor_Warning);

	PDU_GetCenterNumber();
	Regdit_SendInfor();
	Tos_CreateTimer(UIShowValue.SaveValue.SendCycle,0xffff,Timer_Broken0);
	Tos_CreateTimer(28,0xffff,Timer_Broken1);
	Tos_CreateTimer(28,0xffff,Timer_Broken2);
	Tos_CreateTimer(28,0xffff,Timer_Broken3);
	Timer_Broken0();
	Tos_TaskDelay(3000);
	while(1)
	{
		CurMsg=Tos_TaskGetQMsgDelay(100);
		if(CurMsg)
		{
			switch(CurMsg->Qmsg_Type)
			{
				case 0:
					DeBug("准备发送数据",Infor_Warning);
						sta=QuectelM26_Connect();
					if(sta)DeBug("连接服务器[%d]",sta,Infor_Warning);
					QuectelM26_Config();
					Tos_TaskDelay(1000);
					TaskMsg=(HistoryRecord *)CurMsg->Qmsg_Addr;
					sta=QuectelM26_SendLL(0);
					if(sta)
								{
									DeBug("发送数据失败[%d]",sta,Infor_Warning);FailCount++;
									Tos_TaskDelay(10000);
									MCU_Reset();
								}
					else {
											DeBug("发送数据OK",Infor_Warning);
											FailCount=0;RFailCount=0;
											if(USART_RX_Buffer[1][0]==0x30)if(USART_RX_Buffer[1][1]==0x30)if(UIShowValue.SaveValue.SleepMin)TOS_Sleep(UIShowValue.SaveValue.SleepMin);
											GPRS_CloseNet();
							  }
					break;
				case 1:
					sta=QuectelM26_SendHeartbeat();
					if(sta){DeBug("发送心跳失败[%d]",sta,Infor_Warning);FailCount++;}
					else {DeBug("发送心跳OK",Infor_Warning);RFailCount=0;FailCount=0;}
					break;
				case 2:
					sta=Task_SendMsgBT();
					if(sta)DeBug("短信发给[%d]/[%d]人",sta%10,3,Infor_Warning);
					break;
				case 3:
					UIShowValue.RSSI=QuectelM26_GetCSQ();
					QuectelM26_ShowSMS();//获取短信
					break;
			}
			
		}
		
		Tos_TaskDelay(100);
		if(FailCount>0){Tos_TaskDelay(2000);QuectelM26_Connect();FailCount=0;QuectelM26_Config();RFailCount++;}
		if(RFailCount>3)goto R;
	}
}
void Task_M26KGL(void *Tags)
{
	uint8 sta,i,FailCount=0,RFailCount;
	Tos_ArrayMessage *CurMsg,Msg[1];
	HistoryRecord *TaskMsg,TaskMsgBuf[1];	
	for(i=0;i<1;i++)Msg[i].Qmsg_Addr=&TaskMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],1);
R:
	RFailCount=0;
	UIShowValue.RSSI=99;
	sta=QuectelM26_Init();
	if(sta){DeBug("注册网络失败[%d] ",sta,Infor_Warning);GPIO_Set_PWR(0);if(UIShowValue.SaveValue.SleepMin){Task_RecordNow();TOS_Sleep(UIShowValue.SaveValue.SleepMin);}while(1)Tos_TaskDelay(1000);}
	else Task_AutoReg(0);
	sta=QuectelM26_InitSMS(1);
	if(sta)DeBug("初始化短信[%d]",sta,Infor_Warning);
	sta=QuectelM26_Connect();
	if(sta)DeBug("连接服务器[%d]",sta,Infor_Warning);
	PDU_GetCenterNumber();
	Regdit_SendInfor();
	QuectelM26_Config();
	Tos_CreateTimer(UIShowValue.SaveValue.SendCycle,0xffff,Timer_Broken0);
	Tos_CreateTimer(28,0xffff,Timer_Broken1);
	Tos_CreateTimer(60,0xffff,Timer_Broken2);
	Tos_CreateTimer(5,0xffff,Timer_Broken3);
	Timer_Broken0();
	while(1)
	{
		CurMsg=Tos_TaskGetQMsgDelay(100);
		if(CurMsg)
		{
			switch(CurMsg->Qmsg_Type)
			{
				case 0:
					TaskMsg=(HistoryRecord *)CurMsg->Qmsg_Addr;
					sta=QuectelM26_SendHRKGL(TaskMsg);
					if(sta)
								{
									DeBug("发送数据失败[%d]",sta,Infor_Warning);FailCount++;
									
								}
					else {
											DeBug("发送数据OK",Infor_Warning);
											FailCount=0;RFailCount=0;
								      if(UIShowValue.SaveValue.SleepMin)TOS_Sleep(UIShowValue.SaveValue.SleepMin);
							  }
					break;
				case 1:
					sta=QuectelM26_SendHeartbeat();
					if(sta){DeBug("发送心跳失败[%d]",sta,Infor_Warning);FailCount++;}
					else {DeBug("发送心跳OK",Infor_Warning);RFailCount=0;FailCount=0;}
					break;
				case 2:
					sta=Task_SendMsgBT();
					if(sta)DeBug("短信发给[%d]/[%d]人",sta%10,3,Infor_Warning);
					break;
				case 3:
					UIShowValue.RSSI=QuectelM26_GetCSQ();
					QuectelM26_ShowSMS();//获取短信
					break;
			}
			
		}
		
		Tos_TaskDelay(100);
		if(FailCount>0){Tos_TaskDelay(2000);QuectelM26_Connect();FailCount=0;QuectelM26_Config();RFailCount++;}
		if(RFailCount>3)goto R;
	}
}
void Timer_KGM(uint8 Data)
{
	Tos_TaskPutQmsg(Tos_GetTaskIDByName("GPRS"),0,sizeof(Data),&Data);
}
void Task_M26KGM(void *Tags)
{
	uint8 sta,i,FailCount=0,RFailCount;

	Tos_ArrayMessage *CurMsg,Msg[5];
	uint8 *TaskMsg,TaskMsgBuf[5];	
	for(i=0;i<5;i++)Msg[i].Qmsg_Addr=&TaskMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],5);
R:
	RFailCount=0;
	UIShowValue.RSSI=99;
	sta=QuectelM26_Init();
	if(sta){DeBug("注册网络失败[%d] ",sta,Infor_Warning);Tos_TaskDelay(10000);goto R;}
	else Task_AutoReg(0);
	sta=QuectelM26_InitSMS(1);
	if(sta)DeBug("初始化短信[%d]",sta,Infor_Warning);
	PDU_GetCenterNumber();
	Regdit_SendInfor();
	
	Tos_CreateTimer(UIShowValue.SaveValue.SendCycle,0xffff,Timer_Broken0);
	Tos_CreateTimer(28,0xffff,Timer_Broken1);
	Timer_Broken0();
	GPRS_ToSleep();
	while(1)
	{
		CurMsg=Tos_TaskGetQMsgDelay(1);
		if(CurMsg)
		{
			switch(CurMsg->Qmsg_Type)
			{
				case 0:
					TaskMsg=(uint8 *)CurMsg->Qmsg_Addr;
					DeBug("Data[%d]",*TaskMsg,Infor_Warning);
					sta=QuectelM26_Connect();
					QuectelM26_Config();
					if(sta)DeBug("连接服务器[%d]",sta,Infor_Warning);
					sta=QuectelM26_SendHRKGM(*TaskMsg);
					if(sta)
								{
									sta=QuectelM26_SendHRKGM(*TaskMsg);
									DeBug("发送数据失败[%d]",sta,Infor_Warning);FailCount++;
								}
					else {			GPRS_CloseNet();
											DeBug("发送数据OK",Infor_Warning);
											FailCount=0;RFailCount=0;
					
							  }

					break;
				case 1:
					sta=QuectelM26_SendHeartbeat();
					if(sta){DeBug("发送心跳失败[%d]",sta,Infor_Warning);FailCount++;}
					else {DeBug("发送心跳OK",Infor_Warning);RFailCount=0;FailCount=0;}
					break;
				case 2:
					sta=Task_SendMsgBT();
					if(sta)DeBug("短信发给[%d]/[%d]人",sta%10,3,Infor_Warning);
					break;
				case 3:
					UIShowValue.RSSI=QuectelM26_GetCSQ();
					QuectelM26_ShowSMS();//获取短信
					break;
			}
			
		}
	//	else TimeSleep++;
	//	if(TimeSleep>10)if(UIShowValue.SaveValue.SleepMin)TOS_Sleep(UIShowValue.SaveValue.SleepMin);
		Tos_TaskDelay(1000);
		if(FailCount>0){Tos_TaskDelay(2000);QuectelM26_Connect();FailCount=0;QuectelM26_Config();RFailCount++;}
		if(RFailCount>3)goto R;
		
	}
}
