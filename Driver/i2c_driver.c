/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <include.h>
#include <i2c_driver.h>


void delay_us(uint16 us)
{
	us>>=2;
	while(us--);
}

/*********************************************************************************************************
 Func: ����I2C����
*********************************************************************************************************/
void I2C_Start(I2C_HOST_IO_CONTROL I2C_IOCON)
{   
   I2C_IOCON(I2C_HOST_SCL_SET);   delay_us(5);           //��SCL�ĸߵ�ƽ�ڼ�SDA�߲���һ��������     
   I2C_IOCON(I2C_HOST_SDA_SET);   delay_us(10);
   I2C_IOCON(I2C_HOST_SDA_CLR);   delay_us(10);
   I2C_IOCON(I2C_HOST_SCL_CLR);   delay_us(10);          //����ռ������Ȩ          
}

/*********************************************************************************************************
 Func: ֹͣI2C���߿���
*********************************************************************************************************/
void I2C_Stop(I2C_HOST_IO_CONTROL I2C_IOCON)
{
   I2C_IOCON(I2C_HOST_SDA_CLR);   delay_us(20);          //��SCL�ĸߵ��ڼ�SDA�߲���һ��������
   I2C_IOCON(I2C_HOST_SCL_SET);   delay_us(10);
   I2C_IOCON(I2C_HOST_SDA_SET);   delay_us(30);
}


/*********************************************************************************************************
 Func: �ͷ�I2C���߿���
*********************************************************************************************************/
void I2C_Drop(I2C_HOST_IO_CONTROL I2C_IOCON)
{
	I2C_IOCON(I2C_HOST_SDA_SET);
	I2C_IOCON(I2C_HOST_SCL_SET);
}


/*********************************************************************************************************
 Func: ����ACK�ź�
*********************************************************************************************************/
void I2C_SendAck(I2C_HOST_IO_CONTROL I2C_IOCON,uint8 Ack)
{
   if(Ack)I2C_IOCON(I2C_HOST_SDA_SET);
   else   I2C_IOCON(I2C_HOST_SDA_CLR);                   //����ACK�ź�
   I2C_IOCON(I2C_HOST_SCL_SET);   delay_us(10);
   I2C_IOCON(I2C_HOST_SCL_CLR);   delay_us(10); 
   I2C_IOCON(I2C_HOST_SDA_SET); 
}

/*********************************************************************************************************
 Func: ��I2C����д���� 
 Time: 2010-7-20
 Ver.: V1.0
 Note:
*********************************************************************************************************/
uint8 I2C_SendBytes(I2C_HOST_IO_CONTROL I2C_IOCON,uint8 *TxBuffer,uint8 TxLenth)
{
  uint8 i,j,Ack,k=TxLenth;
  while(TxLenth)
  {           
	j=*TxBuffer++;
    for(i=0;i<8;i++,j<<=1)
    {
      if(j&0x80)I2C_IOCON(I2C_HOST_SDA_SET);
      else      I2C_IOCON(I2C_HOST_SDA_CLR);
      I2C_IOCON(I2C_HOST_SCL_SET);     delay_us(10);
      I2C_IOCON(I2C_HOST_SCL_CLR);     delay_us(10);       
    }
    I2C_IOCON(I2C_HOST_SDA_SET); 
	I2C_IOCON(I2C_HOST_SCL_SET);       delay_us(10);
    Ack=I2C_IOCON(I2C_HOST_SDA_DAT);   delay_us(10);        		
    I2C_IOCON(I2C_HOST_SCL_CLR);       delay_us(10);
    if(Ack)return (k-TxLenth);
		TxLenth--;
	}
  return k;
} 

/*********************************************************************************************************
 Func: ��I2C���߶����� 
 Time: 2010-7-20
 Ver.: V1.0
 Note:
*********************************************************************************************************/
uint8 I2C_RecvBytes(I2C_HOST_IO_CONTROL I2C_IOCON,uint8 *RxBuffer,uint8 RxLenth)
{
   uint8 i,j,k=RxLenth;
   while(RxLenth--)
   {
      for(i=0,j=0;i<8;i++)
      {
		j<<=1;
        I2C_IOCON(I2C_HOST_SCL_SET);     delay_us(10);
        if(I2C_IOCON(I2C_HOST_SDA_DAT))j|=0x01;
        I2C_IOCON(I2C_HOST_SCL_CLR);     delay_us(10);        
      }
      *RxBuffer++=j;
      if(RxLenth>0)I2C_SendAck(I2C_IOCON,0);
      else I2C_SendAck(I2C_IOCON,1);
   }   
   return k;   
}


/*********************************************************************************************************
 Func: дI2C����
 Time: 2010-7-20
 Ver.: V1.0
 Note: return 0/����Ӧ   1/�������� 
*********************************************************************************************************/
uint8 I2C_WriteDatas(I2C_HOST_IO_CONTROL I2C_IOCON,uint8 Addr,uint8 *Cmd,uint8 CmdLen,uint8 *TxBuffer,uint8 TxLenth)
{
   uint8 Ack;
   Addr<<=1;
   I2C_Start(I2C_IOCON);
   Ack=I2C_SendBytes(I2C_IOCON,&Addr,1);
   if(Ack==0){I2C_Drop(I2C_IOCON); return 0;}
   Ack=I2C_SendBytes(I2C_IOCON,Cmd,CmdLen);
   Ack=I2C_SendBytes(I2C_IOCON,TxBuffer,TxLenth);
   I2C_Stop(I2C_IOCON);
   return Ack;
}

/*********************************************************************************************************
 Func: ��I2C����
 Time: 2010-7-20
 Ver.: V1.0
 Note: return 0/����Ӧ  1/����
*********************************************************************************************************/
uint8 I2C_ReadDatas(I2C_HOST_IO_CONTROL I2C_IOCON,uint8 Addr,uint8 *Cmd,uint8 CmdLen,uint8 *RxBuffer,uint8 RxLenth)
{
   uint8 Ack;
   Addr<<=1;
   if(CmdLen>0){
		I2C_Start(I2C_IOCON);
   		Ack=I2C_SendBytes(I2C_IOCON,&Addr,1);
   		if(Ack==0){I2C_Drop(I2C_IOCON); return 0;}
   		Ack=I2C_SendBytes(I2C_IOCON,Cmd,CmdLen);
   }
   I2C_Start(I2C_IOCON);
   Addr|=0x01;
   Ack=I2C_SendBytes(I2C_IOCON,&Addr,1);
   Ack=I2C_RecvBytes(I2C_IOCON,RxBuffer,RxLenth);   
   I2C_Stop(I2C_IOCON);
   return Ack;
}

