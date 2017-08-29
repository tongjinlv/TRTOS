/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
//void Moto_A(uint8 Run,uint8 Speed)
//{
//	PWM_Set(2,Speed);
//	PWM_SetMode(2,GPIO_Mode_AIN);
//	switch(Run)
//	{
//		case 0://停止
//		  GPIO_SetIndex(11,1);
//			PWM_SetMode(2,GPIO_Mode_AIN);
//			break;
//		case 1://正向
//		  GPIO_SetIndex(11,0);
//	//	PWM_SetMode(2,GPIO_Mode_AF_PP);
//			break;
//		case 2://反向
//		  GPIO_SetIndex(11,1);
//	//	PWM_SetMode(2,GPIO_Mode_AF_PP);
//			break;
//	}
//}
void Moto_A(char Speed)
{
	if(Speed<0)
	{
		GPIO_SetIndex(11,1);
		PWM_Set(2,(uint8)(0-Speed));
	}else
	{
		GPIO_SetIndex(11,0);
		PWM_Set(2,(uint8)Speed);
	}
}
void Moto_B(char Speed)
{
	if(Speed<0)
	{
		GPIO_SetIndex(10,1);
		PWM_Set(1,(uint8)(0-Speed));
	}else
	{
		GPIO_SetIndex(10,0);
		PWM_Set(1,(uint8)Speed);
	}
}
void Moto_AB(char SA,char SB)
{
	Moto_A(SA);
	Moto_B(SB);
}

