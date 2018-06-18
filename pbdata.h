#ifndef __PBDATA_H 
#define __PBDATA_H
#include "stm8s.h"
#include "usart.h" 

void delay_us(u16 nCount);//us级延时
void delay_ms(u16 nCount);//ms级延时
void BSP_Configuration(void);//外设初始化
void Informal_Work();//未正式工作
#endif

