/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <DeBug.h>
#include <CPU.h>
#include <STM32_CPU.h>
#include <CheakOut.h>
#include <text.h>
/**************************************************************************************
 Func: 禁用JTAG仅适用SWD调试
 Time: 2015-9-02
 Ver.: V1.0
 Note;
**************************************************************************************/
void Remap_SWJ_JTAGDisable()
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
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
 Func: 端口清单初始化
 Time: 2015-9-02
 Ver.: V1.0
 Note;
**************************************************************************************/
void GPIO_InitList(const GPIO_InitStruct *List)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	uint32_t RCC_APB2Periph_GPIOx=0; 
	while(List->GPIO_Speed)
	{
		switch((uintbus)List->GPIOx)
	{
		case (uintbus)GPIOA:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOA;break;
		case (uintbus)GPIOB:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOB;break;
		case (uintbus)GPIOC:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOC;break;
		case (uintbus)GPIOD:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOD;break;
		case (uintbus)GPIOE:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOE;break;
		case (uintbus)GPIOF:RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOF;break;
	}
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Speed=(GPIOSpeed_TypeDef)List->GPIO_Speed;
	GPIO_InitStructure.GPIO_Pin=List->GPIO_Pin; 
	GPIO_InitStructure.GPIO_Mode=List->GPIO_Mode;
	GPIO_Init(List->GPIOx, &GPIO_InitStructure);
	List++;
	}
}
void SysTick_Set()
{
#ifdef SYSTEM_TICK
	SysTick_Config(Tos_Cpu_Freq/SYSTEM_TICK);
#else
	SysTick_Config(Tos_Cpu_Freq/1000);
#endif
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
//内部48兆
void SystemHSIInit (void)
{
	
	 RCC_DeInit(); /*将外设RCC寄存器重设为缺省值 */
   RCC_HSICmd(ENABLE);
   while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)== RESET);//等待HSI就绪
   RCC_HCLKConfig(RCC_SYSCLK_Div1);   /*设置AHB时钟（HCLK） RCC_SYSCLK_Div1——AHB时钟 = 系统时*/ 
   RCC_PCLK2Config(RCC_HCLK_Div1);   /* 设置高速AHB时钟（PCLK2)RCC_HCLK_Div1——APB2时钟 = HCLK*/    
   RCC_PCLK1Config(RCC_HCLK_Div2); /*设置低速AHB时钟（PCLK1）RCC_HCLK_Div2——APB1时钟 = HCLK / 2*/     
   FLASH_SetLatency(FLASH_Latency_2);   /*设置FLASH存储器延时时钟周期数FLASH_Latency_2  2延时周期*/  
   FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);  /*选择FLASH预取指缓存的模,预取指缓存使能*/
   RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);/*设置PLL时钟源及倍频系数，频率为8/2*16=64Mhz*/   
   RCC_PLLCmd(ENABLE);   /*使能PLL */
   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; /*检查指定的RCC标志位(PLL准备好标志)设置与否*/   
   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /*设置系统时钟（SYSCLK） */ 
   while(RCC_GetSYSCLKSource() != 0x08);     /*0x08：PLL作为系统时钟 */     
}
void Standby_Init(BOOL Stop)
{
	GPIO_InitTypeDef   GPIO_InitStructure;      
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);//使能 GPIOA 和复用功能时钟
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;    //PA.0
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;//上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化 IO
	//使用外部中断方式
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); 
	//中断线 0 连接 GPIOA.0
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;  //设置按键所有的外部线路
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    //设外外部中断模
	//式:EXTI 线路为中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;   //上升沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);  //  初始化外部中断
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; //使能按键所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级 2 级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //从优先级 2 级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化 NVIC
	Sys_Enter_Standby(Stop);
}
void EXTI0_IRQHandler_(void)
{                          
	
	EXTI_ClearITPendingBit(EXTI_Line0); //  清除 LINE10 上的中断标志位   
	MCU_Reset();	
} 

