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
#ifdef BOARD_TANK_Ctr
	uint8 n;
	switch(i)
	  {
		case OC_Start:DelayBuf[0]=Def_DelayValue;DelayBuf[1]=0;break;//ң������
		case OC_Stop:DelayBuf[1]=Def_DelayValue;DelayBuf[0]=0;DelayBuf[4]=0;DevRun_Value.AllStatus&=~WSA_Relieve;break;//ң��ֹͣ
		case OC_TankPowerON:if(DevRun_Value.AllStatus&WSA_Tank1Place)DelayBuf[11]=Def_DelayValue;if(DevRun_Value.AllStatus&WSA_Tank2Place)DelayBuf[12]=Def_DelayValue;DevRun_Value.AllStatus|=WSA_TankPowerOn;break;//�����ϵ�
		case OC_TankPowerOFF:DelayBuf[11]=0;DelayBuf[12]=0;DevRun_Value.AllStatus&=~WSA_TankPowerOn;break;//���Ӷϵ�
		case OC_TankForward1:if(DevRun_Value.AllStatus&WSA_TankPowerOn)return;DelayBuf[6]=Def_DelayValue;DelayBuf[8]=Def_DelayValue;break;//ǰ��1��
		case OC_TankForward2:if(DevRun_Value.AllStatus&WSA_TankPowerOn)return;DelayBuf[6]=Def_DelayValue;break;//ǰ��2��
		case OC_TankBack1:if(DevRun_Value.AllStatus&WSA_TankPowerOn)return;DelayBuf[7]=Def_DelayValue;DelayBuf[8]=Def_DelayValue;break;//����1��
		case OC_TankBack2:if(DevRun_Value.AllStatus&WSA_TankPowerOn)return;DelayBuf[7]=Def_DelayValue;break;//����2��
		case OC_TankResetFrq:DelayBuf[10]=Def_DelayValue;break;//��Ƶ����λ
		case OC_TankLock:for(n=0;n<SENSOR_CTR_COUNT;n++)DelayBuf[n]=0;break;//��ͣ
		case OC_HandReset:for(n=6;n<10;n++)DelayBuf[n]=0;break;//�ֱ���λ
		case OC_Relieve:DelayBuf[4]=Def_DelayValue;DevRun_Value.AllStatus|=WSA_Relieve;break;//ǿ�ƽ��
		case OC_UnRelieve:DelayBuf[4]=0;DevRun_Value.AllStatus&=~WSA_Relieve;break;//�ָ�ǿ�ƽ��
		case OC_TankForward1R:if(DevRun_Value.AllStatus&WSA_TankPowerOn)return;DelayBuf[4]=Def_DelayValue;DelayBuf[6]=Def_DelayValue;DelayBuf[8]=Def_DelayValue;break;//ǰ��1��
		case OC_TankForward2R:if(DevRun_Value.AllStatus&WSA_TankPowerOn)return;DelayBuf[4]=Def_DelayValue;DelayBuf[6]=Def_DelayValue;break;//ǰ��2��
		case OC_TankBack1R:if(DevRun_Value.AllStatus&WSA_TankPowerOn)return;DelayBuf[4]=Def_DelayValue;DelayBuf[7]=Def_DelayValue;DelayBuf[8]=Def_DelayValue;break;//����1��
		case OC_TankBack2R:if(DevRun_Value.AllStatus&WSA_TankPowerOn)return;DelayBuf[4]=Def_DelayValue;DelayBuf[7]=Def_DelayValue;break;//����2��
		}
#endif
#ifdef BOARD_TANK_Ctr1
		
		switch(i)
	  {
		case OC_UpDoorOpen:if(!(TankRun_Value.AllStatus&WSA_TankPowerCheckRealy))return;if(!(TankRun_Value.AllStatus&WSA_IfTankRunDownTrue))return;DelayBuf[1]=0;DelayBuf[0]=Def_DelayValue;break;
		case OC_UpDoorClose:if(!(TankRun_Value.AllStatus&WSA_TankPowerCheckRealy))return;if(!(TankRun_Value.AllStatus&WSA_IfTankRunDownTrue))return;DelayBuf[0]=0;DelayBuf[1]=Def_DelayValue;break;
		case OC_DownDoorOpen:if(!(TankRun_Value.AllStatus&WSA_TankPowerCheckRealy))return;if((TankRun_Value.AllStatus&WSA_IfTankRunDownTrue))return;DelayBuf[3]=0;DelayBuf[2]=Def_DelayValue;break;
		case OC_DownDoorClose:if(!(TankRun_Value.AllStatus&WSA_TankPowerCheckRealy))return;if((TankRun_Value.AllStatus&WSA_IfTankRunDownTrue))return;DelayBuf[2]=0;DelayBuf[3]=Def_DelayValue;break;
		}
#endif	

}
void App_BusButton(void *Tags)
{
	uint8 i;
	while(1)
	{
		Tos_TaskDelay(100);
		for(i=0;i<SENSOR_CTR_COUNT;i++)
		{
			if((i!=11)&(i!=12))
			if(DelayBuf[i])DelayBuf[i]--;
			if(DelayBuf[i]==0)DevRun_Value.CTR_DATABIT&=~BIT(i);else DevRun_Value.CTR_DATABIT|=BIT(i);
			if(DelayBuf[4]==0)DevRun_Value.AllStatus&=~WSA_Relieve;else DevRun_Value.AllStatus|=WSA_Relieve;
		}
		CTR_SetUint32(DevRun_Value.CTR_DATABIT);
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
			//if((i!=1)&(i!=0))
			if(DelayBuf[i])DelayBuf[i]--;
			if(DelayBuf[i]==0)DevRun_Value.CTR_DATABIT&=~BIT(i);else DevRun_Value.CTR_DATABIT|=BIT(i);
		}
		CTR_SetUint32(DevRun_Value.CTR_DATABIT);
	}
}
