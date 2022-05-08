#ifndef __MEASURE_H__
#define __MEASURE_H__

#include "stm32f10x.h"

//板子资源初始化，mode为通道数量，选择2和1
extern void change_mode(uint8_t* mode);
extern void measure_init(void);

//正交 PWM 生成
extern void testPWM_init(int period);

//LED 控制函数
#define LED_ON (GPIO_SetBits(GPIOC,GPIO_Pin_13))
#define LED_OFF (GPIO_ResetBits(GPIOC,GPIO_Pin_13))

//键值获取
#define SW1 (!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15))
#define SW2 (!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4))
#define SW3 (!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6))
#define SW4 (!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8))
#define SW5 (!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3))
#define SW6 (!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5))
#define SW7 (!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
#define SW8 (!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))


//光电传感器与输入通道转换
#define LED1_OUT ((uint8_t)5)
#define LED2_OUT ((uint8_t)4)

//获取放大后的光电检测测量值，单位为毫伏
extern uint16_t ADC_get(uint8_t channel,uint8_t time);

#endif /* #ifndef __MEASURE_H__ */
