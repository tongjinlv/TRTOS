/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_Prafire\IO_Driver.h>
#include <STM32_CPU.h>
uint8 DeviceId_IO=DeviceNull;
uint8 KeyIn_Tos_TaskID=Tos_TaskNull;

const GPIO_InitStruct IO_GPIO_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOE,GPIO_Pin_5|GPIO_Pin_6},
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC, GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5},
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA, GPIO_Pin_0|GPIO_Pin_5},
	{0},
};
/******************************************************************************
 Func:��ȡ������׼�ӿں���
 Time: 2015�´�����28
 Ver.: V1.0
 Note:
******************************************************************************/
void IO_Read(void *Addr,void *Buffer,void *Length)
{
	uint8 *TempBit=Addr;
	*TempBit=0x00;
	if(!SIG1)(*TempBit)|=S0;
	if(!SIG2)(*TempBit)|=S1;
}
void IO_Write(void *Addr,void *Buffer,void *Length)
{
	uint8 *TempBit=Addr;
	if(*TempBit&BIT(0))CTR1_ON;else CTR1_OFF;
	if(*TempBit&BIT(1))CTR2_ON;else CTR2_OFF;
	if(*TempBit&BIT(2))CTR3_ON;else CTR3_OFF;
}
/******************************************************************************
 Func:����
 Time: 2015�´�����28
 Ver.: V1.0
 Note:��ȡ����
******************************************************************************/
void Tos_TaskGetIO_InPut()
{
	KeyIn_Tos_TaskID=Tos_TaskCurrent;
}
void Task_GetKey(void *Tags)
{
	uint8 Value;
	MGUI_KeyMsg KeyMsg;
	while(1)
	{
		 Tos_TaskDelay(10);
		 IO_Read((void *)&Value,Null,Null);
		 if(Value)
		 {
		 if(Value&S0)KeyMsg.KeyValue=Key_Right;
		 if(Value&S1)KeyMsg.KeyValue=Key_Down; 
		 Tos_TaskPutQmsg(KeyIn_Tos_TaskID,KeyBoard_Hand,sizeof(MGUI_KeyMsg),&KeyMsg);
		 Tos_TaskDelay(300);
		 }
	}
}
/******************************************************************************
 Func:���ڼ�������
 Time: 2015�´�����28
 Ver.: V1.0
 Note:
******************************************************************************/
void DeviceMount_IO()
{
	DeviceId_IO=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_IO].DeviceId=DeviceId_IO;
	Tos_Device_Tab[DeviceId_IO].DeviceName="IO_Driver";
	Tos_Device_Tab[DeviceId_IO].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_IO].DeviceVirtue=DV_IOList;
	Tos_Device_Tab[DeviceId_IO].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_IO].Init=GPIO_InitList;
	Tos_Device_Tab[DeviceId_IO].Note=(uintbus)&IO_GPIO_List[0];	
	Tos_Device_Tab[DeviceId_IO].Write=IO_Write;
	Tos_Device_Tab[DeviceId_IO].Read=IO_Read;
	Tos_Device_Tab[DeviceId_IO].Exit=Null;
}

