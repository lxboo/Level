#ifndef __UART1_H
#define __UART1_H
#include "stm8s.h"

void UART1_Configuration(void); //自定义串口处理函数
void UART1_Send_byte(u8 byte);  //发送一个8位的数据函数
void Show_Level(long int level1);//显示阈值
void Total_Show();//串口显示全部数据
void UART1_Interrupt_Handle();//串口1中断处理函数，即判断蓝牙接收到的数据并做相应的处理
#endif

