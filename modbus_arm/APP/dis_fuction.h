#ifndef __DIS_FUCTION_H_
#define __DIS_FUCTION_H_
#include "functionList.h"
#include "date.h"

#define LCD_XSIZE 21//横着可以显示21个字符
#define LCD_YSIZE 4//竖着可以显示4行 
#define LCD_XSTART	7//一行菜单开始显示的位置

void DisplayFull(DIS_SING *pDisFull , u8 flag);
void DisplayMenu(FUN_BLOCK *phead ,FUN_BLOCK *ptail , FUN_BLOCK *pfunDisplay);
void Dis1LineMid(char *str , unsigned char y);
void DisplayTime(struct rtc_time *systmtime);
void MainDisplay(DIS_SING *pLCDAllTemp);
void GetTimeStr(char *timebuf , struct rtc_time *systmtime);

#endif
