#ifndef __KEY_H
#define __KEY_H
#include "stm8s.h"

void KEY_Init();//��ʼ������
unsigned char EXTI_Interrupt_Judge();//�ж��ĸ��˿ڷ����ж�
void EXTI_Interrupt_Handle();//�жϴ�����
void KEY_Change_Level_UP_H();//�ϵ�ˮλ��λ����ֵ
void KEY_Change_Level_UP_L();//�µ�ˮλ��λ����ֵ
void KEY_Change_Level_Down_H();//�ϵ�ˮλ��λ����ֵ
void KEY_Change_Level_Down_L();//�µ�ˮλ��λ����ֵ
#endif