/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <usb_driver.h>
#include <Include.h>

uint16 USB_IsrValue;						//�ϴ�USB�ж�ʱ���ж�״ֵ̬
static uint8 USB_ADDRESS=0;					//USB���䵽�ĵ�ַ

const uint8 *USB_DeviceDesc;				//�û�������豸������
const uint8 *USB_ConfigDesc;				//�û����������������
const uint8 *USB_ReportDesc;				//�û�����ı���������
const uint8 *USB_StringDesc[5];				//�û�������ַ���������

USB_RequestDef 	  USB_REQ;						//��ǰ�����������
USB_StateDef	  USB_STATE;					//��ǰUSB���״̬
uint8 (*USB_ClassSpecial_Request)(void);		//�û�������������
uint8 (*USB_VendorType_Request)(void);			//�û������Զ����������
Func USB_ENDP_DATA_IN[8];						//�û�����ǿ��ƶ˵�DATA_IN����
Func USB_ENDP_DATA_OUT[8];						//�û�����ǿ��ƶ˵�DATA_OUT����
Func USB_EndpointConfig;						//�û���ʼ���˵�,USB��reset֮��ص�


USB_EndpDef USB_Endp0;							//���ƶ˵�0


/*---------------------------------------------------------------------------------------------------------
 Func: USB��ʼ������
 Time: 2010-11-10
 Ver.: V1.0
 Note: 
---------------------------------------------------------------------------------------------------------*/
void SystemUSB_Config(uint8 Mode)
{																
	//USB����
	uint16 i;
	if(Mode==1){
		RCC->APB1ENR|=RCC_APB1ENR_USBEN;		
		USB->CNTR=0x8402;
		for(i=0;i<10000;i++);
		USB->CNTR=0x8400;
		USB->ISTR=0x0000;
		NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
		NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);
	}else{
		RCC->APB1ENR&=~RCC_APB1ENR_USBEN;
		NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
		NVIC_DisableIRQ(USB_HP_CAN1_TX_IRQn);
	}
}

/*-----------------------------------------------------------------------------------------------
 Func: USB���� ���÷���״̬
 Time: 2011-4-27
 Ver.: V1.0
 Note:
 ----------------------------------------------------------------------------------------------*/
 void USB_Init(void)
 {
 	uint8 i;
	 GPIO_InitTypeDef GPIO_InitStructure;
	 //OTGģʽѡ��ܽų�ʼ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); //ʹ��PortC
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
 	USB_ClassSpecial_Request=0;
	USB_VendorType_Request=0;
	for(i=0;i<8;i++){
		USB_ENDP_DATA_IN[i]=0;
		USB_ENDP_DATA_OUT[i]=0;
	}
 }

/*-----------------------------------------------------------------------------------------------
 Func: USB���� ���÷���״̬
 Time: 2011-4-27
 Ver.: V1.0
 Note:
 ----------------------------------------------------------------------------------------------*/
 void USB_SetTxRxMode(uint8 EndpId,uint16 TxRxMode)
 {
	uint16 T=USB->EPR[EndpId]&(USB_EPR_STAT_TX|USB_EPR_STAT_RX|0x8F8F);
	if(TxRxMode&USB_EPR_STAT_TX_0)T^=USB_EPR_STAT_TX_0;
	if(TxRxMode&USB_EPR_STAT_TX_1)T^=USB_EPR_STAT_TX_1;
	if(TxRxMode&USB_EPR_STAT_RX_0)T^=USB_EPR_STAT_RX_0;
	if(TxRxMode&USB_EPR_STAT_RX_1)T^=USB_EPR_STAT_RX_1;
	USB->EPR[EndpId]=T;
 }

