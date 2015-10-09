#ifndef __KEYBOARF_H
#define __KEYBOARF_H	

#include "stm32f10x.h"

#define GETIN   10
#define GETOUT  11 
#define KEYUP   12
#define KEYDOWN 13
#define CANCEL  14
#define ENTER   15

//矩阵键盘4*4 IO端口初始化，列线上拉输入
void Key44Port_Init(void);
//矩阵键盘4*4扫描程序，有按键时返回1，否则返回0
uint16_t Key44_Scan(void);
//获取矩阵键盘4*4的键值函数
uint16_t GetKey44val(void);
u16 GetKeyValue(void);

#endif
