#include "ioCC2530.h"

unsigned char dat;

void Set_clock(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONCMD & 0x40);
  CLKCONCMD &= ~0x07;
}

void Init_Uart0(void)
{
  PERCFG &= ~0x01;
  P0SEL |= 0x0C;
  U0BAUD = 59;
  U0GCR = 8;
  U0UCR |= 0x80;
  U0CSR |= 0xC0;
  UTX0IF = 0;
  URX0IE = 1;
  URX0IF = 0;
  EA = 1;
}

void Uart0_send_dat(unsigned char dat)
{
  U0DBUF = dat;
  while (!UTX0IF);
  UTX0IF = 0;
}

#pragma vector = URX0_VECTOR
__interrupt void Service(void)
{
  dat = U0DBUF;
  Uart0_send_dat(dat + 1);
}

void main(void)
{
  Set_clock();
  Init_Uart0();
  for (;;)
  {
    
  }
}