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
	uint8_t mode = 2;
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
		OLED_show8x16string(0,2,"Ctr:");
		OLED_show8x16string(0,4,"L1O:");
		OLED_show8x16string(0,6,"L2O:");
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

			//显示当前比特
			OLED_show8x16number(0,0,mode);
			OLED_show8x16number(32,2,TIM_GetCounter(TIM2));
			OLED_show8x16number(32,4,ADC_get(LED1_OUT,20));
			OLED_show8x16number(32,6,ADC_get(LED2_OUT,20));
			delay_ms(20);
		}
		while(!SW4)
		{

		}
		delay_ms(10);
	}

	return 0;
}
