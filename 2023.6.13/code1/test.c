#include "DeclaPacka.h"

char buff_str[7] = {0};

void main(void)
{
  Set_Clock_32M();
  Init_WD();
  Init_Port();
  Init_ADC();
  Init_Uart0();
  for (;;)
  {
    Timing_2s();
    D3 = 1;
    int value = Get_value();
    Mak_buff_str(value, buff_str);
    str_Send(buff_str);
    D3 = 0;
  }
}