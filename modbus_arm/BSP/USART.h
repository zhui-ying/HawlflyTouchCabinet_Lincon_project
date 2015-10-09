#ifndef	__USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

void USART1_Conf(u32 baudRate);
void PutChar(u8 Data);
void PutStr(u8 *str);
void PutNChar(u8 *buf , u16 size);
int fputc(int ch, FILE *f);
#endif
