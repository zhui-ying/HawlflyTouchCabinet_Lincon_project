/*用户功能实现文件
判断输入数据的类型，根据输入数据查找箱子或分配箱子
*/
#include "includes.h"
#include "dis_fuction.h"
/*用户信息类型*/
#define SENDID 1
#define GETID  2
#define NOID   0

/*运货单有效性*/
#define RIGHT_MSG 1
#define WRONG_MSG 0

typedef struct sendID_msg{
#if COMPANY_FLAG
		u8 flag;
#endif
		u8 time_year[4];
		u8 time_month[2];
		u8 time_day[2];

#if CAB_NUM_FLAG
		u8 cab_num[3];	//存储柜子号，用于柜子的识别，3月31日
#endif

#if COMPANY_FLAG
#if CAB_NUM_FLAG
		u8 rand_data[SENDID_LENGTH-12];
#else
		u8 rand_data[SENDID_LENGTH-9];
#endif

#else

#if CAB_NUM_FLAG
		u8 rand_data[SENDID_LENGTH-11];
#else
		u8 rand_data[SENDID_LENGTH-8];
#endif
#endif
}SEND_IDMSG;

static u8 GetMsgType(u8 *user_msg);
static u8 JudgSendMsg(u8 *user_msg);
static void ChangeSendBoxMsg(BOX_MSG *box_msg , u8 *user_msg);
static void ChangeUserBoxMsg(BOX_MSG *box_msg , u8 *user_msg);
static void RecordBoxMsg(BOX_MSG *box_msg);
extern void GetCabID(u8 *buf);
/*用户功能实现函数，刷卡模式*/
void UserFunction(u8 *user_msg)
{
	u8 user_msg_type = GETID;
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = NONUM;//显示属性

#if !ICMOD
	/*判断信息类型*/
	user_msg_type = GetMsgType(user_msg);

	/*用户信息错误*/
	if(NOID == user_msg_type)
	{
		strcpy(sing_temp->y2 , "无效卡");
		goto user_end;
	}

	/*送货员的信息*/
	if(SENDID == user_msg_type)
	{
#if !TESTMOD
		/*判断该运货单的有效性*/
		if(WRONG_MSG == JudgSendMsg(user_msg))
		{
			strcpy(sing_temp->y2 , "条码已过期或损坏");
			goto user_end;
		}
#endif
		/*搜索可用的箱子*/
		SearchIdleBoxMsg(&box_msg);
		if(NULL == box_msg.virtualnumber[0])
		{
			strcpy(sing_temp->y2 , "箱子已满");	//无箱子可用了
			goto user_end;
		}
		/*打开搜索到的箱子*/
		if(CLOSE_STAT == UserOpenBox(&box_msg))
		{
			strcpy(sing_temp->y2 , "开箱失败，请重刷"); //开箱失败
			goto user_end;
		}

		/*修改box_msg信息*/
		ChangeSendBoxMsg(&box_msg , user_msg);
	}
#endif

	/*一般用户的信息*/
	if(GETID == user_msg_type)
	{
		/*根据用户数据搜索所有箱子*/
		SearchUserBoxMsg(user_msg , &box_msg);
		if(NULL == box_msg.virtualnumber[0])
		{
			strcpy(sing_temp->y2 , "无效卡"); //搜索不到箱子
			goto user_end;
		}
		/*打开搜索到的箱子*/
		if(CLOSE_STAT == UserOpenBox(&box_msg))
		{
			strcpy(sing_temp->y2 , "开箱失败,请重刷"); //开箱失败
			goto user_end;
		}
		/*修改box_msg信息*/
#if !ICMOD
		ChangeUserBoxMsg(&box_msg , user_msg);
#endif
	}

	/*记录信息到flash*/
	RecordBoxMsg(&box_msg );
	/*发送信息给上位机*/
#if ICMOD
#if ICMOD_GPRS
	IC_PCSendUserData(box_msg.station_num);
#endif
#else
	PCSendUserData(box_msg.station_num);
#endif

	/*显示开箱*/
	memset(sing_temp->y2 , 0 , LINE_LENGTH);
	memcpy(sing_temp->y2 ,  box_msg.virtualnumber , VIRTUAL_NUM_LENGTH);
	strcat(sing_temp->y2 , "号箱已开");			 //****箱已开
	strcpy(sing_temp->y3 , "使用后请关闭箱门"); 
user_end:
	DisplaySubBlock(pfunSubBlock);
	FreeMem();
}

