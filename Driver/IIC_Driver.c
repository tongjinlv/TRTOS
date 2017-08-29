/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <include.h>
#include <IIC_driver.h>
#include <STM32_CPU.h>
//////妈妈的，没调好终于调好了，什么破协议，不标准
/*******************************************************************************
 Func: 延迟
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
 Func: 设置成输入方式
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
 Func: 启动IIC总线控制
*******************************************************************************/
void IIC_Start(const GPIO_InitStruct *Pin_Maps)
{   
	 GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
	 GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);IIC_DelayUs(10);   
	 GPIO_ResetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);IIC_DelayUs(10);  
	 GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);IIC_DelayUs(10);   
}

/*******************************************************************************
 Func: 停止IIC总线控制
*******************************************************************************/
void IIC_Stop(const GPIO_InitStruct *Pin_Maps)
{
   GPIO_ResetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin); 
   GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin); IIC_DelayUs(10);
   GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);IIC_DelayUs(30);
	 GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);IIC_DelayUs(20);
}


/*******************************************************************************
 Func: 释放IIC总线控制
*******************************************************************************/
void IIC_Drop(const GPIO_InitStruct *Pin_Maps)
{
	GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
	GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);
}


/*******************************************************************************
 Func: 发送ACK信号
*******************************************************************************/
void IIC_SendAck(const GPIO_InitStruct *Pin_Maps,uint8 Ack)
{
   if(Ack)GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
   else GPIO_ResetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);                   //发送ACK信号
   GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);IIC_DelayUs(10);
   GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);IIC_DelayUs(10); 
   GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin); 
}
/*******************************************************************************
 Func: 读取ACK信号 返回1位好
*******************************************************************************/
uint8 IIC_ReadAck(const GPIO_InitStruct *Pin_Maps)
{
	uint8 CY = 0x00;
  GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
  IIC_Pin_In(Pin_Maps[1]);
  GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);              //拉高时钟线
  IIC_DelayUs(10);                
  CY |= GPIO_ReadInputDataBit(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);    //读应答信号
  IIC_DelayUs(10);             
  GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);              //拉低时钟线
  IIC_Pin_Out(Pin_Maps[1]);
	return CY;
}

uint8 IIC_SendByte(const GPIO_InitStruct *Pin_Maps,uint8 dat)
{
  uint8 i;
  for (i=0; i<8; i++)         			//8位计数器
  {
    if (dat&0x80)	GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);
    else	GPIO_ResetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin) ;              //送数据口
    IIC_DelayUs(10);             			//延时
    GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);                		//拉高时钟线
    IIC_DelayUs(10);             			//延时
    GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);                		//拉低时钟线
    IIC_DelayUs(10);             			//延时
    dat <<= 1;              			//移出数据的最高位
  }
  return IIC_ReadAck(Pin_Maps);
}

uint8 IIC_RecvByte(const GPIO_InitStruct *Pin_Maps)
{
  uint8 i;
  uint8 dat = 0;
  IIC_Pin_In(Pin_Maps[1]);
  GPIO_SetBits(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin);               
  for (i=0; i<8; i++)         	//8位计数器
  {
		dat <<= 1;	
    GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);             
    IIC_DelayUs(10);             	//延时
    if(GPIO_ReadInputDataBit(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin))dat++;                 
    GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);              
    IIC_DelayUs(10);             
    
  }
  IIC_Pin_Out(Pin_Maps[1]);
  return dat;
}




/*******************************************************************************
 Func: 向IIC总线写数据 
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
 Func: 从IIC总线读数据 
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
 Func: 写IIC总线
 Time: 2016-7-20
 Ver.: V1.0
 Note: return 0/无响应   1/发送正常 
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
 Func: 读IIC总线
 Time: 2016-7-20
 Ver.: V1.0
 Note: return 0/无响应  1/正常
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

