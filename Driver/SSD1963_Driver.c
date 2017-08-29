/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <gui_include.h>
#include <SSD1963_Driver.h>


/**********************************************************************
Func:��ʼ������SSD1963�Ķ˿ں�FSMC�ӿ�
Date:2014-5-2
Note:ʹ�õ��ٳ�ʼ��SSD1963��ֹ��ʼ�����ɹ�
**********************************************************************/
void SRAM_Init_LowSpeed(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;
  GPIO_InitTypeDef GPIO_InitStructure; 
  /* Enable GPIOs clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE,ENABLE);
  /* Enable FSMC clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
  /*Һ������λ����ʹ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Pin=S3;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/* ����SSD1963�˿�ģʽ50Mhz ����������� */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin =S0|S1|S4|S5|S7|S8|S9|S10|S11|S14|S15;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin =S7|S8|S9|S10|S11|S12|S13|S14|S15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

/*-- FSMC Configuration ------------------------------------------------------*/
  p.FSMC_AddressSetupTime = 30;
  p.FSMC_AddressHoldTime = 0;
  p.FSMC_DataSetupTime = 100;
  p.FSMC_BusTurnAroundDuration = 	0;
  p.FSMC_CLKDivision = 0;
  p.FSMC_DataLatency = 0;
  p.FSMC_AccessMode = FSMC_AccessMode_A;

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;  
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
  
	/*!< Enable FSMC Bank1_SRAM1 Bank */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE); 
	

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM2;

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
 
	/*!< Enable FSMC Bank1_SRAM2 Bank */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM2, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
                               
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
}
/**********************************************************************
Func:��ʼ������SSD1963�Ķ˿ں�FSMC�ӿ�
Date:2014-5-2
Note:ʹ�ø���ˢ��
**********************************************************************/
void SRAM_Init_HighSpeed(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;

/*-- FSMC Configuration ------------------------------------------------------*/
  p.FSMC_AddressSetupTime = 2;
  p.FSMC_AddressHoldTime = 0;
  p.FSMC_DataSetupTime = 5;
  p.FSMC_BusTurnAroundDuration = 	0;
  p.FSMC_CLKDivision = 0;
  p.FSMC_DataLatency = 0;
  p.FSMC_AccessMode = FSMC_AccessMode_A;
	

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;  
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
	/*!< Enable FSMC Bank1_SRAM1 Bank */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE); 
	

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM2;
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
 	/*!< Enable FSMC Bank1_SRAM2 Bank */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM2, ENABLE); 
	
}




/**********************************************************************
Func:Һ������ʼ��
Date:2014-5-2
Note:
**********************************************************************/

