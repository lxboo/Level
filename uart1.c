#include "pbdata.h"
#include "hcsr04.h"
#include "function.h"
#include "uart1.h"
#include "stm8s_uart1.h"

long int timeinit,levelinit=0,time,level=0;//�ֱ������ʱ�����ȣ�����ʱ�߶ȣ�������ˮλ�߶������ȣ���ǰˮλ
long int UPlevel=250,Downlevel=150;//����ˮλ������ֵ��ˮλ������ֵ�������ϳ�ֵ
   
unsigned char Level_Start[12]={'S','t','a','r','t',' ','l','e','v','e','l',':'};//���崮����ʾ�ַ�Current
unsigned char Level_Cur[14]={'C','u','r','r','e','n','t',' ','l','e','v','e','l',':'};//���崮����ʾ�ַ�Current level
unsigned char Level_UP[9]={'U','P',' ','l','e','v','e','l',':'};//���崮����ʾ�ַ�UP level
unsigned char Level_Dowe[11]={'D','o','w','n',' ','l','e','v','e','l',':'};//���崮����ʾ�ַ�Down level

//����1��ʼ��
void UART1_Configuration(void)
{  
    UART1_DeInit();
    //�����ʣ��ֽ�����1��ֹͣλ������żЧ��λ��   ��ͬ��ģʽ��        ������ܺͷ���
    UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1,UART1_PARITY_NO , UART1_SYNCMODE_CLOCK_DISABLE , UART1_MODE_TXRX_ENABLE);
    UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE  );
    UART1_Cmd(ENABLE );
}

//����һ��8λ�����ݺ���
void UART1_Send_byte(u8 byte)
{
    UART1_SendData8(byte);
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);//��������Ϊ��
}   

//���ڷ�����ʾ
void UART1_Show(void)
{
    u8 i;
    long int levelbuf;
    
    unsigned char  LCD1602_Dig[]={'0','1','2','3','4','5','6','7','8','9','.'};
    unsigned char LCD1602_Buf[]={0,0,0,0}; 
    time=HCSR04_Start();//����HC-SR04��������
    levelbuf=time*340/1000/2;//��ʱ��ת��Ϊ����
    level=levelinit-levelbuf;//���ø߶ȼ�ȥÿ�β������뼴ΪҺλ�߶�ֵ
    LCD1602_Buf[0]=level/1000%10;//m��λֵ
    LCD1602_Buf[1]=level/100%10;//dm��λֵ
    LCD1602_Buf[2]=level/10%10;//cm��λֵ
    LCD1602_Buf[3]=level%10;//mm��λֵ
    //����˵���ַ���ʾ
    for(i=0;i<14;i++)   
    {    
        UART1_Send_byte(Level_Cur[i]);
        UART3_Send_byte(Level_Cur[i]);   
    }
    //����Һλֵ��ʾ
    for(i=0;i<=3;i++)   
    {    
        UART1_Send_byte(LCD1602_Dig[LCD1602_Buf[i]]);
        if(i==0)
            UART1_Send_byte(LCD1602_Dig[10]);
        UART3_Send_byte(LCD1602_Dig[LCD1602_Buf[i]]);   
        if(i==0)
            UART3_Send_byte(LCD1602_Dig[10]);
    }
    UART1_Send_byte('m');//������ʾm
    UART3_Send_byte('m');
    UART1_Send_byte('\r');//����
    UART1_Send_byte('\n');//�س�
    UART3_Send_byte('\r');
    UART3_Send_byte('\n');
    
}

//��ʾ��ֵ
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

//������ʾȫ������
void Total_Show()
{
    unsigned char i;
    for(i=0;i<14;i++)
    {    
        UART1_Send_byte(Level_Cur[i]);
        UART3_Send_byte(Level_Cur[i]); 
     }
    Show_Level(level);//������ʾ��ǰҺλ
    delay_ms(50);
    for(i=0;i<9;i++)
    {    
        UART1_Send_byte(Level_UP[i]);
        UART3_Send_byte(Level_UP[i]);
    }
    Show_Level(UPlevel);//������ʾ������ֵ
    delay_ms(50);
    for(i=0;i<11;i++)
    {    
        UART1_Send_byte(Level_Dowe[i]);
        UART3_Send_byte(Level_Dowe[i]);
    }
    Show_Level(Downlevel);//������ʾ������ֵ
    delay_ms(50);
    for(i=0;i<12;i++)
    {    
        UART1_Send_byte(Level_Start[i]);
        UART3_Send_byte(Level_Start[i]);
    }
    Show_Level(levelinit);//������ʾ���ø߶�
    delay_ms(50);
}

//����1�жϴ����������ж��������յ������ݲ�����Ӧ�Ĵ���
void UART1_Interrupt_Handle()
{
    unsigned char UART1_Dat;
    UART1_Dat=UART1_ReceiveData8();//��ȡ�����жϵ�ֵ
    switch(UART1_Dat)
    {
        case '1':
            HCSR04_Start_Init();//������ʱ�߶�
            break;
        case '2':
            KEY_Change_Level_UP_H();//�ϵ�ˮλ��λ����ֵ
            break;
        case '3':
            KEY_Change_Level_UP_L();//�µ�ˮλ��λ����ֵ
            break;
        case '4':
            KEY_Change_Level_Down_H();//�ϵ�ˮλ��λ����ֵ
            break;
        case '5':
            KEY_Change_Level_Down_L();//�µ�ˮλ��λ����ֵ
            break;
        case '6':
            Total_Show();//��ʾ��ǰˮλ�߶ȣ�����ʱ�߶ȣ���������ֵ
            break;
    }
}

