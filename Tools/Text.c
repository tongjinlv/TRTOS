/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>
#include <text.h>
/******************************************************************************
Func:��ȡ�ַ�������
Time:2014-4-28
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note:�����ַ������Ȱ���������
******************************************************************************/
uint16 GetTextLength(void *Tags)
{
	uint8 *P;
	uint16 i=0;
	P=(uint8 *)Tags;
	while(*P++)i++;
	return i;
}
/******************************************************************************
Func:����IP������
Time:2014-4-28
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note:��IP������
******************************************************************************/
BOOL GPRS_CheckIpTrue(char *S)
{
	char *P=S;
	while(*P)
	{
		if(*P=='.')
		{
			if((*(P-1)>='0')&(*(P-1)<='9'))
			if((*(P+1)>='0')&(*(P+1)<='9'))
			return True;//��IP
		}
		P++;
	}
	return False;
}
/******************************************************************************
Func:ȥ�ո�
Time:2017-4-28
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note:.trim
******************************************************************************/
uint8 StringTrim(void *S)
{
	char *P=(char *)S;
	uint8 i=0;
	while(*P)
	{
		if(*P!=0x20)((char *)S)[i++]=*P;
		P++;
	}
	((char *)S)[i++]=0;
	return i;
}
/******************************************************************************
Func:Ѱ���ַ����е����ִ�
Time:2014-4-28
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note:BufΪԴ����Data�������Index ���ִ�����
******************************************************************************/
uint8 FindNumFromString(uint8 *Buf,uint8 *Data,uint8 index)
{
	uint8 Length,i,c=0,t,has=0,z=0;
	Length=GetTextLength(Buf);
	if(Length)
	{
		Data[0]=0;
		for(i=0;i<Length;i++)
		{
			t=Buf[i];
			if((t>='0')&(t<='9')){if(index==z)Data[c++]=t;has=1;}
			else if(has){if(index==z)Data[c++]=0;has=0;z++;}
		}	
	}
	return c;
}
/******************************************************************************
Func:Ѱ���ַ����еĸ��㴮
Time:2014-4-28
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note:BufΪԴ����Data�������Index ���ִ�����
******************************************************************************/
uint8 FindFloatFromString(uint8 *Buf,uint8 *Data,uint8 index)
{
	uint8 Length,i,c=0,t,has=0,z=0;
	Length=GetTextLength(Buf);
	if(Length)
	{
		Data[0]=0;
		for(i=0;i<Length;i++)
		{
			t=Buf[i];
			if(((t>='0')&(t<='9'))|(t=='.')|(t=='-')){if(index==z)Data[c++]=t;has=1;}
			else if(has){if(index==z)Data[c++]=0;has=0;z++;}
		}	
	}
	return c;
}
/******************************************************************************
Func:Ѱ���ַ����е����ʹ�
Time:2014-4-28
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note:BufΪԴ����Data�������Index ���ִ�����
******************************************************************************/
uint8 FindIntFromString(uint8 *Buf,uint8 *Data,uint8 index)
{
	uint8 Length,i,c=0,t,has=0,z=0;
	Length=GetTextLength(Buf);
	if(Length)
	{
		Data[0]=0;
		for(i=0;i<Length;i++)
		{
			t=Buf[i];
			if(((t>='0')&(t<='9'))|(t=='-')){if(index==z)Data[c++]=t;has=1;}
			else if(has){if(index==z)Data[c++]=0;has=0;z++;}
		}	
	}
	return c;
}
/******************************************************************************
Func:Ѱ���ַ����е����ִ�
Time:2014-4-28
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note:BufΪԴ����Data�������Index ���ִ�����
******************************************************************************/
uint8 FindHexFromString(uint8 *Buf,uint8 *Data,uint8 index)
{
	uint8 Length,i,c=0,t,has=0,z=0;
	Length=GetTextLength(Buf);
	if(Length)
	{
		Data[0]=0;
		for(i=0;i<Length;i++)
		{
			t=Buf[i];
			if(((t>='0')&(t<='9'))||((t<='F')&(t>='A'))){if(index==z)Data[c++]=t;has=1;}
			else if(has){if(index==z)Data[c++]=0;has=0;z++;}
		}	
	}
	return c;
}
/******************************************************************************
Func:Ѱ���ַ����е����ִ�
Time:2014-4-28
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note:BufΪԴ����Data�������Index ���ִ�����
******************************************************************************/
uint8 FindStrFromString(uint8 *Buf,uint8 *Data,uint8 index)
{
	uint8 Length,i,c=0,n=0;
	Length=GetTextLength(Buf);
	if(Length)
	{
		Data[0]=0;
		for(i=0;i<Length;i++)
		{
			if(Buf[i]=='\'')c++;
			if(c==(index*2+1))if(Buf[i]!='\'')Data[n++]=Buf[i];
			if(c>((index*2+1)))return n;
		}	
	}
	Data[n]=0;
	return n;
}
/******************************************************************************
Func:ƥ���ַ���
Time:2014-4-28
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note:����ƥ�䵽���ַ�������ĸ��ַ��û�ҵ�����0
******************************************************************************/
char *Strstr(const char*s1,const char*s2)
{
    int n;
    if(*s2)
    {
        while(*s1)
        {
            for(n=0;*(s1+n)==*(s2+n);n++)
            {
                if(!*(s2+n+1))
                    return(char*)s1;
            }
            s1++;
        }
        return NULL;
    }
    else
        return (char*)s1;
}
/******************************************************************************
Func:���ݴ�64����ת����Ŀ����Ϊ��ѹ������
Time:2014-4-28
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note:��������int
******************************************************************************/
int FromHex64(char t)//�ַ�--->>���� 
{
     if(t>='0'&&t<='9')return t-'0';//����
    if(t>='A'&&t<='Z')return t-'A'+10;//��д��ĸ
    else return t-'a'+36;//Сд��ĸ
}
 /******************************************************************************
Func:��64����ת��
Time:2014-4-28
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note:
******************************************************************************/
char ToHex64(int t)//����-->>>�ַ�
{
  if(t>=0&&t<=9)return (t+'0');
  if(t>=10&&t<=35)return (t-10+'A');
  else return (t-36+'a');
}
/*******************************************************************************************
Func:�������ݵ�RAM
Time:2014-2-2
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: ��ֵΪ�����
*******************************************************************************************/
void Coppy_FromConst(uint8 *D,const uint8 *S,uint16 Length)
{
		while(Length--)*D++=*S++;
}
/*******************************************************************************************
Func:��ȡcount �����ַ�������
Time:2014-5-2
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: ��ֵΪ�����
*******************************************************************************************/
uint16 GetCountSize(const uint8 *Tags)
{
	uint16 i;
	for(i=0;i<0xffff;i++)
	{
		if(Tags[i]==0)return i;
	}
	return 0xffff;
}
/*******************************************************************************
Func:�����ؼ���
Date:2014-5-22
http://www.trtos.com/
By:ͯ����
Note:����λ��
*******************************************************************************/
uint16 StringSearchKey(uint8 *String,uint8 Key)
{
	uint16 i=0;
	while(*String)
	{
		i++;
		if(*String++==Key)return i;
	}
	return 0xffff;
}
void StringReplaceChar(uint8 *String,uint8 Key,uint8 New)
{
	uint8 *P=String;
	while(*P)
	{
		if(*P==Key)*P=New;P++;
	}
}
/******************************************************************************
Func:ɾ���Ƿ��ַ�
Time:2014-7-23
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:
******************************************************************************/
void StringTrmChar(uint8 *String,uint8 Key)
{
	uint8 *P=String,*P1=String;
	while(*P)
	{
		if(*P!=Key)*P1++=*P;
		P++;
	}
	*P1=0;
}
void HtmlGetGB2312(uint8 *String)
{
	uint8 *P=String,*P1=String;
	while(*P)
	{
		if(*P=='%'){*P1++=GetHexFromString(P+1);P+=3;}
		else *P1++=*P++;
	}
	*P1=0;
}
/******************************************************************************
Func:��ȡ�ļ��ļ������ļ��ļ���ʽ
Time:2014-7-23
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:
******************************************************************************/
void GetFileNameFormat(uint8 *File,uint8 *FileName,uint8 *FileFormat)
{
	uint16 i=StringSearchKey(&File[0],'.');
	if(FileName)
	{
		while(*File)
		{
			*FileName++=*File++;
			if(*File=='.'){File++;break;}
		}
		*FileName=0;
	}else File+=i;
	if(FileFormat&&i!=0xffff)
	{
		while(*File)
		{
			*FileFormat++=*File++;
		}
		*FileFormat=0;
	}
}
/******************************************************************************
Func:�ϲ��ļ��ļ������ļ��ļ���ʽ
Time:2014-8-1
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:
******************************************************************************/
void UniteNameFormat(uint8 *File,uint8 *FileName,uint8 *FileFormat)
{
	while(*FileName)
	{
		*File++=*FileName++;
	}
	*File++='.';
	while(*FileFormat)
	{
		*File++=*FileFormat++;
	}
	*File=0;
}
/*******************************************************************************************************----
Func:��չ��
Time:2010-7-28
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: ���������ڽ��ְ��ֽ�չ����Ŀ��ռ�
 	   Array/Ŀ��ռ�   Data/Դ��  EndMode/��С�˸�ʽ  0/С�� 1/���
 	   return P/����Array���º��λ��
******************************************************************************************************----*/
uint8  D16ToArray(void *Array,uint16 Data,uint8 EndMode)
{
    uint8 *P;
	P=(uint8 *)Array;
	if(EndMode){
        *P++=(uint8)(Data>>8);
        *P++=0xff&Data;        
	}else{
        *P++=0xff&Data;
        *P++=(uint8)(Data>>8);
	}	
	return 2;
}


