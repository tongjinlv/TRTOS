/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _MGUI_H_
#define _MGUI_H_
#include <include.h>
#include <TGui_GBk_Driver.h>
 
typedef struct
{
	TGUI_FontType Title_Font;
	TGUI_FontType Menu_Font;
	
	
}MGUI_Style;
typedef enum MGUIOptionType
{
	MGOT_Menu=1,//�˵�ѡ��
	MGOT_OptionBool=3,//��������
	MGOT_OptionU32=4,//
	MGOT_OptionF32=5,//
	MGOT_OptionASCII=6,//
	MGOT_OptionFunc=0,
}MGUIOptionType;
typedef enum MGUIDrawMode
{
	MGDM_ReDraw=1,//�ػ�
	MGDM_ClrDrawOnly=2,//�������
	MGDM_ClrDraw=3,//�������
}MGUIDrawMode;

typedef struct MGUI_MenuStruct
{
	MGUIOptionType  OptionType;
	BOOL   SelectTrue;//ѡ��Ϊ��
	char  *OptionName;//ѡ����
	uintbus OptionValue;//ѡ��ֵ
	struct MGUI_MenuStruct *NextMenu;//��һ���˵�
	struct MGUI_MenuStruct *SubMenu;//�Ӳ˵�
	struct MGUI_MenuStruct *ParentMenu;//���˵�
	struct MGUI_MenuStruct *PrevMenu;//��һ���ڵ�
}MGUI_MenuStruct;
void MGUI_MenuReDraw(MGUIDrawMode Mode);
void MGUI_TestTask(void *Tags);
void MGUI_GetPutIn(void);

#endif
