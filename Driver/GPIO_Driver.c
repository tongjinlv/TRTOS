/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <GPIO_Driver.h>
uint8 DeviceId_GPIO=DeviceNull;
uint8 SelectPin=5;
/**************************************************************************************
 Func: 挂载GPIO设备
 Time: 2016-11-03
 Ver.: V1.0
 Note;
**************************************************************************************/
void DeviceMount_GPIO(const GPIO_InitStruct *List)
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
void GPIO_Set(const GPIO_InitStruct List,uint8 H)
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
	const GPIO_InitStruct *List;
	List=(const GPIO_InitStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
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
	const GPIO_InitStruct *List;
	List=(const GPIO_InitStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
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
BOOL GPIO_Get(const GPIO_InitStruct List)
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
	const GPIO_InitStruct *List;
	List=(const GPIO_InitStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
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
	const GPIO_InitStruct *List;
	List=(const GPIO_InitStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
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
void GPIO_Set_Mode(const GPIO_InitStruct Pin_Map,GPIOMode_TypeDef Mode)
{     
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Pin_Map.GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = Mode ;            
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(Pin_Map.GPIOx, &GPIO_InitStructure);
}
void GPIO_SetMode(uint8 i,GPIOMode_TypeDef Mode)
{     
	
	GPIO_InitTypeDef GPIO_InitStructure;
	const GPIO_InitStruct *List;
	List=(const GPIO_InitStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
	GPIO_InitStructure.GPIO_Pin = List[i].GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = Mode ;            
	GPIO_InitStructure.GPIO_Speed =(GPIOSpeed_TypeDef)List[i].GPIO_Speed;
	GPIO_Init(List[i].GPIOx, &GPIO_InitStructure);
}
/**************************************************************************************
 Func: TIM1初始化，i=0时禁止
 Time: 2017-02-02
 Ver.: V1.0
 Note;
**************************************************************************************/
//void TIM1_Config(uint16 i)
//{
// TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
// NVIC_InitTypeDef         NVIC_InitStructure;
// /*使能TIM2时钟*/
// RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);            //选择组1
// NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;            //TIM2中断
// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //从优先级3级
// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道被使能
// NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

// /*自动重装载值5000*/
// TIM_TimeBaseStructure.TIM_Period = i;
// /*预分频值，+1为分频系数*/
// TIM_TimeBaseStructure.TIM_Prescaler =(20-1); 
// TIM_TimeBaseStructure.TIM_ClockDivision = 0;
// /*TIM向上计数模式*/
// TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
// /*根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位*/ 
// TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
// TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
// /*使能TIMx外设*/
// if(i)TIM_Cmd(TIM1, ENABLE); 
// else TIM_Cmd(TIM1, DISABLE);     
//}
//void TIM1_UP_IRQHandler(void)
//{
//	const GPIO_InitStruct *List;
//	List=(const GPIO_InitStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
// if ( TIM_GetITStatus(TIM1 , TIM_IT_Update) != RESET ) //是否发生中断
// { 
//		TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);    //清除中断待处理位
//    GPIO_WriteBit(List[SelectPin].GPIOx, List[SelectPin].GPIO_Pin, (BitAction)!GPIO_ReadOutputDataBit(List[SelectPin].GPIOx, List[SelectPin].GPIO_Pin));
//	 //GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)!GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13));
// }    
//}
//void TIM1_SetPin(uint8 i,uint16 t)
//{
//	TIM1_Config(t);
//	SelectPin=i;
//}
void GPIO_ExitInit(const GPIO_InitStruct Pin_Map,FunctionalState En)
{
	NVIC_InitTypeDef NVIC_InitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	GPIO_InitStructure.GPIO_Pin =Pin_Map.GPIO_Pin;                                                                           
  GPIO_InitStructure.GPIO_Mode =  Pin_Map.GPIO_Mode;   
  GPIO_Init(Pin_Map.GPIOx, &GPIO_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource9);
  EXTI_InitStructure.EXTI_Line = Pin_Map.GPIO_Pin;                                       
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                          
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;                 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn;                                  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                       
  NVIC_InitStructure.NVIC_IRQChannelCmd = En;                               
  NVIC_Init(&NVIC_InitStructure);
}
