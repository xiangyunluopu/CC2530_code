#include <ioCC2530.h>
#include <stdio.h>
#define D3 P1_0

unsigned int count_s = 0;
unsigned char count = 0;
unsigned char buff_str[64]  = { 0 };

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0X40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0X07;
}

void Init_Port(void)
{
  P1SEL &= ~0X1B;
  P1DIR |= 0X1B;
  P1 &= ~0X1B;
}

void Init_Uart0(void)
{
  PERCFG &= ~0X01;
  P0SEL |= 0X08;
  U0BAUD = 216;
  U0GCR = 10;
  U0UCR |= 0X80;
  U0CSR |= 0X80;
}

void Init_Timer1(void)
{
  CLKCONCMD &= ~0X08;
  EA = 1;
  T1IE = 1;
  T1CCTL0 = (0X04| 0X40);
  T1CC0L = 0XFF & 25000;             // 通过测试1通道我不会用
  T1CC0H = (0XFF00 & 25000) >> 8;
  T1CTL = 0X0E;
}

void Uart0_Send_char(char ch)
{
  while (U0CSR & 0X01);
  U0DBUF = ch;
}

void Uart0_Send_str(char* str)
{
  while (*str != '\0')
  {
    Uart0_Send_char(*str++);
  }
}

#pragma vector = T1_VECTOR
__interrupt void Service_T1(void)
{
  count += 1;
  if (10 == count)
  {
    D3 = 1;
    count_s += 1;
    sprintf((char*)buff_str, "定时器1计时测试：%ds\n", count_s);
    Uart0_Send_str((char*)buff_str);
    count = 0;
    D3 = 0;
  }
}

void main(void)
{
  Set_Clock_32M();
  Init_Port();
  Init_Uart0();
  Init_Timer1();
  for(;;)
  {
    
  }

}