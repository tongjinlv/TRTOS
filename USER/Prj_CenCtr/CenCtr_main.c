/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#ifdef BOARD_CENCTR

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
	}
}


void Task1(void *Tags)
{

	while(1) 
	{
		Tos_TaskDelay(1000);
		
	}
}
void Task2(void *Tags)
{

	while(1)
	{
		Tos_TaskDelay(10);
	}
}
void Task3(void *Tags)
{
	while(1)
	{
		Tos_TaskDelay(1000);
	}
}

void Task4(void *Tags)
{
	while(1)
	{
		Tos_TaskDelay(50);
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
	DeviceMount_TQFS();//����TQFS�ļ�ϵͳ
	Device_Init();//�Թ��ص��豸���г�ʼ��
	Tos_Init();//Tosϵͳ��ʼ��
	Tos_TaskCreate(0,Task0,3000);
	Tos_TaskCreate(1,Task1,3000);
	Tos_TaskCreate(2,Task2,2000);
	Tos_TaskCreate(3,Task3,2000);
	Tos_TaskCreate(4,Task4,2000);
	Tos_Start();//Tosϵͳ����
	while(1);
}
#endif

