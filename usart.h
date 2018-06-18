#ifndef __USART_H
#define __USART_H
#include "stm8s.h"
#include "stm8s_tim2.h"
#include "stm8s_exti.h"

void UART3_Configuration(void);//串口3配置
void UART3_Send_byte(u8 byte);//自定义串口3发送数据
void UART3_Interrupt_Handle();//此函数在中断里面调用，设置水位阈值,串口3中断处理函数，即判断蓝牙接收到的数据并做相应的处理
#endif

