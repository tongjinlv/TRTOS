
<<<<<<<<<<<�ڶԱ�TOSϵͳ��TGUI�����޸Ļ�����������ѭ���¹淶>>>>>>>>>>>>
���汾������
�����°汾�����Ӻͼ򻯣���Ծɹ��̲����ֲ���ͻ
���ṹ�淶��
������֯�ṹ���밴��ԭ�ṹ�Ժ��������������Ը���,�ṹ�������Ĵ����ֹ�ϴ���svn.
����������ϵ�����ܶ�������ȷ��ϵͳ�Ŀɲü��Ժ���ֲ��.

���汾�淶��
�汾�Ź淶 Ver3.43
Version=3.0�汾,�ڸ���Ŀ¼�ṹ�Ϳ�ܽṹ��ʱ�����汾������.
Subedition=43�汾,�����ӻ��޸������ȷǿ�ܽṹ���汾������.


�����ע�⡿
���ж��ڲ����������������л���ֻ�ܶ�������л���.

����������÷���
typedef union 
{
	uint16 W;
	struct
	{
		uint8 a;
		uint8 b;
	}b;
}Word2Byte;

��ʹ���������ؽ���jlinkģʽ��
Remap_SWJ_JTAGDisable();

��BOOTLoader��
Ӧ�ó���ʼ����	�����ж�������ַ
NVIC_SetVectorTable(0x08005000,0);
������淶��
�����Ӻ���ע�����ٱ�֤���������ܽ���(Func)������޸�����(Date)����ע������(Note).
������ע�� ����(Writer)���汾(Ver).


���½����̡�
�½�����ʱ��Ҫ�Թ�������������
�޸�C/C+ѡ���define��ֵ�������Ψһ���͡�����output �е�obj����������û���Ŀ¼��
��������޸�cpu���ͼ������С�ͳ���ռ��ַ�滮

	��			  MCU�ͺ�		FLASH��С      
			     STM32F101xx	  			   |
STM32F10X_LD     STM32F102xx	16~32Kbytes    |
			     STM32F103xx				   |
-----------------------------------------------|				 
				 STM32F101xx				   |
STM32F10X_MD	 STM32F102xx	64~128Kbytes   |
				 STM32F103xx				   |
-----------------------------------------------|
			     STM32F101xx				   |
STM32F10X_HD     STM32F102xx    256~512KBytes  |
				 STM32F103xx 				   |
-----------------------------------------------|
				 STM32F101xx  				   |
STM32F10X_CL     STM32F102xx    			   |
				 STM32F103xx				   |
-----------------------------------------------|

��̬�ڴ�����ʹ��
����Ҫ���ڴ�ѽ��г�ʼ��
ִ�г�ʼ������	
	static uint8 MemBuf[40000];//���������ʹ�þֲ���̬����Ҳ����ʹ��ȫ�ֱ������⺯��ʹ�õľ�Ȼ������ֲ�����
	Mema_Init(&MemBuf[0]);
ʹ��������������ָ�� void *P;
P=Mema_Malloc(�ڴ��С);
���žͿ���ʹ��Pָ��ָ��ķ��Ϳռ�ʵ����
ʹ����ɿ��Զ��ڴ�����ͷ�
Mema_Free��P);�����ر���������Pָ��ĵ�ֵַ��������;�����޸�

����ԭ�ȵ�����ͨ�ýӿ���δ������������������Ϊ�鷳������ֱ�Ӳ���
void Task0(void *Tags)
{
	uint8 Out;

	DeBug_OutSet(DeBug_USART2);//������Ϣͨ�����ڴ�ӡ
	DeBug_SetType(Infor_All);//ֻ��ӡInfor���͵���Ϣ
	while(1)
	{
		Out=0x05;
		//if(!SIG1)Joystick_Send(0x51,0x03,0,0);
		Tos_Device_Tab[DeviceId_IO].Write((void *)&Out,Null,Null);
		Tos_TaskDelay(1000);
		Out=0x02;
		Tos_Device_Tab[DeviceId_IO].Write((void *)&Out,Null,Null);
		Tos_TaskDelay(1000);
	}
}

