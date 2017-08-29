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
	uint8 R=0x00;
	IIC_Start(IIC_Maps);                 //起始信号
	R|=IIC_SendByte(IIC_Maps,SlaveAddress);    //发送设备地址+写信号
	R|=IIC_SendByte(IIC_Maps,REG_Address);     //发送存储单元地址，从0开始	
	IIC_Start(IIC_Maps);                 //起始信号
	R|=IIC_SendByte(IIC_Maps,SlaveAddress+1);  //发送设备地址+读信号
	REG_data=IIC_RecvByte(IIC_Maps);       //读出寄存器数据
	IIC_SendAck(IIC_Maps,1);
	IIC_Stop(IIC_Maps);  
	return REG_data;
}
void InitMPU6050(const GPIO_InitStruct *IIC_Maps)
{
	Single_WriteI2C(IIC_Maps,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(IIC_Maps,SMPLRT_DIV, 0x07);
	Single_WriteI2C(IIC_Maps,CONFIG, 0x06);
	Single_WriteI2C(IIC_Maps,GYRO_CONFIG, 0x18);
	Single_WriteI2C(IIC_Maps,ACCEL_CONFIG, 0x01);
}

int GetData(const GPIO_InitStruct *IIC_Maps,uint8 REG_Address)
{
	uint8 H,L;
	H=Single_ReadI2C(IIC_Maps,REG_Address);
	L=Single_ReadI2C(IIC_Maps,REG_Address+1);
	return (uint16)(H<<8)+L;   //合成数据
}
void MPU_Init(const GPIO_InitStruct *IIC_Maps)
{
	GPIO_InitList(IIC_Maps);
}
void TempGD20(void *Tags)
{
	uint8 Buf[15];
  MPU_Init(MPU_IIC_List);
	InitMPU6050(MPU_IIC_List);
	while(1)
	{
		Tos_TaskDelay(100); 
		DeBug("ACCEL_XOUT_H[%d]",GetData(MPU_IIC_List,ACCEL_XOUT_H),0);
		DeBug("ACCEL_YOUT_H[%d]",GetData(MPU_IIC_List,ACCEL_YOUT_H),0);
		DeBug("ACCEL_ZOUT_H[%d]",GetData(MPU_IIC_List,ACCEL_ZOUT_H),0);
		
		DeBug("GYRO_XOUT_H[%d]",GetData(MPU_IIC_List,GYRO_XOUT_H),0);
		DeBug("GYRO_YOUT_H[%d]",GetData(MPU_IIC_List,GYRO_YOUT_H),0);
		DeBug("GYRO_ZOUT_H[%d]",GetData(MPU_IIC_List,GYRO_ZOUT_H),0);
		
	}
}