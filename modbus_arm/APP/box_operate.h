#ifndef __BOX_OPERATE_H_
#define __BOX_OPERATE_H_

#include "stm32f10x.h"

#define CLOSE_STAT       1//箱子关
#define OPEN_STAT        0//箱子开
#define WAIT_DOOR_TIME  700//等待箱子完全打开时间，开箱时间和等待时间加起来就是开箱反应时间, 最大９９９
#define OPEN_DOOR_TIME 700//开箱时间700ms，即电流延时时间

u8 ReadOneBox(u8 station_port);

void OpenOneDoor(u8 station_port);
u8 UserOpenBox(u8 station_port);

#endif
