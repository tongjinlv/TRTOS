/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _ENCRYPTION_H_
#define _ENCRYPTION_H_
#include <Include.h>


//********************************************************
//����unsigned long char �������͵�����
typedef union
{
   unsigned char  UcType[4];
   unsigned int   UiType[2];
   unsigned long  UlType;
}UILONG; 


//********************************************************
//�궨��
#define     M_DEFAULT_YW       6      //Ĭ����λΪ6λ
#define PASSWORD_GLOBALS


extern uint8  PasswordSum[8];            //������
extern uint8  PasswordTemp[8];           //�����ݴ�

//********************************************************
//
extern void EncryptP(uint8  *ptr);  //��64λ���ݼ���
extern void DecryptP(uint8  *ptr);  //��64λ���ݽ��� uint8  PasswordSum[8];            //������
extern uint8  PasswordTemp[8];           //�����ݴ�

//********************************************************
//
extern void EncryptP(uint8  *ptr);  //��64λ���ݼ���
extern void DecryptP(uint8  *ptr);  //��64λ���ݽ���

#endif