/*用户按取键开箱*/
void UserGetPack(void)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	
UserGetStart:
#if USER_INPUT_BOXNUM
	pfunSubBlock->data_type = ZINUM;//显示属性
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
		goto UserGetStart;
	}
	/*判断该箱是否已注册*/
	if(BOX_USED != box_msg.status)
	{
		strcpy(sing_temp->y1 ,  "该箱未注册或已锁定");
		strcpy(sing_temp->y2 ,  "请重新输入");
		/*送显*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y1 , 0 , LINE_LENGTH);
		goto UserGetStart;			
	}
	else
#endif
	{
		pfunSubBlock->data_type = XINGNUM;//更改属性
		strcpy(sing_temp->y2 ,  "请输入箱子密码");
		/*取得密码*/
		if(CANCEL == KeyDisplay(pfunSubBlock , USER_PASSWORD_LENGTH))
		{
			FreeMem();
			return;
		}
		 /*验证密码*/
#if USER_INPUT_BOXNUM
		if(0 != memcmp(sing_temp->y3 , box_msg.pass_word , USER_PASSWORD_LENGTH))
#else
		SearchUserBoxMsgPassWord((u8 *)sing_temp->y3 , &box_msg);
		if(NULL == box_msg.virtualnumber[0])//没有查到
#endif
		{
			strcpy(sing_temp->y2 ,  "密码错误请重新输入");
			memset(sing_temp->y3 , 0 , LINE_LENGTH);		
			/*送显*/
			DisplaySubBlock(pfunSubBlock);
			goto UserGetStart;			
		}
		memset(sing_temp->y3 , 0 , LINE_LENGTH);
		/*打开箱子*/
		if(CLOSE_STAT == UserOpenBox(&box_msg))
		{
			strcpy(sing_temp->y2 , "开箱失败,请重输"); //开箱失败
			/*送显*/
			DisplaySubBlock(pfunSubBlock);
			goto UserGetStart;
		}
		/*修改box_msg信息*/
#if !ICMOD
		ChangeUserBoxMsg(&box_msg , 0);
#endif
		RecordBoxMsg(&box_msg );
		/*发送信息给上位机*/
#if ICMOD
#if ICMOD_GPRS
	IC_PCSendUserData(box_msg.station_num);
#endif
#else
	PCSendUserData(box_msg.station_num);
#endif

		pfunSubBlock->data_type = NONUM;//更改属性
		/*显示开箱*/
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		memcpy(sing_temp->y2 ,  box_msg.virtualnumber , VIRTUAL_NUM_LENGTH);
		strcat(sing_temp->y2 , "号箱已开");			 //****箱已开
		strcpy(sing_temp->y3 , "使用后请关闭箱门"); 
		DisplaySubBlock(pfunSubBlock);
	}
	FreeMem();	
}

/*判断数据类型,只对条码有效
返回数据类型
*/
u8 GetMsgType(u8 *user_msg)
{
	u8 length;
	length = strlen((char *)user_msg);
	if(SENDID_LENGTH == length)
	{
		return SENDID;
	}
	if(USERID_LENGTH == length)
	{
		return GETID;
	}
	return 0;
}

/*判断运货单的有效性*/
static u8 JudgSendMsg(u8 *user_msg)
{
	SEND_IDMSG *msg_judge;
	uint32_t time_now,time_tm;
	struct rtc_time code_time;
	BOX_MSG box_msg;
#if CAB_NUM_FLAG
	u8 IDbuf[6];
#endif
	memset(&code_time , 0 ,sizeof(struct rtc_time));

	msg_judge = (SEND_IDMSG *)user_msg;

#if COMPANY_FLAG
	/*判断公司标志值*/
	if(COMPANY_FLAG != msg_judge->flag)
	{
		return WRONG_MSG;
	}
#endif

/*判断柜子号，3月31添加*/
#if CAB_NUM_FLAG
	GetCabID(IDbuf);
	/*比较柜子ID号*/
	if(0 != memcmp(IDbuf+3 , msg_judge->cab_num , 3))
	{
		return WRONG_MSG;
	}

#endif
	
	/*开始时间校验*/
	code_time.tm_year = (msg_judge->time_year[0]-'0')*1000 + (msg_judge->time_year[1]-'0')*100 +
	                     (msg_judge->time_year[2]-'0')*10	+ (msg_judge->time_year[3]-'0');
	code_time.tm_mon = (msg_judge->time_month[0]-'0')*10 + (msg_judge->time_month[1]-'0');
	code_time.tm_mday = (msg_judge->time_day[0]-'0')*10 + (msg_judge->time_day[1]-'0');
	code_time.tm_hour = DAY_START_HOUR;

	/*本地时间减去运货单上的时间，本地时间一定要在运货单时间后面
	时间逻辑关系弄错了，本地时间小于条码时间，或本地时间大于条码时间某个长度时间就认为条码无效	2013.4.20
	*/
	time_now = RTC_GetCounter();
	time_tm = mktimev(&code_time); //使用库函数mktimev 只可使用一次，它会修改给进去的值
	if((time_now < time_tm) || (time_now - time_tm) > LONGEST_TIME*60*60)
	{
		return WRONG_MSG;
	}

	/*开始记录校验，所有箱子保有两条记录*/
	for(box_msg.station_num = 0 ; box_msg.station_num < strlen((char *)pboxStatus) ; box_msg.station_num++)
	{
		ReadOneBoxMsg(&box_msg);//读出箱子所有信息
		if(0 == memcmp(box_msg.send_id0 , user_msg , SENDID_LENGTH))//有相同的
		{
			return WRONG_MSG;
		}
		if(0 == memcmp(box_msg.send_id1 , user_msg , SENDID_LENGTH))//有相同的
		{
			return WRONG_MSG;
		}
	}

	/*所有的校验通过*/
	return RIGHT_MSG;
}

