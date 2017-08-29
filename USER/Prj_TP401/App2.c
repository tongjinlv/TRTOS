/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_TP401\App2.h>
void BEEP_Double()
{
	BEEP_ON;
	Tos_TaskDelay(10);
	BEEP_OFF;
	Tos_TaskDelay(40);
	BEEP_ON;
	Tos_TaskDelay(10);
	BEEP_OFF;
}
void Task_BeepDouble()
{
	Task_Join(BEEP_Double,FT_VoidFuncVoid,Null);
}
void Task_SaveConfigs()
{
	UIShowValue.SaveValue.CH.Size=sizeof(UIShowValue.SaveValue);
	Save_AppConfig(&UIShowValue.SaveValue,0);
	Save_AppConfig(&UIShowValue.SaveValue,1);
}
void Task_SaveNandConfig()
{
	UIShowValue.SaveValue.CH.Size=sizeof(UIShowValue.SaveValue);
	W25Q16_SaveConfig(&UIShowValue.SaveValue,0);
}
void Task_LoadNandConfig()
{
	W25Q16_LoadConfig(&UIShowValue.SaveValue,0);
}
void Task_BackConfigs()
{
	UIShowValue.SaveValue.CH.Size=sizeof(UIShowValue.SaveValue);
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
uint8 Get_PrintfRecordCount()
{
	uint8 i=0;
	NandHistoryRecord NHR;
	while(1)
	{
		W25Q16_Read(i*sizeof(NandHistoryRecord)+RECORDADDR,&NHR,sizeof(NandHistoryRecord));
		if(NHR.NextAddr==0xffffffff)break;
		else i++;
		Tos_TaskDelay(1);
		if(i>=0xff)break;
	}
	DeBug("��ӡ��¼����%d",i,Infor_Warning);
	return i;
}
void Task_RecordNow()
{
	NandHistoryRecord NHR;
	if(UIShowValue.RecordCount<0xff)if(UIShowValue.SaveValue.WorkBit&WCB_RecordEN)
	{
	BufferCoppy(&UIShowValue.DateTime,&NHR.HR.DT,sizeof(UIShowValue.DateTime));
	BufferCoppy(&UIShowValue.CH_Value,&NHR.HR.CH_Value,sizeof(UIShowValue.CH_Value));
	NHR.NextAddr=(uint32)UIShowValue.RecordCount*sizeof(NandHistoryRecord)+RECORDADDR+sizeof(NandHistoryRecord);
	SPI_FLASH_BufferWrite((uint8*)&NHR, (uint32)UIShowValue.RecordCount*sizeof(NandHistoryRecord)+RECORDADDR, sizeof(NandHistoryRecord));
	DeBug("�˿̼�¼���洢[%d]",UIShowValue.RecordCount,Infor_Warning);
	UIShowValue.RecordCount++;
	}
}
void Task_Record()
{
	static uint8 TimeCount=0,OldTime,Tout=0,ko=1;
	uint8 TempCycle;
	if((UIShowValue.RunFlag&(WRF_CH1Max|WRF_CH1Min))||(UIShowValue.RunFlag&(WRF_CH2Max|WRF_CH2Min)))TempCycle=2;
	else TempCycle=UIShowValue.SaveValue.RecordCycle;
	if(Tout<100)Tout++;
	if(Tout<10)return;
	if(UIShowValue.SaveValue.SleepMin)
	{
		if(ko)Task_RecordNow();
		ko=0;
		return ;
	}
	if(OldTime!=UIShowValue.DateTime.Min)
	{
		TimeCount++;
		OldTime=UIShowValue.DateTime.Min;
		if(TimeCount>=TempCycle)
		{
			TimeCount=0;
			Task_RecordNow();
		}
	}
}
void Task_Record1()
{
	static uint8 TimeCount=0,OldTime,Tout=0;
	NandHistoryRecord NHR;
	if(Tout<100)Tout++;
	if(Tout<10)return;
	if(OldTime!=UIShowValue.DateTime.Hour)
	{
		TimeCount++;
		OldTime=UIShowValue.DateTime.Hour;
		if(TimeCount>=UIShowValue.SaveValue.RecordCycle)
		{
			TimeCount=0;
			if(UIShowValue.RecordCount<0xff)
			{
			BufferCoppy(&UIShowValue.DateTime,&NHR.HR.DT,sizeof(UIShowValue.DateTime));
			BufferCoppy(&UIShowValue.CH_Value,&NHR.HR.CH_Value,sizeof(UIShowValue.CH_Value));
			NHR.NextAddr=(uint32)UIShowValue.RecordCount*sizeof(NandHistoryRecord)+RECORDADDR+sizeof(NandHistoryRecord);
			SPI_FLASH_BufferWrite((uint8*)&NHR, (uint32)UIShowValue.RecordCount*sizeof(NandHistoryRecord)+RECORDADDR, sizeof(NandHistoryRecord));
			DeBug("�˿̼�¼���洢[%d]",UIShowValue.RecordCount,Infor_Warning);
			UIShowValue.RecordCount++;
			}
		}
	}
}
void Task_PrintfLog()
{

}
void Task_PrintfCurOnlyOne()
{

}
extern void Printf_SysInfor(void);

void Task0_Init()
{
 if(!BOOL_LoadConfigs())UIShowValue.SaveValue.DeBugCFG=0xff;
	DeBug_OutSet(DeBug_USART1);//������Ϣͨ�����ڴ�ӡ
	DeBug_SetType(UIShowValue.SaveValue.DeBugCFG);//ֻ��ӡInfor���͵���Ϣ
	Printf_SysInfor();
	UIShowValue.RunFlag=0;
	UIShowValue.SysWorkMode=0;
	UIShowValue.RecordCount=0;
	UIShowValue.CH_Hold[0].Max=-200;
	UIShowValue.CH_Hold[1].Max=-200;
	UIShowValue.CH_Hold[0].Min=200;
	UIShowValue.CH_Hold[1].Min=200;
	E3V3_OFF;
}
void Task_Plan()
{
	static uint8 i=0,c=0,b=0;
	static uint32 Pool;
	uint16 T;
	uint8 m;
	T=FlowPoolFilter(&Pool,UIShowValue.ADC[0],&b,10);
	UIShowValue.CH_Value[CH_LENGTH]=T*2.5/2048;
	c++;
	if(c>20)
	{
		c--;
		for(m=0;m<CH_LENGTH;m++)
		{
			if(UIShowValue.CH_Value[m]>UIShowValue.CH_Hold[m].Max)UIShowValue.CH_Hold[m].Max=UIShowValue.CH_Value[m];
			if(UIShowValue.CH_Value[m]<UIShowValue.CH_Hold[m].Min)UIShowValue.CH_Hold[m].Min=UIShowValue.CH_Value[m];
		}
	}
	if(UIShowValue.RunFlag&WRF_SensorCH1Connected)
	{
	if(UIShowValue.CH_Value[0]>=UIShowValue.SaveValue.CH_Limit[0].Max)UIShowValue.RunFlag|=WRF_CH1Max;else UIShowValue.RunFlag&=~WRF_CH1Max;
	if(UIShowValue.CH_Value[0]<=UIShowValue.SaveValue.CH_Limit[0].Min)UIShowValue.RunFlag|=WRF_CH1Min;else UIShowValue.RunFlag&=~WRF_CH1Min;
	}
	if(UIShowValue.RunFlag&WRF_SensorCH2Connected)
	{
	if(UIShowValue.CH_Value[1]>=UIShowValue.SaveValue.CH_Limit[1].Max)UIShowValue.RunFlag|=WRF_CH2Max;else UIShowValue.RunFlag&=~WRF_CH2Max;
	if(UIShowValue.CH_Value[1]<=UIShowValue.SaveValue.CH_Limit[1].Min)UIShowValue.RunFlag|=WRF_CH2Min;else UIShowValue.RunFlag&=~WRF_CH2Min;
	}
	if(UIShowValue.CH_Value[2]<3.3)i++;
	else i=0;
	#ifndef BOARD_TP502T
	if(i>200)
		{
//				BEEP_Double();
//				GPIO_DeInit(GPIOA);
//				GPIO_DeInit(GPIOB);
//				GPIO_DeInit(GPIOC);
//				GPIO_DeInit(GPIOD);
//				GPIO_DeInit(GPIOE);
//				Standby_Init();
		}
		#endif
}
void Task_HistoryRecord(void *Tags)
{
	uint32 i=0;
	NandHistoryRecord NHR;
	//float CH_Value[CH_LENGTH];
	if(!(UIShowValue.SaveValue.WorkBit&WCB_HistoryRecord))
	{
		DeBug("�ر���ʷ��¼",Infor_Warning);
		Tos_TaskDelete(Tos_TaskCurrent);
	}
	while(1)
	{
		W25Q16_Read(i*sizeof(NandHistoryRecord)+HISTORYADDR,&NHR,sizeof(NandHistoryRecord));
		if(NHR.NextAddr==0xffffffff)break;
		else i++;
		if(i>0xfff0)
		{
			
			DeBug("��¼����%d",i,Infor_Warning);
			DeBug("��ʷ��¼���",Infor_Warning);
			DeBug("�ر���ʷ��¼",Infor_Warning);
			Tos_TaskDelete(Tos_TaskCurrent);
		}
		Tos_TaskDelay(1);
	}
	Tos_TaskDelay(5000);
	DeBug("��¼����%d",i,Infor_Warning);
	while(1)
	{
		
		//Tos_TaskDelay(60000*UIShowValue.SaveValue.RecordCycle); ˾���
		
		
//		BufferCoppy(&UIShowValue.CH_Value,&CH_Value,sizeof(UIShowValue.CH_Value));//��ͨ��
//		if(UIShowValue.CH_Value[0]>=UIShowValue.SaveValue.CH_Limit[0].Max)UIShowValue.CH_Value[0]=(UIShowValue.SaveValue.CH_Limit[0].Max*0.98+UIShowValue.CH_Value[0]*0.01);
//		if(UIShowValue.CH_Value[0]<=UIShowValue.SaveValue.CH_Limit[0].Min)UIShowValue.CH_Value[0]=(UIShowValue.SaveValue.CH_Limit[0].Min+UIShowValue.CH_Value[0]*0.01);
//		if(UIShowValue.CH_Value[1]>=UIShowValue.SaveValue.CH_Limit[1].Max)UIShowValue.CH_Value[1]=(UIShowValue.SaveValue.CH_Limit[1].Max*0.98+UIShowValue.CH_Value[1]*0.01);
//		if(UIShowValue.CH_Value[1]<=UIShowValue.SaveValue.CH_Limit[1].Min)UIShowValue.CH_Value[1]=(UIShowValue.SaveValue.CH_Limit[1].Min+UIShowValue.CH_Value[1]*0.01);

		
		BufferCoppy(&UIShowValue.DateTime,&NHR.HR.DT,sizeof(UIShowValue.DateTime));
		BufferCoppy(&UIShowValue.CH_Value,&NHR.HR.CH_Value,sizeof(UIShowValue.CH_Value));
		NHR.NextAddr=i*sizeof(NandHistoryRecord)+HISTORYADDR+sizeof(NandHistoryRecord);
		SPI_FLASH_BufferWrite((uint8*)&NHR, i*sizeof(NandHistoryRecord)+HISTORYADDR, sizeof(NandHistoryRecord));i++;
		DeBug("�˿����ݱ���¼%d",i,Infor_Warning);
		Tos_TaskDelay(5*60000);	
		
//		BufferCoppy(&CH_Value,&UIShowValue.CH_Value,sizeof(UIShowValue.CH_Value));
//			
//			
		
	}
}
void Task_HistoryRecord1(void *Tags)
{
	uint32 i=0;
	NandHistoryRecord NHR;
	if(!(UIShowValue.SaveValue.WorkBit&WCB_HistoryRecord))
	{
		DeBug("�ر���ʷ��¼",Infor_Warning);
		Tos_TaskDelete(Tos_TaskCurrent);
	}
	while(1)
	{
		W25Q16_Read(i*sizeof(NandHistoryRecord)+HISTORYADDR,&NHR,sizeof(NandHistoryRecord));
		if(NHR.NextAddr==0xffffffff)break;
		else i++;
		if(i>0xfff0)
		{
			
			DeBug("��¼����%d",i,Infor_Warning);
			DeBug("��ʷ��¼���",Infor_Warning);
			DeBug("�ر���ʷ��¼",Infor_Warning);
			Tos_TaskDelete(Tos_TaskCurrent);
		}
		Tos_TaskDelay(1);
	}
	Tos_TaskDelay(5000);
	DeBug("��¼����%d",i,Infor_Warning);
	while(1)
	{
		
		if(UIShowValue.SaveValue.RecordCycle)
		{
		BufferCoppy(&UIShowValue.DateTime,&NHR.HR.DT,sizeof(UIShowValue.DateTime));
		BufferCoppy(&UIShowValue.CH_Value,&NHR.HR.CH_Value,sizeof(UIShowValue.CH_Value));
		NHR.NextAddr=i*sizeof(NandHistoryRecord)+HISTORYADDR+sizeof(NandHistoryRecord);
		SPI_FLASH_BufferWrite((uint8*)&NHR, i*sizeof(NandHistoryRecord)+HISTORYADDR, sizeof(NandHistoryRecord));i++;
		DeBug("�˿����ݱ���¼%d",i,Infor_Warning);
		}else Tos_TaskDelay(1000);
		Tos_TaskDelay((uint32)UIShowValue.SaveValue.RecordCycle*60000);		
		
	}
}
void Task_PrintfSelectHistory(uint8 *Buf)
{
	uint32 i=0,t;
	NandHistoryRecord NHR;
	DeBug_Get();
	if(UIShowValue.DateTime.Year==0x00)
	{
		DeBug("ϵͳʱ��δ����",0);goto Exit;
	}
	if(UIShowValue.SaveValue.WorkBit&WCB_DTH11)DeBug("����,�¶�[1],ʪ��[1],�¶�[2],ʪ��[2],�¶�[3],ʪ��[3]",0);
	else DeBug("����,�¶�,�¶�",0);
	t=(uint16)Buf[0]*30+Buf[1];
	while(1)
	{
		W25Q16_Read(i*sizeof(NandHistoryRecord)+HISTORYADDR,&NHR,sizeof(NandHistoryRecord));
		if(((uint16)NHR.HR.DT.Mon*30+NHR.HR.DT.Day)>=t)break;
		if(NHR.NextAddr==0xffffffff)break;
		i++;
	}
	t=(uint16)Buf[2]*30+Buf[3];
	while(1)
	{
	W25Q16_Read(i*sizeof(NandHistoryRecord)+HISTORYADDR,&NHR,sizeof(NandHistoryRecord));
	if(((uint16)NHR.HR.DT.Mon*30+NHR.HR.DT.Day)>t)break;
	if(NHR.NextAddr==0xffffffff)break;
	else {i++;DeBug("20%02d-%02d-%02d %02d:%02d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f",NHR.HR.DT.Year,NHR.HR.DT.Mon,NHR.HR.DT.Day,NHR.HR.DT.Hour,NHR.HR.DT.Min,NHR.HR.CH_Value[0],NHR.HR.CH_Value[1],NHR.HR.CH_Value[2],NHR.HR.CH_Value[3],NHR.HR.CH_Value[4],NHR.HR.CH_Value[5],0);}
	Tos_TaskDelay(10);
	}
Exit:
	DeBug_Drop();
}
void W25Q16_EraseThis(uint32 Addr,uint32 Length)
{
	uint32 i,n;
	i=Length/SPI_FLASH_PageSize;
	if(Length%SPI_FLASH_PageSize)i++;
	for(n=0;n<i;n++)
	{
		SPI_FLASH_SectorErase(Addr+SPI_FLASH_PageSize*n);
		Tos_TaskDelay(10);
		if(n%36==0)DeBug("����ҳ%d/%d",n/36,i/36,0);
	}
}
void Task_CleanHistory()
{
	DeBug_Get();
	DeBug("��ʼ��ռ�¼\r\n",0);
	W25Q16_EraseThis(0,sizeof(NandHistoryRecord)*0xffff);
	DeBug("������\r\n",0);
	DeBug_Drop();
}
