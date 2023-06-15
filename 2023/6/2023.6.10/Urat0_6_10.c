#include "ioCC2530.h"

#define LED1 P1_0

unsigned int counter = 0;

void Set_CLK(void)
{
  // 0100 0000
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  //0000 1111
  //CLKCONCMD &= ~0x0F;
  CLKCONCMD &= ~0x07;
}

void Init_Timer1(void)
{
  // 0000 1100
  T1CTL = 0x0E;
  T1CCTL0 |= 0x04;
  T1CC0L = 50000 & 0xFF;
  T1CC0H = ((50000 & 0xFF00) >> 8);
  //T1IF = 0;
  //T1STAT &= ~0x01;
  //TIMIF &= ~0x40;
  IEN1 |= 0x02; 
  // T1IE = 1;
  EA = 1; 
}
#pragma vector = T1_VECTOR
__interrupt void Service(void)
{
  EA = 0;
  counter += 1;
  //T1STAT &= ~0x01;
  EA = 1;
}

void Init_Urat0(void)
{
  PERCFG &= ~0x01; // 复位值本来就是全0，所以此处不会产生实际效果，但是为了加深熟练度我还是写上。
  P0SEL |= 0x08;//P0_3,这个端口用来Send,我只要发送所以初始Send端口
  U0BAUD = 216;//设置波特率57600
  U0GCR = 10;
  U0UCR |= 0x80;
  U0CSR |= 0x80;
  UTX0IF = 0; // 虽然清除标记但是我可能不用，为了加深印象所以写上；
}

void init_LED1(void)
{
  P1SEL &= ~0x01;
  P1DIR |= 0x01;
  P1 &= ~0x01; // LED1 = 0;
}

void UART0SendByte(unsigned char c)
{
    while (U0CSR & 0x01);
    U0DBUF = c;
}

void UART0SendString(char* str)
{

  while (*str != '\0')
  {
    UART0SendByte(*str++);
  }
  //LED1 = 0;
}

void main(void)
{
  Set_CLK();
  //init_LED1();
  //Init_Timer1();
  Init_Urat0();
  while (1)
  {
    //if (counter >= 15)
    //{
      //LED1 = ~LED1;
      //counter = 0;
      //LED1 = 1;
      UART0SendString("Hello ! I am CC2530 .");
      //LED1 = 0;
    //}
  }
}