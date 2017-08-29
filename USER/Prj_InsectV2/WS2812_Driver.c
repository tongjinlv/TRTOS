/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <WS2812_Driver.h>

void WS2812_Delay(uint16 u)
{
	while(u--);
}
uint32 BRG_RGB(uint32 C)//绿红蓝   -》红绿蓝
{
	
	uint16 R,G,B;
	G=C>>16;
	R=(C>>8)&0xff;
	B=C&0xff;
	C=R;C<<=8;
	C|=G;C<<=8;
	C|=B;
	return C;
}
uint32 RGB_Light(uint32 C,uint8 Blv)
{
	
	uint16 R,G,B;
	R=C>>16;
	G=(C>>8)&0xff;
	B=C&0xff;
	R=R*Blv/0xff;
	G=G*Blv/0xff;
	B=B*Blv/0xff;
	C=R;C<<=8;
	C|=G;C<<=8;
	C|=B;
	return C;
}
//void WS2812_WriteList(GPIO_TypeDef *GPIOx,uint16_t Port,uint32 *Data,uint8 Length)
//{
//	uint8 c;
//	uint16 x,y;
//	uint32 T;
//	DIS_INT;
//	for(x=0;x<Length;x++)
//	{
//		T=BRG_RGB(*Data++);
//		for(y=0;y<24;y++)
//		{
//			if(T&S23)
//			{
//				GPIOx->BSRRH=Port;
//				WS2812_Delay(2);
//				GPIOx->BSRRL=Port;
//				WS2812_Delay(1);
//				c<<=1;
//			}else
//			{
//				GPIOx->BSRRH=Port;
//				WS2812_Delay(1);
//				GPIOx->BSRRL=Port;
//				WS2812_Delay(2);
//			}
//			T<<=1;
//		}
//	}
//	EN_INT;
//}

void WS2812_WriteList(GPIO_TypeDef *GPIOx,uint16_t Port,uint32 *Data,uint8 Length)
{
	#define Q {GPIOx->BSRRH=Port;c=1;while(c--);GPIOx->BSRRL=Port;c=3;while(c--);}
  #define G {GPIOx->BSRRH=Port;c=3;while(c--);GPIOx->BSRRL=Port;c=1;while(c--);}
	uint8 c;
	uint8 x,y;
	uint32 T;
		BOOL dd[25];
	DIS_INT;
	for(x=0;x<24;x++)dd[x]=0;
	for(x=0;x<Length;x++)
	{
		T=BRG_RGB(*Data++);
		
		
		
		
		Q Q Q Q   Q Q Q Q
		
		Q Q Q Q   Q Q Q Q
		G G G G   G G G G
		
	}
	EN_INT;
}
void WS2812_Write(uint32 *List)
{
	WS2812_WriteList(GPIOB,GPIO_Pin_15,&List[0],1);
	//WS2812_WriteList(GPIOA,GPIO_Pin_12,&List[1],3);
}
void WS2812_Close()
{
	uint32 Buf[]={0x00,0x00,0x00,0x00};
	WS2812_Write(Buf);
}
void WS2812_Open()
{
	uint32 Buf[]={0x00,0x0,0xffffff,0xffffff};
	WS2812_Write(Buf);
}

void Test(uint8 i)
{
	static uint8 L=12;
	uint32 Buf[]={0x00,0x00,0x00,0x00};
	Buf[2]=RGB_Light(0xEDD0E1,L++);
	Buf[3]=RGB_Light(0xEDD0E1,L++);
	WS2812_Write(Buf);
Tos_TaskDelay(100);
	Buf[2]=0;
	Buf[3]=0;

WS2812_Write(Buf);
Tos_TaskDelay(200);
	Buf[2]=RGB_Light(0xEDD0E1,L++);
	Buf[3]=RGB_Light(0xEDD0E1,L++);
	WS2812_Write(Buf);
Tos_TaskDelay(10);
	Buf[2]=0;
	Buf[3]=0;
WS2812_Write(Buf);
Tos_TaskDelay(1000);
}
void TestStart()
{
	uint32 Buf[]={0x00,0x00,0x00,0x00};
	Buf[2]=RGB_Light(0xffffff,0xff);
	Buf[3]=RGB_Light(0xffffff,0xff);
	Buf[0]=RGB_Light(0xffffff,0xff);
	Buf[1]=RGB_Light(0xffffff,0xff);
	WS2812_Write(Buf);
	Tos_TaskDelay(300);
	Buf[2]=0;
	Buf[3]=0;

WS2812_Write(Buf);
Tos_TaskDelay(300);
	Buf[2]=RGB_Light(0xff0000,0xff);
	Buf[3]=RGB_Light(0xff0000,0xff);
	WS2812_Write(Buf);
	Tos_TaskDelay(300);
	Buf[2]=0;
	Buf[3]=0;
	Buf[0]=RGB_Light(0xffffff,0);
	Buf[1]=RGB_Light(0xffffff,0);
WS2812_Write(Buf);
}
void WS_Double()
{
	uint32 Buf[]={0x00,0x00,0x00,0x00};
	Buf[2]=RGB_Light(0xffffff,0xff);
	Buf[3]=RGB_Light(0xffffff,0xff);
	WS2812_Write(Buf);
	Tos_TaskDelay(200);
	Buf[2]=0x0;
	Buf[3]=0x0;
	WS2812_Write(Buf);
	Tos_TaskDelay(200);
	Buf[2]=RGB_Light(0xffffff,0xff);
	Buf[3]=RGB_Light(0xffffff,0xff);
	WS2812_Write(Buf);
	Tos_TaskDelay(200);
	Buf[2]=RGB_Light(0x0,0xff);
	Buf[3]=RGB_Light(0x0,0xff);
	WS2812_Write(Buf);
}

