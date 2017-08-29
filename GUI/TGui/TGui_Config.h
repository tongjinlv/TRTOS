/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _TGUI_CONFIG_H_
#define _TGUI_CONFIG_H_

/*-------------------------------------------------------------------------
 TGUI �ؼ���ǰ״̬
-------------------------------------------------------------------------*/
#define TGUI_State_UnLoad		0x01					//�ؼ�δ����״̬
#define TGUI_State_ReLoad     	0x02					//�ؼ��ؼ��ص�����
#define TGUI_State_UnFocus		0x03					//�ؼ�ʧȥ����״̬
#define TGUI_State_OnFocus		0x04					//�ؼ���ý���״̬
#define TGUI_State_Deleted		0x05					//�ؼ��ӽ��汻ɾ��״̬
#define TGUI_State_EntryEdit	0x06					//�ؼ�����༭ģʽ  
#define TGUI_State_ExitEdit		0x07					//�ؼ��˳��༭ģʽ
#define TGUI_State_Hidden		0x08					//�ؼ���������״̬

/*-------------------------------------------------------------------------
 TGUI �ؼ�������ʽ
-------------------------------------------------------------------------*/			  
#define TGUI_Style_NoBcolor		0x01					//�ؼ��ޱ���ɫ��ʾ
#define TGUI_Style_NoFrame		0x02					//�ؼ��ޱ߿���ʾ
#define TGUI_Style_NoTitle		0x04					//�ؼ��ޱ�����ʾ
#define TGUI_Style_NoDirH		0x08					//�ؼ���ֱ����,��90��
#define TGUI_Style_NoDirInc		0x10					//�ؼ������� ˮƽ��->�� ��ֱ��->��
#define TGUI_Style_NoVbar		0x20					//�ؼ��޴�ֱ������
#define TGUI_Style_NoHvar		0x40					//�ؼ���ˮƽ������

#define TGUI_Style_Default		0x00					//�ؼ�Ĭ����ʽ

/*-------------------------------------------------------------------------							
 TGUI �ؼ���Ϊ��ʽ
-------------------------------------------------------------------------*/
#define TGUI_Action_EnOnFucus	0x01					//�ؼ�����Ӧ�����¼�
#define TGUI_Action_EnEdit		0x02					//�ؼ�����Ӧ�༭�¼�
#define TGUI_Action_TabDirV		0x04					//�ؼ�����Ӧ��ֱTAB(Up/Down)
#define TGUI_Action_TabDirH		0x08					//�ؼ�����ӦˮƽTAB(Left/Right)
#define TGUI_Action_Enable		0x10					//�ؼ��¼���Ӧ����

/*-------------------------------------------------------------------------
 TGUI ������
-------------------------------------------------------------------------*/
#define TGUI_Dir_Up	  		  0x01
#define TGUI_Dir_Down		  0x02
#define TGUI_Dir_Left		  0x03
#define TGUI_Dir_Right		  0x04

/*-------------------------------------------------------------------------
 TGUI ����ʽ����
-------------------------------------------------------------------------*/
#define TGUI_Line_Light       0xFF
#define TGUI_Line_Dark        0x49
#define TGUI_Line_Face        242
#define TGUI_Line_Back        0xFF
#define TGUI_DotLine_Face     0x00


/*-------------------------------------------------------------------------
 TGUI ����Ԫ������
-------------------------------------------------------------------------*/
#define TGUI_Type_Window	  0x01
#define TGUI_Type_Button	  0x02
#define TGUI_Type_Textbox	  0x03
#define TGUI_Type_TextArea	  0x04
#define TGUI_Type_ComBox	  0x05
#define TGUI_Type_Radio		  0x06
#define TGUI_Type_CheckBox	  0x07
#define TGUI_Type_LineChart	  0x08
#define TGUI_Type_Label		  0x09
#define TGUI_Type_ImageBox	  0x0A
#define TGUI_Type_ProcessBar  0x0B

/*-------------------------------------------------------------------------
 TGUI ������Ϣ����
-------------------------------------------------------------------------*/
#define TGUI_MsgType_KeyBoard 	  0x01				//������Ϣ
#define TGUI_MsgType_SoftEvent	  0x02				//����Ϣ
#define TGUI_MsgType_SysInt		  0x03				//ϵͳ�ж�
#define TGUI_MsgType_TouchScreen  0x04				//��ģ����Ϣ
#define TGUI_MsgType_SysTimer	  0x05				//ʱ����Ϣ


/*-------------------------------------------------------------------------
 TGUI �����¼�����
-------------------------------------------------------------------------*/
#define TGUI_Event_KeyClickDown	  0x01
#define TGUI_Event_KeyClickUp	  0x02
#define TGUI_Event_KeyHolding	  0x03
#define TGUI_Event_TouchDown   	  0x05
#define TGUI_Event_TouchUp		  0x06
#define TGUI_Event_TouchHolding	  0x07
#define TGUI_Event_ControlOnFocus 0x10
#define TGUI_Event_ControlUnFocus 0x11

