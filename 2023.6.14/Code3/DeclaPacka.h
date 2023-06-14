#include <ioCC2530.h>
#include <stdio.h>

#define D3 P1_0
#define D4 P1_1
#define D5 P1_3
#define D6 P1_4

void Init_WD(void);

void Uart0_Send_Char(char ch);

void Uart0_Send_Str(char* str);

void V_LED(void);

void Init_ADC(void);

void Init_Port(void);

void Init_Uart0(void);

void Set_Clock_32M(void);