void _IAP_Command(void *Tags)
{
	uint16 Length;
	uint16 MasterAddr;
	uint16 OffSet;
	uint8 Buf[1500];
	BufferFill(&Buf[0],0xff,sizeof(Buf));
	while(1)
	{
		ClearWithBuffer(&USART1_RX_Buffer[0],sizeof(USART1_RX_Buffer));
		Length=USART1_ReadDatas(Null,sizeof(USART1_RX_Buffer),0);
		MasterAddr=GetWordFromBytes(&USART1_RX_Buffer[0],1);
		if(ZigBee_CheckCrc(&USART1_RX_Buffer[0]))
		{
			WaitDownLoadCount=50;
			Length=5;
			MasterAddr=GetWordFromBytes(&USART1_RX_Buffer[OSE_DevAddr],1);
			switch(USART1_RX_Buffer[OSE_Cmd])
			{
				case SCFF_Write64Byte:
					OffSet=USART1_RX_Buffer[OSE_DataStart];
					OffSet*=64;
					if(OffSet>=sizeof(Buf))break;
					BufferCoppy(&USART1_RX_Buffer[Length],&Buf[OffSet],64);
					break;
				case SCFF_Read1024Byte:
		      IAP_ReadDatas(ApplicationAddress+FLASH_PAGESIZE*GetWordFromBytes(&USART1_RX_Buffer[OSE_DataStart],1),(uint16 *)&Buf[0],512);
				  Length=ZigBee_SendMsg(&USART1_TX_Buffer[0],MasterAddr,SCFF_Read64Byte,&Buf[0],64);
				  USART1_DMAWriteDatas(&USART1_TX_Buffer[0],Length);
					break;
				case SCFF_Read64Byte:
					OffSet=USART1_RX_Buffer[OSE_DataStart];
					OffSet*=64;
				  if(OffSet>=sizeof(Buf))break;
					Length=ZigBee_SendMsg(&USART1_TX_Buffer[0],MasterAddr,SCFF_Read64Byte,&Buf[OffSet],64);
				  USART1_DMAWriteDatas(&USART1_TX_Buffer[0],Length);
					break;
				case SCFF_Write1024Byte:
				  if(Tools_GetCRC16(&Buf[0],FLASH_PAGESIZE)==GetWordFromBytes(&USART1_RX_Buffer[OSE_DataStart],1))
					{
						FLASH_WriteBank(ApplicationAddress+FLASH_PAGESIZE*(GetWordFromBytes(&USART1_RX_Buffer[OSE_DataStart+2],1)),&Buf[0],1024);
						Length=ZigBee_SendMsg(&USART1_TX_Buffer[0],MasterAddr,SCFF_Write1024Byte,&USART1_RX_Buffer[OSE_DataStart+2],2);
						USART1_DMAWriteDatas(&USART1_TX_Buffer[0],Length); 
					}
					BufferFill(&Buf[0],0xff,sizeof(Buf));
				  break;
					case SCFF_GoToBootLoader:
					FLASH_ProgramDone();
					Application_Run(ApplicationAddress);
				  break;
				case SCFF_EraseFlase:
				  	FLASH_ProgramStart(Uint32FromByte(&USART1_RX_Buffer[OSE_DataStart]));
				    Length=ZigBee_SendMsg(&USART1_TX_Buffer[0],MasterAddr,SCFF_EraseFlase,&USART1_RX_Buffer[OSE_DataStart],4);
						USART1_DMAWriteDatas(&USART1_TX_Buffer[0],Length); 
				  break;
			}
		}
	}
}

����̰�����

