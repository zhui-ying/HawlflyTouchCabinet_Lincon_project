#ifndef __FLASH_H
#define __FLASH_H			    
#include <stm32f10x.h>

/*一个箱子占用5个扇区，第一个记录用户信息，后面4个记录4次历史信息*/
#define Sector           4096  //一个扇区有4K，对数据读写以扇区为单位
#define CAB_MSG_ADD   0	  //柜子信息地址
#define BOX_MSG_ADD	 Sector*5 //箱子信息地址，一个箱子占用一个sector的区域
#define H_RECORD_ADD(x)   BOX_MSG_ADD+(x)*Sector

void SPI_Flash_Init(void);	 //FLASH初始化
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //读取flash
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//写入flash

void SPI_Flash_Erase_Chip(void);    	  //整片擦除
void SPI_FLASH_Write_SR(u8 sr);  	//写状态寄存器
void SPI_FLASH_Write_Disable(void);	//写保护


//void SPI_Flash_PowerDown(void);           //进入掉电模式
//void SPI_Flash_WAKEUP(void);			  //唤醒
#endif
