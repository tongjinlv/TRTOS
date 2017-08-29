/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_TP500\Ht1621_Driver.h>

uint8 DeviceId_HT1621=DeviceNull;


/*******************************************************************************
Func:LCD����оƬ�����ӳ�
Date:2016-3-11
Note:
*******************************************************************************/
void Ht1621_Delay(uint16 D)
{
	D*=3;
	while(D--);
}

/*******************************************************************************
Func:LCD IO��ʼ��
Date:2016-3-11
Note:
*******************************************************************************/
const GPIO_InitStruct IO_LCD_List[]=
{
	{GPIO_Speed_2MHz,GPIO_Mode_Out_PP,GPIOC,HT1621_CS|HT1621_WR|HT1621_DAT},//LCD�˿ڳ�ʼ��
	{0},
};
/*******************************************************************************
Func:LCDд������
Date:2016-3-11
Note:
*******************************************************************************/
void Ht1621Wr_Data(u8 Data, u8 cnt)
{
	u8 i;
	for (i = 0; i < cnt; i++)
	{
	 GPIO_ResetBits(GPIOC,HT1621_WR);  
	 Ht1621_Delay(3);
	 if (Data & 0x80)
	 {
			GPIO_SetBits(GPIOC,HT1621_DAT); 
	 }
	 else
	 {
			GPIO_ResetBits(GPIOC,HT1621_DAT);
	 }
	 Ht1621_Delay(3);
	 GPIO_SetBits(GPIOC,HT1621_WR); 
	 Data <<= 1;
	 Ht1621_Delay(1);
	}
}


/*******************************************************************************
Func:LCDд������
Date:2016-3-11
Note:
*******************************************************************************/
void Ht1621Wr_Cmd(u8 Cmd)   //д����Ҳ��������д������һ��ֻдһ��
{
	GPIO_ResetBits(GPIOC,HT1621_CS);  //CS = 0;  �����ף�׼��������
	Ht1621_Delay(3);
  Ht1621Wr_Data(0x80, 4); //д�������־ "100+0",�����ʽ="100+0+8λ�������ֽ�"
  Ht1621Wr_Data(Cmd, 8);  //д����������
	GPIO_SetBits(GPIOC,HT1621_CS);   //��д���ݾ��ٴ�����
	Ht1621_Delay(4);    //д���ݽ���
}
/*******************************************************************************
Func:LCDд��Ĵ���
Date:2016-3-11
Note:
*******************************************************************************/
void Ht1621_WriteReg(u8 Addr, u8 Data)   //���Կ����ĸ���
{
	GPIO_ResetBits(GPIOC,HT1621_CS);  //CS = 0;  �����ף�׼��������
	Ht1621_Delay(3);
	Ht1621Wr_Data(0xa0, 3);         //д�����ݱ�־101
	Ht1621Wr_Data(Addr << 2, 6);    //д���ַ����  ��Ϊ�����ǰ�λ�ģ�ֻ��
	Ht1621Wr_Data(Data << 4, 4);    //д������   ����������ϣ�ֻ�ú�4λ��
	GPIO_SetBits(GPIOC,HT1621_CS);     //���ߣ���ֹ������ 
}
/*******************************************************************************
Func:LCD ����д�Ĵ���
Date:2016-3-11
Note:
*******************************************************************************/
void Ht1621_WriteRegs(u8 SPaddr, u8* SpData, u8 Len)
{
	u8 i;
	if ((SPaddr + Len) > 31)return; 
	GPIO_ResetBits(GPIOC,HT1621_CS);  //CS = 0;  �����ף�׼��������
	Ht1621_WriteReg(0xa0, 3);         //д�����ݱ�־101
	Ht1621_WriteReg(SPaddr << 2, 6);  //д���ַ����
	for (i = 0; i < Len; i++)
	{
	Ht1621_WriteReg(SpData[i], 8);//д������//ѭ��һ��д2������
	} 
	GPIO_SetBits(GPIOC,HT1621_CS);  // //CS���ߣ�Ƭѡ����
}
/*******************************************************************************
Func:LCD ��ʼ��
Date:2016-3-11
Note:
*******************************************************************************/
void HT1621_Init(void)    //��ʼ��LCD   ����
{
	uint8 i=0;
	GPIO_InitList(IO_LCD_List);
	Ht1621Wr_Cmd(0x56);      //1/3duty 4com
	Ht1621Wr_Cmd(0x30);     //ʹ���ڲ�����
	Ht1621Wr_Cmd(0x00);    //����ϵͳ������LCDƫѹ������
	Ht1621Wr_Cmd(0x0a);    //��ֹ���Ź�
	Ht1621Wr_Cmd(0x03);     //��ϵͳ����
	Ht1621Wr_Cmd(0x06);     //��LCDƫѹ
	for(i=0;i<32;i++)Ht1621_WriteReg(i, 0xff);//ȫ��
}
/*******************************************************************************
Func:��ʾ�豸����
Date:2016-3-11
Note:
*******************************************************************************/
void DeviceMount_HT1621(void)
{
	DeviceId_HT1621=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_HT1621].DeviceId=DeviceId_HT1621;
	Tos_Device_Tab[DeviceId_HT1621].DeviceName="HT1621";
	Tos_Device_Tab[DeviceId_HT1621].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_HT1621].DeviceVirtue=DV_Task;//��ʼ����������
	Tos_Device_Tab[DeviceId_HT1621].DeviceState=NotBusy;
	Tos_Device_Tab[DeviceId_HT1621].Init=HT1621_Init;
	Tos_Device_Tab[DeviceId_HT1621].Note=Null;
	Tos_Device_Tab[DeviceId_HT1621].Write=Null;
	Tos_Device_Tab[DeviceId_HT1621].Read=Null;
	Tos_Device_Tab[DeviceId_HT1621].Exit=Null;
}

