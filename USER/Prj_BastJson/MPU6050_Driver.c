/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
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
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I			0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define	SlaveAddress	0xD0	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ

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
    R|=IIC_SendByte(IIC_Maps,SlaveAddress);   //�����豸��ַ+д�ź�
		R|=IIC_SendByte(IIC_Maps,REG_Address);    //�ڲ��Ĵ�����ַ��
    R|=IIC_SendByte(IIC_Maps,REG_data);       //�ڲ��Ĵ������ݣ�
    IIC_Stop(IIC_Maps);                   //����ֹͣ�ź�
	return R;
}
uint8 Single_ReadI2C(const GPIO_InitStruct *IIC_Maps,uint8 REG_Address)
{
	uint8 REG_data;
	uint8 R=0x00;
	IIC_Start(IIC_Maps);                 //��ʼ�ź�
	R|=IIC_SendByte(IIC_Maps,SlaveAddress);    //�����豸��ַ+д�ź�
	R|=IIC_SendByte(IIC_Maps,REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ	
	IIC_Start(IIC_Maps);                 //��ʼ�ź�
	R|=IIC_SendByte(IIC_Maps,SlaveAddress+1);  //�����豸��ַ+���ź�
	REG_data=IIC_RecvByte(IIC_Maps);       //�����Ĵ�������
	IIC_SendAck(IIC_Maps,1);
	IIC_Stop(IIC_Maps);  
	return REG_data;
}
void InitMPU6050(const GPIO_InitStruct *IIC_Maps)
{
	Single_WriteI2C(IIC_Maps,PWR_MGMT_1, 0x00);	//�������״̬
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
	return (uint16)(H<<8)+L;   //�ϳ�����
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