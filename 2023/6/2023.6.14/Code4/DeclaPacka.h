#include "XMF_DS18B20_CC2530.h"
#include <stdio.h>

#define D3 P1_0
#define D4 P1_1
#define D5 P1_3
#define D6 P1_4

void Init_WD(void);

void Delay(unsigned int time);

void Init_Uart0(void);

void Init_Port(void);

void Set_Clock_32M(void);

void Read_Send_temp(void);

void Uart0_Send_str(char* str);