/*-----------------------------------------------------------------------------------------------
 Func: USB���� ��ʼ������
 Time: 2011-4-27
 Ver.: V1.0
 Note:
 ----------------------------------------------------------------------------------------------*/
 void USB_ConfigEndp(uint8 EndpId,uint16 BufferSize,uint16 EndpFlag)
 {
	USB->ENDP[EndpId].TXCOUNT=0;
	USB->ENDP[EndpId].TXADDR=USB_IsrValue;
	if((EndpFlag&USB_EPR_STAT_TX)!=USB_EPR_STAT_TX_DIS){USB_IsrValue+=BufferSize;}
	USB->ENDP[EndpId].RXADDR=USB_IsrValue;
	if((EndpFlag&USB_EPR_STAT_RX)!=USB_EPR_STAT_RX_DIS){USB_IsrValue+=BufferSize;
		BufferSize=BufferSize<48?((BufferSize>>1)<<10):(((BufferSize>>5)-1)<<10)|0x8000;
		USB->ENDP[EndpId].RXCOUNT=BufferSize;		
	}
	USB->EPR[EndpId]=(EndpFlag&(~(USB_EPR_STAT_TX|USB_EPR_STAT_RX)))|EndpId;	//���ÿ���λ
	USB_SetTxRxMode(EndpId,EndpFlag&(USB_EPR_STAT_TX|USB_EPR_STAT_RX));			//�����շ�״̬
 }


/*-----------------------------------------------------------------------------------------------
 Func: USB���� ��ʼ������
 Time: 2011-4-27
 Ver.: V1.0
 Note:
 ----------------------------------------------------------------------------------------------*/
 void USB_Reset(void)
 {	
	USB->BTABLE=0x0000;							//���黺������������ʼ��ַ 
	USB_IsrValue=0x40;
	USB_ConfigEndp(0,USB_ENDP0_PACKETSIZE,USB_EPR_TYPE_CONTROL|USB_EPR_STAT_TX_STALL|USB_EPR_STAT_RX_VALID);
	if(USB_EndpointConfig)USB_EndpointConfig();
	USB->DADDR=USB_DADDR_EF|0;					//ʹ��USBģ��
 }

/*-----------------------------------------------------------------------------------------------
 Func: USB���� �Ӷ˵㻺����n��ȡ����
 Time: 2011-4-27
 Ver.: V1.0
 Note:
 ----------------------------------------------------------------------------------------------*/
 uint8 USB_ReadBuffer(uint8 nEDP,uint8 *RxBuffer,uint16 RxCount)
 {
 	uint8  C;
	uint32 *Addr=(uint32 *)(USB_PMA_BASE+(USB->ENDP[nEDP].RXADDR<<1));	//ת����32λ����(32λֻ�õ�ǰ16λ,�Ұ����ֶ���)
	C=(USB->ENDP[nEDP].RXCOUNT)&0x03FF;									//ȡʵ���յ�������	
	if(RxCount>C)RxCount=C;
	else C=RxCount;
	RxCount=(RxCount+1)>>1;												//���ȡ��
	while(RxCount--){
		*(uint16 *)RxBuffer++=*Addr++;
		RxBuffer++;
	}
	return	C; 
 }


 /*-----------------------------------------------------------------------------------------------
 Func: USB���� �Ӷ˵�������ݰ�
 Time: 2011-4-27
 Ver.: V1.0
 Note: ����: ʣ���ֽ���
 ----------------------------------------------------------------------------------------------*/
 uint16 USB_RecvPacket(uint8 EndpId,USB_EndpDef *Endp,uint8 *RxBuffer,uint16 RxCount)
 {	
	if(Endp->rAddr==0){
		if(RxBuffer>0){
			Endp->rAddr	 =RxBuffer;
			Endp->rLength=RxCount;
			Endp->rOffset=0;		
		}else{
			Endp->rOffset=0;
		}
	}else{
		if(RxCount>Endp->rLength)RxCount=Endp->rLength;
		RxCount=USB_ReadBuffer(EndpId,RxBuffer,RxCount);						//�Ӷ˵㻺������ȡ����
		Endp->rAddr	 +=RxCount;													//���¶����ݵ�ַ		
		Endp->rLength-=RxCount;
		Endp->rOffset+=RxCount;
		if(Endp->rLength==0)Endp->rAddr=0;
	}
	//USB_SetTxRxMode(EndpId,(USB->EPR[EndpId]&USB_EPR_STAT_TX)|USB_EPR_STAT_RX_VALID);
	return Endp->rLength;
 }


