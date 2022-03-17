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

	/* Test Begin */
	measure_init();
	testPWM_init(999);
	while(1)
	{
		ADC_RegularChannelConfig(ADC1,2,1,ADC_SampleTime_7Cycles5);
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
		OLED_show8x16number(0,0,ADC_GetConversionValue(ADC1));
	}
	/* Test End */

	return 0;
}
