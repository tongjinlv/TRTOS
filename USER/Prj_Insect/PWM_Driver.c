/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>


#define PWM_PERIOD 1600


void PwmTimeInt(void)
{
	//TIM4：B6、7、8、9
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4  , ENABLE );//时钟配置
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3  , ENABLE );//时钟配置
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2  , ENABLE );//时钟配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);   /*打开APB2总线上的GPIOA时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC ,ENABLE);   /*打开APB2总线上的GPIOA时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);   /*打开APB2总线上的GPIOA时钟*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM4_CH1,B6   PWM0
	GPIO_Init( GPIOB , &GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM4_CH2,B7   PWM1
	GPIO_Init( GPIOB , &GPIO_InitStructure );
	TIM_TimeBaseStructure.TIM_Period = PWM_PERIOD;//计数重载值为 1KHz
	TIM_TimeBaseStructure.TIM_Prescaler = 2;//预分频值为2+1=3
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//时钟分割0
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInit( TIM4 , &TIM_TimeBaseStructure );
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//工作模式为PWM输出模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//使能比较区配输出极性
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//向上计数
	TIM_OCInitStructure.TIM_Pulse = 0;//预设定的脉宽
	TIM_OC1Init( TIM4 , &TIM_OCInitStructure );
	TIM_OC2Init( TIM4 , &TIM_OCInitStructure );
	TIM_OC3Init( TIM4 , &TIM_OCInitStructure );
	TIM_OC4Init( TIM4 , &TIM_OCInitStructure );
	TIM_OC1PreloadConfig( TIM4 , TIM_OCPreload_Enable );
	TIM_OC2PreloadConfig( TIM4 , TIM_OCPreload_Enable );
	TIM_OC3PreloadConfig( TIM4 , TIM_OCPreload_Enable );
	TIM_OC4PreloadConfig( TIM4 , TIM_OCPreload_Enable );
	TIM_ARRPreloadConfig( TIM4 , ENABLE );//ARR预装最好使能,否则可能会有意外的情况.
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


