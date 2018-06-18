#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "stm8s.h"

#define LED1_H GPIO_WriteHigh(GPIOF,GPIO_PIN_3);//PF3输出高电平
#define LED1_L GPIO_WriteLow(GPIOF,GPIO_PIN_3);//PF3输出低电平
#define LED2_H GPIO_WriteHigh(GPIOF,GPIO_PIN_4);//PF4输出高电平
#define LED2_L GPIO_WriteLow(GPIOF,GPIO_PIN_4);//PF4输出低电平
#define LED3_H GPIO_WriteHigh(GPIOF,GPIO_PIN_0);//PF5输出高电平
#define LED3_L GPIO_WriteLow(GPIOF,GPIO_PIN_0);//PF5输出低电平
#define Machine_Left_H GPIO_WriteHigh(GPIOG,GPIO_PIN_0);//PF6输出高电平
#define Machine_Left_L GPIO_WriteLow(GPIOG,GPIO_PIN_0);//PF6输出低电平
#define Machine_Right_H GPIO_WriteHigh(GPIOG,GPIO_PIN_1);//PF6输出高电平
#define Machine_Right_L GPIO_WriteLow(GPIOG,GPIO_PIN_1);//PF6输出低电平
void Control_Init();//LED指示灯初始化
void HCSR04_Comapre();//比较当前水位与阈值关系
void PID_init();//PID初始化
float PID_realize(float speed);//PID实现
void TIM3_PWM_Init();//定时器3PWM初始化
#endif