/*-----------------------------------------------------------------------------------------------
 Func: USB���� ��ȡ�˵�n�Ľ��ջ�������ַ
 Time: 2011-4-27
 Ver.: V1.0
 Note:
 ----------------------------------------------------------------------------------------------*/
 void USB_WriteBuffer(uint8 nEDP,uint8 *TxBuffer,uint16 TxCount)
 {	 	
	uint32 *Addr =(uint32 *)(USB_PMA_BASE+(USB->ENDP[nEDP].TXADDR<<1));	//ת����32λ����(32λֻ�õ�ǰ16λ,�Ұ����ֶ���)
	TxCount=(TxCount+1)>>1;													//���ȡ��
	while(TxCount--){		
		*Addr++=*(uint16 *)TxBuffer++;
		TxBuffer++;
	}
 }


 /*-----------------------------------------------------------------------------------------------
 Func: USB���� ��˵㷢�����ݰ�
 Time: 2011-4-27
 Ver.: V1.0
 Note: TxBuffer->USB_STATE.WriteAddr
 	   USB_STATE.WriteAddr>0:	
	   		TxCount>0 �������ݰ�
			TxCount=0 �����ݰ�0
	   USB_STATE.WriteAddr=0:
	   	    ֹͣ��
	   return: TxLength
	        =0:   Datapacket Length=0;
			<255: Datapacket Length real
			=255: buffer=0  stall packetet
 ----------------------------------------------------------------------------------------------*/
 uint8 USB_SendPacket(uint8 EndpId,USB_EndpDef *Endp,void *WriteBuffer,uint16 TxCount)
 {	
	uint8  R,Length,BufferSize,*TxBuffer;
	TxBuffer=(uint8 *)WriteBuffer;
	if(TxBuffer){
		BufferSize=USB->ENDP[EndpId].RXADDR-USB->ENDP[EndpId].TXADDR;
		if(EndpId==0){if(TxCount>USB_REQ.wLength)TxCount=USB_REQ.wLength;}
		Length=BufferSize>TxCount?TxCount:BufferSize;
		USB_WriteBuffer(EndpId,TxBuffer,Length);
		USB->ENDP[EndpId].TXCOUNT=Length;
		Endp->wAddr=TxBuffer+Length;
		if(TxCount>Length){															   
			Endp->wLength=TxCount-Length;					
		}else{			
			Endp->wLength=0;
			if(EndpId>0)Endp->wAddr=0;										//���ͽ���
			else if((Length==0)||(Length<BufferSize))USB_Endp0.wAddr=0;		//�´�׼�����Ϳ����ݰ�
		}
		R=Length;
	}else{
		USB->ENDP[EndpId].TXCOUNT=0;		
		R=0xFF;
	}
	if((USB->EPR[EndpId]&USB_EPR_STAT_RX)!=USB_EPR_STAT_RX_DIS){			//˫��˵�
		if(R<0xFF){USB_SetTxRxMode(EndpId,USB_EPR_STAT_TX_VALID|USB_EPR_STAT_RX_VALID);}
		else	  {USB_SetTxRxMode(EndpId,USB_EPR_STAT_TX_STALL|USB_EPR_STAT_RX_VALID);}	
	}else{																	//����˵�
		if(R<0xFF){USB_SetTxRxMode(EndpId,USB_EPR_STAT_TX_VALID|USB_EPR_STAT_RX_DIS);}
		else	  {USB_SetTxRxMode(EndpId,USB_EPR_STAT_TX_STALL|USB_EPR_STAT_RX_DIS);}	
	}
	return R;
 }


