/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <..\USER\Prj_7LCDSJJ\Kaoqinji_Driver.h>
#include <..\USER\Prj_7LCDSJJ\DaCai_Driver.h>
#include <..\USER\Prj_7LCDSJJ\GPRS_Driver.h>
uint16 PageCount,PageIndex;
uint8 RxEn=0;
uint8 SendEn=0xaa;
uint8 RecPic_En=True;
UserInforStruct UserInfor;
uint16 KQ_Xor(uint8 *bufPtr, uint16 Lenth) 
{ 
	uint16 Value=0; 
	while(Lenth!=0) 
	{ 
	Value^=*bufPtr; 
	bufPtr++; 
	Lenth--;
	}
	return Value;
}

uint8 KQ_Pack(uint8 *Buf,uint8 subCmd,uint8 *src,uint8 len) 
{ 
	uint8 i=0;
	uint16 crc; 
	uint16 dstlen; 
	i+=BufferCoppy("##",&Buf[i],2);
	dstlen =len+11;//�����ܳ��� 
	i+=SetWordToBytes(&Buf[i],dstlen,0);
	Buf[i++]=0x0b;	//��������
	Buf[i++]= 0x40;// �������� 
	Buf[i++]= subCmd;// ��������
	i+=BufferCoppy(src,&Buf[i],len);
	crc=KQ_Xor(Buf, dstlen -4);//�������У�� 
	i+=SetWordToBytes(&Buf[i],crc,0);
	Buf[dstlen -2]=0x0d;//������ 
	Buf[dstlen -1]=0x0a;//������ 
	return dstlen;//���ش����ʵ�ʳ��� 
}
uint8 KQ_Export(uint8 *Buf,uint16 Length)
{
	uint16 L,Xo;
	L=GetWordFromBytes(&Buf[2],0);
	if(L!=Length)return False;
	Xo=KQ_Xor(&Buf[0], Length -4);
	if(Xo!=GetWordFromBytes(&Buf[Length -4],0))return False;
	return True;
}
uint8 KQ_CreateSetDateTimePack(uint8 *Buf,Date_Time *DT)
{
	uint8 i=0;
	Buf[i++]=((2000+DT->Year) / 100) & 0xFF;
	Buf[i++]=((2000+DT->Year) %100) & 0xFF;
	Buf[i++]=DT->Mon;
	Buf[i++]=DT->Day;
	Buf[i++]=DT->Hour;
	Buf[i++]=DT->Min;
	Buf[i++]=DT->Sec;
	return i;
}

