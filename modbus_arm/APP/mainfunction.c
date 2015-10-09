/*
功能：实现主界面和母界面的功能和显示操作
与functionList.c文件相关联
*/
#include "includes.h"
extern u8 err;

/*子函数功能送显*/
void DisplaySubBlock(FUN_BLOCK *funBlock)
{
	OSMboxPost(display_box , funBlock);// 发送邮箱,刷新显示
	OSTimeDlyHMSM(0, 0, TIP_S,TIP_MS);
}


/*
功能：实现用户键盘的输入和更新显示
输入：需写入数据的结构体
返回 CANCEL 取消键	 ENTER确认键返回
*/
u8 KeyDisplay(FUN_BLOCK *funBlock , u8 key_length)
{
	u8 *pkey_value = NULL; 
	u8 i=0;
	DIS_SING *sing_temp = (DIS_SING *)(funBlock->current_display);
	OSMboxPost(display_box , funBlock);// 发送邮箱,刷新显示
	while(1)
	{
		pkey_value = OSMboxPend(key_box , 0 , &err);	//无限等待
	
		switch(*pkey_value)
		{
			case CANCEL:  return CANCEL;
								
			case ENTER:   return ENTER; 
		}
		if(*pkey_value < 10)
		{
			if(i<key_length)
			{
				sing_temp->y3[i++] = *pkey_value + '0';	//转换成ASC码
				OSMboxPost(display_box , funBlock);// 发送邮箱,刷新显示	
			}
		}
	}
}

/*获得用于基础功能块的空间
输入key_length 所需的数据长度
返回获得的指针
*/
void GetSubFunBlock(FUN_BLOCK **pfunSubBlock)
{
//	DIS_SING *sing_temp;
	u8 temp;
	temp = sizeof(FUN_BLOCK);
	*pfunSubBlock = malloc(temp);//申请一段临时内存
	memset(*pfunSubBlock , 0 , temp);

	temp = sizeof(DIS_SING);
	(*pfunSubBlock)->current_display = malloc(temp);//全屏显示的指针
	memset((*pfunSubBlock)->current_display , 0 , temp);

//	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
//	sing_temp->y3 = malloc(key_length);//用于存储密码
//	memset(sing_temp->y3 , 0 , key_length);
}

/*
主界面下的功能函数
直接指向子界面
*/
void MainEnter(FUN_BLOCK **funBlock)
{
	*funBlock = (*funBlock)->sub_block;
}

/*母界面下的功能函数*/

/*系统管理员
密码输入，判断密码，进入下一级
*/
void SysEnter(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = XINGNUM;//显示属性

start:
	strcpy(sing_temp->y2 ,  "请输入系统管理员密码");
	if(CANCEL == KeyDisplay(pfunSubBlock , 6))
	{
		FreeMem();
		return;
	}

	ReadCabinetMsg(&cab_msg);
	/*匹配密码*/
	if(0 == memcmp(cab_msg.sys_password , sing_temp->y3 , 6))
	{
		*funBlock = (*funBlock)->sub_block;
	}
	else
	{
		strcpy(sing_temp->y1 ,  "密码错误");
		strcpy(sing_temp->y2 ,  "请重新输入");
		memset(sing_temp->y3 , 0 , 7);		
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		memset(sing_temp->y1 , 0 , LINE_LENGTH);
		goto start;
	}
	FreeMem();
}



