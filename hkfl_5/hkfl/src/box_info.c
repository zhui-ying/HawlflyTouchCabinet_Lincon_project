#include "box_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEEK_SET 0//文件开头
#define SEEK_CUR 1//文件当前位置
#define SEEK_END 2//文件末尾

#define HISTOIRY_HEAD_LEN 1//历史文件包头数据长度
#define MAX_RECORD 200//最大记录个数
/*
function:箱子信息初始化
input: box_num 需要初始化的箱子个数 flag 开机时是否需要初始化 0 是 1 否
output: 0 初始化失败 1初始化成功
*/
unsigned char box_info_init(unsigned char box_num , unsigned char flag)
{
	BOX_MSG box_info;
	unsigned char count = 0;
	FILE *box_file;
	int write_count;
	
	if(flag == 1)
	return 1;//无需初始化，直接返回

	box_file = fopen("box_msg.dat","w+b");//以二进制形态新建文件
	fseek(box_file,0,SEEK_SET);//移动文件指针到首位
	if(box_file == NULL)
	return 0;

	memset(&box_info , 0xff , sizeof(BOX_MSG));
	box_info.type = BOX_TYPE_MIN;
	box_info.status = BOX_IDLE;
	memset(box_info.virtualnumber , '0' , VIRTUAL_NUM_LENGTH);//虚拟箱号先初始化为0
	for(count=0;count<box_num;count++)
	{
		box_info.station_num = count+1;
		box_info.station_port = count+1;
		box_info.virtualnumber[VIRTUAL_NUM_LENGTH-1] = (count+1)%10+'0';//写入个位
		box_info.virtualnumber[VIRTUAL_NUM_LENGTH-2] = (count+1)/10+'0';//写入个位
		write_count = fwrite((char *)&box_info ,  1 , sizeof(BOX_MSG) , box_file);//写入文件中
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//写入失败
		}
	}
	fclose(box_file);//关闭文件
	return 1;
	
}

/*
function: 根据排列号读取箱子信息
input: station_num 箱子排列号  box_info 需写入的箱子信息
output: 1 读取成功 0 读取失败
*/
unsigned char read_box_info_station_num(unsigned char station_num , BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//以二进制形态打开文件,可读可写
	if(NULL == box_file)
	return 0;
	if(0 != fseek(box_file , (station_num-1)*sizeof(BOX_MSG) , SEEK_SET))//移动文件指针到需要的位置
	{
		return 0;//读取失败
	}
	write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//将当前的信息直接读出到box_info中
	if(write_count != sizeof(BOX_MSG))
	{
		fclose(box_file);
		return 0;//读取失败
	}
	fclose(box_file);//关闭文件
	return 1;	
}

/*
function: 通过虚拟箱号读取箱子信息
input: virtualnumber  box_info 需写入的箱子信息
output: 1 读取成功 0 读取失败
*/
unsigned char read_box_info_virtualnumber(char *virtualnumber ,  BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//以二进制形态打开文件,可读可写
	if(NULL == box_file)
	return 0;

	while(1)//匹配读出来的信息，直到相等
	{
		write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//顺序读取
		if(0 == memcmp(virtualnumber , box_info->virtualnumber , VIRTUAL_NUM_LENGTH))
		{
			fclose(box_file);
			return 1;//匹配成功
		}
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//匹配失败，到末尾了
		}
	}
}

/*
function: 通过用户邋ID号读取箱子信息
input: user_ID 用户ID号 box_info 需写入的箱子信息
output: 1 读取成功 0 读取失败
*/
unsigned char read_box_info_user_id(char *user_ID ,  BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//以二进制形态打开文件,可读可写
	if(NULL == box_file)
	return 0;

	while(1)//匹配读出来的信息，直到相等
	{
		write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//顺序读取
		if((box_info->status == BOX_USED) && (0 == memcmp(user_ID , box_info->user_id, USERID_LENGTH)))
		{
			fclose(box_file);
			return 1;//匹配成功
		}
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//匹配失败，到末尾了
		}
	}
}

/*
function: 通过用户ID号读取箱子信息
input: user_ID 用户ID号 box_info 需写入的箱子信息
output: 1 读取成功 0 读取失败
*/
unsigned char read_box_info_pass_word(char *pass_word ,  BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//以二进制形态打开文件,可读可写
	if(NULL == box_file)
	return 0;

	while(1)//匹配读出来的信息，直到相等,只匹配已经分配过的箱子
	{
		write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//顺序读取
		if((box_info->status == BOX_USED) && (0 == memcmp(pass_word , box_info->pass_word, USER_PASSWORD_LENGTH)))
		{
			fclose(box_file);
			return 1;//匹配成功
		}
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//匹配失败，到末尾了
		}
	}
}

/*
function: 通过箱子状态读取箱子信息 ,可用于空箱搜索
input: status 箱子状态 box_info 需写入的箱子信息
output: 1 读取成功 0 读取失败
*/
unsigned char read_box_info_status(char status ,  BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//以二进制形态打开文件,可读可写
	if(NULL == box_file)
	return 0;

	while(1)//匹配读出来的信息，直到相等
	{
		write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//顺序读取
		if(box_info->status == status)
		{
			fclose(box_file);
			return 1;//匹配成功
		}
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//匹配失败，到末尾了
		}
	}
}

