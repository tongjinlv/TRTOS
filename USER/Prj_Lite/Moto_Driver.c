/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/

//马达黑线靠虫子头接，且左右马达线对接
uint8 DeviceId_MOTO=DeviceNull;

/*******************************************************************************
Func:A电机驱动
Date:2016-12-29
Note:负数时反转
*******************************************************************************/
void Moto_A(char Speed)
{
	if(Speed<0)
	{
		GPIO_SetIndex(11,1);
		PWM_Set(2,(uint8)(0-Speed));
	}else
	{
		GPIO_SetIndex(11,0);
		PWM_Set(2,(uint8)Speed);
	}
}
/*******************************************************************************
Func:B电机驱动
Date:2016-12-29
Note:负数时反转
*******************************************************************************/
void Moto_B(char Speed)
{
	if(Speed<0)
	{
		GPIO_SetIndex(10,0);
		PWM_Set(1,(uint8)(0-Speed));
	}else
	{
		GPIO_SetIndex(10,1);
		PWM_Set(1,(uint8)Speed);
	}
}
/*******************************************************************************
Func:AB电机驱动
Date:2016-12-29
Note:负数时反转
*******************************************************************************/
void Moto_AB(char SA,char SB)
{
	Moto_A(SA);
	Moto_B(SB);
}
/*******************************************************************************
Func:电机停止
Date:2016-12-29
Note:
*******************************************************************************/
void Moto_Stop()
{
	Moto_AB(0,0);
}
/**************************************************************************************
 Func: 挂载GPIO设备
 Time: 2016-11-03
 Ver.: V1.0
 Note;
**************************************************************************************/
void DeviceMount_Moto()
{
	DeviceId_MOTO=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_MOTO].DeviceId=DeviceId_MOTO;
	Tos_Device_Tab[DeviceId_MOTO].DeviceName="Moto";
	Tos_Device_Tab[DeviceId_MOTO].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_MOTO].DeviceVirtue=DV_Task;
	Tos_Device_Tab[DeviceId_MOTO].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_MOTO].Init=PwmTimeInt;
	Tos_Device_Tab[DeviceId_MOTO].Note=Null;
	Tos_Device_Tab[DeviceId_MOTO].Write=Null;
	Tos_Device_Tab[DeviceId_MOTO].Read=Null;
	Tos_Device_Tab[DeviceId_MOTO].Exit=Null;
}

