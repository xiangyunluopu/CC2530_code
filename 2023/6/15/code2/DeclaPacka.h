#include <ioCC2530.h>
#include <stdio.h>

#define D3 P1_0

void Init_D3(void);

void Set_Clock_32M(void);

void Init_Uart0(void);

void Init_WD(void);

__interrupt void Service_WDT(void);

void Uart0_Send_str(char* str);

void Uart0_Send_char(char ch);