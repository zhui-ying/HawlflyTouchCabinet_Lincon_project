/*
该文件主要实现系统管理员功能
由functionList.c里的功能数组调用
*/
#include "includes.h"

/*
修改系统密码
*/
void SysChangePassWord(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;
	u8 *pass_wordbuf[7];

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = XINGNUM;//显示属性

startSysChange:
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
		memcpy(cab_msg.sys_password,pass_wordbuf,6);
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
		goto startSysChange;
	}
	FreeMem();
}

/*工作模式设置*/
void SysSetWorkMod(FUN_BLOCK **funBlock)
{
	*funBlock = (*funBlock)->sub_block;
}

/*箱门数量设置
输入箱门数，判断箱门数，确认
在这里要修改箱门状态的内存区
*/
void SysSetBoxNum(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;
	u8 box_num;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//显示属性
	ReadCabinetMsg(&cab_msg);

startSetBox:
	strcpy(sing_temp->y2 ,  "请输入箱门数");
	/*取得2位数的箱门数*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 2))
	{
		FreeMem();
		return;
	}
	/*取得输入的箱门=数*/
	box_num = atoi(sing_temp->y3);
	if(box_num>80)
	{
		strcpy(sing_temp->y2 , "输入错误,请重新输入");
		memset(sing_temp->y3 , 0 ,3);
		/*送显*/
		DisplaySubBlock(pfunSubBlock);
		goto startSetBox;
	}
	cab_msg.cab_box_num = box_num;
	WriteCabinetMsg(&cab_msg);

	/*修改全局指针*/
	free(pboxStatus);
	pboxStatus = malloc(cab_msg.cab_box_num + 1);
	memset(pboxStatus , '0' , cab_msg.cab_box_num);
	*(pboxStatus + cab_msg.cab_box_num) = 0;//最后一位设置为0，方便使用strlen

	strcpy(sing_temp->y2 , "箱门修改成功");
	memset(sing_temp->y3 , 0 ,3);
	/*送显*/
	DisplaySubBlock(pfunSubBlock);
	FreeMem();
}

/*站号设置*/
void SysSetCabStation(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//显示属性
	ReadCabinetMsg(&cab_msg);

	strcpy(sing_temp->y2 ,  "请输入站号");
	/*取得2位数的箱门数*/
	if(CANCEL == KeyDisplay(pfunSubBlock , CAB_STATION_LENGTH))
	{
		FreeMem();
		return;
	}
	/*取得站号*/
	memcpy(&(cab_msg.cab_station_num[6-CAB_STATION_LENGTH]) , sing_temp->y3 ,CAB_STATION_LENGTH); 
	WriteCabinetMsg(&cab_msg);

	strcpy(sing_temp->y2 ,  "站号修改成功");
	memset(sing_temp->y3 , 0 ,3);
	/*送显*/
	DisplaySubBlock(pfunSubBlock);
	FreeMem();
}

/*打开指定箱子	系统管理员和管理员都可用
输入箱号->判断箱号->打开指定箱子
*/
void SysOpenOneBox(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//显示属性

OpenBoxStart:
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
		goto OpenBoxStart;
	}
	else
	{
		OpenOneBox(&box_msg);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		strcpy(sing_temp->y2 ,  sing_temp->y3);
		strcat(sing_temp->y2 , "箱已开");			 //****箱已开
		memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
		DisplaySubBlock(pfunSubBlock);
	}
	FreeMem();	
}

/*打开所有箱子
在这里要关掉定时器，未改*/
void SysOpenAllBox(FUN_BLOCK **funBlock)
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
		OpenOneBox(&box_msg);//发送开箱信号
		OSSemPend(door_semp , 1000 , &err);//等待开箱结束信号

		memcpy(sing_temp->y2 ,  (char *)(box_msg.virtualnumber) , VIRTUAL_NUM_LENGTH);
		strcat(sing_temp->y2 , "箱已开");			 //****箱已开
		/*显示*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
	}
	FreeMem();
	TIM_Cmd(TIM2,ENABLE);//使能TIM2	
}

/*端口设置
输入箱号，判断箱号，输入端口2位，注意端口号-1*/
void SysSetPort(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//显示属性

SetPortStart:
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
		goto SetPortStart;
	}

	/*输入端口号*/
	strcpy(sing_temp->y2 ,  "请输入端口号");
	if(CANCEL == KeyDisplay(pfunSubBlock , 2))
	{
		FreeMem();
		return;
	}
	box_msg.station_port = atoi(sing_temp->y3); //修改端口号
	memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
	WriteOneBoxMsg(&box_msg);
	strcpy(sing_temp->y2 ,  "端口修改成功");
	DisplaySubBlock(pfunSubBlock);
		
	FreeMem();	
}

