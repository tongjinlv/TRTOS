/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef __B_LUX_V20_H
#define __B_LUX_V20_H
#include <Include.h>
#include <STM32_CPU.h>


//���Ŷ���



#define	B_LUX_Addr	  0x46 //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�

void IIC_WriteCmd(const GPIO_InitStruct *Pin_Maps,uint8 REG_Address);
uint32 IIC_Reads(const GPIO_InitStruct *Pin_Maps);
void B_LUX_Init(const GPIO_InitStruct *List);
uint32 B_LUX_GetLux(const GPIO_InitStruct *List);

#endif
