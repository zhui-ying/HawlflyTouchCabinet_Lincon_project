/*网络协议处理文件*/

#include "box_info.h"
#include "GPRS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
function:数据封装
input: sendbuf,需要被封装的发送包 ，cab_num柜子编号，type指令类型 databuf 需要封装的数据 data_len 数据长度
output:封装后的数据长度
*/
int package_send_pack(unsigned char *sendbuf , unsigned char *cab_num ,char type , unsigned char *databuf , int data_len)
{
	//int pack_len;//包长度
	int i;
	/*添加包头*/
	sendbuf[0] = 0xa5;
	sendbuf[1] = 0xa5;
	sendbuf[2] = (data_len+8)>>8;
	sendbuf[3] = (data_len+8)%256;//指令长度
	memcpy(&sendbuf[4] , cab_num , 6);//柜子编号
	sendbuf[10] = type;//指令类型
	memcpy(&sendbuf[11] , databuf , data_len);
	sendbuf[11+data_len] = 0;
	for(i=4;i<11+data_len;i++)//校验值
	{
		sendbuf[11+data_len] += sendbuf[i];
	}
	sendbuf[12+data_len] = 0x5a;
	sendbuf[13+data_len] = 0x5a;
	return 14+data_len;
}

/*function:涉及用户操作的数据部分打包操作
input: data_buf 需要存入的buf flag标志，根据具体指令会不同  box_info 箱子相关数据包 
output: 数据包长度
*/
int package_user_data_pack(unsigned char *data_buf , unsigned char flag , BOX_MSG *box_info)
{
	USER_INFO *user_msg;
	int buf_len = sizeof(USER_INFO);

	memset(data_buf , 0xff , buf_len);//多的部分默认为0xff
	
	user_msg = (USER_INFO *)data_buf;

	user_msg->flag = flag;
	memcpy(user_msg->pass_word,box_info->pass_word,USER_PASSWORD_LENGTH);
	memcpy(user_msg->send_id , box_info->send_id,SENDID_LENGTH);
	memcpy(user_msg->send_num , box_info->send_num,SEND_NUM_LENGTH);
	user_msg->station_num[0] = box_info->station_num/10 + '0';
	user_msg->station_num[1] = box_info->station_num%10 + '0';
	memcpy(user_msg->user_id,box_info->user_id,USERID_LENGTH);
	user_msg->status = box_info->status;
	user_msg->type = box_info->type;
	memcpy(user_msg->virtualnumber,box_info->virtualnumber,VIRTUAL_NUM_LENGTH);
	memcpy(user_msg->user_phnum,box_info->user_phnum,USER_PHNUM_LENGTH);

	return buf_len;
}
/*function:卡号确认函数
input: data_buf 该指令数据部分，send_num 运货员卡号，需要填充
output: 1 确认成功 0 确认失败
*/
int confirm_sender(unsigned char *data_buf , unsigned char *send_num)
{
	SENDER_INFO *sender_msg;
	sender_msg = (SENDER_INFO *)data_buf;
	if(sender_msg->flag == SENDER_OK)
	{
		memcpy(send_num , sender_msg->send_id , SEND_NUM_LENGTH);
		return 1;
	}
	return 0;
	
}

/*function:存物时后台返回用户数据解析
input:data_buf 该指令数据部分 box_info 箱子相关数据包
*/
int save_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info)
{
	USER_INFO *user_msg;
	user_msg = (USER_INFO *)data_buf;
	if(user_msg->flag != OPEN_OK)//不允许开箱
	{
		return 0;
	}
	box_info->station_num = (user_msg->station_num[0]-'0')*10 + user_msg->station_num[1]-'0';
	read_box_info_station_num(box_info->station_num , box_info);//读取所有信息
	memcpy(box_info->pass_word,user_msg->pass_word,USER_PASSWORD_LENGTH);
	memcpy(box_info->send_id , user_msg->send_id,SENDID_LENGTH);
	memcpy(box_info->send_num ,user_msg ->send_num,SEND_NUM_LENGTH);
	box_info->station_num = (user_msg->station_num[0]-'0')*10 + user_msg->station_num[1]-'0';
	memcpy(box_info->user_id,user_msg->user_id,USERID_LENGTH);
	box_info->status = user_msg->status;
	box_info->type = user_msg->type;
	memcpy(box_info->virtualnumber,user_msg->virtualnumber,VIRTUAL_NUM_LENGTH);
	memcpy(box_info->user_phnum,user_msg->user_phnum,USER_PHNUM_LENGTH);	
	return 1;
}

/*
function:用户取包时服务器返回信息，确定是否清除信息，清除用户信息方式为box_info相关信息全为ff
input: data_buf 服务器返回的数据包  box_info 需要被填充的箱子信息
output: 1 清除用户信息 0 保留用户信息
*/
int getout_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info)
{
	USER_INFO *user_msg;
	user_msg = (USER_INFO *)data_buf;
	box_info->station_num = (user_msg->station_num[0]-'0')*10 + user_msg->station_num[1]-'0';
	read_box_info_station_num(box_info->station_num , box_info);//读取所有信息
	if(user_msg->flag == CLEAR_OK)//清除所有用户信息
	{
		box_info->status = BOX_IDLE;
		memset(box_info->pass_word , 0xff , USER_PASSWORD_LENGTH);
		memset(box_info->send_id , 0xff , SENDID_LENGTH);
		memset(box_info->send_num , 0xff , SENDID_LENGTH);
		memset(box_info->user_id , 0xff , USERID_LENGTH);
		memset(box_info->user_phnum , 0xff , USER_PHNUM_LENGTH);
		return 1;
	}else
	{return 0;}
}

