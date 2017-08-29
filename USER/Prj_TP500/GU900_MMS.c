/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <include.h>
#include <Driver_Include.h>
#include <string.h>

BOOL GPRS_CommandAck(char *Send,uint8 *Ack,uint16 Wating)
{
	uint8 i=3;
	uint8 Length;
	while(i--)
	{
		USART_WriteLine(USART2,Send);
		BufferFill(USART_RX_Buffer[1],0x00,USART_RX_BUFFER_SIZE);
		Length=USART_ReadDatas(USART2,Null,50,Wating);
		if(Length)if(strstr((const char *)USART_RX_Buffer[1],(const char *)Ack))return True;
	}
	return False;
}
uint16 GPRS_SendLength=0x6e;
uint16 GPRS_SendData()
{
	uint8 Buf[200];
	uint16 i=0;
	Buf[i++]=0x32;//��Ϣ���ͣ�������Ϣ ��UDPͨ��QOS����һ��
	Buf[i++]=GPRS_SendLength;//���ݳ��ȣ�������127���ֽ�һ��ֻ��Ҫһ���ֽڱ�ʾ
	Buf[i++]=0x00;//�汾
	Buf[i++]=0x10;//���ӱ�־
	i+=BufferCoppy(&UIShowValue.SaveValue.LoginHead[0],&Buf[i],sizeof(UIShowValue.SaveValue.LoginHead));
	Buf[i++]=0x00;//
	Buf[i++]=0x01;//
	USART_WriteDatas(USART2,&Buf[0],i);
	GPRS_SendLength=i+USART_WriteLine(USART2,"{\"sensorDatas\":[{\"value\":+%.2f},{\"value\":+%.2f},{\"lat\":%.6f,\"lng\":%.6f}]}",UIShowValue.CH_Value[0],UIShowValue.CH_Value[1],12,123);
	GPRS_SendLength-=2;
	return i;
}


void GPRS_SendMessage()
{
	USART_WriteDatas(USART2,"+++",3);
	Tos_TaskDelay(1500);
	if(GPRS_CommandAck("AT+CMGF=1","OK",1000)){DeBug_Get();USART_WriteLine(USART2,"����");}
	if(GPRS_CommandAck("AT+CSCS=\"GB2312\"","OK",1000)){DeBug_Get();USART_WriteLine(USART2,"���ø�ʽ");}
	USART_WriteLine(USART2,"AT+CMGS=\"%s\"\r",&UIShowValue.SaveValue.CallNumber[0][0]);
	USART_WriteLine(USART2,"���±���%cAT+CMGF=1",0x1a);
	USART_WriteLine(USART2,"",0x1a);
	if(GPRS_CommandAck("ATO0","OK",1000)){DeBug_Get();USART_WriteLine(USART2,"�˳�");}

}
void Task_GPRS(void *Tags)
{
	while(1)
	{
		
			
//		if(GPRS_CommandAck("AT+CSTT=\"CMNET\"","OK",1000)){DeBug_Get();DeBug_WriteLine(USART2,"�ƶ�");}
//		if(GPRS_CommandAck("AT+CSTT=\"UNINET\"","OK",1000)){DeBug_Get();DeBug_WriteLine(USART2,"��ͨ");}
//		if(GPRS_CommandAck("ATE0","OK",1000)){DeBug_Get();DeBug_WriteLine(USART2,"�����");}
//		if(GPRS_CommandAck("AT&W","OK",1000)){DeBug_Get();DeBug_WriteLine(USART2,"��������");}
		Tos_TaskDelay(10000);	
		GPRS_SendData();
		//GPRS_SendMessage();
	}
}
