#include "stm8s.h"
#include "function.h"
#include "stm8s_tim3.h"

int fi=1;

struct _pid{
    float SetSpeed;            //�����趨ֵ
    float ActualSpeed;        //����ʵ��ֵ
    float err;                //����ƫ��ֵ
    float err_next;            //������һ��ƫ��ֵ
    float err_last;            //��������ǰ��ƫ��ֵ
    float Kp,Ki,Kd;            //������������֡�΢��ϵ��
}pid;

//���ܱ�����ʼ��
void Control_Init()
{
    GPIO_Init(GPIOF,GPIO_PIN_3,GPIO_MODE_OUT_OD_HIZ_SLOW);//PF3���ٿ�©�������̬
    GPIO_Init(GPIOF,GPIO_PIN_4,GPIO_MODE_OUT_OD_HIZ_SLOW);//PF4���ٿ�©�������̬
    GPIO_Init(GPIOF,GPIO_PIN_0,GPIO_MODE_OUT_OD_HIZ_SLOW);//PF0���ٿ�©�������̬
    GPIO_Init(GPIOG,GPIO_PIN_0,GPIO_MODE_OUT_OD_HIZ_SLOW);//PF0���ٿ�©�������̬
    GPIO_Init(GPIOG,GPIO_PIN_1,GPIO_MODE_OUT_OD_HIZ_SLOW);//PF0���ٿ�©�������̬
    
    //ȫ����λ
    LED1_H;
    LED2_H;
    LED3_H;
    Machine_Left_H;
    Machine_Right_H;
}

//�Ƚϵ�ǰˮλ����ֵ��ϵ
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
            LED2_L;//ˮλ����������ֵ��С��2����
            TIM3_SetCompare1(UPlevel*100+5);//ˮ��ֹͣת��
            pid.ActualSpeed=UPlevel;
        }
    }
    if(level<Downlevel)
    {
        if(fi)
        {
            fi=0;
            LED2_H;
            LED3_L;//ˮλ����������ֵ��С��3����
            TIM3_SetCompare1(15000);//ˮ��ȫ��ת��
            pid.ActualSpeed=Downlevel;
        }
    }
    if(level<=UPlevel&&level>=Downlevel)
    {
        LED2_H;//ˮλ����������ֵʱֹͣ����
        LED3_H;
        TIM3_SetCompare1(PID_realize((UPlevel+Downlevel)/2)*100);//����TIM3��׽�Ƚ�1�Ĵ�����ֵ��TIM3->CCR1��
        fi=1;
    }
}

//PID��ʼ��
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

//PIDʵ��
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

//��ʱ��3PWM��ʼ��
void TIM3_PWM_Init()
{
    TIM3_TimeBaseInit(TIM3_PRESCALER_16, UPlevel*100);  //��ʼ��TIM3ʱ����Ԫ  16��Ƶ   16λ�Զ�װ��ֵ  
    //PD2
    TIM3_OC1Init(TIM3_OCMODE_PWM1, TIM3_OUTPUTSTATE_ENABLE,150, TIM3_OCPOLARITY_HIGH);//PWM3ģʽ1  ��������Ƚ�  �����ȳ�ֵ  ����Ƚϼ��ԣ��ߵ�ƽ��  
    TIM3_OC1PreloadConfig(ENABLE);//����Ƚ�1Ԥװ��ʹ�ܣ�TIM3_CCMR1_OC1PE��   
    TIM3_Cmd(ENABLE);//���û��߹رն�ʱ��3
    TIM3_ARRPreloadConfig(ENABLE);//�Զ�Ԥװ������λ��TIM3_CR1_ARPE��
    TIM3_SetCompare1(UPlevel*100+5);     //����TIM3��׽�Ƚ�1�Ĵ�����ֵ��TIM3->CCR1��
}
