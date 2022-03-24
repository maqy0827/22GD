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

//激光波长，单位0.1nm
#define Laser_WaveLength 6328

int main(void)
{
	//初始化延时函数
	delay_init();

	//初始化OLED
	OLED_init();

	//初始化测量所需
	measure_init();

	//初始化测试 PWM
	testPWM_init(999);

	while(1)
	{
		//等待 SW1 被按下
		while(!SW1)
		{
			OLED_show8x16string(0,0,"Waiting...");
			delay_ms(10);
		}

		//失能定时器，更改显示内容
		TIM_Cmd(TIM3,DISABLE);
		TIM_SetCounter(TIM3,0);
		OLED_clear();
		OLED_show8x16string(0,2,"Counter:");
		OLED_show8x16string(0,4,"ADconvt:");
		TIM_Cmd(TIM3,ENABLE);

		//测量中显示
		while(!SW2)
		{
			OLED_show8x16string(0,0,"Measuring");
			OLED_show8x16number(64,2,TIM_GetCounter(TIM3));
			OLED_show8x16number(64,4,adc_get(LED1_OUT));
			delay_ms(10);
		}
		while(!SW3)
		{

		}
		delay_ms(10);
	}

	return 0;
}
