/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <CheakOut.h>
#include <Text.h>
#include <ModBus.h>

/******************************************************************************
Func:У��
Time:2015-7-28
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note://2�ֽڵ�ַ1�ֽ��������ֽ����ݳ��ȣ�
******************************************************************************/
BOOL MyCom_CheckCrc(uint8 *Buf)
{
	uint16 CrcValue,CrcSource,Length;
	Length=Buf[3]+6;
	CrcValue=Tools_GetCRC16(&Buf[2],Length-4); 
	CrcSource=GetWordFromBytes(&Buf[Length-2],0);
	if(CrcSource==CrcValue)return True;
	return False;
}
/******************************************************************************
Func:���У����
Time:2015-7-28
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:���Ȼ�����2
******************************************************************************/
uint16 MyCom_AppendCrc(uint8 *Buf,uint16 Length)
{
	uint16 CrcValue;
	CrcValue=Tools_GetCRC16(&Buf[2],Length-2); 
	Length+=SetWordToBytes(&Buf[Length],CrcValue,0);
	return Length;
}
/******************************************************************************
Func:������Ϣ
Time:2015-7-28
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:
******************************************************************************/
uint8 MyCom_SendMsg(uint8 *Buf,uint16 OnlyAddr,uint8 Cmd,uint8 *Data,uint8 DataLegnth)
{
	uint16 i=0;
	if(DataLegnth>76)return 0;
	i+=SetWordToBytes(&Buf[i],OnlyAddr,1);
	Buf[i++]=Cmd;
	Buf[i++]=DataLegnth;
	i+=BufferCoppy(&Data[0],&Buf[i],DataLegnth);
	i=MyCom_AppendCrc(&Buf[0],i);
	return i;
}


/******************************************************************************
*(���)  0      1 			 2        3        4      5        6        7        8      9       10
*(�ṹ)  ��ʼ		Ŀ���ַ ���ص�ַ	��Ϣ��ʶ ��ˮ��	��Ϣ���� ���ݱ�ʶ ���ݳ��� ���ݶ�	У����  ������
*(���)  1byte	1byte		 1byte		1byte		 1byte  2byte    1byte		2byte    Nbyte  1,2byte 1byte
*(����)  0      1        2        3        4      5        7        8        10     11      12
*(ע��)   ��Ϣ����Ϊ��û����Ϣ��  �ظ���Ϣ�����ݵ���ʽ�ظ�
******************************************************************************/

/*******************************************************************************
Func:����modbus
Date:2014-5-22
http://www.trtos.com/
By:ͯ����
Note:
*******************************************************************************/

/********************************************************************************
Func:ModBus����Э���������
Time:2014-6-13
Ver.:V4.0
http://www.trtos.com/
By:ͯ����
Note;
********************************************************************************/
void ModBus_Create(ModBus_Message *ModBusMsg,uint8 MasterAddr,uint8 SlaveAddr,MasterSlaveMode WorkMode,uint8 CheakMode)
{
	ModBusMsg->StartFlag=ModBus_StartFlag;
	ModBusMsg->EndFlag=ModBus_EndFlag;
	ModBusMsg->SlaveAddr=SlaveAddr;
	ModBusMsg->MasterAddr=MasterAddr;
	ModBusMsg->WorkMode=WorkMode;
	ModBusMsg->CheakMode=CheakMode;
}
/********************************************************************************
Func:ModBus������Ϣ
Time:2014-9-13
Ver.:V4.0
http://www.trtos.com/
By:ͯ����
Note;MsgFlag��Ϣ֡��ʶ,MsgNum��ˮ��,DataFlag���ݱ�ʶ
********************************************************************************/
uint16 ModBus_CreateMsg(string Buf,ModBus_Message *ModBusMsg,uint8 MsgFlag,uint8 MsgNum,uint8 DataFlag,uint8 *Data,uint16 DataLength)
{
	uint16 i=0;
	uint16 Cheak;
	ModBusMsg->MsgFlag=MsgFlag;
	ModBusMsg->MsgNum=MsgNum;
	ModBusMsg->DataFlag=DataFlag;
	ModBusMsg->DataLength=DataLength;
	if(DataLength)ModBusMsg->MsgLength=DataLength+3; 
  else ModBusMsg->MsgLength=0;
	Buf[i++]=ModBusMsg->StartFlag;
	if(ModBusMsg->WorkMode==WorkMode_Master)//��Э������Ϊ����ģʽ
	{
		Buf[i++]=ModBusMsg->SlaveAddr;
		Buf[i++]=ModBusMsg->MasterAddr;
	}else if(ModBusMsg->WorkMode==WorkMode_Slave)//��Э�������ڴӻ�ģʽ
	{
		Buf[i++]=ModBusMsg->MasterAddr;
		Buf[i++]=ModBusMsg->SlaveAddr;
	}
	Buf[i++]=ModBusMsg->MsgFlag;
	Buf[i++]=ModBusMsg->MsgNum;
	Buf[i++]=ModBusMsg->MsgLength>>8;
	Buf[i++]=ModBusMsg->MsgLength&0xff;
	if(DataLength)//����Ϣ��������
	{
		Buf[i++]=ModBusMsg->DataFlag;
		Buf[i++]=ModBusMsg->DataLength>>8;
		Buf[i++]=ModBusMsg->DataLength&0xff;
		BufferCoppy(&Data[0],&Buf[i],ModBusMsg->DataLength);i+=ModBusMsg->DataLength;
	}
	if(ModBusMsg->CheakMode==MBCM_Crc)
	{
		Cheak=Tools_GetCRC16(&Buf[0],i);
		Buf[i++]=Cheak>>8;
		Buf[i++]=Cheak&0xff;
	}else if(ModBusMsg->CheakMode==MBCM_Xor)
	{
		Buf[i++]=Tools_GetXOR8(&Buf[0],i-1);
	}
		Buf[i++]=ModBusMsg->EndFlag; 
	return i;
}

