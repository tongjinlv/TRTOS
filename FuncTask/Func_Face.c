/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <Driver_Include.h>
#include <Tools_Include.h>
#include <Func_Face.h>
uint8 TaskArray_Tos_TaskID=Tos_TaskNull;
/******************************************************************************
Func:加载&更新屏幕通过ModBus协议
Time: 2014-7-20
Ver.: V2.0
By:童金吕
http://www.trtos.com/
Note:
******************************************************************************/
#ifdef LCD_YSIZE
void Task_GetScreen(void *Tags)
{
	uint16 x;
	uint16 y;
	uint16 Temp;
	uint16 ReadLine;
	uint8 Buf[600];
	ModBus_Message ModBusMsg;
	ModBus_Create(&ModBusMsg,0x01,0x94,WorkMode_Slave,MBCM_Xor);
	while(1)
	{
	  x=USART_ReadDatas(USART1,Null,600,0);
	 if(x)
		{
			DeBug_Get();
 			x=ModBus_Expend(USART_RX_Buffer[0],x,&ModBusMsg);
			if(ModBusMsg.MsgFlag==0x02)
			{
			ReadLine=GetWordFromBytes(&USART_RX_Buffer[0][x],1);
			for(y=0;y<LCD_YSIZE;y++){
				x=LCD_Get_Pixel(ReadLine,y);
				Buf[y*2]=x>>8;
				Buf[y*2+1]=x&0xff;
			}
			x= ModBus_CreateMsg(USART_TX_Buffer[0],&ModBusMsg,0x01,0x01,0x01,&Buf[0],LCD_YSIZE*2);
			USART_WriteDatas(USART1,USART_TX_Buffer[0],x);
		  }else if(ModBusMsg.MsgFlag==0x04)
			{
				ReadLine=GetWordFromBytes(&USART_RX_Buffer[0][x],1);
				for(y=0;y<LCD_YSIZE;y++)
				{
				Temp=USART_RX_Buffer[0][y*2+x+2];
				Temp<<=8;
			  Temp|=USART_RX_Buffer[0][y*2+1+x+2];
				LCD_Set_Pixel(ReadLine,y,Temp);
			  }
			}
		}
		Tos_TaskDelay(10);
	}
}
#endif
/****************************************************************************
Date:2014-5-12
Func:串口调试用
By:童金吕
http://www.trtos.com/
Note:
****************************************************************************/
void Usart_Terminal(void *Tags)
{
	uint8 x;
	DeBug_OutSet(DeBug_USART1|DeBug_LCD);//调试信息通过串口打印
	DeBug_Get();
	while(1)
	{
		
	  x=USART_ReadDatas(USART1,Null,600,0);
	 if(x)
		{
			DeBug("%s",USART_RX_Buffer[0],Infor_Infor);
		}
		Tos_TaskDelay(10);
	}
}
/****************************************************************************
Date:2014-5-12
Func:串口调试用
By:童金吕
http://www.trtos.com/
Note:
****************************************************************************/
void Usart_Usart(void *Tags)
{
	uint8 x;
	DeBug_OutSet(DeBug_USART1|DeBug_LCD);//调试信息通过串口打印
	DeBug_Get();
	while(1)
	{
	  x=USART_ReadDatas(USART1,Null,600,0);
	 if(x)
		{
			DeBug("%s",USART_RX_Buffer[0],Infor_Infor);
		}
		Tos_TaskDelay(10);
	}
}
/****************************************************************************
Date:2014-7-25
Func:加入任务到队列
By:童金吕
http://www.trtos.com/
Note:任务队列
****************************************************************************/
void Task_Join(void *CurTask,FuncType Type,uintbus Note)
{
	TaskArrayStruct TS;
	TS.Task=CurTask;
	TS.Type=Type;
	TS.Note=Note;
	Tos_TaskPutQmsg(TaskArray_Tos_TaskID,0,sizeof(TaskArrayStruct),&TS);
}
/****************************************************************************
Date:2014-7-25
Func:任务处理任务
By:童金吕
http://www.trtos.com/
Note:任务队列
****************************************************************************/
void Task_Arrary(void *Tags)
{
	uint8 i,c;
	typedef void(*VoidFuncVoid)(void);
	typedef void(*VoidFuncUint8)(uint8);
	typedef void(*VoidFuncInt)(int);
	typedef void(*VoidFuncVo)(void);
	typedef void(*VoidFuncUint32)(uint32);
	typedef void(*VoidFuncUint16)(uint16);
	Tos_ArrayMessage *CurMsg,*Msg;
	TaskArrayStruct *TaskMsg,*TaskMsgBuf;	
	if((uint32)Tags>0)c=(uint32)Tags;else c=10;
	Msg=Mema_Malloc(sizeof(Tos_ArrayMessage)*c);
	TaskMsgBuf=Mema_Malloc(sizeof(TaskArrayStruct)*c);
	for(i=0;i<c;i++)Msg[i].Qmsg_Addr=&TaskMsgBuf[i];
	Tos_TaskCreateQmsg(&Msg[0],c);
	TaskArray_Tos_TaskID=Tos_TaskCurrent;
	while(1)
	{
		Tos_TaskDelay(10);
		 CurMsg=Tos_TaskGetQMsg();
		if(CurMsg)
		{
			TaskMsg=(TaskArrayStruct *)CurMsg->Qmsg_Addr;
			switch((uint8)TaskMsg->Type)
			{
				case FT_VoidFuncVoid:((VoidFuncVoid)(TaskMsg->Task))();break;
				case FT_VoidFuncUint8:((VoidFuncUint8)(TaskMsg->Task))(TaskMsg->Note);break;
				case FT_VoidFuncUint32:((VoidFuncUint32)(TaskMsg->Task))(TaskMsg->Note);break;
				case FT_VoidFuncInt:((VoidFuncInt)(TaskMsg->Task))(TaskMsg->Note);break;
				case FT_VoidFuncUint:((VoidFuncUint16)(TaskMsg->Task))(TaskMsg->Note);break;
			}
		}
	}
}


