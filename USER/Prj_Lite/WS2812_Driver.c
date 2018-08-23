/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <WS2812_Driver.h>
/*******************************************************************************
Func:WS延迟函数
Date:2016-12-29
Note:
*******************************************************************************/
void WS_Delay(uint16 u)
{
	while(u--);
}
/*******************************************************************************
Func://绿红蓝   -》红绿蓝
Date:2016-12-29
Note:
*******************************************************************************/
uint32 BRG_RGB(uint32 C)
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
/*******************************************************************************
Func:亮度
Date:2016-12-29
Note:
*******************************************************************************/
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
/*******************************************************************************
Func:一次性写入
Date:2016-12-29
Note:
*******************************************************************************/
void WS_WriteList(GPIO_TypeDef *GPIOx,uint16_t Port,uint32 *Data,uint8 Length)
{
	uint16 x,y;
	uint32 T;
	DIS_INT;
	for(x=0;x<Length;x++)
	{
		T=BRG_RGB(*Data++);
		for(y=0;y<24;y++)
		{
			if(T&S23)
			{
				GPIOx->BSRR=Port;
				WS_Delay(5);
				GPIOx->BRR=Port;
				WS_Delay(1);
			}else
			{
				GPIOx->BSRR=Port;
				WS_Delay(1);
				GPIOx->BRR=Port;
				WS_Delay(5);
			}
			T<<=1;
		}
	}
	EN_INT;
}
/*******************************************************************************
Func:亮度
Date:2016-12-29
Note:
*******************************************************************************/
void WS_Write(uint32 *List)
{
	WS_WriteList(GPIOB,GPIO_Pin_15,&List[0],1);
	WS_WriteList(GPIOA,GPIO_Pin_12,&List[1],3);
}
/*******************************************************************************
Func:按位设置颜色
Date:2016-12-29
Note:
*******************************************************************************/
void WS_SetColorBit(uint32 C,uint8 Bit)
{
	if(Bit&S0)UIShowValue.WSReg[0]=C;
	if(Bit&S1)UIShowValue.WSReg[1]=C;
	if(Bit&S2)UIShowValue.WSReg[2]=C;
	if(Bit&S3)UIShowValue.WSReg[3]=C;
	WS_Write(UIShowValue.WSReg);
}
/*******************************************************************************
Func:一起设置颜色
Date:2016-12-29
Note:
*******************************************************************************/
void WS_SetColor(uint32 A,uint32 B,uint32 C,uint32 D)
{
	UIShowValue.WSReg[0]=A;
	UIShowValue.WSReg[1]=B;
	UIShowValue.WSReg[2]=C;
	UIShowValue.WSReg[3]=D;
	WS_Write(UIShowValue.WSReg);
}
/*******************************************************************************
Func:指定设置颜色
Date:2016-12-29
Note:
*******************************************************************************/
void WS_SetDot(uint8 Index,uint32 C)
{
	UIShowValue.WSReg[Index]=C;
	WS_Write(UIShowValue.WSReg);
}
/*******************************************************************************
Func:测试
Date:2016-12-29
Note:
*******************************************************************************/
void Test(uint8 i)
{
	static uint8 L=12;
	UIShowValue.WSReg[2]=RGB_Light(0xEDD0E1,L++);
	UIShowValue.WSReg[3]=RGB_Light(0xEDD0E1,L++);
	WS_Write(UIShowValue.WSReg);
	Tos_TaskDelay(100);
	UIShowValue.WSReg[2]=0;
	UIShowValue.WSReg[3]=0;
	WS_Write(UIShowValue.WSReg);
	Tos_TaskDelay(200);
	UIShowValue.WSReg[2]=RGB_Light(0xEDD0E1,L++);
	UIShowValue.WSReg[3]=RGB_Light(0xEDD0E1,L++);
	WS_Write(UIShowValue.WSReg);
	Tos_TaskDelay(10);
	UIShowValue.WSReg[2]=0;
	UIShowValue.WSReg[3]=0;
	WS_Write(UIShowValue.WSReg);
	Tos_TaskDelay(1000);
}
/*******************************************************************************
Func:渐变色
Date:2016-12-29
Note:
*******************************************************************************/
void WS_ShadeBit(uint32 c,uint32 C,uint8 Bit)
{
	uint16 R,G,B,r,g,b,i;
	float rr,gg,bb,rStep,gStep,bStep;
	g=c>>16;
	r=(c>>8)&0xff;
	b=c&0xff;
	G=C>>16;
	R=(C>>8)&0xff;
	B=C&0xff;
	rStep = (float)(R-r)/255;
	gStep =(float)(G-g)/255;
	bStep = (float)(B-b)/255;
	rr=r;gg=g;bb=b;
	for (i = 0; i < 255; i++) 
	{       
		rr += rStep;
		gg += gStep;
		bb += bStep;
		r=rr;g=gg;b=bb;
		C=r;C<<=8;
		C|=g;C<<=8;
		C|=b;
		if(Bit&S0)UIShowValue.WSReg[0]=C;
		if(Bit&S1)UIShowValue.WSReg[1]=C;
		if(Bit&S2)UIShowValue.WSReg[2]=C;
		if(Bit&S3)UIShowValue.WSReg[3]=C;
		WS_Write(UIShowValue.WSReg);
		Tos_TaskDelay(3);
	}
	if(Bit&S0)UIShowValue.WSReg[0]=0;
	if(Bit&S1)UIShowValue.WSReg[1]=0;
	if(Bit&S2)UIShowValue.WSReg[2]=0;
	if(Bit&S3)UIShowValue.WSReg[3]=0;
	WS_Write(UIShowValue.WSReg);
}
/*******************************************************************************
Func:双闪
Date:2016-12-29
Note:
*******************************************************************************/
void WS_Double()
{
	UIShowValue.WSReg[2]=RGB_Light(0xffffff,0xff);
	UIShowValue.WSReg[3]=RGB_Light(0xffffff,0xff);
	WS_Write(UIShowValue.WSReg);
	Tos_TaskDelay(200);
	UIShowValue.WSReg[2]=0x0;
	UIShowValue.WSReg[3]=0x0;
	WS_Write(UIShowValue.WSReg);
	Tos_TaskDelay(200);
	UIShowValue.WSReg[2]=RGB_Light(0xffffff,0xff);
	UIShowValue.WSReg[3]=RGB_Light(0xffffff,0xff);
	WS_Write(UIShowValue.WSReg);
	Tos_TaskDelay(200);
	UIShowValue.WSReg[2]=RGB_Light(0x0,0xff);
	UIShowValue.WSReg[3]=RGB_Light(0x0,0xff);
	WS_Write(UIShowValue.WSReg);
}
/*******************************************************************************
Func:启动测试
Date:2016-12-29
Note:
*******************************************************************************/
void TestStart()
{
	WS_ShadeBit(000000,0xffff00,S2|S3);
	WS_ShadeBit(0xffff00,0xffffff,S2|S3);
	WS_Double();
}


