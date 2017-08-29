/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
//***************************************
// B_LUX_V20采集程序
//****************************************

#include <B_LUX_V20.h>

void IIC_WriteCmd(const GPIO_InitStruct *Pin_Maps,uint8 REG_Address)
{
  IIC_Start(Pin_Maps);                
  IIC_SendByte(Pin_Maps,B_LUX_Addr);  
  IIC_SendByte(Pin_Maps,REG_Address);  
  IIC_Stop(Pin_Maps);                  
}

uint32 IIC_Reads(const GPIO_InitStruct *Pin_Maps)
{   
  uint8 i;	
	uint8    BUF_0[4];                       //接收数据缓存区      	
	uint16   dis_data_0;   
	uint32 temp;
  IIC_Start(Pin_Maps);                          //起始信号
  IIC_SendByte(Pin_Maps,B_LUX_Addr+1);        //发送设备地址+读信号
  for (i=0; i<3; i++)                        //连续读取6个地址数据，存储中BUF
  {
    BUF_0[i] = IIC_RecvByte(Pin_Maps);          //BUF[0]存储0x32地址中的数据
    if (i == 3)
    {
      IIC_SendAck(Pin_Maps,1);                   //最后一个数据需要回NOACK
    }
    else
    {		
      IIC_SendAck(Pin_Maps,0);                   //回应ACK
    }
  }
  IIC_Stop(Pin_Maps);                           //停止信号
  Tos_TaskDelay(5);
	dis_data_0=BUF_0[0];
  dis_data_0=(dis_data_0<<8)+BUF_0[1];
  temp=(float)dis_data_0/1.2;
  return (uint32)(temp*1.4);
}

void B_LUX_Init(const GPIO_InitStruct *List)
{
  GPIO_InitList(List);
  Tos_TaskDelay(300);	  
  IIC_WriteCmd(List,0x01); 
}

uint32 B_LUX_GetLux(const GPIO_InitStruct *List)
{  
  uint32 temp;
  IIC_WriteCmd(List,0x01);   
  IIC_WriteCmd(List,0x10);  
  Tos_TaskDelay(180);     
  temp=IIC_Reads(List);     
  IIC_WriteCmd(List,0x00);   
  return temp;
} 
