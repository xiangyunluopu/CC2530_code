#include "DeclaPacka.h"
int value;
char buff_str[64];

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
    value = Get_value();
    Mak_buff_str(value,buff_str);
    str_Send(buff_str);
  }
}