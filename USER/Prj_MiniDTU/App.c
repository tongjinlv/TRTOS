/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <GPIO_Driver.h>

void RS485DeBug(void *fmt,uint8 Length)
{
	GPIO_SetIndex(0,1);
	USART_WriteDatas(USART1,fmt,Length);
	Tos_TaskDelay(2);
	GPIO_SetIndex(0,0);
}

void Task0_MiniDTUInit()
{
 if(!BOOL_LoadConfigs())UIShowValue.SaveValue.DeBugCFG=0xff;
	DeBug_OutSet(0);//������Ϣͨ�����ڴ�ӡ
	DeBug_SetType(UIShowValue.SaveValue.DeBugCFG);//ֻ��ӡInfor���͵���Ϣ
	DeBug_SetCallBack(RS485DeBug);
	Printf_SysInfor();

}
