#include "DeclaPacka.h"

void Init_WD(void)
{
  WDCTL = 0x0C; 
  WDTIF = 1;
}

unsigned char buff_str[64] = { 0 };

void Delay(unsigned int time)
{
  unsigned int i;
  unsigned char j;
  for (i = 0; i < time; i += 1)
    for (j = 0; j < 240; j += 1)
    {
      asm("NOP"); asm("NOP"); asm("NOP");
    }
}

void Uart0_Send_char(unsigned char ch)
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

void Read_Send_temp(void)
{
  unsigned char LSB,MSB;
  unsigned int SB_16;
  double temp = 0;
  D3 = 1;
  Init_DS18B20();
  Write_DS18B20(0xCC);
  Write_DS18B20(0x44);
  while (!WDTIF);
  WDTIF = 0;
  while (!WDTIF);
  Init_DS18B20();
  Write_DS18B20(0xCC);
  Write_DS18B20(0xBE);
  LSB = Read_DS18B20();
  MSB = Read_DS18B20();
  SB_16 = MSB;
  SB_16 = (SB_16 << 8) | LSB;
  if (0x00 == (MSB & 0xF8))
  {
    temp = SB_16 * 0.0625;
    sprintf((char*)buff_str,"获取的温度为：%lf摄氏度\n",temp);
  }
  else
  {
    SB_16 = (~SB_16) + 1;
    temp = SB_16 * 0.0625;
    sprintf((char*)buff_str,"获取的温度为：-%f摄氏度\n",temp);
  }
  Uart0_Send_str((char*)buff_str);
  D3 = 0;
}

void Init_Timer1(void)
{
  CLKCONCMD &= ~0x80;
  EA = 1;
  T1IE = 1;
  // 正计数倒计数模式
  // 128分频
  // 定时0.1s
  T1CC0L = (0xFF & 12500);
  T1CC0H = (0xFF00 & 12500) >> 8;
  T1CTL = 0x0C;
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

void Init_Port(void)
{
  P1SEL &= ~0x1B;
  P1DIR |= 0x1B;
  P1 &= ~0x1B;
}

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}