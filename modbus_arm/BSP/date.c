/******************** (C) COPYRIGHT 2009 www.armjishu.com ************************
* File Name          : date.c
* Author             : www.armjishu.com Team
* Version            : V1.0
* Date               : 12/1/2009
* Description        : 日期相关函数
*******************************************************************************/
#include "date.h"

#define FEBRUARY		2
#define	STARTOFTIME		1970
#define SECDAY			86400L
#define SECYR			(SECDAY * 365)
#define	leapyear(year)		((year) % 4 == 0)
#define	days_in_year(a) 	(leapyear(a) ? 366 : 365)
#define	days_in_month(a) 	(month_days[(a) - 1])

struct rtc_time systmtime = {50,59,23,25,12,2012,0};

static int month_days[12] = {	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void RTC_Configuration(void)
{
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}

void RTC_BKPConfiguration(void)
{
	
  if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
  {
    /* Backup data register value is not correct or not yet programmed (when
       the first time the program is executed) */

    /* RTC Configuration */    
	  RTC_Configuration();
    /* Adjust time by values entred by the user on the hyperterminal */    
	 Time_Adjust(&systmtime);
    BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
  }
  else
  {
    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();  		
  }
}

/*
 * This only works for the Gregorian calendar - i.e. after 1752 (in the UK)
 */
void GregorianDay(struct rtc_time * tm)
{
	int leapsToDate;
	int lastYear;
	int day;
	int MonthOffset[] = { 0,31,59,90,120,151,181,212,243,273,304,334 };

	lastYear=tm->tm_year-1;

	/*
	 * Number of leap corrections to apply up to end of last year
	 */
	leapsToDate = lastYear/4 - lastYear/100 + lastYear/400;

	/*
	 * This year is a leap year if it is divisible by 4 except when it is
	 * divisible by 100 unless it is divisible by 400
	 *
	 * e.g. 1904 was a leap year, 1900 was not, 1996 is, and 2000 will be
	 */
	if((tm->tm_year%4==0) &&
	   ((tm->tm_year%100!=0) || (tm->tm_year%400==0)) &&
	   (tm->tm_mon>2)) {
		/*
		 * We are past Feb. 29 in a leap year
		 */
		day=1;
	} else {
		day=0;
	}

	day += lastYear*365 + leapsToDate + MonthOffset[tm->tm_mon-1] + tm->tm_mday;

	tm->tm_wday=day%7;
}

/* Converts Gregorian date to seconds since 1970-01-01 00:00:00.
 * Assumes input in normal date format, i.e. 1980-12-31 23:59:59
 * => year=1980, mon=12, day=31, hour=23, min=59, sec=59.
 *
 * [For the Julian calendar (which was used in Russia before 1917,
 * Britain & colonies before 1752, anywhere else before 1582,
 * and is still in use by some communities) leave out the
 * -year/100+year/400 terms, and add 10.]
 *
 * This algorithm was first published by Gauss (I think).
 *
 * WARNING: this function will overflow on 2106-02-07 06:28:16 on
 * machines were long is 32-bit! (However, as time_t is signed, we
 * will already get problems at other places on 2038-01-19 03:14:08)
 */
u32 mktimev(struct rtc_time *tm)
{
	if (0 >= (int) (tm->tm_mon -= 2)) {	/* 1..12 -> 11,12,1..10 */
		tm->tm_mon += 12;		/* Puts Feb last since it has leap day */
		tm->tm_year -= 1;
	}

	return (((
		(u32) (tm->tm_year/4 - tm->tm_year/100 + tm->tm_year/400 + 367*tm->tm_mon/12 + tm->tm_mday) +
			tm->tm_year*365 - 719499
	    )*24 + tm->tm_hour /* now have hours */
	  )*60 + tm->tm_min /* now have minutes */
	)*60 + tm->tm_sec; /* finally seconds */
}

void to_tm(u32 tim, struct rtc_time * tm)
{
	register u32    i;
	register long   hms, day;

	day = tim / SECDAY;
	hms = tim % SECDAY;

	/* Hours, minutes, seconds are easy */
	tm->tm_hour = hms / 3600;
	tm->tm_min = (hms % 3600) / 60;
	tm->tm_sec = (hms % 3600) % 60;

	/* Number of years in days */
	for (i = STARTOFTIME; day >= days_in_year(i); i++) {
		day -= days_in_year(i);
	}
	tm->tm_year = i;

	/* Number of months in days left */
	if (leapyear(tm->tm_year)) {
		days_in_month(FEBRUARY) = 29;
	}
	for (i = 1; day >= days_in_month(i); i++) {
		day -= days_in_month(i);
	}
	days_in_month(FEBRUARY) = 28;
	tm->tm_mon = i;

	/* Days are what is left over (+1) from all that. */
	tm->tm_mday = day + 1;

	/*
	 * Determine the day of week
	 */
	GregorianDay(tm);
}

void Time_Adjust(struct rtc_time * tm)	//设置时间
{
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
  /* Get time entred by the user on the hyperterminal */
  /* Get wday */
  GregorianDay(tm);
  /* Change the current time */
  RTC_SetCounter(mktimev(tm));
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}
