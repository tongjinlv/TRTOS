/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Gui_Include.h>
#include <Driver_Include.h>
#include <TGUI_Base.h>
#include <TGui_2D_Driver.h>


/*--------------------------------------------------------------------------------------------------------------------------
 Func: TGUI_2D��ͼ����,���ƶ����3D͹��Ч��
 Time: 2010-1-8
 Ver.: V1.0
 Note: (SX,SY)(EX,EY)/�������λ��  LightColor/���߿�ɫ��   DarkColor/���߿�ɫ��    FaceColor/�������ɫ��
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_ObjectPopup(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 FaceColor)
{
  TGUI_Fill_Rectangle(SX,SY,EX,EY,FaceColor);	//���汳��ɫ
	TGui_Draw_Line(SX,EY-1,EX,EY-1,0x8410);		//�±����ڲవ��
	TGui_Draw_Line(EX-1,SY,EX-1,EY,0x8410);		//�ұ����ڲవ��	
	TGui_Draw_Line(SX,SY,EX,SY,0xE73C);			//�ϱ�������
	TGui_Draw_Line(SX,SY,SX,EY,0xE73C);			//���������	
	TGui_Draw_Line(SX,EY,EX,EY,0x4208);			//�±��ذ���
	TGui_Draw_Line(EX,SY,EX,EY,0x4208);			//�ұ��ذ���
}


/*--------------------------------------------------------------------------------------------------------------------------
 Func: TGUI_2D��ͼ����,���ƶ����3D����Ч��
 Time: 2010-1-8
 Ver.: V1.0
 Note: (SX,SY)(EX,EY)/�������λ��  LightColor/���߿�ɫ��   DarkColor/���߿�ɫ��    FaceColor/�������ɫ��
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_ObjectDown(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 FaceColor)
{   
	TGUI_Fill_Rectangle(SX,SY,EX,EY,FaceColor);
	TGui_Draw_Line(SX,SY+1,EX,SY+1,0x8410);		//�±����ڲవ��
	TGui_Draw_Line(SX+1,SY,SX+1,EY,0x8410);		//�ұ����ڲవ��	
	TGui_Draw_Line(SX,SY,EX,SY,0x4208);			//�ϱ�������
	TGui_Draw_Line(SX,SY,SX,EY,0x4208);			//���������	
	TGui_Draw_Line(SX,EY,EX,EY,0xE73C);			//�±��ذ���
	TGui_Draw_Line(EX,SY,EX,EY,0xE73C);			//�ұ��ذ���
}

/*--------------------------------------------------------------------------------------------------------------------------
 Func: TGUI_2D��ͼ����,���ƶ����3D����Ч��
 Time: 2010-1-8
 Ver.: V1.0
 Note: (SX,SY)(EX,EY)/�������λ��  LightColor/���߿�ɫ��   DarkColor/���߿�ɫ��    FaceColor/�������ɫ��
---------------------------------------------------------------------------------------------------------------------------*/
void TGUI_Draw_ObjectIn(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 FaceColor)
{   
	TGUI_Fill_Rectangle(SX,SY,EX,EY,FaceColor);
	TGui_Draw_Line(SX,SY+1,EX,SY+1,0x8410);		//�±����ڲవ��
	TGui_Draw_Line(SX+1,SY,SX+1,EY,0x8410);		//�ұ����ڲవ��	
	TGui_Draw_Line(SX,SY,EX,SY,0x4208);			//�ϱ�������
	TGui_Draw_Line(SX,SY,SX,EY,0x4208);			//���������	
	TGui_Draw_Line(SX,EY,EX,EY,0xE73C);			//�±��ذ���
	TGui_Draw_Line(EX,SY,EX,EY,0xE73C);			//�ұ��ذ���
}
 




