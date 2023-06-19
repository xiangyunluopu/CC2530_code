#include <ioCC2530.h>

#define D4 P1_1
#define D6 P1_4

unsigned char count = 0;

void Init_Port(void)
{
  P1SEL &= ~0x1b;
  P1DIR |= 0x1b;
  P1 &= ~0x1b;
}

void Init_Timer1(void)
{
  EA = 1;
  T1IE = 1;
  T1CCTL0 |= 0X04;
  T1CC0L = 0xff & 12500;
  T1CC0H = (0XFF00 & 12500) >> 8;
  T1CTL = (0X0C|0X02);
}

#pragma vector = T1_VECTOR
__interrupt void Service_T1(void)
{
  count += 1;
  if (0 == (count % 10))
  {
    D4 = ~D4;
  }
  if (40 == count)
  {
    D6 = ~D6;
  }
}

void main(void)
{
  Init_Port();
  Init_Timer1();
  for (;;)
  {
    
  }
}