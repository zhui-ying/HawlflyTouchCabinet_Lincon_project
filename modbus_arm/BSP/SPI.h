#ifndef __SPI_H
#define __SPI_H
#include "stm32f10x.h"

// SPI总线速度设置 
#define SPI_SPEED_2   0
#define SPI_SPEED_8   1
#define SPI_SPEED_16  2
#define SPI_SPEED_256 3
						  	    													  
void SPIx_Init(void);			 //初始化SPI口
u8 SPIx_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
		 
#endif