/*管理员
密码输入，判断密码，进入下一级
*/
void CommEnter(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;
	/*申请内存区，初始化*/
	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = XINGNUM;//显示属性

start:
	strcpy(sing_temp->y2 ,  "请输入管理员密码");

	/*获取键值并判断返回值，键值装载在y3区*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 6))
	{
		FreeMem();
		return;
	}

	ReadCabinetMsg(&cab_msg);
	/*匹配密码*/
	if(0 == memcmp(cab_msg.comm_password , sing_temp->y3 , 6))
	{
		*funBlock = (*funBlock)->sub_block;
	}
	else
	{
		strcpy(sing_temp->y1 ,  "密码错误");
		strcpy(sing_temp->y2 , "请重新输入");
		memset(sing_temp->y3 , 0 , 7);
		/*送显*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		memset(sing_temp->y1 , 0 , LINE_LENGTH);
		goto start;
	}
	FreeMem();
}

/*用户修改密码
输入箱号，判断箱号，输入密码，判断密码，输入新密码，再次输入新密码，判断密码，完成
*/
void UserEnter(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//显示属性

UserStart:
	strcpy(sing_temp->y2 ,  "请输入箱号");
	/*取得VIRTUAL_NUM_LENGTH位数的箱门数*/
	if(CANCEL == KeyDisplay(pfunSubBlock , VIRTUAL_NUM_LENGTH))
	{
		FreeMem();
		return;
	}
	/*根据输入查询对应的箱子*/
	SearchBoxMsg((u8 *)sing_temp->y3 , &box_msg);
	memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
	if(NULL == box_msg.virtualnumber[0])//没有查到
	{
		strcpy(sing_temp->y2 ,  "输入错误请重新输入");
		/*送显*/
		DisplaySubBlock(pfunSubBlock);
		goto UserStart;
	}
	else
	{
		u8 pass_wordbuf[USER_PASSWORD_LENGTH];
		/*判断该箱是否已注册*/
		if(BOX_USED != box_msg.status)
		{
			strcpy(sing_temp->y1 ,  "该箱未注册或已锁定");
			strcpy(sing_temp->y2 ,  "请重新输入");
			/*送显*/
			DisplaySubBlock(pfunSubBlock);
			memset(sing_temp->y1 , 0 , LINE_LENGTH);
			goto UserStart;			
		}

		pfunSubBlock->data_type = XINGNUM;//更改属性
		strcpy(sing_temp->y2 ,  "请输入箱子密码");
		/*取得密码*/
		if(CANCEL == KeyDisplay(pfunSubBlock , USER_PASSWORD_LENGTH))
		{
			FreeMem();
			return;
		}
		if(0 != memcmp(sing_temp->y3 , box_msg.pass_word , USER_PASSWORD_LENGTH))
		{
			strcpy(sing_temp->y2 ,  "密码错误请重新输入");
			memset(sing_temp->y3 , 0 , LINE_LENGTH);		
			/*送显*/
			DisplaySubBlock(pfunSubBlock);
			goto UserStart;			
		}
		memset(sing_temp->y3 , 0 , LINE_LENGTH);

UserNewStart:
		strcpy(sing_temp->y2 , "请输入新密码");
		/*取得6位数的新密码*/
		if(CANCEL == KeyDisplay(pfunSubBlock , USER_PASSWORD_LENGTH))
		{
			FreeMem();
			return;
		}
		/*备份新密码*/
		memcpy(pass_wordbuf , sing_temp->y3 , USER_PASSWORD_LENGTH);
		memset(sing_temp->y3 , 0 ,USER_PASSWORD_LENGTH);
		strcpy(sing_temp->y2 , "请再次输入新密码");
		/*取得6位数的新密码*/
		if(CANCEL == KeyDisplay(pfunSubBlock , USER_PASSWORD_LENGTH))
		{
			FreeMem();
			return;
		}
		/*比较前后两次密码*/
		if(0 == memcmp(pass_wordbuf , sing_temp->y3 , USER_PASSWORD_LENGTH))
		{
			memcpy(box_msg.pass_word,pass_wordbuf,USER_PASSWORD_LENGTH);
			/*写入flash*/
			WriteOneBoxMsg(&box_msg);
			strcpy(sing_temp->y2 , "密码修改成功");
			memset(sing_temp->y3 , 0 , 6);
			/*送显*/
			DisplaySubBlock(pfunSubBlock);
		}
		else
		{
			strcpy(sing_temp->y2 , "密码错误请重新输入");
			memset(sing_temp->y3 , 0 , USER_PASSWORD_LENGTH);
			/*送显*/
			DisplaySubBlock(pfunSubBlock);
			goto UserNewStart;
		}
		FreeMem();
	 }
}

