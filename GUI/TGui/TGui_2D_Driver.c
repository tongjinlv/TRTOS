/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Lcd_Driver.h>
#include <Driver_Include.h>
#include <Math.h>
#include <TGui_2D_Driver.h>
/****************************************************************************
Date:2013/8/14
Vision:V1.0
Func:ˮƽ��ӡһ�ֽ���ʾ����
Note:(Data) һ�ֽڿ����������� (X,Y) ����ȫ�ֵ�ַ�����ı�ȫ�ֵ�ַ
****************************************************************************/
void Draw_X_8Bit(uint8 Data,uint16 X,uint16 Y,uint16 F_Color,uint16 B_Color,uint16 A_Color)
{
	char i;
	for(i=0;i<8;i++)
	{
		if(BIT(i)&Data)LCD_Set_Pixel(X,Y,F_Color);
		else if(B_Color!=A_Color)LCD_Set_Pixel(X,Y,B_Color);
		X++;
	}
}
/****************************************************************************
Date:2013/8/14
Vision:V1.0
Func:��ֱ��ӡһ�ֽ���ʾ����
Note:(Data) һ�ֽڿ����������� (X,Y) ����ȫ�ֵ�ַ�����ı�ȫ�ֵ�ַ
****************************************************************************/
void Draw_Y_8Bit(uint8 Data,uint16 X,uint16 Y,uint16 F_Color,uint16 B_Color,uint16 A_Color)
{
	char i;
	for(i=0;i<8;i++)
	{
		if(BIT(i)&Data)LCD_Set_Pixel(X,Y,F_Color);
		else if(B_Color!=A_Color)LCD_Set_Pixel(X,Y,B_Color);
		Y++;
	}
}
/****************************************************************************
Date:2013/8/14
Vision:V1.0
Func:��ֱƽ��һ�ֽڿ��
Note:(Data) ƽ��һϵ�в��� (X,Y) ����ȫ�ֵ�ַ�����ı�ȫ�ֵ�ַ
****************************************************************************/

void Draw_Full_List(void *Data,uint16 Data_Length,uint16 X,uint16 Y,uint16 F_Color,uint16 B_Color,uint16 A_Color)
{
#ifdef FAST_Draw_Full_List
	Fast_Draw_Fill_List(Data,Data_Length,X,Y,F_Color,B_Color,A_Color);
#else 
	uint16 i;
	uint8 *p;
	p=(uint8 *)Data;
	for(i=0;i<Data_Length;i++)
	{
		Draw_X_8Bit(*p++,X,Y,F_Color,B_Color,A_Color);
		Y++;
	}
#endif
}
/****************************************************************************
Date:2013/8/14
Vision:V1.0
Func:ˮƽƽ��һ�ֽڿ��
Note:(Data) ƽ��һϵ�в��� (X,Y) ����ȫ�ֵ�ַ�����ı�ȫ�ֵ�ַ
****************************************************************************/
void Draw_Row_List(void *Data,uint16 Data_Length,uint16 X,uint16 Y,uint16 F_Color,uint16 B_Color,uint16 A_Color)
{
	uint16 i;
	uint8 *p;
	p=(uint8 *)Data;
	for(i=0;i<Data_Length;i++)
	{
		Draw_Y_8Bit(*p++,X,Y,F_Color,B_Color,A_Color);
		X++;
	}
}