void SSD1963_Initializtion(void)
{
	 uint16_t i;
	 SRAM_Init_LowSpeed();
	
    SSD1963_RESET_CLR
    for(i=50000;i>0;i--);
    SSD1963_RESET_SET
    for(i=0;i<1000;i++);
    SSD1963_CMD=0x01;
    for(i=0;i<1000;i++);
    SSD1963_CMD=0x01;
    for(i=0;i<5000;i++);

    SSD1963_CMD=0xE2;SSD1963_DAT=0x32;                  //VCO_CLK=8M*50=400M
                 SSD1963_DAT=0x04;                  //PLL_CLK=400/4=100M
                 SSD1963_DAT=0x04;                  //����PLL����
            
    SSD1963_CMD=0xE0;SSD1963_DAT=0x01;                  //����PLL
    for(i=0;i<50000;i++);                       //�ȴ�PLL�ȶ�
    SSD1963_CMD=0xE0;SSD1963_DAT=0x03;                  //�л�ϵͳʱ�ӵ�PLLʱ��
    for(i=0;i<1000;i++);                        //�ȴ�PLL�ȶ�

    SSD1963_CMD=0xB8;SSD1963_DAT=0x0F;SSD1963_DAT=0x01;     //��������GPIOΪ��ͨGPIO����
    SSD1963_CMD=0xBA;SSD1963_DAT=0x05;                  //GPIO[3-0]=0001 MODE=1,U/D=0,L/R=1;
    //SSD1963_CMD=0xE6;SSD1963_DAT=0x03;SSD1963_DAT=0x33;SSD1963_DAT=0x33;        //����ʱ�� 100M*0x33333/(2^20)=19.99M
    SSD1963_CMD=0xE6;SSD1963_DAT=0x01;SSD1963_DAT=0x48;SSD1963_DAT=0x9E;    
    SSD1963_CMD=0xB0;SSD1963_DAT=0x20;SSD1963_DAT=0x00;     //�رն�̬�Աȶ�
                 SSD1963_DAT=(uint8)((SSD1963_4_3_XSIZE-1)>>8);
                 SSD1963_DAT=(uint8)((SSD1963_4_3_XSIZE-1));    //����Pannelˮƽ640����
                 SSD1963_DAT=(uint8)((SSD1963_4_3_YSIZE-1)>>8);
                 SSD1963_DAT=(uint8)((SSD1963_4_3_YSIZE-1));    //����Pannel��ֱ480����
                 //SSD1963_DAT=0x00;                        //��ż�о�ΪRGB˳��
    SSD1963_CMD=0xB4;SSD1963_DAT=(uint8)((SSD1963_HT-1)>>8);
                 SSD1963_DAT=(uint8)((SSD1963_HT-1));       //ˮƽ���������� 134+640+16=800TCLK
                 SSD1963_DAT=(uint8)((SSD1963_HPS-1)>>8);
                 SSD1963_DAT=(uint8)((SSD1963_HPS-1));      //ˮƽ���������Ч������ 144TCLK
                 SSD1963_DAT=(uint8)((SSD1963_HPW-1));      //ˮƽ����ʱ�ӿ��(�͵�ƽ)10TCLK
                 SSD1963_DAT=(uint8)((SSD1963_LPS>>8));
                 SSD1963_DAT=(uint8)((SSD1963_LPS));        //ˮƽ����13ʱˮƽͬ������ʱ��ʼ(ǰ13����Ч)
    SSD1963_CMD=0xB6;SSD1963_DAT=(uint8)((SSD1963_VT-1)>>8);
                 SSD1963_DAT=(uint8)((SSD1963_VT-1));       //��ֱ�й���13+480+32=525��
                 SSD1963_DAT=(uint8)((SSD1963_VPS>>8));
                 SSD1963_DAT=(uint8)((SSD1963_VPS));        //��ֱɨ����Чλ���ڵ�13��ʱ
                 SSD1963_DAT=(uint8)((SSD1963_VPW-1));      //��ֱͬ���ź���Ч���2LINE
                 SSD1963_DAT=(uint8)((SSD1963_FPS>>8));
                 SSD1963_DAT=(uint8)((SSD1963_FPS));        //
    SSD1963_CMD=0x3A;SSD1963_DAT=0x50;                  //����ɫ�ʿ��Ϊ18λ
    SSD1963_CMD=0xF0;SSD1963_DAT=0x03;                  //�������ظ�ʽΪRGB565��ʽ

    //SSD1963_CMD=0x0010;                           //����SLEEPģʽ
    //SSD1963_CMD=0x0011;                           //�˳�SLEEPģʽ
    //SSD1963_CMD=0x0012;                           //����ֲ�ģʽ
    //SSD1963_CMD=0x26;SSD1963_DAT=0x00;                //����GAMMA
    //SSD1963_CMD=0x0028;                           //�ر���ʾ
    SSD1963_CMD=0x2A;SSD1963_DAT=0x00;
                 SSD1963_DAT=0x00;
                 SSD1963_DAT=(SSD1963_4_3_XSIZE-1)>>8;
                 SSD1963_DAT=(SSD1963_4_3_XSIZE-1)&0xFF;    //��������ʾλ��0-639
    SSD1963_CMD=0x2B;SSD1963_DAT=0x00;
                 SSD1963_DAT=0x00;
                 SSD1963_DAT=(SSD1963_4_3_YSIZE-1)>>8;
                 SSD1963_DAT=(SSD1963_4_3_YSIZE-1)&0xFF;    //��������ʾλ��0-479
    //SSD1963_CMD=0x2C;                             //��ʼ����ͼ������,���е�ַ�Զ���λ����ʼԭ��   �Զ�����������0x36�����趨 ���������Զ�����
    //SSD1963_CMD=0x30;SSD1963_DAT=0x00;SSD1963_DAT=0x00;SSD1963_DAT=0x00;SSD1963_DAT=0x30; //���þֲ���ʾ��λ��
    //SSD1963_CMD=0x33; SSD1963_DAT=0x00;SSD1963_DAT=0x00;  //�����̶�����
    //              SSD1963_DAT=0x00;SSD1963_DAT=0x00;  //��������
    //              SSD1963_DAT=0x00;SSD1963_DAT=0x00;  //�ײ��̶�����
    //SSD1963_CMD=0x37; SSD1963_DAT=0x00;SSD1963_DAT=0x00;  //������ʼ��
    SSD1963_CMD=0x34;                               //��ֹTE�ź�
    //SSD1963_CMD=0x35;                             //ʹ��TE�ź�
    SSD1963_CMD=0x36;SSD1963_DAT=0x00;                  //��ʾ˳��
    SSD1963_CMD=0x38;                               //�˳�����ģʽ
    //SSD1963_CMD=0x39;                             //�������ģʽ

    //SSD1963_CMD=0x3C;                             //����дͼ������,�����ϴ�д0x2C
    //SSD1963_CMD=0x3E;                             //������ͼ������,�����ϴζ�0x2E
    SSD1963_CMD=0x44;SSD1963_DAT=0x00;SSD1963_DAT=0x00;     //TE�ź���ɨ�赽�ڼ���ʱ���
    SSD1963_CMD=0xBE;SSD1963_DAT=0x0A;                  //PWM_CLK=PCK/256/(256*DAT)
                 SSD1963_DAT=0x80;                  //PWM_DUTY=DAT/256
                 SSD1963_DAT=0x01;                  //PWM��HOST����
                 //SSD1963_DAT=0x80;                //���ȿ���
                 //SSD1963_DAT=0x00;                //�����������
                 //SSD1963_DAT=0x0F;                //�������ȷ�Ƶ��
    //SSD1963_CMD=0xD0;SSD1963_DAT=0xFF;                //��̬�Աȶȵ���
    //SSD1963_CMD=0xE5;                             //���볬�͹���״̬
    SSD1963_CMD=0x29;                               //����ʾ
    SSD1963_CMD=0x13;                               //��������ģʽ
    SSD1963_CMD=0x20;                               //�˳�����ģʽ
   // SSD1963_CMD=0x21;                             //���뷴��ģʽ
	SRAM_Init_HighSpeed();
	SSD1963_Clear_Screen(Color_Black);
}