/*
function:远程读取或设置用户指令执行函数,读取指令则根据排列号读取相应的箱子信息，写入到箱子结构体中，
         写入指令则根据数据包信息，修改箱子信息，并存储
input: data_buf 服务器返回的数据包  box_info 需要被填充的箱子信息
output: 返回的标志位 RW_OK 操作成功 RW_ERR 操作失败
*/
char rw_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info)
{
	USER_INFO *user_msg;
	user_msg = (USER_INFO *)data_buf;

	box_info->station_num = (user_msg->station_num[0]-'0')*10 + user_msg->station_num[1]-'0';
	if(0 == read_box_info_station_num(box_info->station_num , box_info))//读取所有信息
	{
		return RW_ERR;
	}
	
	if(user_msg->flag == R_INFO)//读取用户信息
	{
		return RW_OK;
	}
	if(user_msg->flag == W_INFO)//写入用户信息
	{
		memcpy(box_info->pass_word,user_msg->pass_word,USER_PASSWORD_LENGTH);
		memcpy(box_info->send_id , user_msg->send_id,SENDID_LENGTH);
		memcpy(box_info->send_num ,user_msg ->send_num,SEND_NUM_LENGTH);
		box_info->station_num = (user_msg->station_num[0]-'0')*10 + user_msg->station_num[1]-'0';
		memcpy(box_info->user_id,user_msg->user_id,USERID_LENGTH);
		box_info->status = user_msg->status;
		box_info->type = user_msg->type;
		memcpy(box_info->virtualnumber,user_msg->virtualnumber,VIRTUAL_NUM_LENGTH);
		memcpy(box_info->user_phnum,user_msg->user_phnum,USER_PHNUM_LENGTH);	
		
		write_box_info(box_info);//存储新用户信息
		return RW_OK;
	}
	return RW_ERR;
}

/*
function:远程读取或设置用户信息指令执行函数,读取指令则读取柜子信息到cab_msg，写入指令则更新,需要在脚本中更新系统信息
input: data_buf 服务器返回的数据包  cab_msg 需要被填充的柜子信息，在传入参数前已经读取了系统信息
output: 返回的标志位 RW_OK 操作成功 RW_ERR 操作失败
*/
char rw_cab_server_back(unsigned char *data_buf , CAB_INFO *cab_msg)
{
	CAB_INFO *cab_msgtemp;
	cab_msgtemp = (CAB_INFO *)data_buf;
	if(cab_msgtemp->flag == R_INFO)//读取用户信息
	{
		cab_msg->flag = RW_OK;
		cab_msg->restart_flag = cab_msgtemp->restart_flag;
		return RW_OK;
	}
	if(cab_msgtemp->flag == W_INFO)//写入用户信息
	{
		memcpy((char *)cab_msg , data_buf , sizeof(CAB_INFO));//复制数据包信息
		cab_msg->flag = RW_OK;	
		return RW_OK;
	}
	cab_msg->flag = RW_ERR;
	return RW_ERR;
		
}

/*
function:远程开箱，并根据指令对箱子信息操作
input: data_buf 服务器返回的数据包  server_open_msg与该指令相关的结构体,box_info 箱子信息
output: 返回的标志位 SERVER_OPEN_OK 操作成功 SERVER_OPEN_ERR 操作失败
*/
char server_open_box_back(unsigned char *data_buf , SERVER_OPEN_INFO *server_open_msg , BOX_MSG *box_info)
{
	memcpy((unsigned char *)server_open_msg , data_buf , sizeof(SERVER_OPEN_INFO));

	if(0 == read_box_info_virtualnumber(server_open_msg->virtualnumber ,  box_info))
	{
		server_open_msg->flag = SERVER_OPEN_ERR;
		return SERVER_OPEN_ERR;
	}
	if(server_open_msg->flag == CLEAR_USER_INFO)//清除用户信息
	{
		box_info->status = BOX_IDLE;
		memset(box_info->pass_word , 0xff , USER_PASSWORD_LENGTH);
		memset(box_info->send_id , 0xff , SENDID_LENGTH);
		memset(box_info->send_num , 0xff , SENDID_LENGTH);
		memset(box_info->user_id , 0xff , USERID_LENGTH);
		memset(box_info->user_phnum , 0xff , USER_PHNUM_LENGTH);
		write_box_info(box_info);//存储新用户信息
		server_open_msg->flag = SERVER_OPEN_OK;
		return SERVER_OPEN_OK;		
	}
	if(server_open_msg->flag == NON_CLEAR_USER_INFO)
	{
		server_open_msg->flag = SERVER_OPEN_OK;
		return SERVER_OPEN_OK;
	}
	server_open_msg->flag = SERVER_OPEN_ERR;
	return SERVER_OPEN_ERR;
}