uint8 KQ_GetPicturePack(uint8 *Buf,uint8 Index)
{
	uint8 i=0,n;
	uint8 Data[30];
	for(n=0;n<8;n++)Data[i++]=UserInfor.UserID[n];
	i+=BufferCoppy(&UserInfor.DateTimeTemp[0],&Data[i],8);
	Data[i++]=Index;
  i=KQ_Pack(&Buf[0],0x18,&Data[0],i); 
	return i;
}
void KQ_GetPicturc(uint8 Index)
{
	uint8 Buf[100],Length;
	Length=KQ_GetPicturePack(&Buf[0],Index);
	USART2_WriteDatas(&Buf[0],Length);
}
void _TaskGetSendPic()
{
	uint16 Count,Index=0,BagSize,	CountTimeOut=0;
	Count=UserInfor.PictureSize/128;
	if(UserInfor.PictureSize%128)Count++;
	DaCai_Printf("����ͼ��!");
	for(Index=0;Index<Count;)
	{
		KQ_GetPicturc(Index);
		Tos_TaskDelay(500);
		if(RxEn==1)if(PageIndex==Index){Index++;CountTimeOut=0;CountTimeOut=0;RxEn=0;Count=PageCount;}
		if(RxEn==0)CountTimeOut++;
		if(CountTimeOut>10){DaCai_Printf("��ȡͼ��ʧ��");Tos_TaskDelay(5000);return;}
	}
	RecPic_En=False;
	Tos_TaskDelay(1000);
	BagSize=UserInfor.PictureSize/128;
	Count=BagSize;
	if(UserInfor.PictureSize%128)BagSize++;
	for(Index=0;Index<Count;)
	{
		if(GPRS_CreatePicture(&USART2_TX_Buffer[0],&UserInfor.PicBuf[Index*128],128,BagSize,Index)){Index++;CountTimeOut=0;}
		else CountTimeOut++;
		DaCai_Printf("����ͼ��%d/%d",Index,BagSize);
		Tos_TaskDelay(100);
		if(CountTimeOut>10){DaCai_Printf("����ͼ��ʧ��");Tos_TaskDelay(5000);RecPic_En=True;return;}
	}if(UserInfor.PictureSize%128)
	for(Index=0;Index<5;Index++)
	{
		if(GPRS_CreatePicture(&USART2_TX_Buffer[0],&UserInfor.PicBuf[Count*128],(UserInfor.PictureSize%128),BagSize,Count))break;
		DaCai_Printf("����ͼ��%d/%d",Count,BagSize);
		Tos_TaskDelay(100);
	}
	SendEn=0xbb;
	RecPic_En=True;
}
void TaskGetSendPic()
{
	uint16 Count,Index=0,BagSize,	CountTimeOut=0;
	Count=UserInfor.PictureSize/128;
	if(UserInfor.PictureSize%128)Count++;
	DaCai_Printf("����ͼ��!");
	for(Index=0;Index<Count;)
	{
		KQ_GetPicturc(Index);
		Tos_TaskDelay(500);
		if(RxEn==1)if(PageIndex==Index){Index++;CountTimeOut=0;CountTimeOut=0;RxEn=0;Count=PageCount;}
		if(RxEn==0)CountTimeOut++;
		if(CountTimeOut>10){DaCai_Printf("��ȡͼ��ʧ��");Tos_TaskDelay(5000);return;}
	}
	RecPic_En=False;
	Tos_TaskDelay(1000);
	BagSize=UserInfor.PictureSize/128;
	if(UserInfor.PictureSize%128)BagSize++;
	Index=0;
	while(UserInfor.PictureSize>0)
	{
		if(UserInfor.PictureSize>=128)Count=128;else Count=UserInfor.PictureSize;
		if(GPRS_CreatePicture(&USART2_TX_Buffer[0],&UserInfor.PicBuf[Index*128],Count,BagSize,Index)){Index++;UserInfor.PictureSize-=Count;CountTimeOut=0;}
		else CountTimeOut++;
		DaCai_Printf("����ͼ��%d/%d",Index,BagSize);
		Tos_TaskDelay(100);
		if(CountTimeOut>10){DaCai_Printf("����ͼ��ʧ��");Tos_TaskDelay(5000);RecPic_En=True;return;}
	}
	SendEn=0xbb;
	RecPic_En=True;
}
void KQ_CMD0x26(uint8 *Buf)
{
	uint16 i=0;
	uint32 PicSize;
	if(!Buf[i++])return;//���״̬/0x01�ɹ�0x00ʧ��
	BufferCoppy(&Buf[i],&UserInfor.UserName[0],10);i+=32;//�û���
	BufferCoppy(&Buf[i],&UserInfor.UserID[0],8);i+=8;
	UserInfor.FaceFesh=Buf[i++];//ʶ�����
	BufferCoppy(&Buf[i],&UserInfor.DriverID[0],18);i+=18;//���֤
	if(Tools_GetCRC16(&UserInfor.DriverID[0],18)!=UserInfor.IDCrc)SendEn=0xaa;//��ݷ����ı�ʱ��֤
	UserInfor.IDCrc=Tools_GetCRC16(&UserInfor.DriverID[0],18);
	if(SendEn==0xaa)BufferCoppy(&Buf[i],&UserInfor.DateTimeTemp[0],8);i+=8;//ʱ��
	PicSize=D32FromArray(&Buf[i],0);i+=4;//��Ƭ��С
	if(SendEn==0xaa)UserInfor.PictureSize=PicSize;
	UserInfor.DeverType=Buf[i++];//ְλ
	DaCai_SetTextBox(0x17,6,&UserInfor.UserName[0],sizeof(UserInfor.UserName));
	DaCai_SetTextBox(0x17,12,&UserInfor.UserID[0],sizeof(UserInfor.UserID));
	DaCai_SetTextBox(0x17,8,&UserInfor.DriverID[0],sizeof(UserInfor.DriverID));
	DaCai_TextBox(0x17,17,"%dByte",PicSize);
	if(UserInfor.DeverType==0x01)
	{
		DaCai_TextBox(0x17,14,"��ȫԱ");
		DaCai_SetPage(0x16);
		Run_Value.WorkMode=0x01;
	}
	else if(UserInfor.DeverType==0x02)
	{
		DaCai_TextBox(0x17,14,"˾��");
		Run_Value.RunMode=0x01;
	} else DaCai_TextBox(0x17,14,"��ݴ���[%d]",UserInfor.DeverType);
	GPRS_SendOne(3,1,1,&GPRS_DriverName);
	if(SendEn==0xaa)
	{
		GPRS_SendOne(4,1,1,&TaskGetSendPic);
	}
}
void KQ_CMD0x18(uint8 *Buf)
{
	uint16 i=0;
	uint16 Offset;
	if(!RecPic_En)return;
	PageCount=Buf[i++];
	PageIndex=Buf[i++];
	if(PageCount==0)return;
	if(!CompareWithBuffer(&Buf[i],&UserInfor.UserID[0],8))return;
	if(!CompareWithBuffer(&Buf[i+8],&UserInfor.DateTimeTemp[0],8))return;
	i+=8;//����
	i+=8;//ʱ��
	Offset=494*PageIndex;
	DaCai_Printf("��ȡͼ��%d/%d",PageIndex+1,PageCount);
	if(Offset>=10000)return;
	BufferCoppy(&Buf[i],&UserInfor.PicBuf[Offset],494);
	RxEn=1;
}
void KQ_SetData()
{
	uint8 Length,i=0;
	uint8 Buf[100];
	uint8 Data[10];
	Tos_TaskDelay(1000);
	Length=KQ_CreateSetDateTimePack(&Data[i],&Run_Value.DT);
	Length=KQ_Pack(&Buf[0],0x01,&Data[0],Length);
	USART2_WriteDatas(&Buf[0],Length);
}
void KQ_GetUserInfor()
{
	
}
void KQ_Command(void *Tags)
{
	uint16 Length;
	Tos_TaskDelay(1000);
  KQ_SetData();
	while(1)
	{
		Tos_TaskDelay(1);
		DeBug_Get();
		ClearWithBuffer(&USART2_RX_Buffer[0],1000);
  	Length=USART2_ReadDatas(Null,1000,0);
		if(KQ_Export(&USART2_RX_Buffer[0],Length))
		switch(USART2_RX_Buffer[6])
		{
			case 0x26:KQ_CMD0x26(&USART2_RX_Buffer[7]);break;
			case 0x18:KQ_CMD0x18(&USART2_RX_Buffer[7]);break;
			default:break;
		}
	}
}
