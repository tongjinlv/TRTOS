/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <..\USER\Prj_TankCtr\IO_Driver.h>
#include <..\USER\Prj_TankCtr\App_TankCtr1.h>
/*
0ң������
1ң��ֹͣ
2λ��ʶ��1
3λ��ʶ��2
4λ��ʶ��3
5λ��ʶ��4
6ǰ��
7����
8�ٶ�2
9�ٶ�3
10��Ƶ����λ
11�Ϲ�һͨ��
12�Ϲ޶�ͨ��
*/
#define Def_DelayValue 12 //��������źŴ����ӳٽϴ�������Ӵ�ֵ
DevRun_ValueStruct DevRun_Value;
TankRun_ValueStruct TankRun_Value;
uint8 DelayBuf[SENSOR_CTR_COUNT];
void App_SetButtonDelay(uint8 i)
{
		switch(i)
	  {
		case OC_UpDoorOpen:DelayBuf[1]=0;DelayBuf[0]=Def_DelayValue;break;
		case OC_UpDoorClose:DelayBuf[0]=0;DelayBuf[1]=Def_DelayValue;break;
		case OC_DownDoorOpen:DelayBuf[3]=0;DelayBuf[2]=Def_DelayValue;break;
		case OC_DownDoorClose:DelayBuf[2]=0;DelayBuf[3]=Def_DelayValue;break;
		}	
}

void App_TankButton(void *Tags)
{
	
	uint8 i;
	while(1)
	{
		Tos_TaskDelay(100);
		for(i=0;i<SENSOR_CTR_COUNT;i++)
		{
			if(DelayBuf[i])DelayBuf[i]--;
			if(DelayBuf[i]==0)DevRun_Value.CTR_DATABIT&=~BIT(i);else DevRun_Value.CTR_DATABIT|=BIT(i);
		}
		CTR_SetUint32(DevRun_Value.CTR_DATABIT);
	}
}
