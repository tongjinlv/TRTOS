/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
//void Moto_A(uint8 Run,uint8 Speed)
//{
//	PWM_Set(2,Speed);
//	PWM_SetMode(2,GPIO_Mode_AIN);
//	switch(Run)
//	{
//		case 0://ֹͣ
//		  GPIO_SetIndex(11,1);
//			PWM_SetMode(2,GPIO_Mode_AIN);
//			break;
//		case 1://����
//		  GPIO_SetIndex(11,0);
//	//	PWM_SetMode(2,GPIO_Mode_AF_PP);
//			break;
//		case 2://����
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

