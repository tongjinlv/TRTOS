/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <SPI_Driver.h>
#include <..\USER\Prj_TeleControl\24L01_Driver.h>


 uint8 RX_BUF[RX_PLOAD_WIDTH];		//�������ݻ���
uint8 TX_BUF[TX_PLOAD_WIDTH];		//�������ݻ���
uint8 TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};  // ����һ����̬���͵�ַ
uint8 RX_ADDRESS[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};
uint8 DeviceId_ZIGBEE=DeviceNull;

const GPIO_InitStruct Nrf_GPIO_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5},
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_15},
	{GPIO_Speed_2MHz,GPIO_Mode_IPU,GPIOB,GPIO_Pin_6|GPIO_Pin_7},
	{0},
};

void Nrf_MOSI(BOOL Level){if(Level)GPIO_SetBits(GPIOB,GPIO_Pin_4);else GPIO_ResetBits(GPIOB,GPIO_Pin_4);}
void Nrf_SCLK(BOOL Level){if(Level)GPIO_SetBits(GPIOB,GPIO_Pin_5);else GPIO_ResetBits(GPIOB,GPIO_Pin_5);}
void Nrf_CE(BOOL Level){if(Level)GPIO_SetBits(GPIOB,GPIO_Pin_3);else GPIO_ResetBits(GPIOB,GPIO_Pin_3);}
void Nrf_CSN(BOOL Level){if(Level)GPIO_SetBits(GPIOA,GPIO_Pin_15);else GPIO_ResetBits(GPIOA,GPIO_Pin_15);}
BOOL Nrf_IRQ(){return (BOOL)GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7);}
BOOL Nrf_MISO(){return (BOOL)GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6);}


const SPI_PublicStruct SPI_Nrf={
	Nrf_MOSI,
	Nrf_SCLK,
	Nrf_CE,
	Nrf_CSN,
	Nrf_IRQ,
	Nrf_MISO,
	1,
};
void Nrf_RX_Mode(void)
{
	Nrf_CE(False);	
	SPI_WriteBuf(&SPI_Nrf,NRF_WRITE_REG+RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ    
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+RF_CH,CHANAL);      //����RFͨ��Ƶ��    
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ��      
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+RF_SETUP,0x0f); //����TX�������,0db����,2Mbps,���������濪��   
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+CONFIG, 0x0f);  //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
	Nrf_CSN(True);/*CE���ߣ��������ģʽ*/	
}   
void Nrf_TX_Mode()
{
	SPI_WriteBuf(&SPI_Nrf,NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH);    //дTX�ڵ��ַ 
	SPI_WriteBuf(&SPI_Nrf,NRF_WRITE_REG+RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK   
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+RF_CH,CHANAL);       //����RFͨ��ΪCHANAL
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	Nrf_CSN(True);/*CE���ߣ����뷢��ģʽ*/	
	SPI_Delay(0xffff); //CEҪ����һ��ʱ��Ž��뷢��ģʽ
}
uint8 Nrf_Check(void)
{
	uint8 buf[5]={0xC2,0xC2,0xC2,0xC2,0xC2};
	uint8 buf1[5];
	uint8 i; 
	SPI_WriteBuf(&SPI_Nrf,NRF_WRITE_REG+TX_ADDR,buf,5);	/*д��5���ֽڵĵ�ַ.  */  
	SPI_ReadBuf(&SPI_Nrf,TX_ADDR,buf1,5); /*����д��ĵ�ַ */      
	for(i=0;i<5;i++)/*�Ƚ�*/ 
	{
		if(buf1[i]!=0xC2)
		break;
	}        
	if(i==5)return SUCCESS ;        //MCU��NRF�ɹ����� 
	else return ERROR ;        //MCU��NRF����������
}

uint8 Nrf_Tx_Dat(uint8 *txbuf)
{
	uint8 state;  
	Nrf_CE(False);					
	SPI_WriteBuf(&SPI_Nrf,WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);
	Nrf_CE(True);                           
	while(Nrf_IRQ()!=0); 	                            
	state = SPI_WR(&SPI_Nrf,STATUS);                 
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+STATUS,state); 	
	SPI_WriteReg(&SPI_Nrf,FLUSH_TX,NOP);    //���TX FIFO�Ĵ��� 
	if(state&MAX_RT) return MAX_RT; 
	else if(state&TX_DS)                  //�������
	return TX_DS;
	else return ERROR;                 //����ԭ����ʧ��
} 
uint8 Nrf_Rx_Dat(uint8 *rxbuf)
{
	uint8 state; 
	Nrf_CE(True);
	while(Nrf_IRQ()!=0){Tos_TaskDelay(1);} 
	Nrf_CE(False);  	             
	state=SPI_WR(&SPI_Nrf,STATUS);   
	SPI_WriteReg(&SPI_Nrf,NRF_WRITE_REG+STATUS,state);
	if(state&RX_DR)                                 //���յ�����
	{
	SPI_ReadBuf(&SPI_Nrf,RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
	SPI_WriteReg(&SPI_Nrf,FLUSH_RX,NOP);          //���RX FIFO�Ĵ���
	return RX_DR; 
	}
	else return ERROR;                    //û�յ��κ�����
}
void DeviceMount_ZigBee()
{
	DeviceId_ZIGBEE=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_ZIGBEE].DeviceName="ZigBee";
	Tos_Device_Tab[DeviceId_ZIGBEE].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_ZIGBEE].DeviceVirtue=DV_IOList;
	Tos_Device_Tab[DeviceId_ZIGBEE].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_ZIGBEE].Init=GPIO_InitList;
	Tos_Device_Tab[DeviceId_ZIGBEE].Note=(uintbus)&Nrf_GPIO_List[0];
	Tos_Device_Tab[DeviceId_ZIGBEE].Write=Null;
	Tos_Device_Tab[DeviceId_ZIGBEE].Read=Null;
	Tos_Device_Tab[DeviceId_ZIGBEE].Exit=Null;
}
void Nrf_Task(void *Tags)
{
	uint8 Flag;
	Nrf_RX_Mode();
	while(1)
	{
		Flag=Nrf_Rx_Dat(TX_BUF);
		if(Flag!=ERROR){if(TX_BUF[0])LED3_ON;else LED3_OFF;}
		Tos_TaskDelay(100);
	}
}