/*************************************************************
Func:  �����������
Date:  2015-7-27
Note:  �����ṹ��
*************************************************************/
typedef struct{
	ConfigHeadStruct CHS;
	uint8 Name[11];
	uint8 Age;
	f32 Weight;
	f32 Height;
	uint16 eHeight;
}UserInfor;
UserInfor UI;
/*************************************************************
Func:  �����������
Date:  2015-7-27
Note:  ʹ��
*************************************************************/
void Task1(void *Tags)
{
	char *m;
	StringCoppy("TomCat ba",&UI.Name[0]);
	UI.Age=99;
	UI.Weight=112.11;
	UI.Height=33.33;
	UI.CHS.Size=sizeof(UI);
  //Save_AppConfig(&UI,0);
	while(1)
	{
		if(Load_AppConfig(&UI,0)){
	    DeBug("UI.Age=%d",UI.Age,Infor_Infor);
		DeBug("UI.Name=%s",UI.Name,Infor_Infor);
		DeBug("UI.Weight=%.2f",UI.Weight,Infor_Infor);
		DeBug("UI.Height=%.2f",UI.Height,Infor_Infor);
		DeBug("UI.Size=%d",UI.CHS.Size,Infor_Infor);
		}
		Tos_TaskDelay(100);
	}
}
/*************************************************************
Func:  ��Ϣ���е��÷�
Date:  2014-9-10
Note:  ���շ�
*************************************************************/
void TaskReviceQMsg(void *Tags)
{
	uint8 Buf[100];
	uint16 i;
	Tos_ArrayMessage *CurMsg,Msg[10];
	TQFS_Open_File NewOpenFile;
	CanRxMsg *RxMessage;	
	CanRxMsg RxMessageBuf[10];	
	i=TQFS_FindKeyPageMark(FT_FileHead,FT_FileHead);
	TQFS_SetCursor(&NewOpenFile,i,0);
	for(i=0;i<10;i++)Msg[i].Qmsg_Addr=&RxMessageBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],10);
	while(1)
	{
		Tos_TaskDelay(10);
		CurMsg=Tos_TaskGetQMsg();
		if(CurMsg)
		{
		RxMessage=CurMsg->Qmsg_Addr;
		DeBug("RxMessage->Data[0]=%d",RxMessage->Data[0],Infor_Infor);
		}
	}
}
/*************************************************************
Func:  ��Ϣ���е��÷�
Date:  2014-9-10
Note:  ���ͷ�
*************************************************************/
void TaskSendQMsg(void *Tags)
{
    uint8 i;
	CanRxMsg RxMessage;	
	while(1)
	{
		Tos_TaskDelay(100);
		RxMessage.Data[0]=i++;
		Tos_TaskPutQmsg(2,0,sizeof(CanRxMsg),&RxMessage);
	}
}

/*************************************************************
Func:  Nrf2401ʹ��
Date:  2014-9-22
Note:  ���ͷ�
*************************************************************/
int main(void)
{
  
   SPI_NRF_Init();
   
  /* ����1��ʼ�� */
	USART1_Config();

	printf("\r\n ����һ�� NRF24L01 ���ߴ���ʵ�� \r\n");
   	printf("\r\n �������ߴ��� ������ �ķ�����Ϣ\r\n");
	printf("\r\n   ���ڼ��NRF��MCU�Ƿ��������ӡ�����\r\n");

	 /*���NRFģ����MCU������*/
   	status = NRF_Check(); 

	/*�ж�����״̬*/  
   if(status == SUCCESS)	   
   		 printf("\r\n      NRF��MCU���ӳɹ���\r\n");  
   else	  
   	     printf("\r\n  NRF��MCU����ʧ�ܣ������¼����ߡ�\r\n");


 while(1)
		{
	   	printf("\r\n ������ ������Ӧ����ģʽ\r\n"); 
	 	NRF_TX_Mode();
		 	
			/*��ʼ��������*/	
		status = NRF_Tx_Dat(txbuf);	  
		  
		  /*�жϷ���״̬*/
		  switch(status)
		  	{
		  	  case MAX_RT:
			 	 	printf("\r\n ������ û���յ�Ӧ���źţ����ʹ��������޶�ֵ������ʧ�ܡ� \r\n");
				 break;
	
			  case ERROR:
			  	 	printf("\r\n δ֪ԭ���·���ʧ�ܡ� \r\n");
				 break;
	
			  case TX_DS:
			  		printf("\r\n ������ ���յ� �ӻ��� ��Ӧ���źţ����ͳɹ��� \r\n");	 		
				 break;  								
		  	}			   	
	
	 	printf("\r\n ������ �������ģʽ�� \r\n");	
		NRF_RX_Mode();
	
			/*�ȴ���������*/
		status = NRF_Rx_Dat(rxbuf);
	
			/*�жϽ���״̬*/
			switch(status)
			{
			 case RX_DR:
			 	for(i=0;i<4;i++)
				{					
					printf("\r\n ������ ���յ� �ӻ��� ���͵�����Ϊ��%d \r\n",rxbuf[i]);
					txbuf[i] =rxbuf[i];
				}
				  break;
	
			 case ERROR:
				  	printf("\r\n ������ ���ճ���   \r\n");
				  break;  		
			}
		} 

}


