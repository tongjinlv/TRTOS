/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Tools_Include.h>
#include <Usart_Driver.h>
#include <Tos_Mema.h>
uint8 DeviceId_USART_TX[USART_DEF_CH_SIZE];
uint8 DeviceId_USART_RX[USART_DEF_CH_SIZE];
uint8  USART_TX_TaskID[USART_DEF_CH_SIZE];
uint8  USART_RX_TaskID[USART_DEF_CH_SIZE];
uint8  *USART_RX_Buffer[USART_DEF_CH_SIZE];
uint8  *USART_TX_Buffer[USART_DEF_CH_SIZE];
uint16 USART_RX_Count[USART_DEF_CH_SIZE];
uint16 USART_RX_Index[USART_DEF_CH_SIZE];
void USART_GPIO_InitAll(GPIO_TypeDef *GPIOx_TXD,uint16 GPIO_Pin_TXD,GPIO_TypeDef *GPIOx_RXD,uint16 GPIO_Pin_RXD)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_RXD;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOx_RXD, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_TXD;
	GPIO_Init(GPIOx_TXD,&GPIO_InitStructure);
}
USART_TypeDef* USART_GetTypeDef(uint8 Index)
{
	switch(Index)
	{
		case 0:return USART1;
		case 1:return USART2;
		case 2:return USART3;
		case 3:return UART4;
		case 4:return UART5;
		default:return Null;
	}
}
 uint8 USART_GetIndex(USART_TypeDef* USARTx)
{
	switch((uint32)USARTx)
	{
		case (uint32)USART1:return 0;
		case (uint32)USART2:return 1;
		case (uint32)USART3:return 2;
		case (uint32)UART4:return 3;
		case (uint32)UART5:return 4;
		default:return Null;
	}
}
void USART_GPIO_Init(USART_TypeDef* USARTx)
{
	if(USARTx==USART1)
	{
		#ifdef USART1_GPIO_Remap
		USART_GPIO_InitAll(GPIOB,GPIO_Pin_6,GPIOB,GPIO_Pin_7);
		#else
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
		USART_GPIO_InitAll(GPIOA,GPIO_Pin_9,GPIOA,GPIO_Pin_10);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
		#endif
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //ǧ��Ҫע�� ����һʹ�õ���apb2ʱ��
	}
	if(USARTx==USART2)
	{
		#ifdef USART2_GPIO_Remap
		USART_GPIO_InitAll(GPIOD,GPIO_Pin_5,GPIOD,GPIO_Pin_6);
		#else
		USART_GPIO_InitAll(GPIOA,GPIO_Pin_2,GPIOA,GPIO_Pin_3);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
		#endif
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	}
	if(USARTx==USART3)
	{
		#ifdef USART3_GPIO_Remap
		USART_GPIO_InitAll(GPIOB,GPIO_Pin_10,GPIOB,GPIO_Pin_11);
		#else
		USART_GPIO_InitAll(GPIOB,GPIO_Pin_10,GPIOB,GPIO_Pin_11);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
		#endif
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	}
	if(USARTx==UART4)
	{
		USART_GPIO_InitAll(GPIOC,GPIO_Pin_10,GPIOC,GPIO_Pin_11);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	}
	if(USARTx==UART5)
	{
		USART_GPIO_InitAll(GPIOC,GPIO_Pin_12,GPIOD,GPIO_Pin_2);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	}
}
void USART_ConfigurationAll(USART_TypeDef* USARTx,uint32_t USART_BaudRate,uint8_t NVIC_IRQChannel)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//USART_ClearFlag(USARTx, USART_FLAG_TC); /*�巢����ɱ�־��Transmission Complete flag */ 
	USART_InitStructure.USART_BaudRate = USART_BaudRate; 
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USARTx, &USART_InitStructure);
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
	USART_Cmd(USARTx, ENABLE); 
	USART_ClearFlag(USARTx, USART_FLAG_TC);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;               //ͨ������Ϊ�����ж�  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       //�ж�ռ�ȵȼ�0  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              //�ж���Ӧ���ȼ�0  
	//else NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //�ж���Ӧ���ȼ�0  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //���ж�  
	NVIC_Init(&NVIC_InitStructure);    	 

}

void USART_Configuration(uint8 UsartCH)
{
	USART_GPIO_Init(USART_GetTypeDef(UsartCH));//������ʼ���˿�
	switch(UsartCH)
	{
		case 0:
					#ifdef USART1_BaudRate 
					USART_ConfigurationAll(USART1,USART1_BaudRate,USART1_IRQn);
					#else
				  USART_ConfigurationAll(USART1,115200,USART1_IRQn);
					#endif 
					break;
		case 1:
					#ifdef USART2_BaudRate 
					USART_ConfigurationAll(USART2,USART2_BaudRate,USART2_IRQn);
					#else
					USART_ConfigurationAll(USART2,115200,USART2_IRQn);
					#endif 
					break;
		case 2:
					#ifdef USART3_BaudRate 
					USART_ConfigurationAll(USART3,USART3_BaudRate,USART3_IRQn);
					#else
				  USART_ConfigurationAll(USART3,115200,USART3_IRQn);
					#endif 
					break;
		case 3:
					#ifdef USART3_BaudRate 
					USART_ConfigurationAll(USART3,USART3_BaudRate,USART3_IRQn);
					#else
				  USART_ConfigurationAll(USART3,115200,USART3_IRQn);
					#endif 
					break;
		case 4:
					#ifdef USART4_BaudRate 
					USART_ConfigurationAll(UART4,USART4_BaudRate,UART4_IRQn);
					#else
				  USART_ConfigurationAll(UART4,115200,UART4_IRQn);
					#endif 
					break;
		case 5:
					#ifdef USART5_BaudRate 
					USART_ConfigurationAll(UART5,USART5_BaudRate,UART5_IRQn);
					#else
				  USART_ConfigurationAll(UART5,115200,UART5_IRQn);
					#endif 
					break;
	}
	USART_GPIO_Init(USART_GetTypeDef(UsartCH));//������ʼ���˿�
}
void USART1_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
	    c=USART1->DR;	  
		if(USART_RX_Index[0]<USART_RX_Count[0])
		{
			USART_RX_Buffer[0][USART_RX_Index[0]++]=c;
			Tos_TaskTimeout(USART_RX_TaskID[0],10);
		}
	}
}
#ifndef USART2_EXTINIT
void USART2_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{ 	
	    c=USART2->DR;	  	
		if(USART_RX_Index[1]<USART_RX_Count[1])
		{
			USART_RX_Buffer[1][USART_RX_Index[1]++]=c;
			Tos_TaskTimeout(USART_RX_TaskID[1],10);
		}
	}else USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}
#endif
#ifndef USART3_IRQ_EXT
void USART3_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{ 	
	    c=USART3->DR;	  
		if(USART_RX_Index[2]<USART_RX_Count[2])
		{
			USART_RX_Buffer[2][USART_RX_Index[2]++]=c;
			Tos_TaskTimeout(USART_RX_TaskID[2],10);
		}
	}else USART_ClearITPendingBit(USART3,USART_IT_RXNE); 
}
#endif
#if (USART_DEF_CH_SIZE>3)
#ifndef USART4_IRQ_EXT
void UART4_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{ 	
	    c=UART4->DR;	  
		if(USART_RX_Index[3]<USART_RX_Count[3])
		{
			(USART_RX_Buffer[3][USART_RX_Index[3]++])=c;
			Tos_TaskTimeout(USART_RX_TaskID[3],10);
		}
	} 
}
#endif
#endif
#if (USART_DEF_CH_SIZE>4)
void UART5_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{ 	
	    c=UART5->DR;	  
		if(USART_RX_Index[4]<USART_RX_Count[4])
		{
			(USART_RX_Buffer[4][USART_RX_Index[4]++])=c;
			Tos_TaskTimeout(USART_RX_TaskID[4],10);
		}
	} 
}
#endif

