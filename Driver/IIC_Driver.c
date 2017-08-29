/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <include.h>
#include <IIC_driver.h>
#include <STM32_CPU.h>
//////����ģ�û�������ڵ����ˣ�ʲô��Э�飬����׼
/*******************************************************************************
 Func: �ӳ�
*******************************************************************************/
void IIC_DelayUs(uint16 us)
{
	//us=50;
	while(us--);
}
static void IIC_Pin_Out(const GPIO_InitStruct Pin_Map)
{     
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Pin_Map.GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;            
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(Pin_Map.GPIOx, &GPIO_InitStructure);
}
/*******************************************************************************
 Func: ���ó����뷽ʽ
*******************************************************************************/
static void IIC_Pin_In(const GPIO_InitStruct Pin_Map)
{     
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Pin_Map.GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;          
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(Pin_Map.GPIOx, &GPIO_InitStructure);

}


/*******************************************************************************
 Func: ����IIC���߿���
*******************************************************************************/
void IIC_Start(const GPIO_InitStruct *Pin_Maps)
{   
	 GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
	 GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);IIC_DelayUs(10);   
	 GPIO_ResetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);IIC_DelayUs(10);  
	 GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);IIC_DelayUs(10);   
}

/*******************************************************************************
 Func: ֹͣIIC���߿���
*******************************************************************************/
void IIC_Stop(const GPIO_InitStruct *Pin_Maps)
{
   GPIO_ResetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin); 
   GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin); IIC_DelayUs(10);
   GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);IIC_DelayUs(30);
	 GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);IIC_DelayUs(20);
}


/*******************************************************************************
 Func: �ͷ�IIC���߿���
*******************************************************************************/
void IIC_Drop(const GPIO_InitStruct *Pin_Maps)
{
	GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
	GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);
}


/*******************************************************************************
 Func: ����ACK�ź�
*******************************************************************************/
void IIC_SendAck(const GPIO_InitStruct *Pin_Maps,uint8 Ack)
{
   if(Ack)GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
   else GPIO_ResetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);                   //����ACK�ź�
   GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);IIC_DelayUs(10);
   GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);IIC_DelayUs(10); 
   GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin); 
}
/*******************************************************************************
 Func: ��ȡACK�ź� ����1λ��
*******************************************************************************/
uint8 IIC_ReadAck(const GPIO_InitStruct *Pin_Maps)
{
	uint8 CY = 0x00;
  GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
  IIC_Pin_In(Pin_Maps[1]);
  GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);              //����ʱ����
  IIC_DelayUs(10);                
  CY |= GPIO_ReadInputDataBit(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);    //��Ӧ���ź�
  IIC_DelayUs(10);             
  GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);              //����ʱ����
  IIC_Pin_Out(Pin_Maps[1]);
	return CY;
}

uint8 IIC_SendByte(const GPIO_InitStruct *Pin_Maps,uint8 dat)
{
  uint8 i;
  for (i=0; i<8; i++)         			//8λ������
  {
    if (dat&0x80)	GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
    else	GPIO_ResetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin) ;              //�����ݿ�
    IIC_DelayUs(10);             			//��ʱ
    GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);                		//����ʱ����
    IIC_DelayUs(10);             			//��ʱ
    GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);                		//����ʱ����
    IIC_DelayUs(10);             			//��ʱ
    dat <<= 1;              			//�Ƴ����ݵ����λ
  }
  return IIC_ReadAck(Pin_Maps);
}

uint8 IIC_RecvByte(const GPIO_InitStruct *Pin_Maps)
{
  uint8 i;
  uint8 dat = 0;
  IIC_Pin_In(Pin_Maps[1]);
  GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);               
  for (i=0; i<8; i++)         	//8λ������
  {
		dat <<= 1;	
    GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);             
    IIC_DelayUs(10);             	//��ʱ
    if(GPIO_ReadInputDataBit(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin))dat++;                 
    GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);              
    IIC_DelayUs(10);             
    
  }
  IIC_Pin_Out(Pin_Maps[1]);
  return dat;
}




