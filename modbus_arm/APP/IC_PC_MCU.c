#include "includes.h"
#include "UART485.h"

//u8 pc_msgbuf[PC_MCU_PACK_LENGTH];
u8 recvflag = 1;//接收标志

/*从flash中读取本机ID值*/
static u8 ReadAdd()
{
	u8 station_num;
	CAB_MSG cab_msg;
	ReadCabinetMsg(&cab_msg);
	station_num = (cab_msg.cab_station_num[3]-'0')*100 + (cab_msg.cab_station_num[4]-'0')*10 + cab_msg.cab_station_num[5]-'0';
	return station_num;
}

void IC_GPRSINT(u8 data)
{
	static u8 count=0;
	if(recvflag == 1)
	{
		pc_msgbuf[count++] = data;

		if(count == 1)
		{
			if(pc_msgbuf[0] != RECV_HEAD1)
			{
				count = 0;
				return;			
			}
		}

		if(count == 2)//每接收两个字符检查一次
		{
			if((pc_msgbuf[0] != RECV_HEAD1) || (pc_msgbuf[1] != RECV_HEAD2))
			{
				count = 0;
				return;
			}
		}
	
		if(count == PC_MCU_PACK_LENGTH)
		{
			OSMboxPost(pc_box , pc_msgbuf);// 发送邮箱
			count = 0;
			recvflag = 0;//接受一帧数据后禁止接受
		}
	}
}

/*
检查此帧数据，先检查柜号，再检查校验码
*/
u8 CheckMsg(struct UART485_Com *UART485msg)
{
	u8 cabinet_add;
	u8 *check=0;
	u8 check_value=0;
	recvflag = 1;//可以接收
	cabinet_add = ReadAdd();
	if(cabinet_add != UART485msg->addCode) //柜子号匹配
	{
		return 0;
	}

	for(check = &(UART485msg->startCode[0]);
	       check < &(UART485msg->checkCode);check++)
	{
		check_value ^= *check;//异或校验
	}
	if(check_value != UART485msg->checkCode) //校验失败
	{
		return 0;
	}
	return 1;		
}

/*
发送数据到上位机
参数：comm：命令  box_num 箱号  comm_status 命令状态
*/
void SendPC(u8 comm , u8 box_num , u8 comm_status)
{
	u8 sendbuf[MCU_PC_PACK_LENGTH];
	u8 i;
	memset(sendbuf , 0 ,MCU_PC_PACK_LENGTH);
	sendbuf[0] = SEND_HEAD1;
	sendbuf[1] = SEND_HEAD2;
	sendbuf[2] = ReadAdd();
	sendbuf[3] = comm;
	sendbuf[4] = box_num;
	sendbuf[5] = comm_status;
	
	for(i=0;i<MCU_PC_PACK_LENGTH-1;i++)	//添加校驗位
	{
		sendbuf[MCU_PC_PACK_LENGTH-1] ^= sendbuf[i];	
	}
	PutNChar(sendbuf , MCU_PC_PACK_LENGTH);//send to PC 	
}

/*测试程序,输入comm：命令  box_num 箱号 code ID卡号
生成要发送的数据*/
void Test_PC_MCUdata(u8 comm , u8 box_num , u8 *code)
{
	u8 sendbuf[PC_MCU_PACK_LENGTH];
	u8 i;
	memset(sendbuf , 0 ,PC_MCU_PACK_LENGTH);
	sendbuf[0] = RECV_HEAD1;
	sendbuf[1] = RECV_HEAD2;
	sendbuf[2] = 1;
	sendbuf[3] = comm;
	sendbuf[4] = box_num;
	memcpy(&sendbuf[5] , code , 4);
	
	for(i=0;i<PC_MCU_PACK_LENGTH-1;i++)	//添加校驗位
	{
		sendbuf[PC_MCU_PACK_LENGTH-1] ^= sendbuf[i];	
	}
	PutNChar(sendbuf , PC_MCU_PACK_LENGTH);//send to PC 
	PutNChar("\r\n" , 2);
}

/*
注册箱子
*/
void RegBox(struct UART485_Com *UART485msg)
{
   BOX_MSG box_msg;
   box_msg.station_num = UART485msg->boxNum - 1;//读取箱号，减1与箱子数匹配

   ReadOneBoxMsg(&box_msg);//读取箱子所有相关信息

   box_msg.status = BOX_USED;
   memcpy(box_msg.user_id , UART485msg->IDcode , IC_CODE_LENTH);//复制ID卡号

   WriteOneBoxMsg(&box_msg);//写入信息
   SendPC(REGID , UART485msg->boxNum , IC_SUCCESS);
}

/*
注销箱子
*/
void LogoutBox(struct UART485_Com *UART485msg)
{
   BOX_MSG box_msg;
   box_msg.station_num = UART485msg->boxNum - 1;//读取箱号，减1与箱子数匹配

   ReadOneBoxMsg(&box_msg);//读取箱子所有相关信息

   box_msg.status = BOX_IDLE;
   memset(box_msg.user_id , 0xff , IC_CODE_LENTH);//恢复默认

   WriteOneBoxMsg(&box_msg);//写入信息
   SendPC(LOGOUTID , UART485msg->boxNum , IC_SUCCESS);
}

/*
查询某个箱子状态
*/
void CheckStatus(struct UART485_Com *UART485msg)
{
   BOX_MSG box_msg;
   box_msg.station_num = UART485msg->boxNum - 1;//读取箱号，减1与箱子数匹配

   ReadOneBoxMsg(&box_msg);//读取箱子所有相关信息

   if(box_msg.status == BOX_USED)
   {
   	  SendPC(CHECK_STATUS , UART485msg->boxNum , IC_SUCCESS);
   }
   else 
   if(box_msg.status == BOX_IDLE)
   {
   	  SendPC(CHECK_STATUS , UART485msg->boxNum , IC_FAILE);
   }
}

/*
打开某个箱子
*/
void PcOpenBox(struct UART485_Com *UART485msg)
{
   BOX_MSG box_msg;
   box_msg.station_num = UART485msg->boxNum - 1;//读取箱号，减1与箱子数匹配

   ReadOneBoxMsg(&box_msg);//读取箱子所有相关信息

	OpenOneBox(&box_msg);//开门
	OSSemPend(door_semp , 0 , &err);//等待开门信号
	if(ReadOneBox(&box_msg) == CLOSE_STAT)	//箱子未打开
	{
		SendPC(PCOPENBOX , UART485msg->boxNum , IC_FAILE);//开箱失敗返回给上位机
		return;
	}
	SendPC(PCOPENBOX , UART485msg->boxNum , IC_SUCCESS);//开箱成功返回给上位机
	return;	   	
}

/*返回用户使用记录*/
void IC_PCSendUserData(u8 box_num)
{
   BOX_MSG box_msg;
	struct UART485_Com UART485msg;
   box_msg.station_num = box_num;//读取箱号，减1与箱子数匹配
	UART485msg.boxNum = box_num+1;

   ReadOneBoxMsg(&box_msg);//读取箱子所有相关信息
	if(box_msg.status == BOX_USED)
   {
   	  SendPC(USER_DATA_BACK , UART485msg.boxNum , IC_SUCCESS);
   }
   else 
   if(box_msg.status == BOX_IDLE)
   {
   	  SendPC(USER_DATA_BACK , UART485msg.boxNum , IC_FAILE);
   }
}