/*******************************************************************************************************----
Func:˫��չ��
Time:2010-7-28
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: ���������ڽ�˫�ְ��ֽ�չ����Ŀ��ռ�
 	   Array/Ŀ��ռ�   Data/Դ˫��  EndMode/��С�˸�ʽ  0/С�� 1/���
 	   return P/����Array���º��λ��
******************************************************************************************************----*/
uint8 D32ToArray(void *Array,uint32 Data,uint8 EndMode)
{
    uint8 *P;
	P=(uint8 *)Array;
	if(EndMode){
        *P++=(uint8)(Data>>24);
	    *P++=(uint8)(Data>>16);
        *P++=(uint8)(Data>>8);
        *P++=(uint8)Data;
	}else{	    
        *P++=(uint8)Data;
        *P++=(uint8)(Data>>8);
        *P++=(uint8)(Data>>16);
        *P++=(uint8)(Data>>24);
	}	
	return 4;
}


/*******************************************************************************************************----
Func:�����
Time:2010-7-28
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: ���������ڽ�Ŀ��ռ䰴�ֽ���ͳ���
 	   Array/Ŀ��ռ�   Data/Դ��  EndMode/��С�˸�ʽ  0/С�� 1/���
 	   return P/����Array���º��λ��
******************************************************************************************************----*/
uint16 D16FromArray(void *Array,uint8 EndMode)
{
    uint8 *P;
    uint16 Data;
    P=(uint8 *)Array;
    if(EndMode)
    {
        Data =*P++; Data<<=8;
        Data|=*P++;
    }else{
        Data=*(P+1);Data<<=8;
        Data|=*P;
    }
    return Data;
}


