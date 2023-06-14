#include "ioCC2530.h"

#define D3 P1_0
#define D4 P1_1
#define D5 P1_3
#define D6 P1_4

#define buff_dat_size 3
#define MAX_Speed 10

unsigned int D3_Speed = 0;
unsigned int D4_Speed = 0;
unsigned int D5_Speed = 0;
unsigned int D6_Speed = 0;
char buff_dat[buff_dat_size + 1] = {(char)0};
char Index = 0;
unsigned int count = 0;

void Set_clock_32M(void);
void Init_LED(void);
void Init_Uart0(void);
void Init_all(void);
void Init_timer1(void);

void main(void)
{
  Set_clock_32M();
  Init_all();
  for (;;)
  {
    
  }
}

void Init_all(void)
{
  EA = 1;
  Init_LED();
  Init_timer1();
  Init_Uart0();
}

void Init_timer1(void)
{
  // 0011 1000
  CLKCONCMD &= ~0x38;
  T1IE = 1;
  T1CCTL0 |= 0x04;
  T1CC0L = 0xFF & (25000 / 2);
  T1CC0H = (0xFF00 & (25000/ 2)) >> 8; // 其实就是0.2s啦
  T1CTL = 0x0E;
}
#pragma vector = T1_VECTOR
__interrupt void Service_T1(void)
{
  //EA = 0;
  count += 1;
  //EA = 1;
  
    if (D3_Speed)
    {
      if (0 == (count % (D3_Speed + 1)))
      {
        D3 = ~D3;
      }
    }
    else
    {
      D3 = 0;
    }
    if (D4_Speed)
    {
      if (0 == (count % (D4_Speed + 1)))
      {
        D4 = ~D4;
      }
    }
    else
    {
      D4 = 0;
    }
    if (D5_Speed)
    {
      if (0 == (count % (D5_Speed + 1)))
      {
        D5 = ~D5;
      }
    }
    else
    {
      D5 = 0;
    }
    if (D6_Speed)
    {
      if (0 == (count % (D6_Speed + 1)))
      {
        D6 = ~D6;
      }
    }
    else
    {
      D6 = 0;
    }
}

void Init_Uart0(void)
{
  PERCFG &= ~0x01;
  P0SEL |= 0x04;
  U0BAUD = 216;
  U0GCR = 10;
  U0UCR |= 0x80;
  U0CSR |= 0xC0; // 做个标记
  URX0IE = 1;
  URX0IF = 0;
}
#pragma vector = URX0_VECTOR
__interrupt void Service_URX0(void)
{
  char c = U0DBUF;
  if ('*' == c)
  {
    Index = 0;
    buff_dat[0] = '*';
  }
  else if ('*' == buff_dat[0])
  {
    Index += 1;
    buff_dat[Index] = c;
    if (Index >= 2)
    {
      switch (buff_dat[1])
      {
      case '3':
        D3_Speed = (unsigned int)((buff_dat[2] - '0') % MAX_Speed);
        break;
      case '4':
        D4_Speed = (unsigned int)((buff_dat[2] - '0') % MAX_Speed);
        break;
      case '5':
        D5_Speed = (unsigned int)((buff_dat[2] - '0') % MAX_Speed);
        break;
      case '6':
        D6_Speed = (unsigned int)((buff_dat[2] - '0') % MAX_Speed);
        break;
      }
      for (Index = 0; Index < buff_dat_size; Index += 1)
      {
        buff_dat[Index] = '0';
      }
    }
  }
  URX0IF = 0;
}

void Init_LED(void)
{
  P1SEL &= ~0x1b;
  P1DIR |= 0x1b;
  P1 &= ~0x1b;
}

void Set_clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}