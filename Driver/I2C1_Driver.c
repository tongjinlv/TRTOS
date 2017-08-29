/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <I2C1_Driver.h>
uint8 DeviceId_EEPROM=DeviceNull;

void I2C1_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	I2C_InitTypeDef I2C_InitStructure;

	/* Configure I2C1 pins: SCL and SDA */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;//��©���
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* I2C configuration */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;//���� I2CΪ I2Cģʽ
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;//I2C����ģʽ Tlow / Thigh = 2

	I2C_InitStructure.I2C_OwnAddress1 = I2C1_SLAVE_ADDRESS7;//���õ�һ���豸��ַ

	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;//ʹ��Ӧ��
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//Ӧ�� 7λ��ַ
	I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;//����ʱ��Ƶ��

	/* I2C Peripheral Enable */
	I2C_Cmd(I2C1, ENABLE);//ʹ��I2C����
	/* Apply I2C configuration after enabling it */
	I2C_Init(I2C1, &I2C_InitStructure);
}

void I2C_EE_PageWrite(u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite)
{
	I2C_GenerateSTART(I2C1, ENABLE);//������ʼλ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //��� EV5
	I2C_Send7bitAddress(I2C1, EEPROM_ADDRESS, I2C_Direction_Transmitter);//����������ַ
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); 
	//ADDR=1����� EV6 
	I2C_SendData(I2C1, WriteAddr);    //EEPROM �ľ���洢��ַλ��
	while(! I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//��λ�Ĵ����ǿգ����ݼĴ����Ѿ��գ����� EV8���������ݵ� DR �ȿ�������¼�
	while(NumByteToWrite--)    //���� while ѭ��  ��������
	{
	I2C_SendData(I2C1, *pBuffer); //��������
	pBuffer++; //����ָ����λ
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//���EV8
	}
	I2C_GenerateSTOP(I2C1, ENABLE);//����ֹͣ�ź�
}

void I2C_EE_WaitEepromStandbyState(void)      
{
	vu16 SR1_Tmp = 0;
	do
	{
	I2C_GenerateSTART(I2C1, ENABLE);//������ʼ�ź�
	SR1_Tmp = I2C_ReadRegister(I2C1, I2C_Register_SR1);//�� SR1 �Ĵ���
	I2C_Send7bitAddress(I2C1, EEPROM_ADDRESS, I2C_Direction_Transmitter);//����������ַ����¼�
	}while(!(I2C_ReadRegister(I2C1, I2C_Register_SR1) & 0x0002));//������ղ����ӻ���Ӧ��NACK����˵�� EEPROM �������ڹ�����ֱ����ɲ�������ѭ���壡
	I2C_ClearFlag(I2C1, I2C_FLAG_AF);//��� AF ��־λ
	I2C_GenerateSTOP(I2C1, ENABLE); //����ֹͣ�ź�
}
void I2C_EE_BufferRead(u8* pBuffer, u8 ReadAddr, u16 NumByteToRead)//��Ҫ������ʼ�ź�
{ 
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //���ÿ⺯����� I2C �����Ƿ��� BUSY ״̬
	I2C_GenerateSTART(I2C1, ENABLE);//�����ź�
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));//��� EV5
	I2C_Send7bitAddress(I2C1, EEPROM_ADDRESS, I2C_Direction_Transmitter);//д��������ַ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//��� EV6
	I2C_SendData(I2C1, ReadAddr);  //���Ͷ��ĵ�ַ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//��� EV8
	I2C_GenerateSTART(I2C1, ENABLE);//�����ź�
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));//��� EV5
	I2C_Send7bitAddress(I2C1, EEPROM_ADDRESS, I2C_Direction_Receiver);//��������ַ����������Ϊ��
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));//���EV6
	while(NumByteToRead) 
	{ 
	if(NumByteToRead == 1)//ֻʣ�����һ������ʱ���� if ���
	{
	I2C_AcknowledgeConfig(I2C1, DISABLE);//�����һ������ʱ�ر�Ӧ��λ
	I2C_GenerateSTOP(I2C1, ENABLE);//���һ������ʱʹ��ֹͣλ
	}
	if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)) //��ȡ����
	{ 
	*pBuffer = I2C_ReceiveData(I2C1);//���ÿ⺯��������ȡ���� pBuffer
	pBuffer++; //ָ����λ
	NumByteToRead--;//�ֽ����� 1 
	} 
	}
	I2C_AcknowledgeConfig(I2C1, ENABLE);//��Ӧ��λʹ�ܻ�ȥ���ȴ��´�ͨ��
}


