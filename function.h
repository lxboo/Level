#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "stm8s.h"

#define LED1_H GPIO_WriteHigh(GPIOF,GPIO_PIN_3);//PF3����ߵ�ƽ
#define LED1_L GPIO_WriteLow(GPIOF,GPIO_PIN_3);//PF3����͵�ƽ
#define LED2_H GPIO_WriteHigh(GPIOF,GPIO_PIN_4);//PF4����ߵ�ƽ
#define LED2_L GPIO_WriteLow(GPIOF,GPIO_PIN_4);//PF4����͵�ƽ
#define LED3_H GPIO_WriteHigh(GPIOF,GPIO_PIN_0);//PF5����ߵ�ƽ
#define LED3_L GPIO_WriteLow(GPIOF,GPIO_PIN_0);//PF5����͵�ƽ
#define Machine_Left_H GPIO_WriteHigh(GPIOG,GPIO_PIN_0);//PF6����ߵ�ƽ
#define Machine_Left_L GPIO_WriteLow(GPIOG,GPIO_PIN_0);//PF6����͵�ƽ
#define Machine_Right_H GPIO_WriteHigh(GPIOG,GPIO_PIN_1);//PF6����ߵ�ƽ
#define Machine_Right_L GPIO_WriteLow(GPIOG,GPIO_PIN_1);//PF6����͵�ƽ
void Control_Init();//LEDָʾ�Ƴ�ʼ��
void HCSR04_Comapre();//�Ƚϵ�ǰˮλ����ֵ��ϵ
void PID_init();//PID��ʼ��
float PID_realize(float speed);//PIDʵ��
void TIM3_PWM_Init();//��ʱ��3PWM��ʼ��
#endif