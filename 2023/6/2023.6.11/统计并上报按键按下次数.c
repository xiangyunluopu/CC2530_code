#include "ioCC2530.h"
#include <stdio.h>

#define LED1 P1_0

#define SW2 P0_1

unsigned int count = 0;
char str_buf[64] = { 0 };

void Set_clock(void)
{
  // 0100 0000
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}

void Init_LED1(void)
{
  P1SEL &= ~0x01;
  P1DIR |= 0x01;
  LED1 = 0;
}

void Init_SW2(void)
{// 0000 0010
  P0SEL &= ~0x02;
  P0DIR &= ~0x02;
  P0INP &= ~0x02;
  // 0010 0000
  P2INP &= ~0x20;
}

void Init_Uart0()
{
  PERCFG &= ~0x01;
  //P0_3 0000 1000
  P0SEL |= 0x08;
  
  U0BAUD = 59;
  U0GCR = 8;
  
  U0UCR |= 0x80;
  U0CSR |= 0x80;
}

void Init_all(void)
{
  Init_LED1();
  Init_SW2();
  Init_Uart0();
}

void Delay(unsigned int time)
{
  unsigned int i = 0;
  unsigned char j = 0;
  for (i = 0; i < time; i += 1)
    for (j = 0; j < 240; j += 1)
    {
      asm("NOP");asm("NOP");asm("NOP");
    }
}

void Uart0_send_char(char dat)
{
  while (U0CSR & 0x01);
  U0DBUF = dat;
}

void Uart0_send_str(char* str_buf)
{
  while (*str_buf != '\0')
  {
    Uart0_send_char(*str_buf++);
  }
}

void Scan_sw2(void)
{
  if (!SW2)
  {
    Delay(200);
    if (!SW2)
    {
      LED1 = ~LED1;
      count += 1;
      sprintf(str_buf, "按键按下次数为：%d\r\n", count);
      Uart0_send_str(str_buf);
      while(!SW2);
    }
  }
}

void main(void)
{
  Set_clock();
  Init_all();
  while (1)
  {
    Scan_sw2();
  }
}