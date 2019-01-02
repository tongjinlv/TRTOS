#include <include.h>
uint8 DeviceId_W25Q16=DeviceNull;

#define X_MAX_PIXEL	        240
#define Y_MAX_PIXEL	        240

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


void SPI_Hand_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);
	SPI_SSOutputCmd(SPI1, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5 | GPIO_Pin_7 ;
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

void Lcd_WriteIndex(u8 d)
{
	SPI_SendByte(d,1);   
}
void Lcd_WriteData(u8 d)
{
	SPI_SendByte(d,0);   
}


 void LCD_WR_DATA8(u8 da)
{
	Lcd_WriteData(da);
}	  
void LCD_WR_REG(u8 da)	 
{	
	Lcd_WriteIndex(da);
}

void LCD_Init()
{
	
	SPI_FLASH_RST_LOW();
	Tos_TaskDelay(100); 
	SPI_FLASH_RST_HIGH();
	Tos_TaskDelay(100);
	SPI_FLASH_CS_LOW();
	Tos_TaskDelay(100);
	Tos_TaskDelay(100);
	//************* Start Initial Sequence **********// 
LCD_WR_REG(0x36); 
LCD_WR_DATA8(0x70);

LCD_WR_REG(0x3A); 
LCD_WR_DATA8(0x05);

LCD_WR_REG(0xB2);
LCD_WR_DATA8(0x0C);
LCD_WR_DATA8(0x0C);
LCD_WR_DATA8(0x00);
LCD_WR_DATA8(0x33);
LCD_WR_DATA8(0x33);

LCD_WR_REG(0xB7); 
LCD_WR_DATA8(0x35);  

LCD_WR_REG(0xBB);
LCD_WR_DATA8(0x19);

LCD_WR_REG(0xC0);
LCD_WR_DATA8(0x2C);

LCD_WR_REG(0xC2);
LCD_WR_DATA8(0x01);

LCD_WR_REG(0xC3);
LCD_WR_DATA8(0x12);   

LCD_WR_REG(0xC4);
LCD_WR_DATA8(0x20);  

LCD_WR_REG(0xC6); 
LCD_WR_DATA8(0x0F);    

LCD_WR_REG(0xD0); 
LCD_WR_DATA8(0xA4);
LCD_WR_DATA8(0xA1);

LCD_WR_REG(0xE0);
LCD_WR_DATA8(0xD0);
LCD_WR_DATA8(0x04);
LCD_WR_DATA8(0x0D);
LCD_WR_DATA8(0x11);
LCD_WR_DATA8(0x13);
LCD_WR_DATA8(0x2B);
LCD_WR_DATA8(0x3F);
LCD_WR_DATA8(0x54);
LCD_WR_DATA8(0x4C);
LCD_WR_DATA8(0x18);
LCD_WR_DATA8(0x0D);
LCD_WR_DATA8(0x0B);
LCD_WR_DATA8(0x1F);
LCD_WR_DATA8(0x23);

LCD_WR_REG(0xE1);
LCD_WR_DATA8(0xD0);
LCD_WR_DATA8(0x04);
LCD_WR_DATA8(0x0C);
LCD_WR_DATA8(0x11);
LCD_WR_DATA8(0x13);
LCD_WR_DATA8(0x2C);
LCD_WR_DATA8(0x3F);
LCD_WR_DATA8(0x44);
LCD_WR_DATA8(0x51);
LCD_WR_DATA8(0x2F);
LCD_WR_DATA8(0x1F);
LCD_WR_DATA8(0x1F);
LCD_WR_DATA8(0x20);
LCD_WR_DATA8(0x23);

LCD_WR_REG(0x21); 

LCD_WR_REG(0x11); 
//Delay (120); 

LCD_WR_REG(0x29); 
	
}
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{ 
	LCD_WR_REG(0x2a);
   LCD_WR_DATA8(x1>>8);
   LCD_WR_DATA8(x1);
   LCD_WR_DATA8(x2>>8);
   LCD_WR_DATA8(x2);
  
   LCD_WR_REG(0x2b);
   LCD_WR_DATA8(y1>>8);
   LCD_WR_DATA8(y1);
   LCD_WR_DATA8(y2>>8);
   LCD_WR_DATA8(y2);

   LCD_WR_REG(0x2C);					 						 
}
void Lcd_DrawBMP(u16 x_start,u16 y_start,const unsigned char  *Bmp)
{
	unsigned int w,h;
	uint8_t t;
	SPI_FLASH_CS_LOW();
	w=(uint16_t)Bmp[2]<<8|Bmp[3];
	h=(uint16_t)Bmp[4]<<8|Bmp[5];
	Address_set(x_start,y_start,x_start+w-1,y_start+h-1);
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
void Lcd_DrawBMPNull(u16 x_start,u16 y_start,const unsigned char  *Bmp)
{
	unsigned int w,h;
	uint8_t t;
	SPI_FLASH_CS_LOW();
	w=(uint16_t)Bmp[2]<<8|Bmp[3];
	h=(uint16_t)Bmp[4]<<8|Bmp[5];
	Address_set(x_start,y_start,x_start+w-1,y_start+h-1);
  Lcd_WriteIndex(0x2C);
	SPI_FLASH_RS_HIGH();
	w=h*w;
	h=8;
	while(w--)
	{
		t=Bmp[h++];
		SPI1->DR=0x00;
		t=Bmp[h++];
		SPI1->DR=0x00;
	}
	SPI_FLASH_CS_HIGH();
}
void Lcd_Clear(u8 Color)               
{	
   
   unsigned int i,m;
	 SPI_FLASH_CS_LOW();
   Address_set(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
	 SPI_FLASH_RS_HIGH();
   for(i=8;i<240*240*2;i++)
	 {
		 m=Color;
		 SPI1->DR =m;
		  m=Color;
		 SPI1->DR =m;
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

