#include "DeclaPacka.h"

void Send_str1(char* str)
{
  while (*str != '\0')
  {
    while (U0CSR & 0x01);
    U0DBUF = *str++;
  }
}

void Mak_buff_str(int value,char* buff_str)
{// 000
  *buff_str = (value / 100) + '0';
  *(buff_str + 1) = '.';
  *(buff_str + 2) = ((value % 100) / 10) + '0';
  *(buff_str + 3) = (value % 10) + '0';
  *(buff_str + 4) = 'V';
  *(buff_str + 5) = '\n';
  *(buff_str + 6) = '\0';
}

void str_Send(char* str)
{
  Send_str1("光感模块的光伏电压为：");
  while (*str != '\0')
  {
    while (U0CSR & 0x01);
    U0DBUF = *str++;
  }
}

int Get_value(void)
{
  ADCCON3 = (0x80|0x30|0x00);
  while (!(ADCCON1 & 0x80));
  int value = ((int)((((long)ADCL | ((long)ADCH << 8)) * 330) >> 15));
  return value;
}

void Timing_2s(void)
{
  int Count = 0;
  while (Count < 2)
  {
    while (!WDTIF);
    WDTIF = 0;
    Count += 1;
  }
}

void Init_Uart0(void)
{
  PERCFG &= ~0x01; // TX P0_3 0000 1000
  P0SEL |= 0x08;
  U0BAUD = 216;
  U0GCR = 10;
  U0UCR |= 0x80;
  U0CSR |= 0x80;
}

void Init_ADC(void)
{
  APCFG |= 0x01;
  P0SEL |= 0x01;
  P0DIR &= ~0x01;
}

void Init_Port(void)
{
  P1SEL &= ~0x01;
  P1DIR |= 0x01;
  P1_0 = 0;
}

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONCMD & 0x40);
  CLKCONCMD &= ~0x07;
}

void Init_WD(void)
{ 
  // 0000 1100
  WDCTL = 0x0C; // 看门狗一秒定时
  WDTIF = 0;
}