/*******************************************************************************
 Func: ��IIC����д���� 
 Time: 2016-7-20
 Ver.: V1.0
 Note:
*******************************************************************************/
uint8 IIC_SendBytes(const GPIO_InitStruct *Pin_Maps,uint8 *TxBuffer,uint8 TxLenth)
{
  uint8 i,j,Ack,k=TxLenth;
  while(TxLenth)
  {           
		j=*TxBuffer++;
    for(i=0;i<8;i++,j<<=1)
    {
      if(j&0x80)GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
      else GPIO_ResetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
       GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);  IIC_DelayUs(10);
      GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin); IIC_DelayUs(10);       
    }
    GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin); 
	  GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);
		IIC_DelayUs(5);
		IIC_Pin_In(Pin_Maps[1]);
		IIC_DelayUs(5);
    Ack=GPIO_ReadInputDataBit(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
		IIC_DelayUs(5);
		IIC_Pin_Out(Pin_Maps[1]);
		IIC_DelayUs(5);     		
    GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);IIC_DelayUs(10);
    if(Ack)return (k-TxLenth);
		TxLenth--;
	}
  return k;
} 

/*******************************************************************************
 Func: ��IIC���߶����� 
 Time: 2016-7-20
 Ver.: V1.0
 Note:
*******************************************************************************/
uint8 IIC_RecvBytes(const GPIO_InitStruct *Pin_Maps,uint8 *RxBuffer,uint8 RxLenth)
{
   uint8 i,j=0x00,k=RxLenth;
	
   while(RxLenth--)
   {
      for(i=0,j=0;i<8;i++)
      {
		    j<<=1;
        GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);     
				IIC_DelayUs(5);
				IIC_Pin_In(Pin_Maps[1]);
				IIC_DelayUs(5);
        if(GPIO_ReadInputDataBit(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin))j|=0x01;
				IIC_DelayUs(5);
				IIC_Pin_Out(Pin_Maps[1]);
				IIC_DelayUs(5);
        GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);           
      }
      *RxBuffer++=j;
      if(RxLenth>0)IIC_SendAck(Pin_Maps,0);
      else IIC_SendAck(Pin_Maps,1);
   }
   return k;   
}


/*******************************************************************************
 Func: дIIC����
 Time: 2016-7-20
 Ver.: V1.0
 Note: return 0/����Ӧ   1/�������� 
*******************************************************************************/
uint8 IIC_WriteDatas(const GPIO_InitStruct *Pin_Maps,uint8 Addr,uint8 *Cmd,uint8 CmdLen,uint8 *TxBuffer,uint8 TxLenth)
{
   uint8 Ack;
   Addr<<=1;
   IIC_Start(Pin_Maps);
   Ack=IIC_SendBytes(Pin_Maps,&Addr,1);
   if(Ack==0){IIC_Drop(Pin_Maps); return 0;}
   Ack=IIC_SendBytes(Pin_Maps,Cmd,CmdLen);
   Ack=IIC_SendBytes(Pin_Maps,TxBuffer,TxLenth);
   IIC_Stop(Pin_Maps);
   return Ack;
}

/*******************************************************************************
 Func: ��IIC����
 Time: 2016-7-20
 Ver.: V1.0
 Note: return 0/����Ӧ  1/����
*******************************************************************************/
uint8 IIC_ReadDatas(const GPIO_InitStruct *Pin_Maps,uint8 Addr,uint8 *Cmd,uint8 CmdLen,uint8 *RxBuffer,uint8 RxLenth)
{
   uint8 Ack;
   Addr<<=1;
   if(CmdLen>0){
		IIC_Start(Pin_Maps);
   		Ack=IIC_SendBytes(Pin_Maps,&Addr,1);
   		if(Ack==0){IIC_Drop(Pin_Maps); return 0;}
   		Ack=IIC_SendBytes(Pin_Maps,Cmd,CmdLen);
   }
	 if(RxLenth>0)
	 {
		IIC_Start(Pin_Maps);
		Addr|=0x01;
		Ack=IIC_SendBytes(Pin_Maps,&Addr,1);
		Ack=IIC_RecvBytes(Pin_Maps,RxBuffer,RxLenth);   
	 }
	 IIC_Stop(Pin_Maps);
   return Ack;
}

