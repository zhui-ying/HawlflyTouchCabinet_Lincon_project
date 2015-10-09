
#include "modbusRTU.h"
#include "UART485.h"

struct MODBUS_ADD modbus_Addt;//声明一个modbus结构体变量
struct MODBUS_ADD *modbusAdd;//结构体指针，指向这个变量
int rec_time_out;//超时
int rec_stat;//接收状态
int rec_num;//接收的字节数
int send_count;//要发送的字节数
unsigned char send_buf[200];
//=================================================================================================
// CRC 高位字节值表 
//------------------
const unsigned char CRC_H[] = { 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40 
} ; 
//=================================================================================================
// CRC低位字节值表
//----------------
const unsigned char CRC_L[] = { 
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 
0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 
0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 
0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 
0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 
0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 
0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 
0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 
0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 
0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 
0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 
0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 
0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 
0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 
0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 
0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 
0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 
0x43, 0x83, 0x41, 0x81, 0x80, 0x40 
} ;

/**************************************************************************************************
    NAME : init_MODBUS(void)
   INPUT : NO
  OUTPUT : 
FUNCTION : 
	  modbus初始化
**************************************************************************************************/
void init_MODBUS(void)
{
	modbusAdd = &modbus_Addt; //将指针指向定义好的内存
	rec_stat = PACK_START; //刚开始状态为开始接收
	rec_time_out = 0;//超时计数为0
}
/**************************************************************************************************
    NAME : checkPACK_MODBUS
   INPUT : NO
  OUTPUT : unsigned char 返回校验结果，正确返回非零值，错误返回零。
FUNCTION : 
	   校验接收数据包的正确性
**************************************************************************************************/
unsigned char checkPACK_MODBUS(unsigned char *rec_buff , int rec_num)
{
	unsigned int rec_CRC;

	rec_CRC = (rec_buff[rec_num-2] << 8) | rec_buff[rec_num-1];

	if( rec_CRC == comp_crc16(rec_buff, rec_num-2) )
	{
		return 1;
	}
	else
		return 0;
}

/**************************************************************************************************
    NAME : comp_crc16
   INPUT : unsigned char *pack 数据缓冲首地址, unsigned char num 数据字节数
  OUTPUT : unsigned int 计算结果，低位在前 高位在后（MODBUS 规定）。
FUNCTION : 
	   CRC16 计算 MODBUS使用公式：X16+X15+X2+1 。此不同于CITT公式
**************************************************************************************************/
unsigned int comp_crc16(unsigned char *pack, unsigned char num) 
{ 
	unsigned char CRCcode_H = 0XFF;		// 高CRC字节初始化
	unsigned char CRCcode_L = 0XFF;		// 低CRC 字节初始化
	unsigned char index,i=0;			// 数据索引

	while (num--)
	{ 
		index = CRCcode_L ^ (pack[i++]);	

		CRCcode_L = CRCcode_H ^ CRC_H[index]; 

		CRCcode_H = CRC_L[index]; 
	} 

	return (CRCcode_L << 8 | CRCcode_H);	// MODBUS 规定低位在前
}

/**************************************************************************************************
    NAME : function_MODBUS
   INPUT : NO
  OUTPUT : NO
FUNCTION : 
	   执行MODBUS功能函数
**************************************************************************************************/
void function_MODBUS(unsigned char *rec_buff , unsigned char *send_data)
{	
	switch(rec_buff[1])	// 功能索引
	{
		case 1:
			//read_coil();
			break;

		case 2:
			//read_input_bit();
			break;

		case 3:
			read_reg(rec_buff,send_data);
			break;

		case 4:
			read_reg(rec_buff,send_data);
			break;

		case 5:
			//force_coil_bit();
			break;

		case 6:
			force_reg(rec_buff,send_data);
			break;

		case 15:
			//force_coil_mul();
			break;

		case 16:
			force_reg(rec_buff,send_data);
			break;

		default:

			//send_buff[1] = rec_buff[1] | 0X80;
			//send_buff[2] = ERR_FUN_CODE;		// 不合法功能号
			//send_num = 5;
			break;
	}
}

/*
function：对应modbus功能号03,批量读寄存器
input：rec_buf接收到的指令 send_data需要发送的指令
*/
void read_reg(unsigned char * rec_buff , unsigned char * send_data)
{
	unsigned char begin_add = 0;
	unsigned char data_num = 0;
	unsigned char *piont;
	unsigned int send_CRC;
	unsigned int send_num;
	int i;
	send_data[0] = rec_buff[0];//站号
	send_data[1] = rec_buff[1];//功能码

	begin_add = rec_buff[3]*2;//地址1字节
	data_num = rec_buff[5]*2;//需要读取的字节数
	send_num = 5 + data_num;	// 5个固定字节+数据个数 addr1 + fun1 + num1 +【data】+ crc2 
	send_data[2] = data_num;//字节数
	piont = (unsigned char *)modbusAdd; 
	for(i=0;i<data_num;i++)
	{
		send_data[3+i] = piont[begin_add +i];
	}
	send_CRC = comp_crc16(send_data, send_num-2);
	send_data[send_num-2] = send_CRC >> 8;
	send_data[send_num -1] = send_CRC;
	send_count = send_num;
	PutNChar(send_buf , send_count);
}

/*
function：对应modbus功能号06和16,单个和批量写寄存器
input：rec_buf接收到的指令 send_data需要发送的指令
*/
void force_reg(unsigned char * rec_buf , unsigned char * send_data)
{
	unsigned char fun_code,begin_add,data_num;//功能码，开始地址，数据长度
	unsigned int send_num;//发送数据长度
	unsigned char *piont;
	unsigned int send_CRC;
	int i;

	send_data[0] = rec_buf[0];
	fun_code = rec_buf[1];
	send_data[1] = fun_code;
	send_data[2] = rec_buf[2];
	send_data[3] = rec_buf[3];
	begin_add = rec_buf[3]*2;
	piont = (unsigned char *)modbusAdd;
	
	if(fun_code == 6)//写单个寄存器，返回指令与接收的指令完全一样
	{
		piont[begin_add] = rec_buf[4];//寄存器高位写入
		piont[begin_add+1] = rec_buf[5];//寄存器低位写入
		send_data[4] = rec_buf[4];
		send_data[5] = rec_buf[5];
		send_num = 8;//
	}
	else if(fun_code == 16)//写多个寄存器
	{
		data_num = rec_buf[5]*2;
		send_data[4] = rec_buf[4];
		send_data[5] = rec_buf[5];
		send_num = 8;
		for(i=0;i<data_num;i++)
		{
			piont[begin_add+i] = rec_buf[7+i];
		}
	}
	send_CRC = comp_crc16(send_data, send_num-2);
	send_data[send_num-2] = send_CRC >> 8;
	send_data[send_num -1] = send_CRC;
	send_count = send_num;
    PutNChar(send_buf , send_count);
}

/*超时帧检测，在1ms定时器里面运行，返回当前状态*/
int time_out_check_MODBUS(void)
{
	rec_time_out++;
	if(rec_time_out == 5)				// 两数据接受超时
	{
		rec_stat = PACK_START;
		rec_num = 0;
	}
	else if((rec_time_out == 4) && (rec_num > 4)) // 超时数据帧结束4ms
	{
		rec_stat = PACK_REC_OK;
//		modbus_rtu->rec_num = 0;
	}
		return rec_stat;		
}