/*
function: 通过箱子状态读取箱子信息 ,可用于空箱搜索
input: status 箱子状态 type 箱子类型 box_info 需写入的箱子信息
output: 1 读取成功 0 读取失败
*/
unsigned char read_box_info_status_type(char status , char type , BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//以二进制形态打开文件,可读可写
	if(NULL == box_file)
	return 0;

	while(1)//匹配读出来的信息，直到相等
	{
		write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//顺序读取
		if((box_info->status == status) && (box_info->type == type))//同时满足两个条件
		{
			fclose(box_file);
			return 1;//匹配成功
		}
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//匹配失败，到末尾了
		}
	}
}

/*
function: 写入箱子信息
input: box_info 需写入的箱子信息
output: 1 读取成功 0 读取失败
*/
unsigned char write_box_info(BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//以二进制形态打开文件,可读可写
	if(NULL == box_file)
	return 0;
	fseek(box_file , (box_info->station_num-1)*sizeof(BOX_MSG) , SEEK_SET);//移动文件指针到需要的位置
	write_count = fwrite((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//将当前的信息直接读出到box_info中
	if(write_count != sizeof(BOX_MSG))
	{
		fclose(box_file);
		return 0;//写入失败
	}
	fclose(box_file);//关闭文件
	return 1;		
}

//历史记录初始化，建立文件，设置index值
unsigned char history_info_init(void)
{
	unsigned char index = 0;
	FILE *history_file;
	int write_count;


	history_file = fopen("history.dat","w+b");//以二进制形态新建文件
	fseek(history_file,0,SEEK_SET);//移动文件指针到首位
	if(history_file == NULL)
	return 0;
	write_count = fwrite(&index ,  1 , HISTOIRY_HEAD_LEN , history_file);//写入index值为0
	if(write_count != 1)
	{
		return 0;
	}
	fclose(history_file);
}

//写入某一个历史记录,index从1开始
unsigned char write_history_info(HISTORY_MSG *history_msg)
{
	FILE *history_file;
	int write_count;
	unsigned char index;

	history_file = fopen("history.dat","r+b");//以二进制形态打开文件,可读可写	
	if(history_file == NULL)
	{
		return 0;
	}
	fseek(history_file,0,SEEK_SET);//移动文件指针到首位
	write_count = fread(&index ,  1 , HISTOIRY_HEAD_LEN, history_file);//读取index值
	index++;
	if(index > MAX_RECORD)
	{
		index = 0;//若数据存储超过200个，则从头开始存，形成一个循环
	}
	history_msg->index = index;
	fseek(history_file,(HISTOIRY_HEAD_LEN + index*sizeof(HISTORY_MSG)),SEEK_SET);//移动文件指针到对应写入的位置
	write_count = fwrite((char *)history_msg ,  1 , sizeof(HISTORY_MSG) , history_file);//写入历史记录
	fseek(history_file,0,SEEK_SET);//移动文件指针到首位	
	write_count = fwrite(&index ,  1 , HISTOIRY_HEAD_LEN, history_file);//更新index
	fclose(history_file);
	return 1;
	
}

//读取某一个历史记录
unsigned char read_history_info(unsigned char time_index , HISTORY_MSG *history_msg)
{
	FILE *history_file;
	int write_count;
	unsigned char index;

	history_file = fopen("history.dat","r+b");//以二进制形态打开文件,可读可写	
	if(history_file == NULL)
	{
		return 0;
	}
	fseek(history_file,0,SEEK_SET);//移动文件指针到首位
	write_count = fread(&index ,  1 , HISTOIRY_HEAD_LEN, history_file);//读取index值	
	/*获取文件位置*/
	if(time_index <= index)
	{
		index = index-(time_index-1);//指向以前的记录
	}else
	{
		index = MAX_RECORD - (time_index -1 - index);
	}
	if(0 !=fseek(history_file,(HISTOIRY_HEAD_LEN + index*sizeof(HISTORY_MSG)),SEEK_SET))//移动文件指针到对应读取的位置
	{
		fclose(history_file);
		return 0;
	}
	write_count = fread((char *)history_msg ,  1 , sizeof(HISTORY_MSG) , history_file);//读取历史记录	
	if(history_msg->index != index)
	{
		fclose(history_file);
		return 0;		
	}
	fclose(history_file);
	return 1;
	
}

//获取历史记录条数
unsigned char read_history_count(void)
{
	FILE *history_file;
	int write_count;
	unsigned char index=0;
	HISTORY_MSG history_msg;
	
	if(1 == read_history_info(MAX_RECORD , &history_msg))
	{
		//查看最大记录出有没有记录
		return MAX_RECORD;//直接返回最大记录数
	}



	history_file = fopen("history.dat","r+b");//以二进制形态打开文件,可读可写	
	if(history_file == NULL)
	{
		return 0;
	}
	fseek(history_file,0,SEEK_SET);//移动文件指针到首位
	write_count = fread(&index ,  1 , HISTOIRY_HEAD_LEN, history_file);//读取index值	
	return index;//返回记录位置
	fclose(history_file);	
	
}


