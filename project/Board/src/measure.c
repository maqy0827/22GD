#include "measure.h"

//转换模式
void change_mode(uint8_t* mode)
{
	TIM_DeInit(TIM2);
	if(*mode == 1)
	{
		TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
		*mode = 2;
	}
	else if(*mode == 2)
	{
		TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0);
		*mode = 1;
	}
	TIM_SetCounter(TIM2,0);
	TIM_Cmd(TIM2, ENABLE);
	return;
}

//测量初始化
void measure_init(void)
{
	//初始化 PB3 - PB9 按键输入引脚，PC13 LED 引脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = 0x01FC;					//PB3 - PB9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//50MHz 输出速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入，外部下拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				//PA15
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//核心板 LED引脚初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		//开漏输出
	GPIO_Init(GPIOC,&GPIO_InitStructure);


	//TIM2 设定 输入捕获计数，输入端口 PA0 ，正交解码计数时输入 PA0 PA1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能 GPIOA 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		//使能TIM2时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//PA0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//50MHz 输出速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	TIM_DeInit(TIM2);
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;				//重装载寄存器
	TIM_TimeBaseStructure.TIM_Prescaler = 0;				//预分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;		//重复计数次数
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

	//选择正交解码/直接计数
	//TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0);
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

	TIM_SetCounter(TIM2,0);
	TIM_Cmd(TIM2, ENABLE);


	//初始化 ADC1 IN2345 用于提高测量精度
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;	//PA4 - PA5
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//50MHz 输出速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			//模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//两 ADC 互相独立
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			//扫描转换模式不开
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		//连续转换模式不开
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//不适用外部触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//数据对齐方式右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;					//转换通道数量1
	ADC_Init(ADC1,&ADC_InitStructure);

	RCC_ADCCLKConfig(RCC_PCLK2_Div8);						//时钟分频 8(9 MHz)
	ADC_Cmd(ADC1,ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);				//校准
	while(ADC_GetCalibrationStatus(ADC1));	//等待校准完成


	//初始化串口1，不使用串口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);

	//初始化 PA9 PA10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据长度 8 位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		//停止位1
	USART_InitStructure.USART_Parity = USART_Parity_No;			//无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//同时收发
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);

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
	TIM_TimeBaseStructure.TIM_Prescaler = 2699;				//预分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4;	//时钟分割
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
	return;
}

void USART1send(uint8_t ch)
{
	while (!(USART1->SR & USART_FLAG_TXE));
	USART1->DR = (uint8_t)ch;
	return;
}

void datstx(uint16_t ans)
{
	USART1send(0x03);
	USART1send(0xfc);
	USART1send(ans &0x00FF);
	USART1send(ans >>8);
	USART1send(0xfc);
	USART1send(0x03);
	return;
}

uint16_t ADC_get(uint8_t channel,uint8_t time)
{
	int ans = 0;

	//设置采集通道和周期
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_71Cycles5);
	uint8_t a = time;

	//进行 time 次采集
	while(a --)
	{
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
		ans += (int)ADC_GetConversionValue(ADC1);
	}
	ans /= time;
	ans = (ans * 3300)>>12;
	return ans;
}
