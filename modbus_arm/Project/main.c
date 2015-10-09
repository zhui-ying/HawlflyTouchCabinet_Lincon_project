/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名  ：main.c
 * 描述    ：板载的LED1、LED2、LED3、以固定的频率轮流闪烁（频率可调）。         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.0.0
 *
 * 作者    ：fire  QQ: 313303034 
 * 博客    ：firestm32.blog.chinaunix.net
**********************************************************************************/	

#include "includes.h"

static OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		  //定义栈


  
int main(void)
{ 
  	BSP_Init();	//底层硬件初始化
	OSInit();  //系统初始化
	OSTaskCreate(Task_Start,(void *)0,
	   &startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);  //创建启动函数

	OSStart();
    return 0;
 }

/******************* (C) COPYRIGHT 2011 野火嵌入式开发工作室 *****END OF FILE****/