/*-----------------------------------------------------------------------------------------------
 Func: USB���� ���ƶ˵�DATA_OUT�жϷ���->��׼�������
 Time: 2011-4-29
 Ver.: V1.0
 Note:		  USB_RequestInfor
 ----------------------------------------------------------------------------------------------*/
 void USB_DATAOUT_ISR()
 {
	uint8 R;
	R=USB_SendPacket(0,&USB_Endp0,&R,0);
 }



 /*-----------------------------------------------------------------------------------------------
 Func: USB���� ���ƶ˵�DATA_IN�жϷ���->��׼�������
 Time: 2011-4-29
 Ver.: V1.0
 Note:		  USB_RequestInfor
 ----------------------------------------------------------------------------------------------*/
 void USB_DATAIN_ISR()
 {
 	uint8 R;
	if(USB_STATE.CurState==USB_STATE_SET_ADDRESS){
		USB->DADDR=USB_DADDR_EF|USB_ADDRESS;
		R=USB_SendPacket(0,&USB_Endp0,&R,0);	
	}else{
		R=USB_SendPacket(0,&USB_Endp0,USB_Endp0.wAddr,USB_Endp0.wLength);
	}
	return ;
 }


 /*-----------------------------------------------------------------------------------------------
 Func: USB���� ���ƶ˵�SETUP�жϷ���->��׼�������
 Time: 2011-4-29
 Ver.: V1.0
 Note:		  USB_RequestInfor
 ----------------------------------------------------------------------------------------------*/
 uint8 USB_SETUP_SUB_NODATA_ISR()
 {
 	uint8 RESULT=USB_RESULT_SUCCESS;	
	switch(USB_REQ.bRequest){
		case b_REQUEST_CLEAR_FEATURE:
			if((USB_REQ.wValue==FEATURE_DEVICE_REMOTE_WAKEUP)&&(USB_REQ.wIndex==0)){
				USB_STATE.CurFeature&=~S5;
			}
			break;
		case b_REQUEST_SET_FEATURE:							//�豸���ѹ���
			if((USB_REQ.wValue==FEATURE_DEVICE_REMOTE_WAKEUP)&&(USB_REQ.wIndex==0)){
				//if(USB_STATE.CurFeature&S5)
			}
			break;
		case b_REQUEST_SET_ADDRESS:	
			USB_ADDRESS=USB_REQ.wValue&0x007F;				//address<128
			USB_STATE.CurState=USB_STATE_SET_ADDRESS;		//���õ�ַ�׶�
			break;
		case b_REQUEST_SET_CONFIGURATION:
			USB_STATE.CurConfiguration=USB_REQ.wValue&0x00FF;
			break;												 
		case b_REQUEST_SET_INTERFACE:
			USB_STATE.CurInterface=USB_REQ.wValue&0x00FF;
			break;	
		default:	RESULT=USB_RESULT_UNSUPPORT;	break;
	}		
	return RESULT;
}

 /*-----------------------------------------------------------------------------------------------
 Func: USB���� ���ƶ˵�SETUP�жϷ���->��׼�������
 Time: 2011-4-29
 Ver.: V1.0
 Note: return/0
 ----------------------------------------------------------------------------------------------*/
 uint8 USB_SETUP_SUB_DATA_ISR()
 {
 	uint8 T,TxBuffer[10];
 	uint8 RESULT=USB_RESULT_SUCCESS;
	switch(USB_REQ.bRequest){
		case b_REQUEST_SET_DESCRIPTOR:			break;
		case b_REQUEST_GET_CONFIGURATION:		break;
		case b_REQUEST_GET_INTERFACE:	 		break;
		case b_REQUEST_SYNCH_FRAME:		 		break;					
		case b_REQUEST_GET_STATUS:									//״̬����
			switch(USB_REQ.bmRequestType&0x1F){
				case bm_REQUEST_RECIPIENT_DEVICE:
					if(USB_STATE.CurFeature&S5)TxBuffer[0]|=S1;
					if(!(USB_STATE.CurFeature&S6))TxBuffer[0]|=S0;
					USB_SendPacket(0,&USB_Endp0,TxBuffer,2);
					break;
				case bm_REQUEST_RECIPIENT_INTERFACE: USB_SendPacket(0,&USB_Endp0,"00",2); break;
				case bm_REQUEST_RECIPIENT_ENDPOINT:	 USB_SendPacket(0,&USB_Endp0,"00",2); break;
				default:	RESULT=USB_RESULT_UNSUPPORT;	break;					
			}
			break;	
		case b_REQUEST_GET_DESCRIPTOR:						//�豸������
			switch(USB_REQ.wValue>>8){
				case USB_DESCRIPTOR_TYPE_DEVICE: 
					USB_SendPacket(0,&USB_Endp0,(uint8 *)USB_DeviceDesc,*USB_DeviceDesc);			//�����豸������					
					break;
				case USB_DESCRIPTOR_TYPE_CONFIGURATION:
					USB_SendPacket(0,&USB_Endp0,(uint8 *)USB_ConfigDesc,*(USB_ConfigDesc+2));		//��������������
					break;
				case USB_DECSRIPTOR_TYPE_HID_CONFIG:
					USB_SendPacket(0,&USB_Endp0,(uint8 *)(USB_ConfigDesc+18),*(USB_ConfigDesc+18));	//����HID������
					break;
				case USB_DECSRIPTOR_TYPE_HID_REPORT:
					USB_SendPacket(0,&USB_Endp0,(uint8 *)USB_ReportDesc,*(USB_ConfigDesc+25));		//����report����
					break;
				case USB_DESCRIPTOR_TYPE_STRING:													//�ַ���������	
					T=USB_REQ.wValue&0xFF;
					USB_SendPacket(0,&USB_Endp0,(uint8 *)USB_StringDesc[T],*USB_StringDesc[T]);
					break;
				default:	RESULT=USB_RESULT_UNSUPPORT;	break;
			}							
			break;				
		default:	RESULT=USB_RESULT_UNSUPPORT;	break;
	}	
	return RESULT;
 }


 /*-----------------------------------------------------------------------------------------------
 Func: USB���� ���ƶ˵�SETUP�жϷ���
 Time: 2011-4-29
 Ver.: V1.0
 Note:		  USB_RequestInfor
 ----------------------------------------------------------------------------------------------*/
 void USB_SETUP_SUB_ISR(uint8 nEDP)
 {
 	uint8 i,RESULT;
 	uint8 RxBuffer[10];
 	USB_ReadBuffer(nEDP,RxBuffer,10);
	USB_REQ.bmRequestType	=RxBuffer[0];
	USB_REQ.bRequest		=RxBuffer[1];
	USB_REQ.wValue			=((uint16)RxBuffer[3]<<8)|RxBuffer[2];
	USB_REQ.wIndex			=((uint16)RxBuffer[5]<<8)|RxBuffer[4];
	USB_REQ.wLength			=((uint16)RxBuffer[7]<<8)|RxBuffer[6];
	switch(USB_REQ.bmRequestType&0x60){						//��ȡ���������
		case bm_REQUEST_TYPE_STANDARD:						//��׼����
			if(USB_REQ.wLength==0){							//����0������������,����0�������ݰ�	
				RESULT=USB_SETUP_SUB_NODATA_ISR();				
				if(RESULT==USB_RESULT_SUCCESS)USB_SendPacket(0,&USB_Endp0,&i,0);
			}else{											//Ҫ���з�������				
				RESULT=USB_SETUP_SUB_DATA_ISR();			//�����׼�������ݰ�				
			}
			break;			
		case bm_REQUEST_TYPE_CLASS:
			if(USB_ClassSpecial_Request)RESULT=USB_ClassSpecial_Request();			//�����û�����������
			else	RESULT=USB_RESULT_UNSUPPORT; 
			break;
		case bm_REQUEST_TYPE_VENDOR:
			if(USB_VendorType_Request)RESULT=USB_VendorType_Request();		//�����Զ�������
			else	RESULT=USB_RESULT_UNSUPPORT;
			break;						
		default:	RESULT=USB_RESULT_UNSUPPORT;	break;
	}
	if(RESULT==USB_RESULT_UNSUPPORT)USB_SendPacket(0,&USB_Endp0,0,0);
 }																								  


 /*-----------------------------------------------------------------------------------------------
 Func: USB���� �����ж�
 Time: 2011-4-27
 Ver.: V1.0
 Note:		  USB_RequestInfor
 ----------------------------------------------------------------------------------------------*/
 void USB_CTR_ISR(void){
 	uint8  Edp_Id,Edp_Dir;
	uint16 Edp_State;
	Edp_Id	=	USB_IsrValue&USB_ISTR_EP_ID;					//ȡ�ж϶˵��
	Edp_Dir	=	USB_IsrValue&USB_ISTR_DIR;						//ȡ���䷽��	
	if(Edp_Id==0){												//�˵�0�ж�					
		USB_SetTxRxMode(0,USB_EPR_STAT_TX_NAK|USB_EPR_STAT_RX_NAK);
		Edp_State	=	USB->EPR[0]&0x8F8F;						//���η�תλ
		if(Edp_Dir==0){											//�˵�0 IN���鴫�����
			USB->EPR[0]=(Edp_State&(~USB_EPR_CTR_TX));			//��TX
			USB_DATAIN_ISR(); 
		}else{													//�˵�0 OUT�����STEUP�������			
			if(Edp_State&USB_EPR_CTR_TX){						//OUT�������
				USB->EPR[0]=(Edp_State&(~USB_EPR_CTR_TX));				
				USB_DATAIN_ISR();
				USB_STATE.CurState=USB_STATE_DATA_IN;			//��������׶�
			}else if(Edp_State&USB_EPR_CTR_RX){									
				if(Edp_State&USB_EPR_SETUP){					//SETUP�������				
					USB->EPR[0]=(Edp_State&(~USB_EPR_CTR_RX));	//��RX										
					USB_STATE.CurState=USB_STATE_SETUP;			//��������
					USB_SETUP_SUB_ISR(0);										
				}else{											//OUT���ݰ�
					USB->EPR[0]=(Edp_State&(~USB_EPR_CTR_RX));	//��RX
					USB_DATAOUT_ISR();
				}
			}
		}
	}else{														//�Ƕ˵�0�ж�
		Edp_State=USB->EPR[Edp_Id]&0x8F8F;
		if(Edp_State&USB_EPR_CTR_RX){
			USB->EPR[Edp_Id]=(Edp_State&(~USB_EPR_CTR_RX));		//��RX
			if(USB_ENDP_DATA_OUT[Edp_Id])USB_ENDP_DATA_OUT[Edp_Id]();
		}
		if(Edp_State&USB_EPR_CTR_TX){
			USB->EPR[Edp_Id]=(Edp_State&(~USB_EPR_CTR_TX));		//��TX
			if(USB_ENDP_DATA_IN[Edp_Id])USB_ENDP_DATA_IN[Edp_Id]();				
		}
	} 
 }


