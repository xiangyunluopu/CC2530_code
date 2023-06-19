#include <ioCC2530.h>

#define D6 P1_4

unsigned char count = 0;
unsigned char flag = 0;
//unsigned char buff_str[64] = { 0 };

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0X40;
  while (!(CLKCONSTA & 0X40));
  CLKCONCMD &= ~0X07;
}

void Init_Prot(void)
{
  P1SEL &= ~0X1B;
  P1DIR |= 0X1B;
  P1 &= ~0X1B;
}

void Init_Uart0(void)
{
  PERCFG &= ~0X01;
  P0SEL |= 0X08;
  U0BAUD = 216;
  U0GCR = 10;
  U0UCR |= 0X80;
  U0CSR |= 0X80;
}

void Init_Timer1_IE(void)
{
  CLKCONCMD &= ~0X08;
  EA = 1;
  T1IE = 1;
  T1CCTL0 |= 0X04;
  T1CC0L = 0XFF & 50000;
  T1CC0H = (0XFF00 & 50000) >> 8;
  T1CTL = 0X0E;
}

#pragma vector = T1_VECTOR
__interrupt void Service_T1(void)
{
  count += 1;
  if (10 == count)
  {
    flag = 1;
  }
}

void Uart0_Send_char(unsigned char ch)
{
  while (U0CSR & 0X01);
  U0DBUF = ch;
}

void Uart0_Send_str(char* str)
{
  while (*str != '\0')
  {
    Uart0_Send_char(*str++);
  }
}

void main(void)
{
  Set_Clock_32M();
  Init_Uart0();
  Init_Prot();
  Init_Timer1_IE();
  for (;;)
  {
    if (flag)
    {
      D6 = 1;
      T1CTL = 0;
      Uart0_Send_str("hello, world!\n");
      count = 0;
      T1CNTL = 0;
      T1CTL = 0X0E;
      D6 = 0;
      flag = 0;
    }
  }
}