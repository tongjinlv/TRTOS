/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _EXCEL_H_
#define _EXCEL_H_
#include <include.h>
typedef struct Excel{
	_TGui_2D *TB;
	uint16  	Row_High;//�и�
	uint16  	Row_Count;//����
	void    	*Columns_Array;//�п������
	uint16  	Columns_Count;//����
	void    	*Title;//����
	uint8     Gird_Align;//���뷽ʽ
}_TGUI_Excel;

extern _TGUI_Excel *P_TGui_CurXls;
void Tos_SetExcleHandle(_TGUI_Excel *Xls);
void Tos_DrawTable(void);
void Tos_SetTableString(uint16 Columns,uint16 Rows,void *Tags);
void Tos_SetTableData(uint16 Columns,uint16 Rows,f32 Number,uint8 NumType,uint8 DotLenth);
void Tos_SetTableString(uint16 Columns,uint16 Rows,void *Tags);

#endif
