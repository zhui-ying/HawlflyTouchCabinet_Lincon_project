#ifndef __DATA_H_
#define __DATA_H_

#include "stm32f10x.h"

struct rtc_time {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
};

/*全局变量显示*/
extern struct rtc_time systmtime;

void RTC_Configuration(void);
void RTC_BKPConfiguration(void);
    
void GregorianDay(struct rtc_time * tm);
uint32_t mktimev(struct rtc_time *tm);
void to_tm(uint32_t tim, struct rtc_time * tm);
void Time_Adjust(struct rtc_time * tm);

#endif
