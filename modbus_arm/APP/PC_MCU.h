#ifndef __PC_MCU_H_
#define __PC_MCU_H_

#include "user_cfg.h"

/*指令格式定义*/
#define HEAD1 0xa5
#define HEAD2 0xa5

#define OVER_FLAG 0x40

/*数据指令类型定义*/
#define POWER_ON  'A'
#define USER_DATA 'B'
#define PC_COMM   'C'

/*指令头部格式*/
typedef struct HEAD_Block{
	unsigned char head1;
	unsigned char head2;	//指令头
	unsigned char length[2];//数据长度 = length[0]<<8 + length[1];
	unsigned char cabID[6]; //柜子编号，最后几位有效
	unsigned char type;//指令类型
}HEAD_BLOCK;

/*指令数据包格式*/
#if !GUANG_DONG_MOD
typedef struct pack_block{
	char station_num[2];      //（2Byte）箱子排列号
	char virtualnumber[VIRTUAL_NUM_LENGTH];     //（VIRTUAL_NUM_LENGTH Byte）虚拟箱号
	char status;             //箱子状态（'1' 存物  '0' 取物 ）
	char barcode[SENDID_LENGTH];        //条码号（送货员）
	char userID[USERID_LENGTH];         //ID号（客户）
	char userPassWord[USER_PASSWORD_LENGTH];//用户密码
}PACK_BLOCK;
#else
typedef struct pack_block{
	char station_num[2];      //（2Byte）箱子排列号
	char virtualnumber[VIRTUAL_NUM_LENGTH];     //（VIRTUAL_NUM_LENGTH Byte）虚拟箱号
	char status;             //箱子状态（'1' 存物  '0' 取物 ）
	char barcode[GUANG_DONG_SENDID_LENGTH];        //条码号（送货员）
	char userID[GUANG_DONG_USERID_LENGTH];         //ID号（客户）
	char userPassWord[USER_PASSWORD_LENGTH];//用户密码
}PACK_BLOCK;

#endif

unsigned char OpenPack(unsigned char *rec_buf);
void PCSendUserData(unsigned char station_num);
void PCRecvUserData(unsigned char *databuf);
void PCSysPowerOn(void);
void PC_MCUComm(unsigned char *databuf);

#endif

