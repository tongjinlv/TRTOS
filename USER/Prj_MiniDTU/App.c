/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
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
	DeBug_OutSet(0);//调试信息通过串口打印
	DeBug_SetType(UIShowValue.SaveValue.DeBugCFG);//只打印Infor类型的消息
	DeBug_SetCallBack(RS485DeBug);
	Printf_SysInfor();

}
