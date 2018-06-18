#ifndef __KEY_H
#define __KEY_H
#include "stm8s.h"

void KEY_Init();//初始化按键
unsigned char EXTI_Interrupt_Judge();//判断哪个端口发生中断
void EXTI_Interrupt_Handle();//中断处理函数
void KEY_Change_Level_UP_H();//上调水位高位的阈值
void KEY_Change_Level_UP_L();//下调水位高位的阈值
void KEY_Change_Level_Down_H();//上调水位低位的阈值
void KEY_Change_Level_Down_L();//下调水位低位的阈值
#endif