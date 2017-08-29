/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <include.h>
#include <Tools_Include.h>
#include <Can1_Driver.h>
uint8 CAN_Tos_TaskID=Tos_TaskNull;
uint8 DeviceId_CAN1=DeviceNull;
Tos_ArrayMessage Msg[10]; 
CanRxMsg RxMessageBuf[10];
/*************************************************************
Func:  CAN �����ж�
Date:  2014-8-26
Note:  ������û��ʹ��
*************************************************************/
void USB_HP_CAN0_TX_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN1, CAN_IT_TME)!=RESET)	 //FIFO���ж�
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_TME);      //����жϱ��
                         
	}	
}
extern void CAN_Istr(CanRxMsg *RxMessage);
extern void USB_Istr(void);
/*************************************************************
Func:  CAN �����ж�
Date:  2014-8-26
Note:  ֮ǰ������Ϊ���������
*************************************************************/

#if defined(USBHID_ENABLE)
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  USB_Istr();
}

#elif defined(CAN_ISTR_EN)
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;	
	if (CAN_GetITStatus(CAN1, CAN_IT_FMP0)!=RESET)	 //FIFO1��Ϣ�Һ�״̬��־ 
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);     //����жϱ��
		CAN_Receive(CAN1, CAN_FIFO0, &RxMessage); 	 //��FIFO1�еı�����浽��ʱ�ṹ����
		CAN_Istr(&RxMessage);
	}	
}
#endif

/*************************************************************
Func:  CAN GPIO��ʼ��
Date:  2014-8-26
Note:  
*************************************************************/
void CAN1_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOF,ENABLE);
	GPIO_Struct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Struct.GPIO_Pin=GPIO_Pin_11;
	GPIO_Init(GPIOA,&GPIO_Struct);

	GPIO_Struct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Struct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Struct.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
}

/*************************************************************
Func:  CAN �ж�����
Date:  2014-8-26
Note:  
*************************************************************/
void CAN1_NVIC_Cfg(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable CAN1 RX0 interrupt IRQ channel */
   NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

}

void CAN_SIG_Filter_Configs()
{
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	CAN_FilterInitStructure.CAN_FilterNumber=0;	 
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	 // ��ʶ������λģʽ
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;   // 32λ������
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;			
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;		// ����
	
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;   //����
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;	 // FIFO0ָ�������
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
}
/*************************************************************
Func:  CAN ��ʼ��
Date:  2014-8-26
Note:  
*************************************************************/
void CAN_SIG_Init(void)
{
	CAN_InitTypeDef        CAN_InitStructure;

	CAN1_NVIC_Cfg();
	CAN1_GPIO_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
		
	CAN_DeInit(CAN1);//�ָ���Ĭ��ֵ
	CAN_StructInit(&CAN_InitStructure);//��λ��������   

	CAN_InitStructure.CAN_TTCM=DISABLE;//��ֹʱ�䴥��ͨ��ģʽ
	CAN_InitStructure.CAN_ABOM=DISABLE;//�������CAN_MCR�Ĵ�����INRQλ������1�����0��һ��Ӳ�����
                                     //��128��11λ����������λ�����˳�����״̬��
	CAN_InitStructure.CAN_AWUM=DISABLE;//˯��ģʽͨ�����CAN_MCR�Ĵ�����SLEEPλ�����������
	CAN_InitStructure.CAN_NART=ENABLE;//DISABLE;CAN����ֻ������1�Σ����ܷ��͵Ľ����Σ��ɹ���������ٲö�ʧ��
	CAN_InitStructure.CAN_RFLM=DISABLE;//�ڽ������ʱFIFOδ��������������FIFO�ı���δ����������һ���յ��ı��ĻḲ��ԭ��
	CAN_InitStructure.CAN_TXFP=DISABLE;//����FIFO���ȼ��ɱ��ĵı�ʶ��������
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;   
#ifdef HSI_USER
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_6tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;
	CAN_InitStructure.CAN_Prescaler=9;//36/8/16
#else 
CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler=9;//36/8/16
#endif
	
	// CAN  BaudRate = RCC_APB1PeriphClock/(CAN_SJW+CAN_BS1+CAN_BS2)/CAN_Prescaler */
	CAN_Init(CAN1,&CAN_InitStructure);										
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
	CAN_SIG_Filter_Configs();
	
} 

void CAN_SIG_SendMsg(uint8 *Data,uint32 Addr)
{
	uint16 TransmitMailbox=0,i=0;
	CanTxMsg  TxMessage;
	TxMessage.IDE=CAN_ID_STD;
	TxMessage.StdId=Addr;
	TxMessage.RTR=CAN_RTR_DATA;//��������֡
	BufferCoppy(Data,&TxMessage.Data[0],8);
	TxMessage.DLC=8;
	TransmitMailbox=CAN_Transmit(CAN1,&TxMessage);
	while(CAN_TransmitStatus(CAN1,TransmitMailbox)!=CANTXOK) 
	{
	i++;
	if(i>=0xff){CAN_SIG_Init();return;}
	Tos_TaskDelay(1);
	}
}
///*************************************************************
//Func:  CAN ������Ϣ
//Date:  2014-8-26
//Note:  
//*************************************************************/
//void CAN1_SendMsg(void *Msg,uint8 Length)
//{
//	static uint8 TestValue='0';
//	uint16 TransmitMailbox=0,i=0;
//	CanTxMsg  TxMessage;
//	TxMessage.ExtId=0x11<<13;//���հ��ַ
//	TxMessage.RTR=CAN_RTR_DATA;//��������֡
//	TxMessage.IDE=CAN_ID_EXT;
//	TxMessage.DLC=Length+1;//�������ݵĳ���
//	BufferCoppy(Msg,&TxMessage.Data[0],Length);
//	TxMessage.Data[Length]=TestValue;
//	TransmitMailbox=CAN_Transmit(CAN1,&TxMessage);
//	while((CAN_TransmitStatus(CAN1,TransmitMailbox)!=CANTXOK)&&(i!=0xff)) 
//	{
//	i++;
//		Tos_TaskDelay(1);
//	}
//	if(i==0xff)DeBug("Can Send TimeOut1",Infor_Infor);
//	else DeBug("Can Send Succeed1",Infor_Infor);
//	if(TestValue<'9')TestValue++;
//	else TestValue='0';
//}
void DeviceMount_Can1()
{
	DeviceId_CAN1=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_CAN1].DeviceName="CAN1";
	Tos_Device_Tab[DeviceId_CAN1].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_CAN1].DeviceVirtue=DV_Task;
	Tos_Device_Tab[DeviceId_CAN1].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_CAN1].Init=CAN_SIG_Init;
	Tos_Device_Tab[DeviceId_CAN1].Write=Null;
	Tos_Device_Tab[DeviceId_CAN1].Read=Null;
	Tos_Device_Tab[DeviceId_CAN1].Exit=Null;
}






