/*-------------------------------------------------------------------------
 TGUI ����ؼ��¼�����״̬
-------------------------------------------------------------------------*/
#define TGUI_Result_BackSpace	  0x01				//�ؼ�Ҫ����һ������
#define TGUI_Result_NextSpace	  0x02				//�ؼ�Ҫ����һ������
#define TGUI_Result_Ok			  0x03				//�ؼ�������ȷ
#define TGUI_Result_Yes			  0x04				//�ؼ�����ȷ��
#define TGUI_Result_No			  0x05				//�ؼ����ط���
#define TGUI_Result_Cancel		  0x06				//�ؼ�����ȡ��
#define TGUI_Result_Null		  0x07				//�ؼ����ؿ�
#define TGUI_Result_Ignore		  0x08				//�ؼ�����ǰ�¼�����
#define TGUI_Result_Error		  0x09				//�ؼ����ش���
#define TGUI_Result_Success		  0x0A				//�ؼ����سɹ�

/*-------------------------------------------------------------------------
 TGUI ����༭����
-------------------------------------------------------------------------*/
#define TGUI_EditType_Num		  0x01				//������������
#define TGUI_EditType_Dot		  0x02				//���������
#define TGUI_EditType_Sig		  0x04				//�����������
#define TGUI_EditType_UpDown	  0x08				//�������¼��Ӽ�
#define TGUI_EditType_OkEdit	  0x10				//��ȷ���ٱ༭

#define TGUI_EditType_EnEdit	  0x80				//��ǰ�༭ʹ��״̬
#define TGUI_EditType_Default     0x17

/*-------------------------------------------------------------------------
 TGUI ���尴��ֵ
-------------------------------------------------------------------------*/
#define TGUI_Key_Num0	  0x01
#define TGUI_Key_Num1	  0x02
#define TGUI_Key_Num2	  0x03
#define TGUI_Key_Num3	  0x04
#define TGUI_Key_Num4	  0x05
#define TGUI_Key_Num5	  0x06
#define TGUI_Key_Num6	  0x07
#define TGUI_Key_Num7	  0x08
#define TGUI_Key_Num8	  0x09
#define TGUI_Key_Num9	  0x0A
#define TGUI_Key_Dot	  0x0B				//.����
#define TGUI_Key_Add	  0x0C				//+����
#define TGUI_Key_Sub	  0x0D				//-����
#define TGUI_Key_Mul	  0x0E				//*����
#define TGUI_Key_Div	  0x0F				///����
#define TGUI_Key_Up		  0x30
#define TGUI_Key_Down	  0x31
#define TGUI_Key_Left	  0x32
#define TGUI_Key_Right	  0x33
#define TGUI_Key_Ok		  0x34
#define TGUI_Key_Esc	  0x35
#define TGUI_Key_Cannel	  0x36
#define TGUI_Key_F1		  0x50	
#define TGUI_Key_F2		  0x51
#define TGUI_Key_F3		  0x52
#define TGUI_Key_F4		  0x53
#define TGUI_Key_F5		  0x54




/*-------------------------------------------------------------------------
 TGUIȫ������
--------------------------------------------------------------------------*/
#define TGUI_Image_Null		0xFFFFFFFF		//����ͼƬΪ��
#define TGUI_Object_Null	0x00			//��Ԫ��
#define TGUI_Cursor_Width	0x02			//��������
#define TGUI_Cursor_Height  0x10			//������߶�

#define TGUI_OnFocus_ForeColor	0x0000		//ѡ��״̬�µ�ǰ��ɫ
#define TGUI_OnFocus_BackColor	0xFFFF		//ѡ��״̬�µı���ɫ
#define TGUI_OnEdit_ForeColor	0xFFFF		//�༭״̬�µ�ǰ��ɫ
#define TGUI_OnEdit_BackColor	0x001F		//�༭״̬�µı���ɫ


/*-------------------------------------------------------------------------
 TGUI���ڿؼ�����
-------------------------------------------------------------------------*/

#define TGUI_Window_TitleHeight	    30				//���崰�ڱ������߶�����
#define TGUI_Window_TitleBackColor 	Color_Blue		//���崰�ڱ���������ɫ
#define TGUI_Window_TitleForeColor	Color_White		//���崰�ڱ�����ǰ��ɫ
#define TGUI_Window_TitleLenth		11				//���崰�ڱ��ⳤ��
#define TGUI_Window_BackColor		Color_White		//���崰��Ĭ�ϱ���ɫ
#define TGUI_Window_ForeColor		Color_Black		//���崰��Ĭ��ǰ��ɫ
#define TGUI_Window_Buffer_Lenth	20
#define TGUI_Window_CursorEnable	0x01			//���ڹ�꿪��
#define TGUI_Window_CursorState		0x02			//���ڹ��״̬


