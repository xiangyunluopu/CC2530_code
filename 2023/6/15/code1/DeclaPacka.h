#include <ioCC2530.h>
#include <stdio.h>

#define D3 P1_0

void Set_Clock_32M(void); // 设置32M系统时钟

void Init_Port(void); // 初始化要用的D3灯

void Init_Uart0(void); // 初始化UART0，用于发送

void Init_WD(void); // 看门狗初始化为定时器模式定时间隔一秒

__interrupt void Service_WDT(void); // 看门狗中断服务函数

void Uart0_Send_str(char* str); // uart0发送字符串

void Uart0_Send_dat(unsigned char ch); // uart0发送字符