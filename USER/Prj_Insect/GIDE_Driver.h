/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
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
}GIDE_Type;//低位为小数点位数

typedef  struct
{
	const char *Option;
	void *Value;
  uint8 Length;
	uint8 Note;//菜单类型Note=菜单深度
}GIDE_Struct;
typedef  struct
{
	const char *Option;
	void *Value;
}ECHO_Struct;
extern const GIDE_Struct GIDEList[];
#endif
