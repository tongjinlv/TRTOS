/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <GPIO_Driver.h>
#include <STM32_CPU.h>
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
void Uart2_DeBug(void *Str,uint8 Length)
{
	USART_WriteDatas(USART2,Str,Length);
}

void Task0_MiniDTUInit()
{
 if(!BOOL_LoadConfigs())UIShowValue.SaveValue.DeBugCFG=0xff;
	DeBug_OutSet(0);
	DeBug_SetType(0xff);
	DeBug_SetCallBack(Uart2_DeBug);
}


/*

LCD_BUF[0]|=S0;关
LCD_BUF[0]|=S1;低
LCD_BUF[0]|=S2;中
LCD_BUF[0]|=S3;高
LCD_BUF[0]|=S4;风扇左下叶
LCD_BUF[0]|=S5;风扇左上叶
LCD_BUF[0]|=S6;风扇上叶
LCD_BUF[0]|=S7;圈A

LCD_BUF[1]|=S0;风扇下叶
LCD_BUF[1]|=S1;风扇右下叶
LCD_BUF[1]|=S2;风扇中心
LCD_BUF[1]|=S3;风扇右上叶
LCD_BUF[1]|=S7;左分隔

LCD_BUF[1-7]|=S4;8左下
LCD_BUF[1-7]|=S5;8心
LCD_BUF[1-7]|=S5;8左上

LCD_BUF[2]|=S7;倒计时
LCD_BUF[3]|=S7;时钟两点
LCD_BUF[4]|=S7;15分钟后启动关机
LCD_BUF[5]|=S7;分钟两点
LCD_BUF[6]|=S7;右分隔
LCD_BUF[7]|=S7;级
LCD_BUF[8]|=S6;异常报警
LCD_BUF[8]|=S5;净化器开启
LCD_BUF[8]|=S4;照明等级
LCD_BUF[9]|=S7;ug/m3
LCD_BUF[10]|=S7;中横线
LCD_BUF[11]|=S7;PM2.5
LCD_BUF[12]|=S7;API

LCD_BUF[13]|=S0;需要清洁
LCD_BUF[13]|=S1|S2|S3|S4|S5|S6|S7;需要保养

LCD_BUF[14]|=S1;保养周期
LCD_BUF[14]|=S2;一级
LCD_BUF[14]|=S0;Logo


*/


void Setblower(uint8 i)
{
	static uint8 c;
	switch(c)
	{
		case 0:LCD_BUF[0]|=S6;LCD_BUF[1]|=S0;c++;break;
		case 1:LCD_BUF[0]|=S4;LCD_BUF[1]|=S3;c++;break;
		case 2:LCD_BUF[0]|=S5;LCD_BUF[1]|=S1;c=0;break;
		default:c=0;break;
	}
	switch(c)
	{
		case 0:LCD_BUF[0]|=S5;LCD_BUF[1]|=S3;LCD_BUF[1]|=S0;;c++;break;
		case 1:LCD_BUF[0]|=S6;LCD_BUF[0]|=S4;LCD_BUF[1]|=S1;c=0;break;
		default:c=0;break;
	}
	
}
void Task1_Uart4LCD(void *Tags)
{
	uint16 Length;
	USART_TypeDef *USARTx=(USART_TypeDef *)Tags;
	uint8 UsartCH=USART_GetIndex(USARTx);
	while(1)
	{
		ClearWithBuffer(USART_RX_Buffer[UsartCH],50);
		Length=USART_ReadDatas(USARTx,Null,50,1000);
		if(Length)
		{
			//BufferCoppy(&USART_RX_Buffer[UsartCH][0],LCD_BUF,Length);
			
			UIShowValue.SaveValue.BlowerNum=USART_RX_Buffer[UsartCH][0];
		USART_WriteDatas(USARTx,USART_RX_Buffer[UsartCH],Length);
		}
	}
}
void SetBlow(uint8 I)
{
	switch(I)
	{
		case 0:GPIO_SetIndex(8,0);GPIO_SetIndex(9,0);GPIO_SetIndex(10,0);break;
		case 1:GPIO_SetIndex(8,0);GPIO_SetIndex(9,0);GPIO_SetIndex(10,1);break;
		case 2:GPIO_SetIndex(8,1);GPIO_SetIndex(9,0);GPIO_SetIndex(10,0);break;
		case 3:GPIO_SetIndex(8,0);GPIO_SetIndex(9,1);GPIO_SetIndex(10,0);break;
	}
	
	
}

