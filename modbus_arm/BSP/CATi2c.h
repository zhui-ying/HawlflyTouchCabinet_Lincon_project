/*-----------------------------------------------
  名称：IIC协议 头文件
------------------------------------------------*/  
#ifndef __CATI2C_H__
#define __CATI2C_H__  

#include "stm32f10x.h"

#define AddCATlock   0x40
#define AddCATdoor   0x48
#define AddCATstatus 0x44

#define GPIO_SDA  GPIOA
#define SDA_PIN  GPIO_Pin_0
#define GPIO_SCL  GPIOA
#define SCL_PIN  GPIO_Pin_1

/*扩展部分1*/
#define EXT1_AddCATlock1   0x40
#define EXT1_AddCATdoor1   0x48
#define EXT1_AddCATstatus1 0x44

#define EXT1_AddCATlock2   0x42
#define EXT1_AddCATdoor2   0x4a
#define EXT1_AddCATstatus2 0x46

#define EXT1_GPIO_SDA  GPIOG
#define EXT1_SDA_PIN  GPIO_Pin_13
#define EXT1_GPIO_SCL  GPIOG
#define EXT1_SCL_PIN  GPIO_Pin_14
/*扩展部分2*/
#define EXT2_AddCATlock1   0x40
#define EXT2_AddCATdoor1   0x48
#define EXT2_AddCATstatus1 0x44

#define EXT2_AddCATlock2   0x42
#define EXT2_AddCATdoor2   0x4a
#define EXT2_AddCATstatus2 0x46

#define EXT2_GPIO_SDA  GPIOG
#define EXT2_SDA_PIN  GPIO_Pin_8
#define EXT2_GPIO_SCL  GPIOG
#define EXT2_SCL_PIN  GPIO_Pin_9

extern u8 ack;

void WriteCATData(u8 add, u8 subadd ,u16 dat);//16位的数
u16 ReadCATData(u8 add);

void EXT1_WriteCATData(u8 add, u8 subadd ,u16 dat);//16位的数
u16 EXT1_ReadCATData(u8 add);

void EXT2_WriteCATData(u8 add, u8 subadd ,u16 dat);//16位的数
u16 EXT2_ReadCATData(u8 add);

void CAT955Init(void);


#endif
