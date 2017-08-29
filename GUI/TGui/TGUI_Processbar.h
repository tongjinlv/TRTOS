/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TGUI_PROCESSBAR_H_
#define _TGUI_PROCESSBAR_H_

#include <Include.h>

typedef struct
{
    TGUI_ControlBase Control;
	uint16 FontColor;				  //������ɫ
	uint16 BackColor;				  //����������ɫ
	uint16 ForeColor;				  //������ǰ��ɫ
	uint16 BorderColor;				  //�������߿�ɫ��
	uint16 MaxValue;				  //���������ֵ��
	uint16 CurValue;  				  //��������ǰֵ��
	uint8  CurProcess;				  //��������ǰ��ʾ����ֵ
	void  (*Changed)(uint8 ID);       //������ֵ�����ı��ʱ�򴥷��¼� 
}TGUI_ProcessBar;


void  TGUI_ProcessBar_SetProcess(TGUI_ProcessBar *CurProcessBar,uint16 Value);
uint8 TGUI_ProcessBar_GetProcess(TGUI_ProcessBar *CurProcessBar);
void  TGUI_ProcessBar_SetColor(TGUI_ProcessBar *CurProcessBar,uint16 Fcolor,uint16 Bcolor,uint16 Dcolor);
void  TGUI_ProcessBar_ReDraw(void *Object,uint8 State);
uint8 TGUI_ProcessBar_Event(void *Object,uint8 EventType,uint8 EventValue);
void  TGUI_ProcessBar_Create(u16 ID,u16 SX,u16 SY,u16 W,u16 H,u16 MaxValue,u8 Style,u8 Action,TGUI_ProcessBar *NewProcessBar);


#endif
