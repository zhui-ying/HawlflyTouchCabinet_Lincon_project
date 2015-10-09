#ifndef __USER_CFG_H_
#define __USER_CFG_H_

#define INIT_FLAG  0x07//flash初始化标志位

#define ICMOD 0 //选择IC卡模式，为1 为IC卡模式，为0 则为条码模式
#define ICMOD_485 0
#define ICMOD_GPRS 1//GPRS模式，注意：GPRS模式指令包含485模式指令

#define OLD_NEW_BOARD 1//新老板子识别标志 0 老板子  1 新板子

#define PC_MOD 1//选择是否有上位机，有选项为1
#define PC_BKP_NUM 19200//485或GPRS波特率 	 485为9600  GPRS为19200
#define GUANG_DONG_MOD 1 //特别的广东模式,多余项填充0xff
#define GUANG_DONG_SENDID_LENGTH 20
#define GUANG_DONG_USERID_LENGTH 20

#define BOX_FEED_BACK	1//选择有没有箱门状态反馈  0无 ，1有
#define USER_INPUT_BOXNUM 0	 //选择用户是直接输密码开箱0 还是先输箱号再输密码1
#define TESTMOD 0 //选择判断条码是否已失效，1 不判断 0 判断
/*箱子状态*/
#define CLOSE_STAT       1//箱子关
#define OPEN_STAT        0//箱子开

/*各个输入长度定义*/
#if !ICMOD
#define SENDID_LENGTH  20	  //送货员的开箱信息长度,条码模式下
#define USERID_LENGTH  6	  //取货人的信息长度 ,条码模式下
#else
#define SENDID_LENGTH  17	  //送货员的开箱信息长度，IC模式下
#define USERID_LENGTH  4	  //取货人的信息长度，IC模式下
#endif

#define USER_PASSWORD_LENGTH 6 //用户密码长度
#define VIRTUAL_NUM_LENGTH 4//虚拟箱号长度一般为4或2
#define CAB_STATION_LENGTH 3 //柜子的站号长度设置,IC网络模式下，柜号不能超过255

#define BOXNUM 16//默认箱门数16

#define COMPANY_FLAG 0//定义公司特定标志位，若为0，没有标志位，否则为其他字符 'H'
#define CAB_NUM_FLAG 1//定义是否需要匹配柜号，三位数
#define DAY_START_HOUR 6//定义一天开始的时间，与时间校验有关
#define LONGEST_TIME  48//有效期保持的最长时间，小时


#define TIME_MAIN	 8*50	  //等待8s回到主界面

#define TIP_S		1
#define TIP_MS		500	  //提示时间1.5s

#define OPEN_DOOR_TIME 700//开箱时间700ms
#define WAIT_DOOR_TIME  700//等待箱子完全打开时间，开箱时间和等待时间加起来就是开箱反应时间, 最大９９９

/*主屏幕更改程序*/
#define MAIN_LINE1 "顺 客 隆"
#define MAIN_LINE3 "刷卡或按'取'开箱"
#define MAIN_LINE4 "tel:4001-029-529"

#endif