/*---------------------------------------------------------------------------------------------------------------------------
 Func: ���Ƶ���
 Time: 2010-1-5
 Ver.: V1.0
 Note: ���������ڻ�������ֱ��,���õ�һ����ֱ�߲岹�㷨
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_DotLine(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 Fcolor,uint16 Bcolor)
{	
	uint8 T;
	uint16 X,Y,C,B,K=0;
	int16 Fe;
	if(X0>X1){													//����ɴ������һ���
	 	C=X0;X0=X1;X1=C;				
		C=Y0;Y0=Y1;Y1=C;
	}
	if(Y0>Y1){Y1=Y0-Y1;T=1;Y=0;}								//����������ֱ��ת������һ����
	else {Y1=Y1-Y0;T=0;Y=Y0;}
	X1-=X0;
	if(X0==X1)LCD_Draw_DotLineY(X0,Y0,Y1,Fcolor,Bcolor);		//���ٻ��ƴ�ֱ��
	else if(Y0==Y1)LCD_Draw_DotLineX(X0,Y0,X1,Fcolor,Bcolor);	//���ٻ���ˮƽ��
	else{														//���ٵ�һ����ֱ�߲岹
		C=Y1+X1;Fe=0;X=X0;									     
		while(C--){
			if(Fe>0){Fe-=Y1;} else {Fe+=X1;}
			if(Fe>0){X++;}    else {Y++;}																				
			if(K&0x0001)B=Bcolor;								//���Ʊ���ɫ��
			else		B=Fcolor;								//����ǰ��ɫ��
			if(T>0)LCD_Set_Pixel(X,Y0-Y,B);			
			else LCD_Set_Pixel(X,Y,B);	
			K++;												//��ͳ��
		}	
	}
}

/*---------------------------------------------------------------------------------------------------------------------------
 Func: ���ƾ���
 Time: 2010-1-6
 Ver.: V1.0
 Note: 
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_Rectangle(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 Color)
{
	LCD_Draw_LineX(X0,Y0,X1-X0,Color);
	LCD_Draw_LineX(X0,Y1,X1-X0,Color);	
	LCD_Draw_LineY(X0,Y0,Y1-Y0,Color);	
	LCD_Draw_LineY(X1,Y0,Y1-Y0,Color); 	
}
/*--------------------------------------------------------------------------------------------------------
 �޸ľ�������
--------------------------------------------------------------------------------------------------------*/
void TGUI_Set_Rectangle(Rectangle *Rect,uint16 SX,uint16 SY,uint16 EX,uint16 EY)
{
	Rect->SX=SX;
	Rect->SY=SY;
	Rect->EX=EX;
	Rect->EY=EY;
}

