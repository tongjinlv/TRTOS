/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <..\USER\Prj_BlackBox\IO_Driver.h>

uint8 DeviceId_CONTROL=DeviceNull;
uint8 DeviceId_SIGNAL=DeviceNull;
void GPIO_Control_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE); 
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_9;//ָʾ��
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;//���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	Remap_SWJ_JTAGDisable();//����jtag
}
void GPIO_Signal_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ�� GPIOA �͸��ù���ʱ��
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ�� IO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ�� GPIOA �͸��ù���ʱ��
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ�� IO
}
void DeviceMount_Control()
{
	DeviceId_CONTROL=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_CONTROL].DeviceId=DeviceId_CONTROL;
	Tos_Device_Tab[DeviceId_CONTROL].DeviceName="CTR";
	Tos_Device_Tab[DeviceId_CONTROL].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_CONTROL].DeviceVirtue=ReadOnly|WriteOnly|CharDerice;
	Tos_Device_Tab[DeviceId_CONTROL].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_CONTROL].Init=GPIO_Control_Init;
	Tos_Device_Tab[DeviceId_CONTROL].Write=Null;
	Tos_Device_Tab[DeviceId_CONTROL].Read=Null;
	Tos_Device_Tab[DeviceId_CONTROL].Exit=Null;
}
void DeviceMount_Signel()
{
	DeviceId_SIGNAL=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_SIGNAL].DeviceId=DeviceId_SIGNAL;
	Tos_Device_Tab[DeviceId_SIGNAL].DeviceName="CTR";
	Tos_Device_Tab[DeviceId_SIGNAL].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_SIGNAL].DeviceVirtue=ReadOnly|WriteOnly|CharDerice;
	Tos_Device_Tab[DeviceId_SIGNAL].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_SIGNAL].Init=GPIO_Signal_Init;
	Tos_Device_Tab[DeviceId_SIGNAL].Write=Null;
	Tos_Device_Tab[DeviceId_SIGNAL].Read=Null;
	Tos_Device_Tab[DeviceId_SIGNAL].Exit=Null;
}


