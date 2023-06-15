#include "DeclaPacka.h"

unsigned char buff_str1[64];
unsigned char buff_str2[64];

void Uart0_Send_char(char ch)
{
  while (U0CSR & 0x01);
  U0DBUF = ch;
}
  
void Uart0_Send_str(char* str)
{
  while (*str != '\0')
  {
    Uart0_Send_char(*str++);
  }
}

#pragma vector = WDT_VECTOR
__interrupt void Service_WDT(void)
{
  unsigned int dat;
  double ADCV;
  D3 = 1;
  ADCCON3 = (0x80|0x30|0x0D);
  while(!(ADCCON1 & 0x80));
  dat = ADCH;
  dat = ((dat << 8) | ADCL) >> 2;
  ADCV = (dat >> 3) * (3.3 / 1023);
  sprintf((char*)buff_str1, "���ο���ѹͨ����ȡ��ADCֵΪ:%d, ", dat);
  sprintf((char*)buff_str2, "ת��Ϊ��ѹΪ:%lfV\n", ADCV);
  Uart0_Send_str((char*)buff_str1);
  Uart0_Send_str((char*)buff_str2);
  D3 = 0;
  WDTIF = 0;
}

void Init_WD(void)
{
  EA = 1;
  IEN2 |= 0x20;
  WDTIF = 0;
  WDCTL = 0x0C;
}

void Init_Uart0(void)
{
  PERCFG &= ~0x01;
  P0SEL |= 0x08;
  U0BAUD = 216;
  U0GCR = 10;
  U0UCR |= 0x80;
  U0CSR |= 0x80;
}

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}

void Init_D3(void)
{
  P1SEL &= ~0x01;
  P1DIR |= 0x01;
  P1 &= ~0x01;
}