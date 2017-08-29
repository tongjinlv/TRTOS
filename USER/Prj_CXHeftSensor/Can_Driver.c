/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <include.h>
#include <Tools_Include.h>
#include <..\USER\Prj_CXHeftSensor\Can_Driver.h>

void CAN_Filter_Configs(uint16 LocalAddr,BOOL Host)
{
	if(Host)
	{
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
		DeBug("Configs Filter For Master",Infor_Infor);
	CAN_FilterInitStructure.CAN_FilterNumber=0;	 
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	 // ��ʶ������λģʽ
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;   // 32λ������
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x00;			// id��λ����
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;		// ���������α�ʶ��
	CAN_FilterInitStructure.CAN_FilterIdLow=(uint16)(CAN_GROUP<<3)|CAN_RTR_DATA|CAN_ID_EXT;;		//id��λ����		
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;	 // FIFO0ָ�������
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	}
	else
	{
		
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
		DeBug("Configs Filter For Slave Addr=0x%x",LocalAddr,Infor_Infor);
	CAN_FilterInitStructure.CAN_FilterNumber=0;	 
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	 // ��ʶ������λģʽ
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;   // 32λ������
	CAN_FilterInitStructure.CAN_FilterIdHigh=LocalAddr;			
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;		// ����
	
	CAN_FilterInitStructure.CAN_FilterIdLow=(uint16)(CAN_GROUP<<3)|CAN_RTR_DATA|CAN_ID_EXT;		//id��λ����		
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;   //����
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;	 // FIFO0ָ�������
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_FilterInitStructure.CAN_FilterNumber=1;	 
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	 // ��ʶ������λģʽ
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;   // 32λ������
	CAN_FilterInitStructure.CAN_FilterIdHigh=0xffff;			// �豸���Խӵ��㲥��ַ
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;		// ����
	
	CAN_FilterInitStructure.CAN_FilterIdLow=(uint16)(CAN_GROUP<<3)|CAN_RTR_DATA|CAN_ID_EXT;		//id��λ����		
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;   //����
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;	 // FIFO0ָ�������
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	}
}
/*************************************************************
Func:  CAN �ж�����
Date:  2014-8-26
Note:  
*************************************************************/
void CAN_NVIC_Cfg(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable CAN1 RX0 interrupt IRQ channel */
   NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

} 

/*************************************************************
Func:  CAN ������Ϣ
Date:  2014-8-26
Note:  
*************************************************************/
void CAN_SendMsg(void *Msg,uint8 Length)
{
	static uint8 TestValue='0';
	uint16 TransmitMailbox=0,i=0;
	CanTxMsg  TxMessage;
	TxMessage.ExtId=0x11<<13;//���հ��ַ
	TxMessage.RTR=CAN_RTR_DATA;//��������֡
	TxMessage.IDE=CAN_ID_EXT;
	TxMessage.DLC=Length+1;//�������ݵĳ���
	BufferCoppy(Msg,&TxMessage.Data[0],Length);
	TxMessage.Data[Length]=TestValue;
	TransmitMailbox=CAN_Transmit(CAN1,&TxMessage);
	while((CAN_TransmitStatus(CAN1,TransmitMailbox)!=CANTXOK)&&(i!=0xff)) 
	{
	i++;
		Tos_TaskDelay(1);
	}
	if(i==0xff)DeBug("Can Send TimeOut1",Infor_Infor);
	else DeBug("Can Send Succeed1",Infor_Infor);
	if(TestValue<'9')TestValue++;
	else TestValue='0';
}






















