/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <STM32L_CPU.h>
#include <GPIOL_Driver.h>

uint8 DeviceId_GPIO=DeviceNull;
/**************************************************************************************
 Func: 挂载GPIO设备
 Time: 2016-11-03
 Ver.: V1.0
 Note;
**************************************************************************************/
void DeviceMount_GPIO(const GPIO_ListStruct *List)
{
	DeviceId_GPIO=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_GPIO].DeviceId=DeviceId_GPIO;
	Tos_Device_Tab[DeviceId_GPIO].DeviceName="GPIO";
	Tos_Device_Tab[DeviceId_GPIO].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_GPIO].DeviceVirtue=DV_IOList;
	Tos_Device_Tab[DeviceId_GPIO].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_GPIO].Init=GPIO_InitList;
	Tos_Device_Tab[DeviceId_GPIO].Note=(uintbus)List;
	Tos_Device_Tab[DeviceId_GPIO].Write=Null;
	Tos_Device_Tab[DeviceId_GPIO].Read=Null;
	Tos_Device_Tab[DeviceId_GPIO].Exit=Null;
}
/**************************************************************************************
 Func: 设置GPIO电平
 Time: 2016-11-03
 Ver.: V1.0
 Note;按照map
**************************************************************************************/
void GPIO_Set(const GPIO_ListStruct List,uint8 H)
{
	if(H)GPIO_SetBits(List.GPIOx,List.GPIO_Pin);
	else GPIO_ResetBits(List.GPIOx,List.GPIO_Pin);
}
/**************************************************************************************
 Func: 设置GPIO电平
 Time: 2016-11-03
 Ver.: V1.0
 Note;按照索引
**************************************************************************************/
void GPIO_SetIndex(uint8 i,uint8 H)
{
	const GPIO_ListStruct *List;
	List=(const GPIO_ListStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
	GPIO_Set(List[i],H);
}
/**************************************************************************************
 Func: 获取GPIO状态
 Time: 2016-11-03
 Ver.: V1.0
 Note;重排
**************************************************************************************/
void GPIO_SetAll(uint32 D)
{
	uint8 i;
	const GPIO_ListStruct *List;
	List=(const GPIO_ListStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
	for(i=0;i<0xff;i++)
	{
		if(!List[i].GPIO_Speed)break;
		GPIO_Set(List[i],(BOOL)(D&0x01));
		D>>=1;
	}
}
/**************************************************************************************
 Func: 获取GPIO状态
 Time: 2016-11-03
 Ver.: V1.0
 Note;单个
**************************************************************************************/
BOOL GPIO_Get(const GPIO_ListStruct List)
{
	if(GPIO_ReadInputDataBit(List.GPIOx,List.GPIO_Pin))return True;
	return False;
}
/**************************************************************************************
 Func: 获取GPIO状态
 Time: 2016-11-03
 Ver.: V1.0
 Note;重排
**************************************************************************************/
uint32 GPIO_GetAll()
{
	uint8 i;
	uint32 D=0;
	const GPIO_ListStruct *List;
	List=(const GPIO_ListStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
	for(i=0;i<0xff;i++)
	{
		if(!List[i].GPIO_Speed)break;
		if(GPIO_ReadInputDataBit(List[i].GPIOx,List[i].GPIO_Pin))D|=BIT(i);
		else D&=~BIT(i);
	}
	return D;
}
/**************************************************************************************
 Func: 获取
 Time: 2016-11-03
 Ver.: V1.0
 Note;按照索引
**************************************************************************************/
BOOL GPIO_GetIndex(uint8 i)
{
	const GPIO_ListStruct *List;
	List=(const GPIO_ListStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
	if(GPIO_ReadInputDataBit(List[i].GPIOx,List[i].GPIO_Pin))return True;
	return False;
}
/**************************************************************************************
 Func: 设置端口模式
 Time: 2016-11-03
 Ver.: V1.0
 Note;
	GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
**************************************************************************************/
void GPIO_Set_Mode(const GPIO_ListStruct Pin_Map,GPIOMode_TypeDef Mode)
{     
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Pin_Map.GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = Mode ;            
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(Pin_Map.GPIOx, &GPIO_InitStructure);
}
//void GPIO_ExitInit(const GPIO_InitStruct Pin_Map,FunctionalState En)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;  
//	GPIO_InitTypeDef GPIO_InitStructure;
//	EXTI_InitTypeDef EXTI_InitStructure;

//	GPIO_InitStructure.GPIO_Pin =Pin_Map.GPIO_Pin;                                                                           
//  GPIO_InitStructure.GPIO_Mode =  Pin_Map.GPIO_Mode;   
//  GPIO_Init(Pin_Map.GPIOx, &GPIO_InitStructure);

//  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource9);
//  EXTI_InitStructure.EXTI_Line = Pin_Map.GPIO_Pin;                                       
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                          
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;                 
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);

//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//  NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn;                                  
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                       
//  NVIC_InitStructure.NVIC_IRQChannelCmd = En;                               
//  NVIC_Init(&NVIC_InitStructure);
//}
