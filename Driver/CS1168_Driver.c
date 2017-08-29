/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Cs1168_Driver.h>

#define CS1168_CLK_SET 	GPIOA->BSRR=S2	
#define CS1168_CLK_CLR 	GPIOA->BRR=S2
#define CS1168_DAT 	   (GPIOA->IDR&S1)

int16 CS1168_ADC;
/*******************************************************************************
Func:CS1168ר����ʱ
Date:2014-10-9
Note:
*******************************************************************************/
void CS1168_Delay(uint8 i)
{
	i*=20;
	while(i--);
}
/*******************************************************************************
Func:CS1168�˿ڳ�ʼ��
Date:2014-10-9
Note:
*******************************************************************************/
void CS1168_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*******************************************************************************
FuncCS11685��ʼ��
Date:2014-10-9
Note:
*******************************************************************************/
uint8 IniCS1168()
{
	u16	count;
	count=65535;
	CS1168_GPIO_Init();
	CS1168_CLK_CLR;
	CS1168_Delay(1);
	CS1168_CLK_SET;
	CS1168_Delay(1);
	while(!CS1168_DAT)
	{					
		count--;
		if(count==0)
			return	1;
	}
	count=65535;
	while(CS1168_DAT)
	{
		count--;
		if(count==0)
			return	1;			
	}
	CS1168_CLK_CLR;   
	return	0; 
}
/*******************************************************************************
Func:CS1168��ȡ����
Date:2014-10-9
Note:
*******************************************************************************/
uint8 CS1168_ReceiveByte(void)
{
	u8 i;
	u8 rdata = 0;
	
	for(i = 8; i!=0; i--)
	{
		rdata <<= 1;
		CS1168_CLK_CLR;
		CS1168_Delay(1);
		CS1168_CLK_SET;
		CS1168_Delay(1);
		if(CS1168_DAT)
		{
			rdata += 1;
		}
	}        
	return(rdata);
}
/*******************************************************************************
Func:CS1168��ȡADC
Date:2014-10-9
Note:
*******************************************************************************/
int16 CS1168_ReadADC()
{
	uint8  i;
	uint32 Count=1000;
	static uint16 dat;
	uint8 Buf[3];	
	while(CS1168_DAT&Count--)
	{
		//return	1;
	}
	if(Count<1)return dat;
	CS1168_CLK_CLR;
	CS1168_Delay(1);
	CS1168_CLK_SET;					//��һ��SCLK �ź�Ϊ��Ӧ�ź�
	CS1168_Delay(1);
	for(i = 0; i < 2; i++)
	{
		Buf[i] = CS1168_ReceiveByte();
	}
	CS1168_ReceiveByte();
	CS1168_CLK_CLR;				  
	dat=Buf[0]*256+Buf[1];
	return	(int16)dat; 
}
