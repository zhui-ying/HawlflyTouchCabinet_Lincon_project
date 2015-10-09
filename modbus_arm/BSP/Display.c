#include "Display.h"
#include "wordlib.h"
#include "string.h"

void LCDPutChar(u8 x , u8 y , u8 *data);
void LCDPutCH(u8 x , u8 y , u8 *data);

u8 LCDbuf[8][128];//显示映射缓冲区

void GPIO_Configuration(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStructure; 

	RCC_APB2PeriphClockCmd(RCC_GPIO_RS | RCC_GPIO_RW | RCC_GPIO_EN |
	                           RCC_GPIO_CS1 | RCC_GPIO_CS2 | RCC_GPIO_DATA , ENABLE);  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                 //设置GPIO的工作状态 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                               //设置GPIO的速度 

	GPIO_InitStructure.GPIO_Pin=RS_PIN;
  GPIO_Init(GPIO_RS, &GPIO_InitStructure);
	                                 
	GPIO_InitStructure.GPIO_Pin=RW_PIN;
  GPIO_Init(GPIO_RW, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin=EN_PIN;
  GPIO_Init(GPIO_EN, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin=CS1_PIN;
  GPIO_Init(GPIO_CS1, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin=CS2_PIN;
  GPIO_Init(GPIO_CS2, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin=DATA_PIN;
  GPIO_Init(GPIO_DATA, &GPIO_InitStructure); 
}

void Delay(u32 z) 
{ 
          u32 x,y;  
        for(x=z;x>0;x--) 
                for(y=27;y>0;y--); 
} 

void OutPutData(u8 data)	 //输出数据
{
	GPIO_DATA->BSRR = 0x00ff0000;	//清零对应位
	GPIO_DATA->BSRR = (data);//  |0x00ff0000
}
 
void lcd_busy(void) 
{
		OutPutData(0xff);
    Delay(1);
}

/*写指令*/
void WriteComm(u8 comm)
{
	lcd_busy();
	RSL;
	 RWL;
	OutPutData(comm);  //列地址赋值，x取值0----64
	ENH;
	 Delay(2);
	 ENL;
}

/*写数据*/
void WriteData(u8 data)
{
	lcd_busy(); 
	RSH;
	RWL;
	OutPutData(data);  //数据送显
	ENH;
	 Delay(2);
	ENL;
	OutPutData(0xff);
}   

/*定位x0-127 y0-7*/
void set_xy(u8 x,u8 y) 
{
   if (x>=64)   
   	{
   		CS1H;
   		Delay(1);
   		CS2L;
   	} 
   else         
   	{
   		CS1L;
   		Delay(1);
   		CS2H;
   	}
	WriteComm(0x40|x);
    WriteComm(0xb8|y);
    OutPutData(0xff);  //判别是左半屏，还是右半屏
}

/*在指定位置写数据*/
void lw(u8 x,u8 y,u8 dd) 
{
	set_xy(x,y);
	WriteData(dd);
}

/*刷新一行屏幕*/
void RefreshOneLine(u8 x_start , u8 x_end , u8 y)
{
	u8 *pLCD;
	set_xy(x_start,y*2);
	for(pLCD = &LCDbuf[y*2][x_start] ; pLCD<&LCDbuf[y*2][64];)
	{
		WriteData(*pLCD++);
	}
	set_xy(x_start,y*2+1);
	for(pLCD = &LCDbuf[y*2+1][x_start] ; pLCD<&LCDbuf[y*2+1][64];)
	{
		WriteData(*pLCD++);
	}

	set_xy(64,y*2);
	for(pLCD = &LCDbuf[y*2][64] ; pLCD<&LCDbuf[y*2][x_end];)
	{
		WriteData(*pLCD++);
	}
	set_xy(64,y*2+1);
	for(pLCD = &LCDbuf[y*2+1][64] ; pLCD<&LCDbuf[y*2+1][x_end];)
	{
		WriteData(*pLCD++);
	}
	memset(LCDbuf[y*2] , 0 ,128);
	memset(LCDbuf[y*2+1] , 0 ,128);
}

/*刷新屏幕*/
void RefreshLCD(void)
{
	u8 *pLCD;
	u8 i;

	for(i=0;i<8;i++)//刷新左半屏
	{
		set_xy(0,i);
		for(pLCD = &LCDbuf[i][0] ; pLCD<&LCDbuf[i][64];)
		{
			WriteData(*pLCD++);
		}
	}

	for(i=0;i<8;i++) //刷新右半屏
	{
		set_xy(64,i);
		for(pLCD = &LCDbuf[i][64] ; pLCD<=&LCDbuf[i][127];)
		{
			WriteData(*pLCD++);
		}
	}
	memset(LCDbuf , 0 , 1024);//刷屏后清映射区
}

/*显示一行，查找字库将对应的模填入到LCDbuf中
x0-127  y0-3
*/
void Display1Line(u8 x , u8 y ,const u8 *buf)
{
	u8 *tempbuf;
	u8 i=0;
	for(tempbuf = (u8 *)buf ; *tempbuf!='\0';)
	{
		if(*tempbuf < 0x80)	  
		{
			LCDPutChar(6*i+x , 2*y ,tempbuf);  //asc码字符库
			tempbuf++;
			i++;
		}
		else
		{
			LCDPutCH(6*i+x , 2*y , tempbuf);//汉字字符集
			i+=2;
			tempbuf+=2;
		}
	}
}

/*
写入一个数据
查找asc码字符库 , 写入LCDbuf
x0-127 y 0-7
*/
void LCDPutChar(u8 x , u8 y , u8 *data)
{
  u8 i;
  const ASCWORD *pchar;
  pchar = asc_code;
  if(x>121 || y>7)
  {
  	return;
  }
  while(pchar->index[0] != '\0')
  {
  	 if(pchar->index[0] == *data)
	 {
	 	for(i=0;i<6;i++)
		{
			LCDbuf[y][x+i] = pchar->msk[2*i];
			LCDbuf[y+1][x+i] = pchar->msk[2*i+1];
		}
		return;
	 }
	 pchar++;
  }
}

/*
写入一个汉字数据
查找汉字码字符库 , 写入LCDbuf
x0-127 y 0-7
*/
void LCDPutCH(u8 x , u8 y , u8 *data)
{
  u8 i;
  const CHWORD *pch;
  pch = cha_code;
  if(x>115 || y>7)
  {
  	return;
  }
  while(pch->index[0] != '\0')
  {
  	 if(pch->index[0] == *data && pch->index[1] == *(data+1))
	 {
	 	for(i=0;i<12;i++)
		{
			LCDbuf[y][x+i] = pch->msk[2*i];
			LCDbuf[y+1][x+i] = pch->msk[2*i+1];
		}
		return;
	 }
	 pch++;
  }
}

void LCDinit(void) 
{ 
		GPIO_Configuration();

		ENL;	RSL;  RWL;
		CS1H;	CS2H;		
		CS1L;	CS2H;		
		RSL;	RWL;		
		OutPutData(0x3f); //开显示
		ENH;	Delay(5);	 ENL;		
		CS1L; CS2H;		
		RSL;	RWL;		
		OutPutData(0xc0);//显示首行
		ENH;	Delay(5);	 ENL;
		CS1L;	CS2L;		
		CS1H; CS2L;		
		RSL;	RWL;		
		OutPutData(0x3f);
		ENH;	Delay(5);	 ENL;
		CS1H;	 CS2L;		
		RSL;	RWL;		
		OutPutData(0xc0);
		ENH; 	Delay(5);  ENL;		
		CS1L;	CS2L;		
//		clr_screen();
		CS1H;CS2H;//清屏
}
