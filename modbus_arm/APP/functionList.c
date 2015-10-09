#include "functionList.h"
#include "mainfunction.h"
#include "sysfunction.h"
#include "commfunction.h"

#include "stm32f10x.h"
#include "menu_cfg.h"
#include "user_cfg.h"

#include <stdlib.h>
#include <string.h>

void ProcNull(FUN_BLOCK **funBlock);

FUN_BLOCK *pfunBlock = mainFunBlock;//定义一个全局指针,指向各个结构体
FUN_BLOCK *pfunSubBlock = NULL;//定义一个专门指向临时申请内存的全局指针，便于清空指针
//DIS_SING displayFull;//定义一个全局的显示全屏变量
DIS_SING mainDisolayFull = 
{MAIN_LINE1,
"",
MAIN_LINE3,
MAIN_LINE4};

/*定义结构体数组，该数组根据前面的数字排序，并生成一个链表*/

/*主界面*/
FUN_BLOCK mainFunBlock[1] =
{{&mainDisolayFull , 0 , 0 , 0 , parentFunBlock , ProcNull , NONUM}};

/*主功能选择功能菜单*/
FUN_BLOCK parentFunBlock[MAX_PARENT_FUN_BLOCK] =      
{
{PARENT_FUN1"、系统管理员" , 0 , 0 , mainFunBlock , sysFunBlock , SysEnter , NONUM},
{PARENT_FUN2"、管理员" , 0 , 0 , mainFunBlock , commFunBlock , CommEnter , NONUM},
{PARENT_FUN3"、修改用户密码" , 0 , 0 , mainFunBlock , userChangeCodeFunBlock , UserEnter , NONUM},
{PARENT_FUN4"、" , 0 , 0 , mainFunBlock , 0 , ProcNull , NONUM},
};


/*系统管理员下的功能菜单
下一级操作指向自己本身*/
FUN_BLOCK sysFunBlock[MAX_SYS_FUN_BLOCK] = 
{
/*显示内容*/				  /*前后个*/  /*上一级操作*/	 /*下一级操作*/	 /*该级的功能函数*/  /*显示属性*/
{SYS_FUN1"、修改系统密码"  , 0 , 0 , parentFunBlock , &sysFunBlock[0]  , SysChangePassWord    , NONUM},
{SYS_FUN2"、工作模式设置"  , 0 , 0 , parentFunBlock , &sysFunBlock[1]  , SysSetWorkMod        , NONUM},
{SYS_FUN3"、箱门数量设置"  , 0 , 0 , parentFunBlock , &sysFunBlock[2]  , SysSetBoxNum         , NONUM},
{SYS_FUN4"、站号设置"      , 0 , 0 , parentFunBlock , &sysFunBlock[3]  , SysSetCabStation     , NONUM},
{SYS_FUN5"、打开指定箱子"  , 0 , 0 , parentFunBlock , &sysFunBlock[4]  , SysOpenOneBox        , NONUM},
{SYS_FUN6"、打开所有箱子"  , 0 , 0 , parentFunBlock , &sysFunBlock[5]  , SysOpenAllBox        , NONUM},
{SYS_FUN7"、端口设置"      , 0 , 0 , parentFunBlock , &sysFunBlock[6]  , SysSetPort           , NONUM},
{SYS_FUN8"、设置系统时间"  , 0 , 0 , parentFunBlock , &sysFunBlock[7]  , SysSetTime           , NONUM},
{SYS_FUN9"、查询使用记录"  , 0 , 0 , parentFunBlock , &sysFunBlock[8]  , SysCheckRecord       , NONUM},
{SYS_FUN10"、恢复出厂设置" , 0 , 0 , parentFunBlock , &sysFunBlock[9]  , SysRecoveryInit      , NONUM},
{SYS_FUN11"、退出"         , 0 , 0 , parentFunBlock , &sysFunBlock[10] , SysExit              , NONUM},
{SYS_FUN12"、"             , 0 , 0 , parentFunBlock , &sysFunBlock[11] , 0                    , NONUM},
{SYS_FUN13"、"             , 0 , 0 , parentFunBlock , &sysFunBlock[12] , 0                    , NONUM},
{SYS_FUN14"、"             , 0 , 0 , parentFunBlock , &sysFunBlock[13] , 0                    , NONUM},
{SYS_FUN15"、"             , 0 , 0 , parentFunBlock , &sysFunBlock[14] , 0                    , NONUM},
};

