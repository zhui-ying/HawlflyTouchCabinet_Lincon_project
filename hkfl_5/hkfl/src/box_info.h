#ifndef __BOX_INFO_H_
#define __BOX_INFO_H_

//#define unsigned char uchar

/*箱子状态*/
#define BOX_IDLE	'0' //空闲
#define BOX_USED  '1'//已分配给用户或箱子里有物品
#define BOX_LOCK  '3'//锁定，不参与分配，只有管理员可以操作
#define BOX_OK_PC  '2' //返回上位机开机成功

/*箱子型号*/
#define BOX_TYPE_MIN '1'//小
#define BOX_TYPE_MID '2'//中
#define BOX_TYPE_MAX '3'//大

/*箱子信息长度设置*/
#define VIRTUAL_NUM_LENGTH 4 //虚拟箱号长度一般为4或2
#define USER_PASSWORD_LENGTH 6 //用户密码长度
#define SENDID_LENGTH  20	  //送货员的开箱信息长度
#define USERID_LENGTH  10	  //取货人的信息长度
#define USER_PHNUM_LENGTH 11//用户的手机号
#define SEND_NUM_LENGTH 10//发货员ID号

/*一个基本箱子的所有信息，所有对箱子的操作都基于此结构体进行*/
typedef struct box_msg
{
	unsigned char station_num;//箱子排列号 数值 从1开始
	unsigned char station_port;//箱子端口号 数值 从1开始
	char virtualnumber[VIRTUAL_NUM_LENGTH];//虚拟账号，一般2-4位 后面全用字符形式
	char type;//箱子型号 '1'小  '2'中  '3'大
	char status;    //箱子状态
	char user_id[USERID_LENGTH];//用户ID 该处为用户的条码号或IC卡号， 多的补0xff，空余的也补0xff
	char user_phnum[USER_PHNUM_LENGTH];
	char pass_word[USER_PASSWORD_LENGTH];//用户密码 一般为6位
	char send_num[SEND_NUM_LENGTH];//发货员编号
	char send_id[SENDID_LENGTH];//发货员使用的条码号
}BOX_MSG;

typedef struct history_msg
{
	unsigned char index;//0到200循环计数
	BOX_MSG box_info;//当前箱子信息
	unsigned long data_time;//当前时间
}HISTORY_MSG;

/*箱子信息相关所需的基本函数*/
unsigned char box_info_init(unsigned char box_num , unsigned char flag);//对箱子信息初始化
unsigned char read_box_info_station_num(unsigned char station_num , BOX_MSG *box_info);//根据排列号读取箱子信息
unsigned char read_box_info_virtualnumber(char *virtualnumber ,  BOX_MSG *box_info);//根据虚拟箱号读取信息
unsigned char read_box_info_user_id(char *user_id ,  BOX_MSG *box_info);//根据用户ID读取信息
unsigned char read_box_info_pass_word(char *pass_word ,  BOX_MSG *box_info);//根据用户密码读取信息
unsigned char read_box_info_status(char status ,  BOX_MSG *box_info);//根据箱子状态读取信息,可用于空箱搜索
unsigned char read_box_info_status_type(char status , char type , BOX_MSG *box_info);//根据箱子状态和类型读取信息,可用于空箱加类型搜索

unsigned char write_box_info(BOX_MSG *box_info);//写入某个箱子信息，可按照排列号搜索位置

/*历史记录相关所需基本函数*/
unsigned char history_info_init(void);//历史记录初始化，建立文件，设置index值
unsigned char read_history_info(unsigned char index , HISTORY_MSG *history_msg);//读取某一个历史记录
unsigned char write_history_info(HISTORY_MSG *history_msg);//写入某一个历史记录
unsigned char read_history_count(void);
#endif

