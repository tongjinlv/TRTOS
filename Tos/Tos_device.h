/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TOS_DERICE_H_
#define _TOS_DERICE_H_
#include <include.h>


typedef struct
{
	char *DeviceName;    //�豸����
	uint8 DeviceId;       //�豸Id
	uint8 DeviceOwnerId;  //�豸�������ĸ�����ӵ��
	uint8 DeviceWaitId;   //�ȴ���ȡ���豸������ID
	uint8 DeviceVirtue;   //�豸����
	uint8 DeviceState;    //�豸״̬
	DeviceWRFunc Write;  //�豸д�ӿ�
	DeviceWRFunc Read;   //�豸���ӿ�
	void  *Init;   //�豸��ʼ���ӿ�
	void  *Exit;   //�豸�˳��ӿ�
	uintbus Note;
}DeviceInfor;

enum DericeVirtue//�豸����
{
	DV_Array=1,//���豸
	DV_IOList=2,//IO�嵥�豸
	DV_Task=3,//��ͨ�豸
	DV_TaskValue=4,//����
};
enum DeviceState
{
	Delete   =0,//ɾ��������
	NotBusy  =1,//�豸����״̬
	Busy     =2,//�豸æ
	Ready    =3 //�豸����
};

#define DeviceNull 0xff 
#define TosErrorID 0xff
#define FlashConfigNull 0xff
extern DeviceInfor	*Tos_Device_Tab;
extern uint8 DeviceId_Index;
void DeviceList_Init(void);
void Device_Init(void);
BOOL Device_Ok(uint8 ID);
BOOL DeviceUnMount(uint8 ID);
BOOL Tos_TaskGetDev(uint8 ID,uint32 Timeout);
BOOL Tos_TaskDropDev(uint8 ID);
uint8 Device_Count(void);
void DeviceList_Printf(void);
#endif
