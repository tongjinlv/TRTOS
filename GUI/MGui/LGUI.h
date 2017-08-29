/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _LGUI_H_
#define _LGUI_H_
#include <Include.h>


#define Menu_StartX 10
#define Menu_StartY 50

typedef enum
{
   Draw_All=0xff,
   Draw_Title=0x01,
   Draw_Value=0x02,
   Draw_Clear=0x04,
   Draw_Base=0x08
}LPageDrawMode;
typedef enum
{
   ME_Null=0x00,//û���κ�����
   ME_Menu=0x01,//�˵���
   ME_Task=0x02
}LMenuEnum;
#define MenuEnumMax 4
typedef enum
{
   VT_int8=0x10,
   VT_uint8=0x20,
   VT_int16=0x30,
   VT_uint16=0x40,
   VT_int32=0x50,
   VT_uint32=0x60,
   VT_float=0x70,
   VT_Write=0x80,
   VT_Eeprom=0x08
}LValue_Type;//��λΪС����λ��
typedef struct
{
    char *Option;
    char *Unit;
    uintbus Value;
    uint8   VType;    
}LMenu;
typedef struct 
{
    uint8 Menu_Flag;    
    uint8 DrawMode;
    Func  CurFunc;
    Func  NextFunc;
    uint8 CurMode;
    uint8 PageDeep;
    uint8 DeepRecord[5];
    uint8 Index;
    uint8 *Title;
    uintbus SelectValue;
    uint8 SelectType;
}LMenuStruct;

extern LMenuStruct PageMenu;




#endif

