#include "pbdata.h"
#include "hcsr04.h"
#include "function.h"
#include "uart1.h"
#include "stm8s_uart1.h"

long int timeinit,levelinit=0,time,level=0;//分别定义空置时脉冲宽度；空置时高度，做差后的水位高度脉冲宽度；当前水位
long int UPlevel=250,Downlevel=150;//定义水位上限阈值；水位下限阈值；并附上初值
   
unsigned char Level_Start[12]={'S','t','a','r','t',' ','l','e','v','e','l',':'};//定义串口显示字符Current
unsigned char Level_Cur[14]={'C','u','r','r','e','n','t',' ','l','e','v','e','l',':'};//定义串口显示字符Current level
unsigned char Level_UP[9]={'U','P',' ','l','e','v','e','l',':'};//定义串口显示字符UP level
unsigned char Level_Dowe[11]={'D','o','w','n',' ','l','e','v','e','l',':'};//定义串口显示字符Down level

//串口1初始化
void UART1_Configuration(void)
{  
    UART1_DeInit();
    //波特率，字节数，1个停止位，无奇偶效验位，   非同步模式，        允许接受和发送
    UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1,UART1_PARITY_NO , UART1_SYNCMODE_CLOCK_DISABLE , UART1_MODE_TXRX_ENABLE);
    UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE  );
    UART1_Cmd(ENABLE );
}

//发送一个8位的数据函数
void UART1_Send_byte(u8 byte)
{
    UART1_SendData8(byte);
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);//发送数据为空
}   

//串口发送显示
void UART1_Show(void)
{
    u8 i;
    long int levelbuf;
    
    unsigned char  LCD1602_Dig[]={'0','1','2','3','4','5','6','7','8','9','.'};
    unsigned char LCD1602_Buf[]={0,0,0,0}; 
    time=HCSR04_Start();//测量HC-SR04的脉冲宽度
    levelbuf=time*340/1000/2;//将时间转换为距离
    level=levelinit-levelbuf;//空置高度减去每次测量距离即为液位高度值
    LCD1602_Buf[0]=level/1000%10;//m单位值
    LCD1602_Buf[1]=level/100%10;//dm单位值
    LCD1602_Buf[2]=level/10%10;//cm单位值
    LCD1602_Buf[3]=level%10;//mm单位值
    //串口说明字符显示
    for(i=0;i<14;i++)   
    {    
        UART1_Send_byte(Level_Cur[i]);
        UART3_Send_byte(Level_Cur[i]);   
    }
    //串口液位值显示
    for(i=0;i<=3;i++)   
    {    
        UART1_Send_byte(LCD1602_Dig[LCD1602_Buf[i]]);
        if(i==0)
            UART1_Send_byte(LCD1602_Dig[10]);
        UART3_Send_byte(LCD1602_Dig[LCD1602_Buf[i]]);   
        if(i==0)
            UART3_Send_byte(LCD1602_Dig[10]);
    }
    UART1_Send_byte('m');//串口显示m
    UART3_Send_byte('m');
    UART1_Send_byte('\r');//换行
    UART1_Send_byte('\n');//回车
    UART3_Send_byte('\r');
    UART3_Send_byte('\n');
    
}

//显示阈值
void Show_Level(long int level1)
{
    unsigned char i;
    unsigned char  LCD1602_Dig[]={'0','1','2','3','4','5','6','7','8','9','.'};
    unsigned char LCD1602_Buf[]={0,0,0,0}; 
    level=level1;
    LCD1602_Buf[0]=level/1000%10;
    LCD1602_Buf[1]=level/100%10;
    LCD1602_Buf[2]=level/10%10;
    LCD1602_Buf[3]=level%10;
    for(i=0;i<=3;i++)
    {        
        UART1_Send_byte(LCD1602_Dig[LCD1602_Buf[i]]); 
        if(i==0)
            UART1_Send_byte(LCD1602_Dig[10]);
        UART3_Send_byte(LCD1602_Dig[LCD1602_Buf[i]]); 
        if(i==0)
            UART3_Send_byte(LCD1602_Dig[10]);
    }
    UART1_Send_byte('m');
    UART3_Send_byte('m');
    UART1_Send_byte('\r');
    UART1_Send_byte('\n');
    UART3_Send_byte('\r');
    UART3_Send_byte('\n');
    
}

//串口显示全部数据
void Total_Show()
{
    unsigned char i;
    for(i=0;i<14;i++)
    {    
        UART1_Send_byte(Level_Cur[i]);
        UART3_Send_byte(Level_Cur[i]); 
     }
    Show_Level(level);//串口显示当前液位
    delay_ms(50);
    for(i=0;i<9;i++)
    {    
        UART1_Send_byte(Level_UP[i]);
        UART3_Send_byte(Level_UP[i]);
    }
    Show_Level(UPlevel);//串口显示上限阈值
    delay_ms(50);
    for(i=0;i<11;i++)
    {    
        UART1_Send_byte(Level_Dowe[i]);
        UART3_Send_byte(Level_Dowe[i]);
    }
    Show_Level(Downlevel);//串口显示下限阈值
    delay_ms(50);
    for(i=0;i<12;i++)
    {    
        UART1_Send_byte(Level_Start[i]);
        UART3_Send_byte(Level_Start[i]);
    }
    Show_Level(levelinit);//串口显示空置高度
    delay_ms(50);
}

//串口1中断处理函数，即判断蓝牙接收到的数据并做相应的处理
void UART1_Interrupt_Handle()
{
    unsigned char UART1_Dat;
    UART1_Dat=UART1_ReceiveData8();//读取按键中断的值
    switch(UART1_Dat)
    {
        case '1':
            HCSR04_Start_Init();//检测空置时高度
            break;
        case '2':
            KEY_Change_Level_UP_H();//上调水位高位的阈值
            break;
        case '3':
            KEY_Change_Level_UP_L();//下调水位高位的阈值
            break;
        case '4':
            KEY_Change_Level_Down_H();//上调水位低位的阈值
            break;
        case '5':
            KEY_Change_Level_Down_L();//下调水位低位的阈值
            break;
        case '6':
            Total_Show();//显示当前水位高度，空置时高度，上下限阈值
            break;
    }
}

