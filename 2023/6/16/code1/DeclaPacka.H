#include "XMF_DS18B20_CC2530.h"
#include <stdio.h>

#define D3 P1_0
#define D4 P1_1
#define D5 P1_3
#define D6 P1_4

void Uart0_Send_char(unsigned char ch);

void Uart0_Send_str(char* str);

void Get_adcv_temp_makstr(double* adcv, double* temp, char* buff_str);

void Init_ADC(void);

__interrupt void Service_WD(void);

void Init_WD_IE(void);

void Init_Uart0(void);

void Delay(unsigned int time);

void Init_Port(void);

void Set_Clock_32M(void);

void LED_Check(void);