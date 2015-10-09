#include "includes.h"

extern u8 err;
/*
修改管理员密码
*/
void CommChangePassWord(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;
	u8 *pass_wordbuf[7];

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = XINGNUM;//显示属性

startCommChange:
	strcpy(sing_temp->y2 , "请输入新密码");
	/*取得6位数的新密码*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 6))
	{
		FreeMem();
		return;
	}
	/*备份新密码*/
	memcpy(pass_wordbuf , sing_temp->y3 , 6);
	memset(sing_temp->y3 , 0 ,6);
	strcpy(sing_temp->y2 , "请再次输入新密码");
	/*取得6位数的新密码*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 6))
	{
		FreeMem();
		return;
	}
	/*比较前后两次密码*/
	if(0 == memcmp(pass_wordbuf , sing_temp->y3 , 6))
	{
		ReadCabinetMsg(&cab_msg);
		memcpy(cab_msg.comm_password,pass_wordbuf,6);
		/*写入flash*/
		WriteCabinetMsg(&cab_msg);
		strcpy(sing_temp->y2 , "密码修改成功");
		memset(sing_temp->y3 , 0 , 6);
		/*送显*/
		DisplaySubBlock(pfunSubBlock);
	}
	else
	{
		strcpy(sing_temp->y2 , "密码错误请重新输入");
		memset(sing_temp->y3 , 0 , 6);
		/*送显*/
		DisplaySubBlock(pfunSubBlock);
		goto startCommChange;
	}
	FreeMem();
}

/*注册用户*/
void CommRegistUser(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//显示属性

RegistStart:
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
		goto RegistStart;
	}
	else
	{
		u8 *icbuf = NULL;
		/*判断该箱是否空闲*/
		if(BOX_IDLE != box_msg.status)
		{
			strcpy(sing_temp->y1 ,  "该箱已注册或锁定");
			strcpy(sing_temp->y2 ,  "请重新输入");
			/*送显*/
			DisplaySubBlock(pfunSubBlock);
			memset(sing_temp->y1 , 0 , LINE_LENGTH);
			goto RegistStart;			
		}

		/*得到正确箱号后下面等待ＩＣ卡输入*/
		strcpy(sing_temp->y2 ,  "请刷卡、、、");
		OSMboxPost(display_box , pfunSubBlock);// 发送邮箱,刷新显示
		icbuf = OSMboxPend(user_box , 5000 , &err);//等待5s
		ICcardDisable();
		if(icbuf == NULL)//超时返回
		{
			FreeMem();
			ICcardEnable();
			return;
		}
		/*写入对应的信息*/
		memcpy(box_msg.user_id , icbuf , USERID_LENGTH);
		memset(box_msg.pass_word , '8' , USER_PASSWORD_LENGTH);//写入默认密码888888
		box_msg.status = BOX_USED;
		pboxStatus[box_msg.station_num] = BOX_USED;
		WriteOneBoxMsg(&box_msg);

		strcpy(sing_temp->y2 ,  "注册成功!");
		/*显示*/
		DisplaySubBlock(pfunSubBlock);
		ICcardEnable();
	}
	FreeMem();
}


/*注销用户*/
void CommCancleUser(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//显示属性

CancleStart:
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
		goto CancleStart;
	}
	else
	{
		/*判断该箱是否已注册*/
		if(BOX_USED != box_msg.status)
		{
			strcpy(sing_temp->y1 ,  "该箱未注册或已锁定");
			strcpy(sing_temp->y2 ,  "请重新输入");
			/*送显*/
			DisplaySubBlock(pfunSubBlock);
			memset(sing_temp->y1 , 0 , LINE_LENGTH);
			goto CancleStart;			
		}

		/*写入对应的信息，回到初始状态*/
		memset(box_msg.user_id , 0xff , USERID_LENGTH);
		memset(box_msg.pass_word , 0xff , USER_PASSWORD_LENGTH);
		box_msg.status = BOX_IDLE;
		pboxStatus[box_msg.station_num] = BOX_IDLE;
		WriteOneBoxMsg(&box_msg);

		strcpy(sing_temp->y2 ,  "注销成功!");
		/*显示*/
		DisplaySubBlock(pfunSubBlock);
	}
	FreeMem();
}

