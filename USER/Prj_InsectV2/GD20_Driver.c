/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <IIC_Driver.c>

const GPIO_InitStruct IO_IIC_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_2},//CLK
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_10},//SDA
	{0}
};
uint8 Init_L3GD20(void)
{
	//0x6b,0xeb
	uint8 Addr[1],i;
	uint8 Cmd[]={0x0f,0x00,0x09,0x30,0x00};
	for(i=0;i<5;i++)
	{
		Addr[0]=0x20+i;
		IIC_WriteDatas(IO_IIC_List,0x6b,Addr,1,&Cmd[i],1);
	}
	return 0;
}
void GD20_Read()
{
	uint8 Addr[1],i;
	uint8 Cmd[6];
	uint16 *P,z;
	P=(uint16 *)&Cmd[0];
	for(i=0;i<6;i++)
	{
		Addr[0]=0x28+i;
		IIC_ReadDatas(IO_IIC_List,0x6b,Addr,1,&Cmd[i],1);
	}
	DeBug("cmd[%d]",GetWordFromBytes(&Cmd[0],0),0);
	DeBug("cmd[%d]",GetWordFromBytes(&Cmd[2],0),0);
	DeBug("cmd[%d]",GetWordFromBytes(&Cmd[4],0),0);
}
void GD20_Init()
{
	uint8 Buf[2],RX[6],adr,z;
	GPIO_InitList(IO_IIC_List);
	if(Init_L3GD20())DeBug("Init_L3GD20初始化成功%x",0xD6>>1,0);
	while(1)
	{
		GD20_Read();
		Tos_TaskDelay(100);
	}
	
}
uint8 Init_MMA8451Q(void)
{
	//0x6b,0xeb
	uint8 Addr[1],i;
	uint8 Cmd[1];
	Addr[0]=0x2a;Cmd[0]=0x01;
	IIC_WriteDatas(IO_IIC_List,0xeb,Addr,1,Cmd,1);
	Addr[0]=0x0e;Cmd[0]=0x00;
	IIC_WriteDatas(IO_IIC_List,0xeb,Addr,1,Cmd,1);
	Addr[0]=0x2b;Cmd[0]=0x02;
	IIC_WriteDatas(IO_IIC_List,0xeb,Addr,1,Cmd,1);
	return 0;
}
void MMA8451Q_Read()
{
		uint8 Addr[1],i;
	uint8 Cmd[6];
	for(i=0;i<6;i++)
	{
		Addr[0]=0x01+i;
		IIC_ReadDatas(IO_IIC_List,0xeb,Addr,1,&Cmd[i],1);
	}
	DeBug("cmd[%d]",GetWordFromBytes(&Cmd[0],1),0);
	DeBug("cmd[%d]",GetWordFromBytes(&Cmd[2],1),0);
	DeBug("cmd[%d]",GetWordFromBytes(&Cmd[4],1),0);
}
void MMA8451Q_Init()
{
	uint8 Buf[2],RX[6],adr,z;
	GPIO_InitList(IO_IIC_List);
	if(Init_MMA8451Q())DeBug("MMA8451Q_Init初始化成功%x",0xeb>>1,0);
	while(1)
	{
		MMA8451Q_Read();
		Tos_TaskDelay(100);
	}
	
}
