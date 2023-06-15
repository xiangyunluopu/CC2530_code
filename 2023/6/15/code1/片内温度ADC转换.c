#include "DeclaPacka.h"

void main(void)
{
  Set_Clock_32M();
  Init_Port();
  Init_Uart0();
  Init_WD();
  for (;;)
  {
    
  }
}