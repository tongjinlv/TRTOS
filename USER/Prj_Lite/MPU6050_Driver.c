/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_Insect\MPU6050_Driver.h>
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
	Single_WriteI2C(IIC_Maps,CONFIG, 0x04);
	Single_WriteI2C(IIC_Maps,GYRO_CONFIG, 0x08);
	Single_WriteI2C(IIC_Maps,ACCEL_CONFIG, 0x08);

}
short GetData(const GPIO_InitStruct *IIC_Maps,uint8 REG_Address)
{
	uint8 H,L;
	H=Single_ReadI2C(IIC_Maps,REG_Address);
	L=Single_ReadI2C(IIC_Maps,REG_Address+1);
	return (uint16)(H<<8)+L;   //�ϳ�����
}
float  q0=1,q1=0,q2=0,q3=0;          
float  exInt=0,eyInt=0,ezInt=0; 

#define	Kp		0.8f                        
#define	Ki		0.001f                         
#define	halfT	0.004f 
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az,float *Angle,float *Angley,float *Yaw)
{
	float  norm;
	float  vx, vy, vz;
	float  ex, ey, ez;
	*Angle=0.0;
	*Angley=0.0;
	norm = sqrt(ax*ax + ay*ay + az*az);	//�Ѽ��ٶȼƵ���ά����ת�ɵ�ά����   
	ax = ax / norm;
	ay = ay / norm;
	az = az / norm;

		//	�����ǰ���Ԫ������ɡ��������Ҿ����еĵ����е�����Ԫ�ء� 
		//	�������Ҿ����ŷ���ǵĶ��壬��������ϵ������������ת����������ϵ��������������Ԫ��
		//	���������vx vy vz����ʵ���ǵ�ǰ��ŷ���ǣ�����Ԫ�����Ļ����������ϵ�ϣ����������
		//	������λ������
	vx = 2*(q1*q3 - q0*q2);
	vy = 2*(q0*q1 + q2*q3);
	vz = q0*q0 - q1*q1 - q2*q2 + q3*q3 ;

	ex = (ay*vz - az*vy) ;
	ey = (az*vx - ax*vz) ;
	ez = (ax*vy - ay*vx) ;

	exInt = exInt + ex * Ki;
	eyInt = eyInt + ey * Ki;
	ezInt = ezInt + ez * Ki;

	gx = gx + Kp*ex + exInt;
	gy = gy + Kp*ey + eyInt;
	gz = gz + Kp*ez + ezInt;

	q0 = q0 + (-q1*gx - q2*gy - q3*gz) * halfT;
	q1 = q1 + ( q0*gx + q2*gz - q3*gy) * halfT;
	q2 = q2 + ( q0*gy - q1*gz + q3*gx) * halfT;
	q3 = q3 + ( q0*gz + q1*gy - q2*gx) * halfT;

	norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
	q0 = q0 / norm;
	q1 = q1 / norm;
	q2 = q2 / norm;
	q3 = q3 / norm;

	*Angle  = asin(2*(q0*q2 - q1*q3 )) * 57.2957795f; // ����   ����ɶ�
	*Angley = asin(2*(q0*q1 + q2*q3 )) * 57.2957795f; // ���
	*Yaw = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;  
}


void GetAngle(GYRODataStruct *P)
{    
	short Gyro_y=0,Gyro_x=0,Gyro_z=0;           //Y�������������ݴ�
	short Accel_x=0,Accel_y=0,Accel_z=0;	      //X����ٶ�ֵ�ݴ�

	float  Angle_ax=0.0,Angle_ay=0.0,Angle_az=0.0;  //�ɼ��ٶȼ���ļ��ٶ�(������)
	float  Angle_gy=0.0,Angle_gx=0.0,Angle_gz=0.0;  //�ɽ��ٶȼ���Ľ�����(�Ƕ���)

	//������ �Ӽ�������������������������������������������������������������������������������������
	int   g_x=0,g_y=0,g_z=0;            							 //�����ǽ�������

	Accel_y= GetData(MPU_IIC_List,ACCEL_YOUT_H) ;	//��ȡ6050���ٶ�����
	Accel_x= GetData(MPU_IIC_List,ACCEL_XOUT_H) ;		   
	Accel_z= GetData(MPU_IIC_List,ACCEL_ZOUT_H) ;	

	Gyro_x = GetData(MPU_IIC_List,GYRO_XOUT_H)-g_x;//��ȡ6050���ٶ�����
	Gyro_y = GetData(MPU_IIC_List,GYRO_YOUT_H)-g_y;
	Gyro_z = GetData(MPU_IIC_List,GYRO_ZOUT_H)-g_z;

	Angle_ax = Accel_x/8192.0;        //�������û���
	Angle_ay = Accel_y/8192.0;
	Angle_az = Accel_z/8192.0;

	Angle_gx = Gyro_x/65.5*0.0174533;//�������û���
	Angle_gy = Gyro_y/65.5*0.0174533;
	Angle_gz = Gyro_z/65.5*0.0174533;
	IMUupdate(Angle_gx,Angle_gy,Angle_gz,Angle_ax,Angle_ay,Angle_az,&P->Angle,&P->Angley,&P->Yaw);
	
}
void Task_Gyro(void *Tags)
{
	GYRODataStruct *P=(GYRODataStruct *)Tags;
  GPIO_InitList(MPU_IIC_List);
	InitMPU6050(MPU_IIC_List);
	while(1)
	{
		Tos_TaskDelay(100);
		GetAngle(P);
		P->Temperature=(float)GetData(MPU_IIC_List,TEMP_OUT_H)/10;
		DeBug("X=[%.1f]Y=[%.1f] Z=%.1f T=%.1f",P->Angle,P->Angley,P->Yaw,P->Temperature,0);
	}
}

