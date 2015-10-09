#ifndef __UART485_H_
#define __UART485_H_
#include "stm32f10x.h"

void GPRS_UART485_init(u32 baudRate);
void PutNChar(u8 *buf , u16 size);
void delay10ms(void);
void PutChar(u8 Data);
#endif
