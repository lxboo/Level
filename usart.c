#include "pbdata.h"   //声明

void UART3_Configuration(void)//串口3通讯配置
{
    UART3_DeInit();
    UART3_Init((u32)9600, UART3_WORDLENGTH_8D, UART3_STOPBITS_1, \
    UART3_PARITY_NO ,  UART3_MODE_TXRX_ENABLE);//波特率，字节数，1个停止位，无奇偶效验位，允许接受和发送
    
    UART3_ITConfig(UART3_IT_RXNE_OR,ENABLE  );
    UART3_Cmd(ENABLE );		
}

//串口3发送数据
void UART3_Send_byte(u8 byte)  
{
    UART3_SendData8((unsigned char)byte); //发送一个8位的数据
    while (UART3_GetFlagStatus(UART3_FLAG_TXE) == RESET);//获得指定标志位置位状态   发送数据寄存器空标志
}

//串口3中断处理函数，即判断蓝牙接收到的数据并做相应的处理
void UART3_Interrupt_Handle()
{
    unsigned char UART3_Dat;
    UART3_Dat=UART3_ReceiveData8();//读取按键中断的值
    switch(UART3_Dat)
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