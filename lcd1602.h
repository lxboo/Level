#ifndef __LCD1602_H
#define __LCD1602_H
#include "stm8s.h"

void LCD1602_Init();//LED����ܳ�ʼ��
void LEDS_Show(long int LEDSlevel);//�������ʾ
void LEDS_Show_AHPU();//�������ʾ�ַ�AHPU
#endif