void Task_Face(void *Tags)
{
	uint8 Buf[100];
	IpPortStruct IPPort;
	BEEP_ON;
	Tos_TaskDelay(4);
	BEEP_OFF;
	while(1)
	{
		RTC_Get();
		Ht1621_DrawHome();
		DHT11_Read(&UIShowValue.CH_Value[0],&UIShowValue.CH_Value[1]);
		Tos_TaskDelay(500);
//		IpPortFromString(&IPPort,"121.121.10.121:8080");
//		DeBug_Get();
//		DeBug("%d.%d.%d.%d:%d",IPPort.Ip[0],IPPort.Ip[1],IPPort.Ip[2],IPPort.Ip[3],IPPort.Port,Infor_Error);
//		IpPortToString(&IPPort,&Buf[0]);
//		DeBug("%s",&Buf[0],Infor_Error);
		
	}
}

��ϵͳ��ʱ���÷���
void Tasdk()
{
	DeBug("ZZZZZZZZZZZZZZZZZZZ",4);
}
void Tasdk1()
{
	DeBug("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",4);
}


void Task_1(void *Tags)
{
	Tos_Timer *P,*P2;
	P=Tos_CreateTimer(1,TTF_FOREVER,Tasdk);
	P2=Tos_CreateTimer(4,TTF_FOREVER,Tasdk1);
	Tos_TaskDelay(10000);
	Tos_DeleteTimer(P);
	Tos_DeleteTimer(P2);
	P=Tos_CreateTimer(1,TTF_FOREVER,Tasdk);
	while(1)
	{
		Tos_TaskDelay(100);
	}
}
void Task3(void *Tags)
{
	uint8 *P;
	uint8 i;
	const buf[1000];
	uint8 Buf[100];
	Tos_TaskDelay(2000);
	DeBug("start",4);
	GetStringByFmt(&Buf[0],"{SensorData:[{'Value1':%.2f},{'Value2':%d},{'Value2':%s}]}",12.0,6,"trtos");
	while(1)
	{
		Tos_TaskDelay(1000);
		Tos_TaskDelay(1000);
		DeBug("%s",Buf,4);
	}
}
uint8 Json_Get(uint8 *Str,uint8 *Buf,uint8 *Get)
{
	uint8 da=0,db=0;
	BOOL Ok=False;
	uint8 *P;
	P=Strstr(Str,Get);
	P+=GetTextLength(Get);
	while(*P)
	{
		if(*P=='['){da++;Ok=True;}
		if(!da)if(*P=='{'){db++;Ok=True;}
		if(*P==']')da--;
		if(!da)if(*P=='}')db--;
		if((da==0)&(db==0)&Ok){(*Buf++)=*P;return GetTextLength(Buf); }
		if((da|db))(*Buf++)=*P;
		P++;
	}
}
void Task4(void *Tags)
{
	uint8 *P="{SensorData:[{'Value1':12.00},{'Value2':6},{'Value2':trtos}]}";
	uint8 Buf[100];
	Tos_TaskDelay(2000);
	DeBug("start",4);
	BufferFill(Buf,0x00,sizeof(Buf));
	Json_Get(P,Buf,"SensorData");
	while(1)
	{
		Tos_TaskDelay(1000);
		Tos_TaskDelay(1000);
		DeBug("%s",Buf,4);
		
	}
}
