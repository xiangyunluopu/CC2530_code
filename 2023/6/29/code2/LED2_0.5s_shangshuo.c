#include <ioCC2530.h>

#define LED2 P1_5

unsigned char count = 0;

void init_LED2(void)
{
  // 0010 0000
  P1SEL &= ~0x20;
  P1DIR |= 0x20;
  P1_5 = 0;
}

void init_timer1(void)
{
  CLKCONCMD &= 0x80;
  T1CTL |= 0X05;
  T1IE = 1;
  EA = 1;
}

#pragma vector = T1_VECTOR
__interrupt void Service_T1(void)
{
  count += 1; // 30 : 0.5s
  if (30 * 3 == count) // 第1.5秒打开LED2
  {
    LED2 = 1;
  }
  if (30 * 4 == count) // 第2.0秒关闭LED2，并且清除计数变量；
  {
    LED2 = 0;
    count = 0;
  }
}

void main(void)
{
  init_LED2();
  init_timer1();
  
  for (;;)
  {
    
  }
}