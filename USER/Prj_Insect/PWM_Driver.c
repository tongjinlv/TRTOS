/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>


#define PWM_PERIOD 1600


void PwmTimeInt(void)
{
	//TIM4��B6��7��8��9
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4  , ENABLE );//ʱ������
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3  , ENABLE );//ʱ������
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2  , ENABLE );//ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);   /*��APB2�����ϵ�GPIOAʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC ,ENABLE);   /*��APB2�����ϵ�GPIOAʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);   /*��APB2�����ϵ�GPIOAʱ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM4_CH1,B6   PWM0
	GPIO_Init( GPIOB , &GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM4_CH2,B7   PWM1
	GPIO_Init( GPIOB , &GPIO_InitStructure );
	TIM_TimeBaseStructure.TIM_Period = PWM_PERIOD;//��������ֵΪ 1KHz
	TIM_TimeBaseStructure.TIM_Prescaler = 2;//Ԥ��ƵֵΪ2+1=3
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//ʱ�ӷָ�0
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInit( TIM4 , &TIM_TimeBaseStructure );
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//����ģʽΪPWM���ģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ�ܱȽ������������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//���ϼ���
	TIM_OCInitStructure.TIM_Pulse = 0;//Ԥ�趨������
	TIM_OC1Init( TIM4 , &TIM_OCInitStructure );
	TIM_OC2Init( TIM4 , &TIM_OCInitStructure );
	TIM_OC3Init( TIM4 , &TIM_OCInitStructure );
	TIM_OC4Init( TIM4 , &TIM_OCInitStructure );
	TIM_OC1PreloadConfig( TIM4 , TIM_OCPreload_Enable );
	TIM_OC2PreloadConfig( TIM4 , TIM_OCPreload_Enable );
	TIM_OC3PreloadConfig( TIM4 , TIM_OCPreload_Enable );
	TIM_OC4PreloadConfig( TIM4 , TIM_OCPreload_Enable );
	TIM_ARRPreloadConfig( TIM4 , ENABLE );//ARRԤװ���ʹ��,������ܻ�����������.
	TIM_Cmd( TIM4 , ENABLE );
}

void PWM_SetMode(uint8 CH,GPIOMode_TypeDef Made)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = Made;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	if(CH==1)GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM4_CH2,B7   PWM1
	if(CH==2)GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM4_CH2,B7   PWM1
	GPIO_Init( GPIOB , &GPIO_InitStructure );
}

void PWM_Set(uint8 PwmChannel,uint8  PwmValue)
{
	uint32 t;
	t=PWM_PERIOD;
	   t= t*PwmValue/100;
			switch(PwmChannel)
			{
				 case 1:  TIM4->CCR1 = t;
									break;
				 case 2:  TIM4->CCR2 = t;
									break;          
			}

}


