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
		OLED_show8x16number(0,0,TIM_GetCounter(TIM3));
		OLED_show8x16number(0,2,adc_get(LED1_OUT));
		delay_ms(10);
	}
	/* Test End */

	return 0;
}
