#include "DeclaPacka.h"

void Uart0_Send_dat(unsigned char ch)
{
  while (U0CSR & 0x01);
  U0DBUF = ch;
}

void Uart0_Send_str(char* str)
{
  while(*str != '\0')
  {
    Uart0_Send_dat(*str++);
  }
}

#pragma vector = WDT_VECTOR
__interrupt void Service_WDT(void)
{
  unsigned char buff_str[64];
  unsigned int dat;
  double temp;
  D3 = 1;
  ADCCON3 = (0x00|0x30|0x0E);
  while(!(ADCCON1 & 0x80));
  dat = ADCH;
  dat = ((dat << 8) | ADCL) >> 2;
  sprintf((char*)buff_str,"温度传感器获取的值为:%d\n",dat);
  Uart0_Send_str((char*)buff_str);
  temp = (dat >> 3) * (1.25 / 1023);
  sprintf((char*)buff_str,"经过转换后的电压为:%lfV\n",temp);
  Uart0_Send_str((char*)buff_str);
  D3 = 0;
  WDTIF = 0;
}

void Init_WD(void)
{
  WDCTL = 0x0C; // 定时器模式定时间隔一秒
  WDTIF = 0;
  EA = 1;
  IEN2 |= 0x20;
}

void Init_Uart0(void)
{
  PERCFG &= ~0x01;
  P0SEL |= 0x08;
  U0BAUD = 216;
  U0GCR = 12;
  U0UCR |= 0x80;
  U0CSR |= 0x80;
}

void Init_Port(void)
{ //0000 0001 P1_0
  P1SEL &= ~0x01;
  P1DIR |= 0x01;
  P1_0 = 0;
}

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while(CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}