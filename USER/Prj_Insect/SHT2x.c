/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include "GPIO_Driver.h"
#include <..\USER\Prj_Insect\SHT2x.h>
#define SHT21ADDR 0x80

uint8 SHT21_Reset(const GPIO_InitStruct *IIC_Maps)
{
  uint8  error=0;       
  IIC_Start(IIC_Maps);
  error |= IIC_SendByte(IIC_Maps,0x80);
  error |= IIC_SendByte(IIC_Maps,0xfe);                      
  IIC_Stop(IIC_Maps);
  Tos_TaskDelay(100);
  return error;
}
uint8 SHT21_Config(const GPIO_InitStruct *IIC_Maps)
{
  uint8  error=0;       
  IIC_Start(IIC_Maps);
	IIC_SendByte(IIC_Maps,0x80);
	if(!IIC_SendByte(IIC_Maps,0xe6))
	{
		IIC_SendByte(IIC_Maps,0x83);
		IIC_Stop(IIC_Maps);
	}
  return error;
}
void SHT21Init(const GPIO_InitStruct *IIC_Maps)
{
	GPIO_InitList(IIC_Maps);
	SHT21_Reset(IIC_Maps);
	SHT21_Config(IIC_Maps);
}


void HHT21_Read(const GPIO_InitStruct *IIC_Maps,u8 *Buf)
{
  IIC_Start(IIC_Maps);
  IIC_SendByte(IIC_Maps,0x80);
  if(!IIC_SendByte(IIC_Maps,0xf5))
		{
			do
			{
				IIC_DelayUs(30);
				IIC_Start(IIC_Maps);	
				Tos_TaskDelay(10); 
			}while(IIC_SendByte(IIC_Maps,SHT21ADDR|0x01));
			Buf[0]=IIC_RecvByte(IIC_Maps);
			IIC_SendAck(IIC_Maps,0);
			Buf[1]=IIC_RecvByte(IIC_Maps);
			IIC_SendAck(IIC_Maps,0);
			Buf[2]=IIC_RecvByte(IIC_Maps);
			IIC_SendAck(IIC_Maps,1);
			IIC_Stop(IIC_Maps);
		}
  IIC_Start(IIC_Maps);
  IIC_SendByte(IIC_Maps,0x80);
  if(!IIC_SendByte(IIC_Maps,0xf3))
		{
			do
			{
				IIC_DelayUs(30);
				IIC_Start(IIC_Maps);
				Tos_TaskDelay(10); 				
			}while(IIC_SendByte(IIC_Maps,SHT21ADDR|0x01));
			Buf[3]=IIC_RecvByte(IIC_Maps);
			IIC_SendAck(IIC_Maps,0);
			Buf[4]=IIC_RecvByte(IIC_Maps);
			IIC_SendAck(IIC_Maps,0);
			Buf[5]=IIC_RecvByte(IIC_Maps);
			IIC_SendAck(IIC_Maps,1);
			IIC_Stop(IIC_Maps);
		}
}

float GetTemp(uint8 *Buf)
{
  float Value;
  uint16 t;
  t=Buf[0];
  t*=0xff;
  t|=Buf[1];
  t &= ~0x0003;     
  Value= -46.85 + 175.72/65536 *(float)t; 
  return Value;
}
float GetHmi(uint8 *Buf)
{
  float Value;
  uint16 t;
  t=Buf[0];
  t*=0xff;
  t|=Buf[1];
  t &= ~0x0003;       
  Value = -6.0 + 125.0/65536 * (float)t; 
  return Value;
}
const GPIO_InitStruct IIC_Maps[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,GPIO_Pin_15},
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_9},
	{0},
};

void TempHmi(void *Tags)
{
	uint8 Buf[15];
  SHT21Init(IIC_Maps);
	while(1)
	{
		Tos_TaskDelay(1000); 
		HHT21_Read(IIC_Maps,Buf);
	//	DeBug("湿度%.2f",GetHmi(&Buf[0]),0);
	//	DeBug("温度%.2f",GetTemp(&Buf[3]),0);
		BufferFill(Buf,0,10);
	}
}
