#ifndef __LCD1602_H
#define __LCD1602_H
#include "stm8s.h"

void LCD1602_Init();//LED数码管初始化
void LEDS_Show(long int LEDSlevel);//数码管显示
void LEDS_Show_AHPU();//数码管显示字符AHPU
#endif