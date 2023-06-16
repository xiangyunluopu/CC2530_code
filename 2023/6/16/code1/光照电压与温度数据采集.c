#include "DeclaPacka.h"

unsigned char buff_str[64];
unsigned char flag = 0;
double adcv;
double temp;

void main(void)
{
  Set_Clock_32M();
  Init_Port();
  LED_Check();
  Init_Uart0();
  Init_ADC();
  Init_WD_IE();
  for (;;)
  {
    if (flag)
    {
      P1 |= 0x1b;
      Get_adcv_temp_makstr(&adcv, &temp, (char*)buff_str);
      Uart0_Send_str((char*)buff_str);
      P1 &= ~0x1b;
      flag = 0;
    }
  }
  
}

#pragma vector = WDT_VECTOR
__interrupt void Service_WD(void)
{
  flag = 1;
  WDTIF = 0;
}