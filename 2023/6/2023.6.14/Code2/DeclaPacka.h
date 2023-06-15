#include <ioCC2530.h>

#include <stdio.h>

#define D5 P1_3

void Uart0_Send_Char(char ch);

void Uart0_Send_Str(char* str);

void Send(unsigned int adc_value, float adc_volta);

float adc_value_trans_volta(unsigned int adc_value);

unsigned int get_adc_value(void);

void Init_WD(void);

void Init_Uart(void);

void Init_ADC(void);

void Init_Port(void);

void Set_Clock_32M(void);


