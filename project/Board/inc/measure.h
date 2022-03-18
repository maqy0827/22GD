#ifndef __MEASURE_H__
#define __MEASURE_H__

#include "stm32f10x.h"

//板子资源初始化
extern void measure_init(void);

//正交 PWM 生成
extern void testPWM_init(int period);

//LED 控制函数
#define LED_ON (GPIO_SetBits(GPIOC,GPIO_Pin_13))
#define LED_OFF (GPIO_ResetBits(GPIOC,GPIO_Pin_13))

//键值获取
#define KEY1 (~GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15))
#define KEY2 (~GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4))
#define KEY3 (~GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6))
#define KEY4 (~GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8))
#define KEY5 (~GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3))
#define KEY6 (~GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5))
#define KEY7 (~GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
#define KEY8 (~GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))


//光电传感器与输入通道转换
#define S1_OUT ((uint8_t)3)
#define S2_OUT ((uint8_t)2)
#define LED1_OUT ((uint8_t)4)
#define LED2_OUT ((uint8_t)5)

//获取放大后的光电检测测量值
extern uint16_t adc_get(uint8_t channel);

#endif /* #ifndef __MEASURE_H__ */
