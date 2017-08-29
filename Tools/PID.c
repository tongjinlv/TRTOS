/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <include.h>
#include <PID.h>
typedef struct PID_Uint
 {
	int U_kk;
	int ekk;
	int ekkk;
	int Ur;                                //�޷����ֵ,���ʼ��
	int Un;                                //��������
	//int multiple;                //PIDϵ���ķŴ��������������ݵ�����£����PID���������þ���          �̶�Ϊ256
	int Kp;                                //��������С�����
	int Ti;                                //���֣��Ӵ���С��
	int Td;                                //΢�֣���Ѳ�߰�ʱ��Ϊ0
	int k1;                                //
	int k2;
	int k3;
 }PID_Uint;
/******************************************************************** 
�� �� ����void Init_PID_uint(PID_uint *p)
��    �ܣ���ʼ��PID����
 ˵    �������ñ�����֮ǰ��Ӧ���ȶ�Kp,Ti,Td������        ,���˹�ʽ
 ��ڲ�����PID��Ԫ�Ĳ����ṹ�� ��ַ
 �� �� ֵ����
***********************************************************************/
void Init_PID_uint(PID_Uint *p)
 {
         p->k1=(p->Kp)+(p->Kp)*1024/(p->Ti)+(p->Kp)*(p->Td)/1024;
         p->k2=(p->Kp)+2*(p->Kp)*(p->Td)/1024;
         p->k3=(p->Kp)*(p->Td)/1024;
 }
 /******************************************************************** 
�� �� ����void reset_Uk(PID_Uint *p)
��    �ܣ���ʼ��U_kk,ekk,ekkk
˵    �����ڳ�ʼ��ʱ���ã��ı�PID����ʱ�п�����Ҫ����
 ��ڲ�����PID��Ԫ�Ĳ����ṹ�� ��ַ
 �� �� ֵ����
***********************************************************************/
void reset_Uk(PID_Uint *p)
 {
         p->U_kk=0;
         p->ekk=0;
         p->ekkk=0;
 }
 /******************************************************************** 
�� �� ����int PID_commen(int set,int jiance,PID_Uint *p)
��    �ܣ�ͨ��PID����
 ˵    ���������ⵥ��PID�Ŀ�����
 ��ڲ���������ֵ��ʵ��ֵ��PID��Ԫ�ṹ��
 �� �� ֵ��PID������
***********************************************************************/
int PID_common(int set,int jiance,PID_Uint *p)
 {
         int ek,U_k=0;
         ek=jiance-set;
         if((ek>(p->Un))||(ek<-(p->Un)))                //���ֲ�������
                U_k=(p->U_kk)+(p->k1)*ek-(p->k2)*(p->ekk)+(p->k3)*(p->ekkk);
         p->U_kk=U_k;
            p->ekkk=p->ekk;
         p->ekk=ek;
         if(U_k>(p->Ur))                                        //��������������
                U_k=p->Ur;
         if(U_k<-(p->Ur))
                 U_k=-(p->Ur);        
         return U_k/1024; 
 }
/*-------------------------------------------------------------------------
Func:������PID�㷨 ��ʼ������
Time:2010-8-8
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:
-------------------------------------------------------------------------*/
void PID_Create(PID *PID,f16 Kp,f16 Ki,f16 Kd,int16 MaxOut,int16 MinOut)
{
    PID->Kp=Kp;
    PID->Ki=Ki;
    PID->Kd=Kd;    
    PID->Error=0;
    PID->LError=0;
    PID->LLError=0;
    PID->Output=0;
    PID->Outset=0;
    PID->MaxOutput=MaxOut;
    PID->MinOutput=MinOut;
}

/*-------------------------------------------------------------------------
Func:������PID�㷨 ����Ԥ�����
Time:2010-8-8
Ver.:V1.0
http://www.trtos.com/
By:ͯ����
Note:
-------------------------------------------------------------------------*/
void PID_SetOutput(PID *PID,f16 SetValue)
{
    if(SetValue > PID->MaxOutput)PID->Outset = PID->MaxOutput;
    else if(SetValue < PID->MinOutput)PID->Outset = PID->MinOutput;    
    else PID->Outset = SetValue;    
}

/*-------------------------------------------------------------------------
Func:������PID�㷨 ���㵱ǰ���
Time:2010-8-8
Ver.:V1.0 
http://www.trtos.com/
By:ͯ����
Note: CurValue/��ǰ����ֵ 
       ����/��ǰ����õ������ֵ
-------------------------------------------------------------------------*/
int16 PID_CrcOutput(PID *PID,int16 CurValue)
{
    f16 P,I,D;
    int16 V;
    PID->Error = CurValue - PID->Outset;
    P = PID->Kp * (PID->Error - PID->LError);
    I = PID->Ki * PID->Error;
    D = PID->Kd * (PID->Error + PID->LLError - 2*PID->LError);
    PID->LLError = PID->LError;
    PID->LError  = PID->Error;
    V=(int16)(P+I+D);
    if(V > PID->MaxOutput)V = PID->MaxOutput;
    else if(V < PID->MinOutput)V = PID->MinOutput;
    PID->Output=V;
    return V;
}
