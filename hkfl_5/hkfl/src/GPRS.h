#ifndef __GPRS_H_
#define __GPRS_H_

#define CAB_NUM_LEN 6
#define HEAD_DATA 0xa5
#define TAIL_DATA 0x5a

/*指令类型定义*/
#define HEART_BEAT    'A'//心跳包
#define SENDER_CONFIRM     'B'//存包时运货员信息确认
#define SAVE_USER_INFO  'C'//存包时发送用户信息
#define GETOUT_USER_INFO 'D'//客户取包时的用户信息
#define RW_USER_INFO 'E'//读取或写入用户信息
#define RW_CAB_INFO 'F' //读取或写入柜子信息
#define SERVER_OPEN_BOX  'G'//远程开箱

/*SENDER_CONFIRM 数据部分 B*/
#define SENDER_ASK  '0'//请求操作权限
#define SENDER_OK  '1'//允许操作
#define SENDER_ERR '2'//不允许

#define SEND_ID_LEN 20
#define SEND_PSD_LEN 6

typedef struct 
{
	char flag;//标志
	char send_id[SEND_ID_LEN];//发货员ID号
	char send_psd[SEND_PSD_LEN];//发货员密码
}SENDER_INFO;

/*用户信息*/
/*箱子信息长度设置*/
#define GPRS_VIRTUAL_NUM_LENGTH 4 //虚拟箱号长度一般为4或2
#define GPRS_USER_PASSWORD_LENGTH 6 //用户密码长度
#define GPRS_SENDID_LENGTH  20	  //送货员的开箱信息长度
#define GPRS_USERID_LENGTH  10	  //取货人的信息长度
#define GPRS_USER_PHNUM_LENGTH 15//用户的手机号
#define GPRS_SEND_NUM_LENGTH 20//发货员ID号

#define GPRS_ADMIN_PSD_LENGTH 6

/*SAVE_USER_INFO 标志部分定义 C */
#define OPEN_ASK '0'
#define OPEN_OK '1'
#define OPEN_ERR '2'
#define GET_PACK_BACK '3'

/*GETOUT_USER_INFO 标志部分定义 D */
#define CLEAR_ASK '0'
#define CLEAR_OK '1'
#define CLEAR_ERR '2'

/*RW_USER_INFO RW_CAB_INFO 标志部分定义 E F*/
#define R_INFO '0'
#define W_INFO '1'
#define RW_OK '2'
#define RW_ERR '3'

/*重启标志部分定义 */
#define NON_RESTART '0'
#define RESTART '1'
#define SYS_START '2'//系统启动标志


/*SERVER_OPEN_BOX 标志部分定义 G*/
#define CLEAR_USER_INFO '0'
#define NON_CLEAR_USER_INFO '1'
#define SERVER_OPEN_OK '2'
#define SERVER_OPEN_ERR '3'


typedef struct
{
	char flag;
	char station_num[2];
	char virtualnumber[GPRS_VIRTUAL_NUM_LENGTH];//虚拟账号，一般2-4位 后面全用字符形式
	char type;//箱子型号 '1'小  '2'中  '3'大
	char status;    //箱子状态
	char send_id[GPRS_SENDID_LENGTH];//发货员使用的条码号
	char send_num[GPRS_SEND_NUM_LENGTH];//发货员编号
	char user_id[GPRS_USERID_LENGTH];//用户ID 该处为用户的条码号或IC卡号， 多的补0xff，空余的也补0xff
	char pass_word[GPRS_USER_PASSWORD_LENGTH];//用户密码 一般为6位
	char user_phnum[GPRS_USER_PHNUM_LENGTH];

}USER_INFO;

#define GPRS_CAB_NUM_LEN 6
typedef struct 
{
	unsigned char head[2];
	unsigned char comm_len[2];//指令长度，comm_len[0]*256+comm_len[1]
	char cabinet_num[GPRS_CAB_NUM_LEN];//柜子编号
	char comm_type;//指令类型	
}PACK_HEAD_INFO;

/*远程读取或设置柜子信息数据结构体*/
typedef struct
{
	char flag;//标志位
	char cabinet_num[GPRS_CAB_NUM_LEN];//柜子编号
	unsigned char box_num;//柜子的箱门数量
	char admin_psd[GPRS_ADMIN_PSD_LENGTH];//管理员密码
	char restart_flag;//重启标志
}CAB_INFO;

/*远程开箱指令结构体数据部分*/
typedef struct
{
	char flag;//标志
	char virtualnumber[GPRS_VIRTUAL_NUM_LENGTH];
}SERVER_OPEN_INFO;

PACK_HEAD_INFO ex_pack_head_msg;
int package_send_pack(unsigned char *sendbuf , unsigned char *cab_num ,char type , unsigned char *databuf , int data_len);
int confirm_sender(unsigned char *data_buf , unsigned char *send_num);
int package_user_data_pack(unsigned char *data_buf , unsigned char flag , BOX_MSG *box_info);
int save_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info);
//int confirm_save_pack(unsigned char *data_buf , BOX_MSG *box_info);
int getout_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info);
char rw_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info);
char rw_cab_server_back(unsigned char *data_buf , CAB_INFO *cab_msg);
char server_open_box_back(unsigned char *data_buf , SERVER_OPEN_INFO *server_open_msg , BOX_MSG *box_info);

#endif

