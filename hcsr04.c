#include "pbdata.h"
#include "hcsr04.h"
#include "stm8s.h"
#include "stm8s_tim2.h"
#include "function.h"

extern unsigned char Level_Start[12];
extern unsigned char Level_Cur[14];
extern unsigned char Level_UP[9];
extern unsigned char Level_Dowe[11];

//初始化超声波HC-SR04
void HCSR04_Init()
{
    GPIO_Init(GPIOG,GPIO_PIN_5,GPIO_MODE_OUT_PP_LOW_FAST);//PG5慢速开漏输出高阻态
    GPIO_Init(GPIOG,GPIO_PIN_6,GPIO_MODE_IN_PU_NO_IT);//PG6输入上拉
}

//开始测量
long int HCSR04_Start()
{
    long int timeus,timeus1,timeus2;
    extern long int time,UPlevel;
    //给20us的高电平信号
    Trig_H;
    delay_us(20);
    Trig_L;
    while(!Echo);//等待接收端变为高电平
    timeus1=TIM2_GetCounter();//再次读取计数器值并赋给timeus
    //等待接收端变为低电平
    while(Echo)
    {
        timeus2=TIM2_GetCounter();//再次读取计数器值并赋给timeus
        if(timeus2>=0&&timeus2<(2000*UPlevel/340))
        return time;
    }
    timeus=timeus2-timeus1;
    return timeus;
}

//定时器2初始化并且开始计数
void HCSR04_TIM2_Init()
{
    TIM2_DeInit();
    TIM2_TimeBaseInit(0x04,0xffff);//预分频器值设为4（即预分频系数为16），自动重装为0xffff
    TIM2_Cmd(ENABLE);//使能计数
    TIM2_SetCompare1(0xffff);//设置通道1捕获
}

//检测空置时高度
void HCSR04_Start_Init()
{
    extern long int timeinit,levelinit;
    long int timeinitbuf=0;
    unsigned char i;
    int j=1000;
    extern unsigned char flag;
    LED1_L;//正常工作，指示灯常亮
    timeinit=HCSR04_Start();//累加测量10次HC-SR04的脉冲宽度
    levelinit=timeinit*340/1000/2;
    for(i=0;i<12;i++)   //准备数据
    {    
        UART1_Send_byte(Level_Start[i]);
        UART3_Send_byte(Level_Start[i]);   //发送数据
    }
    Show_Level(levelinit);//显示空置时高度
    while(j--)
    {
        delay_us(10);
        LEDS_Show(levelinit);
    }
    flag=1;//只有运行完检测空置时的函数，此标志位置1，才能开始检测实时水位，否则不工作
}