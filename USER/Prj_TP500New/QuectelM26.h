/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
/***************************************************************************************************
	* Copyright (c) 2016, Biohermes
	* All rights reserved.
	* �ļ����ƣ� QuectelM26.h
	* ժ Ҫ��    GSMģ��
	* ��ǰ�汾�� V1.0, �׽�, 2016-01-05
	* ���ļ�¼�� ��
***************************************************************************************************/

#ifndef _QUECTELM26_H_
#define _QUECTELM26_H_

#include <Include.h>

#define     RX_BUFF_LEN             20                          //���ջ������鳤��
#define         M26_OK                  0                               //OK
#define         STRING_ERR              1                               //��Ԥ�ڷ����ַ���
#define         CONNECT_ERR             2                               //��ģ�����Ӵ���
#define         QUERY_BAUD_ERR          3                               //�����ʴ���
#define         CLOSE_SOCKET_ERR        4
#define         CLOSE_CONTEXT_ERR       5
#define         SQ_ERR                  6                               //�źŲ�ѯ����
#define         REG_ERR                 7                               //����ע��ʧ��
#define         GREG_ERR                8                               //GPRS����ʧ��
#define         SET_CONTEXT_ERR         9
#define         ACT_CONTEXT_ERR         10
#define         QUERY_ACT_ERR           11
#define         SET_SOCKET_ERR          12
#define         ENTER_DATA_MODE_ERR     13
#define         QUERY_SOCKET_ERR        14
#define         RESET_ERR               15
#define         DEFAULT_ERR             16
#define         QUERY_PIN_ERR           17                              //��SIM������SIM����PIN��
#define         BACK_TO_TRAN_ACCESS_MODE_ERR    18
#define         OVER_TIME               19

#define         M26_POWER_ON            GPRS_ON
#define         M26_POWER_OFF           GPRS_OFF

#define         M26_RESET_ON            PWKEY_OFF
#define         M26_RESET_OFF           PWKEY_ON


extern u8 QuectelM26_PowerUp(void);
extern u8 QuectelM26_PowerDown(void);
extern u8 QuectelM26_Init(void);                                //gsmģ���ʼ��
extern u8 QuectelM26_ConnectNet(void);                          //gsmģ����������
extern u8 QuectelM26_CloseNet(void);                            //gsm�ر���������
extern u8 QuectelM26_CheckNet(void);                            //��ѯgsm�����Ƿ��Ѿ���ͨ
extern u8 QuectelM26_ResetModule(void);                         //ģ�鸴λ
extern void QuectelM26_Demo(void);                              //M26����Demo
uint8 QuectelM26_GetCSQ(void);
extern u16 g_u16OverTimeCnt;                                      //�뵹��ʱ��������Ҫ��ÿ���Լ�1
extern u8 g_u8RxIndexW;                                         //���ڽ��ռ�����д�������� ����ΪRxDataBuff���鳤�� RX_BUFF_LEN
extern u8 RxDataBuff[RX_BUFF_LEN];                              //���ڽ���BUFF


#endif