/*用户打开指定的箱子
返回 OPEN_STAT 打开成功
     CLOSE_STAT 打开失败
	 添加分多次等待，提高系统运行速度
*/
u8 UserOpenBox(BOX_MSG *box_msg)
{
	u8 count_open_time = 10;//分10次等待	WAIT_DOOR_TIME/
	OpenOneBox(box_msg);

	OSSemPend(door_semp , 0 , &err);//等待开门信号
	/*开箱完毕后再等一段时间*/
	while(count_open_time--)
	{
		 if(OPEN_STAT == ReadOneBox(box_msg))
		 {
		 	break;
		 }
		 OSTimeDlyHMSM(0, 0, 0,WAIT_DOOR_TIME/10);
	}
	
	if(CLOSE_STAT == ReadOneBox(box_msg))
	{
		return CLOSE_STAT;
	}
	return OPEN_STAT;
}

/*修改送货员送货成功后对应的信息*/
void ChangeSendBoxMsg(BOX_MSG *box_msg , u8 *user_msg)
{											
	box_msg->status = BOX_USED; //修改箱子状态
	memcpy(box_msg->send_id1 , box_msg->send_id0 , SENDID_LENGTH);
	memcpy(box_msg->send_id0 , user_msg , SENDID_LENGTH);		  //记录送货员ID
	memset(box_msg->user_id , 0xff , USERID_LENGTH);//清空用户ID
	memset(box_msg->pass_word , 0xff , USER_PASSWORD_LENGTH);//清空用户密码
	pboxStatus[box_msg->station_num] = BOX_USED;
/*
#if TESTMOD	
	memcpy(box_msg->user_id , "201212291234" , 12);
	memcpy(box_msg->pass_word , "123456" , 6);
#endif*/
}

/*修改客户取货成功后对应的信息*/
void ChangeUserBoxMsg(BOX_MSG *box_msg , u8 *user_msg)
{
	box_msg->status = BOX_IDLE;  //修改箱子状态
	pboxStatus[box_msg->station_num] = BOX_IDLE;
}

/*找出最近的历史记录，返回记录的相对地址
若i大于4，
*/
u8 FindHNearestRecord(u8 station_num ,H_BOX_MSG *box_hmsg)
{
	u8 i,temp=0;
	/*找出最大值*/
	for(i=1;i<=4;i++)
	{
		ReadOneBoxHMsg(station_num , i ,box_hmsg);
		if(temp < box_hmsg->hCount)
		{
			temp = box_hmsg->hCount;
		}
		else
		if(temp > box_hmsg->hCount)
		{
			break;
		}
	}
//	if(i == 5) i = 4;
	return i-1;
}

/*记录用户信息到flash
还有记录历史记录*/
void RecordBoxMsg(BOX_MSG *box_msg)
{
	H_BOX_MSG box_hmsg;
	u8 i=0;
	/*记录用户信息*/
	WriteOneBoxMsg(box_msg);
	/*找出最近的记录*/
	i = FindHNearestRecord(box_msg->station_num , &box_hmsg);
	if(i>=4)	 i = 1;			
	else	    i++;
	
	box_hmsg.hCount++;
	/*到达一个极限值时再翻转重来*/
	if(box_hmsg.hCount == 252)
	{
		for(i=1;i<=3;i++)
		{
			ReadOneBoxHMsg(box_msg->station_num , i ,&box_hmsg);
			box_hmsg.hCount = i;
			WriteOneBoxHMsg(box_msg->station_num , i ,&box_hmsg);
		}
		box_hmsg.hCount = i;
	}
	GetTimeStr((char *)box_hmsg.hTime , &systmtime);//读取时间
	box_hmsg.hStatus = box_msg->status;		 //读取状态
	WriteOneBoxHMsg(box_msg->station_num , i ,&box_hmsg);
}