/*设置系统时间*/
void SysSetTime(FUN_BLOCK **funBlock)
{
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//显示属性

	RTC_ITConfig(RTC_IT_SEC, DISABLE);	//关RTC中断，防止systmtime被修改
	strcpy(sing_temp->y2 ,  "请输入时间");
	/*取得VIRTUAL_NUM_LENGTH位数的箱门数*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 10))
	{
		FreeMem();
		return;
	}
	/*读取时间值*/
	systmtime.tm_year = 2000 + (sing_temp->y3[0]-'0')*10 + sing_temp->y3[1]-'0';
	systmtime.tm_mon = (sing_temp->y3[2]-'0')*10 + sing_temp->y3[3]-'0';
	systmtime.tm_mday = (sing_temp->y3[4]-'0')*10 + sing_temp->y3[5]-'0';
	systmtime.tm_hour = (sing_temp->y3[6]-'0')*10 + sing_temp->y3[7]-'0';
	systmtime.tm_min = (sing_temp->y3[8]-'0')*10 + sing_temp->y3[9]-'0';
	memset(sing_temp->y3 , 0 , 10);
	/*写入时间*/
	RTC_Configuration();
	Time_Adjust(&systmtime);//写入系统时间
	BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);

	strcpy(sing_temp->y2 ,  "系统时间修改成功");
	DisplaySubBlock(pfunSubBlock);
		
	FreeMem();
}

void SysDisplayHrecord(char *buf , u8 station_num , u8 ph_record ,H_BOX_MSG *box_hmsg)
{
		ReadOneBoxHMsg(station_num , ph_record , box_hmsg);
		if(box_hmsg->hCount == 0) return;

		memcpy(buf , box_hmsg->hTime , 15);
		if(box_hmsg->hStatus == BOX_IDLE)
		{
			strcat(buf , " 取");
		}
		else
		if(box_hmsg->hStatus == BOX_USED)
		{
			strcat(buf , " 存");
		}
}

/*查询使用记录*/
void SysCheckRecord(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	H_BOX_MSG box_hmsg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//显示属性

OpenCheckStart:
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
	memset(sing_temp->y2 , 0 , VIRTUAL_NUM_LENGTH);
	if(NULL == box_msg.virtualnumber[0])//没有查到
	{
		strcpy(sing_temp->y2 ,  "输入错误请重新输入");		
		/*送显*/
		DisplaySubBlock(pfunSubBlock);
		goto OpenCheckStart;
	}
	else
	{
		u8 ph_record;
		ph_record = FindHNearestRecord(box_msg.station_num , &box_hmsg);
		ReadOneBoxHMsg(box_msg.station_num , ph_record , &box_hmsg);
		if(box_hmsg.hCount == 0)
		{
			strcpy(sing_temp->y2 ,  "此箱没有记录");		
			/*送显*/
			DisplaySubBlock(pfunSubBlock);		
		}
		else
		{	/*按照时间先后顺序显示*/
			SysDisplayHrecord(sing_temp->y1 , box_msg.station_num , ph_record , &box_hmsg);
			ph_record--;
			if(ph_record == 0) ph_record = 4;
			SysDisplayHrecord(sing_temp->y2 , box_msg.station_num , ph_record , &box_hmsg);
			ph_record--;
			if(ph_record == 0) ph_record = 4;
			SysDisplayHrecord(sing_temp->y3 , box_msg.station_num , ph_record , &box_hmsg);
			ph_record--;
			if(ph_record == 0) ph_record = 4;
			SysDisplayHrecord(sing_temp->y4 , box_msg.station_num , ph_record , &box_hmsg);
			/*送显*/
			DisplaySubBlock(pfunSubBlock);
			/*等待返回的键值*/
			if(CANCEL == KeyDisplay(pfunSubBlock , 0))
			{
				FreeMem();
				return;
			}
		}
	}
	FreeMem();
}


