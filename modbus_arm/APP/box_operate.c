/*
主要实现各个箱子的信息读取和存储以及开箱关箱操作
*/

#include "includes.h"
#include "flash.h"
#include "CATi2c.h"

/*读取箱子状态
输入箱子的排列号
*/
u8 ReadOneBox(u8 station_port)
{
	u16 temp;
	u8 position , port;
	port = station_port;//找出对应的端口
	position = port/16;
	switch(position)
	{
	case 0:
	temp = ReadCATData(AddCATdoor);
	temp = ReadCATData(AddCATdoor);//多读几次
	temp = temp & (0x0001<<port);
	break;

	case 1:
	temp = EXT1_ReadCATData(EXT1_AddCATdoor1);
	temp = EXT1_ReadCATData(EXT1_AddCATdoor1);//多读几次
	temp = temp & (0x0001<<(port-position*16));
	break;

	case 2:
	temp = EXT1_ReadCATData(EXT1_AddCATdoor2);
	temp = EXT1_ReadCATData(EXT1_AddCATdoor2);//多读几次
	temp = temp & (0x0001<<(port-position*16));
	break;

	case 3:
	temp = EXT2_ReadCATData(EXT2_AddCATdoor1);
	temp = EXT2_ReadCATData(EXT2_AddCATdoor1);//多读几次
	temp = temp & (0x0001<<(port-position*16));
	break;

	case 4:
	temp = EXT2_ReadCATData(EXT2_AddCATdoor2);
	temp = EXT2_ReadCATData(EXT2_AddCATdoor2);//多读几次
	temp = temp & (0x0001<<(port-position*16));
	break;
	default : return 0;
	}
	if(temp != 0)
	{
		return CLOSE_STAT;//	 3月31日修改 ,将CLOSE_STAT和OPEN_STAT位置对调
	}					  //
	else				  //
	{					  //
		return OPEN_STAT; //
	}
}

/*打开某个箱子，用于开箱任务中*/
void OpenOneDoor(u8 station_port)
{
	u8 boxPort;
	u16 temp;
	boxPort = station_port;
	if(boxPort<16)
	{
		temp = 0x0001<<boxPort;
		WriteCATData(AddCATlock,0x02,temp);//开某个箱子
		OSTimeDlyHMSM(0, 0, 0,OPEN_DOOR_TIME);	 //延时，待定
		WriteCATData(AddCATlock,0x02,0);//关某个箱子
	}
	if(boxPort>=16 && boxPort<32)
	{
		boxPort -= 16;
		temp = 0x0001<<boxPort;
		EXT1_WriteCATData(EXT1_AddCATlock1,0x02,temp);//开某个箱子
		OSTimeDlyHMSM(0, 0, 0,OPEN_DOOR_TIME);	 //延时，待定
		EXT1_WriteCATData(EXT1_AddCATlock1,0x02,0);//关某个箱子
	}
	if(boxPort>=32 && boxPort<48)
	{
		boxPort -= 32;
		temp = 0x0001<<boxPort;
		EXT1_WriteCATData(EXT1_AddCATlock2,0x02,temp);//开某个箱子
		OSTimeDlyHMSM(0, 0, 0,OPEN_DOOR_TIME);	 //延时，待定
		EXT1_WriteCATData(EXT1_AddCATlock2,0x02,0);//关某个箱子
	}
	if(boxPort>=48 && boxPort<64)
	{
		boxPort -= 48;
		temp = 0x0001<<boxPort;
		EXT2_WriteCATData(EXT2_AddCATlock1,0x02,temp);//开某个箱子
		OSTimeDlyHMSM(0, 0, 0,OPEN_DOOR_TIME);	 //延时，待定
		EXT2_WriteCATData(EXT2_AddCATlock1,0x02,0);//关某个箱子
	}
	if(boxPort>=64 && boxPort<80)
	{
		boxPort -= 64;
		temp = 0x0001<<boxPort;
		EXT2_WriteCATData(EXT2_AddCATlock2,0x02,temp);//开某个箱子
		OSTimeDlyHMSM(0, 0, 0,OPEN_DOOR_TIME);	 //延时，待定
		EXT2_WriteCATData(EXT2_AddCATlock2,0x02,0);//关某个箱子
	}
}

/*用户打开指定的箱子
返回 OPEN_STAT 打开成功
     CLOSE_STAT 打开失败
	 添加分多次等待，提高系统运行速度
*/
u8 UserOpenBox(u8 station_port)
{
	u8 count_open_time = 10;//分10次等待	WAIT_DOOR_TIME/
	OpenOneDoor(station_port);
	/*开箱完毕后再等一段时间*/
	while(count_open_time--)
	{
		 if(OPEN_STAT == ReadOneBox(station_port))
		 {
		 	break;
		 }
		 OSTimeDlyHMSM(0, 0, 0,WAIT_DOOR_TIME/10);
	}
	
	if(CLOSE_STAT == ReadOneBox(station_port))
	{
		return CLOSE_STAT;
	}
	return OPEN_STAT;
}