/*---------------------------------------------------------------------------------------------------------------------------
 Func: TGUI_2D��ͼ,���ƾ���
 Time: 2010-1-6
 Ver.: V1.0
 Note: 
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_DotRectangle(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 Fcolor,uint16 Bcolor)
{
	LCD_Draw_DotLineX(X0,Y0,X1-X0,Fcolor,Bcolor);
	LCD_Draw_DotLineX(X0,Y1,X1-X0,Fcolor,Bcolor);
	LCD_Draw_DotLineY(X0,Y0,Y1-Y0,Fcolor,Bcolor);	
	LCD_Draw_DotLineY(X1,Y0,Y1-Y0,Fcolor,Bcolor);
}                        

/*---------------------------------------------------------------------------------------------------------------------------
 Func: TGUI_2D��ͼ,����Բ�Ǿ���
 Time: 2011-6-11
 Ver.: V1.0
 Note: ColorU/�ϱ���ɫ��  ColorP/�±���ɫ��
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_ArcRectangle(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 R,uint16 ColorU,uint16 ColorD)
{
	uint16 C,X,Y,XA,YA,XB,YB;
	int16 Fe;
	TGui_Draw_Line(SX+R,SY,EX-R,SY,ColorU);						//�ϱ���
	TGui_Draw_Line(SX+R,EY,EX-R,EY,ColorD);						//�±���
	TGui_Draw_Line(SX,SY+R,SX,EY-R,ColorU);						//�����
	TGui_Draw_Line(EX,SY+R,EX,EY-R,ColorD);						//�ұ���
	XA=EX-R;YA=SY+R;											//��һ����ԭ��
	SX+=R;	SY+=R;												//�ڶ�����ԭ��
	XB=SX; 	YB=EY-R;											//��������ԭ��
	EX-=R;	EY-=R;												//��������ԭ��
	C=R<<1;Fe=0;X=R,Y=0;
	while(C--){
		if(Fe>0)Fe=Fe-2*X+1;
		else Fe=Fe+2*Y+1;
		if((Fe>0)&&(X>0))X--;
		else Y++;
		LCD_Set_Pixel(EX+X,EY+Y,ColorD);						//���Ƶ�������
		LCD_Set_Pixel(XB-X,YB+Y,ColorU); 						//���Ƶ�������
		LCD_Set_Pixel(SX-X,SY-Y,ColorU);						//���Ƶڶ�����
		LCD_Set_Pixel(XA+X,YA-Y,ColorU);						//���Ƶ�һ����
	}	
}


/*---------------------------------------------------------------------------------------------------------------------------
 Func: TGUI_2D��ͼ����,����Բ��
 Time: 2010-1-5
 Ver.: V1.0
 Note: (X0,Y0)Բ������  R/Բ�뾶
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_Circle(uint16 X0,uint16 Y0,uint16 R,uint16 Color)
{
	uint16 C,X,Y;
	int16 Fe;
	C=R<<1;Fe=0;X=R,Y=0;
	while(C--){
		if(Fe>0)Fe=Fe-2*X+1;
		else Fe=Fe+2*Y+1;
		if(Fe>0)X--;
		else Y++;
		LCD_Set_Pixel(X0+X,Y0+Y,Color);							//���Ƶ�һ����
		LCD_Set_Pixel(X0-X,Y0+Y,Color);	 						//���Ƶڶ�����
		LCD_Set_Pixel(X0-X,Y0-Y,Color);							//���Ƶ�������
		LCD_Set_Pixel(X0+X,Y0-Y,Color);							//���Ƶ�������
	}	
}

void CirclePoint(int x,int y,int x0,int y0,int color)
{
	LCD_Set_Pixel(x+x0,y+y0,color);
	LCD_Set_Pixel(y+x0,x+y0,color);
	LCD_Set_Pixel(y+x0,-x+y0,color);
	LCD_Set_Pixel(x+x0,-y+y0,color);
	LCD_Set_Pixel(-x+x0,-y+y0,color);
	LCD_Set_Pixel(-y+x0,-x+y0,color);
	LCD_Set_Pixel(-y+x0,x+y0,color);
	LCD_Set_Pixel(-x+x0,y+y0,color);
}
void TGUI_DrawRound(int x0,int y0,int r,int color)
{
	int x,y,d;
	x=0;
	y=r;
	d=1-r;
	CirclePoint(x,y,x0,y0,color);
	while(x<=y)
	{
		if(d<0){d+=2*x+3;x++;}
		else{d+=2*(x-y)+5;x++;y--;}
		CirclePoint(x,y,x0,y0,color);
	}
}
void TGUI_DrawRound2(uint16 X0,uint16 Y0,uint16 R0,uint16 Xo,uint16 Color)
{
	uint16 X,Y,RR,XX;
	RR=R0*R0;
	for(X=0;X<R0;X++)
	{
		XX=X*X;
		for(Y=0;Y<=R0;Y++)
		{
			if(fabs((XX+Y*Y)<RR)&&fabs((XX+Y*Y)>(Xo)))CirclePoint(X,Y,X0,Y0,Color);
		}
	}
}
/*---------------------------------------------------------------------------------------------------------------------------
 Func: TGUI_2D��ͼ����,����Բ��
 Time: 2010-1-5
 Ver.: V1.0
 Note: (X0,Y0)Բ������  R/Բ�뾶
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_DotCircle(uint16 X0,uint16 Y0,uint16 R,uint16 Fcolor,uint16 Bcolor)
{
	uint16 C,X,Y,B,K=0;
	int16 Fe;
	C=R<<1;Fe=0;X=R,Y=0;
	while(C--){
		if(Fe>0)Fe=Fe-2*X+1;
		else Fe=Fe+2*Y+1;
		if(Fe>0)X--;
		else Y++;
		if(K&0x0001)B=Bcolor;									//���Ʊ�����
		else B=Fcolor;											//����ǰ����
		LCD_Set_Pixel(X0+X,Y0+Y,B);								//���Ƶ�һ����
		LCD_Set_Pixel(X0-X,Y0+Y,B);		 						//���Ƶڶ�����
		LCD_Set_Pixel(X0-X,Y0-Y,B);								//���Ƶ�������
		LCD_Set_Pixel(X0+X,Y0-Y,B);								//���Ƶ�������
		K++;
	}	
}


/*---------------------------------------------------------------------------------------------------------------------------
 Func: WGUI_2D��ͼ����,Բ���ڲ����
 Time: 2010-1-5
 Ver.: V1.0
 Note: (X,Y)Բ������  R/Բ�뾶
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Fill_Circle(uint16 X0,uint16 Y0,uint16 R,uint16 Color)
{
	uint16 C;
	int16 Fe,X,Y;
	C=R<<1;Fe=0;X=R,Y=0;
	while(C--){
		if(Fe>0)Fe=Fe-2*X+1;
		else Fe=Fe+2*Y+1;
		if(Fe>0)X--;
		else {Y++;		
		    LCD_Draw_LineX(X0-X+1,Y0+Y,X*2-1,Color);
		    LCD_Draw_LineX(X0-X+1,Y0-Y,X*2-1,Color);
		}
	}
	LCD_Draw_LineX(X0-R+2,Y0,2*R-3,Color);	
}


/*---------------------------------------------------------------------------------------------------------------------------
 Func: WGUI_2D��ͼ����,����ʵ�߻���
 Time: 2010-1-5
 Ver.: V1.0
 Note: (X0,Y0)Բ������  R0/��Բ�뾶 R1/��Բ�뾶	ColorR0/��Բɫ��	ColorR1/��Բɫ��
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_Ring(uint16 X0,uint16 Y0,uint16 R0,uint16 R1,uint16 ColorR0,uint16 ColorR1)
{
	TGUI_Draw_Circle(X0,Y0,R0,ColorR0);										//������Բ	
	TGUI_Draw_Circle(X0,Y0,R1,ColorR1);										//������Բ
}

/*---------------------------------------------------------------------------------------------------------------------------
 Func: WGUI_2D��ͼ����,��价��
 Time: 2010-11-9
 Ver.: V1.0
 Note: (X0,Y0)Բ������  R0/��Բ�뾶 R1/��Բ�뾶	ColorR0/��Բɫ��	ColorR1/��Բɫ��
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Fill_Ring(uint16 X0,uint16 Y0,uint16 R0,uint16 R1,uint16 ColorR0,uint16 ColorR1)
{
	uint16 C,C1;
	int16 Fe,X,Y,Fe1,X1,Y1;	
	C=R0<<1; Fe=0; X=R0; Y=0;
	C1=R1<<1;Fe1=0;X1=R1;Y1=0;
	while(C1--){													//����Բ��Ϊ������־
		if(Fe1>0)Fe1=Fe1-(X1<<1)+1;									//��Բ����һ��
		else 	 Fe1=Fe1+(Y1<<1)+1;												  						
		if(Fe1>0)X1--;
		else{
			Y1++;
			if(C){
				while((Y!=Y1)&&(C>0)){
					if(Fe>0) Fe=Fe-(X<<1)+1;							//��Բ����һ��
					else	 Fe=Fe+(Y<<1)+1;
					if(Fe>0)X--;   
					else {Y++;}
					C--;
				}
				if(C>0){												//�Ƿ񵽴ﶥ��
					LCD_Draw_LineX(X0-X1, Y0+Y, X1-X,  ColorR1);		//�����Բ����뻷	
					LCD_Draw_LineX(X0-X,  Y0+Y, X*2+1, ColorR0);		//�����Բ�ϰ뻷
					LCD_Draw_LineX(X0+X+1,Y0+Y, X1-X,  ColorR1);		//�����Բ���Ұ뻷
					LCD_Draw_LineX(X0-X1, Y0-Y, X1-X,  ColorR1);		//�����Բ����뻷	
					LCD_Draw_LineX(X0-X,  Y0-Y, X*2+1, ColorR0);		//�����Բ�°뻷
					LCD_Draw_LineX(X0+X+1,Y0-Y, X1-X,  ColorR1);		//�����Բ���Ұ뻷		
				}else{
					LCD_Draw_LineX(X0-X1,Y0+Y1,X1*2+1,ColorR1);			//�����Բ�ϰ뻷
		    		LCD_Draw_LineX(X0-X1,Y0-Y1,X1*2+1,ColorR1);			//�����Բ�°뻷
				}
			}else{
				LCD_Draw_LineX(X0-X1,Y0+Y1,X1*2+1,ColorR1);				//�����Բ�ϰ뻷
		    	LCD_Draw_LineX(X0-X1,Y0-Y1,X1*2+1,ColorR1);				//�����Բ�°뻷
			}
		}		
	}	
	LCD_Draw_LineX(X0-R1,Y0,R1-R0,ColorR1);	
	LCD_Draw_LineX(X0-R0+1,Y0,R0*2,ColorR0);	
	LCD_Draw_LineX(X0+R0,Y0,R1-R0,ColorR1);	
}

/*---------------------------------------------------------------------------------------------------------------------------
 Func: WGUI_2D��ͼ,�������
 Time: 2010-1-6
 Ver.: V1.0
 Note: 
---------------------------------------------------------------------------------------------------------------------------*/

