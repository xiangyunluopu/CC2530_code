#include <ioCC2530.h>
#include <stdio.h>

#define D3 P1_0

void Set_Clock_32M(void); // ����32Mϵͳʱ��

void Init_Port(void); // ��ʼ��Ҫ�õ�D3��

void Init_Uart0(void); // ��ʼ��UART0�����ڷ���

void Init_WD(void); // ���Ź���ʼ��Ϊ��ʱ��ģʽ��ʱ���һ��

__interrupt void Service_WDT(void); // ���Ź��жϷ�����

void Uart0_Send_str(char* str); // uart0�����ַ���

void Uart0_Send_dat(unsigned char ch); // uart0�����ַ