void USART_WriteDatas(USART_TypeDef* USARTx,u8* Data,u16 Length)
{
	while(Length--)
	{
		USART_SendData(USARTx,*Data++);
		 while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
	}
}
uint16 USART_WriteLine(USART_TypeDef* USARTx,char *fmt,...)
{
	va_list ap;
	uint16 Length;
  char Buf[200];
  va_start(ap,fmt);
  vsprintf(Buf,fmt,ap);
  va_end(ap);
	Length=GetTextLength(Buf);
	USART_WriteDatas(USARTx,(uint8 *)&Buf[0],Length);
	return Length;
}
uint16 USART_ReadDatas(USART_TypeDef* USARTx,uint8 *Buf,uint16 Length,uint32 TimeOut)
{
	BOOL R;
	uint8 UsartCH;
	uint32 Size;
	UsartCH=USART_GetIndex(USARTx);
	assert_param(IS_USART_ALL_PERIPH(USARTx));
	R=Tos_TaskGetDev(DeviceId_USART_RX[UsartCH],0);
  Size=Mema_GetSize(USART_RX_Buffer[UsartCH]);
  if(R)
	{
		USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);//����ģ���Ҫ�������ݵ�ʱ��Űѽ����жϴ򿪣���Ȼ�˷���Դ��˵��������������
		USART_RX_TaskID[UsartCH]=Tos_TaskCurrent;
		if(Length>=Size)Length=Size;
		USART_RX_Count[UsartCH]=Length;
		USART_RX_Index[UsartCH]=0;
		if(TimeOut)Tos_TaskDelay(TimeOut);
		else Tos_TaskSuspend(USART_RX_TaskID[UsartCH]); 
	  Tos_TaskDropDev(DeviceId_USART_RX[UsartCH]);
		USART_ITConfig(USARTx, USART_IT_RXNE, DISABLE);
	}
	if(Buf!=Null)BufferCoppy(&USART_RX_Buffer[UsartCH][0],&Buf[0],USART_RX_Index[UsartCH]);
	return USART_RX_Index[UsartCH];
}
void USART_Write(void *Addr,void *Data,void *Length)
{
	USART_TypeDef* USARTx=(USART_TypeDef*)Addr;
	uint8 *Buf=(uint8 *)Data;
	uint16  L=*(uint16 *)Length;
	USART_WriteDatas(USARTx,Buf,L);
}
void USART_Read(void *Addr,void *Data,void *Length)
{
	USART_TypeDef* USARTx=(USART_TypeDef*)Addr;
	uint8 *Buf=(uint8 *)Data;
	uint16  *L=(uint16 *)Length;
	uint8 UsartCH=USART_GetIndex(USARTx);
	*L=USART_ReadDatas(USARTx,Buf,Mema_GetSize(USART_RX_Buffer[UsartCH]),0);
}
void DeviceMount_Usart(USART_TypeDef* USARTx)
{
	uint8 UsartCH;
	UsartCH=USART_GetIndex(USARTx);
	if(DeviceId_USART_RX[UsartCH]==DeviceNull)DeviceId_USART_RX[UsartCH]=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].DeviceName="USARRx";
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].DeviceVirtue=DV_Array;//����ע�⣬���豸���ֽ��豸
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].DeviceState=Ready;
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].Init=USART_Configuration;
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].Note=UsartCH;//��ʼ������
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].Write=USART_Write;//��дͨ�ú����ӿ�
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].Read=USART_Read;//��дͨ�ú����ӿ�
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].Exit=Null;
	USART_RX_Count[UsartCH]=0;
	USART_RX_Buffer[UsartCH]=Mema_Malloc(USART_RX_BUFFER_SIZE);
	UsartCH=USART_GetIndex(USARTx);
	if(DeviceId_USART_TX[UsartCH]==DeviceNull)DeviceId_USART_TX[UsartCH]=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].DeviceName="USARTx";
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].DeviceVirtue=DV_Array;//����ע�⣬���豸���ֽ��豸
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].DeviceState=Ready;
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].Init=USART_Configuration;
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].Note=UsartCH;//��ʼ������
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].Write=USART_Write;//��дͨ�ú����ӿ�
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].Read=USART_Read;//��дͨ�ú����ӿ�
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].Exit=Null;
	USART_TX_Buffer[UsartCH]=Mema_Malloc(USART_TX_BUFFER_SIZE);
}
