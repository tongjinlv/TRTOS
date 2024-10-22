#include <include.h>
uint8 DeviceId_W25Q16=DeviceNull;

#define SPI_FLASH_RS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_3)
#define SPI_FLASH_RS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_3)

#define SPI_FLASH_CLK_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define SPI_FLASH_CLK_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_5)

#define SPI_FLASH_DAT_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define SPI_FLASH_DAT_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_7)

#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)
unsigned char const bmp1[]={
/*--  调入了一幅图像：D:\我的文档\My Pictures\12864-555.bmp  --*/
/*--  宽度x高度=128x64  --*/
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X80,0XC0,0XE0,0XE0,0XE0,0XC0,0XC0,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X80,0XE0,0XE0,0XF0,0XF8,
0XF8,0XF0,0XE0,0XC0,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XE0,0XF0,0XF0,0XF0,0XF0,0XE0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X80,0X80,0XC0,0XE0,0XF0,0XF0,0XF0,0XE0,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X70,0XF0,0XF0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XE0,0XE0,0XE0,0XE0,0XFC,
0XFF,0XFF,0XFF,0XE7,0XE1,0XE3,0XEF,0X1F,0X1F,0X0E,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X80,0XE0,0XE0,0XF8,0XF8,0XFE,0XFF,0X7F,0X3F,0X1F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X1F,0X3F,0X7F,0XFE,0XFC,0XF8,0XF0,0XE0,0XC0,0X00,0X00,0X00,0X00,
0XC0,0XE0,0XE0,0XE0,0XE0,0XC0,0X80,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X00,0X00,0X00,0X80,0XC0,0XE0,0XE0,0XE0,0XE0,0XC0,0X00,0X00,0X00,0X80,0XE0,0XE0,
0XF8,0XF8,0XFE,0XFE,0XFF,0XFF,0XFF,0XFF,0XE7,0XE3,0XC1,0X00,0XE0,0XE0,0XE0,0XE0,
0XC0,0X00,0XE0,0XE0,0XE0,0XE0,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XE1,0XFF,0XFF,
0XFF,0X3F,0X01,0X01,0XF9,0XFD,0XFC,0XFE,0X1E,0XFE,0XFC,0XFC,0XF0,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X03,0X03,0X03,0X03,0X01,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0X01,0X03,0X03,0X03,0X03,0X00,0X00,0X00,0X00,
0X00,0X01,0X03,0X0F,0X0F,0X1F,0X3F,0X7F,0XFE,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFC,0XFE,0X7F,0X3F,0X1F,0X0F,0X07,0X03,0X01,0X00,0X00,0X00,0X00,0X00,0X01,0X03,
0X07,0X0F,0X1F,0X3F,0X7F,0XFF,0XFF,0XFF,0XFB,0XF3,0XE1,0XC0,0X01,0X03,0X03,0X03,
0X01,0X00,0X71,0XFB,0XFB,0XFB,0X71,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0X07,0X07,
0X03,0X00,0X00,0X00,0X07,0X07,0X07,0X03,0X00,0X03,0X07,0X07,0X03,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0X07,0X0F,
0X07,0X07,0X03,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X07,0X07,0X0F,0X0F,0X07,0X03,
0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X03,0X07,0X07,0X03,0X01,0X00,0X00,0X00,0X00,
0X00,0X00,0X3C,0X3E,0X7E,0X3E,0X1C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0XC0,0XE0,0XF0,0XF8,
0XFC,0XFE,0XFE,0XFE,0XFC,0XF8,0XF0,0XE0,0XC0,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFC,0XFE,
0XFE,0XFE,0XFC,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0XC0,0XE0,0XF0,0XF8,0XFC,0XFC,0XFC,0X7C,
0X38,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X10,0X7C,0XFC,
0XFC,0XFC,0XF8,0XF0,0XE0,0XC0,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X60,0XF0,0XF8,0XFC,0XFE,0X7F,0X3F,0X1F,0X0F,0X07,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X07,0X07,0X0F,0X1F,0X3F,0XFF,0XFE,0XFC,0XF8,0XF0,0X60,
0X00,0X00,0X00,0X20,0XF8,0XF8,0XF8,0XF8,0XF0,0XE0,0XC0,0X80,0X00,0X00,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0X00,0X80,0XC0,0XE0,0XF0,0XF8,0XF8,0XF8,0XF8,0X70,0X00,0X00,
0X00,0X00,0X70,0XF8,0XFC,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF9,0XF8,0X70,
0X20,0XF8,0XF8,0XFC,0XF8,0X70,0X00,0X70,0XF8,0XFC,0XF8,0XF8,0X20,0X00,0X00,0X00,
0X00,0X00,0X78,0XF8,0XFC,0XF8,0XF8,0X00,0X70,0XF8,0XFC,0XFC,0XF8,0X70,0X00,0XF8,
0XF9,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XFC,0XF8,0X70,0X20,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X01,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X01,0X03,0X07,0X0F,0X1F,0X3F,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0X3F,0X1F,0X0F,0X07,0X03,0X01,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X01,0X03,0X07,0X0F,0X1F,0X3F,0X7F,0XFF,0XFF,0XFC,0XF8,0XF0,
0XE0,0X00,0X00,0X01,0X00,0X00,0X00,0X3C,0X3E,0XFE,0XFE,0X3C,0X18,0X00,0X00,0X00,
0X00,0X00,0X3C,0X3E,0XFE,0XFE,0X3C,0X08,0X00,0X00,0X01,0X01,0X00,0X40,0XF0,0XF8,
0XFC,0XFF,0XFF,0X7F,0X3F,0X1F,0X0F,0X07,0X03,0X01,0X00,0X00,0X00,0X00,0X00,0X80,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X03,0X03,0X03,0X03,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X03,
0X07,0X07,0X03,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X01,0X01,0X01,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0X1F,0X1F,0X1F,0X1F,0X06,0X00,0X00,0X00,
0X00,0X00,0X0F,0X1F,0X1F,0X1F,0X1F,0X04,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X01,
0X01,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
};
void SPI_Hand_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);
	SPI_SSOutputCmd(SPI1, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}
