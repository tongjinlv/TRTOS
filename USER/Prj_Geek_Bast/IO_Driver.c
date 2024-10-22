/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <..\USER\Prj_Geek_Bast\IO_Driver.h>
#include <STM32_CPU.h>
uint8 DeviceId_IO=DeviceNull;


void DeviceMount_IO(const GPIO_InitStruct *List)
{
	DeviceId_IO=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_IO].DeviceId=DeviceId_IO;
	Tos_Device_Tab[DeviceId_IO].DeviceName="IO";
	Tos_Device_Tab[DeviceId_IO].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_IO].DeviceVirtue=DV_IOList;
	Tos_Device_Tab[DeviceId_IO].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_IO].Init=GPIO_InitList;
	Tos_Device_Tab[DeviceId_IO].Note=(uintbus)List;
	Tos_Device_Tab[DeviceId_IO].Write=Null;
	Tos_Device_Tab[DeviceId_IO].Read=Null;
	Tos_Device_Tab[DeviceId_IO].Exit=Null;
}
