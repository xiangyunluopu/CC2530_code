#include "DeclaPacka.h"

void main(void)
{
  Set_Clock_32M();
  Init_Port();
  Init_ADC();
  Init_Uart();
  Init_WD();
  for(;;)
  {
    if (WDTIF)
    {
      unsigned int adc_value = 0;
      float adc_volta = 0;
      D5 = 1;
      ADCCON3 = (0x80|0x30|0x00);
      while (!(ADCCON1 & 0x80));
      adc_value = get_adc_value();
      adc_volta = adc_value_trans_volta(adc_value);
      Send(adc_value, adc_volta);
      D5 = 0;
      WDTIF = 0;
    }
  }
}