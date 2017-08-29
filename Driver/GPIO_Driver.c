/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <GPIO_Driver.h>
uint8 DeviceId_GPIO=DeviceNull;
uint8 SelectPin=5;
/**************************************************************************************
 Func: ����GPIO�豸
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
 Func: ����GPIO��ƽ
 Time: 2016-11-03
 Ver.: V1.0
 Note;����map
**************************************************************************************/
void GPIO_Set(const GPIO_InitStruct List,uint8 H)
{
	if(H)GPIO_SetBits(List.GPIOx,List.GPIO_Pin);
	else GPIO_ResetBits(List.GPIOx,List.GPIO_Pin);
}
/**************************************************************************************
 Func: ����GPIO��ƽ
 Time: 2016-11-03
 Ver.: V1.0
 Note;��������
**************************************************************************************/
void GPIO_SetIndex(uint8 i,uint8 H)
{
	const GPIO_InitStruct *List;
	List=(const GPIO_InitStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
	GPIO_Set(List[i],H);
}
/**************************************************************************************
 Func: ��ȡGPIO״̬
 Time: 2016-11-03
 Ver.: V1.0
 Note;����
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
 Func: ��ȡGPIO״̬
 Time: 2016-11-03
 Ver.: V1.0
 Note;����
**************************************************************************************/
BOOL GPIO_Get(const GPIO_InitStruct List)
{
	if(GPIO_ReadInputDataBit(List.GPIOx,List.GPIO_Pin))return True;
	return False;
}
/**************************************************************************************
 Func: ��ȡGPIO״̬
 Time: 2016-11-03
 Ver.: V1.0
 Note;����
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
 Func: ��ȡ
 Time: 2016-11-03
 Ver.: V1.0
 Note;��������
**************************************************************************************/
BOOL GPIO_GetIndex(uint8 i)
{
	const GPIO_InitStruct *List;
	List=(const GPIO_InitStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
	if(GPIO_ReadInputDataBit(List[i].GPIOx,List[i].GPIO_Pin))return True;
	return False;
}
/**************************************************************************************
 Func: ���ö˿�ģʽ
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
 Func: TIM1��ʼ����i=0ʱ��ֹ
 Time: 2017-02-02
 Ver.: V1.0
 Note;
**************************************************************************************/
//void TIM1_Config(uint16 i)
//{
// TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
// NVIC_InitTypeDef         NVIC_InitStructure;
// /*ʹ��TIM2ʱ��*/
// RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);            //ѡ����1
// NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;            //TIM2�ж�
// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //�����ȼ�3��
// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQͨ����ʹ��
// NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

// /*�Զ���װ��ֵ5000*/
// TIM_TimeBaseStructure.TIM_Period = i;
// /*Ԥ��Ƶֵ��+1Ϊ��Ƶϵ��*/
// TIM_TimeBaseStructure.TIM_Prescaler =(20-1); 
// TIM_TimeBaseStructure.TIM_ClockDivision = 0;
// /*TIM���ϼ���ģʽ*/
// TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
// /*����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ*/ 
// TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
// TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
// /*ʹ��TIMx����*/
// if(i)TIM_Cmd(TIM1, ENABLE); 
// else TIM_Cmd(TIM1, DISABLE);     
//}
//void TIM1_UP_IRQHandler(void)
//{
//	const GPIO_InitStruct *List;
//	List=(const GPIO_InitStruct *)(Tos_Device_Tab[DeviceId_GPIO].Note);
// if ( TIM_GetITStatus(TIM1 , TIM_IT_Update) != RESET ) //�Ƿ����ж�
// { 
//		TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);    //����жϴ�����λ
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
