/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TGUI_WINDOW_H_
#define _TGUI_WINDOW_H_

#include <Include.h>
#include <Tos_Include.h>
#include <Gui_Include.h>


/*-------------------------------------------------------------------------
 �ṹ����
-------------------------------------------------------------------------*/
typedef struct _TGUI_Window
{		
	TGUI_ControlBase Control;									//GUI�����ṹ
	uint8  Mark;												//���ڵ�˽�б�־
	void * Title;												//���ڱ���
	uint16 BackColor;											//���ڱ���ɫ
	uint16 ForeColor;											//����ǰ��ɫ		
	TGUI_FontType Font;
	void * BackImage;											//���ڱ���ͼƬ				
	uint8  ControlsCount;										//��ǰ������Ԫ�ظ���ͳ��
	void * CurControl;											//��ǰ�����еĽ���Ԫ��
	uint8  Buffer[TGUI_Window_Buffer_Lenth];					//�������ڹ�������
	uint8 (*OnEvent)(uint16 ID,Tos_ArrayMessage *Msg);		//������Ϣ�¼��ص�
	void  (*OnPaint)(uint16 ID);
	Tos_Timer Timer;											//���ڶ�ʱ��
	uint16 CursorSX;											//�����ڹ��λ��X
	uint16 CursorSY;											//�����ڹ��λ��Y
}TGUI_Window;		


extern TGUI_Window *PreFocusWindow;								//ǰһ�����㴰��
extern TGUI_Window *CurFocusWindow;								//��ǰ�����

							
void * TGUI_GetType_OnFocus(TGUI_Window *CurWindow);
void TGUI_Window_DrawBackGround(TGUI_Window *CurWindow,uint16 SX,uint16 SY,uint16 EX,uint16 EY);
void TGUI_Window_DrawBody(TGUI_Window *CurWindow);
void TGUI_Window_ReDraw(void *Object,uint8 State);
uint8 TGUI_Window_Event(void *Object,uint8 EventType,uint8 EventValue);
void TGUI_Window_CursorShow(TGUI_Window *CurWindow);
void TGUI_Window_SetCursor(TGUI_Window *CurWindow,uint16 SX,uint16 SY,uint8 Enable);
void TGUI_Window_AddControl(TGUI_Window *CurWindow,void *Control);
//void TGUI_Window_OverCut(Rectangle *Rect1,Rectangle *Rect2);
void TGUI_Window_Move(TGUI_Window *CurWindow,uint16 SX,uint16 SY);
																				;
uint8 TGUI_Event_Filter(TGUI_Window *CurWindow,Tos_ArrayMessage *CurMsg);
uint8 TGUI_Window_BackSpace(void);
uint8 TGUI_Window_NextSpace(void);
uint16 TGUI_Window_GetEventControl(TGUI_Window *CurWindow,uint16 X,uint16 Y);
uint8 TGUI_Window_ControlsSetFocus(TGUI_Window *CurWindow,uint16 ID);
void * TGUI_Window_GetControl(TGUI_Window *CurWindow,uint16 ID);
void TGUI_SetWindow_OnFocus(TGUI_Window *CurWindow);
void TGUI_Window_Create(uint16 ID,uint16 SX,uint16 SY,uint16 W,uint16 H,void *Title,uint8 Style,TGUI_Window *NewWindow);
void TGUI_Window_Config(TGUI_Window *CurWindow,uint16 Fcolor,uint16 Bcolor,void *ImageAddr);

#endif