/*******************************************************************************************************----
Func:˫�����
Time:2010-7-28
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: ���������ڽ�Ŀ��ռ䰴�ֽ���ͳ�˫��
 	   Array/Ŀ��ռ�   EndMode/��С�˸�ʽ  0/С�� 1/���
 	   return P/����Array���º��λ��
******************************************************************************************************----*/
uint32 D32FromArray(void *Array,uint8 EndMode)
{
    uint8 *P;
    uint32 Data;
    P=(uint8 *)Array;
		switch(EndMode)
		{
			case 1:
				 Data =*P++;Data<<=8;
        Data|=*P++;Data<<=8;
        Data|=*P++;Data<<=8;
        Data|=*P;
				break;
			case 0:
				 P+=3;
        Data =*P--;Data<<=8;
        Data|=*P--;Data<<=8;
        Data|=*P--;Data<<=8;
        Data|=*P;
			break;
			case 2:
				Data =*(P+2);Data<<=8;
        Data|=*(P+3);Data<<=8;
        Data|=*(P+0);Data<<=8;
        Data|=*(P+1);
			break;
		}
    return Data;
}
/*******************************************************************************************************----
Func:˫�����
Time:2010-7-28
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: ���������ڽ�Ŀ��ռ䰴�ֽ���ͳ�˫��
 	   Array/Ŀ��ռ�   EndMode/��С�˸�ʽ  0/С�� 1/���
 	   return P/����Array���º��λ��
******************************************************************************************************----*/
float F32FromArray(void *Array,uint8 EndMode)
{
    uint8 *P;
    uint32 Data;
    P=(uint8 *)Array;
    if(EndMode)
    {
        Data =*P++;Data<<=8;
        Data|=*P++;Data<<=8;
        Data|=*P++;Data<<=8;
        Data|=*P;
    }else{
        P+=3;
        Data =*P--;Data<<=8;
        Data|=*P--;Data<<=8;
        Data|=*P--;Data<<=8;
        Data|=*P;
    }
    return *((float *)&Data);
}

