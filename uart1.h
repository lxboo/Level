#ifndef __UART1_H
#define __UART1_H
#include "stm8s.h"

void UART1_Configuration(void); //�Զ��崮�ڴ�����
void UART1_Send_byte(u8 byte);  //����һ��8λ�����ݺ���
void Show_Level(long int level1);//��ʾ��ֵ
void Total_Show();//������ʾȫ������
void UART1_Interrupt_Handle();//����1�жϴ����������ж��������յ������ݲ�����Ӧ�Ĵ���
#endif

