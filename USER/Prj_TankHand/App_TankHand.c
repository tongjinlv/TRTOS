/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <..\USER\Prj_TankHand\App_TankHand.h>
#include <..\USER\Prj_TankHand\App1_TankHand.h>
#include <..\USER\Prj_TankHand\Oled_GUI.h>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <FuncTask_Include.h>
#include <HandKey_Driver.h>
#include <GUI_Include.h>


App_RunValue Run_Value;

const OLED_MenuStruct Menu0x1200[7]={
	{"(1)����",(void *)&Menu0x1000[0],VT_Menu,1},
	{"(2)�޵�ַ %d(0-255)",(void *)&Run_Value.SValue.TankAddr,VT_Uint8,Null},
	{"(3)����ַ %d(0-255)",(void *)&Run_Value.SValue.BusAddr,VT_Uint8,Null},
  {"(4)�п� %d(0-255)",(void *)&Run_Value.SValue.CenterAddr,VT_Uint8,Null},
	{"(5)��������", (void *)&Save_Configs,VT_Task,Null},
	{0},
};
const OLED_MenuStruct Menu0x1300[7]={
	{"(1)����",(void *)&Menu0x1000[0],VT_Menu,1},
	{"(2)���� %d(50-255)",(void *)&Run_Value.SValue.Brightness,VT_Uint8,Null},
  {"(2)˯�� %d(1-255)",(void *)&Run_Value.SValue.TimeSleep,VT_Uint8,Null},
	{"(3)��������", (void *)&Save_Configs,VT_Task,Null},
	{0},
};
const OLED_MenuStruct Menu0x1400[11]={
	{"(1)����",(void *)&Menu0x1000[0],VT_Menu,1},
  {"(2)��������",(void *)&Click_ClearWeight,VT_Task,Null},
  {"(3)���ر궨",(void *)&Click_CorrectWeight,VT_Task,Null},
  {"(4)λ������",(void *)&Click_ClearRange,VT_Task,Null},
  {"(5)λ�ñ궨",(void *)&Click_CorrectRange,VT_Task,Null},
	{"(6)���ö���",(void *)&Click_CorrectFullWeight,VT_Task,Null},
	{"(7)�ָ�����(R)", (void *)&Click_ReadValue,VT_Task,Null},
  {"(8)��������(R)", (void *)&Click_SaveValue,VT_Task,Null},
  {"(9)���� %.1fT",(void *)&DevRun_Value.SensorValue[0],VT_ROMFloat,Null},
  {"(10)λ�� %.1fM",(void *)&DevRun_Value.SensorValue[1],VT_ROMFloat,Null},
	{0},
};
const OLED_MenuStruct Menu0x1500[5]={
	{"(1)����",(void *)&Menu0x1000[0],VT_Menu,1},
  {"(2)�޸�����",(void *)&Click_ChangePassword,VT_Task,Null},
  {"(3)��������",(void *)&Click_SetPassword,VT_Task,Null},
	{0},
};
const OLED_MenuStruct Menu0x1000[7]={
	{"(1)����",(void *)&MenuHome[0],VT_Menu,0},
	{"(2)��������",(void *)&Menu0x1300[0],VT_Menu,2},
	{"(3)Զ������",(void *)&Menu0x1400[0],VT_Menu,2},
  {"(4)��ȫ����",(void *)&Menu0x1500[0],VT_Menu,2},
	{0},
};
const OLED_MenuStruct Menu0x3000[10]={
	{"(1)����",(void *)&MenuHome[0],VT_Menu,0},
	{"(2)���� 0x%x",(void *)&DevRun_Value.Host_Sig_Data,VT_ROMUint32,Null},
	{"(3)��� 0x%x",(void *)&DevRun_Value.Host_Ctr_Data,VT_ROMUint32,Null},
  {"(4)״̬ 0x%x",(void *)&DevRun_Value.AllStatus,VT_ROMUint32,Null},
  {"(5)λ�� %d(ADC)",(void *)&DevRun_Value.ADC_Value[1],VT_ROMUint16,Null},
  {"(6)����A %d(ADC)",(void *)&DevRun_Value.AD6x[0],VT_ROMUint16,Null},
  {"(7)����B %d(ADC)",(void *)&DevRun_Value.AD6x[1],VT_ROMUint16,Null},
	{"(8)����C %d(ADC)",(void *)&DevRun_Value.AD6x[2],VT_ROMUint16,Null},
	{"(9)����D %d(ADC)",(void *)&DevRun_Value.AD6x[3],VT_ROMUint16,Null},
	{0},
};
const OLED_MenuStruct Menu0x4000[]={
	{"(1)����",(void *)&MenuHome[0],VT_Menu,0},
	{"(2)��������A %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_SensorG1Ok},
	{"(3)��������B %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_SensorG2Ok},
	{"(4)��������C %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_SensorG3Ok},
	{"(5)��������D %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_SensorG4Ok},
	{"(6)λ�ô��� %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_SensorR1Ok},
	{"(7)��λA %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_Tank1Place},
	{"(8)��λB %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_Tank2Place},
	{"(9)�ϵ� %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_SysPowerOn},
	{"(10)���� %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_SysError},
	{"(11)���ſ���λ %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_TapOpenRealy},
	{"(12)���Źص�λ %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_TapCloseRealy},
	{"(13)�ܷ⵽λ %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_SealedInPlace},
	{"(14)������ %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_BusRun},
	{"(15)CAN�ɼ�IO %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_SensorIOTOK},
	{"(16)CAN�޿����� %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_SensorTankOK},
	{0},
};
const OLED_MenuStruct Menu0x5000[10]={
	{"(1)����",(void *)&MenuHome[0],VT_Menu,0},
	{"(2)ϵͳ:TRTOS v2.1",Null,Null,Null},
  {"(3)״̬:%s",(void *)&Run_Value.LicStatus,VT_ROMStr,Null},
  {"(4)ע����Ϣ:%d",(void *)&Run_Value.SValue.LicCount,VT_ROMInt16,Null},
  {"(5)ע��",(void *)&Click_RegLic,VT_Task,Null},
	{0},
};
const OLED_MenuStruct MenuHome[8]={
	{"(1)����",(void *)&Menu0x1000[0],VT_Menu,1},
	{"(2)��λ��Ƶ��",(void *)Click_ResetFrq,VT_Task,Null},
  {"(3)�����в���",(void *)Menu0x3000,VT_Menu,1},
  {"(4)���ϼ��!",(void *)Menu0x4000,VT_Menu,1},
  {"(5)�����豸",(void *)Menu0x5000,VT_Menu,1},
  {"(6)���� %.1fV",(void *)&Run_Value.Voltage,VT_ROMFloat,Null},
	{0},
};
const OLED_MenuStruct MenuWork[7]={
	{"����%.1fT",(void *)&DevRun_Value.SensorValue[0],VT_Float,Null},
  {"λ��%.1fM",(void *)&DevRun_Value.SensorValue[1],VT_Float,Null},
	{"���� %s",(void *)&Run_Value.Status,VT_ROMStr,Null},
	{"����%dT",(void *)&DevRun_Value.FullWeight,VT_Uint8,Null},
	{"���� %s",(void *)&DevRun_Value.AllStatus,VT_ROMBOOL,WSA_DownLoadOver},
	{0},
};

void GoTo_Stop()
{
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1)
	{
		if(Send_ButtonCommand(2))Printf_Waiting("Stoping....",10);
    else return;		
		Printf_Infor("STOP",10);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1)Tos_TaskDelay(100);
		Printf_Waiting("Starting....",10);
	}
}
void TaskFor_SetWork(void *Tags)
{
	uint16 i;
	BOOL WorkTrue=False;
	Tos_ArrayMessage Msg[2];
  MGUI_KeyMsg *KeyMsg,KeyMsgBuf[2];	
	POWER_EN;//OLED��Դ
	LAMP9_ON;//�Ϲ�ͨ��                                                                                                        ;
	LAMP10_ON;//���ſ���λ
	LAMP11_ON;//���Źص�λ
	LAMP12_ON;//�ܷ⵽λ
	LAMP13_ON;//ͨ��
	LAMP14_OFF;//��Դ
	LAMP2_ON;//����
	LAMP3_ON;//ǿ������
	Load_Configs();
	Menu_Init(&MenuHome[0]);
	KeyBoard_Configuration();
	Tos_TaskGetHandKey();
	SetKey_WorkMode(KWM_Null);
  Set_Brightness();
  for(i=0;i<2;i++)Msg[i].Qmsg_Addr=&KeyMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],2);
	Run_Value.Status="";
	while(1)
	{
re:		 if(KeyMsg->KeyValue==Key_4)GoTo_Stop();
	 if(WorkTrue==True){Draw_Work();}
		 if(WorkTrue==False){Draw_Home();}
		 SSD1325_OutBuffer();
		 Tos_TaskDelay(1);
      KeyMsg=MUI_GetKey(0);
		 if(KeyMsg)
		 {
			if(KeyMsg->KeyType==KeyBoard_Null)goto re;
			if(WorkTrue==True)
			 {
					if(KeyMsg->KeyType==KeyBoard_Hand)
				{
				Beep_WithKey();
					Run_Value.HeartBeat=0;
					if(KeyMsg->KeyValue==Key_A){Run_Value.Status="����";Send_ButtonCommand(OC_UpDoorOpen);}
					if(KeyMsg->KeyValue==Key_B){Run_Value.Status="�ط�";Send_ButtonCommand(OC_UpDoorClose);}
					if(KeyMsg->KeyValue==Key_1){Run_Value.Status="����";Send_ButtonCommand(OC_DownDoorOpen);}
					if(KeyMsg->KeyValue==Key_3){Run_Value.Status="�ط�";Send_ButtonCommand(OC_DownDoorClose);}
					if(KeyMsg->KeyValue==Key_5)TankRelieveClick();
					if(KeyMsg->KeyValue==Key_C)TankPowerClick();
					if(KeyMsg->KeyValue==Key_D){Run_Value.Status="����";Send_ButtonCommand(OC_Start);Printf_Waiting(String_Wating,10);}//����
					if(KeyMsg->KeyValue==Key_E){Run_Value.Status="ֹͣ";Send_ButtonCommand(OC_Stop);WorkTrue=False;Menu_Init(&MenuHome[0]);Printf_Waiting(String_Wating,10);}//ͣ��
				}
				if(KeyMsg->KeyType==KeyBoard_RockerBar)
				{
					Beep_WithKey();
					Run_Value.HeartBeat=0;
					if(KeyMsg->KeyValue==Key_X)if((KeyMsg->KeyTime<0)&(KeyMsg->KeyTime>-3)){Run_Value.Status="ǰ��";Send_ButtonCommand(OC_TankForward1);}
					if(KeyMsg->KeyValue==Key_X)if((KeyMsg->KeyTime<-2)&(KeyMsg->KeyTime>-5)){Run_Value.Status="ǰ��";Send_ButtonCommand(OC_TankForward2);}
					if(KeyMsg->KeyValue==Key_X)if((KeyMsg->KeyTime>0)&(KeyMsg->KeyTime<3)){Run_Value.Status="����";Send_ButtonCommand(OC_TankBack1);}
					if(KeyMsg->KeyValue==Key_X)if((KeyMsg->KeyTime>2)&(KeyMsg->KeyTime<5)){Run_Value.Status="����";Send_ButtonCommand(OC_TankBack2);}
					if(KeyMsg->KeyValue==Key_Y)if((KeyMsg->KeyTime<0)){Run_Value.Status="�㶯";Send_ButtonCommand(OC_TankBackDot);}
				if(KeyMsg->KeyValue==Key_Y)if((KeyMsg->KeyTime>0)){Run_Value.Status="�㶯";Send_ButtonCommand(OC_TankForwardDot);}
				}
				if(KeyMsg->KeyType==KeyBoard_Null)
				{

				}
			 }
			 if(WorkTrue==False)
			 {
				 if(KeyMsg->KeyType==KeyBoard_Hand)
				{
					Beep_WithKey();
					if(KeyMsg->KeyValue==Key_1){if(PageMenu.DeepRecord[PageMenu.Index])PageMenu.DeepRecord[PageMenu.Index]--;}
					if(KeyMsg->KeyValue==Key_3){if(PageMenu.OptionLength>PageMenu.DeepRecord[PageMenu.Index])PageMenu.DeepRecord[PageMenu.Index]++;}
					if(KeyMsg->KeyValue==Key_A)PageMenu.DeepRecord[PageMenu.Index]=0;
					if(KeyMsg->KeyValue==Key_B)Enter_Menu();
					if(KeyMsg->KeyValue==Key_D){Run_Value.Status="����";WorkTrue=True;Menu_Init(&MenuWork[0]);Send_ButtonCommand(OC_Start);StartCheck();}//����
					if(KeyMsg->KeyValue==Key_E){Send_ButtonCommand(OC_Stop);}//ͣ��
				}
				if(KeyMsg->KeyType==KeyBoard_RockerBar)
				{
					Beep_WithKey();
					if(KeyMsg->KeyValue==Key_X)Run_Value.HandSpeedX=KeyMsg->KeyTime;
					if(KeyMsg->KeyValue==Key_Y)Run_Value.HandSpeedY=KeyMsg->KeyTime;
					if(KeyMsg->KeyValue==Key_X)if(KeyMsg->KeyTime<0){if(PageMenu.DeepRecord[PageMenu.Index])PageMenu.DeepRecord[PageMenu.Index]--;}
					if(KeyMsg->KeyValue==Key_X)if(KeyMsg->KeyTime>0){if(PageMenu.OptionLength>PageMenu.DeepRecord[PageMenu.Index])PageMenu.DeepRecord[PageMenu.Index]++;}
					if(KeyMsg->KeyValue==Key_Y)if(KeyMsg->KeyTime<0)PageMenu.DeepRecord[PageMenu.Index]=0;
					if(KeyMsg->KeyValue==Key_Y)if(KeyMsg->KeyTime>0)Enter_Menu();
					
				 }
			 }
		}
		
	}
}





