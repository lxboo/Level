#ifndef __HCSR04_H
#define __HCSR04_H
#include "stm8s.h"

#define Trig_H GPIO_WriteHigh(GPIOG,GPIO_PIN_5)//Trig���ƶ˶��嵽PG5����ߵ�ƽ
#define Trig_L GPIO_WriteLow(GPIOG,GPIO_PIN_5)//Trig���ƶ˶��嵽PG5����͵�ƽ
#define Echo GPIO_ReadInputPin(GPIOG,GPIO_PIN_6)

void HCSR04_Init();//��ʼ��������HC-SR04
long int HCSR04_Start();//��ʼ����
void HCSR04_TIM2_Init();
void HCSR04_Comapre();//�Ƚϵ�ǰˮλ����ֵ��ϵ
void HCSR04_Start_Init();//������ʱ�߶�
#endif