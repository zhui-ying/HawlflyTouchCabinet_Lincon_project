#ifdef _ADMIN_INFO_H
#define _ADMIN_INFO_H

#define ADMIN_ID_LENTH 10
#define ADMIN_PSD_LENTH 6

#define ADMIN_FLAG 'N' //为N表示未注册
//系统信息和管理员信息
typedef struct admin_info
{
	char cab_add[6];//柜子站号
	unsigned char box_num;//一个柜子箱子数量
	char init_flag;//初始化标志,为'1'，已经初始化 ，为其他值，未初始化
	char admin1;//管理员编号，为N表示未注册
	char admin1_id[ADMIN_ID_LENTH];//管理员ＩＤ卡号
	char admin1_psd[ADMIN_PSD_LENTH];//管理员密码
	char admin2;
	char admin2_id[ADMIN_ID_LENTH];//管理员ＩＤ卡号
	char admin2_psd[ADMIN_PSD_LENTH];//管理员密码
	char admin3;
	char admin3_id[ADMIN_ID_LENTH];//管理员ＩＤ卡号
	char admin3_psd[ADMIN_PSD_LENTH];//管理员密码	
}ADMIN_MSG;

unsigned char admin_init(void);//柜子和管理员信息初始化
unsigned char read_admin_info(ADMIN_MSG *admin_info);//读取系统信息
unsigned char write_admin_info(ADMIN_MSG *admin_info);//写入系统信息
unsigned char judge_admin_psd(char *password);//通过密码判断管理员是否正确
unsigned char judge_admin_id(char *admin_id);//通过ID卡号判断管理员是否正确

#endif
