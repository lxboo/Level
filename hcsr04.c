#include "pbdata.h"
#include "hcsr04.h"
#include "stm8s.h"
#include "stm8s_tim2.h"
#include "function.h"

extern unsigned char Level_Start[12];
extern unsigned char Level_Cur[14];
extern unsigned char Level_UP[9];
extern unsigned char Level_Dowe[11];

//��ʼ��������HC-SR04
void HCSR04_Init()
{
    GPIO_Init(GPIOG,GPIO_PIN_5,GPIO_MODE_OUT_PP_LOW_FAST);//PG5���ٿ�©�������̬
    GPIO_Init(GPIOG,GPIO_PIN_6,GPIO_MODE_IN_PU_NO_IT);//PG6��������
}

//��ʼ����
long int HCSR04_Start()
{
    long int timeus,timeus1,timeus2;
    extern long int time,UPlevel;
    //��20us�ĸߵ�ƽ�ź�
    Trig_H;
    delay_us(20);
    Trig_L;
    while(!Echo);//�ȴ����ն˱�Ϊ�ߵ�ƽ
    timeus1=TIM2_GetCounter();//�ٴζ�ȡ������ֵ������timeus
    //�ȴ����ն˱�Ϊ�͵�ƽ
    while(Echo)
    {
        timeus2=TIM2_GetCounter();//�ٴζ�ȡ������ֵ������timeus
        if(timeus2>=0&&timeus2<(2000*UPlevel/340))
        return time;
    }
    timeus=timeus2-timeus1;
    return timeus;
}

//��ʱ��2��ʼ�����ҿ�ʼ����
void HCSR04_TIM2_Init()
{
    TIM2_DeInit();
    TIM2_TimeBaseInit(0x04,0xffff);//Ԥ��Ƶ��ֵ��Ϊ4����Ԥ��Ƶϵ��Ϊ16�����Զ���װΪ0xffff
    TIM2_Cmd(ENABLE);//ʹ�ܼ���
    TIM2_SetCompare1(0xffff);//����ͨ��1����
}

//������ʱ�߶�
void HCSR04_Start_Init()
{
    extern long int timeinit,levelinit;
    long int timeinitbuf=0;
    unsigned char i;
    int j=1000;
    extern unsigned char flag;
    LED1_L;//����������ָʾ�Ƴ���
    timeinit=HCSR04_Start();//�ۼӲ���10��HC-SR04��������
    levelinit=timeinit*340/1000/2;
    for(i=0;i<12;i++)   //׼������
    {    
        UART1_Send_byte(Level_Start[i]);
        UART3_Send_byte(Level_Start[i]);   //��������
    }
    Show_Level(levelinit);//��ʾ����ʱ�߶�
    while(j--)
    {
        delay_us(10);
        LEDS_Show(levelinit);
    }
    flag=1;//ֻ�������������ʱ�ĺ������˱�־λ��1�����ܿ�ʼ���ʵʱˮλ�����򲻹���
}