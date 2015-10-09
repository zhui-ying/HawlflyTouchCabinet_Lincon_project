/*用户操作函数，该文件包含所有与用户和发件员相关的操作，主要有输入密码开箱取物，刷ID卡直接开箱取物，刷运货条码直接开箱*/
#include "lincon.h"
#include "box_info.h"

void test_display(char *outbuf , unsigned char *inbuf , int len)
{
	int i=0;
	for(i=0;i<len;i++)
	{
		if(inbuf[i]<'0' || inbuf[i]>'9')
		{
			outbuf[i] = '*';
		}else
		{
			outbuf[i] = inbuf[i];
		}
	}
}



