#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*******************设置任务优先级*******************/
#define STARTUP_TASK_PRIO   0
#define USER_TASK_PRIO      3	//用户外围模块
#define KEYVALUE_TASK_PRIO  2	//键值
#define OPENBOX_TASK_PRIO   4 //	开箱
#define TIME_TASK_PRIO      6	//时间
#define PC_TASK_PRIO   	    1	  //上位机任务
#define DISPLAY_TASK_PRIO	 5	//显示任务

/************设置栈大小（单位为 OS_STK ）************/
#define STARTUP_TASK_STK_SIZE   128 
#define USER_TASK_STK_SIZE      128	//用户
#define KEYVALUE_TASK_STK_SIZE  128	//键值
#define TIME_TASK_STK_SIZE      128	//时间
#define PC_TASK_STK_SIZE        128	//打印机
#define OPENBOX_TASK_STK_SIZE   128 //	时间 
#define DISPLAY_TASK_STK_SIZE   128//显示

#endif

