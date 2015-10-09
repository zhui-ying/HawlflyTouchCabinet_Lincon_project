#include <stdio.h>

#include "lincon.h"
#include "string.h"

#define debug 1

#define PACKET_BUF_SIZE                 128

#define SERIAL_STATUS_OK                0
#define SERIAL_STATUS_SYS_ERR           -1
#define SERIAL_STATUS_PORT_ERR          -2
#define SERIAL_STATUS_TIMEOUT           -3
#define SERIAL_STATUS_PKT_ERR           -4
#define SERIAL_STATUS_PACK_ERR           -5
static int serial_id;

static int recv_pack(char *recv_packet, int recv_total_len, int *recv_len,int timeout);
static int send_pack(char *send_packet_buf);

/*模块初始化*/
static int echodemo_init()
{
    //char com_port[16];
	//long baud=9600;
    //rtdb_get_data_value_by_name("echodemo", "serialname", com_port);
    //rtdb_get_data_value_by_name("echodemo", "baud", &baud);
 
    //serial_id = serial_open(com_port, baud, SERIAL_PARITY_NO, 8, SERIAL_STOPBIT_ONE, 1000);
    //打开串口，COM1，9600,无校验，8位，一个停止位，通讯超时 100
//    serial_id = serial_open("COM1", 9600, SERIAL_PARITY_NO, 8, SERIAL_STOPBIT_ONE, 100);
    if (serial_id < 0)
    {
        return 0;
    }


    return 1;
}
/*创建发送包*/
static int echodemo_build_send_packet(char *send_buf, int buf_len)
{
    static unsigned int send_count=0;
    int send_len;

	send_count++;
   // rtdb_get_data_value_by_name("echodemo", "send_count", &send_count);
    send_len = sprintf(send_buf, "send packet: %u\n", send_count);
    return send_len;
}
/*实现发送和接收*/
static int echodemo_transaction(char *send_packet, int send_len, char *recv_packet, int recv_total_len, int *recv_len, 
                             int serial_id,int timeout)
{
    if (serial_id == -1)
        return SERIAL_STATUS_PORT_ERR;
    
    if (!serial_flush(serial_id, SERIAL_FLUSH_RX|SERIAL_FLUSH_TX))
        return SERIAL_STATUS_PORT_ERR;

    if (serial_write(serial_id, send_packet, send_len) != send_len)
        return SERIAL_STATUS_PORT_ERR;

    //read packet
    *recv_len = 0;
    while(1)
    {
        int ret,i;
        int read_len;
        
        ret = serial_poll(serial_id,timeout);
        if (ret < 0)
           return SERIAL_STATUS_PORT_ERR;
        if (ret == 0)
            return SERIAL_STATUS_TIMEOUT;
        
        if (recv_total_len <= *recv_len)
            return SERIAL_STATUS_PKT_ERR;
        
        read_len = serial_read(serial_id, recv_packet+(*recv_len), recv_total_len-(*recv_len));
        if (read_len <= 0)
            return SERIAL_STATUS_PORT_ERR;

        *recv_len += read_len;
        for(i = 0; i < *recv_len; i++)
        {
            if (recv_packet[i] == '\n')
            {
                return SERIAL_STATUS_OK;
            }
        }
    }
    return SERIAL_STATUS_PORT_ERR;
}

static int echodemo_resp_packet_handle(char *recv_packet, int packet_len)
{
	recv_packet[packet_len-1] = 0;
    rtdb_set_data_value_by_name("test_parm", "recv_buf", recv_packet);
    return SERIAL_STATUS_OK;
}

/*在新的进程里一直循环执行的函数，实现数据的接收和发送*/
static int echodemo_run()
{/*
    int ret, send_len, recv_len = 0;
    char send_packet_buf[PACKET_BUF_SIZE];
    char recv_packet_buf[PACKET_BUF_SIZE];
    unsigned char send_flag , recv_flag;
*/
	int count=0;
    while(1)
    {
    	debug_printf("3G_GPRS %d\n",count);
    	count++;
    	sys_sleep(1000);
    /*
        if ((send_len =echodemo_build_send_packet(send_packet_buf, sizeof(send_packet_buf))) == 0)
            return SERIAL_STATUS_PKT_ERR;
        rtdb_set_data_value_by_name("test_parm", "send_buf", send_packet_buf);
       // debug_printf("!!!!!!!!!!!!!!!!!!!!\n");
        ret = echodemo_transaction(send_packet_buf, send_len, recv_packet_buf, sizeof(recv_packet_buf), &recv_len, serial_id, 1000);
        if (ret == SERIAL_STATUS_OK)
        {
            echodemo_resp_packet_handle(recv_packet_buf, recv_len);
        }
		//rtdb_set_data_value_by_name("echodemo","status",&ret);

        sys_sleep(1000);
        rtdb_get_data_value_by_name("sys_set","send_pack_flag",&send_flag);//查询是否有数据发送
        if(send_flag == 1)
        {
			rtdb_get_data_value_by_name("sys_set","send_pack",send_packet_buf);//复制数据
			send_flag = 0;
			rtdb_set_data_value_by_name("sys_set","send_pack_flag",&send_flag);
			ret = send_pack(send_packet_buf);//数据发送
        }
        ret = recv_pack(recv_packet_buf, sizeof(recv_packet_buf), &recv_len,100);
        if(SERIAL_STATUS_TIMEOUT != ret)
        rtdb_set_data_value_by_name("test_parm","ret",&ret);
        if(recv_len != 0)
        rtdb_set_data_value_by_name("test_parm","rec_len",&recv_len);
        serial_flush(serial_id, SERIAL_FLUSH_RX);//清空接收缓存
        if(ret == SERIAL_STATUS_OK)//成功接收一帧消息
        {
   			 rtdb_set_data_value_by_name("sys_set", "recv_pack", recv_packet_buf);
   			 recv_flag = 1;
			 rtdb_set_data_value_by_name("sys_set", "recv_pack_flag", &recv_flag);//接收到一帧	
			 debug_printf("recv 1 pack\n");
        }
        memset(recv_packet_buf , 0 , PACKET_BUF_SIZE);*/
    }
    
    return SERIAL_STATUS_OK;
}