/*管理员下的功能菜单*/
FUN_BLOCK commFunBlock[MAX_COMM_FUN_BLOCK] = 
{															  
/*显示内容*/				  /*前后个*/ /*上一级操作*/		 /*下一级操作*/   	 /*该级的功能函数*/  /*显示属性*/
{COMM_FUN1"、修改管理员密码"  , 0 , 0 , &parentFunBlock[1] , &commFunBlock[0] , CommChangePassWord , NONUM},
{COMM_FUN2"、注册用户"        , 0 , 0 , &parentFunBlock[1] , &commFunBlock[1] , CommRegistUser     , NONUM},
{COMM_FUN3"、注销用户"        , 0 , 0 , &parentFunBlock[1] , &commFunBlock[2] , CommCancleUser     , NONUM},
{COMM_FUN4"、打开指定箱子"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[3] , SysOpenOneBox      , NONUM},
{COMM_FUN5"、打开所有箱子"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[4] , SysOpenAllBox      , NONUM},
{COMM_FUN6"、清除所有箱子"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[5] , CommClearAllBox    , NONUM},
{COMM_FUN7"、锁定指定箱子"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[6] , CommLockOneBox     , NONUM},
{COMM_FUN8"、解锁指定箱子"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[7] , CommUnLockOneBox   , NONUM},
{COMM_FUN9"、锁定所有箱子"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[8] , CommLockAllBox     , NONUM},
{COMM_FUN10"、解锁所有箱子"   , 0 , 0 , &parentFunBlock[1] , &commFunBlock[9] , CommUnLockAllBox   , NONUM},
{COMM_FUN11"、查询使用记录"   , 0 , 0 , &parentFunBlock[1] , &commFunBlock[10] , SysCheckRecord    , NONUM},
{COMM_FUN12"、退出"           , 0 , 0 , &parentFunBlock[1] , &commFunBlock[11] , SysExit           , NONUM},
{COMM_FUN13"、"               , 0 , 0 , &parentFunBlock[1] , &commFunBlock[12] , 0 , NONUM},
{COMM_FUN14"、"               , 0 , 0 , &parentFunBlock[1] , &commFunBlock[13] , 0 , NONUM},
{COMM_FUN15"、"               , 0 , 0 , &parentFunBlock[1] , &commFunBlock[14] , 0 , NONUM},
};

/*用户更改密码功能菜单*/
FUN_BLOCK userChangeCodeFunBlock[1] = 
{0 , 0 , 0 , mainFunBlock , mainFunBlock , 0 , ZINUM};


/*
自动排序结构体，并生成双向链表，链表头和尾为空比较大于99或为空的的不参与链表
input：FUN_BLOCK **funBlock结构体数组 ，length 数组元素个数
*/
void AdjustBlock(FUN_BLOCK *funBlock , u8 length)
{
 	u8 *numbuf , *tempbuf;
	FUN_BLOCK *funBlocktemp;
	u8 i,j,temp,min_value=0,min_value1=0;

	numbuf = malloc(length);
	tempbuf = numbuf;
	for(funBlocktemp = funBlock ; funBlocktemp < funBlock + length ; funBlocktemp++)//读取所有箱子的编号
	{
		*tempbuf++ = (u8)atoi((char const *)funBlocktemp->current_display);
	}
	/*找出最小值*/
	for(i=0;i<length;i++)
	{
		if(numbuf[i] == 1)
		{
			min_value = i;
			break;
		}
	}
	pfunBlock = &funBlock[i];//全局指针指向链表头

	temp = 100;
	/*查找length*length次，再不修改数组的前提下按从小到大的顺序找出来赋值*/
	for(i=0;i<length;i++)
	{
		for(j=0;j<length;)
		{
			/*找出离上次值最近的一个*/
			if(numbuf[j] > numbuf[min_value])
			{
				if(temp > numbuf[j] - numbuf[min_value])
				{
					temp = numbuf[j] - numbuf[min_value];
					min_value1 = j;
				}
			}
			j++;
		}//end for(j=0;j<length;)
		if(numbuf[min_value1] > 20)  break;//遇到不需要指向的值直接退出循环
		if(min_value != min_value1)
		{
			funBlock[min_value].pnext_block = &funBlock[min_value1];//前面的指针指向后面
			funBlock[min_value1].plast_block = &funBlock[min_value];//后面的指针指向前面
		}
		min_value = min_value1;
		temp = 100;
	}//end for(i=0;i<length;i++)
	free(numbuf);
}

/*
空执行函数，响应enter键,采用指向指针的指针，这样可以在子函数中修改指针
需要注意表达式优先级的问题
*/
void ProcNull(FUN_BLOCK **funBlock)
{
	*funBlock = (*funBlock)->sub_block;
}


