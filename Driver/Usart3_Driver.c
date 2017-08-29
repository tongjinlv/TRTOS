/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <STM32LIB_Include.h>
#include <Tools_Include.h>
#include <Usart3_Driver.h>
uint8 DeviceId_USART3=DeviceNull;
uint8 DeviceId_USART3_RX=DeviceNull;
uint8  USART3_TX_TaskID=Tos_TaskTotal;
uint8  USART3_RX_TaskID=Tos_TaskTotal;
uint8  USART3_RX_Buffer[USART_RX_BUFFER_SIZE];
uint8  USART3_TX_Buffer[USART_TX_BUFFER_SIZE];
uint16 USART3_RX_Count=Null;
uint16 USART3_RX_Index;

/******************************************************************************
 Func: ����1�Ķ˿�����
 Time: 2014-7-23
 Ver.: V1.0
 Note:
******************************************************************************/
void USART3_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);   
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //����ʱ������ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//USART1_RX���� 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	//USART1_��������
}

void USART3_Struct_Init(uint32 Baud)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = Baud; 
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
}
void USART3_RX_Enable(FunctionalState En)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;               //ͨ������Ϊ����1�ж�  
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
void USART3_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	USART3_GPIO_Init();
 RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);  
#ifdef USART3_BaudRate
	USART_InitStructure.USART_BaudRate = USART3_BaudRate; 
#else 
	USART_InitStructure.USART_BaudRate = 115200; 
#endif
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE); 
	//����UART1�ж�    
	USART3_RX_Enable(ENABLE);
}

/**************************************************************************************
 Func: ���������ж�
 Time: 2014-6-12
 Ver.: V1.0
 Note;
**************************************************************************************/
void USART3_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{ 	
	    c=USART3->DR;	  
		if(USART3_RX_Index<USART3_RX_Count)
		{
			(USART3_RX_Buffer[USART3_RX_Index++])=c;
			Tos_TaskTimeout(USART3_RX_TaskID,10);
		}
	} 
}
/**************************************************************************************
 Func: ���ڷ��͵�������
 Time: 2014-6-12
 Ver.: V1.0
 Note;
**************************************************************************************/
void USART3_SendByte(u16 Data)
{ 
  while((USART3->SR & USART_FLAG_TXE) == 0);
   USART3->DR = (Data & (uint16_t)0x01FF);	 
}
/**************************************************************************************
 Func: DMA�����ж�
 Time: 2014-6-12
 Ver.: V1.0
 Note;
**************************************************************************************/
void DMA1_Channel6_IRQHandler(void)//����1DMA�����жϺ���  
{  
    DMA_ClearFlag(DMA1_FLAG_TC4);  
	if(Tos_TaskGetState(USART3_TX_TaskID)==_TTS_Suspend)return;
	if(Tos_TaskGetState(USART3_TX_TaskID)==_TTS_Stop)Tos_TaskRecover(USART3_TX_TaskID);
	else Tos_TaskTimeout(USART3_TX_TaskID,10);//��ֹ������û�й���ͷ���dma�����ж���
}  
/**************************************************************************************
 Func: ʹ��DMA��ʽ��������
 Time: 2014-6-12
 Ver.: V1.0
 Note;
**************************************************************************************/
void USART3_DMAConfiguration()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	USART3_Configuration();
	  
	//����DMAʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	//DMA�����ж�����
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
//DMA1ͨ��4����
	DMA_DeInit(DMA1_Channel6);
	//�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART3->DR);
	//�ڴ��ַ
	DMA_InitStructure.DMA_MemoryBaseAddr =(uint32)USART3_TX_Buffer;//��ַδ��������������
	//dma���䷽����
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	//����DMA�ڴ���ʱ�������ĳ���
	DMA_InitStructure.DMA_BufferSize =sizeof(USART3_TX_Buffer);//����δ�趨����������
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
	DMA_Init(DMA1_Channel6,&DMA_InitStructure);
	DMA_ITConfig(DMA1_Channel6,DMA_IT_TC,ENABLE);
	USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
}
void USART3_WriteDatas(u8* Data,u16 Length)
{
 	 u16 i;
 	 for (i=0; i<Length; i++){
 	USART3_SendByte(Data[i]);
 	}
}
void USART3_DMAWriteDatas(u8* Data,u16 Length)
{
	BOOL R;
	
	R=Tos_TaskGetDev(DeviceId_USART3,0);
  if(R)
	{
		USART3_TX_TaskID=Tos_TaskCurrent;
		DMA1_Channel6->CMAR=(uint32)Data;	
		DMA1_Channel6->CNDTR=(uint32)Length;
		DMA_Cmd(DMA1_Channel6, ENABLE);
		Tos_TaskStop(USART3_TX_TaskID); 
		DMA_Cmd(DMA1_Channel6,DISABLE);
	  Tos_TaskDropDev(DeviceId_USART3);
	}
	
}	
uint16 USART3_ReadDatas(uint8 *Buf,uint16 Length,uint32 TimeOut)
{
	BOOL R;
	R=Tos_TaskGetDev(DeviceId_USART3_RX,0);
	USART3_RX_Enable(ENABLE);
  if(R)
	{
		USART3_RX_TaskID=Tos_TaskCurrent;
		USART3_RX_Count=Length;
		USART3_RX_Index=0;
		if(TimeOut)Tos_TaskDelay(TimeOut);
		else Tos_TaskStop(USART3_RX_TaskID); 
	  Tos_TaskDropDev(DeviceId_USART3_RX);
		USART3_RX_Enable(DISABLE);
	}
	
	return USART3_RX_Index;
}
void DeviceMount_Usart3()
{
	DeviceId_USART3=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_USART3].DeviceId=DeviceId_USART3;
	Tos_Device_Tab[DeviceId_USART3].DeviceName="USART3";
	Tos_Device_Tab[DeviceId_USART3].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_USART3].DeviceVirtue=DV_Task;
	Tos_Device_Tab[DeviceId_USART3].DeviceState=Ready;
	Tos_Device_Tab[DeviceId_USART3].Init=USART3_Configuration;
	Tos_Device_Tab[DeviceId_USART3].Write=Null;//��дͨ�ú����ӿ�
	Tos_Device_Tab[DeviceId_USART3].Read=Null;//��дͨ�ú����ӿ�
	Tos_Device_Tab[DeviceId_USART3].Exit=Null;
	
	DeviceId_USART3_RX=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_USART3_RX].DeviceId=DeviceId_USART3_RX;
	Tos_Device_Tab[DeviceId_USART3_RX].DeviceName="USART3_RX";
	Tos_Device_Tab[DeviceId_USART3_RX].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_USART3_RX].DeviceVirtue=DV_Task;
	Tos_Device_Tab[DeviceId_USART3_RX].DeviceState=Ready;
	Tos_Device_Tab[DeviceId_USART3_RX].Init=Null;
	Tos_Device_Tab[DeviceId_USART3_RX].Write=Null;//��дͨ�ú����ӿ�
	Tos_Device_Tab[DeviceId_USART3_RX].Read=Null;//��дͨ�ú����ӿ�
	Tos_Device_Tab[DeviceId_USART3_RX].Exit=Null;
}
