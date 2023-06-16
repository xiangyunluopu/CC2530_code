#include "DeclaPacka.h"

void Uart0_Send_char(unsigned char ch)
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

void Get_adcv_temp_makstr(double* adcv, double* temp, char* buff_str)
{
  unsigned int LSB,MSB;
  unsigned int buff_adcv;
  unsigned int buff_temp;
  Init_DS18B20();
  Write_DS18B20(0xcc);
  Write_DS18B20(0x44);
  ADCCON3 = (0x80|0x30|0x00);
  //Delay(4000);
  while (!(ADCCON1 & 0x80));
  buff_adcv = ADCH;
  buff_adcv = (buff_adcv << 8) | ADCL;
  *adcv = (double)(buff_adcv >> 5) * (3.3 / 1023);
  Init_DS18B20();
  Write_DS18B20(0xcc);
  Write_DS18B20(0xbe);
  LSB = Read_DS18B20();
  MSB = Read_DS18B20();
  buff_temp = MSB;
  buff_temp = (buff_temp << 8) | LSB;
  if (0XF8 == (MSB & 0xf8))
  {// 负数
    buff_temp = (~buff_temp) + 1;
    *temp = (double)buff_temp * 0.0625;
    sprintf(buff_str, "捕获的的光伏电压:%.2lfV;捕获的温度为:-%.1lfC\n", *adcv, *temp);
  }
  else
  {// 正数
    *temp = (double)buff_temp * 0.0625;
    sprintf(buff_str, "捕获的的光伏电压:%.2lfV;捕获的温度为:%.1lfC\n", *adcv, *temp);
  }
  
}

void Init_ADC(void)
{
  APCFG |= 0x01; // P0_0
}

void Init_WD_IE(void)
{
  EA = 1;
  IEN2 |= 0X20;
  WDCTL = 0X0C;
}

void Init_Uart0(void)
{
  PERCFG &= ~0X01;
  P0SEL |= 0X08;
  U0BAUD = 59;
  U0GCR = 8;
  U0UCR |= 0X80;
  U0CSR |= 0X80;
}

void Delay(unsigned int time)
{
  
  for (;time > 0; time -= 1)
    for(unsigned char i = 0; i < 240; i += 1)
    {
      asm("NOP");asm("NOP");asm("NOP");
    }
}

void LED_Check(void)
{
  P1 |= 0x1b;
  Delay(10000);
  P1 &= ~0x1b;
}

void Init_Port(void)
{
  P1SEL &= ~0x1b;
  P1DIR |= 0x1b;
  P1 &= ~0x1b;
}

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (!(CLKCONSTA & 0X40));
  CLKCONCMD &= ~0X07;
}