/*
基本命令格式
leading sign(2Byte) + Command length(2 Byte) + ID(6Byte)
 + command type(1Byte) + command data(n) + overflag(1Byte)

leading sign = 0xA5A5,命令的前导标识
overflag = 0x40
command length= 6(ID) +1(command type)+n (com mand data)+1(overflag)

*/
#include "PC_MCU.h"
#include "IC_PC_MCU.h"
#include "functionList.h"

#include "box_operate.h"
#include "BSP.h"
#include "UART485.h"
#include "sysinit.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*中断接收函数*/
void PCInt(u8 data)
{
	static u8 Recvbegin = 0,count=0;
	static u16 length=0;
	pc_msgbuf[count++] = data;
	if(Recvbegin == 0)
	{
		if(count == 1 && pc_msgbuf[0] != HEAD1)//判断头1
		{
			count = 0;
			return;
		}
	
		if(count == 2 && pc_msgbuf[1] != HEAD2)	//判断头2 
		{
			count = 0;
			return;
		}
	
		if(count == 4) //计算长度
		{
			length = ((u16)pc_msgbuf[2]<<8) + pc_msgbuf[3] + 4;
			if(length > PC_MSG_SIZE)
			{
				count = 0;
				return;				
			}
			Recvbegin = 1;
		}
	}

	if((count >= length) && (1 == Recvbegin))
	{
		OSMboxPost(pc_box , pc_msgbuf);// 发送邮箱
		PCIntDisable();
		Recvbegin = 0;
		count = 0;
	}
}

/*取得ＩＤ号*/
void GetCabID(u8 *buf)
{
	CAB_MSG cab_msg;
	ReadCabinetMsg(&cab_msg);
	memcpy(buf , cab_msg.cab_station_num , 6);	
}

/*根据格式封装包，并发送
input: send_data 需要发送的数据 ， type 指令类型 ，数据包大小
*/
void ClosePack(u8 *send_data , u8 type , u16 size)
{
	u8 *sendBuf;
	HEAD_BLOCK *head_msg;
	sendBuf = malloc(size + sizeof(HEAD_BLOCK) + 10);//获取内存
	head_msg = (HEAD_BLOCK *)sendBuf;//类型转换
	/*加入头*/
	head_msg->head1 = HEAD1;
	head_msg->head2 = HEAD2;
	/*加入长度*/
	head_msg->length[0] = (u8)((size + sizeof(HEAD_BLOCK) - 3)/256);
	head_msg->length[1] = (u8)((size + sizeof(HEAD_BLOCK) - 3)%256);
	/*加入ID号*/
	GetCabID(head_msg->cabID);
	/*加入指令类型*/
	head_msg->type = type;
	/*加入数据*/
	memcpy(sendBuf + sizeof(HEAD_BLOCK) , send_data , size);
	/*加入结束符*/
	sendBuf[sizeof(HEAD_BLOCK) + size] = OVER_FLAG;

	/*开始发送数据*/
	PutNChar(sendBuf , sizeof(HEAD_BLOCK) + size + 1);
	free(sendBuf); //释放内存
}

/*解析包，判断接收到的包是否正确
正确返回 指令类型 错误 返回0
*/
u8 OpenPack(u8 *rec_buf)
{
	HEAD_BLOCK *head_msg;
	u16 length;
	u8 IDbuf[6];
	head_msg = (HEAD_BLOCK *)rec_buf;
	GetCabID(IDbuf);
	/*比较柜子ID号*/
	if(0 != memcmp(IDbuf , head_msg->cabID , 6))
	{
		return 0;
	}

	/*检查结束符*/
	length = (((u16)(head_msg->length[0]))<<8) + head_msg->length[1]+4;
	if(OVER_FLAG != rec_buf[length-1])
	{
		return 0;	
	}
	/*返回指令类型*/
	return head_msg->type;
}

