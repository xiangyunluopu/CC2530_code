#ifndef XMF_DS18B20_H
#define XMF_DS18B20_H

#include "ioCC2530.h"

#define OW_SKIP_ROM 0xcc
#define DS18B20_CONVERT 0x44
#define DS18B20_READ 0xbe

//DAT���Ŷ��壬������ֲʱ�谴ʵ������޸�
#define DQ P0_1
#define SetIOSel() P0SEL &= ~0x02
#define SetInput() P0DIR &= ~0x02
#define SetOutput() P0DIR |= 0x02


//��������
void Delay_OneWire(unsigned int t);
void Write_DS18B20(unsigned char dat);
unsigned char Init_DS18B20(void);
unsigned char Read_DS18B20(void);
#endif