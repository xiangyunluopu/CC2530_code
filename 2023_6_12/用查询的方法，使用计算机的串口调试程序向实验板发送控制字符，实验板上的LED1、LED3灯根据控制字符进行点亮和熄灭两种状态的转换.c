#include "ioCC2530.h"

#define D3 P1_0
#define D4 P1_1

#define dat_buff_size 3

char Index = 0;
char dat_buff[dat_buff_size + 1] = {(char)0};

void Set_Clock(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}

void Init_Uart0(void)
{
  PERCFG &= ~0x01; // 0000 1100
  P0SEL |= 0x0C;
  U0BAUD = 216;
  U0GCR = 10;
  U0UCR |= 0x80;
  U0CSR |= 0xC0;
  URX0IF = 0;
}

void Receive_handler(void)
{
  char c = 0;
  c = U0DBUF;
  URX0IF = 0;
  if ('#' == c)
  {
    Index = 0;
    dat_buff[0] = c;
  }
  else if ('#' == dat_buff[0])
  {
    Index += 1;
    dat_buff[Index] = c;
    if (Index >= 2)
    {
      char onoff = dat_buff[2] - '0';
      if ('3' == dat_buff[1])
      {
        D3 = onoff;
      }
      else if ('4' == dat_buff[1])
      {
        D4 = onoff;
      }
      for (Index = 0; Index < dat_buff_size; Index += 1)
      {
        dat_buff[Index] = (char)0;
      }
    }
  }
}

void Init_LED(void)
{
  // 0000 0011
  P1SEL &= ~0x03;
  P1DIR |= 0x03;
  P1 &= ~0x03;
}

void main(void)
{
  Set_Clock();
  Init_LED();
  Init_Uart0();
  for (;;)
  {
    if (URX0IF)
    {
      Receive_handler();
    }
  }
}