static void echodemo_release()
{
    return;
}

static ctrl_io_driver_t echodemo_drive={NULL, "echodemo", echodemo_init, echodemo_run, echodemo_release};

int module_init(char *params)
{
			
    control_io_register_driver(&echodemo_drive);
    return 1;
}


void module_exit()
{
}

/*和校验*/
static int check_sum(char *recv_packet , int pack_len)
{
	int i=0;
	unsigned char check_value=0;
	for(i=4;i<pack_len-3;i++)
	{
		check_value += recv_packet[i];
	}
	if(check_value == recv_packet[pack_len-3])
	{
		return 1;
	}
	else
	{
		#if debug
		return 1;
		#endif
		return 0;
	}
}

/*function:实现数据的接收和数据的初步解析
input: recv_packet接收数据放在这个包里 recv_total_len可以接收的最大字节数 timeout 超时
output: 当前串口数据状态，SERIAL_STATUS_OK 成功接收一帧数据
*/
static int recv_pack(char *recv_packet, int recv_total_len, int *recv_len,int timeout)
{
	// int recv_len=0;//recv_packet中接收的总字节数
	 int pack_len=0;//接收包的总长度
	 *recv_len = 0;
    while(1)
    {
        int ret,i;
        int read_len;
        
        ret = serial_poll(serial_id,timeout);
        if (ret < 0)
           return SERIAL_STATUS_PORT_ERR;
        if (ret == 0)
            return SERIAL_STATUS_TIMEOUT;
        
        read_len = serial_read(serial_id, recv_packet + *recv_len, recv_total_len-(*recv_len));
        if (read_len <= 0)//未收到数据
            return SERIAL_STATUS_PORT_ERR;

        *recv_len += read_len;//数据长度

       // return SERIAL_STATUS_OK;

        /*数据初步解析*/
        if(recv_packet[0] != 0xa5 || recv_packet[1] != 0xa5)//包头不对，放弃该数据
        {
			//serial_flush(serial_id, SERIAL_FLUSH_RX);//清空接收缓存
			return SERIAL_STATUS_PACK_ERR;
        }
        pack_len = recv_packet[2]*256 + recv_packet[3];//读取指令长度
        pack_len = pack_len+6;//根据协议，添加上头尾的长度
        
        if(pack_len <= *recv_len)//一帧数据接收完毕
        {
			if((recv_packet[pack_len-1] != 0x5a) || (recv_packet[pack_len-2] != 0x5a) || !check_sum(recv_packet , pack_len))//包尾校验,校验和
			{
				//serial_flush(serial_id, SERIAL_FLUSH_RX);//清空接收缓存
				return SERIAL_STATUS_PACK_ERR;				
			}
			//serial_flush(serial_id, SERIAL_FLUSH_RX);//清空接收缓存
			return SERIAL_STATUS_OK;
        }
        if(pack_len < *recv_len)
        {
			//	serial_flush(serial_id, SERIAL_FLUSH_RX);//清空接收缓存
			//	return SERIAL_STATUS_PACK_ERR;				
        }
    }	
}

static int send_pack(char *send_packet_buf)
{
	int send_len;
     send_len = send_packet_buf[2]*256 + send_packet_buf[3];//读取指令长度
     send_len = send_len+6;//根据协议，添加上头尾的长度	
     if (!serial_flush(serial_id, SERIAL_FLUSH_TX))
        return SERIAL_STATUS_PORT_ERR;

    if (serial_write(serial_id, send_packet_buf, send_len) != send_len)
        return SERIAL_STATUS_PORT_ERR;    
}