/*******************************************************************************************
Func:��ȡ�ַ����ĺͣ���ֵΪ�����
Time:2014-2-2
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: *
*******************************************************************************************/
uint16 GetArraySum(void *Tags,uint16 Lentgh)
{
	uint16 i;
	uint8 *Msg=(uint8 *)Tags;
	uint16 Sum=0;
	for(i=0;i<Lentgh;i++)
	{
		Sum+=Msg[i];
		if(Msg[i]==0)return Sum;
	}
	return Sum;
}
uint16 GetStringByFmt(char *String,char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	vsprintf(String,fmt,ap);
	va_end(ap);
	return GetTextLength(String);
}
/*******************************************************************************************
Func:TTS�����㷨 ����ת��Ϊ�ַ���
Time:2014-2-2
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: *Dstr/ת������ַ��� Number/��ת�������� DotLenth/С�������λ��
*******************************************************************************************/
uint8 GetStringFromNumber(uint8 *Dstr,f32 Number,uint8 NumType,uint8 DotLenth)
{
	uint8 Temp[40],j=0,i=0,k;
	int32 T,M=0;
	switch(NumType){	
		case 'B':	M=2;	break;
		case 'O':	M=8;	break;
		case 'D':	M=10;	break;
		case 'H':	M=16;	break;
	}
	if(Number<0){					//ȡ����
		*Dstr++='-';
		Number=0-Number;
		j++;
	}
	T=(int32)Number;				//ȡ��������
	Number-=T;						//ȡС������
	do
	{								//�����������
        k=T%M;
        Temp[i++] = k>9 ? k-10+'A' : k+'0';
		T/=M;		
	}while(T>0);
	j+=i;
	while(i--)*Dstr++=Temp[i];		//�洢��������	
	if((DotLenth>0)&(NumType=='D')){	 //��10��������С��
		j++;
		*Dstr++='.';		
		while(DotLenth--){
			Number*=M;
			i=(uint8)Number;			
			*Dstr++=i+'0';
			Number-=i;
			j++;	
		}
	}	
	*Dstr=0;
	return ++j;
}
/******************************************************************************
Func:��ȡBool���͵�ֵ
Time:2014-10-12
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:
******************************************************************************/
BOOL VoidGetBool(uintbus Value)
{
	BOOL V;
	V=*(BOOL *)Value;
	if(V!=False)V=True;
	return V;
}
/******************************************************************************
Func:��ȡuint32���͵�ֵ
Time:2014-10-12
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:
******************************************************************************/
uint32 VoidGetU32(uintbus Value)
{
	uint32 V;
	V=*(uint32 *)Value;
	return V;
}
/******************************************************************************
Func:��ȡBool���͵�ֵ
Time:2014-10-12
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:
******************************************************************************/
f32 VoidGetF32(uintbus Value)
{
	f32 V;
	V=*(f32 *)Value;
	return V;
}
/******************************************************************************
Func:�ַ���ת����������
Time:2015-8-3
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: 
******************************************************************************/
f32 GetStringToNumber(uint8 *Sstr)
{
	uint8 T,F=0,D=0;
	f32 RealValue=0;
	f32 Factor=1;
	while(*Sstr>0){
		T=*Sstr++;
		if(T=='-')F=1;
		else if(T=='.'){D=1;}
		else if((T>='0')&&(T<='9')){
			if(!D){RealValue*=10;RealValue+=T-'0';}
			else 
			{
				Factor*=0.1;
				RealValue+=(Factor*(T-'0'));
			}
		}else 
		{
			if(F)RealValue*=(-1);//�����Ƿ��ַ���Ϊ������
			return RealValue;
		}
	}
	if(F)RealValue*=(-1);
	return RealValue;
}
/*******************************************************************************************
Func:TTS�����㷨 �ַ���ת��Ϊ����//����㷨��������д��������
Time:2010-3-25
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: *Sstr/��ת����Դ�����ַ��� return/ת�������ֵ
 	   ���ַ����к��зǷ��ַ�����0ֵ
*******************************************************************************************/
f32 _GetStringToNumber(uint8 *Sstr)
{
	uint8 T,F=0,D=0,Factor=0;
	f32 RealValue=0;
	while(*Sstr>0){
		T=*Sstr++;
		if(T=='-')F=1;
		else if(T=='.'){
			D=1;Factor=10;
		}else if((T>='0')&&(T<='9')){		
			T=T-'0';	
			if(D==0)RealValue=RealValue*10+T;
			else	{
				RealValue=RealValue+(f32)T/(f32)Factor;
				Factor*=10;
			}
		}else return 0;		
	}
	if(F)RealValue*=(-1);
	return RealValue;
}
/*******************************************************************************
Func:BOOL���ʹ��ַ���ת��
Date:2014-5-22
http://www.trtos.com/
By:ͯ����
Note:
*******************************************************************************/
BOOL GetStringToBool(uint8 *Str)
{
	while(*Str)
	{
		if(*Str=='Y')return True;
		if(*Str=='N')return False;
		Str++;
	}
	return False;
}
/*******************************************************************************
Func:Buf���
Date:2014-5-22
http://www.trtos.com/
By:ͯ����
Note:
*******************************************************************************/
void BufferFill(void *S,uint8 Data,uint16 Length)
{
	uint8 *P;
	P=(uint8 *)S;
	while(Length--)*P++=Data;
}

