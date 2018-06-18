#include "stm8s.h"
#include "function.h"
#include "stm8s_tim3.h"

int fi=1;

struct _pid{
    float SetSpeed;            //定义设定值
    float ActualSpeed;        //定义实际值
    float err;                //定义偏差值
    float err_next;            //定义上一个偏差值
    float err_last;            //定义最上前的偏差值
    float Kp,Ki,Kd;            //定义比例、积分、微分系数
}pid;

//功能报警初始化
void Control_Init()
{
    GPIO_Init(GPIOF,GPIO_PIN_3,GPIO_MODE_OUT_OD_HIZ_SLOW);//PF3慢速开漏输出高阻态
    GPIO_Init(GPIOF,GPIO_PIN_4,GPIO_MODE_OUT_OD_HIZ_SLOW);//PF4慢速开漏输出高阻态
    GPIO_Init(GPIOF,GPIO_PIN_0,GPIO_MODE_OUT_OD_HIZ_SLOW);//PF0慢速开漏输出高阻态
    GPIO_Init(GPIOG,GPIO_PIN_0,GPIO_MODE_OUT_OD_HIZ_SLOW);//PF0慢速开漏输出高阻态
    GPIO_Init(GPIOG,GPIO_PIN_1,GPIO_MODE_OUT_OD_HIZ_SLOW);//PF0慢速开漏输出高阻态
    
    //全部置位
    LED1_H;
    LED2_H;
    LED3_H;
    Machine_Left_H;
    Machine_Right_H;
}

//比较当前水位与阈值关系
void HCSR04_Comapre()
{
    int j=500;
    extern long int level,UPlevel,Downlevel;
    if(level>UPlevel)
    {
        if(fi)
        {
            fi=0;
            LED3_H;
            LED2_L;//水位高于上限阈值，小灯2报警
            TIM3_SetCompare1(UPlevel*100+5);//水泵停止转动
            pid.ActualSpeed=UPlevel;
        }
    }
    if(level<Downlevel)
    {
        if(fi)
        {
            fi=0;
            LED2_H;
            LED3_L;//水位低于下限阈值，小灯3报警
            TIM3_SetCompare1(15000);//水泵全速转动
            pid.ActualSpeed=Downlevel;
        }
    }
    if(level<=UPlevel&&level>=Downlevel)
    {
        LED2_H;//水位低于上限阈值时停止报警
        LED3_H;
        TIM3_SetCompare1(PID_realize((UPlevel+Downlevel)/2)*100);//设置TIM3捕捉比较1寄存器的值（TIM3->CCR1）
        fi=1;
    }
}

//PID初始化
void PID_init(){
    pid.SetSpeed=0.0;
    pid.ActualSpeed=Downlevel;
    pid.err=0.0;
    pid.err_last=0.0;
    pid.err_next=0.0;
    pid.Kp=0.2;
    pid.Ki=0.015;
    pid.Kd=0.2;
}

//PID实现
float PID_realize(float speed){
    float incrementSpeed;
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;
    incrementSpeed=pid.Kp*(pid.err-pid.err_next)+pid.Ki*pid.err+pid.Kd*(pid.err-2*pid.err_next+pid.err_last);
    pid.ActualSpeed+=incrementSpeed;
    pid.err_last=pid.err_next;
    pid.err_next=pid.err;
    return pid.ActualSpeed;
}

//定时器3PWM初始化
void TIM3_PWM_Init()
{
    TIM3_TimeBaseInit(TIM3_PRESCALER_16, UPlevel*100);  //初始化TIM3时基单元  16分频   16位自动装载值  
    //PD2
    TIM3_OC1Init(TIM3_OCMODE_PWM1, TIM3_OUTPUTSTATE_ENABLE,150, TIM3_OCPOLARITY_HIGH);//PWM3模式1  启用输出比较  脉冲宽度初值  输出比较极性（高电平）  
    TIM3_OC1PreloadConfig(ENABLE);//输出比较1预装载使能（TIM3_CCMR1_OC1PE）   
    TIM3_Cmd(ENABLE);//启用或者关闭定时器3
    TIM3_ARRPreloadConfig(ENABLE);//自动预装载允许位（TIM3_CR1_ARPE）
    TIM3_SetCompare1(UPlevel*100+5);     //设置TIM3捕捉比较1寄存器的值（TIM3->CCR1）
}