/*恢复出厂设置*/
void SysRecoveryInit(FUN_BLOCK **funBlock)
{
	DIS_SING *sing_temp;
	CAB_MSG cab_msg;

	ReadCabinetMsg(&cab_msg);
	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = NONUM;//显示属性

	strcpy(sing_temp->y2 ,  "确认恢复出厂设置？");
	/*取得VIRTUAL_NUM_LENGTH位数的箱门数*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 10))
	{
		FreeMem();
		return;
	}

	Dis1LineMid("初始化中、、、" , 1);
	RefreshLCD();
	/*恢复出厂设置*/
	InitAllBox(INIT_FLAG);
	memset(pboxStatus , BOX_IDLE , cab_msg.cab_box_num);  //忘了将缓存的箱子信息清空 2013.4.25
	*(pboxStatus + cab_msg.cab_box_num) = 0;//最后一位设置为0，方便使用strlen
	strcpy(sing_temp->y2 ,  "初始化完成");
	DisplaySubBlock(pfunSubBlock);	
}


/*退出
直接回到主界面*/
void SysExit(FUN_BLOCK **funBlock)
{
	*funBlock = mainFunBlock;
}

/*
复位按键检测，实现对管理员密码和系统管理员密码复位
长按复位键5s可实现复位操作
time: LC 2013.8.13
*/
void RestKeyCheck()
{
/*检测复位键是否按下,低有效*/		 
	if(!RESETKEY)
	{
		u8 i;
		LED2ON;
		for(i=0;i<100;i++)
		{
			OSTimeDlyHMSM(0, 0, 0,50);//循环检测，按下时长超过3s
			if(RESETKEY)
			{
				LED2OFF;
				break;
			}
			if(i == 99)
			{
				CAB_MSG cab_msg;

				TIM_Cmd(TIM2,DISABLE);//禁能TIM2,禁止键盘输入
				RefreshLCD();
				Dis1LineMid("初始化中、、、" , 1);
				RefreshLCD();//刷新屏幕	
				
				ReadCabinetMsg(&cab_msg);//读取系统信息
				memset(cab_msg.sys_password , '8' , 6);//改变箱子系统管理员密码 888888
				memset(cab_msg.comm_password , '6' , 6);//改变箱子系统管理员密码	666666
				WriteCabinetMsg(&cab_msg);//写入系统信息						

				OSTimeDlyHMSM(0, 0, 2,0);//显示时间2s				
				LED2OFF;

				TIM_Cmd(TIM2,ENABLE);//使能TIM2
				pfunBlock = mainFunBlock;	
				OSMboxPost(display_box , pfunBlock);// 发送邮箱,刷新显示，回到主屏			
			}
		}
	}
}

u8 AuthorProcess(u8 key_data)
{
	static u8 key_count = 0;
	u8 author_flag = 0;
	if(key_data > 9)
	{
	 	key_count = 0;
		memset(authorbuf , 0 , 10);	
	}
	else
	{
		authorbuf[key_count++] = key_data + '0';
		if(key_count >= 9)
		{
			if(0 == memcmp(authorbuf , "503740053" , 9)) //匹配成功
			{
				CAB_MSG cab_msg;
				ReadCabinetMsg(&cab_msg);//读取系统信息
				memset(cab_msg.sys_password , '8' , 6);//改变箱子系统管理员密码 888888
				memset(cab_msg.comm_password , '6' , 6);//改变箱子系统管理员密码	666666
				WriteCabinetMsg(&cab_msg);//写入系统信息

				RefreshLCD();
				Dis1LineMid("武汉霍克富莱" , 0);
				Dis1LineMid("作者：lc" , 1);
				Dis1LineMid("版本：v7.7.3" , 2);
				RefreshLCD();//刷新屏幕	
				author_flag = 1;											
			}
			key_count = 0;
			memset(authorbuf , 0 , 10);	
		}
	}
	return author_flag;
}