void Sys_Standby(BOOL Stop)
{  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);  //使能 PWR 外设时钟
	PWR_WakeUpPinCmd(ENABLE);   //使能唤醒管脚功能
	PWR_BackupAccessCmd(ENABLE);
	if(Stop)PWR_EnterSTANDBYMode();    //进入待命（STANDBY）模式       
	else PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFE);
}
//系统进入待机模式
void Sys_Enter_Standby(BOOL Stop)
{     
	RCC_APB2PeriphResetCmd(0X01FC,DISABLE);  //复位所有 IO 口
	Sys_Standby(Stop);
}
void MCU_Reset(void)
{
	__disable_fault_irq();      // STM32 软复位  
	NVIC_SystemReset();
}


/*******************************************************************************
Func:获取唯一标示
Date:2014-5-22
Note:
*******************************************************************************/
uint16 GetLockCode()//获取唯一编号
{
	uint16 CrcValue;
	CrcValue=Tools_GetCRC16((uint8 *)(0x1ffff7e8),12);  
	return CrcValue;
}
uint16 Get_CPUID(uint8 *Buf,uint8 Index)
{
	uint32 Temp=*(vu32*)(0x1ffff7e8+Index*4);
	return GetStringFromNumber(Buf,Temp,'H',0);
}
uint32 GetLockCode8(void)
{
	static u32 CpuID[3];
	static u32 Lock_Code;
	CpuID[0]=*(vu32*)(0x1ffff7e8);
	CpuID[1]=*(vu32*)(0x1ffff7ec);
	CpuID[2]=*(vu32*)(0x1ffff7f0);
	Lock_Code=(CpuID[0]>>1)+(CpuID[1]>>2)+(CpuID[2]>>3);
	return Lock_Code;
}
void IAP_Unlock()
{
	FLASH_Unlock();
}
void IAP_ProgramHalfWord(uint32 Address, uint16 Data)
{
	FLASH_ProgramHalfWord(Address,Data);
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
	CpuID[0]=*(vu32*)(0x1ffff7e8);
	CpuID[2]=*(vu32*)(0x1ffff7ec);
	CpuID[1]=*(vu32*)(0x1ffff7f0);
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
Func:获取任务个数
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
Func:打印唯一ID
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
Func:打印时间
Date:2014-5-22
Note:
*******************************************************************************/
void Printf_DateTime(char *Str,Date_Time *DT)
{
	DeBug("%s%d/%d/%d %d:%d:%d",Str,DT->Year,DT->Mon,DT->Day,DT->Hour,DT->Min,DT->Sec,Infor_Infor);
}
/*******************************************************************************
Func:打印数组
Date:2014-5-22
Note:
*******************************************************************************/
void Printf_Bytes(uint8 *Bytes,uint8 Length)
{
	uint8 i;
	for(i=0;i<Length;i++)DeBug("Buf[%d]=0x%x",i,Bytes[i],Infor_Infor);
}
/*******************************************************************************
Func:打印任务信息
Date:2014-5-22
Note:
*******************************************************************************/
void Printf_TaskInfor()
{

	DeBug("TaskPoolSize:%d but has %d task create.",Tos_TaskTotal,GetTosTask_Count(),Infor_Infor);
}
/*******************************************************************************
Func:打印lcd屏幕信息
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
Func:打印系统信息
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
Func:当挂在nandflash 打印信息
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
Func:打印板子信息
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
 Func:打印系统信息 
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
 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); /* 写入0x5555,用于允许狗狗寄存器写入功能 */
 IWDG_SetPrescaler(IWDG_Prescaler_256); /* 狗狗时钟分频,40K/256=156HZ(6.4ms)*/
 IWDG_SetReload(0xff0);/* 喂狗时间 5s/6.4MS=781 .注意不能大于0xfff*/
 IWDG_ReloadCounter();/* 喂狗*/
 IWDG_Enable(); /* 使能狗狗*/
}
void IWDG_Reload()
{
	IWDG_ReloadCounter();//系统狗/使能休眠功能后需要关闭系统狗
}
