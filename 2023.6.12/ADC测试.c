#include "ioCC2530.h"
#include <stdio.h>

#define D3 P1_0

void Set_Clock_32M(void);
void Init_ADC(void);
void Init_WD(void);
void Init_Uart0(void);
void get_ADC(void);
void Init_Port(void);
void Uart_Send_data(char data);
void Uart0_Send_str(char* str);
void main(void)
{
  int count = 0;
  Set_Clock_32M();
  Init_ADC();
  Init_Uart0();
  Init_WD();
  Init_Port();
  
  for(;;)
  {
    if (WDTIF)
    {
      WDTIF = 0;
      count += 1;
      if (count)
      {
        count = 0;
        get_ADC();
      }
    }
  }
}

void Init_Port(void)
{
  P1SEL &= ~0x01;
  P1DIR |= 0x01;
  P1 &= ~0x01; // D3 = 0;
}

void get_ADC(void)
{
  D3 = 1;
  long ADCV = 0;
  char buff_str[64] = {0};
  ADCCON3 = (0x80|0x30|0x00);
  while (!(ADCCON1 & 0x80));
  ADCV = (((long)ADCH << 8) | ((long)ADCL) >> 2);
  sprintf(buff_str,"AIN0获取的数值为：%d\n",(int)(ADCV));
  while (!UTX0IF);
  Uart0_Send_str(buff_str);
  D3 = 0;
}
            
void Uart0_Send_str(char* str)
{
  while (*str != '\0')
  {
    Uart_Send_data(*str++);
  }
}

void Uart_Send_data(char data)
{
  while  (!UTX0IF);
  UTX0IF = 0;
  U0DBUF = data;
}

void Init_WD(void)
{
  CLKCONCMD &= ~0x08;
  WDCTL = 0x0C;
  WDTIF = 0;
}

void Init_Uart0(void)
{
  PERCFG &= ~0x01; // 0000 1000
  P0SEL |= 0x08;
  U0BAUD = 216;
  U0GCR = 10;
  U0UCR |= 0x80;
  U0CSR |= 0x80;
  UTX0IF = 1;
}

void Init_ADC(void)
{
  APCFG |= 0x01;
  P0SEL |= 0x01;
  P0DIR &= ~0x01;
}

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}