/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <StandardModBus.h>

/******************************************************************************
Func:ĩβ���У��
Time:2016-4-28
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:�����ܳ���
******************************************************************************/

uint16 MB_AppendCrc(uint8 *Buf,uint16 Length)
{
	uint16 CrcValue;
	CrcValue=Tools_GetCRC16(&Buf[0],Length); 
	Buf[Length++]=CrcValue&0xff;
	Buf[Length++]=CrcValue>>8;
	return Length;
}
/******************************************************************************
Func:У��
Time:2016-4-28
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:�����ܳ���
******************************************************************************/
BOOL MB_CheckCrc(uint8 *Buf,uint16 Length)
{
	uint16 CrcValue,CrcSource;
	CrcValue=Tools_GetCRC16(&Buf[0],Length-2); 
	CrcSource=Buf[Length-1];CrcSource<<=8;
	CrcSource|=Buf[Length-2];
	if(CrcSource==CrcValue)return True;
	return False;
}
/******************************************************************************
Func:������ȡ����
Time:2016-4-28
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:
******************************************************************************/
uint16 MB_CreateReadMsg(uint8 *Buf,uint8 DevAddr,ModBusCmdCode CmdCode,uint16 Addr,uint16 Length)
{
	uint16 i=0;
	Buf[i++]=DevAddr;
	Buf[i++]=CmdCode;
	Buf[i++]=Addr>>8;
	Buf[i++]=Addr&0xff;
	Buf[i++]=Length>>8;
	Buf[i++]=Length&0xff;
	i=MB_AppendCrc(&Buf[0],i);
	return i;
}
