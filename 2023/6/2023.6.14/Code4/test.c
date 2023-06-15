#include "DeclaPacka.h"

void main(void)
{
  Set_Clock_32M();
  Init_Port();
  Init_Uart0();
  Init_WD();
  for (;;)
  {
    Read_Send_temp();
    while (!WDTIF);
    WDTIF = 0;
    while (!WDTIF);
  }
}