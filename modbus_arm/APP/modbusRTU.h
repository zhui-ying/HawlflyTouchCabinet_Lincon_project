#ifndef __MODBUSRTU_H
#define __MODBUSRTU_H

/*modbusRTU头文件，实现ARM上的通讯功能*/

//=================================================================================================
#define MODBUS_ADDR			0X01//modbus协议站号
//-----------------------------------
#define PACK_START		1	// 数据开始接受
#define PACK_REC_ING		2//正在接收数据
#define PACK_ADDR_ERR		4	// 地址不符合
#define PACK_REC_OK		8	// 与接收字节数 共同判断 接受一个帧成功
/*结构体定义*/

/*modbus位置定义，严格按照触摸屏定义的来，触摸屏是16位的，解析的时候需要
把地址*2然后对应下面的地址*/
struct MODBUS_ADD{
unsigned char station_num_H;
unsigned char station_num_L;//箱子排列号，高位一般为0
unsigned char station_port_H;
unsigned char station_port_L;//箱子端口号，高位一般为0
unsigned char send_comm_H;
unsigned char send_comm_L;//发送指令，高位一般为0
unsigned char back_comm_H;
unsigned char back_comm_L;//反馈指令，高位一般为0
unsigned char send_id[24];//运货单号
unsigned char user_id[4];//用户ID号
unsigned char send_id_flag_H;
unsigned char send_id_flag_L;//运货单号扫描标志
unsigned char user_id_flag_H;
unsigned char user_id_flag_L;//用户ID使用标志
};

extern struct MODBUS_ADD modbus_Addt;//声明一个modbus结构体变量
extern struct MODBUS_ADD *modbusAdd;//结构体指针，指向这个变量
extern int rec_time_out;//超时
extern int rec_stat;//接收状态
extern int rec_num;//接收的字节数
extern int send_count;//要发送的字节数
extern unsigned char send_buf[200];

unsigned char checkPACK_MODBUS(unsigned char *rec_buff , int rec_num);

unsigned int comp_crc16(unsigned char *pack, unsigned char num);
void init_MODBUS(void);
unsigned char checkPACK_MODBUS(unsigned char *rec_buff , int rec_num);
unsigned int comp_crc16(unsigned char *pack, unsigned char num);
void function_MODBUS(unsigned char *rec_buff , unsigned char *send_data);
void read_reg(unsigned char * rec_buff , unsigned char * send_data);
void force_reg(unsigned char * rec_buf , unsigned char * send_data);
int time_out_check_MODBUS(void);
#endif
