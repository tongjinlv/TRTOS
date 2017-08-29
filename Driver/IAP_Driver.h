/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _IAP_DRIVER_H_
#define _IAP_DRIVER_H_
#include <include.h>

#define PAGE_SIZE                         (512)  
#define EnValueOffset      0x4c00
#define ApplicationOffset  0x5000
#define BootLoaderAddress  NVIC_VectTab_FLASH
#define ApplicationAddress  (BootLoaderAddress+ApplicationOffset)//Ӧ�ó��������������ַ��������
#define  ENVALUE_ADDR_BASE  (FLASH_ADDR_BASE+EnValueOffset)
typedef enum 
{
	AFT_SPINand=1,//��SPI nandflash�ϻ�ȡ�̼�
	AFT_IIC=2,//��iic�����豸�ϻ�ȡ�̼�
	AFC_FLASH=3,//�������ڴ��ϻ�ȡ�̼�
}AppFromType;
typedef struct
{
	ConfigHeadStruct CHS;
	uint32 AppToAddr;//App��Ҫ���ص��ľ�����ַ
	uint32 AppFromAddr;//App�����ĸ���ַ��ȡ
	AppFromType AppFromType;//App��Դ��������
	uint32 AppSize;//Ӧ�ô�С(bytes)
	uint8 UpdateApp;//True�й̼���Ҫ��������Ӧ����True��boot�ü�
	uint8 UpdateOver;//��������True����ת��Ӧ�ú���Ӧ����False��Ӧ��û�ü٣�ֱ�����´ο���ʱ�ع�
	uint16 Version;
}EnValue;

#endif
