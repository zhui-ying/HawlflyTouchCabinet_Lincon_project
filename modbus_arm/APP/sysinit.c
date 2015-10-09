#include "includes.h"


#if OS_CRITICAL_METHOD == 3u                 /* Allocate storage for CPU status register               */
    OS_CPU_SR  cpu_sr = 0u;
#endif

/*IC卡接收数据任务，通过邮箱IC_msgbuf传递信息*/
OS_EVENT *IC_box;
u8 IC_msgbuf[PC_MSG_SIZE];

/*条码，一旦接收到完整的条码,通过邮箱barcode_msgbuf传递用户信息*/
OS_EVENT *barcode_box;
char barcode_msgbuf[USER_MSG_SIZE];

/*modbus_rtu 数据接收和发送，一旦接收到数据，通过邮箱modbus_msgbox传递信息到任务中*/
OS_EVENT *modbus_box;
u8 modbus_msgbuf[MODBUS_MSG_SIZE];

/*发送箱子信息给开箱任务*/
OS_EVENT *open_box;//开箱任务开箱端口号邮箱

/*开箱结束信号*/
OS_EVENT *door_semp;

/*堆栈定义区*/
OS_STK pc_task_stk[PC_TASK_STK_SIZE];
OS_STK openbox_task_stk[OPENBOX_TASK_STK_SIZE];

/*
创建所有事件
*/
void CreatAllEvent(void)
{
	open_box = OSMboxCreate(0);
	door_semp = OSSemCreate(0);
	barcode_box = OSMboxCreate(0);
	IC_box = OSMboxCreate(0);
	modbus_box = OSMboxCreate(0);
}

/*
fuction:创建所有任务
*/
void CreatAllTask(void)
{
//	OSTaskCreate(pc_task,(void *)0,		  	
//	   &pc_task_stk[PC_TASK_STK_SIZE-1], PC_TASK_PRIO);
	OSTaskCreate(openbox_task,(void *)0,		  	
	   &openbox_task_stk[OPENBOX_TASK_STK_SIZE-1], OPENBOX_TASK_PRIO);
}

