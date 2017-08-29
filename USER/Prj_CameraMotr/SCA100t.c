/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <..\USER\Prj_CAMERAMOTR\SCA100t.h>
uint16 AngleXY[2];
void GPIO_SCA100T_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE); 
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_13|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE); 
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void SCA_Delay(uint16 n)
{
	n*=10;
    while(n--);
}
void SPI_Stop()
{
    SCACLK_L;
    SCACS_H;    
    SCA_Delay(10);
}
void SPI_Reset(void){
    SPI_Stop();
}
void SPI_Start(void){
    SCACLK_L;
    SCACS_L;
    SCA_Delay(10);
}
void SPI_WriteByte(uint8 wdata )
{
	uint8 i;
	for( i = 0 ; i < 8 ; ++i ){
	SCACLK_L;
	SCA_Delay(10);
	if(wdata & 0x80)SCAIN_H;else SCAIN_L;
	wdata = wdata << 1;
	SCA_Delay(10);
	SCACLK_H;
	SCA_Delay(10);
	}
	SCACLK_L;
}
uint8 SPI_ReadBit(void)
{
    SCACLK_H;
    SCA_Delay(10);
    SCACLK_L;
    SCA_Delay(10);
    return SCAOUT_D;
}

uint16 SPI_ReadBits(uint8 n )
{
    uint16 rtemp=0,i;
    for( i = 0 ; i < n ; i++ ){  ;
        SCA_Delay(10);
			   rtemp<<=1;
        if( SCAOUT_D == 1 ){
            rtemp++;
        }else{
        }
        SCACLK_H;
        SCA_Delay(10);
        SCACLK_L;
        SCA_Delay(10);

    }
    return rtemp;
}
uint16 SPI_GetX( void )
{
    uint16 result;
    SPI_Start();
    SPI_WriteByte( RDAX );
    result = SPI_ReadBits(11);
    SPI_Stop();
    return result;

}
uint16 SPI_GetReg(uint8 Cmd,uint8 Length)
{
    uint16 result;
    SPI_Start();
    SPI_WriteByte( Cmd );
    result = SPI_ReadBits(Length);
    SPI_Stop();
    return result;

}
uint16 SPI_GetY( void )
{
    uint16 result;
    SPI_Start();
    SPI_WriteByte( RDAY );
    result = SPI_ReadBits(11);
    SPI_Stop();
    return result;

}

void SCA_Init( void )
{
		GPIO_SCA100T_Init();
	  SPI_Reset();
    SPI_Start();
    SPI_WriteByte( MEAS );
    SPI_Stop();
}
void Task_GetAngle(void *Tags)
{
	uint32 Pool[2];
	uint8 Index[2];
	SCA_Init();
	while(1)
	{
		Tos_TaskDelay(10);
		AngleXY[0]=FlowPoolFilter(&Pool[0],SPI_GetReg(RDAX,11),&Index[0],10);
		Tos_TaskDelay(10);
		AngleXY[1]=FlowPoolFilter(&Pool[1],SPI_GetReg(RDAY,11),&Index[1],10);
	}
}
