#include "ioCC2530.h"

#define D3 P1_0

void Set_Clock_32M(void);
// ϵͳʱ��
void Init_WD(void);
// ���Ź�
void Init_Port(void);
// LED
void Init_ADC(void); 
// ADC_P0_0
void Init_Uart0(void); 
// Uart0_TX_P0_3
void Timing_2s(void); 
// 2�붨ʱ
int Get_value(void); 
// ��ȡADCֵ
void Mak_buff_str(int value,char* buff_str);
// ����str
void str_Send(char* str); 
// ����
void Send_str1(char* str);
// e,mmmmm