/*D

这是对应的源SEGCreateCode[0] 需要填入对应的目标SEGCreateCode[1]
源
						----BIT(2)----
					|              |
					|BIT(0)        |BIT(1)
					 ----BIT(7)----
					|              |
					|BIT(5)        |BIT(6)
  	DP	   ----BIT(4)----	
		BIT(3)

目标
					 ----BIT(0)----
					|              |
					|BIT(4)        |BIT(1)
					 ----BIT(5)----
					|              |
					|BIT(6)        |BIT(2)
  	DP	   ----BIT(3)----	
		BIT(7)
*/
//源目标对应
const uint8 SEGCreateCode[][2]={
	{0,6},
	{1,5},
	{2,4},
	{3,3},
	{4,2},
	{5,1},
	{6,0},
	{7,7},
	};
const uint8 SEGBaseCode[]={
	_XXX_XXX,//0
	_X____X_,//1
	X_XX_XX_,//2
	XX_X_XX_,//3
	XX____XX,//4
	XX_X_X_X,//5
	XXXX_X_X,//6
	_X___XX_,//7
	XXXX_XXX,//8
	XX_X_XXX,//9
	________,//.
	X_______,//-   
	________,// 
	_XXX__XX,//U
	X_X__XXX,//P
	X_X__X_X,//F
	X_XX___X,//T
	XXXX___X,//B
	XXXX____,//O
	XXX___XX,//H
	__XX_X_X,//C
	__XX___X,//L
	_XX__XXX,//N
};
uint8 *SEGCharList="0123456789.- UPFTBOHCLN";

void SEEGet(uint8 *Buf,const uint8 Code[][2])
{
	uint8 buf[9];
	uint8 i=sizeof(SEGBaseCode);
	uint8 n,m;
	for(n=0;n<i;n++)
	{
		Buf[n]=0;
		for(m=0;m<8;m++)if(SEGBaseCode[n]&(1<<Code[m][0]))Buf[n]|=(1<<Code[m][1]);
	}
	for(n=0;n<i;n++)
	{
		for(m=0;m<8;m++)if(Buf[n]&(1<<(7-m)))buf[m]='X';else buf[m]='_';
		buf[m]=0;
		DeBug("%s,//%c",buf,SEGCharList[n],2);
	}
}
//Buf  是用来放置缓存SEGCreateCode
void SEGTrun(uint8 *Buf)
{
	SEEGet(Buf,SEGCreateCode);
}
