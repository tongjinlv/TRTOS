/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/

#ifndef _TGUI_BUTTON_H_
#define _TGUI_BUTTON_H_

#include <TGUI_base.h>
#include <Gui_Include.h>

/*------------------------------------------------------------------------------
 Func: TGUI Button�ṹ
------------------------------------------------------------------------------*/
typedef struct
{		
	TGUI_ControlBase Control;										//��ť�����ṹ
	uint16	ForeColor;												//��ť�ı�ɫ��
	uint16  BackColor;												//��ť�ı�����ɫ��
	TGUI_FontType  Font;
  uint8 	Text[TGUI_Button_Lenth];  								//��ť�ı�	
	void	(*OnFocus)(uint16 ID);									//��ť��ý����¼��ص�����
	void	(*UnFocus)(uint16 ID);									//��ťʧȥ�����¼��ص�����
	void	(*OnClick)(uint16 ID);									//��ť�������¼��ص�����
}TGUI_Button;

void	TGUI_Button_SetText(TGUI_Button *CurButton,void *NewText);			//���ð�ť�ı�
uint8  *TGUI_Button_GetText(TGUI_Button *CurButton);						//��ȡ��ť�ı�
void	TGUI_Button_SetColor(TGUI_Button *CurButton,u16 Fcolor,u16 Bcolor);	//���ð�ťɫ��
void 	TGUI_Button_ReDraw(void *Object,uint8 State);						//ˢ���ػ水ť
void	TGUI_Button_Hidden(TGUI_Button *CurButton);							//���ذ�ť�ؼ�
void	TGUI_Button_Show(TGUI_Button *CurButton);							//��ʾ��ť�ؼ�
uint8 	TGUI_Button_Event(void *Object,uint8 EventType,uint8 EventValue);	//��ť�¼�����
void	TGUI_Button_Create(u16 ID,u16 SX,u16 SY,u16 W,u16 H,void *InitText,u8 Flag,TGUI_Button *NewButton);	//������ť�ؼ�

#endif

