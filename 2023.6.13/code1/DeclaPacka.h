#include "ioCC2530.h"

#define D3 P1_0

void Set_Clock_32M(void);
// 系统时钟
void Init_WD(void);
// 看门狗
void Init_Port(void);
// LED
void Init_ADC(void); 
// ADC_P0_0
void Init_Uart0(void); 
// Uart0_TX_P0_3
void Timing_2s(void); 
// 2秒定时
int Get_value(void); 
// 获取ADC值
void Mak_buff_str(int value,char* buff_str);
// 生成str
void str_Send(char* str); 
// 发送
void Send_str1(char* str);
// e,mmmmm