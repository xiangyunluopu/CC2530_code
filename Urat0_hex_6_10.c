#include "ioCC2530.h"

#define LED1 P1_0

unsigned int count = 0;

unsigned char HexData[] = {0xC4, 0xF0, 0xFF & 8, 0xFF & 9, 0x00, 0xD8, 0xE5, 0x00, 0xD2};
unsigned char sz = sizeof(HexData) / sizeof(HexData[0]);

//unsigned char* p_hexdata = HexData;

void Set_CLK(void)
{
  // 0100 0000
  CLKCONCMD &= ~0x40;
  while (!CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x0F;
}

void LED(void)
{
  P1SEL &= ~0x01;
  P1DIR |= 0x01;
  P1_0 = 0;
}

void Timer1(void)
{
  T1IE = 1;
  T1CCTL0 |= 0x04;
  T1CC0L = 50000 & 0xFF;
  T1CC0H = ((50000 & 0xFF00) >> 8);
  T1CTL = 0x0E;
}
#pragma vector = T1_VECTOR
__interrupt void SERVICE(void)
{
  EA = 0;
  count += 1;
  EA = 1;
}

void Uart0(void)
{
  PERCFG &= ~0x01;
  P0SEL |= 0x08;
  //57600
  U0BAUD = 216;
  U0GCR = 10;
  U0UCR &= ~0x80;
  U0CSR |= 0x80;
  UTX0IF = 0;
}
  
void Init_All(void)
{
  EA = 1;
  Timer1();
  LED();
  Uart0();
}

void UART0_Send_Byte(unsigned char c)
{
  while(U0CSR & 0x01);
  U0DBUF = c;
}

void UART0_Send_String(unsigned char* str)
{
  while (*str != '\0')
  {
    UART0_Send_Byte(*str++);
  }
}

void UART0SendData(unsigned char Data)
{
  while(U0CSR & 0x01);
  U0DBUF = Data;
}

void UART0_Send_HexData(unsigned char* HexData, unsigned int sz)
{
  while (sz--)
  {
    UART0SendData(*HexData++);
  }
}

void main(void)
{
  Set_CLK();
  Init_All();
  
  while (1)
  {
    if (count >= 15)
    {
      count = 0;
      LED1 = 1;
      //UART0_Send_String("hello , world .");
      UART0_Send_HexData(HexData, sz);
      LED1 = 0;
    }
  }
}