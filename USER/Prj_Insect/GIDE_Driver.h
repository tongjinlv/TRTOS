/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _GIDE_DRIVER_H_
#define _GIDE_DRIVER_H_
#include <Include.h>


#define FLASH_GIDE_PAGE 54
#define GIDE_ADDR_BASE  (FLASH_ADDR_BASE+FLASH_GIDE_PAGE*1024)


typedef enum
{
    GT_End=0x00,
		GT_U16U16U16=0x01,
		GT_U32=0x01,
		GT_I8I8=0x02,
		GT_U8U32=0x03,
}GIDE_Type;//��λΪС����λ��

typedef  struct
{
	const char *Option;
	void *Value;
  uint8 Length;
	uint8 Note;//�˵�����Note=�˵����
}GIDE_Struct;
typedef  struct
{
	const char *Option;
	void *Value;
}ECHO_Struct;
extern const GIDE_Struct GIDEList[];
#endif
