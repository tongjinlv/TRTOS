/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TGUI_LABEL_H_
#define _TGUI_LABEL_H_
#include <Include.h>
#include <Gui_Include.h>
#include <TGUI_Label.h>

typedef struct{
  TGUI_ControlBase Control;    
	uint16 ForeColor;  									//��ǩ��ʾǰ��ɫ
	uint16 BackColor;									//��ǩ��ʾ����ɫ
	uint16 BorderColor;									//��ǩ�߿�ɫ��
	uint8  Alignment;									//��ǩ�ı����뷽ʽ
	TGUI_FontType  Font;										//��ʾ����
	uint8  Text[TGUI_Label_Lenth];						//��ǩ�ı�����
}TGUI_Label;


void TGUI_Label_ReDraw(void *Object,uint8 State);
void TGUI_Label_Create(uint16 ID,uint16 SX,uint16 SY,uint16 W,uint16 H,void *InitText,uint8 Style,TGUI_Label *NewLabel);
void TGUI_Label_SetColor(TGUI_Label *CurLabel,uint16 Fcolor,uint16 Bcolor,uint16 Dcolor);
uint8 TGUI_Label_SetText(TGUI_Label *CurLabel,void *NewText);
#endif 
