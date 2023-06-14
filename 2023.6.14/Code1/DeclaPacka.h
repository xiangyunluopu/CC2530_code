#include <ioCC2530.h>
#include <stdio.h>

#define D3 P1_0
#define D4 P1_1

static unsigned int value = 0;

static unsigned char buff_str1[32] = { 0 };

static unsigned char count = 0;

void Set_Clock_32M(void); // ����ϵͳʱ��Ƶ��Ϊ32M

void Init_Port(void);// ��ʼ��D3 D4

void Init_ADC(void); // ����P0_0Ϊģ��ͨ����ʹ��ADC�ж������ж�

void Init_Uart0(void); // ����

void Urat0_Send_str(char* str); // �����ַ���

void Uart0_Send_Char(unsigned char ch); // �����ַ�

void Init_WD(void); // ��ʼ�����Ź�

#pragma vector = ADC_VECTOR
__interrupt void Service(void); // ADC������������str,������

#pragma vector = WDT_VECTOR
__interrupt void Service_WDT(void); // ���Ź���������count += 1,count == 3ʱ������ADCת��
