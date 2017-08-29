/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <TGui_Include.h>
#include <Tools_Include.h>
#include <TGUI_Label.h>


/******************************************************************************
 Func: �ػ浱ǰLabel�ؼ�
 Time: 2014-4-26
 Ver.: V1.0
 Note:
*******************************************************************************/
void TGUI_Label_ReDraw(void *Object,uint8 State)
{ 								
	TGUI_Label *CurLabel=(TGUI_Label *)Object;
	TGUI_ControlBase *P=&(CurLabel->Control);
	P->State=State;
    if(State!=TGUI_State_Hidden){								//�����ǩ�������¼� 		       		
		TGUI_Set_Font(CurLabel->Font);
		if(!(P->Style&TGUI_Style_NoFrame)){	
			TGUI_Draw_Rectangle(P->SX,P->SY,P->EX,P->EY,CurLabel->BorderColor);	
		}
		if(!(P->Style&TGUI_Style_NoBcolor)){						
			TGUI_Fill_Rectangle(P->SX+1,P->SY+1,P->EX-1,P->EY-1,CurLabel->BackColor);
			TGUI_Set_Color(CurLabel->ForeColor,Null,CurLabel->BackColor,Null);
			TGUI_Draw_FormatString(P->SX,P->SY,P->EX,P->EY,CurLabel->Text,CurLabel->Alignment);
		}else{
			TGUI_Set_Color(CurLabel->ForeColor,Null,CurLabel->BackColor,Null);
			TGUI_Draw_String(P->SX,P->SY,P->EX,P->EY,CurLabel->Text,CurLabel->Alignment);
		}		
		TGUI_Set_Font(TGUI_DefaultFont);
    }else{       
      TGUI_Fill_Rectangle(P->SX,P->SY,P->EX,P->EY,P->ParentWindow->BackColor);
    }    
}
/*******************************************************************************
 Func: ���ı���ǩд���ı�
 Time: 2014-3-25
 Ver.: V2.0
 Note: return 0/����ʧ��  1/���óɹ�
*******************************************************************************/
uint8 TGUI_Label_SetText(TGUI_Label *CurLabel,void *NewText)
{
	if(GetTextLength(NewText)>TGUI_Label_Lenth)return TGUI_Result_Error;
	StringCoppy(NewText,CurLabel->Text);
	if(CurFocusWindow==CurLabel->Control.ParentWindow){
		TGUI_Label_ReDraw(CurLabel,CurLabel->Control.State);				//�ػ��ı���
	}
	return TGUI_Result_Success;
}

/*******************************************************************************
 Func: ��ȡ�ı���ǩ������
 Time: 2014-12-26
 Ver.: V1.0
 Note:
*******************************************************************************/
uint8 * TGUI_Label_GetText(TGUI_Label *CurLabel)
{
    return CurLabel->Text;
}


/*******************************************************************************
 Func: ���ı���ǩ�����ı�
 Time: 2013-12-26
 Ver.: V1.0
 Note:
*******************************************************************************/
uint8 TGUI_Label_ApendText(TGUI_Label *CurLabel,void *NewText)
{
	uint8 i,j;
	i=GetTextLength(CurLabel->Text);					  			//����ԭ�ı����ַ�����
	j=GetTextLength(NewText);										//��������������
	if((i+j)<=TGUI_Label_Lenth){									//���㻺�����Ƿ�������
		StringEndingAppend(NewText,CurLabel->Text);					//ƴ�����ַ������ı���
		if(CurFocusWindow==CurLabel->Control.ParentWindow){
			TGUI_Label_ReDraw(CurLabel,CurLabel->Control.State);	//�ػ��ı���
		}
		return TGUI_Result_Success;
	}							
	return TGUI_Result_Error;							 				
}


/*******************************************************************************
 Func: ���ı���ǩ���ı�����
 Time: 2013-12-26
 Ver.: V1.0
 Note:
*******************************************************************************/
void GUI_Label_ClearText(TGUI_Label *CurLabel)
{ 
    CurLabel->Text[0]='\0';												//���ı�������
	if(CurFocusWindow==CurLabel->Control.ParentWindow){
		TGUI_Label_ReDraw(CurLabel,CurLabel->Control.State);				//�ػ��ı���
	}	                              
}


/*******************************************************************************
 Func: ���ı���ǩд������
 Time: 2013-3-25
 Ver.: V2.0
 Note: return 0/����ʧ��  1/���óɹ�
*******************************************************************************/
uint8 TGUI_Label_SetNumber(TGUI_Label *CurLabel,f32 Number,uint8 DP)
{
	uint8 Text[10];
	GetStringFromNumber(Text,Number,'D',DP);
	return TGUI_Label_SetText(CurLabel,Text);
}


