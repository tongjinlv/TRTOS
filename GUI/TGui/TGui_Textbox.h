/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TGUI_TEXTBOX_H_
#define _TGUI_TEXTBOX_H_
#include <Include.h>
typedef struct
{
    TGUI_ControlBase Control;
	uint16 ForeColor;
	uint16 BackColor;
	uint8  Text[TGUI_Textbox_Lenth];					//�ı�������
	uint8  MaxLength;									//��������ַ�����
	uint8  EditType;									//�ı���������������
	void  (*OnFocus)  (uint16 ID);						//�ı����ý����¼�
	void  (*UnFocus)  (uint16 ID);						//�ı���ʧȥ�����¼�	
	void  (*EntryEdit)(uint16 ID);						//�ı������༭�¼�
	void  (*ExitEdit) (uint16 ID);						//�ı������༭�¼�	
	void  (*OnKeyEdit)(uint16 ID,uint8 KeyValue);		//�ı���༭�ص�����	
}TGUI_Textbox; 

uint8	TGUI_Textbox_SetText(TGUI_Textbox *CurTextbox,void *NewText);			//�����ı����ı�
uint8  *TGUI_Textbox_GetText(TGUI_Textbox *CurTextbox);							//��ȡ�ı����ı�
uint8	TGUI_Textbox_ApendText(TGUI_Textbox *CurTextbox,void *NewText);			//ƴ���ı����ı�
void	TGUI_Textbox_ClearText(TGUI_Textbox *CurTextbox);						//���ı����ı�
void	TGUI_Textbox_SetNumber(TGUI_Textbox *CurTextbox,f32 Number,uint8 DP);	//�����ı�����ʾ����
f32		TGUI_Textbox_GetNumber(TGUI_Textbox *CurTextbox);						//�Ի�ȡ�ı����е�����ֵ(������������ֵĻ�)
void	TGUI_Textbox_SetColor(TGUI_Textbox *CurTextbox,u16 Fcolor,u16 Bcolor);	//�����ı���ɫ��
void 	TGUI_Textbox_ReDraw(void *Object,uint8 State);							//ˢ���ػ��ı���
void	TGUI_Textbox_Hidden(TGUI_Textbox *CurTextbox);							//�����ı���ؼ�
void	TGUI_Textbox_Show(TGUI_Textbox *CurTextbox);							//��ʾ�ı���ؼ�
uint8	TGUI_Textbox_ValueEdit(TGUI_Textbox *CurTextbox,uint8 Key);				//�ı����ַ�����༭
uint8 	TGUI_Textbox_Event(void *Object,uint8 EventType,uint8 EventValue);		//�ı����¼�����
void	TGUI_Textbox_Create(u16 ID,u16 SX,u16 SY,u16 W,u16 H,void *InitText,u8 Style,u8 Action,TGUI_Textbox *NewTextbox);	//�����ı���ؼ�

#endif
