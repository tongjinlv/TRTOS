/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <TQFS_Include.h>
#include <FuncTask_Include.h>
void Task0(void *Tags)
{
	Printf_SysInfor();
	while(1)
	{
		LED_ON;
		Tos_TaskDelay(30);
		LED_OFF;
		Tos_TaskDelay(100);	
		LED_ON;
		Tos_TaskDelay(30);
		LED_OFF;
		Tos_TaskDelay(1000);	
		DeBug("Tos_CPUInfor.Userate_CPU=%d",Tos_CPUInfor.Userate_CPU,Infor_Infor);
	}
}


void Task1(void *Tags)
{

 	File_Infor FI;
	TQFS_Open_File NewOpenFile;
 	uint16 i;
	TQFS_Init();
  TQFS_FormatNand();
	i=TQFS_FindKeyPageMark(FT_NotUsed,FT_FileHead);
	TQFS_FileRoomInfor(&FI,"TempTest3.txt",0,ReadOnly|WriteOnly);
	TQFS_CreateFileRoom(&NewOpenFile,i,&FI);
	TQFS_SetCursor(&NewOpenFile,i,0);
	while(1) 
	{
		TQFS_WritePageContext(&NewOpenFile,(uint8 *)"�˲�����",8);
		DeBug("NewOpenFile.Page=%d Offset=%d",NewOpenFile.PageCursor,NewOpenFile.OffsetCursor,Infor_Infor);
		Tos_TaskDelay(1000);
		DeBug("%d",Nand_GetID(),Infor_Infor);
	}
}
void Task2(void *Tags)
{
	uint16 i;
  Tos_ArrayMessage *CurMsg,Msg[10];
  CanRxMsg *RxMessage,RxMessageBuf[10];	
	TQFS_Open_File NewOpenFile;
	for(i=0;i<10;i++)Msg[i].Qmsg_Addr=&RxMessageBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],10);
	i=TQFS_FindKeyPageMark(FT_FileHead,FT_FileHead);
	TQFS_SetCursor(&NewOpenFile,i,0);

	while(1)
	{
		Tos_TaskDelay(10);
		CurMsg=Tos_TaskGetQMsg();
		if(CurMsg)
		{
			RxMessage=CurMsg->Qmsg_Addr;
		  DeBug("RxMessage=%s",&RxMessage->Data[0],Infor_Infor);
			//DeBug("RxMessage.Data[0]=%d",RxMessage->Data[0],Infor_Infor);
		}
		DeBug("Get RxMessage",Infor _Infor);
	}
}
void Task3(void *Tags)
{
	//AD7705_Init(0);
	while(1)
	{
		//Printf_ObjectFileList(FT_RootDirHead,0);
		Tos_TaskDelay(100);
		//TQFS_CreateRootFolder();
	//	DeBug("TQFS_SearchFileByNameAndType%d",TQFS_SearchFileByNameAndType("Root",FT_RootDirHead),Infor_Infor);
	//	Printf_Bytes(&Buf[0],10);
		//DeBug("AD7705_GetCH1=%d",AD7705_ReadFitel(),Infor_Infor);
	}
}

void Task4(void *Tags)
{
  uint32 i;
	TQFS_Open_File NewOpenFile;
	CAN1_Filter_Configs(0,True);
	TQFS_SetCursor(&NewOpenFile,i,0);
	CANBUS_Create(True);
	CANBUS_Start();
	while(1)
	{
		
		//CAN1_SendMsg("nihao",5);
		//CANBUS_TXD_DeviceReset(CanBus_Broadcast);
		//CANBUS_TXD_DeviceSetAddr(0X1);
	//	CANBUS_TXD_DeviceSetU32Data(0x1,0x12335454);
		
		CANBUS_TXD_DeviceGetData(0x1,2);
		
	//	BufferCoppy("nihao",&RxMessage.Data[0],6);
		//RxMessage.Data[0]=i++;
	//	Tos_TaskPutQmsg(2,0,sizeof(CanRxMsg),&RxMessage);
		Tos_TaskDelay(100);
	}
}

int main(void)
{
	RCC_Configuration();//ʱ�ӿ���������
	DeBug_Init();//���Թ��ܳ�ʼ��
	DeviceList_Init();//�豸�б��ʼ��
	DeviceMount_Usart1();//����Usart����1
	DeviceMount_Led();//����led�豸��led��ʵ���Բ������豸����
	DeviceMount_Flash();//����flash
	DeviceMount_NandFlash();//����TQFS�ļ�ϵͳ
	Device_Init();//�Թ��ص��豸���г�ʼ��
	Tos_Init();//Tosϵͳ��ʼ��
	Tos_TaskCreate(0,Task0,Null,"Task_System",3000);
	Tos_TaskCreate(1,Task1,Null,"TaskTask1",3000);
	//Tos_TaskCreate(2,Task2,Null,"TaskTask2",2000);
	//Tos_TaskCreate(3,Task_CAN_Master,Null,"Task_CAN_Master",2000);
	//Tos_TaskCreate(4,Task4,Null,"Task4",2000);
	Tos_Start();//Tosϵͳ����
	while(1);
}
#endif

