/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <FuncTask_Include.h>
#include <..\USER\Prj_7LCDSJJ\IO_Driver.c>
#include <AT24C08_Driver.c>
#include <isl1208_driver.c>
#include <..\USER\Prj_7LCDSJJ\DaCai_Driver.c>
#include <..\USER\Prj_7LCDSJJ\Kaoqinji_Driver.c>
#include <..\USER\Prj_7LCDSJJ\GPRS_Driver.c>
#include <..\USER\Prj_7LCDSJJ\App2.c>
#include <..\USER\Prj_7LCDSJJ\App1.c>

void Task0(void *Tags)
{
	
	LEDLINK_OFF;
	LEDSRART_OFF;
	LED3_OFF;
	LED2_OFF;
	LED1_R;
	ClearWithBuffer((uint8 *)&Run_Value,sizeof(Run_Value));
	ISL1208_GetDateTime(&Run_Value.SDT);
	DaCai_SetDateTime(&Run_Value.SDT);
	DaCai_SetDateLight(Run_ValueRege.Lamp);
	Run_Value.Ctr|=S9;//�������
	Run_Value.RunMode=0x00;//������֤ģʽ
	Run_Value.WorkMode=0x01;//����ģʽ
	Run_Value.SysRunSec=0x00;
	Run_Value.MaintenanceMode=0x00;
	while(1)
	{
		LEDRUN_OFF;
		LED1_RG
		Tos_TaskDelay(500);
		LEDRUN_ON;
		Tos_TaskDelay(490);
		LED1_OFF;
		Run_Value.SysRunSec++;
		ISL1208_GetDateTime(&Run_Value.DT);
		CAN_SIG_SendMsg((uint8 *)&Run_Value.Ctr,0x2a0);
		if(!(uint8)((Run_Value.Sig&S2)>0))Run_Value.RunMode&=~S4;else Run_Value.RunMode|=S4;
		if(Run_Value.WorkMode==0x01)
		{
			switch(Run_Value.RunMode)
			{
				case 0x10:Run_Value.Ctr&=~S0;Run_Value.Ctr&=~S1;break;
				case 0x11:Run_Value.Ctr|=S0;Run_Value.Ctr|=S1;break;
				default :Run_Value.Ctr&=~S0;Run_Value.Ctr&=~S1;break;
			}
		}
		else {Run_Value.Ctr&=~S0;Run_Value.Ctr&=~S1;}
		if(!(uint8)((Run_Value.Sig&S3)>0))Run_Value.RunMode=0x00;
		Task_OutSig();
		if((uint8)((Run_Value.Sig&S0)>0))Run_Value.LeftSafe&=~BIT(0);else Run_Value.LeftSafe|=BIT(0);//����λ
		if((uint8)((Run_Value.Sig&S1)>0))Run_Value.LeftSafe&=~BIT(1);else Run_Value.LeftSafe|=BIT(1);//����λ
		if((uint8)((Run_Value.Sig&S4)>0))Run_Value.LeftError&=~BIT(6);else Run_Value.LeftError|=BIT(6);//��·����
		if((uint8)((Run_Value.Sig&S2)>0))Run_Value.LeftActive&=~BIT(3);else Run_Value.LeftActive|=BIT(3);//����
		if((uint8)((Run_Value.Sig&S3)>0))Run_Value.LeftActive&=~BIT(4);else Run_Value.LeftActive|=BIT(4);//˫��
		if((uint8)((Run_Value.Sig&S5)>0))Run_Value.LeftActive&=~BIT(7);else Run_Value.LeftActive|=BIT(7);//����
		if((uint8)((Run_Value.Sig&S6)>0))Run_Value.LeftActive&=~BIT(8);else Run_Value.LeftActive|=BIT(8);//����
	}
}
void TaskKey(void *Tags)
{
	uint16 i;
	Tos_ArrayMessage *CurMsg,Msg[10];
  MGUI_KeyMsg *KeyMsg,KeyMsgBuf[10];	
	for(i=0;i<10;i++)Msg[i].Qmsg_Addr=&KeyMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],10);
	Tos_TaskGetKeyCode();
	while(1)
	{		
		Tos_TaskDelay(10);
		 CurMsg=Tos_TaskGetQMsg();
		if(CurMsg)
		{
			KeyMsg=CurMsg->Qmsg_Addr;
			if(Run_ValueRege.Lamp>4)if(KeyMsg->KeyValue==Key_Up)Run_ValueRege.Lamp-=4;
			if(Run_ValueRege.Lamp<220)if(KeyMsg->KeyValue==Key_Down)Run_ValueRege.Lamp+=4;
			if(KeyMsg->KeyValue==Key_Enter)Save_Configs();
			DaCai_SetDateLight(Run_ValueRege.Lamp);
		}
	}
}
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;	
	if (CAN_GetITStatus(CAN1, CAN_IT_FMP0)!=RESET)	 //FIFO1��Ϣ�Һ�״̬��־ 
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);     //����жϱ��
		CAN_Receive(CAN1, CAN_FIFO0, &RxMessage); 	 //��FIFO1�еı�����浽��ʱ�ṹ����
		switch(RxMessage.StdId)
			{
				case 0x1c0:Run_Value.Sig=Uint32FromByte(&RxMessage.Data[0]);break;
				default:break;
			}
	}	
}
int main(void)
{
	RCC_Configuration();
	DeviceList_Init();
	DeviceMount_Usart(USART1);
	DeviceMount_Usart(USART2);
	DeviceMount_Usart(USART3);
	DeviceMount_Control();
	DeviceMount_Signel();
	DeviceMount_CodeKey();
	DeviceMount_Flash();
	DeviceMount_ISL1208();
	DeviceMount_Can1();
	Device_Init();
	Tos_Init();
 	Tos_TaskCreate(0,Task0,Null,"Tast0",3000);
	Tos_TaskCreate(1,GPRS_Task2,Null,"Tast0",5000);
	Tos_TaskCreate(2,LCD_Command,Null,"Tast0",1000);
	Tos_TaskCreate(4,KQ_Command,Null,"Tast0",3000);
	Tos_TaskCreate(5,TaskKey,Null,"Tast0",1000);
	Tos_Start();
	while(1);
}


