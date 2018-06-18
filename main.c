#include "pbdata.h"
#include "function.h"
#include "hcsr04.h"
#include "stm8s.h"
#include "lcd1602.h"

extern long int level;//定义外部液位值

int main(void)
{
    unsigned char i=200;
    
    BSP_Configuration();//初始化硬件
    while(1)
    {
      
        Informal_Work();//未正式工作
        LED1_L;//正常工作，指示灯常亮
        UART1_Show(level);//向串口发送数据并显示
        while(i--)
        {
          delay_us(10);
          LEDS_Show(level);//数码管显示
        }
        i=200;
        HCSR04_Comapre();//液位比较
    }
}
