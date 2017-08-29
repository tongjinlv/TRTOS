/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TGUI_BASE_H_
#define _TGUI_BASE_H_
#include <Include.h>

#define TGUI_STYLE_3D		0
#define TGUI_SoftKeyboard_En 1


/*-------------------------------------------------------------------------
TGUI������Ϣ�ṹ����
-------------------------------------------------------------------------*/
typedef struct
{
	uint8 KeyType;				//�����¼�����
	uint8 KeyValue;				//���̼�ֵ
	uint8 KeyTime;				//��ʱ�����
}TGUI_KeyMsg;

/*-------------------------------------------------------------------------
TGUI��������Ϣ�ṹ����
-------------------------------------------------------------------------*/
typedef struct
{
	uint8  TouchType;				//�����¼�����
	uint16 TouchValueX;				//����Xֵ
	uint16 TouchValueY;				//����Yֵ
	uint8  TouchTime;				//����ʱ�����
}TGUI_TouchMsg;


typedef struct
{
	uint8  TP;														//�ؼ�Ԫ������
	uint16 ID;														//�ؼ�ID��
	uint16 SX;														//�ؼ�λ��������SX
	uint16 SY;														//�ؼ�λ��������SY
	uint16 EX;														//�ؼ�λ��������EX
	uint16 EY;														//�ؼ�λ��������EY
	uint8  State;													//�ؼ���ǰ״̬
	uint8  Style;													//�ؼ��Ļ�����ʽ
	uint8  Action;													//�ؼ�����Ϊ��ʽ
	void * PrevControl;												//ָ��ǰһ���ؼ�
	void * NextControl;											   	//ָ���һ���ؼ�
  struct _TGUI_Window *ParentWindow;								//ָ��ؼ��ĸ�����	
	void  (*ReDraw)(void *Object,uint8 Param);					  	//����ؼ����ػ淽��
	uint8 (*Event) (void *Object,uint8 EventType,uint8 EventValue);	//�ؼ��¼�����ӿ�
	void *Control;
}TGUI_ControlBase;

#define TGUI_DefaultFont	TGUI_FontType_16X16

void TGUI_Draw_ObjectPopup(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 FaceColor);
void TGUI_Draw_ObjectDown(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 FaceColor);
void TGUI_Draw_ObjectIn(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 FaceColor);


#endif