void TGUI_Fill_Rectangle(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 Color)
{
#ifdef FAST_Fill_Rectangle
	Fast_Fill_Rectangle(X0,Y0,X1,Y1+1,Color);
#else 
	uint16 T;
	T=X1-X0+1;
	while(Y0<=Y1)LCD_Draw_LineX(X0,Y0++,T,Color);
#endif
}

void TGUI_Fill_Bar(uint16 x1, uint16 y1, uint16 x2, uint16 y2,uint16 Max,uint16 Rate)
{
   uint16 W,H;
   uint8 attr=1,i=0;
   W=x2-x1;
   H=y2-y1;
   if(W>H)
   while(1)
    {
       if((i++)>(W*Rate/Max))attr=0;
       TGui_Draw_Line(x1,y1,x1,y2,attr);
       if(x1++>=x2)break; 
    } 
}                                                                                  
/*---------------------------------------------------------------------------------------------------------------------------
 Func: WGUI_2D��ͼ,���Բ�Ǿ���
 Time: 2011-6-11
 Ver.: V1.0
 Note: R/Բ�ǰ뾶 ColorU/�ϲ���ɫ��  ColorP/�²���ɫ��
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Fill_ArcRectangle(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 R,uint16 ColorU,uint16 ColorD)
{
	uint16 C,X,Y;
	int16 Fe;
	C=(EY+SY)>>1;
	SY+=R;	EY-=R;
	LCD_Clear_Area(SX,SY,EX,C,ColorU);							//���body�ϲ���
	LCD_Clear_Area(SX,C,EX,EY,ColorD);							//���body�²���
	SX+=R;	EX-=R;
	C=R<<1;Fe=0;X=R,Y=0;
	while(C--){
		if(Fe>0)Fe=Fe-2*X+1;
		else Fe=Fe+2*Y+1;		
		if((Fe>0)&&(X>0))X--;
		else {														
			Y++;
			TGui_Draw_Line(SX-X,SY-Y,EX+X,SY-Y,ColorU);		    //����body�ϲ�
			TGui_Draw_Line(SX-X,EY+Y,EX+X,EY+Y,ColorD);			//����body�²�
		}																							
	}
}

/*---------------------------------------------------------------------------------------------------------------------------
 Func: WGUI_2D��ͼ,������������
 Time: 2010-1-6
 Ver.: V1.0
 Note; (SX,SY)/��ʼ�����λ��   Direction/���Ʒ��� =0:������ 1:������ 2:������ 3:������ Color/����ɫ��
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_Triangle(uint16 SX,uint16 SY,uint16 Lenth,uint8 Direction,uint16 Color)
{                                                  
    uint16 i=2;
    LCD_Set_Pixel(SX,SY,Color);Lenth-=2;
    switch(Direction)
    {           
        case Dir_UpDown:    
            while(Lenth--){LCD_Set_Pixel(--SX,++SY,Color);LCD_Set_Pixel(SX+i,SY,Color);i+=2;} 
            LCD_Draw_LineX(--SX,++SY,i+1,Color); 
            break;
        case Dir_DownUp:    
            while(Lenth--){LCD_Set_Pixel(--SX,--SY,Color);LCD_Set_Pixel(SX+i,SY,Color);i+=2;} 
            LCD_Draw_LineX(--SX,--SY,i+1,Color);
            break;
        case Dir_LeftRight: 
            while(Lenth--){LCD_Set_Pixel(++SX,--SY,Color);LCD_Set_Pixel(SX,SY+i,Color);i+=2;} 
            LCD_Draw_LineY(++SX,--SY,i+1,Color);
            break;
        case Dir_RightLeft: 
            while(Lenth--){LCD_Set_Pixel(--SX,--SY,Color);LCD_Set_Pixel(SX,SY+i,Color);i+=2;} 
            LCD_Draw_LineY(--SX,--SY,i+1,Color);
            break;   
    }                                        
}

/*---------------------------------------------------------------------------------------------------------------------------
 Func: WGUI_2D��ͼ,�����������
 Time: 2010-1-6
 Ver.: V1.0
 Note; (SX,SY)/��ʼ�����λ��   Direction/���Ʒ��� =0:������ 1:������ 2:������ 3:������ Color/���ɫ��
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Fill_Triangle(uint16 SX,uint16 SY,uint16 Lenth,uint8 Direction,uint16 Color)
{                                                  
    uint16 i=1;                                              
    Lenth-=2;
    switch(Direction)
    {
        case Dir_UpDown:    while(Lenth--){LCD_Draw_LineX(SX--,++SY,i,Color);i+=2;} break;
        case Dir_DownUp:    while(Lenth--){LCD_Draw_LineX(SX--,--SY,i,Color);i+=2;} break;
        case Dir_LeftRight: while(Lenth--){LCD_Draw_LineY(++SX,SY--,i,Color);i+=2;} break;
        case Dir_RightLeft: while(Lenth--){LCD_Draw_LineY(--SX,SY--,i,Color);i+=2;} break;   
    }
}

/*---------------------------------------------------------------------------------------------------------------------------
 Func: WGUI_2D��ͼ����,����BMPͼ��
 Time: 2010-1-5
 Ver.: V1.0
 Note: (X,Y)ͼ����ʼλ�� W/λͼ��� H/λͼ�߶� *Bmp/λͼ����
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_Bitmap(uint16 X,uint16 Y,uint16 W,uint16 H,uint16 *Bmp)
{
	while(H--){LCD_Fill_LineX(X,Y++,W,Bmp);Bmp+=W;}
}

/*---------------------------------------------------------------------------------------------------------------------------
 Func: WGUI_2D��ͼ����,BMPͼ�ο���ˮƽ���
 Time: 2010-1-5
 Ver.: V1.0
 Note: ���������Խ�λͼ���п���ˮƽ�������
 	   (X,Y)ͼ����ʼλ�� W/λͼ��� H/λͼ�߶� WL/��������� *Bmp/λͼ����
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Fill_BitmapX(uint16 X,uint16 Y,uint16 W,uint16 H,uint16 WL,uint16 *Bmp)
{
	uint16 i,j;
	i=WL/W;j=WL%W;					
	while(i--){TGUI_Draw_Bitmap(X,Y,W,H,Bmp);X+=W;}
	while(H--){LCD_Fill_LineX(X,Y++,j,Bmp);Bmp+=W;}		
}

/*---------------------------------------------------------------------------------------------------------------------------
 Func: WGUI_2D��ͼ����,BMPͼ�ο��ٴ�ֱ���
 Time: 2010-1-5
 Ver.: V1.0
 Note: ���������Խ�λͼ���п��ٴ�ֱ�������
 	   (X,Y)ͼ����ʼλ�� W/λͼ��� H/λͼ�߶� HL/�������߶� *Bmp/λͼ����
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Fill_BitmapY(uint16 X,uint16 Y,uint16 W,uint16 H,uint16 HL,uint16 *Bmp)
{
	uint16 i,j;
	i=HL/H;j=HL%H;					
	while(i--){TGUI_Draw_Bitmap(X,Y,W,H,Bmp);Y+=H;}
	while(j--){LCD_Fill_LineX(X,Y++,W,Bmp);Bmp+=W;}
}

/*--------------------------------------------------------------------------------------------------------------------------
 Func: TGUI_2D��ͼ����,���ƶ����3D͹��Ч��
 Time: 2010-1-8
 Ver.: V1.0
 Note: (SX,SY)(EX,EY)/�������λ��  LightColor/���߿�ɫ��   DarkColor/���߿�ɫ��    FaceColor/�������ɫ��
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_ObjectPopUp(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 LightColor,uint16 DarkColor,uint16 FaceColor)
{
    LCD_Draw_LineX(SX,SY,EX-SX,LightColor);
    LCD_Draw_LineY(SX,SY,EY-SY,LightColor);
    LCD_Draw_LineX(SX,EY,EX-SX,DarkColor);
    LCD_Draw_LineY(EX,SY,EY-SY+1,DarkColor);
    TGUI_Fill_Rectangle(SX,SY,EX,EY,FaceColor);
}

/*--------------------------------------------------------------------------------------------------------------------------
 Func: TGUI_2D��ͼ����,���ƶ����3D����Ч��
 Time: 2010-1-8
 Ver.: V1.0
 Note: (SX,SY)(EX,EY)/�������λ��  LightColor/���߿�ɫ��   DarkColor/���߿�ɫ��    FaceColor/�������ɫ��
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_ObjectPopDown(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 LightColor,uint16 DarkColor,uint16 FaceColor)
{
    LCD_Draw_LineX(SX,SY,EX-SX,DarkColor);
    LCD_Draw_LineY(SX,SY,EY-SY,DarkColor);
    LCD_Draw_LineX(SX,EY,EX-SX,LightColor);
    LCD_Draw_LineY(EX,SY,EY-SY+1,LightColor);
    TGUI_Fill_Rectangle(SX,SY,EX,EY,FaceColor);
}
/*--------------------------------------------------------------------------------------------------------------------------
 Func: TGUI_2D��ͼ����,����ͼƬ
 Time: 2014-6-10
 Ver.: V1.0
 Note: 
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_Image(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 PX,uint16 PY,void *ImageAddr)
{
	uint32 T;
	T=(uint32)ImageAddr;	
	if(T<0xFFFF){														//���ͼƬ
		
	}else if(T<0x8000000){												//�Ƿ���ַ
			
	}else if(T<0x20000000){												//ROM��ַ
		TGUI_Draw_Bitmap(SX,SY,EX-SX,EY-SY,ImageAddr);
	}else{																//RAM��ַ
	}
}
