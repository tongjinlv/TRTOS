/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I			0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据，+1为读取

const GPIO_InitStruct IO_IIC_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_13},//CLK
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_12},//SDA
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
		IIC_WriteDatas(IO_IIC_List,0xD0,Addr,1,&Cmd[i],1);
	}
	return 0;
}
void GD20_Read()
{
	uint8 Addr[1],i;
	uint8 Cmd[6];
	static uint8 addr=0x00;
	for(i=0;i<6;i++)
	{
		Addr[0]=i;
		IIC_ReadDatas(IO_IIC_List,0xD0>>1,Addr,1,&Cmd[i],1);
	}
	DeBug("cmd[%d]",GetWordFromBytes(&Cmd[0],0),0);
	DeBug("cmd[%d]",GetWordFromBytes(&Cmd[2],0),0);
	DeBug("cmd[%d]",GetWordFromBytes(&Cmd[4],0),0);
}
void GD20_Init()
{
	uint8 Buf[2],RX[6],adr,z;
	GPIO_InitList(IO_IIC_List);
	//if(Init_L3GD20())DeBug("Init_L3GD20初始化成功%x",0xD6>>1,0);
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
const GPIO_InitStruct MPU_IIC_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_13},//CLK
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOB,GPIO_Pin_12},//SDA
	{0}
};
uint8 Single_WriteI2C(const GPIO_InitStruct *IIC_Maps,uint8 REG_Address,uint8 REG_data)
{
		uint8 R=0x00;
		IIC_Start(IIC_Maps);
    R|=IIC_SendByte(IIC_Maps,SlaveAddress);   //发送设备地址+写信号
    R|=IIC_SendByte(IIC_Maps,REG_Address);    //内部寄存器地址，
    R|=IIC_SendByte(IIC_Maps,REG_data);       //内部寄存器数据，
    IIC_Stop(IIC_Maps);                   //发送停止信号
	return R;
}
uint8 Single_ReadI2C(const GPIO_InitStruct *IIC_Maps,uint8 REG_Address)
{
	uint8 REG_data;
	IIC_Start(IIC_Maps);                 //起始信号
	DeBug("dd[%d]",IIC_SendByte(IIC_Maps,SlaveAddress),0);;    //发送设备地址+写信号
	IIC_SendByte(IIC_Maps,REG_Address);     //发送存储单元地址，从0开始	
	IIC_Start(IIC_Maps);                 //起始信号
	IIC_SendByte(IIC_Maps,SlaveAddress+1);  //发送设备地址+读信号
	REG_data=IIC_RecvByte(IIC_Maps);       //读出寄存器数据
	IIC_SendAck(IIC_Maps,1);
	IIC_Stop(IIC_Maps);  
	return REG_data;
}
void MPU_Init(const GPIO_InitStruct *IIC_Maps)
{
	GPIO_InitList(IIC_Maps);
}
void TempGD20(void *Tags)
{
	uint8 Buf[15];
  MPU_Init(MPU_IIC_List);
	while(1)
	{
		Tos_TaskDelay(1000); 
		DeBug("dd[%d]",Single_WriteI2C(MPU_IIC_List,CONFIG,0),0);
		
	}
}
