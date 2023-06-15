#include "ioCC2530.h"

void Set_Clock(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}

void Init_Uart0(void)
{
  PERCFG &= ~0x01;
  // P0_3 因为只用到发送所以只需要初始一个端口
  P0SEL |= 0x08;
  U0BAUD = 216;
  U0GCR = 10; // bit57600
  U0CSR |= 0x80;
  U0UCR |= 0x80;
  // 接下来不需要查询发生标志位所以不去管了；我们查询控制与状态寄存器中的活动位来判断是否在发送字节；
}

void Uart0_Send_8bit(unsigned char ch)
{
  while (U0CSR & 0x01); // 查询活动位，如果正在发送我们就等待发送完，再往U0DBUF中装填字节
  U0DBUF = ch;
}

void Uart0_Send_str(unsigned char* str)
{
  while (*str != '\0')
  {
    Uart0_Send_8bit(*str++);
  }
}

void main(void)
{
  Set_Clock();
  Init_Uart0();
  
  for (;;)
  {
     Uart0_Send_str("hello world");// 题目要求不断发送hell0 world 那我们就无限发送
  }
}