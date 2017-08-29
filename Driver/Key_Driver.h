/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/
#ifndef _KEY_DRIVER_H_
#define _KEY_DRIVER_H_

enum KeyTypeEnum
{
	Key_UpIng=1,//����̧��
	Key_DownIng=2,//��������
	Key_UpTimeOut=3,//̧��һ��ʱ�䴥��
	Key_DownTimeOut=4,//����һ��ʱ�䴥��
	Key_DownBate=5,//���½���
	Key_OneClick=6,
};
enum KeyBoard_Command_FrameFlag
{
	KCFF_IsKeyMsg=1,
};
enum KeyBoardType
{
	KeyBoard_Hand=1,
	KeyBoard_Touch=2,
	KeyBoard_RockerBar=3,
	KeyBoard_Null=4,
};
enum KeyValueEnum
{
	Key_Printf=0x01,
	Key_UpDown=0x02,
	Key_WkUp=0x04,
	Key_Left=0x25,//��
  Key_Up=0x26,//��
  Key_Right=0x27,//��
  Key_Down=0x28,//��
	Key_Enter=0x0d,//ȷ��
	Key_Esc=35,//�˳�
	Key_Ctrl=35,
	Key_A='A',
	Key_B='B',
	Key_C='C',
	Key_D='D',
	Key_E='E',
	Key_1='1',
	Key_2='2',
	Key_3='3',
	Key_4='4',
	Key_5='5',
	Key_6='6',
	Key_7='7',
	Key_8='8',
	Key_9='9',
	Key_0='0',
	Key_X='X',
	Key_Y='Y'
	
};
typedef struct
{
	uint8 KeyType;				//�����¼�����
	uint8 KeyValue;				//���̼�ֵ
	int8 KeyTime;				//��ʱ�����
}MGUI_KeyMsg;

void Task_KeyBoard(void *Tags);
MGUI_KeyMsg * MUI_GetKey(uint16 D);
void Tos_TaskGetHandKey(void);
#endif
