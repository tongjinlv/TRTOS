/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Gui_include.h>
#include <Tools_Include.h>
#include <TGUI_Button.h>                                                  
        







/*------------------------------------------------------------------------------
 Func: ��ʾ��ť�ı�
 Time: 2009-12-26
 Ver.: V1.0
 Note:
------------------------------------------------------------------------------*/
static void TGUI_Button_ShowText(TGUI_Button *CurButton)
{		
	  TGUI_ControlBase *P=&(CurButton->Control);
	  TGUI_Set_Font(CurButton->Font);
	  TGUI_Set_Color(CurButton->ForeColor,Null,CurButton->BackColor,Null);
    TGUI_Draw_String(P->SX,P->SY,P->EX,P->EY,CurButton->Text,Align_CenterCenter);
}


/*------------------------------------------------------------------------------
 Func: �尴ť�ı�����
 Time: 2009-12-26
 Ver.: V1.0
 Note:
------------------------------------------------------------------------------*/
static void TGUI_Button_ClearText(TGUI_Button *CurButton)
{
    TGUI_ControlBase *P=&(CurButton->Control);
	CurButton->Text[0]='\0';
	if(CurButton->Control.ParentWindow==CurFocusWindow){
		if(TGUI_STYLE_3D){
			TGUI_3D_Draw_ObjectBody(P->SX,P->SY,P->EX,P->EY,P->State);
		}else{
			TGUI_Fill_Rectangle(P->SX+2,P->SY+2,P->EX-2,P->EY-2,CurButton->BackColor);
		}
	}
}

/*------------------------------------------------------------------------------
 Func: ���ð�ť�ı�
 Time: 2009-12-26
 Ver.: V1.0
 Note: 
------------------------------------------------------------------------------*/
void TGUI_Button_SetText(TGUI_Button *CurButton,void *NewText)
{
	TGUI_Button_ClearText(CurButton);
	BufferCoppy(NewText,CurButton->Text,TGUI_Button_Lenth-1);	
	if(CurButton->Control.ParentWindow==CurFocusWindow)
	{
		TGUI_Button_ShowText(CurButton);
	}	
}


/*------------------------------------------------------------------------------
 Func: ��ȡButton�ı�
 Time: 2009-12-26
 Ver.: V1.0
 Note:
------------------------------------------------------------------------------*/
uint8 *TGUI_Button_GetText(TGUI_Button *CurButton)
{
    return CurButton->Text;
}

