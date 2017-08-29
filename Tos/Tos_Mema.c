/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Tos_Mema.h>
#include <text.h>
TOS_MEMA_Ptr *RootMema;

uint8 MemBuf[MEMA_BUFFER_SIZE];
/********************************************************************************
Func: �ڴ��ʼ��
Time: 2015-09-14
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note; �����ڴ�ѵ�ַ
********************************************************************************/
void Mema_Init(uint8 *Addr)
{
	RootMema=(TOS_MEMA_Ptr *)Addr;//��λ�õ��ڴ��ͷ
	RootMema->NextPtr=0;
	RootMema->Size=sizeof(TOS_MEMA_Ptr);
}
/********************************************************************************
Func: �����ڴ�
Time: 2015-09-14
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note; ȥ���˸��ڵ�
********************************************************************************/
void *Mema_Malloc(uint16 Size)
{
	TOS_MEMA_Ptr *P=RootMema,*TP;
	Size+=sizeof(TOS_MEMA_Ptr);
	while(P->NextPtr!=0)
	{
		if(((uint32)P->NextPtr-(uint32)P-P->Size)>=Size)//����ǰ�ڵ�ͺ�ڵ�֮���ܲ��������
		{
			TP=(TOS_MEMA_Ptr *)((uint32)P+P->Size);
			TP->Size=Size;
			TP->NextPtr=P->NextPtr;
			P->NextPtr=TP;
			return (uint8 *)((uint32)TP+sizeof(TOS_MEMA_Ptr));
		}
		P=P->NextPtr;
	}
	TP=(TOS_MEMA_Ptr *)((uint32)P+P->Size);
	TP->NextPtr=0;
	TP->Size=Size;
	P->NextPtr=TP;
	
	return (uint8 *)((uint32)TP+sizeof(TOS_MEMA_Ptr));
}
/********************************************************************************
Func: �����ڴ�ʹ�����
Time: 2015-09-14
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note; ȥ���˸��ڵ�
********************************************************************************/
uint32 Mema_Count()
{
	TOS_MEMA_Ptr *P=RootMema;
	uint32 Size=P->Size;
	while(P->NextPtr!=0)
	{
		P=P->NextPtr;
		Size+=P->Size;
	}
	return Size;
}
/********************************************************************************
Func:�ͷ�ռ���ڴ�
Time: 2015-09-14
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note; ȥ���˸��ڵ�
********************************************************************************/
void Mema_Free(void *Addr)
{
	TOS_MEMA_Ptr *P=RootMema,*TP=0;
	while(P->NextPtr)
	{
		if((uint32)P==((uint32)(uint8 *)Addr-sizeof(TOS_MEMA_Ptr)))goto Free;
		TP=P;
		P=P->NextPtr;
	}
	if(TP)TP->NextPtr=0;return;
Free:
	TP->NextPtr=P->NextPtr;//�����ڵ�����ӽڵ㸸�ڵ���ӽڵ��������ڵ��ӽڵ�
}
uint32 Mema_GetSize(void *Addr)
{
	TOS_MEMA_Ptr *P;
	 P=(TOS_MEMA_Ptr *)((uint32)Addr-sizeof(TOS_MEMA_Ptr));
	return (P->Size-sizeof(TOS_MEMA_Ptr));
}
/********************************************************************************
Func:�ı�����
Time: 2015-11-12
Ver.: V1.0
http://www.trtos.com/
By:ͯ����
Note; 
********************************************************************************/
void *Mema_Extend(void *Addr,uint16 Size)
{
	uint8 *PR;
	TOS_MEMA_Ptr *P;
	PR=Mema_Malloc(Size);
	P=(TOS_MEMA_Ptr *)((uint8 *)Addr-sizeof(TOS_MEMA_Ptr));
	BufferCoppy(Addr,PR,P->Size-sizeof(TOS_MEMA_Ptr));
	Mema_Free(Addr);
	return PR;
}

