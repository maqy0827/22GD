#include "measure.h"

//测量初始化
void measure_init(void)
{
	//使用 TIM3 输出 PWM 测试 TIM2 的计数功能

	//TIM2 设定 输入捕获计数，输入端口 PA0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能 GPIOA 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		//使能TIM2时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//PA0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//50MHz 输出速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	//浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	TIM_DeInit(TIM2);
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;				//重装载寄存器
	TIM_TimeBaseStructure.TIM_Prescaler = 0;				//预分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;		//重复计数次数
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	//外部计数，预分频关闭，上升沿计数
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0);
	TIM_SetCounter(TIM2,0);
	TIM_Cmd(TIM2, ENABLE);

	return;
}

//使用 TIM3 输出两路相位差 90 度的 PWM 测试用函数
void testPWM_init(int period)
{
	//TIM3 设定比较输出，输出端口 PA6 PA7
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		//使能 TIM3 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能 GPIOA 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//使能复用时钟

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//PA6 PA7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//50MHz 输出速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//服用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_DeInit(TIM3);
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = period;				//重装载寄存器
	TIM_TimeBaseStructure.TIM_Prescaler = 31;				//预分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV2;	//时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;		//重复计数次数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStrue;
	TIM_OCInitStrue.TIM_OCMode = TIM_OCMode_Toggle;			//CNT = CCR 时反转电平
	TIM_OCInitStrue.TIM_Pulse = 0;
	TIM_OCInitStrue.TIM_OCPolarity = TIM_OCPolarity_High;	//有效输出高电平
	TIM_OCInitStrue.TIM_OutputState = TIM_OutputState_Enable;//输出使能
	TIM_OC1Init(TIM3,&TIM_OCInitStrue);
	TIM_OC2Init(TIM3,&TIM_OCInitStrue);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);		//使能预装载寄存器
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	//产生两路相位差 90 度的信号
	TIM_SetCompare1(TIM3,period/4);
	TIM_SetCompare2(TIM3,period/4*3);


	TIM_Cmd(TIM3,ENABLE);
}
