/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Rtc_driver.h>

DateTime Timer;

uint8 DeviceId_RTC=DeviceNull;

void RTC_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void RTC_Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSEConfig(RCC_LSE_ON);
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{}
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	RTC_WaitForLastTask();
	RTC_SetPrescaler(32767); 
	RTC_WaitForLastTask();
}
void RTC_IRQHandler(void)
{
if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//�����ж�
	{							
	
 	}
	if(RTC_GetITStatus(RTC_IT_ALR)!= RESET)//�����ж�
	{
		RTC_ClearITPendingBit(RTC_IT_ALR);		//�������ж�	  	   
  	} 				  								 
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		//�������ж�
	RTC_WaitForLastTask();	 
}

void Time_Adjust(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  PWR_BackupAccessCmd(ENABLE); 
	RTC_WaitForLastTask();
	RTC_SetCounter(0xffaff);
	RTC_WaitForLastTask();
}


void RTC_Init()
{
	RTC_NVIC_Configuration();
	DeBug( "\r\n This is a RTC demo...... \r\n" ,Infor_Error);
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		DeBug("\r\nThis is a RTC demo!\r\n",Infor_Error);
		DeBug("\r\n\n RTC not yet configured....",Infor_Error);
		RTC_Configuration();
		DeBug("\r\n RTC configured....",Infor_Error);
		Time_Adjust();
		
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}
	else
	{
		if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
		{
			DeBug("\r\n\n Power On Reset occurred....",Infor_Error);
		}
		else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
		{
			DeBug("\r\n\n External Reset occurred....",Infor_Error);
		}
		DeBug("\r\n No need to configure RTC....",Infor_Error);
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		RTC_WaitForLastTask();
	}
	
	#ifdef RTCClockOutput_Enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_TamperPinCmd(DISABLE); 
	BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
	#endif
	
	RCC_ClearFlag();
}

u8 Is_Leap_Year(u16 year)
{                     
       if(year%4==0) //�����ܱ�4����
       { 
             if(year%100==0) 
              { 
                     if(year%400==0)return 1;//�����00��β,��Ҫ�ܱ�400����          
                     else return 0;   
              }else return 1;   

       }else return 0; 
}        
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //���������ݱ�   
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};//ƽ����·����ڱ�
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(syear<2000||syear>2099)return 1;//syear��Χ1970-2099���˴����÷�ΧΪ2000-2099        
	for(t=1970;t<syear;t++) //��������ݵ��������
	{
	if(Is_Leap_Year(t))seccount+=31622400;//�����������
	else seccount+=31536000;                    //ƽ���������
	}
	smon-=1;
	for(t=0;t<smon;t++)         //��ǰ���·ݵ����������
	{
	seccount+=(u32)mon_table[t]*86400;//�·����������
	if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//����2�·�����һ���������         
	}
	seccount+=(u32)(sday-1)*86400;//��ǰ�����ڵ���������� 
	seccount+=(u32)hour*3600;//Сʱ������
	seccount+=(u32)min*60;      //����������
	seccount+=sec;//�������Ӽ���ȥ
	RCC->APB1ENR|=1<<28;//ʹ�ܵ�Դʱ��
	RCC->APB1ENR|=1<<27;//ʹ�ܱ���ʱ��
	PWR->CR|=1<<8;    //ȡ��������д����
	PWR_BackupAccessCmd(ENABLE);
	RTC_WaitForLastTask();
	RTC_SetCounter(seccount);
	RTC_WaitForLastTask();
	return 0;      
}

u8 RTC_Get_Week(u16 year,u8 month,u8 day)

{     
	u16 temp2;
	u8 yearH,yearL;
	yearH=year/100;     yearL=year%100;      // ���Ϊ21����,�������100  
	if (yearH>19)yearL+=100;
	// ����������ֻ��1900��֮���  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}

u8 RTC_Get(void)
{
	 static u16 daycnt=0;
	 u32 timecount=0; 
	 u32 temp=0;
	 u16 temp1=0;
	 timecount=RTC_GetCounter();
	 temp=timecount/86400;   //�õ�����(��������Ӧ��)
	 if(daycnt!=temp)//����һ����
	 {       
					daycnt=temp;
					temp1=1970;  //��1970�꿪ʼ
					while(temp>=365)
					{                          
								 if(Is_Leap_Year(temp1))//������
								 {
												if(temp>=366)temp-=366;//�����������
												else {temp1++;break;}  
								 }
								 else temp-=365;       //ƽ�� 
								 temp1++;  
					}   
					Timer.w_year=temp1;//�õ����
					temp1=0;
					while(temp>=28)//������һ����
					{
								 if(Is_Leap_Year(Timer.w_year)&&temp1==1)//�����ǲ�������/2�·�
								 {
												if(temp>=29)temp-=29;//�����������
												else break; 
								 }
								 else 
								 {
												if(temp>=mon_table[temp1])temp-=mon_table[temp1];//ƽ��
												else break;
								 }
								 temp1++;  
					}
					Timer.w_month=temp1+1;//�õ��·�
					Timer.w_date=temp+1;  //�õ����� 
	 }
	 temp=timecount%86400;     //�õ�������      
	 Timer.hour=temp/3600;     //Сʱ
	 Timer.min=(temp%3600)/60; //����      
	 Timer.sec=(temp%3600)%60; //����
	 Timer.week=RTC_Get_Week(Timer.w_year,Timer.w_month,Timer.w_date);//��ȡ����   
	 return 0;

}     
void Time_Show(void)
{
	RTC_Get();
	DeBug("%d-%d-%d %d:%d:%d",Timer.w_year,Timer.w_month,Timer.w_date,Timer.hour,Timer.min,Timer.sec,Infor_Error);
}
		//Show_Timer(Timer.w_year,Timer.w_month,Timer.w_date,Timer.hour,Timer.min,Timer.sec);
//RTC_Set(2016,03,23,11,40,11);
void DeviceMount_RTC()
{
	DeviceId_RTC=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_RTC].DeviceName="RTC";
	Tos_Device_Tab[DeviceId_RTC].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_RTC].DeviceVirtue=DV_Task;
	Tos_Device_Tab[DeviceId_RTC].DeviceState=Ready;
	Tos_Device_Tab[DeviceId_RTC].Init=RTC_Init;
	Tos_Device_Tab[DeviceId_RTC].Write=Null;//��дͨ�ú����ӿ�
	Tos_Device_Tab[DeviceId_RTC].Read=Null;//��дͨ�ú����ӿ�
	Tos_Device_Tab[DeviceId_RTC].Exit=Null;
}
