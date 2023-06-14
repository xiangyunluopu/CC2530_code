#include <ioCC2530.h>
#include <stdio.h>

#define D3 P1_0
#define D4 P1_1

static unsigned int value = 0;

static unsigned char buff_str1[32] = { 0 };

static unsigned char count = 0;

void Set_Clock_32M(void); // 设置系统时钟频率为32M

void Init_Port(void);// 初始化D3 D4

void Init_ADC(void); // 配置P0_0为模拟通道，使能ADC中断与总中断

void Init_Uart0(void); // 发送

void Urat0_Send_str(char* str); // 发送字符串

void Uart0_Send_Char(unsigned char ch); // 发送字符

void Init_WD(void); // 初始化看门狗

#pragma vector = ADC_VECTOR
__interrupt void Service(void); // ADC服务函数，生成str,并发送

#pragma vector = WDT_VECTOR
__interrupt void Service_WDT(void); // 看门狗服务函数，count += 1,count == 3时，启动ADC转换
