#include "pbdata.h"
#include "function.h"
#include "hcsr04.h"
#include "stm8s.h"
#include "lcd1602.h"

extern long int level;//�����ⲿҺλֵ

int main(void)
{
    unsigned char i=200;
    
    BSP_Configuration();//��ʼ��Ӳ��
    while(1)
    {
      
        Informal_Work();//δ��ʽ����
        LED1_L;//����������ָʾ�Ƴ���
        UART1_Show(level);//�򴮿ڷ������ݲ���ʾ
        while(i--)
        {
          delay_us(10);
          LEDS_Show(level);//�������ʾ
        }
        i=200;
        HCSR04_Comapre();//Һλ�Ƚ�
    }
}
