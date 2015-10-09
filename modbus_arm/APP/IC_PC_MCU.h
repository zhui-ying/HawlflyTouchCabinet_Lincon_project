#ifndef __IC_PC_MCU_H_
#define __IC_PC_MCU_H_

#define IC_CODE_LENTH  4

#define  PACK_OK   1
#define  PACK_ERR  0
#define  PC_MCU_PACK_LENGTH 10
#define  MCU_PC_PACK_LENGTH	7

#define RECV_HEAD1  0xa5
#define RECV_HEAD2  0xa6
#define SEND_HEAD1 0x5a
#define SEND_HEAD2 0x6a

#define REGID      0x31
#define LOGOUTID   0x32
#define CHECK_STATUS  0x33
#define PCOPENBOX     0x34
#define USER_DATA_BACK	 0x35

#define IC_FAILE 0x00
#define IC_SUCCESS 0xff

struct UART485_Com {

	unsigned char startCode[2];
	unsigned char addCode;
	unsigned char commder;
	unsigned char boxNum;
	unsigned char IDcode[4];
	unsigned char checkCode;
};

void IC_GPRSINT(unsigned char data);//÷–∂œ ¥¶¿Ì
void Test_PC_MCUdata(unsigned char comm , unsigned char box_num , unsigned char *code);
//unsigned char ReadAdd();
unsigned char CheckMsg(struct UART485_Com *UART485msg);
void RegBox(struct UART485_Com *UART485msg);
void LogoutBox(struct UART485_Com *UART485msg);
void CheckStatus(struct UART485_Com *UART485msg);
void PcOpenBox(struct UART485_Com *UART485msg);
void SendPC(unsigned char comm , unsigned char box_num , unsigned char comm_status);

//extern void USART1_Conf(unsigned int baudRate);

#endif