void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite)
{
	u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;
	Addr = WriteAddr % I2C_PageSize;//�鿴����ĵ�ַ�ǲ��� 8 ��������
	count = I2C_PageSize -  Addr;//��ʾ������һҳҳ�׵�ַ�ľ��루��������
	NumOfPage =   NumByteToWrite / I2C_PageSize;//���һ���ж���ҳ
	NumOfSingle = NumByteToWrite % I2C_PageSize;//�������һҳ�����ݵ�����
	if(Addr == 0) //�������ĵ�ַ����ҳ��ַ
	{
	if(NumOfPage == 0) //�������һҳ����
	{
	I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);//����д������NumOfSingle ����һҳ��������Ϊʵ��
	I2C_EE_WaitEepromStandbyState();//�ȴ� EEPROM ��������ڲ�����
	}
	/* If NumByteToWrite > I2C_PageSize */
	else  //���������һҳ����
	{
	while(NumOfPage--)//��һ�� while ѭ����ִ��ҳдѭ���������ж���ҳ��д���ٴ�
	{
	I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize); //����д��������I2C_PageSize ������Ϊʵ��ִ��ҳд
	I2C_EE_WaitEepromStandbyState();//�ȴ� EEPROM ��������ڲ�����
	WriteAddr +=   I2C_PageSize;//ÿִ����һ��ҳд��Ӧ�ĵ�ַҲ��Ҫ�� 8 ��λ
	pBuffer += I2C_PageSize;//����ָ���� 8 ��λ 
	}
	if(NumOfSingle!=0)//����в���һҳ������������ִ��
	{
	I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);//����д������NumOfSingle����һҳ��������Ϊʵ��
	I2C_EE_WaitEepromStandbyState();//�ȴ� EEPROM ��������ڲ�����
	}
	}
	}
	else //����ĵ�ַ������ҳ��ַ
	{
	if(NumOfPage== 0) //�������һҳ
	{
	I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);//����д������NumOfSingle ����һҳ��������Ϊʵ��
	I2C_EE_WaitEepromStandbyState();//�ȴ� EEPROM ��������ڲ�����
	}
	else//�����һҳ��һҳ����
	{
	NumByteToWrite -= count;//����ַ������ȱʡλ�ò������ݣ����ݵĶ��پ��� count��ֵ��NumByteToWrite ������ֵ���ǲ�������֮��ʣ��δ���͵�����
	NumOfPage =   NumByteToWrite / I2C_PageSize;//ʣ���ҳ��
	NumOfSingle = NumByteToWrite % I2C_PageSize;//����һҳ����������
	if(count != 0)//����ַ������ȱʡλ�ò�������
	{  
	I2C_EE_PageWrite(pBuffer , WriteAddr, count);//����д�������� count Ϊʵ�Σ�����ַȱʡ�����Ĳ��ֵ�ַ�����������
	I2C_EE_WaitEepromStandbyState();//�ȴ� EEPROM ��������ڲ�����
	WriteAddr += count;//���� count �󣬵�ַ����λ����һҳ���׵�ַ
	pBuffer += count;//����ָ���� count ��λ
	} 
	while(NumOfPage--)//��ʣ���ҳ������д�� EEPROM
	{
	I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize);//����д��������I2C_PageSize ������Ϊʵ��ִ��ҳд
	I2C_EE_WaitEepromStandbyState();//�ȴ� EEPROM ��������ڲ�����
	WriteAddr +=   I2C_PageSize;//����ַ�� 8 ��λ
	pBuffer += I2C_PageSize;   //������ָ���� 8 ��λ
	}
	if(NumOfSingle != 0)//������һҳ������д�� EEPROM
	{
	I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);//����д������NumOfSingle����һҳ��������Ϊʵ��
	I2C_EE_WaitEepromStandbyState();//�ȴ� EEPROM ��������ڲ�����
	}
	}
	}  
}
void EEPROM_Write(uint32 Addr,void *Data,uint16 Length)
{
	I2C_EE_PageWrite(Data,Addr,Length);
}
void EEPROM_Read(uint32 Addr,void *Data,uint16 Length)
{
	I2C_EE_BufferRead(Data,Addr,Length);
}

void EEPROM_SaveConfig(void *Data,uint8 Sector)
{
	Save_VoidConfig(EEPROM_Write,0,Data,Sector);
}
BOOL EEPROM_LoadConfig(void *Data,uint8 Sector)
{
	return Load_VoidConfig(EEPROM_Read,0,Data,Sector);
}

void DeviceMount_EEPROM()
{
	DeviceId_EEPROM=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_EEPROM].DeviceName="24C08";
	Tos_Device_Tab[DeviceId_EEPROM].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_EEPROM].DeviceVirtue=DV_Task;
	Tos_Device_Tab[DeviceId_EEPROM].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_EEPROM].Init=I2C1_Configuration;
	Tos_Device_Tab[DeviceId_EEPROM].Note=Null;
	Tos_Device_Tab[DeviceId_EEPROM].Write=Null;
	Tos_Device_Tab[DeviceId_EEPROM].Read=Null;
	Tos_Device_Tab[DeviceId_EEPROM].Exit=Null;
}

/*END OF FUNCTION*/