/*******************************************************************************
 Func: ���ı���ǩд������
 Time: 2013-3-25
 Ver.: V2.0
 Note: return 0/����ʧ��  1/���óɹ�
*******************************************************************************/
f32	TGUI_Label_GetNumber(TGUI_Label	*CurLabel)
{
	return GetStringToNumber(CurLabel->Text);
}


/*******************************************************************************
 Func: �����ı���ǩ��ɫ��
 Time: 2013-12-26
 Ver.: V1.0
 Note:
*******************************************************************************/
void TGUI_Label_SetColor(TGUI_Label *CurLabel,uint16 Fcolor,uint16 Bcolor,uint16 Dcolor)
{
	CurLabel->ForeColor=Fcolor;
	CurLabel->BackColor=Bcolor;
	CurLabel->BorderColor=Dcolor;
	if(CurFocusWindow==CurLabel->Control.ParentWindow){
		TGUI_Label_ReDraw(CurLabel,CurLabel->Control.State);
	}
}


/*******************************************************************************
 Func: �����ı���ǩ������ʽ
 Time: 2013-12-26
 Ver.: V1.0
 Note:
*******************************************************************************/
void TGUI_Label_SetAlignment(TGUI_Label *CurLabel,uint8 Alignment)
{
	if(CurLabel->Alignment!=Alignment){
		CurLabel->Alignment=Alignment;
		if(CurFocusWindow==CurLabel->Control.ParentWindow){
			TGUI_Label_ReDraw(CurLabel,CurLabel->Control.State);
		}
	}
}
/******************************************************************************
 Func: �����ı���ǩ
 Time: 2013-6-9
 Ver.: V2.0
 Note: 
*******************************************************************************/
void TGUI_Label_Hidden(TGUI_Label *CurLabel)
{
	if(CurLabel->Control.ParentWindow==CurFocusWindow)
	{
		TGUI_Label_ReDraw(CurLabel,TGUI_State_Hidden);			//�ػ�ؼ�
	}else{
		CurLabel->Control.State=TGUI_State_Hidden;
	}
}


/******************************************************************************
 Func: ��ʾ�ı���ǩ
 Time: 2013-6-9
 Ver.: V2.0
 Note: 
*******************************************************************************/
void TGUI_Label_Show(TGUI_Label *CurLabel)
{
	TGUI_ControlBase *P=&(CurLabel->Control);
	if(P->State==TGUI_State_Hidden){
		if(P->ParentWindow->CurControl==CurLabel)P->State=TGUI_State_OnFocus;
		else P->State=TGUI_State_ReLoad;
		if(P->ParentWindow==CurFocusWindow)TGUI_Label_ReDraw(CurLabel,P->State);
	}
}


/*------------------------------------------------------------------------------
 Func: ����Label�¼�
 Time: 2014-3-25
 Ver.: V1.0
 Note: 
------------------------------------------------------------------------------*/
uint8 TGUI_Label_Event(void *Object,uint8 EventType,uint8 EventValue)
{
	return TGUI_Result_Ignore;	
}


/*------------------------------------------------------------------------------
 Func: ����TextBox�ؼ�
 Time: 2014-3-25
 Ver.: V1.0
 Note:
------------------------------------------------------------------------------*/
void TGUI_Label_Create(uint16 ID,uint16 SX,uint16 SY,uint16 W,uint16 H,void *InitText,uint8 Style,TGUI_Label *NewLabel)
{
	TGUI_ControlBase *P=&(NewLabel->Control);
	P->TP=TGUI_Type_Label;
	P->ID=ID;
    P->SX=SX;
    P->SY=SY;
    P->EX=SX+W;
    P->EY=SY+H;
	P->State=TGUI_State_UnLoad;
	P->Style=Style;
	P->Action=0;
	P->PrevControl=0;
	P->NextControl=0;	
	P->ParentWindow=0;    
	P->ReDraw=TGUI_Label_ReDraw;							//���嵱ǰ�ؼ����ػ淽��
	P->Event=TGUI_Label_Event;
	StringCoppy(InitText,NewLabel->Text);
	NewLabel->Alignment=TGUI_Label_Align;
	NewLabel->ForeColor=TGUI_Label_Fcolor;
	NewLabel->BackColor=TGUI_Label_Bcolor;
	NewLabel->BorderColor=TGUI_Label_BDcolor;
	NewLabel->Font=TGUI_DefaultFont;
}




