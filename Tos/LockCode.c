/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <CheakOut.h>
#include <LockCode.h>

extern void IAP_Lock(void);
extern void IAP_Unlock(void);
extern void IAP_ProgramHalfWord(uint32 Address, uint16 Data);

/********************************************************************************
Func:��֤��
Date:2014-6-10
By:ͯ����
http://www.trtos.com/
Note:��֤ʹ�ܵ�CPU������Ҫ¼���CPU��ΨһID  CrcУ����
********************************************************************************/
const uint16 CodeTab[]={
0x5568,0xf451,0x6266,0x6B38,0x2423,0x1F39,0x4442,0x8461,0x44b2,0x3613,0x8E19,0xc650,0x2541,
0xbb29,0x529e,0X4887
};

uint16 GetLockCrcCode()//��ȡΨһ���
{
	uint16 CrcValue;
	CrcValue=Tools_GetCRC16((uint8 *)(0x1ffff7e8),12);  
	return CrcValue;
}
/********************************************************************************
Func:оƬ��֤
Date:2014-6-10
By:ͯ����
http://www.trtos.com/
Note:
********************************************************************************/
BOOL AppLicense()
{
	uint16 i;
	uint16 Code=GetLockCrcCode();
	for(i=0;i<sizeof(CodeTab);i++)if(Code==CodeTab[i])return True;
	return False;
}
/********************************************************************************
Func:��ֹ����
Date:2014-6-10
By:ͯ����
http://www.trtos.com/
Note:
********************************************************************************/
const uint16 DisCode=0xffff;
BOOL App_DisCoppy()
{
	uint16 CrcValue,t;
	uint32 z;
	CrcValue=Tools_GetCRC16((uint8 *)(0x1ffff7e8),12);  
	z=(uint32)&DisCode;
	t=*((uint16 *)(uint32)&DisCode);
	if(t==0xffff)
	{
		IAP_Unlock();
		IAP_ProgramHalfWord(z,CrcValue);
		IAP_Lock();
	}
	t=*((uint16 *)(uint32)&DisCode);
	if(t!=CrcValue)return False;
	return True;
}
