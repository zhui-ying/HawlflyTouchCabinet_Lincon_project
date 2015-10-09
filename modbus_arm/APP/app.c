#include "includes.h"

u8 err;

void Task_Start(void *p_arg)
{
	u8 *modbus_buf;	
	CreatAllEvent();
	CreatAllTask();
	init_MODBUS();
    while (1)
    {
	   modbus_buf = OSMboxPend(modbus_box , 0 , &err);	//无限等待
	   function_MODBUS(modbus_buf , send_buf); //数据处理和发送
	   memset(modbus_msgbuf , 0 , MODBUS_MSG_SIZE);//清缓存
	   rec_num = 0;
	   rec_stat = PACK_START; //准备下一次接收
    }
}

/*与触摸屏通信的任务
void pc_task(void *p_arg)
{

}
*/
/*开箱任务，循环检测指定位，是否需要开箱*/
void openbox_task(void *p_arg)
{
 // BOX_MSG *box_msg = NULL;
  static int LED_count = 0;
  while(1)
  {
	if((1 == modbusAdd->send_comm_L) && (modbusAdd->station_num_L != 0))//有开箱指令产生
	{
//		unsigned char box_station_num;
		unsigned char box_port;
//		box_station_num = modbusAdd->station_num_L;
		box_port = modbusAdd->station_port_L-1;  //读取箱子相关信息
		modbusAdd->send_comm_L = 0;//置零，防止重复指令
		if(OPEN_STAT == UserOpenBox(box_port))
		{
			modbusAdd->back_comm_L = 1;//开箱成功返回
			modbusAdd->station_num_L = 0;			
		}
	}
	OSTimeDlyHMSM(0, 0, 0,10);	 //延时10ms检测一次
	/*运行灯闪烁*/
	LED_count++;
	if(LED_count  == 100)
	{
		LED1ON;
	}
	if(LED_count  == 200)
	{
		LED1OFF;
		LED_count = 0;
	}
  }
}

