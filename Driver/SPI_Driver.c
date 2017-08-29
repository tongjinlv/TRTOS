/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <SPI_Driver.h>
#include <GPIO_Driver.h>

uint8 DeviceId_SPI=DeviceNull;

const GPIO_InitStruct *SPIPin_Maps;

const GPIO_InitStruct Pin_Maps_Sample[]=//新版本
{
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_11},//【0】mosi
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOA,GPIO_Pin_10},//【1】miso
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_12},//【2】sck
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_8},//【3】cs
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_13},//【4】reset
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOB,GPIO_Pin_14},//【5】rxtx
	{0},
};

void Spi_Init(GPIO_InitStruct *Tags)
{
	SPIPin_Maps=Tags;
	GPIO_InitList(SPIPin_Maps);
	GPIO_SetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);//cs
	GPIO_SetBits(SPIPin_Maps[4].GPIOx,SPIPin_Maps[4].GPIO_Pin);//reset
	GPIO_SetBits(SPIPin_Maps[5].GPIOx,SPIPin_Maps[5].GPIO_Pin);//rxtx
}
void Spi_Delay( uint8 i )
{
	i*=10;
	while(i--);
}

uint8 Spi_InOut( uint8 outData )
{
	uint8 i;
	for(i=0;i<8;i++)
	{
		if(outData&0x80)GPIO_SetBits(SPIPin_Maps[0].GPIOx,SPIPin_Maps[0].GPIO_Pin);else GPIO_ResetBits(SPIPin_Maps[0].GPIOx,SPIPin_Maps[0].GPIO_Pin);
		outData<<=1;
		Spi_Delay(1);
		GPIO_SetBits(SPIPin_Maps[2].GPIOx,SPIPin_Maps[2].GPIO_Pin);
		Spi_Delay(1);
		if(GPIO_ReadInputDataBit(SPIPin_Maps[1].GPIOx,SPIPin_Maps[1].GPIO_Pin))outData|=0x01;else outData&=~0x01;
		GPIO_ResetBits(SPIPin_Maps[2].GPIOx,SPIPin_Maps[2].GPIO_Pin);
	  Spi_Delay(1);
	}
	return outData;
}
uint8 Spi_ReadReg(uint8 add)
{
	uint8 t;
	GPIO_ResetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);
	Spi_InOut(add);
	t=Spi_InOut(0x00);
	GPIO_SetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);
	return t;
}
void Spi_WriteReg(uint8 add,uint8 value)
{
	GPIO_ResetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);
	Spi_InOut(0x80|add);
	Spi_InOut(value);
	GPIO_SetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);
}

uint8 Spi_Read(uint8 adr)
{
  uint8 tmp; 
	GPIO_ResetBits(SPIPin_Maps[2].GPIOx,SPIPin_Maps[2].GPIO_Pin);
  GPIO_ResetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);
  Spi_InOut(adr);                                        
  tmp = Spi_InOut(0x00);  
  GPIO_ResetBits(SPIPin_Maps[2].GPIOx,SPIPin_Maps[2].GPIO_Pin);
  GPIO_SetBits(SPIPin_Maps[0].GPIOx,SPIPin_Maps[0].GPIO_Pin);
  GPIO_SetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);
  return(tmp);
}
void Spi_Write(uint16 WrPara)                
{                                                       

  GPIO_ResetBits(SPIPin_Maps[2].GPIOx,SPIPin_Maps[2].GPIO_Pin);
  GPIO_ResetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);
  WrPara |= 0x8000;                                        
	Spi_InOut(WrPara>>8);
	Spi_InOut(WrPara&0xff);
  GPIO_ResetBits(SPIPin_Maps[2].GPIOx,SPIPin_Maps[2].GPIO_Pin);
  GPIO_SetBits(SPIPin_Maps[0].GPIOx,SPIPin_Maps[0].GPIO_Pin);
  GPIO_SetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);
}
void SpiReads(uint8 adr, uint8 *ptr, uint8 length)
{
  uint8 i;
	GPIO_ResetBits(SPIPin_Maps[2].GPIOx,SPIPin_Maps[2].GPIO_Pin);
	GPIO_ResetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);
	Spi_InOut(adr); 
	for(i=0;i<length;i++)ptr[i] = Spi_InOut(0x00);
	GPIO_ResetBits(SPIPin_Maps[2].GPIOx,SPIPin_Maps[2].GPIO_Pin);
  GPIO_SetBits(SPIPin_Maps[0].GPIOx,SPIPin_Maps[0].GPIO_Pin);
  GPIO_SetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);
}

