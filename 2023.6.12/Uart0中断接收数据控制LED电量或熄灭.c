#include "ioCC2530.h"

#define D5 P1_3
#define D6 P1_4

#define dat_buff_size 3

char Index = 0;
char dat_buff[dat_buff_size + 1] = {(char)0};

void init_LED(void)
{// 0001 1000
  P1SEL &= ~0x18;
  P1DIR |= 0x18;
  P1 &= ~0x18;
}

void Set_clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}

void init_Uart0(void)
{
  PERCFG &= ~0x01;
  // P0_2 只需要接收所以只要初始化这个接收引脚 0000 0100
  P1SEL |= 0x04;
  // 32M bit率 57600
  U0BAUD = 216;
  U0GCR = 10;
  U0UCR |= 0x80;
  U0CSR |= 0xC0;
  URX0IE = 1;
  URX0IF = 0;
}
#pragma vector = URX0_VECTOR
__interrupt void Service_URX0(void)
{
  char c = U0DBUF;
  if ('#' == c)
  {
    Index = 0;
    dat_buff[0] = '#';
  }
  else if ('#' == dat_buff[0])
  {
    Index += 1;
    dat_buff[Index] = c;
    if (Index >= 2)
    {
      char onoff = dat_buff[2] - '0';
      if ('5' == dat_buff[1])
      {
        D5 = onoff;
      }
      else if ('6' == dat_buff[1])
      {
        D6 = onoff;
      }
      for (Index = 0; Index < dat_buff_size; Index += 1)
      {
        dat_buff[Index] = '0';
      }
    }
  }
  
  URX0IF = 0;
}

void Init_all(void)
{// 使能总中断
  EA = 1;
  Set_clock_32M();
  init_LED();
  init_Uart0();
}

void main(void)
{
  Init_all();
  for (;;);
}