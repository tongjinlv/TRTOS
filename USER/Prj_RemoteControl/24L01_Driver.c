/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <..\USER\Prj_RemoteControl\24L01_Driver.h>

 uint8 RX_BUF[RX_PLOAD_WIDTH];		//�������ݻ���
 uint8 TX_BUF[TX_PLOAD_WIDTH];		//�������ݻ���
 uint8 TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};  // ����һ����̬���͵�ַ
 uint8 RX_ADDRESS[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};

#define NRF_CE_SET      GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define NRF_CE_CLR      GPIO_ResetBits(GPIOB,GPIO_Pin_3)

#define NRF_CSN_SET     GPIO_SetBits(GPIOA,GPIO_Pin_15)
#define NRF_CSN_CLR     GPIO_ResetBits(GPIOA,GPIO_Pin_15)

#define NRF_SCK_SET     GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define NRF_SCK_CLR     GPIO_ResetBits(GPIOB,GPIO_Pin_5)

#define NRF_MOSI_SET    GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define NRF_MOSI_CLR    GPIO_ResetBits(GPIOB,GPIO_Pin_4)

#define NRF_MISO_DAT   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define NRF_IRQ_DAT    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
void Nrf_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	NRF_CE_CLR;
	NRF_CSN_SET;
	NRF_SCK_CLR;
	Remap_SWJ_JTAGDisable();
}
void Nrf_Delay(uint16 i)
{
	while(i--);
}
uint8 Nrf_WR(uint8 Data)
{
	uint8 i,Temp=0x00;
	for(i=0;i<8;i++)
	{
		Temp<<=1;
		if(Data&0x80)NRF_MOSI_SET;else NRF_MOSI_CLR;
		if(NRF_MISO_DAT)Temp|=0x01;
		Data<<=1;
		Nrf_Delay(1);
		NRF_SCK_SET;
		Nrf_Delay(1);
		NRF_SCK_CLR;
	  Nrf_Delay(1);
	}
	return Temp;
}
uint8 Nrf_WriteReg(uint8 reg,uint8 dat)
{
	uint8 status;
	NRF_CE_CLR;
	NRF_CSN_CLR;
	status = Nrf_WR(reg);
	Nrf_WR(dat);        
	NRF_CSN_SET;	
	return(status);
}


/*
 * ��������Nrf_ReadReg
 * ����  �����ڴ�NRF�ض��ļĴ�����������
 * ����  ��reg:NRF������+�Ĵ�����ַ��
 * ���  ���Ĵ����е�����
 * ����  ���ڲ�����
 */
uint8 Nrf_ReadReg(uint8 reg)
{
 	uint8 reg_val;
	NRF_CE_CLR;
 	NRF_CSN_CLR;
	Nrf_WR(reg); 
	reg_val = Nrf_WR(NOP);
	NRF_CSN_SET;		
	return reg_val;
}	
uint8 Nrf_ReadBuf(uint8 reg,uint8 *pBuf,uint8 Length)
{
 	uint8 status, byte_cnt;
  NRF_CE_CLR;
	NRF_CSN_CLR;
	status = Nrf_WR(reg); 
	for(byte_cnt=0;byte_cnt<Length;byte_cnt++)		  
	pBuf[byte_cnt] = Nrf_WR(NOP); //��NRF24L01��ȡ����  
	NRF_CSN_SET;		
 	return status;		//���ؼĴ���״ֵ̬
}



/*
 * ��������Nrf_WriteBuf
 * ����  ��������NRF�ļĴ�����д��һ������
 * ����  ��reg:NRF������+�Ĵ�����ַ��
 		   pBuf���洢�˽�Ҫд��д�Ĵ������ݵ����飬�ⲿ����
		   bytes: pBuf�����ݳ���	
 * ���  ��NRF��status�Ĵ�����״̬
 * ����  ���ⲿ����
 */