void Spi_Writes(uint8 adr, uint8 *ptr, uint8 length)
{ 
  uint8 i;
	GPIO_ResetBits(SPIPin_Maps[2].GPIOx,SPIPin_Maps[2].GPIO_Pin);
	GPIO_ResetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);       
	Spi_InOut(adr|0x80);
	for(i=0;i<length;i++)
	Spi_InOut(ptr[i]);
	GPIO_ResetBits(SPIPin_Maps[2].GPIOx,SPIPin_Maps[2].GPIO_Pin);
  GPIO_SetBits(SPIPin_Maps[0].GPIOx,SPIPin_Maps[0].GPIO_Pin);
  GPIO_SetBits(SPIPin_Maps[3].GPIOx,SPIPin_Maps[3].GPIO_Pin);
}
void DeviceMount_SPI(const GPIO_InitStruct *List)
{
	DeviceId_SPI=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_SPI].DeviceId=DeviceId_SPI;
	Tos_Device_Tab[DeviceId_SPI].DeviceName="SPI";
	Tos_Device_Tab[DeviceId_SPI].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_SPI].DeviceVirtue=DV_IOList;
	Tos_Device_Tab[DeviceId_SPI].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_SPI].Init=Spi_Init;
	Tos_Device_Tab[DeviceId_SPI].Note=(uintbus)List;
	Tos_Device_Tab[DeviceId_SPI].Write=Null;
	Tos_Device_Tab[DeviceId_SPI].Read=Null;
	Tos_Device_Tab[DeviceId_SPI].Exit=Null;
}

//void SPI_Delay(uint16 i)
//{
//	while(i--);
//}
//uint8 SPI_WR(const SPI_PublicStruct *SPI,uint8 Data)
//{
//	uint8 i,Temp=0x00;
//	for(i=0;i<8;i++)
//	{
//		Temp<<=1;
//		if(Data&0x80)SPI->MOSI(True);else SPI->MOSI(False);
//		if(SPI->MISO())Temp|=0x01;
//		Data<<=1;
//		SPI_Delay(SPI->Delay);
//		SPI->SCLK(True);
//		SPI_Delay(SPI->Delay);
//		SPI->SCLK(False);
//	  SPI_Delay(SPI->Delay);
//	}
//	return Temp;
//}
//uint8 SPI_WriteReg(const SPI_PublicStruct *SPI,uint8 reg,uint8 dat)
//{
//	uint8 status;
//	SPI->CE(False);
//	SPI->CSN(False);
//	status = SPI_WR(SPI,reg);
//	SPI_WR(SPI,dat);        
//	SPI->CSN(True);	
//	return(status);
//}
//uint8 SPI_ReadReg(const SPI_PublicStruct *SPI,uint8 reg,uint8 dat)
//{
//	uint8 reg_val;
//	SPI->CE(False);
//	SPI->CSN(False);
//	SPI_WR(SPI,reg); 
//	reg_val =SPI_WR(SPI,0xff);
//	SPI->CSN(True);		
//	return reg_val;
//}
//uint8 SPI_ReadBuf(const SPI_PublicStruct *SPI,uint8 reg,uint8 *pBuf,uint8 LCEgth)
//{
// 	uint8 status, byte_cnt;
//	SPI->CE(False);
//	SPI->CSN(False);
//	status =SPI_WR(SPI,reg); 
//	for(byte_cnt=0;byte_cnt<LCEgth;byte_cnt++)		  
//	pBuf[byte_cnt] = SPI_WR(SPI,0xff); //从NRF24L01读取数据  
//	SPI->CSN(True);			
// 	return status;		//返回寄存器状态值
//}
//uint8 SPI_WriteBuf(const SPI_PublicStruct *SPI,uint8 reg ,uint8 *pBuf,uint8 LCEgth)
//{
//	uint8 status,byte_cnt;
//	SPI->CE(False);
//	SPI->CSN(False);
//	status =SPI_WR(SPI,reg); 
//	for(byte_cnt=0;byte_cnt<LCEgth;byte_cnt++)
//	SPI_WR(SPI,*pBuf++);	//写数据到缓冲区 	 
//	SPI->CSN(True);				
//	return (status);	//返回NRF24L01的状态 		
//}