/*******************************************************************************************
Func:�����ַ���
Time:2014-2-2
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: *
*******************************************************************************************/
uint16 BufferCoppy(void *S,void *Out,uint16 Length)
{
	uint16 Count=0;
	INT8U *PS,*PD;
	PS=(INT8U *)S;
	PD=(INT8U *)Out;
	Count =Length;
	while (Length--)
	{
		(*PD++)=(*PS++);
	}
	return Count;
} 
/*******************************************************************************************
Func:�����ַ���
Time:2014-2-2
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: *
*******************************************************************************************/
uint16 StringCoppy(void *S,void *Out)
{
	uint16 i=0;
	INT8U *PS,*PD;
	PS=(INT8U *)S;
	PD=(INT8U *)Out;
	while (*PS)
	{
		(*PD++)=(*PS++);
		i++;
	}
	*PD=0;
	return i;
}
/*******************************************************************************
Func:TQFS���õ���   ��ȡ��ȷ���ַ���
Date:2014-5-22
http://www.trtos.com/
By:ͯ����
Note:�ַ�����β��Ϊδ����0xff ��Ϊ0
*******************************************************************************/
void CreateTrueString(void *S)
{
	uint8 i;
	uint8 *P=(uint8 *)S;
	for(i=0;i<0xff;i++)
	{
		if(P[i]==0xff&&P[i+1]==0xff)break;
		if(P[i]==0x00)return;
	}
	P[i]=0x00;
}
/*******************************************************************************************
Func:�ַ���Сдת��
Time:2014-2-2
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: Dir=FalseתΪ��д  Dir=True תΪСд
*******************************************************************************************/
void CharToUpperLower(uint8 Byte,BOOL Dir)
{
	if(Dir)
	{
		if(Byte<='z'&Byte>='a')Byte-=('a'-'A');
	}else 
	{
		if(Byte<='Z'&Byte>='A')Byte+=('a'-'A');
	}
}
/*******************************************************************************************
Func:�ַ�����Сдת��
Time:2014-2-2
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: Dir=FalseתΪ��д  Dir=True תΪСд
*******************************************************************************************/
void StringToUpperLower(uint8 *String,BOOL Dir)
{
	while(*String>0)
	{
		CharToUpperLower(*String++,Dir);
	}
}
/*******************************************************************************************
Func:�ַ������β
Time:2014-2-2
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: 
*******************************************************************************************/
void StringEndingAppend(void *End,void *Out)
{
	int Length;
	INT8U *PS,*PD;
	PS=(INT8U *)Out;
	PD=(INT8U *)End;
	PS+=GetTextLength(Out);
	Length=GetTextLength(End);
	if(Length==-1)return;
	while(Length--)
	{
		(*PS++)=(*PD++);
	}
	(*PS++)=0;
}
/**************************************************************************************
Func:�ַ������ͷ
Time:2014-2-2
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: 
***************************************************************************************/
void StringHeadAppend(void *Head,void *Out)
{
	INT8U Temp[40];
	StringCoppy(Head,&Temp[0]);
	StringEndingAppend(Out,&Temp[0]);
	StringCoppy(&Temp[0],Out);
}
/***************************************************************************************
Func:��ֵ�˲��㷨,ȥ����Сֵ�����ֵ
Time:2013-7-5
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: ȥ��һ����Сֵ,ȥ��һ�����ֵ,��ȥ����ֵ������дΪ0
 	   ������Ҫ������ֵ�������0,��Ϊ���򱻺���
****************************************************************************************/
void MidFilter_ByWords(uint16 *Sdata,uint16 Length)
{
	uint16 *Sptr,ID,Min,Max,MinID,MaxID;
	if(Length<3)return;
	Sptr=Sdata;Min=0xFFFF;Max=0;ID=0;MinID=0;MaxID=0;
	do{
		if(*Sdata<Min)	{Min=*Sdata;MinID=ID;}
		if(*Sdata>=Max) {Max=*Sdata;MaxID=ID;}
		Sdata++;ID++;
	}while(--Length);
	Sptr[MinID]=0;	Sptr[MaxID]=0;
}
/***************************************************************************************
Func:MQTT���ȴ��
Date:2016-4-22
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint8 MQTT_LegnthToByte(uint32 Length,uint8 *Bytes)
{
	uint8 digit,i=0;
	do
	{
  digit =Length%128;
  Length = Length/128;
  if (Length>0)
    digit = digit|0x80;
		Bytes[i++]=digit;
	}
	while(Length>0);
	return i;
}
/***************************************************************************************
Func:MQTT���Ƚ��
Date:2016-4-22
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint32 MQTT_GetLength(uint8 *Bytes)
{
	uint8 multiplier =1,i=0,digit;
	uint32 value=0;
	do
	{
  digit =Bytes[i++];
  value +=(digit&127) * multiplier;
  multiplier *= 128;
	}
	while((digit&128) != 0);
	return value;
}
float Abs(float Data)
{
	if(Data>0)return Data;
	else return (0-Data);
}
/*******************************************************************************************
Func:ƽ��ֵ�˲�,��ȡ�����ƽ��ֵ
Time:2013-7-5
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: 
*******************************************************************************************/
uint16 AvrFilter_ByWords(uint16 *Sdata,uint16 Length,uint16 SumLen)
{
	uint32 Tsum=0;
	if(Length==0)return 0;
	do{	Tsum+=*Sdata++;	}while(--Length);
	return (uint16)(Tsum/SumLen);
}
/*******************************************************************************************
Func:����ɢ��
Time:2013-7-5
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note: 
*******************************************************************************************/
uint32 DispersionRatioByWords(uint16 *Sdata,uint16 Length)
{
	uint16 Avr;
	uint32 Dis=0;
	Avr=AvrFilter_ByWords(Sdata,Length,Length);
	do{	Dis+=__fabs(Avr-(*Sdata++));}while(--Length);
 return Dis;
}
/*******************************************************************************************
Func:�����˲���
Time:2014-9-18
Ver.:V2.0
http://www.trtos.com/
By:ͯ����
Note: 
*******************************************************************************************/
uint16 FlowPoolFilter(uint32 *Pool,uint16 Data,uint8 *PoolIndex,uint8 PoolSize)
{
	uint16 Old_Filter=0;
	if(*PoolIndex)Old_Filter=((*Pool)/(*PoolIndex));
	(*Pool)+=Data;
	if((*PoolIndex)<PoolSize)(*PoolIndex)++;
	else (*Pool)-=Old_Filter; 
	return (*Pool)/(*PoolIndex);
}
/***************************************************************************************
Func:�������л�ȡ16λ���ȵ�����
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:Mode=0С��,Mode=1���
***************************************************************************************/
uint16 GetWordFromBytes(string Buf,uint8 Mode)
{
	uint16 Temp=0;
	if(Mode==0)
	{
		Temp=Buf[1];
		Temp<<=8;
		Temp|=Buf[0];
	}else
	{
		Temp=Buf[0];
		Temp<<=8;
		Temp|=Buf[1];
	}
	return Temp;
}
/***************************************************************************************
Func:����16λ��ȵ����ݵ�������
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:Mode=0С��,Mode=1���
***************************************************************************************/
uint8 SetWordToBytes(string Buf,uint16 Data,uint8 Mode)
{
	if(Mode==0)
	{
		Buf[1]=Data>>8;
		Buf[0]=Data&0xff;
	}else
	{
		Buf[0]=Data>>8;
		Buf[1]=Data&0xff;
	}
	return 2;
}
/***************************************************************************************
Func:Ѱ���ַ�����
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint16 FindChar_Count(string Str,char Key)
{
	uint16 Count=0;
	while(*Str)
	{
		if(*(Str++)==Key)Count++;
	}
	return Count;
}
/***************************************************************************************
Func:Ѱ�ҹؼ���
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint16 SerchKeyFromBytes(uint8 *Buf,uint8 Key,uint16 Length)
{
	uint16 i;
	for(i=0;i<Length;i++)
	{
		if((*Buf++)==Key)return i;
	}
	return 0xffff;
}
/***************************************************************************************
Func:�Ƚ�����
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
BOOL CompareWithBuffer(uint8 *S,uint8 *K,uint16 Length)
{
	while(Length--)
	{
		if(*S++!=*K++)return False;
	}
	return True;
}
/***************************************************************************************
Func:�Ƚ��ַ���
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
BOOL CompareWithString(uint8 *S,uint8 *K)
{
	if(GetTextLength(S)!=GetTextLength(K))return False;
	while(*S&&*K)
	{
		if(*S++!=*K++)return False;
	}
	return True;
}
/***************************************************************************************
Func:�����ַ�λ�ò���¼λ��
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint8 SplitWithString(uint8 *S,uint8 Key,uint8 *Buf)
{
	uint8 Index=0;
	uint8 i=0;
	while(*S)
	{
		if(*S==Key){Buf[i++]=Index;}
		Index++;
		S++;
	}
	if(Index==0)return 0;
	return i+1;
}
/***************************************************************************************
Func:���������
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
void ClearWithBuffer(uint8 *S,uint16 Length)
{
	while(Length--)
	{
		*S++=0;
	}
}
/***************************************************************************************
Func:���㵽����
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint8 Float32ToByte(uint8 *S,float Data,uint8 Mode)
{
	uint8 *P;
	uint8 i=4;
	P=(uint8 *)&Data;
	switch(Mode)
	{
		case 0:
			while(i--)
			{
				*S++=*P++;
			}break;
		case 1:
			break;
	}
	return 4;
}
/***************************************************************************************
Func:���ε�����
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint16 Uint32ToByte(uint8 *S,uint32 Data)
{
	uint8 *P;
	uint8 i=4;
	P=(uint8 *)&Data;
	while(i--)
	{
		*S++=*P++;
	}
	return 4;
}
/***************************************************************************************
Func:
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint16 Uint16ToByte(uint8 *S,uint32 Data)
{
	uint16 *P;
	uint8 i=4;
	P=(uint16 *)&Data;
	while(i--)
	{
		*S++=*P++;
	}
	return 2;
}
/***************************************************************************************
Func:���ε�����
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
float Float32FromByte(uint8 *S)
{
	float *P;
	P=(float *)S;
	return *P;
}
/***************************************************************************************
Func:���ε�����
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint32 Uint32FromByte(uint8 *S)
{
	uint32 *P;
	P=(uint32 *)S;
	return *P;
}
/***************************************************************************************
Func:IP���ַ���
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint8 IpPortToString(IpPortStruct *IPPort,uint8 *String)
{
	uint8 n,Length,Index=0;
	for(n=0;n<4;n++)
	{
		Length=GetStringFromNumber(&String[Index],IPPort->Ip[n],'D',0);
		Index+=(Length);
		if(n==3)String[Index-1]=':';else String[Index-1]='.';
	}
	Length=GetStringFromNumber(&String[Index],IPPort->Port,'D',0);
	Index+=(Length);
	return Index;
}
/***************************************************************************************
Func:�ַ���תIP
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
void IpPortFromString(IpPortStruct *IPPort,uint8 *String)
{
	uint8 i=0,c=0;
	uint16 T=0;
	while(*String)
	{
		if((*String>='0')&(*String<='9'))
		{
			T*=10;
			T+=(*String-'0');
		}
		if(*String=='.'){IPPort->Ip[c++]=T;T=0;}
		if(*String==':'){IPPort->Ip[c++]=T;T=0;}
		String++;
		if(i++>20)break;
	}
	IPPort->Port=T;
}
/***************************************************************************************
Func:
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint32 StringToIPUint32(uint8 *String)
{
	uint8 i=0;
	uint16 T=0;
	uint32 Temp=0;
	while(*String)
	{
		if((*String>='0')&(*String<='9'))
		{
			T*=10;
			T+=(*String-'0');
		}
		if(*String=='.'){Temp<<=8;if(T>0xff)T=0xff;Temp|=T;T=0;}//������������⣬��ʱûʱ�俴
		String++;
		if(i++>15)break;
	}
	Temp<<=8;Temp|=T;
	return Temp;
}
/***************************************************************************************
Func:
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint8 IPUint32ToString(uint8 *String,uint32 IP)
{
	uint8 n,Length,Temp,Index=0;
	for(n=0;n<4;n++)
	{
		Temp=IP/0xffffff;
		IP<<=8;
		Length=GetStringFromNumber(&String[Index],Temp,'D',0);
		Index+=(Length);
		if(n!=3)String[Index-1]='.';	
	}
	return Index;
}
/***************************************************************************************
Func:
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint8 Bcd_Decimal(uint8 bcd)
{
 return bcd-(bcd >> 4)*6;
}
/***************************************************************************************
Func:
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint8 Decimal_Bcd(uint8 decimal)
{
	return (uint8) (decimal+(decimal / 10)*6);
}
/***************************************************************************************
Func:
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
void FmtToBuf(char *String,char *fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    vsprintf(String,fmt,ap);
    va_end(ap);
}
/*******************************************************************************
Func:ģʽƥ��
Date:2015-09-05
http://www.trtos.com/
By:ͯ����
Note:ϵͳ��strstr������Ȼ�����⣬ֻ���Լ�ʵ����
*******************************************************************************/
uint16 BytesFindString(char *S,const char *T,int Length)
{
	uint16 i=0,j=0;
	while(Length-->0&T[j]>0)
	{
		if(S[i]==T[j])
    {i++;j++;}
		else {i=i-j+1;j=0;}
	}
	if(T[j]==0)return i;
	else return 0;
}
/*******************************************************************************
Func:���ַ���ת��16������
Date:2015-09-05
http://www.trtos.com/
By:ͯ����
Note:
*******************************************************************************/
uint8 GetHexFromString(uint8 *String)
{
	uint8 Data=0x00;
	if((String[0]>='0')&(String[0]<='9'))Data=(String[0]-'0')*16;
	else if((String[0]>='A')&(String[0]<='F'))Data=(String[0]-'A'+10)*16;
	else if((String[0]>='a')&(String[0]<='f'))Data=(String[0]-'a'+10)*16;
	if((String[1]>='0')&(String[1]<='9'))Data+=(String[1]-'0');
	else if((String[1]>='A')&(String[1]<='F'))Data+=(String[1]-'A'+10);
	else if((String[1]>='a')&(String[1]<='f'))Data+=(String[1]-'a'+10);
	return Data;
}
/*******************************************************************************
Func:��TFT565ɫת������ɫ
Date:2015-09-15
http://www.trtos.com/
By:ͯ����
Note:
*******************************************************************************/
Color_RGB TFT_RGB(uint16 Color)
{
	Color_RGB T;
	T.R=0x1f&(Color>>11);
	T.G=0x3f&(Color>>5);
	T.B=0x1f&(Color);
	return T;
}
/*******************************************************************************
Func:24bitɫתTFT565ɫ
Date:2015-09-15
http://www.trtos.com/
By:ͯ����
Note:
*******************************************************************************/
uint16 RGB_TFT(Color_RGB T)
{
	uint16 C;
	C=0x1f&(T.R);
	C<<=6;
	C|=(0x3f&(T.R));
	C<<=5;
	C|=(0x1f&(T.B));
	return C;
}
/***************************************************************************************
Func:
Date:2014-6-14
http://www.trtos.com/
By:ͯ����
Note:
***************************************************************************************/
uint16 ALL_TFT(uint32 Color)
{
	uint16 C;
	C=0x1f&(Color>>16);
	C<<=6;
	C|=(0x3f&(Color>>8));
	C<<=5;
	C|=(0x1f&(Color));
	return C;
}
/*******************************************************************************
Func:�޵ж˵㽻��
Date:2017-03-25
http://www.trtos.com/
By:ͯ����
Note:SwitchEndian(BufA,BufB,4,0x4321);
����Ȥ
		SwitchEndian(&F,BufA,4,0x3214);
		SwitchEndian(BufA,&f,4,0x3214);
		DeBug("%x",f,1);
*******************************************************************************/
uint8 SwitchEndian(void *S,void *D,uint8 Length,uint32 Endian)
{
	uint8 Buf[8],c,ci;
	uint8 *PS=(uint8 *)S;
	uint8 *PD=(uint8 *)D;
	uint8 i=Length;
	for(c=0;c<sizeof(Buf);c++)
	{
		Buf[c]=(Endian&0xf);
		if(!Buf[c])break;
		Buf[c]-=0x01;
		Endian>>=4;
	}
		i/=c;
		while(i--)
		{
			for(ci=0;ci<c;ci++)
			{
				PD[ci]=PS[Buf[c-ci-1]];
			}
			PD+=c;
		}
	return Length;
}
//��ë��
void *GetVoidData(void *S,uint8 Length,uint32 Endian)
{
	uint8 *P;
	SwitchEndian(S,P,Length,Endian);
	return (void *)P;
}
