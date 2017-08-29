/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <DeBug.h>
//#include <CPU.h>
#include <STM32L_CPU.h>
#include <CheakOut.h>
#include <text.h>
/**************************************************************************************
 Func: ����JTAG������SWD����
 Time: 2015-9-02
 Ver.: V1.0
 Note;
**************************************************************************************/
void Remap_SWJ_JTAGDisable()
{
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
	while(1)
	{	DeBug_Get();
		DeBug("ErrorFile%s->Line%d",file,line,Infor_Infor);
		Tos_TaskDelay(1000);
	}
}
#endif
/**************************************************************************************
 Func: �˿��嵥��ʼ��
 Time: 2015-9-02
 Ver.: V1.0
 Note;
**************************************************************************************/
void GPIO_InitList(const GPIO_ListStruct *List)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	uint32_t RCC_APB2Periph_GPIOx; 
	while(List->GPIOx)
	{
		switch((uintbus)List->GPIOx)
	{
		case (uintbus)GPIOA:RCC_APB2Periph_GPIOx=RCC_AHBPeriph_GPIOA;break;
		case (uintbus)GPIOB:RCC_APB2Periph_GPIOx=RCC_AHBPeriph_GPIOB;break;
		case (uintbus)GPIOC:RCC_APB2Periph_GPIOx=RCC_AHBPeriph_GPIOC;break;
		case (uintbus)GPIOD:RCC_APB2Periph_GPIOx=RCC_AHBPeriph_GPIOD;break;
		case (uintbus)GPIOE:RCC_APB2Periph_GPIOx=RCC_AHBPeriph_GPIOE;break;
		case (uintbus)GPIOF:RCC_APB2Periph_GPIOx=RCC_AHBPeriph_GPIOF;break;
	}
	RCC_AHBPeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx,ENABLE);
	switch(List->GPIO_Mode)
	{
		case GPIO_Mode_Out_PP:
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
			break;
		case GPIO_Mode_IPU:
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
			GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
			GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
			break;
		case GPIO_Mode_Out_OD:
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
			GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
			break;
		case GPIO_Mode_AF_PP:
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
			GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
			break;
	}
	GPIO_InitStructure.GPIO_Pin =List->GPIO_Pin ;
	GPIO_InitStructure.GPIO_Speed=List->GPIO_Speed;
	GPIO_Init(List->GPIOx, &GPIO_InitStructure);
	List++;
	}
}
void SysTick_Set()
{
	SysTick_Config(Tos_Cpu_Freq/1000);
}
void BareDelay(uint32 i)
{
	uint32 m;
	while(i--)
	{
		m=72000000000/Tos_Cpu_Freq;
		while(m--);
	}
}

void Standby_Init(BOOL Stop)
{
//	GPIO_InitTypeDef   GPIO_InitStructure;      
//	NVIC_InitTypeDef NVIC_InitStructure;
//	EXTI_InitTypeDef EXTI_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);//ʹ�� GPIOA �͸��ù���ʱ��
//	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;    //PA.0
//	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;//��������
//	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ�� IO
//	//ʹ���ⲿ�жϷ�ʽ
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); 
//	//�ж��� 0 ���� GPIOA.0
//	EXTI_InitStructure.EXTI_Line = EXTI_Line0;  //���ð������е��ⲿ��·
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    //�����ⲿ�ж�ģ
//	//ʽ:EXTI ��·Ϊ�ж�����
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;   //�����ش���
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);  //  ��ʼ���ⲿ�ж�
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ� 2 ��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //�����ȼ� 2 ��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ�� NVIC
//	Sys_Enter_Standby(Stop);
}
void EXTI0_IRQHandler(void)
{                          
	
	EXTI_ClearITPendingBit(EXTI_Line0); //  ��� LINE10 �ϵ��жϱ�־λ   
	MCU_Reset();	
} 

void Sys_Standby(BOOL Stop)
{  
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);  //ʹ�� PWR ����ʱ��
//	PWR_WakeUpPinCmd(ENABLE);   //ʹ�ܻ��ѹܽŹ���
//	PWR_BackupAccessCmd(ENABLE);
//	if(Stop)PWR_EnterSTANDBYMode();    //���������STANDBY��ģʽ       
//	else PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFE);
}
//ϵͳ�������ģʽ
void Sys_Enter_Standby(BOOL Stop)
{     
	RCC_APB2PeriphResetCmd(0X01FC,DISABLE);  //��λ���� IO ��
	Sys_Standby(Stop);
}
void MCU_Reset(void)
{
	__disable_fault_irq();      // STM32 ��λ  
	NVIC_SystemReset();
}

