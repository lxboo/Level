#include "stm8s.h"
#include "key.h"
#include "hcsr04.h"
#include "function.h"
#include "stm8s_exti.h"

extern long int UPlevel,Downlevel;
extern unsigned char Level_Start[12];
extern unsigned char Level_Cur[14];
extern unsigned char Level_UP[9];
extern unsigned char Level_Dowe[11];

//��ʼ������
void KEY_Init()
{
    GPIO_Init(GPIOE,GPIO_PIN_1,GPIO_MODE_IN_PU_IT);//PE1�����������ⲿ�ж�
    GPIO_Init(GPIOE,GPIO_PIN_2,GPIO_MODE_IN_PU_IT);//PE2�����������ⲿ�ж�
    GPIO_Init(GPIOE,GPIO_PIN_3,GPIO_MODE_IN_PU_IT);//PE3�����������ⲿ�ж�
    GPIO_Init(GPIOE,GPIO_PIN_4,GPIO_MODE_IN_PU_IT);//PE4�����������ⲿ�ж�
    GPIO_Init(GPIOE,GPIO_PIN_5,GPIO_MODE_IN_PU_IT);//PE5�����������ⲿ�ж�
    GPIO_Init(GPIOE,GPIO_PIN_6,GPIO_MODE_IN_PU_IT);//PE6�����������ⲿ�ж�
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE,EXTI_SENSITIVITY_FALL_ONLY);//PE���½��ش����ж�
}

//�ж��ĸ��˿ڷ����ж�
unsigned char EXTI_Interrupt_Judge()
{
    unsigned char KEY_Val=0;
    if(GPIO_ReadInputPin(GPIOE,GPIO_PIN_1)==0)
        KEY_Val=1;
    else if(GPIO_ReadInputPin(GPIOE,GPIO_PIN_2)==0)
        KEY_Val=2;
    else if(GPIO_ReadInputPin(GPIOE,GPIO_PIN_3)==0)
        KEY_Val=3;
    else if(GPIO_ReadInputPin(GPIOE,GPIO_PIN_4)==0)
        KEY_Val=4;
    else if(GPIO_ReadInputPin(GPIOE,GPIO_PIN_5)==0)
        KEY_Val=5;
    else if(GPIO_ReadInputPin(GPIOE,GPIO_PIN_6)==0)
        KEY_Val=6;
    return KEY_Val;
}

//�����жϴ�����
void EXTI_Interrupt_Handle()
{
    unsigned char KEY_Dat;
    KEY_Dat=EXTI_Interrupt_Judge();//��ȡ�����жϵ�ֵ
    switch(KEY_Dat)
    {
        case 1:
            HCSR04_Start_Init();//������ʱ�߶�
            break;
        case 2:
            KEY_Change_Level_UP_H();//�ϵ�ˮλ��λ����ֵ
            break;
        case 3:
            KEY_Change_Level_UP_L();//�µ�ˮλ��λ����ֵ
            break;
        case 4:
            KEY_Change_Level_Down_H();//�ϵ�ˮλ��λ����ֵ
            break;
        case 5:
            KEY_Change_Level_Down_L();//�µ�ˮλ��λ����ֵ
            break;
        case 6:
            Total_Show();//��ʾ��ǰˮλ�߶ȣ�����ʱ�߶ȣ���������ֵ
            break;
    }
}

//�ϵ�ˮλ������ֵ
void KEY_Change_Level_UP_H()
{
  unsigned char i;
  int j=500;
  UPlevel+=10;
  for(i=0;i<9;i++)   //׼������
  {    
    UART1_Send_byte(Level_UP[i]);
    UART3_Send_byte(Level_UP[i]);   //��������
  }
  Show_Level(UPlevel);//��ʾ������ֵ
  while(j--)
      {
        delay_us(10);
        LEDS_Show(UPlevel);
      }
}
//�µ�ˮλ������ֵ 
void KEY_Change_Level_UP_L()
{
  unsigned char i;
  int j=500;
  UPlevel-=10;
  for(i=0;i<9;i++)   //׼������
  {    
    UART1_Send_byte(Level_UP[i]);
    UART3_Send_byte(Level_UP[i]);   //��������
  }
  Show_Level(UPlevel);//��ʾ������ֵ
  while(j--)
      {
        delay_us(10);
        LEDS_Show(UPlevel);
      }
}

//�ϵ�ˮλ������ֵ 
void KEY_Change_Level_Down_H()
{
  unsigned char i;
  int j=500;
  Downlevel+=10;
  for(i=0;i<11;i++)   //׼������
  {    
    UART1_Send_byte(Level_Dowe[i]);
    UART3_Send_byte(Level_Dowe[i]);   //��������
  }
  Show_Level(Downlevel);//��ʾ������ֵ
  while(j--)
      {
        delay_us(10);
        LEDS_Show(Downlevel);
      }  
}
  
//�µ�ˮλ������ֵ
void KEY_Change_Level_Down_L()
{
  unsigned char i;
  int j=500;
  Downlevel-=10;
  for(i=0;i<11;i++)   //׼������
  {    
    UART1_Send_byte(Level_Dowe[i]);
    UART3_Send_byte(Level_Dowe[i]);   //��������
  }
  Show_Level(Downlevel);//��ʾ������ֵ
  while(j--)
      {
        delay_us(10);
        LEDS_Show(Downlevel);
      } 
}
  
    