/*http://api.tlink.io/tlink_interface/api/device/sendSwitchValue.htm
{"deviceNo":"AM84P32Z3SM60DS2","sensorId":"200037704","value":"55"}
*/
void TaskRead(void *Tags)
{
	uint16 Length;
	uint8 Buf[20];
	USART_TypeDef *USARTx=(USART_TypeDef *)Tags;
	uint8 UsartCH=USART_GetIndex(USARTx);
	while(1)
	{
		
		ClearWithBuffer(USART_RX_Buffer[UsartCH],100);
		Length=USART_ReadDatas(USARTx,Null,100,100);
		if(Length)
		{
			DeBug((char *)USART_RX_Buffer[UsartCH],5);
			USART_RX_Buffer[UsartCH][Length]=0;
			if(Strstr((const char *)USART_RX_Buffer[UsartCH],"switch"))
			{
				FindNumFromString(USART_RX_Buffer[UsartCH],&Buf[0],1);
				Length=GetStringToNumber(Buf);
				UIShowValue.LostSetTime=Length;
				UIShowValue.DateTime.Hour=Length/60;
				UIShowValue.DateTime.Min=Length%60;
				DeBug("SetTime Hour=%d Min=%d",UIShowValue.DateTime.Hour,UIShowValue.DateTime.Min,5);
				UIShowValue.SysWorkMode|=WCB_Open;
				Beep(2);
			}
			if(Strstr((const char *)USART_RX_Buffer[UsartCH],"connect ok"))UIShowValue.GPRSFailCount=0;
		}
	}
}

void TaskWrite(void *Tags)
{
	uint8 Buf[30],Length;
	USART_TypeDef *USARTx=(USART_TypeDef *)Tags;
	uint8 UsartCH=USART_GetIndex(USARTx);
	while(1)
	{
		Length=GetStringByFmt((char *)&Buf[0],"#%d,%d,%d,%d#",UIShowValue.LostSetTime,UIShowValue.SysWorkMode&WCB_Start,UIShowValue.PM25_Value,UIShowValue.DateTime.Hour*60+UIShowValue.DateTime.Min);
		USART_WriteDatas(USARTx,&Buf[0],Length);
		Tos_TaskDelay(10000);
	//	USART_WriteDatas(USARTx,"RESET         ",Length);
	}
}
void Task_Plan(void *Tags)
{
	uint8 c=0;
	while(1)
	{
			Tos_TaskDelay(2000);
			if(UIShowValue.SysWorkMode&WCB_Open)
			{
				if(UIShowValue.SysWorkMode&WCB_Start)GPIO_SetIndex(1,0);
				if(UIShowValue.SaveValue.BlowerNum==4)
				{
					if(UIShowValue.PM25_Value>1000)SetBlow(3);
					else if(UIShowValue.PM25_Value>100)SetBlow(2);
					else if(UIShowValue.PM25_Value>0)SetBlow(1);
					if(UIShowValue.PM25_Value>1000)UIShowValue.ShowFlag|=WSB_OpenAirCleaner;else UIShowValue.ShowFlag&=~WSB_OpenAirCleaner;
				}else 
				{
					SetBlow(UIShowValue.SaveValue.BlowerNum);
					if(UIShowValue.SaveValue.BlowerNum)UIShowValue.ShowFlag|=WSB_OpenAirCleaner;
					else UIShowValue.ShowFlag&=~WSB_OpenAirCleaner;
				}
				GPIO_SetIndex(6,0);
			}else
			{
				GPIO_SetIndex(1,1);
				SetBlow(0);
				GPIO_SetIndex(3,1);
				GPIO_SetIndex(6,1);
			}
			if(UIShowValue.ShowFlag&WSB_OpenAirCleaner)GPIO_SetIndex(7,1);else GPIO_SetIndex(7,0);
			if(c++>100)
			{
				if(UIShowValue.GPRSFailCount++>100)
				{
					USART_WriteDatas(USART3,"RESET  ",6);
					UIShowValue.GPRSFailCount=0;
				}
				if(UIShowValue.GPRSFailCount>10)DeBug("GPRS Fail Count=%d",UIShowValue.GPRSFailCount,5);
				c=0;
			}
	}
}
