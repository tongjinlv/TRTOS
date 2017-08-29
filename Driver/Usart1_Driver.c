/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <STM32LIB_Include.h>
#include <Tools_Include.h>
#include <Usart1_Driver.h>
uint8 DeviceId_USART1=DeviceNull;
uint8 DeviceId_USART1_RX=DeviceNull;
uint8  USART1_TX_TaskID=Tos_TaskTotal;
uint8  USART1_RX_TaskID=Tos_TaskTotal;
uint8  USART1_RX_Buffer[USART_RX_BUFFER_SIZE];
uint8  USART1_TX_Buffer[USART_TX_BUFFER_SIZE];
uint16 USART1_RX_Count=Null;
uint16 USART1_RX_Index;

/******************************************************************************
 Func: ����1�Ķ˿�����
 Time: 2014-7-23
 Ver.: V1.0
 Note:
******************************************************************************/
void USART1_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
#ifdef USART1_GPIO_Remap
	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);//ʹ�ܶ˿���ӳ�� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//USART1_RX���� 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	//USART1_��������
#else
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//USART1_RX���� 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	//USART1_��������
#endif
}
void USART1_Struct_Init(uint32 Baud)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = Baud; 
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
}
void USART1_RX_Enable(FunctionalState En)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               //ͨ������Ϊ����1�ж�  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;       //�ж�ռ�ȵȼ�0  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              //�ж���Ӧ���ȼ�0  
	NVIC_InitStructure.NVIC_IRQChannelCmd = En;                 //���ж�  
	NVIC_Init(&NVIC_InitStructure);   
}
/**************************************************************************************
 Func: ��ʼ��Tos
 Time: 2014-1-31
 Ver.: V1.0
 Note; ���ڳ�ʼ��ϵͳ����
**************************************************************************************/
void USART1_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	USART1_GPIO_Init();
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);  
#ifdef USART1_BaudRate
	USART_InitStructure.USART_BaudRate = USART1_BaudRate; 
#else 
	USART_InitStructure.USART_BaudRate = 115200; 
#endif
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE); 
	//����UART1�ж�    
	USART1_RX_Enable(ENABLE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
}

/**************************************************************************************
 Func: ���������ж�
 Time: 2014-6-12
 Ver.: V1.0
 Note;
**************************************************************************************/
void USART1_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
	    c=USART1->DR;	  
		if(USART1_RX_Index<USART1_RX_Count)
		{
			(USART1_RX_Buffer[USART1_RX_Index++])=c;
			Tos_TaskTimeout(USART1_RX_TaskID,10);
		}
	} 
}
/**************************************************************************************
 Func: ʹ��DMA��ʽ��������
 Time: 2014-6-12
 Ver.: V1.0
 Note;
**************************************************************************************/
void USART1_DMAConfiguration()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	USART1_Configuration();
	  
	//����DMAʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	//DMA�����ж�����
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
//DMA1ͨ��4����
	DMA_DeInit(DMA1_Channel4);
	//�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
	//�ڴ��ַ
	DMA_InitStructure.DMA_MemoryBaseAddr =(uint32)USART1_TX_Buffer;//��ַδ��������������
	//dma���䷽����
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	//����DMA�ڴ���ʱ�������ĳ���
	DMA_InitStructure.DMA_BufferSize =sizeof(USART1_TX_Buffer);//����δ�趨����������
	//����DMA���������ģʽ��һ������
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//����DMA���ڴ����ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//���������ֳ�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	//�ڴ������ֳ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	//����DMA�Ĵ���ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	//����DMA�����ȼ���
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	//����DMA��2��memory�еı����������
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4,&DMA_InitStructure);
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
}
/**************************************************************************************
 Func: DMA�����ж�
 Time: 2014-6-12
 Ver.: V1.0
 Note;
**************************************************************************************/
void DMA1_Channel4_IRQHandler(void)//����1DMA�����жϺ���  
{  
    DMA_ClearFlag(DMA1_FLAG_TC4);  
	if(Tos_TaskGetState(USART1_TX_TaskID)==_TTS_DelayWait)return;
	if(Tos_TaskGetState(USART1_TX_TaskID)==_TTS_Suspend)Tos_TaskRecover(USART1_TX_TaskID);
	else Tos_TaskTimeout(USART1_TX_TaskID,10);//��ֹ������û�й���ͷ���dma�����ж���
}  

void USART1_WriteDatas(u8* Data,u16 Length)
{
 	 u16 i;
 	 for (i=0; i<Length; i++){
 	USART1_SendByte(Data[i]);
 	}
}


void Usart1_Write(void *Addr,void *Data,void *Length)
{
	USART1_TX_TaskID=Tos_TaskCurrent;
	DMA1_Channel4->CMAR=(uint32)Data;	
	DMA1_Channel4->CNDTR=(uint32)Length;
	DMA_Cmd(DMA1_Channel4, ENABLE);
	Tos_TaskStop(USART1_TX_TaskID); 
	DMA_Cmd(DMA1_Channel4,DISABLE);
}

void DeviceMount_Usart1()
{
	DeviceMount_Usart(USART1);
}
void USART1_DMAWriteDatas(u8* Data,u16 Length)
{
	BOOL R;
	R=Tos_TaskGetDev(DeviceId_USART1,0);
  if(R)
	{
		USART1_TX_TaskID=Tos_TaskCurrent;
		DMA1_Channel4->CMAR=(uint32)Data;	
		DMA1_Channel4->CNDTR=(uint32)Length;
		DMA_Cmd(DMA1_Channel4, ENABLE);
		Tos_TaskStop(USART1_TX_TaskID); 
		DMA_Cmd(DMA1_Channel4,DISABLE);
	  Tos_TaskDropDev(DeviceId_USART1);
	}
	
}	
uint16 USART1_ReadDatas(uint8 *Buf,uint16 Length,uint32 TimeOut)
{
	BOOL R;
	R=Tos_TaskGetDev(DeviceId_USART1_RX,0);
	USART1_RX_Enable(ENABLE);
  if(R)
	{
		USART1_RX_TaskID=Tos_TaskCurrent;
		USART1_RX_Count=Length;
		USART1_RX_Index=0;
		if(TimeOut)Tos_TaskDelay(TimeOut);
		else Tos_TaskSuspend(USART1_RX_TaskID); 
	  Tos_TaskDropDev(DeviceId_USART1_RX);
		USART1_RX_Enable(DISABLE);
	}
	
	return USART1_RX_Index;
}

/**************************************************************************************
 Func: ���ڷ��͵�������
 Time: 2014-6-12
 Ver.: V1.0
 Note;
**************************************************************************************/
void USART1_SendByte(u16 Data)
{ 
   while (!(USART1->SR & USART_FLAG_TXE));
   USART1->DR = (Data & (uint16_t)0x01FF);	 
}
/**************************************************************************************
 Func: ���ڷ����ַ���
 Time: 2014-6-12
 Ver.: V1.0
 Note;
**************************************************************************************/
void USART1_Printf(u8 *Data)
{
	USART1_WriteDatas(Data,GetTextLength(Data));
}
/**************************************************************************************
 Func: ����������������
 Time: 2014-6-12
 Ver.: V1.0
 Note;
**************************************************************************************/
u16 USART1_ReciveByte()
{
   while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
   return (USART_ReceiveData(USART1)); 
}

