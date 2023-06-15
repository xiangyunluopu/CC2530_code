#include "ioCC2530.h"

#define D4 P1_1
#define D6 P1_4

#define D4_open 0xA1
#define D4_closed 0xA2
#define D6_open 0xB1
#define D6_closed 0xB2

void Set_Clock_32M(void);
void Init_Port(void);
void Init_Uart(void);
void Uart0_Send_Str(char* str);
void Uart0_Send_Data(char data);

void main(void)
{
  Set_Clock_32M();
  Init_Port();
  Init_Uart();
  for(;;)
  {
    
  }
}
#pragma vector = URX0_VECTOR
__interrupt void Service_URX0(void)
{
  char cmd = U0DBUF;
  switch (cmd)
  {
  case D4_open:
    D4 = 1;
    Uart0_Send_Str("D4 is open!\n");
    break;
  case D4_closed:
    D4 = 0;
    Uart0_Send_Str("D4 is closed!\n");
    break;
  case D6_open:
    D6 = 1;
    Uart0_Send_Str("D6 is open!\n");
    break;
  case D6_closed:
    D6 = 0;
    Uart0_Send_Str("D6 is closed!\n");
    break;
  default:
    Uart0_Send_Str("ERROR!!!\n");
    break;
  }
  URX0IF = 0; //虽然在此程序中没什么意义写上加深印象
}

void Uart0_Send_Str(char* str)
{
  while (*str != '\0')
  {
    Uart0_Send_Data(*str++);
  }
}

void Uart0_Send_Data(char data)
{
  while (!UTX0IF);
  UTX0IF = 0;
  U0DBUF = data;
}

void Init_Uart(void)
{
  EA = 1;
  PERCFG &= ~0x01; // 0000 1100
  P0SEL |= 0x0C;
  U0BAUD = 59;
  U0GCR = 8;
  U0UCR |= 0x80;
  U0CSR |= 0xC0;
  URX0IE = 1;
  URX0IF = 0;
  UTX0IF = 1; // 初始化为一
}

void Init_Port(void)
{// 0001 0010
  P1SEL &= ~0x12;
  P1DIR |= 0x12;
  P1 &= ~0x12;
}

void Set_Clock_32M(void)
{
  CLKCONCMD &= ~0x40;
  while (CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x07;
}