/*******************************************************************************
Func:��ȡΨһ��ʾ
Date:2014-5-22
Note:
*******************************************************************************/
uint16 GetLockCode()//��ȡΨһ���
{
	uint16 CrcValue;
	CrcValue=Tools_GetCRC16((uint8 *)(__IO uint8 *)(0x1ffff7e8),12);  
	return CrcValue;
}
uint16 Get_CPUID(uint8 *Buf,uint8 Index)
{
	uint32 Temp=*(__IO uint32*)(0x1ffff7e8+Index*4);
	return GetStringFromNumber(Buf,Temp,'H',0);
}
uint32 GetLockCode8(void)
{
	static u32 CpuID[3];
	static u32 Lock_Code;
	CpuID[0]=*(uint32*)(0x1ffff7e8);
	CpuID[1]=*(uint32*)(0x1ffff7ec);
	CpuID[2]=*(uint32*)(0x1ffff7f0);
	Lock_Code=(CpuID[0]>>1)+(CpuID[1]>>2)+(CpuID[2]>>3);
	return Lock_Code;
}
void IAP_Unlock()
{
	FLASH_Unlock();
}
void IAP_ProgramHalfWord(uint32 Address, uint16 Data)
{
	FLASH_FastProgramWord(Address,Data);
}
void IAP_ErasePage(uint32 Page_Address)
{
	FLASH_ErasePage(Page_Address);
}
void IAP_Lock()
{
		FLASH_Lock();
}
uint8 GetCodeStr64(uint8 *Buf)
{
	uint32 CpuID[3];
	uint8 i,c=0;
	CpuID[0]=*(__IO uint32*)(0x1ffff7e8);
	CpuID[2]=*(__IO uint32*)(0x1ffff7ec);
	CpuID[1]=*(__IO uint32*)(0x1ffff7f0);
	for(i=0;i<3;i++)
	{
		while(CpuID[i])
		{
			Buf[c++]=ToHex64(CpuID[i]%62);
			CpuID[i]/=62;
		}
	}
	Buf[c++]=0;
	return c;
}
uint16 Get_FlashSize()
{
	uint16 STM32_FLASH_SIZE;
	STM32_FLASH_SIZE= *(u16*)(0x1FFFF7E0); 
	return STM32_FLASH_SIZE;
}
/*******************************************************************************
Func:��ȡ�������
Date:2014-5-22
Note:
*******************************************************************************/
uint8 GetTosTask_Count()
{
	uint8 i;
	uint8 Count=0;
	for(i=0;i<Tos_TaskTotal;i++)
	{
		if(Tos_TaskTcb[i].Task_ST!=_TTS_Deleted)Count++;
	}
	return Count;
}
/*******************************************************************************
Func:��ӡΨһID
Date:2014-5-22
Note:
*******************************************************************************/
void Printf_LockCode()
{
	uint8 Buf[20];
	GetCodeStr64(Buf);
	DeBug("OnlyID:%s",Buf,Infor_Infor);
}
/*******************************************************************************
Func:��ӡʱ��
Date:2014-5-22
Note:
*******************************************************************************/
void Printf_DateTime(char *Str,Date_Time *DT)
{
	DeBug("%s%d/%d/%d %d:%d:%d",Str,DT->Year,DT->Mon,DT->Day,DT->Hour,DT->Min,DT->Sec,Infor_Infor);
}
/*******************************************************************************
Func:��ӡ����
Date:2014-5-22
Note:
*******************************************************************************/
void Printf_Bytes(uint8 *Bytes,uint8 Length)
{
	uint8 i;
	for(i=0;i<Length;i++)DeBug("Buf[%d]=0x%x",i,Bytes[i],Infor_Infor);
}
/*******************************************************************************
Func:��ӡ������Ϣ
Date:2014-5-22
Note:
*******************************************************************************/
void Printf_TaskInfor()
{

	DeBug("TaskPoolSize:%d but has %d task create.",Tos_TaskTotal,GetTosTask_Count(),Infor_Infor);
}
/*******************************************************************************
Func:��ӡlcd��Ļ��Ϣ
Date:2014-5-22
Note:
*******************************************************************************/
void Printf_LcdType()
{
#ifdef LCD_XSIZE
	if(Device_Ok(DeviceId_LCD))
	{
	DeBug("LcdType:%dx%d",LCD_XSIZE,LCD_YSIZE,Infor_Infor);
	}else DeBug("Not Find LCD",Infor_Infor);
#endif
}
/*******************************************************************************
Func:��ӡϵͳ��Ϣ
Date:2014-5-22
Note:
*******************************************************************************/
void Printf_TosInfor()
{
	uint8 i;
	for(i=0;i<Tos_TaskTotal;i++)
	{
		if(Tos_TaskTcb[i].Task_Name!=Null)DeBug("Task[%d]Name:%s(%d)",i,Tos_TaskTcb[i].Task_Name,Tos_TaskTcb[i].TaskStackSize,Infor_Infor);
	}
	i--;
	DeBug("MemorySize:%d but user:%d",MEMA_BUFFER_SIZE,Mema_Count(),Infor_Infor);
}
/*******************************************************************************
Func:������nandflash ��ӡ��Ϣ
Date:2014-5-22
Note:
*******************************************************************************/
void Printf_NandInfor()
{
	#if defined(Nand_Infor)
	if(Device_Ok(DeviceId_NANDFLASH))
	{
	DeBug("Find NandFlash:",Infor_Infor);
	DeBug("ID:%x\n",Nand_GetID(),Infor_Infor);
	DeBug("TabIn[%d]Block",Nand_Infor.TabInBlock,Infor_Infor);
	DeBug("FileStartIn[%d]Page",Nand_Infor.FileStartPage,Infor_Infor);
	DeBug("TQFS_CanUse:%dPages",Nand_Infor.FT_CanUse,Infor_Infor);
	DeBug("FT_Bad:%dPages",Nand_Infor.FT_Bad,Infor_Infor);
	DeBug("FileCount:%d",Nand_Infor.FT_FileHead,Infor_Infor);
	DeBug("FolderCount:%dPages",Nand_Infor.FT_FolderHead,Infor_Infor);
	DeBug("LinkCount:%dPages",Nand_Infor.FT_LinkHead,Infor_Infor);
	DeBug("FT_Other%dPages",Nand_Infor.FT_Other,Infor_Infor);
	}else DeBug("Not Find NandFlash",Infor_Infor);
	#endif
}
/*******************************************************************************
Func:��ӡ������Ϣ
Date:2014-5-22
Note:
*******************************************************************************/
void Printf_BoardInfor()
{
	DeBug("Board_Name:%s",Board_Name,Infor_Infor);
	DeBug("CPU_Model:%s",CPU_Model,Infor_Infor);
	DeBug("Cpu_OSC_FREQ: %dMhz",OSC_FREQ,Infor_Infor);
	DeBug("Cpu_Freq: %dMhz",Tos_Cpu_Freq,Infor_Infor);
}
/******************************************************************************
 Func:��ӡϵͳ��Ϣ 
 Time: 2014-7-27
 Ver.: V1.0
 Note:
******************************************************************************/
void Printf_SysInfor()
{
	DeBug("\nTos System Start..........",Infor_Infor);
	Printf_BoardInfor();
	Printf_LcdType();
	Printf_LockCode();
	DeviceList_Printf();
	Printf_TaskInfor();
	Printf_NandInfor();
	Printf_TosInfor();
}


void IWDG_Configuration(void)
{
 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); /* д��0x5555,�����������Ĵ���д�빦�� */
 IWDG_SetPrescaler(IWDG_Prescaler_256); /* ����ʱ�ӷ�Ƶ,40K/256=156HZ(6.4ms)*/
 IWDG_SetReload(0xff0);/* ι��ʱ�� 5s/6.4MS=781 .ע�ⲻ�ܴ���0xfff*/
 IWDG_ReloadCounter();/* ι��*/
 IWDG_Enable(); /* ʹ�ܹ���*/
}
void IWDG_Reload()
{
	IWDG_ReloadCounter();//ϵͳ��/ʹ�����߹��ܺ���Ҫ�ر�ϵͳ��
}
