/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_Lora\spi.h>
#include <GPIO_Driver.h>
#include <..\USER\Prj_Lora\ini.h>

#ifdef NEW_VERSION
const GPIO_InitStruct Pin_Maps[]=//新版本
{
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_11},//mosi
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOA,GPIO_Pin_10},//miso
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_12},//sck
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_8},//cs
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_13},//reset
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOB,GPIO_Pin_14},//rxtx
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOA,GPIO_Pin_0},//io0
	{0},
};
#else
const GPIO_InitStruct Pin_Maps[]=//旧版本
{
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_12},//mosi
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOA,GPIO_Pin_10},//miso
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_11},//sck
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOA,GPIO_Pin_8},//cs
	{GPIO_Speed_50MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_13},//reset
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOB,GPIO_Pin_14},//rxtx
	{GPIO_Speed_50MHz,GPIO_Mode_IPU,GPIOA,GPIO_Pin_9},//io0
	{0},
};
#endif

void SpiInit( void )
{
	GPIO_InitList(Pin_Maps);
	GPIO_SetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);//cs
	GPIO_SetBits(Pin_Maps[4].GPIOx,Pin_Maps[4].GPIO_Pin);//reset
	GPIO_SetBits(Pin_Maps[5].GPIOx,Pin_Maps[5].GPIO_Pin);//rxtx
	GPIO_SetBits(Pin_Maps[6].GPIOx,Pin_Maps[6].GPIO_Pin);//io0
}
void SX_Delay( uint8_t i )
{
	i*=10;
	while(i--);
}

uint8_t SpiInOut( uint8_t outData )
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		if(outData&0x80)GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);else GPIO_ResetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);
		outData<<=1;
		SX_Delay(1);
		GPIO_SetBits(Pin_Maps[2].GPIOx,Pin_Maps[2].GPIO_Pin);
		SX_Delay(1);
		if(GPIO_ReadInputDataBit(Pin_Maps[1].GPIOx,Pin_Maps[1].GPIO_Pin))outData|=0x01;else outData&=~0x01;
		GPIO_ResetBits(Pin_Maps[2].GPIOx,Pin_Maps[2].GPIO_Pin);
	  SX_Delay(1);
	}
	return outData;
}
uint8 ReadReg(uint8 add)
{
	uint8 t;
	GPIO_ResetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);
	SpiInOut(add);
	t=SpiInOut(0x00);
	GPIO_SetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);
	return t;
}
void WriteReg(uint8 add,uint8 value)
{
	GPIO_ResetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);
	SpiInOut(0x80|add);
	SpiInOut(value);
	GPIO_SetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);
}

u8 SPIRead(u8 adr)
{
  u8 tmp; 
	GPIO_ResetBits(Pin_Maps[2].GPIOx,Pin_Maps[2].GPIO_Pin);
  GPIO_ResetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);
  SpiInOut(adr);                                         //Send address first
  tmp = SpiInOut(0x00);  
  GPIO_ResetBits(Pin_Maps[2].GPIOx,Pin_Maps[2].GPIO_Pin);
  GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);
  GPIO_SetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);
  return(tmp);
}
void SPIWrite(uint16 WrPara)                
{                                                       

  GPIO_ResetBits(Pin_Maps[2].GPIOx,Pin_Maps[2].GPIO_Pin);
  GPIO_ResetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);
  
  WrPara |= 0x8000;                                        //MSB must be "1" for write 
	SpiInOut(WrPara>>8);
	SpiInOut(WrPara&0xff);
  GPIO_ResetBits(Pin_Maps[2].GPIOx,Pin_Maps[2].GPIO_Pin);
  GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);
  GPIO_SetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);
}
void SPIBurstRead(u8 adr, u8 *ptr, u8 length)
{
  u8 i;
	GPIO_ResetBits(Pin_Maps[2].GPIOx,Pin_Maps[2].GPIO_Pin);
	GPIO_ResetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);
	SpiInOut(adr); 
	for(i=0;i<length;i++)ptr[i] = SpiInOut(0x00);
	GPIO_ResetBits(Pin_Maps[2].GPIOx,Pin_Maps[2].GPIO_Pin);
  GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);
  GPIO_SetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);
}

void BurstWrite(u8 adr, u8 *ptr, u8 length)
{ 
  u8 i;
	GPIO_ResetBits(Pin_Maps[2].GPIOx,Pin_Maps[2].GPIO_Pin);
	GPIO_ResetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);       
	SpiInOut(adr|0x80);
	for(i=0;i<length;i++)
	SpiInOut(ptr[i]);
	GPIO_ResetBits(Pin_Maps[2].GPIOx,Pin_Maps[2].GPIO_Pin);
  GPIO_SetBits(Pin_Maps[0].GPIOx,Pin_Maps[0].GPIO_Pin);
  GPIO_SetBits(Pin_Maps[3].GPIOx,Pin_Maps[3].GPIO_Pin);
}