/*-----------------------------------------------------------------------------------------------
 Func: USB���� �����ж�
 Time: 2011-4-27
 Ver.: V1.0
 Note:
 ----------------------------------------------------------------------------------------------*/
void USB_HP_CAN_TX_IRQHandler(void)
 {
	USB_IsrValue=USB->ISTR;	
	USB->ISTR&=~USB_IsrValue;
	if(USB_IsrValue&USB_ISTR_CTR){				//�˵���ȷ�����һ�����ݴ���
		while(USB->ISTR & USB_ISTR_CTR){
			USB_CTR_ISR();				
		}
	}
}						  


 /*-----------------------------------------------------------------------------------------------
 Func: USB���� �����ж�
 Time: 2011-4-27
 Ver.: V1.0
 Note:
 ----------------------------------------------------------------------------------------------*/
 void USB_LP_CAN_RX0_IRQHandler(void)
 {
	USB_IsrValue=USB->ISTR;	
	USB->ISTR&=~USB_IsrValue;
	if(USB_IsrValue&USB_ISTR_CTR){				//�˵���ȷ�����һ�����ݴ���
		USB_CTR_ISR();
	}
	if(USB_IsrValue&USB_ISTR_PMAOVR){}			//���黺�������
	if(USB_IsrValue&USB_ISTR_ERR){}				//�������,�Զ��ش�
	if(USB_IsrValue&USB_ISTR_WKUP){}			//��������
	if(USB_IsrValue&USB_ISTR_SUSP){}			//����ģ������					  
	if(USB_IsrValue&USB_ISTR_RESET){			//��λ�ж�,��λ��ַ�Ͷ˵�Ĵ���
		USB_Reset();		
	}
	if(USB_IsrValue&USB_ISTR_SOF){}				//֡�ױ�־
	if(USB_IsrValue&USB_ISTR_ESOF){}			//����֡�ױ�ʶλδ�յ��ж�
}