void SPI_Soft_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

u8 SPI_SendByte_(u8 data,uint8_t cmd)
{
	int i;
	if(cmd)SPI_FLASH_RS_LOW();
	else SPI_FLASH_RS_HIGH();
	for(i=0;i<8;i++)
   {
		 SPI_FLASH_CLK_LOW();
		if(data&0x80) {SPI_FLASH_DAT_HIGH();}
		else {SPI_FLASH_DAT_LOW();}
		SPI_FLASH_CLK_HIGH();
		__nop();;;
	 	data<<=1;
   }
	 return 0;
}
u8 SPI_SendByte(u8 data,uint8_t cmd)
{
	if(cmd)SPI_FLASH_RS_LOW();
	else SPI_FLASH_RS_HIGH();
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(SPI1, data);
}


void LCD_Init()
{
	SPI_FLASH_CS_LOW();
	SPI_SendByte(0xAE,1);   //display off
	SPI_SendByte(0x20,1);	//Set Memory Addressing Mode	
	SPI_SendByte(0x10,1);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	SPI_SendByte(0xb0,1);	//Set Page Start Address for Page Addressing Mode,0-7
	SPI_SendByte(0xc8,1);	//Set COM Output Scan Direction
	SPI_SendByte(0x00,1);//---set low column address
	SPI_SendByte(0x10,1);//---set high column address
	SPI_SendByte(0x40,1);//--set start line address
	SPI_SendByte(0x81,1);//--set contrast control register
	SPI_SendByte(0xFF,1);
	SPI_SendByte(0xa1,1);//--set segment re-map 0 to 127
	SPI_SendByte(0xa6,1);//--set normal display
	SPI_SendByte(0xa8,1);//--set multiplex ratio(1 to 64)
	SPI_SendByte(0x3F,1);//
	SPI_SendByte(0xa4,1);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	SPI_SendByte(0xd3,1);//-set display offset
	SPI_SendByte(0x00,1);//-not offset
	SPI_SendByte(0xd5,1);//--set display clock divide ratio/oscillator frequency
	SPI_SendByte(0xf0,1);//--set divide ratio
	SPI_SendByte(0xd9,1);//--set pre-charge period
	SPI_SendByte(0x22,1); //
	SPI_SendByte(0xda,1);//--set com pins hardware configuration
	SPI_SendByte(0x12,1);
	SPI_SendByte(0xdb,1);//--set vcomh
	SPI_SendByte(0x20,1);//0x20,0.77xVcc
	SPI_SendByte(0x8d,1);//--set DC-DC enable
	SPI_SendByte(0x14,1);//
	SPI_SendByte(0xaf,1);//--turn on oled panel 
	SPI_FLASH_CS_HIGH();
}
void LCD_Clear(uint16 c)
{
	unsigned char i,j;
	SPI_FLASH_CS_LOW();
	for(i=0;i<8;i++)
	{
		SPI_SendByte(0xb0+i,1);
		SPI_SendByte(0x00,1);
		SPI_SendByte(0x10,1);
		for(j=0;j<128;j++)
		{
		  	SPI_SendByte(c,0);
		}
	}
	SPI_FLASH_CS_HIGH();
}
void LCD_Show(const uint8_t *Bmp)
{
	unsigned char i,j;
	int z=0;
	SPI_FLASH_CS_LOW();
	for(i=0;i<8;i++)
	{
		SPI_SendByte(0xb0+i,1);
		SPI_SendByte(0x00,1);
		SPI_SendByte(0x10,1);
		for(j=0;j<128;j++)
		{
		  	SPI_SendByte(Bmp[z++],0);
		}
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