uint8 Nrf_WriteBuf(uint8 reg ,uint8 *pBuf,uint8 Length)
{
	uint8 status,byte_cnt;
	NRF_CE_CLR;
	NRF_CSN_CLR;			
	status = Nrf_WR(reg); 
	for(byte_cnt=0;byte_cnt<Length;byte_cnt++)
	Nrf_WR(*pBuf++);	//д���ݵ������� 	 
	NRF_CSN_SET;			
	return (status);	//����NRF24L01��״̬ 		
}
void Nrf_RX_Mode(void)
{
	NRF_CE_CLR;	
	Nrf_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	Nrf_WriteReg(NRF_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
	Nrf_WriteReg(NRF_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ    
	Nrf_WriteReg(NRF_WRITE_REG+RF_CH,CHANAL);      //����RFͨ��Ƶ��    
	Nrf_WriteReg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ��      
	Nrf_WriteReg(NRF_WRITE_REG+RF_SETUP,0x0f); //����TX�������,0db����,2Mbps,���������濪��   
	Nrf_WriteReg(NRF_WRITE_REG+CONFIG, 0x0f);  //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
	NRF_CSN_SET;/*CE���ߣ��������ģʽ*/	
}   
void Nrf_TX_Mode(void)
{  
	NRF_CE_CLR;		
	Nrf_WriteBuf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH);    //дTX�ڵ��ַ 
	Nrf_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK   
	Nrf_WriteReg(NRF_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
	Nrf_WriteReg(NRF_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
	Nrf_WriteReg(NRF_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
	Nrf_WriteReg(NRF_WRITE_REG+RF_CH,CHANAL);       //����RFͨ��ΪCHANAL
	Nrf_WriteReg(NRF_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
	Nrf_WriteReg(NRF_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF_CSN_SET;/*CE���ߣ����뷢��ģʽ*/	
	Nrf_Delay(0xffff); //CEҪ����һ��ʱ��Ž��뷢��ģʽ
}
uint8 Nrf_Check(void)
{
	uint8 buf[5]={0xC2,0xC2,0xC2,0xC2,0xC2};
	uint8 buf1[5];
	uint8 i; 
	Nrf_WriteBuf(NRF_WRITE_REG+TX_ADDR,buf,5);	/*д��5���ֽڵĵ�ַ.  */  
	Nrf_ReadBuf(TX_ADDR,buf1,5); /*����д��ĵ�ַ */      
	for(i=0;i<5;i++)/*�Ƚ�*/ 
	{
		if(buf1[i]!=0xC2)
		break;
	} 
	       
	if(i==5)
		return SUCCESS ;        //MCU��NRF�ɹ����� 
	else
		return ERROR ;        //MCU��NRF����������
}
uint8 Nrf_Tx_Dat(uint8 *txbuf)
{
	uint8 state;  
	NRF_CE_CLR;					
	Nrf_WriteBuf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);
	NRF_CE_SET;

	/*�ȴ���������ж� */                            
	while(NRF_IRQ_DAT!=0); 	

	/*��ȡ״̬�Ĵ�����ֵ */                              
	state = Nrf_ReadReg(STATUS);

	/*���TX_DS��MAX_RT�жϱ�־*/                  
	Nrf_WriteReg(NRF_WRITE_REG+STATUS,state); 	
	Nrf_WriteReg(FLUSH_TX,NOP);    //���TX FIFO�Ĵ��� 

	/*�ж��ж�����*/    
	if(state&MAX_RT)                     //�ﵽ����ط�����
	return MAX_RT; 

	else if(state&TX_DS)                  //�������
	return TX_DS;
	else						  
	return ERROR;                 //����ԭ����ʧ��
} 
u8 Nrf_Rx_Dat(u8 *rxbuf)
{
	u8 state; 
	NRF_CE_SET;	 //�������״̬
	/*�ȴ������ж�*/
	while(NRF_IRQ_DAT!=0)Tos_TaskDelay(1); 

	NRF_CE_CLR;  	 //�������״̬
	/*��ȡstatus�Ĵ�����ֵ  */               
	state=Nrf_ReadReg(STATUS);

	/* ����жϱ�־*/      
	Nrf_WriteReg(NRF_WRITE_REG+STATUS,state);

	/*�ж��Ƿ���յ�����*/
	if(state&RX_DR)                                 //���յ�����
	{
	Nrf_ReadBuf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
	Nrf_WriteReg(FLUSH_RX,NOP);          //���RX FIFO�Ĵ���
	return RX_DR; 
	}
	else    
	return ERROR;                    //û�յ��κ�����
}

void Nrf_Task(void *Tags)
{
	uint8 Flag;
	BOOL EN=False,OldEN;
	Nrf_GPIO_Init();
	Nrf_TX_Mode();
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))EN=True;else EN=False;
		TX_BUF[0]=EN;
		TX_BUF[2]=ADCBuffer[2]/0xff;
		TX_BUF[3]=ADCBuffer[2]%0xff;
		if(EN)LED3_OFF;
		if(EN!=OldEN)
			{
			Flag=Nrf_Tx_Dat(TX_BUF);
			if(Flag==0x20){LED3_ON;OldEN=EN;}else LED3_OFF;
		}
		Tos_TaskDelay(100);
	}
}