/********************************************************************************
Func:ModBus���
Time:2014-6-13
Ver.:V4.0
http://www.trtos.com/
By:ͯ����
Note;����Ϊ��������Ϣ�е�ƫ��λ��
********************************************************************************/
uint16 ModBus_Expend(string Buf,uint16 Length,ModBus_Message *ModBusMsg)
{
	uint16 i=0; 
	uint16 DataOffSet=0;
	uint16 Cheak;
	uint8 TempAddr;
	BOOL Broad_True;
	ModBusMsg->ErrorFlag=ModBus_SizeError;//��ʼ�������ʾ
	if(Buf[i++]!=ModBusMsg->StartFlag) goto Error_FlagError;//��ʼ��־����
	if(ModBusMsg->WorkMode==WorkMode_Master)//��Э�鹤��������ģʽ
	{
		if(Buf[i++]!=ModBusMsg->MasterAddr)goto Error_AddrError;
		if(Buf[i++]!=ModBusMsg->SlaveAddr);//����ģʽʱ����������Ϣ
	}else 
  if(ModBusMsg->WorkMode==WorkMode_Slave)
	{
		TempAddr=Buf[i++];
		if((TempAddr!=ModBusMsg->SlaveAddr)&(TempAddr!=ModBus_Broadcast))goto Error_AddrError;
		if(Buf[i++]!=ModBusMsg->MasterAddr);//goto Error_AddrError;//����ģʽʱ����������Ϣ
		if(TempAddr==ModBus_Broadcast)Broad_True=True;else Broad_True=False;
	}
	ModBusMsg->MsgFlag=Buf[i++]; 
	ModBusMsg->MsgNum=Buf[i++]; 
	ModBusMsg->MsgLength=Buf[i++]; 
	ModBusMsg->MsgLength<<=8;
	ModBusMsg->MsgLength|=Buf[i++]; 
	if(ModBusMsg->MsgLength)
	{
	ModBusMsg->DataFlag=Buf[i++]; 
	ModBusMsg->DataLength=Buf[i++];  
	ModBusMsg->DataLength<<=8;
	ModBusMsg->DataLength|=Buf[i++]; 
	DataOffSet=i;	
	i+=ModBusMsg->DataLength;
	if(ModBusMsg->MsgLength!=(ModBusMsg->DataLength+3))goto Error_SizeError;//��������ܶ�����Ϣ
	}   
	if(ModBusMsg->CheakMode==MBCM_Xor)
	{
		Cheak=Tools_GetXOR8(&Buf[0],i);//if(i!=(Length-2))goto Error_SizeError;
		if(Cheak!=Buf[i])goto Error_CheakError;
		else goto NotError_Return;
	}else if(ModBusMsg->CheakMode==MBCM_Crc)
	{
		Cheak=Tools_GetCRC16(&Buf[0],i);//if(i!=(Length-3))goto Error_SizeError;
		if(Cheak!=GetWordFromBytes(&Buf[i],1))goto Error_CheakError;
		else goto NotError_Return;
	}

NotError_Return:if(Broad_True==True)ModBusMsg->ErrorFlag=ModBus_Broad;
	else ModBusMsg->ErrorFlag=ModBus_Ok;
	return DataOffSet;
Error_CheakError:ModBusMsg->ErrorFlag=ModBus_CheakError;return 0;
Error_FlagError:ModBusMsg->ErrorFlag=ModBus_FlagError;return 0;
Error_AddrError:ModBusMsg->ErrorFlag=ModBus_AddrError;return 0;
Error_SizeError:ModBusMsg->ErrorFlag=ModBus_SizeError;return 0;
}
/********************************************************************************
Func:�������ݰ��Ľṹ����
Time:2014-6-13
Ver.:V4.0
http://www.trtos.com/
By:ͯ����
Note;
********************************************************************************/
void ModBus_Clear(ModBus_Message *ModBusMsg)
{
	ClearWithBuffer((uint8 *)ModBusMsg,sizeof(ModBus_Message));
}







