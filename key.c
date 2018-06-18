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

//初始化按键
void KEY_Init()
{
    GPIO_Init(GPIOE,GPIO_PIN_1,GPIO_MODE_IN_PU_IT);//PE1输入上拉，外部中断
    GPIO_Init(GPIOE,GPIO_PIN_2,GPIO_MODE_IN_PU_IT);//PE2输入上拉，外部中断
    GPIO_Init(GPIOE,GPIO_PIN_3,GPIO_MODE_IN_PU_IT);//PE3输入上拉，外部中断
    GPIO_Init(GPIOE,GPIO_PIN_4,GPIO_MODE_IN_PU_IT);//PE4输入上拉，外部中断
    GPIO_Init(GPIOE,GPIO_PIN_5,GPIO_MODE_IN_PU_IT);//PE5输入上拉，外部中断
    GPIO_Init(GPIOE,GPIO_PIN_6,GPIO_MODE_IN_PU_IT);//PE6输入上拉，外部中断
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE,EXTI_SENSITIVITY_FALL_ONLY);//PE口下降沿触发中断
}

//判断哪个端口发生中断
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

//按键中断处理函数
void EXTI_Interrupt_Handle()
{
    unsigned char KEY_Dat;
    KEY_Dat=EXTI_Interrupt_Judge();//读取按键中断的值
    switch(KEY_Dat)
    {
        case 1:
            HCSR04_Start_Init();//检测空置时高度
            break;
        case 2:
            KEY_Change_Level_UP_H();//上调水位高位的阈值
            break;
        case 3:
            KEY_Change_Level_UP_L();//下调水位高位的阈值
            break;
        case 4:
            KEY_Change_Level_Down_H();//上调水位低位的阈值
            break;
        case 5:
            KEY_Change_Level_Down_L();//下调水位低位的阈值
            break;
        case 6:
            Total_Show();//显示当前水位高度，空置时高度，上下限阈值
            break;
    }
}

//上调水位上限阈值
void KEY_Change_Level_UP_H()
{
  unsigned char i;
  int j=500;
  UPlevel+=10;
  for(i=0;i<9;i++)   //准备数据
  {    
    UART1_Send_byte(Level_UP[i]);
    UART3_Send_byte(Level_UP[i]);   //发送数据
  }
  Show_Level(UPlevel);//显示上限阈值
  while(j--)
      {
        delay_us(10);
        LEDS_Show(UPlevel);
      }
}
//下调水位上限阈值 
void KEY_Change_Level_UP_L()
{
  unsigned char i;
  int j=500;
  UPlevel-=10;
  for(i=0;i<9;i++)   //准备数据
  {    
    UART1_Send_byte(Level_UP[i]);
    UART3_Send_byte(Level_UP[i]);   //发送数据
  }
  Show_Level(UPlevel);//显示上限阈值
  while(j--)
      {
        delay_us(10);
        LEDS_Show(UPlevel);
      }
}

//上调水位下限阈值 
void KEY_Change_Level_Down_H()
{
  unsigned char i;
  int j=500;
  Downlevel+=10;
  for(i=0;i<11;i++)   //准备数据
  {    
    UART1_Send_byte(Level_Dowe[i]);
    UART3_Send_byte(Level_Dowe[i]);   //发送数据
  }
  Show_Level(Downlevel);//显示上限阈值
  while(j--)
      {
        delay_us(10);
        LEDS_Show(Downlevel);
      }  
}
  
//下调水位下限阈值
void KEY_Change_Level_Down_L()
{
  unsigned char i;
  int j=500;
  Downlevel-=10;
  for(i=0;i<11;i++)   //准备数据
  {    
    UART1_Send_byte(Level_Dowe[i]);
    UART3_Send_byte(Level_Dowe[i]);   //发送数据
  }
  Show_Level(Downlevel);//显示上限阈值
  while(j--)
      {
        delay_us(10);
        LEDS_Show(Downlevel);
      } 
}
  
    
