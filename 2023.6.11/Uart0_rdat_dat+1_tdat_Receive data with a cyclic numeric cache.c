#include "ioCC2530.h"

#define MAX 64

unsigned char Queue[MAX] = { 0 };
unsigned char front = 0;
unsigned char rear = 0;
//unsigned char dat_p_1 = 0;

void Set_clock(void)
{
  // 0100 0000
  // 0000 0111
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}

void init_uart0(void)
{
  PERCFG &= ~0x01;
  // 0000 1100
  P0SEL |= 0x0C;
  U0BAUD = 59;
  U0GCR = 8;
  U0UCR |= 0x80;
  U0CSR |= 0xC0;
  UTX0IF = 1; //设成一是因为我需要这样用
  URX0IE = 1;
  URX0IF = 0;
  EA = 1;
}

void Urat0_send_dat(void)
{
  if (rear != front)
  {
    if (UTX0IF)
    {
      UTX0IF = 0;
      front = (front + 1) % MAX;
      U0DBUF = Queue[front] + 1;
    }
  }
}

#pragma vector = URX0_VECTOR
__interrupt void Service_URX0(void)
{
  if ((rear + 1) % MAX != front)
  {
    rear = (rear + 1) % MAX;
    Queue[rear] = U0DBUF;
  }
  else
  {
    while ((rear + 1) % MAX == front)
    {
     Urat0_send_dat();
    }
    rear = (rear + 1) % MAX;
    Queue[rear] = U0DBUF;
  }
}

void Init_all(void)
{
  init_uart0();
}

void main(void)
{
  Set_clock();
  Init_all();
  for (;;)
  {
    Urat0_send_dat();
  }
}

