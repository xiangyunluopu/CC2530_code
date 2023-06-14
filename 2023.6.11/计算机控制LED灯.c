#include "ioCC2530.h"

#define D3 P1_0
#define D4 P1_1

#define buff_size 3

unsigned char buffdat[buff_size + 1];
unsigned char c;
unsigned char onoff = 0;

unsigned int count = 0;

void init_LED(void)
{
  // 0000 0011
  P1SEL &= ~0x03;
  P1DIR |= 0x03;
  P1 &= ~0x03;
}

void init_Uart0(void)
{
  //EA = 1;
  PERCFG &= ~0x01;
  // 0000 1100
  P1SEL |= 0x0C;
  U0BAUD = 216;
  U0GCR = 10;
  U0UCR |= 0x80;
  U0CSR |= 0xC0;
  UTX0IF = 0;
  URX0IF = 0;
}

void Init_all(void)
{
  init_LED();
  init_Uart0();
}

void Set_clock(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}

void receive_handler(void)
{
  c = U0DBUF;
  URX0IF = 0;
  if ('#' == c)
  {
    count = 0;
    buffdat[0] = c;
  }
  else if ('#' == buffdat[0])
  {
    count += 1;
    buffdat[count] = c;
  }
  if (count >= 2)
  {
    onoff = buffdat[2] - 0x30;
    switch (buffdat[1])
    {
    case '1':
      D3 = ~D3;
      break;
    case '2':
      D4 = ~D4;
      break;
    }
    for (count = 0; count < buff_size; count += 1)
    {
      buffdat[count] = 0;
    }
  }
}

void main(void)
{
  Set_clock();
  Init_all();
  for (;;)
  {
    if (URX0IF)
    {
      receive_handler();
    }
  }
}