/*清除所有箱子
将所有箱子设定为可使用状态
*/
void CommClearAllBox(FUN_BLOCK **funBlock)
{
	DIS_SING *sing_temp;
	BOX_MSG box_msg;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = NONUM;//显示属性

	TIM_Cmd(TIM2,DISABLE);//禁能TIM2
	for(box_msg.station_num=0; box_msg.station_num<strlen((char *)pboxStatus);box_msg.station_num++)
	{
		ReadOneBoxMsg(&box_msg);
		box_msg.status = BOX_IDLE;//修改箱子状态
		WriteOneBoxMsg(&box_msg);
		pboxStatus[box_msg.station_num] = BOX_IDLE;
		memcpy(sing_temp->y2 ,  (char *)(box_msg.virtualnumber) , VIRTUAL_NUM_LENGTH);
		strcat(sing_temp->y2 , "箱已清除");			 //****箱已清除
		/*显示*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
	}
	FreeMem();
	TIM_Cmd(TIM2,ENABLE);//使能TIM2	
}

/*锁定指定箱子*/
void CommLockOneBox(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//显示属性

LockOneStart:
	strcpy(sing_temp->y2 ,  "请输入箱号");
	/*取得VIRTUAL_NUM_LENGTH位数的箱门数*/
	if(CANCEL == KeyDisplay(pfunSubBlock , VIRTUAL_NUM_LENGTH))
	{
		FreeMem();
		return;
	}
	/*根据输入查询对应的箱子*/
	SearchBoxMsg((u8 *)sing_temp->y3 , &box_msg);
	if(NULL == box_msg.virtualnumber[0])//没有查到
	{
		strcpy(sing_temp->y2 ,  "输入错误请重新输入");
		memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
		/*送显*/
		DisplaySubBlock(pfunSubBlock);
		goto LockOneStart;
	}
	else
	{
		box_msg.status = BOX_LOCK; //状态改为锁定
		WriteOneBoxMsg(&box_msg);
		pboxStatus[box_msg.station_num] = BOX_LOCK;

		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		strcpy(sing_temp->y2 ,  sing_temp->y3);
		strcat(sing_temp->y2 , "箱已锁定");			 //****箱已锁定
		memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
		DisplaySubBlock(pfunSubBlock);
	}
	FreeMem();
}

/*解锁指定箱子*/
void CommUnLockOneBox(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//显示属性

UnLockOneStart:
	strcpy(sing_temp->y2 ,  "请输入箱号");
	/*取得VIRTUAL_NUM_LENGTH位数的箱门数*/
	if(CANCEL == KeyDisplay(pfunSubBlock , VIRTUAL_NUM_LENGTH))
	{
		FreeMem();
		return;
	}
	/*根据输入查询对应的箱子*/
	SearchBoxMsg((u8 *)sing_temp->y3 , &box_msg);
	if(NULL == box_msg.virtualnumber[0])//没有查到
	{
		strcpy(sing_temp->y2 ,  "输入错误请重新输入");
		memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
		/*送显*/
		DisplaySubBlock(pfunSubBlock);
		goto UnLockOneStart;
	}
	else
	{
		box_msg.status = BOX_IDLE; //状态改为空闲
		WriteOneBoxMsg(&box_msg);
		pboxStatus[box_msg.station_num] = BOX_IDLE;

		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		strcpy(sing_temp->y2 ,  sing_temp->y3);
		strcat(sing_temp->y2 , "箱已解锁");			 //****箱已解锁
		memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
		DisplaySubBlock(pfunSubBlock);
	}
	FreeMem();
}

/*锁定所有箱子*/
void CommLockAllBox(FUN_BLOCK **funBlock)
{
	DIS_SING *sing_temp;
	BOX_MSG box_msg;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = NONUM;//显示属性

	TIM_Cmd(TIM2,DISABLE);//禁能TIM2
	for(box_msg.station_num=0; box_msg.station_num<strlen((char *)pboxStatus);box_msg.station_num++)
	{
		ReadOneBoxMsg(&box_msg);
		box_msg.status = BOX_LOCK;//修改箱子状态
		WriteOneBoxMsg(&box_msg);
		pboxStatus[box_msg.station_num] = BOX_LOCK;

		memcpy(sing_temp->y2 ,  (char *)(box_msg.virtualnumber) , VIRTUAL_NUM_LENGTH);
		strcat(sing_temp->y2 , "箱已锁定");			 //****箱已锁定
		/*显示*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
	}
	FreeMem();
	TIM_Cmd(TIM2,ENABLE);//使能TIM2	
}

/*解锁所有箱子*/
void CommUnLockAllBox(FUN_BLOCK **funBlock)
{
	DIS_SING *sing_temp;
	BOX_MSG box_msg;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = NONUM;//显示属性

	TIM_Cmd(TIM2,DISABLE);//禁能TIM2
	for(box_msg.station_num=0; box_msg.station_num<strlen((char *)pboxStatus);box_msg.station_num++)
	{
		ReadOneBoxMsg(&box_msg);
		box_msg.status = BOX_IDLE;//修改箱子状态
		WriteOneBoxMsg(&box_msg);
		pboxStatus[box_msg.station_num] = BOX_IDLE;
		memcpy(sing_temp->y2 ,  (char *)(box_msg.virtualnumber) , VIRTUAL_NUM_LENGTH);
		strcat(sing_temp->y2 , "箱已解锁");			 //****箱已解锁
		/*显示*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
	}
	FreeMem();
	TIM_Cmd(TIM2,ENABLE);//使能TIM2	
}




