/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <COMEnu.h>
#include <stdlib.h>
#include <..\USER\Prj_Insect\App.h>
UIShowStruct UIShowValue;

void CreateTask(void(*vfFuncPointer)(void *Tags))
{
	Tos_TaskCreateFindID(vfFuncPointer,0,"CT",1000);
}
int RandomADC(int Max,int Min)
{
	int num;
	srand(UIShowValue.ADC[5]+UIShowValue.ADC[1]);
	num = rand() % (Max - Min) + Min; 
	return num;
}
void RandomLight(uint32 A,uint32 B)
{
	WS_ShadeBit(0,A,S2|S3);
	WS_ShadeBit(A,B,S2|S3);
	WS_ShadeBit(B,0,S2|S3);
}
void RandomEYE()
{
	RandomLight(RandomADC(0xffffff,0xff),RandomADC(0xffffff,0xff));
	
}
void Task_SaveConfigs()
{
	UIShowValue.SaveValue.CH.Size=sizeof(UIShowValue.SaveValue);
	Save_AppConfig(&UIShowValue.SaveValue,0);
	Save_AppConfig(&UIShowValue.SaveValue,1);
}

BOOL BOOL_LoadConfigs()
{
	BOOL Ok;
	Ok=Load_AppConfig(&UIShowValue.SaveValue,0);
	if(!Ok)
	{
		DeBug("���ò���Ƭ��һ����",Infor_Warning);
		Ok=Load_AppConfig(&UIShowValue.SaveValue,1);
	}
	return Ok;
}
void System_ResetDelay()
{
	Tos_TaskDelay(100);
	MCU_Reset();
}
void System_SaveConfig()
{
	Tos_TaskDelay(10);
	Task_Join(Task_SaveConfigs,FT_VoidFuncVoid,Null);
}
void System_Reset()
{
	Task_Join(System_ResetDelay,FT_VoidFuncVoid,Null);
}
void Task_LoadConfigs()
{
	BOOL_LoadConfigs();
}

void Task_ReBackConfigs()
{
	Load_AppConfig(&UIShowValue.SaveValue,1);
}

const COM_MenuStruct MenuList[]={
	{"��������",(void *)&System_SaveConfig,VT_Task,Null},
	{"��ȡ����",(void *)&Task_LoadConfigs,VT_Task,Null},
	{"�����豸",(void *)&System_Reset,VT_Task,Null},
	{"��ӽ�:%d",(void *)&UIShowValue.ADC[0],VT_Uint16,Null},
	{"�ҽӽ�:%d",(void *)&UIShowValue.ADC[3],VT_Uint16,Null},
	{"��ǰ��:%d",(void *)&UIShowValue.ADC[5],VT_Uint16,Null},
	{"�м�:%d",(void *)&UIShowValue.ADC[4],VT_Uint16,Null},
	{"��ǰ��:%d",(void *)&UIShowValue.ADC[2],VT_Uint16,Null},
	{"��ѹ:%d",(void *)&UIShowValue.ADC[1],VT_Uint16,Null},
	{"�˵�",Null,VT_End,Null},
};
