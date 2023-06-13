#include "DeclaPacka.h"

void Uart0_Send_char(char ch)
{
  while (U0CSR & 0x01);
  U0DBUF = ch;
}

void Uart0_Send_str(char* str)
{
  while (*str != '\0')
  {
    Uart0_Send_char(*str++);
  }
}

#pragma vector = WDT_VECTOR
__interrupt void Service_WDT(void)
{
  WDTIF = 0;
  char buff_str[9] = { 0 };
  
  int tmperature = 0;
  ADCCON3 = (0x00|0x30|0x0E);
  while (!(ADCCON1 & 0x80));
  // 搞不定
  Uart0_Send_str("片内温度为:");
  Uart0_Send_str(buff_str);
}

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}

void Init_Uart0(void)
{
  PERCFG &= ~0x01;
  // P0_3; 0000 1000;
  P0SEL |= 0x08;
  U0BAUD = 216;
  U0GCR = 10;
  U0UCR |= 0x80;
  U0CSR |= 0x80;
}

void Init_WD(void)
{
  EA = 1;
  // 0010 0000
  IEN2 |= 0x20;
  // 0000 1100
  WDCTL = 0x0C;
}