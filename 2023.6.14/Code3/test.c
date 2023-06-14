#include "DeclaPacka.h"

void main(void)
{
  Set_Clock_32M();
  Init_Uart0();
  Init_Port();
  Init_ADC();
  Init_WD();
  for (;;)
  {
    V_LED();
  }
}