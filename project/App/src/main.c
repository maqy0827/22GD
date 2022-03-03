/*
 * @Author: 诗云
 * @Date: 2022-02-28 10:22:38
 * @FilePath: \22GDproject\project\App\src\main.c
 * @Description: 主函数
 * 
 */
#include "stm32f10x.h"
#include "oled.h"
#include "delay.h"

int main(void)
{
	//初始化延时函数
	delay_init();
	//初始化OLED
	OLED_init();
	

	
	return 0;
}
