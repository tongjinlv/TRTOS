/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <AD7705_Driver.h>
#include <Text.h>

/*******************************************************************************
Func:ר����ʱ����
Date:2014-10-9
Note:
*******************************************************************************/
void AD7705_Delay(uint8 i)
{
	i*=5;
	while(i--);
}
/*******************************************************************************
Func:GPIO��ʼ��
Date:2014-10-9
Note:
*******************************************************************************/
void AD7705_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*******************************************************************************
Func:Ӳ����λ
Date:2014-10-9
Note:
*******************************************************************************/
void AD7705_Reset()
{
	AD7705_RST_CLR;
	AD7705_Delay(15);
	AD7705_RST_SET;
	AD7705_Delay(5);
}
/*******************************************************************************
Func:��ȡһ�ֽ�
Date:2014-10-9
Note:
*******************************************************************************/
uint8 AD7705_ReadByte()
{
	uint8 Data=0,i;
	for(i=0;i<8;i++)
	{
		Data<<=1;
		AD7705_CLK_CLR;
		AD7705_Delay(5);
		if(AD7705_OUT_DAT)Data++;
		AD7705_CLK_SET;
		AD7705_Delay(5);
	}
	return Data;
}

/*******************************************************************************
Func:дһ�ֽ�
Date:2014-10-9
Note:
*******************************************************************************/
void AD7705_WriteByte(unsigned char data) 
{ 
	unsigned char i;
  for(i=0; i<8; i++) 
  { 
    AD7705_CLK_CLR; 
    if(data&0x80) AD7705_DIN_SET
    else 
    AD7705_DIN_CLR;                  
    AD7705_Delay(5); 
    AD7705_CLK_SET;                  
    AD7705_Delay(5);
    data <<= 1; 
  }          
  AD7705_DIN_SET;          
} 
/*******************************************************************************
Func:AD7705��ʼ��
Date:2014-10-9
Note:
*******************************************************************************/
void AD7705_Init(uint8 CH)
{
	
	unsigned char i;
	AD7705_GPIO_Init();
	AD7705_CS_CLR;
	for(i=10;i>0;i--) 
	{AD7705_WriteByte(0xff);}  //����DIN�ߵ�ƽд�������ָ�AD7705�ӿ�
	AD7705_Reset();         /* ��ֹ����ʧ�� */ 
	AD7705_WriteByte(0x21); /* дch0 clock register */ 
	AD7705_WriteByte(0x00); /* 2.4576MHzʱ�ӣ�20Hz���ݸ������� */ 
	AD7705_WriteByte(0x11); /*ѡ�����üĴ���,ʹ��chnanel 1*/
	AD7705_WriteByte(0x44); 
	AD7705_Delay(100);
}
/*******************************************************************************
Func:AD7705��ʼ��
Date:2014-10-9
Note:
*******************************************************************************/
uint16 AD7705_GetADC() 
{
	uint16 Temp;
	while(AD7705_DEDY_DAT)Tos_TaskDelay(1);     //����׼����           
	AD7705_WriteByte(0x39);     
	Temp=AD7705_ReadByte();
	Temp<<=8;
	Temp|=AD7705_ReadByte();	//AD7705_ReadWord();//��ȡ  
	return Temp; 
}
uint16 AD7705_ReadFitel()
{
	static uint32 Pool=0;
	static uint8 PoolIndex=0;
	uint16 Temp;
	Temp=FlowPoolFilter(&Pool,AD7705_GetADC(),&PoolIndex,3);
	return Temp;
}
