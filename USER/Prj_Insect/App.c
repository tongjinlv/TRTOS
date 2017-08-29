/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
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
		DeBug("配置参数片区一错误",Infor_Warning);
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
	{"保存配置",(void *)&System_SaveConfig,VT_Task,Null},
	{"读取配置",(void *)&Task_LoadConfigs,VT_Task,Null},
	{"重启设备",(void *)&System_Reset,VT_Task,Null},
	{"左接近:%d",(void *)&UIShowValue.ADC[0],VT_Uint16,Null},
	{"右接近:%d",(void *)&UIShowValue.ADC[3],VT_Uint16,Null},
	{"左前方:%d",(void *)&UIShowValue.ADC[5],VT_Uint16,Null},
	{"中间:%d",(void *)&UIShowValue.ADC[4],VT_Uint16,Null},
	{"右前方:%d",(void *)&UIShowValue.ADC[2],VT_Uint16,Null},
	{"电压:%d",(void *)&UIShowValue.ADC[1],VT_Uint16,Null},
	{"菜单",Null,VT_End,Null},
};
