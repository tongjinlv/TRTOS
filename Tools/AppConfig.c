/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <AppConfig.h>
#include <CheakOut.h>
/**************************************************************************************
����:������Ӧ�������ļ�ʱ��Ҫ��Ӧ�ò����ṹ��ͷ������ConfigHeadStructʵ��

**************************************************************************************/

extern void IAP_Lock(void);
extern void IAP_Unlock(void);
extern void IAP_ProgramHalfWord(uint32 Address, uint16 Data);
extern void IAP_ErasePage(uint32 Page_Address);

/**************************************************************************************
Func:��Ƭ���ڲ�flash���
Time:2015-07-25
Ver.1.0  	
http://www.trtos.com/
By:ͯ����
Note: SizeΪ���ݳ�����sizeof��ʵ�壩
**************************************************************************************/
void Flash_WriteData(uint32 Addr,void *Data,uint16 Size)
{
	#define SmallPageSize 512
	uint16 i,c=0;
	uint16 *P;
	P=(uint16 *)Data;
	IAP_Unlock();
	c=Size/SmallPageSize;
	if(Size%SmallPageSize)c++;
	for(i=0;i<c;i++)IAP_ErasePage(Addr+SmallPageSize*i);
	i=0;
	while(Size--)IAP_ProgramHalfWord(Addr+i++*2,*P++);
	IAP_Lock();
}
/**************************************************************************************
Func:Flash�ڲ�falsh����
Time:2015-07-25
Ver.1.0  	
http://www.trtos.com/
By:ͯ����
Note: SizeΪ���ݳ�����sizeof��ʵ�壩
**************************************************************************************/
void Flash_ReadData(uint32 Addr,void *Data,uint16 Size)
{
	uint8 *P,*S;
	P=(uint8 *)Data;
	S=(uint8 *)(Addr);
	while(Size--)*P++=*S++;
}
/**************************************************************************************
Func:���ʹ洢����
Time:2015-09-5
Ver.1.0  	
http://www.trtos.com/
By:ͯ����
Note: Sector�洢����
**************************************************************************************/
void Save_VoidConfig(void(*Save)(uint32 Addr,void *Data,uint16 Size),uint32 Addr,void *Data,uint16 Sector)
{
	uint16 *S;
	ConfigHeadStruct *CHS;
	S=(uint16 *)Data;
	CHS=(ConfigHeadStruct *)S;
	CHS->CrcValue=Tools_GetCRC16((uint8*)(uint32)((uint32)Data+sizeof(ConfigHeadStruct)),CHS->Size-sizeof(ConfigHeadStruct));
	Save(Addr+Sector*CONFIG_SECTOR_SPACE,S,CHS->Size);
}
/**************************************************************************************
Func:�洢Ӧ�ó����������
Time:2015-09-5
Ver.1.0  	
http://www.trtos.com/
By:ͯ����
Note: Sector�洢����
**************************************************************************************/
void Save_AppConfig(void *Data,uint16 Sector)
{
	assert_param(Sector<2);//���ڱ�������ֻ����ʹ���������õ�λ
	Save_VoidConfig(Flash_WriteData,CONFIGS_ADDR_BASE,Data,Sector);
}
/**************************************************************************************
Func:��ȡ��������
Time:2015-09-5
Ver.1.0  	
http://www.trtos.com/
By:ͯ����
Note: 
**************************************************************************************/
BOOL Load_VoidConfig(void(*Load)(uint32 Addr,void *Data,uint16 Size),uint32 Addr,void *Data,uint16 Sector)
{
	uint8 *P;
	uint16 CrcValue;
	ConfigHeadStruct *CHS;
	assert_param(Sector<2);
	P=(uint8 *)Data;
	Load(Addr+Sector*CONFIG_SECTOR_SPACE,Data,4 );//��ȡͷ��
	CHS=(ConfigHeadStruct *)P;
	if(CHS->Size>2048|CHS->Size<4)goto Error;
	Load(Addr+Sector*CONFIG_SECTOR_SPACE,Data,CHS->Size);
	CrcValue=Tools_GetCRC16((uint8*)(uint32)((uint32)P+sizeof(ConfigHeadStruct)),CHS->Size-sizeof(ConfigHeadStruct));
	if(CrcValue!=CHS->CrcValue)goto Error;
	return True;
Error:
	return False;
}
/**************************************************************************************
Func:��ȡ��������
Time:2015-09-5
Ver.1.0  	
http://www.trtos.com/
By:ͯ����
Note: 
**************************************************************************************/
BOOL Load_AppConfig(void *Data,uint16 Sector)
{
	assert_param(Sector<2);//���ڱ�������ֻ����ʹ���������õ�λ
	return Load_VoidConfig(Flash_ReadData,CONFIGS_ADDR_BASE,Data,Sector);
}
/**************************************************************************************
Func:����������Ϣ
Time:2015-09-5
Ver.1.0  	
http://www.trtos.com/
By:ͯ����
Note: 
**************************************************************************************/
void Create_Message(void *Buf,uint8 Length)
{
	ConfigHeadStruct *CHS;
	CHS=(ConfigHeadStruct *)Buf;
	CHS->Size=Length;
	CHS->CrcValue=Tools_GetCRC16((uint8*)(uint32)((uint32)Buf+sizeof(ConfigHeadStruct)),CHS->Size-sizeof(ConfigHeadStruct));
}
/**************************************************************************************
Func:������Ϣ
Time:2015-09-5
Ver.1.0  	
http://www.trtos.com/
By:ͯ����
Note: 
**************************************************************************************/
BOOL Export_Message(void *Buf,uint8 Length)
{
	uint16 CrcValue;
	ConfigHeadStruct *CHS;
	if(Length<sizeof(ConfigHeadStruct))return False;
	CHS=(ConfigHeadStruct *)Buf;
	if(CHS->Size!=Length)return False;
	CrcValue=Tools_GetCRC16((uint8*)(uint32)((uint32)Buf+sizeof(ConfigHeadStruct)),CHS->Size-sizeof(ConfigHeadStruct));
	if(CrcValue!=CHS->CrcValue)return False;
	return True;
}

















