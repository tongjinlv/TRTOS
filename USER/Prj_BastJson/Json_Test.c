/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
void Task3(void *Tags)
{
	uint8 *P;
	uint8 i;
	const uint8 buf[1000];
	uint8 Buf[100];
	DeBug("start",4);
	GetStringByFmt(&Buf[0],"{SensorData:[{'Value1':%.2f},{'Value2':%d},{'Value2':%s}]}",12.0,6,"trtos");
	while(1)
	{
		Tos_TaskDelay(1000);
		Tos_TaskDelay(1000);
		DeBug("%s",Buf,4);
	}
}
uint8 Json_Get(uint8 *Str,uint8 *Buf,uint8 *Get)
{
	uint8 da=0,db=0;
	BOOL Ok=False;
	uint8 *P;
	P=Strstr(Str,Get);
	P+=GetTextLength(Get);
	while(*P)
	{
		if(*P=='['){da++;Ok=True;}
		if(!da)if(*P=='{'){db++;Ok=True;}
		if(*P==']')da--;
		if(!da)if(*P=='}')db--;
		if((da==0)&(db==0)&Ok){(*Buf++)=*P;return GetTextLength(Buf); }
		if((da|db))(*Buf++)=*P;
		P++;
	}
}
void Json_Create(void *Tags)
{
	uint8 *P="{SensorData:[{'Value1':12.00},{'Value2':6},{'Value2':trtos}]}";
	uint8 Buf[100];
	Tos_TaskDelay(2000);
	DeBug("start",4);
	BufferFill(Buf,0x00,sizeof(Buf));
	Json_Get(P,Buf,"SensorData");
	while(1)
	{
		Tos_TaskDelay(1000);
		Tos_TaskDelay(1000);
		DeBug("%s",Buf,4);
		
	}
}
