#ifndef __SYSINIT_H_
#define __SYSINIT_H_
#include  "ucos_ii.h"

#define USER_MSG_SIZE  25//用户信息输入的大小暂定为25
#define PC_MSG_SIZE  100
#define MODBUS_MSG_SIZE 100	

/*上位机接收数据任务，通过邮箱pc_msgbuf传递信息*/
extern OS_EVENT *IC_box;
extern u8 IC_msgbuf[PC_MSG_SIZE];

/*条码，一旦接收到完整的条码,通过邮箱barcode_msgbuf传递用户信息*/
extern OS_EVENT *barcode_box;
extern char barcode_msgbuf[USER_MSG_SIZE];

/*modbus_rtu 数据接收和发送，一旦接收到数据，通过邮箱modbus_msgbox传递信息到任务中*/
extern OS_EVENT *modbus_box;
extern u8 modbus_msgbuf[MODBUS_MSG_SIZE];

/*发送箱子信息给开箱任务*/
extern OS_EVENT *open_box;//开箱任务开箱端口号邮箱

/*开箱结束信号*/
extern OS_EVENT *door_semp;

/*堆栈定义区*/
extern OS_STK pc_task_stk[PC_TASK_STK_SIZE];
extern OS_STK openbox_task_stk[OPENBOX_TASK_STK_SIZE];

void CreatAllTask(void);
void CreatAllEvent(void);
#endif

