#include "pbdata.h"
#include "function.h"

unsigned char flag=0;

//us级延时
void delay_us(u16 nCount)
{
    nCount *=3; 
    while(--nCount);
}

//ms级延时
void delay_ms(u16 nCount)
{
    while(nCount--)
    {
        delay_us(1000);
    }
}

//外设初始化
void BSP_Configuration(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);  //配置内部高速振荡器（HSI）的分频器--1分频
    UART1_Configuration();//串口1初始化  
    HCSR04_Init();//初始化超声波HC-SR04
    Control_Init();
    LCD1602_Init();
    HCSR04_TIM2_Init();
    TIM3_PWM_Init();//定时器3PWM初始化
    PID_init();//PID初始化
    KEY_Init();//初始化按键
    UART3_Configuration();//串口3初始化    
    __enable_interrupt(); //中断使能
}

//未正式工作
void Informal_Work()
{
    unsigned char j;
    //未检测空置时高度，此标志位为0，工作指示灯一直闪烁
    while(flag==0)
    {
        j=50;
        LED1_L;//小灯亮
        while(j--)
        {
            delay_us(10);
            LEDS_Show_AHPU();//数码管显示字符AHPU
        }
        j=50;
        LED1_H;//小灯灭
        while(j--)
        {
            delay_us(10);
            LEDS_Show_AHPU();
        }
    }
}