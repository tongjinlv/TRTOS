/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/

#ifndef _TGUI_3D_DRIVER_H_
#define _TGUI_3D_DRIVER_H_

#include <include.h>

#define TGUI_3D_Params_OnFocus	0x0001
#define TGUI_3D_Params_UnFocus	0x0002
#define TGUI_3D_Params_OnEdit	0x0003

#define TGUI_3D_OnFocus_ColorU	0x2703	 					//3D���󽹵�ʱɫA
#define TGUI_3D_OnFocus_ColorD	0x0DE0			  			//3D���󽹵�ʱɫB
#define TGUI_3D_OnFocus_ColorB	Color_Red					//3D���󽹵�ʱ�߿�ɫ

#define TGUI_3D_UnFocus_ColorU	0x045E						//3D����ʧȥ����ʱɫA
#define TGUI_3D_UnFocus_ColorD	0x03DA						//3D����ʧȥ����ʱɫB
#define TGUI_3D_UnFocus_ColorB	Color_White					//3D���󽹵�ʱ�߿�ɫ

#define TGUI_3D_OnEdit_ColorU	0xFA69						//3D����༭ʱɫA
#define TGUI_3D_OnEdit_ColorD	0xE001						//3D����༭ʱɫB
#define TGUI_3D_OnEdit_ColorB	Color_Green					//3D����༭ʱ�߿�ɫ


#define TGUI_3D_Shadow_Class1	0x7411						//3D������Ӱɫ��1
#define TGUI_3D_Shadow_Class2	0xA598						//3D������Ӱɫ��2
#define TGUI_3D_Shadow_Class3	0xCEDC						//3D������Ӱɫ��3


#define TGUI_ArcCorner_Radius	4							//Բ�ǻ��Ȱ뾶


extern void TGUI_3D_Draw_ObjectShadow(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 Params);
extern void TGUI_3D_Draw_ObjectBorder(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 Params);
extern void TGUI_3D_Draw_ObjectBody(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 Params);
void TGUI_3D_Draw_ObjectBody(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 Params);


#endif



