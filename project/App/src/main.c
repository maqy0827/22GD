/*
 * @Author: 诗云
 * @Date: 2022-02-28 10:22:38
 * @FilePath: \22GDproject\Project\App\src\main.c
 * @Description: 主函数
 *
 */
#include "stm32f10x.h"
#include "oled.h"
#include "delay.h"
#include "measure.h"
#include "stdio.h"

//重定向 printf 函数
int fputc(int ch, FILE *f)
{
	while (!(USART1->SR & USART_FLAG_TXE));
	USART1->DR = (uint8_t)ch;
	return ch;
}


//激光波长，单位0.1nm
#define Laser_WaveLength (632/2)

int main(void)
{
	uint8_t mode = 2;
	int ans = 0,N = 0;
	delay_init();	//初始化延时函数
	OLED_init();	//初始化OLED
	measure_init();//初始化测量所需
	//testPWM_init();

	while(1)
	{
		OLED_clear();

		//等待 SW1 被按下，开始
		while(!SW1)
		{
			OLED_show8x16string(0,0,"Waiting...");
			delay_ms(50);
		}

		//失能定时器，更改显示内容
		TIM_Cmd(TIM2,DISABLE);
		TIM_SetCounter(TIM2,0);
		OLED_clear();
		OLED_show8x16string(0,0,"Sft:");
		OLED_show8x16string(0,2,"Ctr:");
		OLED_show8x16string(0,4,"L1O:");
		TIM_Cmd(TIM2,ENABLE);

		//测量中显示
		while(!SW2)
		{
			//SW3 计数模式转换
			if(SW3)
			{
				change_mode(&mode);
				while(SW3);
			}

			//获取计数值并计算位移
			N = (int16_t)TIM_GetCounter(TIM2);
			if(mode == 1)
			{
				ans = N * Laser_WaveLength;
			}
			else if(mode == 2)
			{
				ans = N * (Laser_WaveLength/4);
			}

			//显示位移和调试信息
			OLED_show8x16number(32,0,ans);
			OLED_show8x16number(32,2,N);
			OLED_show8x16number(32,4,ADC_get(LED1_OUT,20));
			OLED_show8x16number(32,6,ADC_get(LED2_OUT,20));
			OLED_show8x16number(0,6,mode);
			delay_ms(20);
			//printf("ans=%dnm\n",ans);
			datstx(ans);
		}
		while(!SW4)
		{

		}
		delay_ms(10);
	}

	return 0;
}
