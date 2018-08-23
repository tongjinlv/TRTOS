/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/

void Beep_Dot(uint16 z)
{
	uint16 i;
	i=z;
	GPIO_SetIndex(5,0);
	while(i--);
	GPIO_SetIndex(5,1);
	i=z;
	while(i--);
	GPIO_SetIndex(5,0);
}
//滴滴
void Beep_DD(uint16 f,uint16 w,uint8 d)
{
	uint16 W;
	while(d--)
	{
		W=w;
		while(W--)Beep_Dot(f);
		Tos_TaskDelay(30);
	}
}
//变频到
void Beep_A2B(uint16 A,uint16 B)
{
	while(A!=B)
	{
		Beep_Dot(A);
		if(A>B)A--;
		if(A<B)A++;
	}
}
void Beep_A2BT(uint16 A,uint16 B,uint16 T)
{
	if(A==B)
	{
		while(T--)
		{
			Beep_Dot(A);
			if(T%100==0)Tos_TaskDelay(1);
		}
		return;
	}
		while(A!=B)
		{
		Beep_Dot(A);
		if(A>B)A--;
		if(A<B)A++;
		}
}
//蜜蜂叫
void Beep_Bee()
{
	Beep_A2B(400,600);
	Tos_TaskDelay(30);
	Beep_A2B(600,90);
	Tos_TaskDelay(10);
	Beep_A2B(600,90);
	Tos_TaskDelay(40);
	Beep_A2B(300,500);
}

void Beep_ON()
{
	Beep_A2B(0,500);
	Beep_DD(500,400,2);
	Beep_A2B(500,600);
	Beep_DD(1000,330,1);
}
void Beep_OFF()
{
	Beep_DD(800,330,2);
	Beep_DD(600,400,2);
}
void Beep_TIM(uint16 A,uint16 B,uint16 T)
{
//	if(A==B)
//	{
//		TIM1_SetPin(5,A);
//		Tos_TaskDelay(T);
//	}else
//	{
//		while(A!=B)
//		{
//		TIM1_SetPin(5,A);
//		if(A>B)A--;
//		if(A<B)A++;
//		Tos_TaskDelay(1);
//		}
//	}
//	TIM1_SetPin(5,0);
//	GPIO_SetIndex(5,0);
}
