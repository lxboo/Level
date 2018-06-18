#include "pbdata.h"   //����

void UART3_Configuration(void)//����3ͨѶ����
{
    UART3_DeInit();
    UART3_Init((u32)9600, UART3_WORDLENGTH_8D, UART3_STOPBITS_1, \
    UART3_PARITY_NO ,  UART3_MODE_TXRX_ENABLE);//�����ʣ��ֽ�����1��ֹͣλ������żЧ��λ��������ܺͷ���
    
    UART3_ITConfig(UART3_IT_RXNE_OR,ENABLE  );
    UART3_Cmd(ENABLE );		
}

//����3��������
void UART3_Send_byte(u8 byte)  
{
    UART3_SendData8((unsigned char)byte); //����һ��8λ������
    while (UART3_GetFlagStatus(UART3_FLAG_TXE) == RESET);//���ָ����־λ��λ״̬   �������ݼĴ����ձ�־
}

//����3�жϴ����������ж��������յ������ݲ�����Ӧ�Ĵ���
void UART3_Interrupt_Handle()
{
    unsigned char UART3_Dat;
    UART3_Dat=UART3_ReceiveData8();//��ȡ�����жϵ�ֵ
    switch(UART3_Dat)
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