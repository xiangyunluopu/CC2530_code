#include "XMF_DS18B20_CC2530.h"

//��������ʱ����
void Delay_OneWire(unsigned int t)
{
  while(t--);
}

//DS18B20оƬ��ʼ��
unsigned char Init_DS18B20(void)
{
  unsigned char initflag = 0;
  SetIOSel();
  SetOutput();
  DQ = 0;
  Delay_OneWire(800); 
  DQ = 1;
  Delay_OneWire(50); 
  SetInput();
  initflag = DQ;    
  Delay_OneWire(100);
  
  return initflag;
}

//ͨ����������DS18B20дһ���ֽ�
void Write_DS18B20(unsigned char dat)
{
  unsigned char i;
  SetOutput();
  for(i=0;i<8;i++)
  {
    DQ = 0;
    DQ = dat & 0x01;
    Delay_OneWire(50);
    DQ = 1;
    dat >>= 1;
  }
  Delay_OneWire(50);
}

//��DS18B20��ȡһ���ֽ�
unsigned char Read_DS18B20(void)
{
  unsigned char i;
  unsigned char dat;
  
  for(i=0; i<8; i++)
  {
    SetOutput();
    DQ = 0;
    dat >>= 1;
    DQ = 1;
    SetInput();
    if(DQ == 1)
    {
      dat |= 0x80;
    }	    
    Delay_OneWire(50);
  }
  return dat;
}