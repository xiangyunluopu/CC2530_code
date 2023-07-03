#include <ioCC2530.h>

#define LED2 P1_5

void Delay(unsigned int time)
{
  unsigned char k = 240;
  while (time--)
    while (k--)
    {
      asm("NOP");
      asm("NOP");
      asm("NOP");
    }
}

void main(void)
{ 
  // 0010 0000
  P1SEL &= ~0x20;
  P1DIR |= 0x20;
  P1 &= ~0x20; // LED2 นุ
  
  for (;;)
  {
    Delay(2000);
    LED2 = ~LED2;
  }
  
}