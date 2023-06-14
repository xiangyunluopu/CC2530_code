#include "DeclaPacka.h"

void Init_WD(void)
{
  WDCTL = 0x0C; // 定时，且一秒定时
  // 0010 0000
  IEN2 |= 0x20;
  EA = 1;
  WDTIF = 0;
}

#pragma vector = WDT_VECTOR
__interrupt void Service_WDT(void)
{
  D4 = ~D4;
  WDTIF = 0;
  count += 1;
  if (count == 3)
  {
    D3 = 1;
    count = 0;
    ADCCON3 = (0x80|0x20|0x00);
  }
}

void Init_Uart0(void)
{
  PERCFG &= ~0x01;
  // 0000 1000 P0_3
  P0SEL |= 0x08;
  U0BAUD = 59;
  U0GCR = 8;
  U0UCR |= 0x80;
  U0CSR |= 0x80;
}

void Init_ADC(void)
{
  APCFG |= 0x01; //P0_0 0000 0001
  P0SEL |= 0x01;
  P0DIR &= ~0x01;
  ADCIE = 1;
  EA = 1; // 我怀疑 EA 的意思就是 All_IE
}

void Uart0_Send_Char(unsigned char ch)
{
  while (U0CSR & 0x01);
  U0DBUF = ch;
}

void Urat0_Send_str(char* str)
{
  while (*str != '\0')
  {
    Uart0_Send_Char(*str++);
  }
}

#pragma vector = ADC_VECTOR
__interrupt void Service(void)
{
  value = (unsigned int)(((long)ADCL | ((long)ADCH << 8)) >> 2);
  sprintf((char*)buff_str1, "AIN0获取的值为：%d\r\n", value);
  Urat0_Send_str((char*)buff_str1);
  D3 = 0;
}

void Init_Port(void)
{
  //P1_0  0000 0001
  P1SEL &= ~0x01;
  P1DIR |= 0x01;
  D3 = 0;
  // P1_1 0000 0010
  P1SEL &= ~0x02;
  P1DIR |= 0x02;
  D4 = 0;
}

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}