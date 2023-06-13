#include <ioCC2530.h>
#include <stdio.h>

//static unsigned int a = 10;

void Set_Clock_32M(void);

void Init_Uart0(void);

void Init_WD(void);

void Uart0_Send_str(char* str);

void Uart0_Send_char(char ch);

#pragma vector = WDT_VECTOR
__interrupt void Service_WDT(void);