void SSD1963_Clear_Screen(uint16 Color)
{
    uint32 C,i=(SSD1963_4_3_XSIZE*SSD1963_4_3_YSIZE)>>1;
    SSD1963_Set_Cursor(0,0,SSD1963_4_3_XMAX,SSD1963_4_3_YMAX);
    C=((uint32)Color<<16)|Color;
    do{SSD1963_DAT32=C;}while(--i);
}

/*--------------------------------------------------------------------------------------------------------
 Func: SSD1963_���� ���õ�ǰ���λ��
 Time: 2010-11-3
 Ver.: V1.0
 Note:
--------------------------------------------------------------------------------------------------------*/
void SSD1963_Set_Cursor(uint16 X,uint16 Y,uint16 EX,uint16 EY)
{
    SSD1963_CMD=0x2A;
    SSD1963_DAT=X>>8;
    SSD1963_DAT=X&0xFF;
    SSD1963_DAT=EX>>8;
    SSD1963_DAT=EX&0xFF;
    SSD1963_CMD=0x2B;
    SSD1963_DAT=Y>>8;
    SSD1963_DAT=Y&0xFF;
    SSD1963_DAT=EY>>8;
    SSD1963_DAT=EY&0xFF;
    SSD1963_CMD=0x2C;
}


/*--------------------------------------------------------------------------------------------------------
 Func: SSD1963_����д��
 Time: 2010-1-5
 Ver.: V1.0
 Note: Color 0/ǰ��ɫ  1/����ɫ
--------------------------------------------------------------------------------------------------------*/
void SSD1963_Set_Pixel(uint16 X,uint16 Y,uint16 Color)
{
    SSD1963_Set_Cursor(X,Y,X,Y);
    SSD1963_DAT=Color;
}

