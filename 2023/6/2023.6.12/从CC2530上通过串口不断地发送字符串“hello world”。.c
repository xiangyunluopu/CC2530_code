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
  // P0_3 ��Ϊֻ�õ���������ֻ��Ҫ��ʼһ���˿�
  P0SEL |= 0x08;
  U0BAUD = 216;
  U0GCR = 10; // bit57600
  U0CSR |= 0x80;
  U0UCR |= 0x80;
  // ����������Ҫ��ѯ������־λ���Բ�ȥ���ˣ����ǲ�ѯ������״̬�Ĵ����еĻλ���ж��Ƿ��ڷ����ֽڣ�
}

void Uart0_Send_8bit(unsigned char ch)
{
  while (U0CSR & 0x01); // ��ѯ�λ��������ڷ������Ǿ͵ȴ������꣬����U0DBUF��װ���ֽ�
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
     Uart0_Send_str("hello world");// ��ĿҪ�󲻶Ϸ���hell0 world �����Ǿ����޷���
  }
}