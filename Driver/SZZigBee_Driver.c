/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>

/******************************************************************************
 Func: У��
 Time: 2015-7-28
 Ver.: V1.0
 Note://2�ֽڵ�ַ1�ֽ��������ֽ����ݳ��ȣ�
******************************************************************************/
BOOL ZigBee_CheckCrc(uint8 *Buf)
{
	uint16 CrcValue,CrcSource,Length;
	Length=Buf[3]+6;
	CrcValue=Tools_GetCRC16(&Buf[2],Length-4); 
	CrcSource=GetWordFromBytes(&Buf[Length-2],0);
	if(CrcSource==CrcValue)return True;
	return False;
}
/******************************************************************************
 Func: ���У����
 Time: 2015-7-28
 Ver.: V1.0
 Note:���Ȼ�����2
******************************************************************************/
uint16 ZigBee_AppendCrc(uint8 *Buf,uint16 Length)
{
	uint16 CrcValue;
	CrcValue=Tools_GetCRC16(&Buf[2],Length-2); 
	Length+=SetWordToBytes(&Buf[Length],CrcValue,0);
	return Length;
}
/******************************************************************************
 Func: ������Ϣ
 Time: 2015-7-28
 Ver.: V1.0
 Note:
******************************************************************************/
uint8 ZigBee_SendMsg(uint8 *Buf,uint16 OnlyAddr,uint8 Cmd,uint8 *Data,uint16 DataLegnth)
{
	uint16 i=0;
	if(DataLegnth>76)return 0;
	i+=SetWordToBytes(&Buf[i],OnlyAddr,1);
	Buf[i++]=Cmd;
	Buf[i++]=DataLegnth;
	i+=BufferCoppy(&Data[0],&Buf[i],DataLegnth);
	i=ZigBee_AppendCrc(&Buf[0],i);
	return i;
}

/******************************************************************************
 Func: У��
 Time: 2015-7-28
 Ver.: V1.0
 Note://2�ֽڵ�ַ1�ֽ��������ֽ����ݳ��ȣ�
******************************************************************************/
BOOL ZBUS_CheckCrc(uint8 *Buf)
{
	uint16 CrcValue,CrcSource,Length;
	Length=((uint16)Buf[3])*0xff+Buf[4]+7;
	CrcValue=Tools_GetCRC16(&Buf[2],Length-4); 
	CrcSource=GetWordFromBytes(&Buf[Length-2],0);
	if(CrcSource==CrcValue)return True;
	return False;
}
/******************************************************************************
 Func: ���У����
 Time: 2015-7-28
 Ver.: V1.0
 Note:���Ȼ�����2
******************************************************************************/
uint16 ZBUS_AppendCrc(uint8 *Buf,uint16 Length)
{
	uint16 CrcValue;
	CrcValue=Tools_GetCRC16(&Buf[2],Length-2); 
	Length+=SetWordToBytes(&Buf[Length],CrcValue,0);
	return Length;
}
/******************************************************************************
 Func: ������Ϣ
 Time: 2015-7-28
 Ver.: V1.0
 Note:
******************************************************************************/
uint8 ZBUS_SendMsg(uint8 *Buf,uint16 OnlyAddr,uint8 Cmd,uint8 *Data,uint16 DataLegnth)
{
	uint16 i=0;
	i+=SetWordToBytes(&Buf[i],OnlyAddr,1);
	Buf[i++]=Cmd;
	Buf[i++]=DataLegnth/0xff;
	Buf[i++]=DataLegnth%0xff;
	i+=BufferCoppy(&Data[0],&Buf[i],DataLegnth);
	i=ZigBee_AppendCrc(&Buf[0],i);
	return i;
}