/*
发送用户数据指令,发送flash内相应的信息
input: 箱子编号
*/
void PCSendUserData(u8 station_num)
{
	BOX_MSG box_msg;
	PACK_BLOCK pack_msg;

	memset((char *)&pack_msg , 0xff , sizeof(PACK_BLOCK));//先全部填充0xff，方便填充多余数据
	box_msg.station_num = station_num;
	ReadOneBoxMsg(&box_msg);
	/*写入箱子排列号*/
	sprintf(pack_msg.station_num , "%02d" , station_num);
	/*写入虚拟箱号*/
	memcpy(pack_msg.virtualnumber , box_msg.virtualnumber , VIRTUAL_NUM_LENGTH);
	/*写入状态*/
	pack_msg.status = box_msg.status;
	/*写入条码号*/
	memcpy(pack_msg.barcode , box_msg.send_id0 , SENDID_LENGTH);
	/*写入客户ＩＤ*/
	memcpy(pack_msg.userID , box_msg.user_id , USERID_LENGTH);
	/*写入客户密码*/
	memcpy(pack_msg.userPassWord , box_msg.pass_word , USER_PASSWORD_LENGTH);

	/*封装发送*/
	ClosePack((u8 *)(&pack_msg) , USER_DATA , sizeof(PACK_BLOCK));
}

/*
接收到用户数据后的处理 ，存入flash
根据协议，需要修改用户数据
*/
void PCRecvUserData(u8 *databuf)
{
	PACK_BLOCK *pack_msg;
	BOX_MSG box_msg;
	/*将网络数据包指针指向buf，便于取得信息，将网络数据包和用户信息包隔离开来*/
	pack_msg = (PACK_BLOCK *)databuf;
	box_msg.station_num = (pack_msg->station_num[0]-'0')*10 + pack_msg->station_num[1]-'0';
	ReadOneBoxMsg(&box_msg);
	/*只对分配过的箱子修改*/
	if(box_msg.status != BOX_USED)
	{
		return;
	}
	/*修改客户ID*/	
	memcpy(box_msg.user_id , pack_msg->userID , USERID_LENGTH);
	/*修改客户密码*/
	memcpy(box_msg.pass_word , pack_msg->userPassWord , USER_PASSWORD_LENGTH);
	/*写入flash*/
	WriteOneBoxMsg(&box_msg);
}

/*
接收到PC_COMM 类型指令后的处理，目前只有上位机开箱指令
开过之后需清除用户数据
*/
void PC_MCUComm(u8 *databuf)
{
	PACK_BLOCK *pack_msg;
	BOX_MSG box_msg;

	pack_msg = (PACK_BLOCK *)databuf;
	box_msg.station_num = (pack_msg->station_num[0]-'0')*10 + pack_msg->station_num[1]-'0';
	ReadOneBoxMsg(&box_msg);
	/*判断是否开箱*/
	if(pack_msg->status == BOX_USED) 
	{
		/*打开对应的箱子*/
		if(CLOSE_STAT == UserOpenBox(&box_msg))
		{
			/*开箱失败*/
			pack_msg->status = BOX_IDLE;
		}
		else								  //
		{  //开箱成功						  //   3月31日修改，开箱成功后返回 BOX_OK_PC
			pack_msg->status = BOX_OK_PC;	  //
		}									  //
		/*写入条码号*/
		memcpy(pack_msg->barcode , box_msg.send_id0 , SENDID_LENGTH);
		/*写入客户ＩＤ*/
		memcpy(pack_msg->userID , box_msg.user_id , USERID_LENGTH);
		/*写入客户密码*/
		memcpy(pack_msg->userPassWord , box_msg.pass_word , USER_PASSWORD_LENGTH);			
		/*封装发送*/
		ClosePack((u8 *)(pack_msg) , PC_COMM , sizeof(PACK_BLOCK));
		/*清空该箱*/
		if(pack_msg->status == BOX_OK_PC)
		{
			box_msg.status = BOX_IDLE;
			pboxStatus[box_msg.station_num] = BOX_IDLE;
			WriteOneBoxMsg(&box_msg);

//			pfunBlock = mainFunBlock;
//			OSMboxPost(display_box , pfunBlock);// 发送邮箱,刷新显示
		}
	}
}


/*下位机开机启动指令，一般不用*/
void PCSysPowerOn(void)
{
  char *buf = "ON OK";
	/*封装发送*/
	ClosePack((u8 *)buf , POWER_ON , strlen(buf));
}

