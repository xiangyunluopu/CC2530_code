#include "DeclaPacka.h"

char buff_str1[64] = { 0 };

void Uart0_Send_Char(char ch)
{
  while (U0CSR & 0x01);
  U0DBUF = ch;
}

void Uart0_Send_Str(char* str)
{
  while (*str != '\0')
  {
    Uart0_Send_Char(*str++);
  }
}

void Send(unsigned int adc_value, float adc_volta)
{
  unsigned int a = 100 * adc_volta;
  sprintf((char*)buff_str1, "AIN0获取的值为：%d, 转换成电压值为：%d.%d%d\r\n", adc_value, a / 100, (a / 10) % 10, a % 10);
  Uart0_Send_Str((char*)buff_str1);
}

float adc_value_trans_volta(unsigned int adc_value)
{
  return (adc_value >> 3) * (3.3 / 1023);
}

unsigned int get_adc_value(void)
{
  unsigned int value = ADCH;
  value = ((value << 8) | ADCL);
  return (value >> 2);
}

void Init_WD(void)
{
  WDCTL = 0x0C;
  WDTIF = 0;
}

void Init_Uart(void)
{
  PERCFG &= ~0x01;
  // P0_3 0000 1000
  P0SEL |= 0x08;
  U0BAUD = 59;
  U0GCR = 8;
  U0UCR |= 0x80;
  U0CSR |= 0x80;
}

void Init_ADC(void)
{
  // 0000 0001
  APCFG |= 0x01;
  P0SEL |= 0x01;
  P0DIR &= ~0x01;
}

void Init_Port(void)
{
  // P1_3  0000 1000
  P1SEL &= ~0x08;
  P1DIR |= 0x08;
  P1_3 = 0;
}

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}
