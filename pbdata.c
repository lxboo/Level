#include "pbdata.h"
#include "function.h"

unsigned char flag=0;

//us����ʱ
void delay_us(u16 nCount)
{
    nCount *=3; 
    while(--nCount);
}

//ms����ʱ
void delay_ms(u16 nCount)
{
    while(nCount--)
    {
        delay_us(1000);
    }
}

//�����ʼ��
void BSP_Configuration(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);  //�����ڲ�����������HSI���ķ�Ƶ��--1��Ƶ
    UART1_Configuration();//����1��ʼ��  
    HCSR04_Init();//��ʼ��������HC-SR04
    Control_Init();
    LCD1602_Init();
    HCSR04_TIM2_Init();
    TIM3_PWM_Init();//��ʱ��3PWM��ʼ��
    PID_init();//PID��ʼ��
    KEY_Init();//��ʼ������
    UART3_Configuration();//����3��ʼ��    
    __enable_interrupt(); //�ж�ʹ��
}

//δ��ʽ����
void Informal_Work()
{
    unsigned char j;
    //δ������ʱ�߶ȣ��˱�־λΪ0������ָʾ��һֱ��˸
    while(flag==0)
    {
        j=50;
        LED1_L;//С����
        while(j--)
        {
            delay_us(10);
            LEDS_Show_AHPU();//�������ʾ�ַ�AHPU
        }
        j=50;
        LED1_H;//С����
        while(j--)
        {
            delay_us(10);
            LEDS_Show_AHPU();
        }
    }
}