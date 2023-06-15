#include "DeclaPacka.h"

unsigned char count = 0;
unsigned char flag = 0;

void Init_WD(void)
{
  WDCTL = 0x0E;
}

void Uart0_Send_Char(char ch)
{
  while (U0CSR & 0x01);
  U0DBUF = ch;
}

char buff_str1[64] = { 0 };

void Uart0_Send_Str(char* str)
{
  while (*str != '\0')
  {
    Uart0_Send_Char(*str++);
  }
}

void V_LED(void)
{
  
  if (WDTIF)
  {
    count += 1;
    if (count == 7)
    {
      unsigned int adc_value;
      float adc_volta;
      unsigned int adc_volta_100;
      ADCCON3 = (0x80|0x20|0x00);
      while (!(ADCCON1 & 0x80));
      adc_value = ADCL;
      adc_value = (adc_value | (ADCH << 8)) >> 2;
      adc_volta = (3.3 / 1023) * (adc_value >> 3);
      adc_volta_100 = (unsigned int)(adc_volta * 100);
      sprintf((char*)buff_str1, "\nAIN0获取的值为:%d\n转换成电压为%d.%d%dV\n", adc_value, adc_volta_100 / 100, (adc_volta_100 / 10) % 10, adc_volta_100 % 10);
      Uart0_Send_Str((char*)buff_str1);
      
      P1 &= ~0x1B;
      if (adc_volta < 0.47)
      {
        D5 = 1;
      }
      if (adc_volta < 0.94)
      {
        D6 = 1;
      }
      if (adc_volta < 1.41)
      {
        D3 = 1;
      }
      if (adc_volta < 1.88)
      {
        D4 = 1;
      }
      if (adc_volta < 1.88)
      {
        flag = 1;
      }
      if (flag)
      {
        if (adc_volta < 0.47)
        {
          Uart0_Send_Str("D3 = 1\nD4 = 1\nD5 = 1\nD6 = 1\n");
        }
        else if (adc_volta < 0.94)
        {
          Uart0_Send_Str("D3 = 1\nD4 = 1\nD5 = 0\nD6 = 1\n");
        }
        else if (adc_volta < 1.41)
        {
          Uart0_Send_Str("D3 = 1\nD4 = 1\nD5 = 0\nD6 = 0\n");
        }
        else if (adc_volta < 1.88)
        {
          Uart0_Send_Str("D3 = 0\nD4 = 1\nD5 = 0\nD6 = 0\n");
        }
        else
        {
          Uart0_Send_Str("D3 = 0\nD4 = 0\nD5 = 0\nD6 = 0\n");
        }
      }
      count = 0;
    }
    WDTIF = 0;
  } 
}

void Init_ADC(void)
{
  APCFG |= 0x01;
  P0SEL |= 0x01;
  P0DIR &= ~0x01;
}

void Init_Port(void)
{
  P1SEL &= ~0x1B;
  P1DIR |= 0x1B;
  P1 &= ~0x1B;
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

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}