//Func: LCD��ȡ��ɫ��
uint16 SSD1963_Get_Pixel(uint16 X,uint16 Y)
{
    SSD1963_Set_Cursor(X,Y,X,Y);
    SSD1963_CMD=0x2E;
    return SSD1963_DAT;
}
/*--------------------------------------------------------------------------------------------------------
//��������
--------------------------------------------------------------------------------------------------------*/
void SSD1963_SET_Light(u8 Light)
{
	SSD1963_CMD=0XBE;
	SSD1963_DAT=0X0A;
	SSD1963_DAT=Light;
	SSD1963_DAT=0x01;
}/*--------------------------------------------------------------------------------------------------------
//����SSD1963  GPIO���
--------------------------------------------------------------------------------------------------------*/
void SSD1963_CLOSE_DISP(void)
{
    SSD1963_CMD=0xBA;
    SSD1963_DAT=0x00;                   
}
//Func: LCDˮƽ��ʵ��
void SSD1963_Draw_LineX(uint16 SX,uint16 SY,uint16 W,uint16 Color)
{
//  uint32 C;
    SSD1963_INC_DIRH            //ˮƽ��������
    SSD1963_Set_Cursor(SX,SY,SX+W-1,SY);
    do{SSD1963_DAT=Color;}while(--W);
    /*
    SX=W&0x01; W>>=1; C=((uint32)Color<<16)|Color;
    for(;W>0;--W)SSD1963_DAT32=C;
    if(SX)SSD1963_DAT=Color;
    */
}

//Func: LCDˮƽ�������
void SSD1963_Fill_LineX(uint16 SX,uint16 SY,uint16 W,uint16 *Cbuffer)
{
    uint32 *P;
    SSD1963_INC_DIRH
    SSD1963_Set_Cursor(SX,SY,SX+W,SY);
	//do{SSD1963_DAT=*Cbuffer++;}while(--W);
    SX=W&0x01; W>>=1; P=(uint32 *)Cbuffer;	
    for(;W>0;--W)SSD1963_DAT32=*P++;
    if(SX)SSD1963_DAT=*((uint16 
	*)P);
}

//Func: LCD��ֱ�������
void SSD1963_Fill_LineY(uint16 SX,uint16 SY,uint16 H,uint16 *Cbuffer)
{
    uint32 *P;
    SSD1963_INC_DIRV
    SSD1963_Set_Cursor(SX,SY,SX,SY+H);
    SX=H&0x01; H>>=1; P=(uint32 *)Cbuffer;
    for(;H>0;--H)SSD1963_DAT32=*P++;
    if(SX)SSD1963_DAT=*((uint16 *)P);
}

//Func: LCD��ֱ��ʵ��
void SSD1963_Draw_LineY(uint16 SX,uint16 SY,uint16 H,uint16 Color)
{
//  uint32 C;
    SSD1963_INC_DIRV            //��ֱ��������
    SSD1963_Set_Cursor(SX,SY,SX,SY+H);
    do{SSD1963_DAT=Color;}while(--H);
    /*
    C=((uint32)Color<<16)|Color;
    SX=H&0x01; H>>=1;
    for(;H>0;--H)SSD1963_DAT32=C;
    if(SX)SSD1963_DAT=Color;
    */
}

//Func: LCD����ˮƽ����
void SSD1963_Draw_DotLineX(uint16 SX,uint16 SY,uint16 W,uint16 Fcolor,uint16 Bcolor)
{
    uint32 C;
    SSD1963_INC_DIRH            //ˮƽ��������
    SSD1963_Set_Cursor(SX,SY,SX+W,SY);
    C=((uint32)Bcolor<<16)|Fcolor;
    SX=W&0x01; W>>=1;
    for(;W>0;--W)SSD1963_DAT32=C;
    if(SX)SSD1963_DAT=Fcolor;
}

//Func: LCD���ƴ�ֱ����
void SSD1963_Draw_DotLineY(uint16 SX,uint16 SY,uint16 H,uint16 Fcolor,uint16 Bcolor)
{
    uint32 C;
    SSD1963_INC_DIRV            //��ֱ��������
    SSD1963_Set_Cursor(SX,SY,SX,SY+H);
    C=((uint32)Bcolor<<16)|Fcolor;
    SX=H&0x01; H>>=1;
    for(;H>0;--H)SSD1963_DAT32=C;
    if(SX)SSD1963_DAT=Fcolor;
}

//Func: LCD��������
void SSD1963_Clear_Area(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 Color)
{
    uint32 T,C;
    SSD1963_Set_Cursor(SX,SY,EX,EY);
    T=(uint32)(EX-SX+1)*(uint32)(EY-SY+1);
    SX=T&0x01; T>>=1; C=((uint32)Color<<16)|Color;
    do{SSD1963_DAT32=C;}while(--T);
    if(SX)SSD1963_DAT=Color;
}


void SSD1963_Write(void *Addr,void *Buffer,void *Length)
{

}
void SSD1963_Read(void *Addr,void *Buffer,void *Length)
{
	
}



