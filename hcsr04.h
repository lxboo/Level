#ifndef __HCSR04_H
#define __HCSR04_H
#include "stm8s.h"

#define Trig_H GPIO_WriteHigh(GPIOG,GPIO_PIN_5)//Trig控制端定义到PG5输出高电平
#define Trig_L GPIO_WriteLow(GPIOG,GPIO_PIN_5)//Trig控制端定义到PG5输出低电平
#define Echo GPIO_ReadInputPin(GPIOG,GPIO_PIN_6)

void HCSR04_Init();//初始化超声波HC-SR04
long int HCSR04_Start();//开始测量
void HCSR04_TIM2_Init();
void HCSR04_Comapre();//比较当前水位与阈值关系
void HCSR04_Start_Init();//检测空置时高度
#endif