void TGUI_Button_ReDraw(void *Object,uint8 State)
{
	TGUI_Button *CurButton=(TGUI_Button *)Object;
	TGUI_ControlBase *P=&(CurButton->Control);
	switch(State)
	{
		case TGUI_State_ReLoad:
				 TGUI_Draw_ObjectPopup(P->SX,P->SY,P->EX,P->EY,CurButton->BackColor);
				 TGUI_Button_ShowText(CurButton);
			   P->State=TGUI_State_UnFocus;					//״̬����Ϊ�Ѽ���״̬	
		break;
		case TGUI_State_OnFocus:							//��ť��ý���
				 TGUI_Draw_ObjectPopup(P->SX,P->SY,P->EX,P->EY,CurButton->BackColor);
         TGUI_Draw_DotRectangle(P->SX+2,P->SY+2,P->EX-2,P->EY-2,Color_Black,CurButton->BackColor);
				 TGUI_Button_ShowText(CurButton);
			   P->State=State;	
		break;
		case TGUI_State_UnFocus:							//��ťʧȥ����			
				 TGUI_Draw_ObjectPopup(P->SX,P->SY,P->EX,P->EY,CurButton->BackColor);
			   TGUI_Button_ShowText(CurButton);
			   P->State=State;																		 
		break;	
		case TGUI_State_EntryEdit:							//��ť������
				 TGUI_Draw_ObjectDown(P->SX,P->SY,P->EX,P->EY,CurButton->BackColor);
				 TGUI_Draw_DotRectangle(P->SX+2,P->SY+2,P->EX-2,P->EY-2,Color_Black,CurButton->BackColor);
			   TGUI_Button_ShowText(CurButton);
			   P->State=State;									//״̬����Ϊ�Ѽ���״̬			
    break;
		case TGUI_State_ExitEdit:							//��ť����
				 TGUI_Draw_ObjectPopup(P->SX,P->SY,P->EX,P->EY,CurButton->BackColor);
				 TGUI_Draw_DotRectangle(P->SX+2,P->SY+2,P->EX-2,P->EY-2,Color_Black,CurButton->BackColor);
			   TGUI_Button_ShowText(CurButton);
			   P->State=TGUI_State_OnFocus;					//״̬����Ϊ�Ѽ���״̬			
    break;
		case TGUI_State_Hidden:
			   TGUI_Window_DrawBackGround(P->ParentWindow,P->SX,P->SY,P->EX,P->EY);
			   P->State=TGUI_State_Hidden;
		break;	
	}
	
}
/*------------------------------------------------------------------------------
 Func: �ػ浱ǰButton�ؼ�
 Time: 2009-12-26
 Ver.: V1.0
 Note:
------------------------------------------------------------------------------*/
void _TGUI_Button_ReDraw(void *Object,uint8 State)
{                                 
	TGUI_Button *CurButton=(TGUI_Button *)Object;
	TGUI_ControlBase *P=&(CurButton->Control);
    switch(State){
		case TGUI_State_ReLoad:								//��ť���ص�����
			if(TGUI_STYLE_3D){
				TGUI_3D_Draw_ObjectBody(P->SX,P->SY,P->EX,P->EY,TGUI_State_UnFocus);
				TGUI_3D_Draw_ObjectBorder(P->SX,P->SY,P->EX,P->EY,TGUI_State_UnFocus);
			}else{
				TGUI_Draw_ObjectPopup(P->SX,P->SY,P->EX,P->EY,CurButton->BackColor);
			}
			TGUI_Button_ShowText(CurButton);
			P->State=TGUI_State_UnFocus;					//״̬����Ϊ�Ѽ���״̬																				 
			break;
		case TGUI_State_OnFocus:							//��ť��ý���
			if(TGUI_STYLE_3D){
				TGUI_3D_Draw_ObjectBody(P->SX,P->SY,P->EX,P->EY,TGUI_State_OnFocus);
				TGUI_3D_Draw_ObjectBorder(P->SX,P->SY,P->EX,P->EY,TGUI_State_OnFocus);			
			}else{
				TGUI_Draw_ObjectPopup(P->SX,P->SY,P->EX,P->EY,CurButton->BackColor);
               	TGUI_Draw_DotRectangle(P->SX+2,P->SY+2,P->EX-2,P->EY-2,Color_Black,CurButton->BackColor);
			}
			TGUI_Button_ShowText(CurButton);
			P->State=State;	
			break;
        case TGUI_State_UnFocus:							//��ťʧȥ����			
			if(TGUI_STYLE_3D){
				TGUI_3D_Draw_ObjectBody(P->SX,P->SY,P->EX,P->EY,TGUI_State_UnFocus);
				TGUI_3D_Draw_ObjectBorder(P->SX,P->SY,P->EX,P->EY,TGUI_State_UnFocus);			
			}else{
				TGUI_Draw_ObjectPopup(P->SX,P->SY,P->EX,P->EY,CurButton->BackColor);
			}
			TGUI_Button_ShowText(CurButton);
			P->State=State;																		 
			break;
        case TGUI_State_EntryEdit:							//��ť������
			if(TGUI_STYLE_3D){
				TGUI_3D_Draw_ObjectBody(P->SX,P->SY,P->EX,P->EY,TGUI_State_EntryEdit);
				TGUI_3D_Draw_ObjectBorder(P->SX,P->SY,P->EX,P->EY,TGUI_State_EntryEdit);						
			}else{
				TGUI_Draw_ObjectDown(P->SX,P->SY,P->EX,P->EY,CurButton->BackColor);
				TGUI_Draw_DotRectangle(P->SX+2,P->SY+2,P->EX-2,P->EY-2,Color_Black,CurButton->BackColor);
			}
			TGUI_Button_ShowText(CurButton);
			P->State=State;									//״̬����Ϊ�Ѽ���״̬			
            break;
		case TGUI_State_ExitEdit:							//��ť����
			if(TGUI_STYLE_3D){
				TGUI_3D_Draw_ObjectBody(P->SX,P->SY,P->EX,P->EY,TGUI_State_OnFocus);
				TGUI_3D_Draw_ObjectBorder(P->SX,P->SY,P->EX,P->EY,TGUI_State_OnFocus);						
			}else{	
				TGUI_Draw_ObjectPopup(P->SX,P->SY,P->EX,P->EY,CurButton->BackColor);
				TGUI_Draw_DotRectangle(P->SX+2,P->SY+2,P->EX-2,P->EY-2,Color_Black,CurButton->BackColor);
			}
			TGUI_Button_ShowText(CurButton);
			P->State=TGUI_State_OnFocus;					//״̬����Ϊ�Ѽ���״̬			
            break;
		case TGUI_State_Hidden:
			TGUI_Window_DrawBackGround(P->ParentWindow,P->SX,P->SY,P->EX,P->EY);
			P->State=TGUI_State_Hidden;
			break;		        
	}
}