/*-------------------------------------------------------------------------
 TGUI��ť�ؼ�����
-------------------------------------------------------------------------*/
#define TGUI_Button_ForeColor    0x0000						//��ť����ǰ��ɫ
#define TGUI_Button_BackColor    0xCDff						//��ť����ɫ
#define TGUI_Button_TextColor	 0xFFFF						//��ť�����ı�
#define TGUI_Button_Lenth		 9							//��ť�ı�������

/*-------------------------------------------------------------------------
TGUI�ı���ؼ�����
-------------------------------------------------------------------------*/
#define Textbox_Enable     0x01
#define Textbox_Password   0x02
#define Textbox_Multiline  0x03

#define TGUI_Textbox_FaceColor   0x0000
#define TGUI_Textbox_BackColor   0xFFFF
#define TGUI_Textbox_BDcolor	 0x0000
#define TGUI_Textbox_Lenth  8
#define TGUI_Textbox_AlignMent	Align_CenterCenter

/*-------------------------------------------------------------------------
TGUI�ı���ؼ�����
-------------------------------------------------------------------------*/
#define TextArea_Enable     0x01
#define TextArea_Password   0x02
#define TextArea_Multiline  0x03 

#define TGUI_TextArea_Face   0xFF  
#define TGUI_TextArea_Back   0x49
#define TGUI_TextArea_Lenth  100
#define TGUI_TextArea_ScrollBarWidth 16


/*-------------------------------------------------------------------------
TGUI�����˵���ؼ�����
-------------------------------------------------------------------------*/
#define TGUI_ComBox_ForeColor   0xFFFF  
#define TGUI_ComBox_BackColor   0xCDB4
#define TGUI_ComBox_ForeColorH	0xFFFF		//����ѡ����ǰ��ɫ
#define TGUI_ComBox_BackColorH	0x4228		//����ѡ�����ɫ
#define TGUI_ComBox_Lenth  14 
#define TGUI_ComBox_ScrollBarWidth 20		//ComBox�ؼ����������

#define TGUI_ComBox_ListLines   15
#define TGUI_ComBox_ItemLenth   15
#define TGUI_ComBox_ItemsMax    16
#define TGUI_ComBox_LineFirst	10			//������������Ԫ�ؼ��
#define TGUI_ComBox_LineHeight  23			//����Ԫ����ʾ�о�

#define TGUI_ComBox_Flag_Expand 0x01		//ComBox�ؼ�����������չ��


/*-------------------------------------------------------------------------
TGUI�����˵���ؼ�����
-------------------------------------------------------------------------*/
#define TGUI_Object_FaceColor 242			//�ؼ�����ɫ��	
#define TGUI_Object_DarkColor 0x49  		//�ؼ���Ӱɫ��


/*-------------------------------------------------------------------------
TGUI ��ѡ��ť�ؼ�����
-------------------------------------------------------------------------*/
#define TGUI_Radio_Face   0xCDB4  
#define TGUI_Radio_Back   0xFFFF
#define TGUI_Radio_Lenth  14 

#define TGUI_Radio_ItemLenth   11
#define TGUI_Radio_ItemsMax    10

#define TGUI_Radio_ChooseMode  0x04			//��ѡ�ؼ�����ѡ��״̬

/*-------------------------------------------------------------------------
 TGUI ��ѡ��ť����
-------------------------------------------------------------------------*/
#define TGUI_CheckBox_Face   0xFF  
#define TGUI_CheckBox_Back   0x49
#define TGUI_CheckBox_Lenth  14 

#define TGUI_CheckBox_ItemLenth   11
#define TGUI_CheckBox_ItemsMax    10

#define TGUI_CheckBox_ChooseMode  0x04

/*-------------------------------------------------------------------------
 TGUI Label��ǩ�ؼ�����
-------------------------------------------------------------------------*/
#define TGUI_Label_Lenth	20
#define TGUI_Label_Align	Align_CenterCenter
#define TGUI_Label_Fcolor	Color_Black
#define TGUI_Label_Bcolor	Color_White
#define TGUI_Label_BDcolor	Color_Black					//��ǩ�߿�ɫ��

/*-------------------------------------------------------------------------
 TGUI ImageBox��ǩ�ؼ�����
-------------------------------------------------------------------------*/
#define TGUI_ImageBox_Bcolor Color_White
#define TGUI_ImageBox_BDcolor Color_Black

/*-------------------------------------------------------------------------
 TGUI ProcessBar�������ؼ�����
-------------------------------------------------------------------------*/
#define TGUI_ProcessBar_Fcolor  0xBB88
#define TGUI_ProcessBar_Bcolor  0x94B2
#define TGUI_ProcessBar_BDcolor Color_Black;

#endif
