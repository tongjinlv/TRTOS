#include <include.h>
uint8 DeviceId_W25Q16=DeviceNull;

#define X_MAX_PIXEL	        160
#define Y_MAX_PIXEL	        80

#define SPI_FLASH_CLK_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define SPI_FLASH_CLK_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_5)

#define SPI_FLASH_DAT_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define SPI_FLASH_DAT_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_7)

#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)

#define SPI_FLASH_RST_LOW()       GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define SPI_FLASH_RST_HIGH()      GPIO_SetBits(GPIOB, GPIO_Pin_0)

#define SPI_FLASH_RS_LOW()       GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define SPI_FLASH_RS_HIGH()      GPIO_SetBits(GPIOB, GPIO_Pin_1)

#define SPI_FLASH_BL_LOW()       GPIO_ResetBits(GPIOB, GPIO_Pin_10)
#define SPI_FLASH_BL_HIGH()      GPIO_SetBits(GPIOB, GPIO_Pin_10)

void SPI_Hand_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);
	SPI_SSOutputCmd(SPI1, ENABLE);
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_10 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}
void SPI_Delay(uint32_t i)
{
	while(i--);
}
u8 SPI_SendByte(u8 data,uint8_t cmd)
{
	if(cmd)SPI_FLASH_RS_LOW();
	else SPI_FLASH_RS_HIGH();
	SPI_Delay(10); 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(SPI1, data);
	SPI_Delay(10); 
}
u8 SPI_SendByteND(u8 data,uint8_t cmd)
{

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(SPI1, data);
}
void Lcd_WriteIndex(u8 d)
{
	SPI_SendByte(d,1);   
}
void Lcd_WriteData(u8 d)
{
	SPI_SendByte(d,0);   
}
void LCD_WriteData_16Bit(u16 Data)
{
	 Lcd_WriteData(Data>>8); 	//写入高8位数据
	 Lcd_WriteData(Data); 			//写入低8位数据

}
void LCD_Init()
{
	SPI_FLASH_BL_HIGH();
	SPI_FLASH_RST_LOW();
	Tos_TaskDelay(100); 
	SPI_FLASH_RST_HIGH();
	Tos_TaskDelay(100);
	SPI_FLASH_CS_LOW();
	Tos_TaskDelay(1);
	Lcd_WriteIndex(0x11);//Sleep exit 
	Tos_TaskDelay(100);
	Lcd_WriteIndex(0x21); 
	Lcd_WriteIndex(0x21); 
	Lcd_WriteIndex(0xB1); 
	Lcd_WriteData(0x05);
	Lcd_WriteData(0x3A);
	Lcd_WriteData(0x3A);
	Lcd_WriteIndex(0xB2);
	Lcd_WriteData(0x05);
	Lcd_WriteData(0x3A);
	Lcd_WriteData(0x3A);
	Lcd_WriteIndex(0xB3); 
	Lcd_WriteData(0x05);  
	Lcd_WriteData(0x3A);
	Lcd_WriteData(0x3A);
	Lcd_WriteData(0x05);
	Lcd_WriteData(0x3A);
	Lcd_WriteData(0x3A);
	Lcd_WriteIndex(0xB4);
	Lcd_WriteData(0x03);
	Lcd_WriteIndex(0xC0);
	Lcd_WriteData(0x62);
	Lcd_WriteData(0x02);
	Lcd_WriteData(0x04);
	Lcd_WriteIndex(0xC1);
	Lcd_WriteData(0xC0);
	Lcd_WriteIndex(0xC2);
	Lcd_WriteData(0x0D);
	Lcd_WriteData(0x00);
	Lcd_WriteIndex(0xC3);
	Lcd_WriteData(0x8D);
	Lcd_WriteData(0x6A);   
	Lcd_WriteIndex(0xC4);
	Lcd_WriteData(0x8D); 
	Lcd_WriteData(0xEE); 
	Lcd_WriteIndex(0xC5);  /*VCOM*/
	Lcd_WriteData(0x0E);    
	Lcd_WriteIndex(0xE0);
	Lcd_WriteData(0x10);
	Lcd_WriteData(0x0E);
	Lcd_WriteData(0x02);
	Lcd_WriteData(0x03);
	Lcd_WriteData(0x0E);
	Lcd_WriteData(0x07);
	Lcd_WriteData(0x02);
	Lcd_WriteData(0x07);
	Lcd_WriteData(0x0A);
	Lcd_WriteData(0x12);
	Lcd_WriteData(0x27);
	Lcd_WriteData(0x37);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x0D);
	Lcd_WriteData(0x0E);
	Lcd_WriteData(0x10);
	Lcd_WriteIndex(0xE1);
	Lcd_WriteData(0x10);
	Lcd_WriteData(0x0E);
	Lcd_WriteData(0x03);
	Lcd_WriteData(0x03);
	Lcd_WriteData(0x0F);
	Lcd_WriteData(0x06);
	Lcd_WriteData(0x02);
	Lcd_WriteData(0x08);
	Lcd_WriteData(0x0A);
	Lcd_WriteData(0x13);
	Lcd_WriteData(0x26);
	Lcd_WriteData(0x36);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x0D);
	Lcd_WriteData(0x0E);
	Lcd_WriteData(0x10);
	Lcd_WriteIndex(0x3A); 
	Lcd_WriteData(0x05);
	Lcd_WriteIndex(0x36);
	Lcd_WriteData(0xA8);//
	Lcd_WriteIndex(0x29); 
	SPI_FLASH_CS_HIGH();
}
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end)
{		
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+1);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+1);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+0x1A);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+0x1A);	
	Lcd_WriteIndex(0x2c);
}
void Lcd_DrawBMP(u16 x_start,u16 y_start,const unsigned char  *Bmp)
{
	unsigned int w,h;
	uint8_t t;
	SPI_FLASH_CS_LOW();
	w=(uint16_t)Bmp[2]<<8|Bmp[3];
	h=(uint16_t)Bmp[4]<<8|Bmp[5];
	Lcd_SetRegion(x_start,y_start,x_start+w-1,y_start+h-1);
  Lcd_WriteIndex(0x2C);
	SPI_FLASH_RS_HIGH();
	w=h*w;
	h=8;
	while(w--)
	{
		t=Bmp[h++];
		SPI1->DR=t;
		t=Bmp[h++];
		SPI1->DR=t;
	}
	SPI_FLASH_CS_HIGH();
}
void Lcd_Clear(u8 Color)               
{	
   
   unsigned int i,m;
	 SPI_FLASH_CS_LOW();
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
	 SPI_FLASH_RS_HIGH();
   for(i=8;i<25608;i++)
	 {
		 SPI1->DR =Color;
	 }		 
	 SPI_FLASH_CS_HIGH();
}
void DeviceMount_LCD()
{
	DeviceId_W25Q16=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_W25Q16].DeviceName="LCD";
	Tos_Device_Tab[DeviceId_W25Q16].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_W25Q16].DeviceVirtue=DV_Task;
	Tos_Device_Tab[DeviceId_W25Q16].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_W25Q16].Init=SPI_Hand_Init;
	Tos_Device_Tab[DeviceId_W25Q16].Note=Null;
	Tos_Device_Tab[DeviceId_W25Q16].Exit=Null;
}

