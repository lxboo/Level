#ifndef __USART_H
#define __USART_H
#include "stm8s.h"
#include "stm8s_tim2.h"
#include "stm8s_exti.h"

void UART3_Configuration(void);//����3����
void UART3_Send_byte(u8 byte);//�Զ��崮��3��������
void UART3_Interrupt_Handle();//�˺������ж�������ã�����ˮλ��ֵ,����3�жϴ����������ж��������յ������ݲ�����Ӧ�Ĵ���
#endif