/*------------------------------------------------------------------------------
 Func: ���ð�ťɫ��
 Time: 2009-12-26
 Ver.: V1.0
 Note:
------------------------------------------------------------------------------*/
void TGUI_Button_SetColor(TGUI_Button *CurButton,uint16 Fcolor,uint16 Bcolor)
{
	CurButton->ForeColor=Fcolor;
	CurButton->BackColor=Bcolor;
	if(CurButton->Control.ParentWindow==CurFocusWindow)
	{
		TGUI_Button_ReDraw(CurButton,CurButton->Control.State);	
	}
}	


/*------------------------------------------------------------------------------
 Func: ����ť����
 Time: 2009-12-26
 Ver.: V1.0
 Note:
-----------------------------------------------------------------------------*/
void TGUI_Button_Hidden(TGUI_Button *CurButton)
{	
	if(CurButton->Control.ParentWindow==CurFocusWindow)
	{
		TGUI_Button_ReDraw(CurButton,TGUI_State_Hidden);			//�ػ�ؼ�
	}else{
		CurButton->Control.State=TGUI_State_Hidden;
	}
}

/*------------------------------------------------------------------------------
 Func: ����ť��ʾ
 Time: 2009-12-26
 Ver.: V1.0
 Note:
-----------------------------------------------------------------------------*/
void TGUI_Button_Show(TGUI_Button *CurButton)
{
	TGUI_ControlBase *P=&(CurButton->Control);
	if(P->State==TGUI_State_Hidden){
		if(P->ParentWindow->CurControl==CurButton)P->State=TGUI_State_OnFocus;
		else P->State=TGUI_State_ReLoad;
		if(P->ParentWindow==CurFocusWindow)TGUI_Button_ReDraw(CurButton,P->State);
	}
}


