#include "stm8s.h"
#include "lcd1602.h"

unsigned char LEDS_Buf[]={0,0,0,0};
unsigned char LEDS[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char LEDSP[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};

//LED数码管初始化
void LCD1602_Init()
{
    GPIO_Init(GPIOC, GPIO_PIN_1, GPIO_MODE_OUT_OD_HIZ_SLOW);//PC1为慢速开漏输出高阻态
    GPIO_Init(GPIOC, GPIO_PIN_2, GPIO_MODE_OUT_OD_HIZ_SLOW);//PC2为慢速开漏输出高阻态
    GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_OD_HIZ_SLOW);//PC3为慢速开漏输出高阻态
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_SLOW);//PC4为慢速开漏输出高阻态
    GPIO_Init(GPIOB, GPIO_PIN_ALL, GPIO_MODE_OUT_OD_HIZ_SLOW);//PB为慢速开漏输出高阻态
}

//数码管显示
void LEDS_Show(long int LEDSlevel)
{
    extern long int level;
    LEDS_Buf[0]=LEDSlevel/1000%10;
    LEDS_Buf[1]=LEDSlevel/100%10;
    LEDS_Buf[2]=LEDSlevel/10%10;
    LEDS_Buf[3]=LEDSlevel%10;
      
    GPIO_WriteLow(GPIOC, GPIO_PIN_1);
    GPIO_Write(GPIOB,LEDSP[LEDS_Buf[0]]);
    delay_ms(1);
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
    
    GPIO_WriteLow(GPIOC, GPIO_PIN_2);
    GPIO_Write(GPIOB,LEDS[LEDS_Buf[1]]);
    delay_ms(1);
    GPIO_WriteHigh(GPIOC, GPIO_PIN_2);
    
    GPIO_WriteLow(GPIOC, GPIO_PIN_3);
    GPIO_Write(GPIOB,LEDS[LEDS_Buf[2]]);
    delay_ms(1); 
    GPIO_WriteHigh(GPIOC, GPIO_PIN_3);
    
    GPIO_WriteLow(GPIOC, GPIO_PIN_4);
    GPIO_Write(GPIOB,LEDS[LEDS_Buf[3]]);
    delay_ms(1);
    GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
}

//数码管显示字符AHPU
void LEDS_Show_AHPU()
{ 
    GPIO_WriteLow(GPIOC, GPIO_PIN_1);
    GPIO_Write(GPIOB,0x77);
    delay_ms(1);
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
    
    GPIO_WriteLow(GPIOC, GPIO_PIN_2);
    GPIO_Write(GPIOB,0x76);
    delay_ms(1);
    GPIO_WriteHigh(GPIOC, GPIO_PIN_2);
    
    GPIO_WriteLow(GPIOC, GPIO_PIN_3);
    GPIO_Write(GPIOB,0x73);
    delay_ms(1); 
    GPIO_WriteHigh(GPIOC, GPIO_PIN_3);
    
    GPIO_WriteLow(GPIOC, GPIO_PIN_4);
    GPIO_Write(GPIOB,0x3e);
    delay_ms(1);
    GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
}

