/*
函数功能配置文件，根据注释修改对应的宏定义，标注对应的字符序号，
可自由排列各个选项的位子位置，若为"0"或大于该列选项最大值，则不
选择这一部分功能。注意要加双引号
*/
#ifndef __MENU_CFG_H_
#define __MENU_CFG_H_


#define PARENT_FUN1	"1"//系统管理员
#define PARENT_FUN2  "2"//管理员
#define PARENT_FUN3	"3"//修改用户密码
#define PARENT_FUN4	"0"

#define SYS_FUN1		"1"//修改系统密码
#define SYS_FUN2		"2"//工作模式设置
#define SYS_FUN3		"3"//箱门数量设置
#define SYS_FUN4		"4"//站号设置
#define SYS_FUN5		"5"//打开指定箱子
#define SYS_FUN6		"6"//打开所有箱子
#define SYS_FUN7		"7"//端口设置
#define SYS_FUN8		"8"//设置系统时间
#define SYS_FUN9		"9"//查询使用记录
#define SYS_FUN10		"10"//恢复出厂设置
#define SYS_FUN11		"11"//退出
#define SYS_FUN12		"0"//
#define SYS_FUN13		"0"
#define SYS_FUN14	   "0"
#define SYS_FUN15		"0"

#define COMM_FUN1		"1"//修改管理员密码
#define COMM_FUN2		"2"//注册用户
#define COMM_FUN3		"3"//注销用户
#define COMM_FUN4		"4"//打开指定箱子
#define COMM_FUN5		"5"//打开所有箱子
#define COMM_FUN6		"6"//清除所有箱子
#define COMM_FUN7		"7"//锁定指定箱子
#define COMM_FUN8		"8"//解锁指定箱子
#define COMM_FUN9		"9"//锁定所有箱子
#define COMM_FUN10	"10"//解锁所有箱子
#define COMM_FUN11	"11"//查询使用记录
#define COMM_FUN12	"12"//退出
#define COMM_FUN13	"0"//
#define COMM_FUN14	"0"//
#define COMM_FUN15	"0"//

#endif

