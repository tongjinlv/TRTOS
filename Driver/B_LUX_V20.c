/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
//***************************************
// B_LUX_V20�ɼ�����
//****************************************

#include <B_LUX_V20.h>

void IIC_WriteCmd(const GPIO_InitStruct *Pin_Maps,uint8 REG_Address)
{
  IIC_Start(Pin_Maps);                
  IIC_SendByte(Pin_Maps,B_LUX_Addr);  
  IIC_SendByte(Pin_Maps,REG_Address);  
  IIC_Stop(Pin_Maps);                  
}

uint32 IIC_Reads(const GPIO_InitStruct *Pin_Maps)
{   
  uint8 i;	
	uint8    BUF_0[4];                       //�������ݻ�����      	
	uint16   dis_data_0;   
	uint32 temp;
  IIC_Start(Pin_Maps);                          //��ʼ�ź�
  IIC_SendByte(Pin_Maps,B_LUX_Addr+1);        //�����豸��ַ+���ź�
  for (i=0; i<3; i++)                        //������ȡ6����ַ���ݣ��洢��BUF
  {
    BUF_0[i] = IIC_RecvByte(Pin_Maps);          //BUF[0]�洢0x32��ַ�е�����
    if (i == 3)
    {
      IIC_SendAck(Pin_Maps,1);                   //���һ��������Ҫ��NOACK
    }
    else
    {		
      IIC_SendAck(Pin_Maps,0);                   //��ӦACK
    }
  }
  IIC_Stop(Pin_Maps);                           //ֹͣ�ź�
  Tos_TaskDelay(5);
	dis_data_0=BUF_0[0];
  dis_data_0=(dis_data_0<<8)+BUF_0[1];
  temp=(float)dis_data_0/1.2;
  return (uint32)(temp*1.4);
}

void B_LUX_Init(const GPIO_InitStruct *List)
{
  GPIO_InitList(List);
  Tos_TaskDelay(300);	  
  IIC_WriteCmd(List,0x01); 
}

uint32 B_LUX_GetLux(const GPIO_InitStruct *List)
{  
  uint32 temp;
  IIC_WriteCmd(List,0x01);   
  IIC_WriteCmd(List,0x10);  
  Tos_TaskDelay(180);     
  temp=IIC_Reads(List);     
  IIC_WriteCmd(List,0x00);   
  return temp;
} 