/*------------------------------------------------------------------------------
 Func: ����Button�¼�
 Time: 2010-3-25
 Ver.: V1.0
 Note: 
------------------------------------------------------------------------------*/
uint8 TGUI_Button_Event(void *Object,uint8 EventType,uint8 EventValue)
{
	uint8 Result=TGUI_Result_Null;
	TGUI_Button *CurButton=(TGUI_Button *)Object;
	TGUI_ControlBase *P=&(CurButton->Control);
	if(P->State==TGUI_State_Hidden)		return TGUI_Result_Ignore;				//�ؼ�����,����Ӧ�����¼�
	if(!(P->Action&TGUI_Action_Enable))	return TGUI_Result_Ignore;				//�ؼ�����,����Ӧ�����¼�
	switch(EventType){
		case TGUI_Event_KeyClickDown:  											//�а��������¼�
			switch(EventValue){								  
				case TGUI_Key_Ok:												
					TGUI_Button_ReDraw(CurButton,TGUI_State_EntryEdit);			//��ť�����¼�		
					break;				
				case TGUI_Key_Left:
					if(P->Action&TGUI_Action_TabDirH)Result=TGUI_Result_BackSpace;	//ˮƽTAB Left
					break;
				case TGUI_Key_Right:
					if(P->Action&TGUI_Action_TabDirH)Result=TGUI_Result_NextSpace;	//ˮƽTAB Right
					break;
				case TGUI_Key_Up:
					if(P->Action&TGUI_Action_TabDirV)Result=TGUI_Result_BackSpace;	//��ֱTAB Up
					break;
				case TGUI_Key_Down:
					if(P->Action&TGUI_Action_TabDirV)Result=TGUI_Result_NextSpace;	//��ֱTAB Down
					break;
				default: Result=TGUI_Result_Ignore;
					break;
			}
			break;
		case TGUI_Event_KeyClickUp:												
			switch(EventValue){
				case TGUI_Key_Ok:													//��ť�����¼�
					TGUI_Button_ReDraw(CurButton,TGUI_State_ExitEdit);				//�ػ水ť������ʽ
					if(CurButton->OnClick!=0)CurButton->OnClick(P->ID);				//����ť�¼��ص�					
					break;
				default: Result=TGUI_Result_Ignore;
					break;
			}
			break;
		case TGUI_Event_TouchDown:
			TGUI_Button_ReDraw(CurButton,TGUI_State_EntryEdit);						//���������¼�
			break;
		case TGUI_Event_TouchUp:
			if(P->State!=TGUI_State_OnFocus){
				TGUI_Button_ReDraw(CurButton,TGUI_State_ExitEdit);						//�ػ水ť������ʽ			
			//	if( (TGUI_Mouse_X>P->SX) && (TGUI_Mouse_X<P->EX) &&	
			//		(TGUI_Mouse_Y>P->SY) && (TGUI_Mouse_Y<P->EY) )
			//	{
					if(CurButton->OnClick!=0)CurButton->OnClick(P->ID);						//�������¼��ص�								
			//	}
			}
			break;
		case TGUI_Event_ControlOnFocus:		    									//�ؼ���ý����¼�
			TGUI_Button_ReDraw(CurButton,TGUI_State_OnFocus);						//����ť��ý����¼�
			if(CurButton->OnFocus!=0)CurButton->OnFocus(P->ID);						//�����ý���ص�
			break;
		case TGUI_Event_ControlUnFocus:												//�ؼ�ʧȥ�����¼�
			TGUI_Button_ReDraw(CurButton,TGUI_State_UnFocus);						//����ťʧȥ�����¼�
			if(CurButton->UnFocus!=0)CurButton->UnFocus(P->ID);						//����ʧȥ����ص�
			break;
		default: Result=TGUI_Result_Ignore;
			break;				 
	}
	return Result;	
}


/*------------------------------------------------------------------------------
 Func: ����Button�ؼ�
 Time: 2009-12-26
 Ver.: V1.0
 Note:
------------------------------------------------------------------------------*/
void TGUI_Button_Create(uint16 ID,uint16 SX,uint16 SY,uint16 W,uint16 H,void *InitText,uint8 Style,TGUI_Button *NewButton)
{	
	TGUI_ControlBase *P=&(NewButton->Control);
	P->TP=TGUI_Type_Button;										//д��ť����
	P->ID=ID;					 								//д��ťID			
    P->SX=SX;													//�������λ��
    P->SY=SY;
    P->EX=SX+W;
    P->EY=SY+H; 
	P->State=TGUI_State_UnLoad;									//��ʼ����ťΪδ����״̬
    P->Style=Style;												//�ؼ�Ĭ����ʽ
	P->Action=TGUI_Action_EnOnFucus|TGUI_Action_EnEdit|TGUI_Action_TabDirV|TGUI_Action_TabDirH|TGUI_Action_Enable;
	P->PrevControl=0;
	P->NextControl=0;
	P->ParentWindow=0;											//д��ť������
	P->ReDraw=TGUI_Button_ReDraw;								//���尴ť�ػ淽��
	P->Event=TGUI_Button_Event;									//���尴ť�¼�����
	StringCoppy(InitText,NewButton->Text);					//��ʼ����ť�ı�
	NewButton->ForeColor=TGUI_Button_ForeColor;
	NewButton->BackColor=TGUI_Button_BackColor;
	NewButton->Font=TGUI_DefaultFont;
	NewButton->OnFocus=0;
	NewButton->UnFocus=0;
	NewButton->OnClick=0;
	P->Control=NewButton;
}



