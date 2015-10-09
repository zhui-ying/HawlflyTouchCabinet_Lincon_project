
#include "KeyBoard.h"


#define RCC_KEY44PORT		RCC_APB2Periph_GPIOG
#define KEY44PORT GPIOG    //	     4*4键盘连接的IO口，GPIOA~GPIOE
#define KEY44LSB  GPIO_Pin_0// 4*4键盘按顺序接到IO口上，最低位对应第一行
#define KEY44LSBn 0			 //最低位对应IO引脚号
#define KEY44ROW  0x0f//(KEY44LSB+(KEY44LSB<<1)+(KEY44LSB<<2)+(KEY44LSB<<3))//4*4键盘的行线
#define KEY44COL  (0x00f0<<(uint16_t)KEY44LSBn) 
//按键消抖动延时若干 ms
void Key_delayms(u32 n)
{
	u32 i;
	while(n--)
	for(i=0;i<0x0f5f;i++);
}

//矩阵键盘4*4 IO端口初始化，列线上拉输入
void Key44Port_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO的模式设置结构体变量
	RCC_APB2PeriphClockCmd(RCC_KEY44PORT , ENABLE);
  GPIO_InitStructure.GPIO_Pin = KEY44ROW;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //行线推挽式输出 
  GPIO_Init(KEY44PORT, &GPIO_InitStructure); 
  GPIO_InitStructure.GPIO_Pin = KEY44COL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    //列线上拉输入
  GPIO_Init(KEY44PORT, &GPIO_InitStructure); 

//	GPIO_ResetBits(KEY44PORT , KEY44ROW);
}
//矩阵键盘4*4扫描程序，有按键时返回1，否则返回0
uint16_t Key44_Scan(void)
{
	KEY44PORT->ODR &= ~KEY44ROW;  //行线全部置0
	if(((KEY44PORT->IDR)&KEY44COL)!=KEY44COL)
	 	{
		  KEY44PORT->ODR |= KEY44ROW;//有按键时，行线全部置高电平，准备扫描
		  return (uint16_t)1;
		}
	 else
		return (uint16_t)0;
}
/*****************************************************************************
*名    称：GetKey44val()
*功    能：获取矩阵键盘4*4的键值函数
*入口参数：无
*出口参数：获取到的键值，已经提前定义键值排列
*键值分布：0  1  2  3
*          4  5  6  7
*          8  9  10 11
*          9  10 11 12
*****************************************************************************/
uint16_t GetKey44val(void)
{
	uint16_t i,row,key,keyval;
	key=0;
	row=~KEY44LSB;
	for(i=0;i<4;i++)
	{
		KEY44PORT->ODR &= row;
		if(((KEY44PORT->IDR)& KEY44COL)!=KEY44COL)
		{
			Key_delayms(1);
			if(((KEY44PORT->IDR)&KEY44COL)!=KEY44COL)
			{
			  key=((~((KEY44PORT->IDR)& KEY44COL))& KEY44COL)+((~row)& KEY44ROW);
			  break;
			}
		}
		KEY44PORT->ODR |= ~row;
		row=(row<<1)|(KEY44LSB);
	}
	KEY44PORT->ODR &= ~KEY44ROW;
	while(((KEY44PORT->IDR)&KEY44COL)!=KEY44COL);
	Key_delayms(5);
	switch((key>>KEY44LSBn))	   
	{	  //bit7~bit4:列线，4列；bit3~bit0:行线，4行
		case 0x11: keyval=1; break;//第一行
		case 0x21: keyval=4; break;
		case 0x41: keyval=7; break;
		case 0x81: keyval=GETIN; break;
		case 0x12: keyval=2; break;//第二行
		case 0x22: keyval=5; break;
		case 0x42: keyval=8; break;
		case 0x82: keyval=0; break;
		case 0x14: keyval=3; break;//第三行
		case 0x24: keyval=6; break;
		case 0x44: keyval=9;break;
		case 0x84: keyval=GETOUT;break;
		case 0x18: keyval=KEYUP;break;//第四行
		case 0x28: keyval=CANCEL;break;
		case 0x48: keyval=ENTER;break;
		case 0x88: keyval=KEYDOWN;break;
		default:   keyval=16;break;
	}
	return keyval;
}

u16 GetKeyValue(void)
{
	u16 keyval = 16;
	KEY44PORT->ODR &= ~KEY44ROW;  //行线全部置0
	if(((KEY44PORT->IDR)&KEY44COL) != KEY44COL)//检测列线是否有0位出现
	{
		/*检测到有按键开始进入扫描*/
		u16 i,key,row;
		row = ~KEY44LSB;
		for(i=0;i<4;i++)
		{
			 KEY44PORT->ODR |= KEY44ROW;//有按键时，行线全部置高电平，准备扫描		
			 KEY44PORT->ODR &= row;
			 
			 if(((KEY44PORT->IDR)&KEY44COL) != KEY44COL)
			 {
			 	key = ((~((KEY44PORT->IDR)& KEY44COL))& KEY44COL)+(~(KEY44PORT->ODR) & KEY44ROW);
				switch((key>>KEY44LSBn))	   
				{	  //bit7~bit4:列线，4列；bit3~bit0:行线，4行
					case 0x11: keyval=1; break;//第一行
					case 0x21: keyval=4; break;
					case 0x41: keyval=7; break;
					case 0x81: keyval=GETIN; break;
					case 0x12: keyval=2; break;//第二行
					case 0x22: keyval=5; break;
					case 0x42: keyval=8; break;
					case 0x82: keyval=0; break;
					case 0x14: keyval=3; break;//第三行
					case 0x24: keyval=6; break;
					case 0x44: keyval=9;break;
					case 0x84: keyval=GETOUT;break;
					case 0x18: keyval=KEYUP;break;//第四行
					case 0x28: keyval=CANCEL;break;
					case 0x48: keyval=ENTER;break;
					case 0x88: keyval=KEYDOWN;break;
					default:   keyval=16;break;
				}
				break;
			 }
			KEY44PORT->ODR |= ~row;
		    row=(row<<1)|(KEY44LSB);
		}
	}
	return keyval;
}

