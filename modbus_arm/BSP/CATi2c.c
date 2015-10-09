/*-----------------------------------------------
  名称：IIC协议 
  论坛：www.doflye.net
  编写：shifang
  修改：无
  内容：函数是采用软件延时的方法产生SCL脉冲,固对高晶振频率要作 一定的修改....(本例是1us机器
		周期,即晶振频率要小于12MHZ)
------------------------------------------------*/  
  
              
#include "CATi2c.h"


#define  _Nop()   delay()  //定义空指令

#define SDA_H  GPIO_SetBits(GPIO_SDA,SDA_PIN) 
#define SDA_L  GPIO_ResetBits(GPIO_SDA,SDA_PIN)
#define SCL_H  GPIO_SetBits(GPIO_SCL,SCL_PIN) 
#define SCL_L  GPIO_ResetBits(GPIO_SCL,SCL_PIN)
#define SDA_IN GPIO_ReadInputDataBit(GPIO_SDA, SDA_PIN)

#define EXT1_SDA_H  GPIO_SetBits(EXT1_GPIO_SDA,EXT1_SDA_PIN) 
#define EXT1_SDA_L  GPIO_ResetBits(EXT1_GPIO_SDA,EXT1_SDA_PIN)
#define EXT1_SCL_H  GPIO_SetBits(EXT1_GPIO_SCL,EXT1_SCL_PIN) 
#define EXT1_SCL_L  GPIO_ResetBits(EXT1_GPIO_SCL,EXT1_SCL_PIN)
#define EXT1_SDA_IN GPIO_ReadInputDataBit(EXT1_GPIO_SDA, EXT1_SDA_PIN)

#define EXT2_SDA_H  GPIO_SetBits(EXT2_GPIO_SDA,EXT2_SDA_PIN) 
#define EXT2_SDA_L  GPIO_ResetBits(EXT2_GPIO_SDA,EXT2_SDA_PIN)
#define EXT2_SCL_H  GPIO_SetBits(EXT2_GPIO_SCL,EXT2_SCL_PIN) 
#define EXT2_SCL_L  GPIO_ResetBits(EXT2_GPIO_SCL,EXT2_SCL_PIN)
#define EXT2_SDA_IN GPIO_ReadInputDataBit(EXT2_GPIO_SDA, EXT2_SDA_PIN)
                         
u8 ack;	              //应答标志位

/*------------------------------------------------
                    启动总线
------------------------------------------------*/
static void EXT1_Start_I2c(void);
/*------------------------------------------------
                    结束总线
------------------------------------------------*/
static void EXT1_Stop_I2c(void);
/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: void  EXT1_SendByte(unsigned char c);
功能:  将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
     此状态位进行操作.(不应答或非应答都使ack=0 假)     
     发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
------------------------------------------------------------------*/
static void  EXT1_SendByte(u16 c);
/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: unsigned char  EXT1_RcvByte();
功能:  用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
     发完后请用应答函数。  
------------------------------------------------------------------*/	
static unsigned char  EXT1_RcvByte(void);
/*----------------------------------------------------------------
                     应答子函数
原型:  void EXT1_Ack_I2c(void);
----------------------------------------------------------------*/
static void EXT1_Ack_I2c(void);
/*----------------------------------------------------------------
                     非应答子函数
原型:  void EXT1_NoAck_I2c(void);
----------------------------------------------------------------*/
static void EXT1_NoAck_I2c(void);


/*------------------------------------------------
                    启动总线
------------------------------------------------*/
static void EXT2_Start_I2c(void);
/*------------------------------------------------
                    结束总线
------------------------------------------------*/
static void EXT2_Stop_I2c(void);
/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: void  EXT2_SendByte(unsigned char c);
功能:  将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
     此状态位进行操作.(不应答或非应答都使ack=0 假)     
     发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
------------------------------------------------------------------*/
static void  EXT2_SendByte(u16 c);
/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: unsigned char  EXT2_RcvByte();
功能:  用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
     发完后请用应答函数。  
------------------------------------------------------------------*/	
static unsigned char  EXT2_RcvByte(void);
/*----------------------------------------------------------------
                     应答子函数
原型:  void EXT2_Ack_I2c(void);
----------------------------------------------------------------*/
static void EXT2_Ack_I2c(void);
/*----------------------------------------------------------------
                     非应答子函数
原型:  void EXT2_NoAck_I2c(void);
----------------------------------------------------------------*/
static void EXT2_NoAck_I2c(void);


/*------------------------------------------------
                    启动总线
------------------------------------------------*/
static void Start_I2c(void);
/*------------------------------------------------
                    结束总线
------------------------------------------------*/
static void Stop_I2c(void);
/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: void  SendByte(unsigned char c);
功能:  将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
     此状态位进行操作.(不应答或非应答都使ack=0 假)     
     发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
------------------------------------------------------------------*/
static void  SendByte(u16 c);
/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: unsigned char  RcvByte();
功能:  用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
     发完后请用应答函数。  
------------------------------------------------------------------*/	
static unsigned char  RcvByte(void);
/*----------------------------------------------------------------
                     应答子函数
原型:  void Ack_I2c(void);
----------------------------------------------------------------*/
static void Ack_I2c(void);
/*----------------------------------------------------------------
                     非应答子函数
原型:  void NoAck_I2c(void);
----------------------------------------------------------------*/
static void NoAck_I2c(void);

static void delay(void)
{
	u16 i = 0x0f;
	while(i--);
}

void WriteCATData(u8 add, u8 subadd ,u16 dat)//16位的数，高有效
{
	dat = ~dat;//按位取反
   Start_I2c();               //启动总线
   SendByte(add);             //发送器件地址
     if(ack==0)return;
   SendByte(subadd);            //发送器件子地址
     if(ack==0)return;
   SendByte((u8)(dat&0x00ff));             //发送数据1
     if(ack==0)return;
   SendByte((u8)((dat&0xff00)>>8));             //发送数据2
     if(ack==0)return;
   Stop_I2c();  
}			 

u16 ReadCATData(u8 add)
 {
   unsigned char Val1=0,Val2=0;
	u16 Val;
   Start_I2c();               //启动总线
   SendByte(add);             //发送器件地址
     if(ack==0)return(0);
   SendByte(0);             //发送器件地址
     if(ack==0)return(0);

	Start_I2c();               //启动总线
	SendByte(add+1);             //发送器件地址
	  if(ack==0)return(0);
   Val1=RcvByte();
   Ack_I2c();                 //发送应答位

   Val2=RcvByte();
   NoAck_I2c();                 //发送非应答位
   Stop_I2c();                  //结束总线

	Val = (u16)Val2*256 + (u16)Val1;
  return(Val);
 }	 

void I2CIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);

	/* PA1,0 SCL and SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //设置管脚为复用功能开漏输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);          //I2C接口使用的GPIO管脚初始化

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG ,ENABLE);

	/* 扩展部分PG13,14,8,9 SCL and SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //设置管脚为复用功能开漏输出
	GPIO_Init(GPIOG, &GPIO_InitStructure);          //I2C接口使用的GPIO管脚初始化
}

void CAT955Init(void)
{
  I2CIOInit();
  WriteCATData(AddCATlock,0x06,0xffff);//设置CATlock方向为输出
  WriteCATData(AddCATlock,0x02,0);//关所有箱子

  WriteCATData(AddCATdoor,0x06,0);//设置CATdoor方向为输入
  WriteCATData(AddCATstatus,0x06,0);//设置CATstatus方向为输入
  WriteCATData(AddCATdoor,0x04,0);//设置CATdoor极性反转
  WriteCATData(AddCATstatus,0x04,0);//设置CATstatus极性反转
/*扩展部分*/
  EXT1_WriteCATData(EXT1_AddCATlock1,0x06,0xffff);//设置CATlock方向为输出
  EXT1_WriteCATData(EXT1_AddCATlock1,0x02,0);//关所有箱子

  EXT1_WriteCATData(EXT1_AddCATdoor1,0x06,0);//设置CATdoor方向为输入
  EXT1_WriteCATData(EXT1_AddCATstatus1,0x06,0);//设置CATstatus方向为输入
  EXT1_WriteCATData(EXT1_AddCATdoor1,0x04,0);//设置CATdoor极性反转
  EXT1_WriteCATData(EXT1_AddCATstatus1,0x04,0);//设置CATstatus极性反转

  EXT1_WriteCATData(EXT1_AddCATlock2,0x06,0xffff);//设置CATlock方向为输出
  EXT1_WriteCATData(EXT1_AddCATlock2,0x02,0);//关所有箱子

  EXT1_WriteCATData(EXT1_AddCATdoor2,0x06,0);//设置CATdoor方向为输入
  EXT1_WriteCATData(EXT1_AddCATstatus2,0x06,0);//设置CATstatus方向为输入
  EXT1_WriteCATData(EXT1_AddCATdoor2,0x04,0);//设置CATdoor极性反转
  EXT1_WriteCATData(EXT1_AddCATstatus2,0x04,0);//设置CATstatus极性反转

  EXT2_WriteCATData(EXT2_AddCATlock1,0x06,0xffff);//设置CATlock方向为输出
  EXT2_WriteCATData(EXT2_AddCATlock1,0x02,0);//关所有箱子

  EXT2_WriteCATData(EXT2_AddCATdoor1,0x06,0);//设置CATdoor方向为输入
  EXT2_WriteCATData(EXT2_AddCATstatus1,0x06,0);//设置CATstatus方向为输入
  EXT2_WriteCATData(EXT2_AddCATdoor1,0x04,0);//设置CATdoor极性反转
  EXT2_WriteCATData(EXT2_AddCATstatus1,0x04,0);//设置CATstatus极性反转

  EXT2_WriteCATData(EXT2_AddCATlock2,0x06,0xffff);//设置CATlock方向为输出
  EXT2_WriteCATData(EXT2_AddCATlock1,0x02,0);//关所有箱子

  EXT2_WriteCATData(EXT2_AddCATdoor2,0x06,0);//设置CATdoor方向为输入
  EXT2_WriteCATData(EXT2_AddCATstatus2,0x06,0);//设置CATstatus方向为输入
  EXT2_WriteCATData(EXT2_AddCATdoor2,0x04,0);//设置CATdoor极性反转
  EXT2_WriteCATData(EXT2_AddCATstatus2,0x04,0);//设置CATstatus极性反转
}

/*------------------------------------------------
                    启动总线
------------------------------------------------*/
void Start_I2c(void)
{
  SDA_H;   //发送起始条件的数据信号
  _Nop();
  SCL_H;
  _Nop();    //起始条件建立时间大于4.7us,延时
  _Nop();
  _Nop();
  _Nop();
  _Nop();    
  SDA_L;     //发送起始信号
  _Nop();    //起始条件锁定时间大于4μ
  _Nop();
  _Nop();
  _Nop();
  _Nop();       
  SCL_L;    //钳住I2C总线，准备发送或接收数据
  _Nop();
  _Nop();
}
/*------------------------------------------------
                    结束总线
------------------------------------------------*/
void Stop_I2c(void)
{
  SDA_L;    //发送结束条件的数据信号
  _Nop();   //发送结束条件的时钟信号
  SCL_H;    //结束条件建立时间大于4μ
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  SDA_H;    //发送I2C总线结束信号
  _Nop();
  _Nop();
  _Nop();
  _Nop();
}




/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: void  SendByte(unsigned char c);
功能:  将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
     此状态位进行操作.(不应答或非应答都使ack=0 假)     
     发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
------------------------------------------------------------------*/
void  SendByte(u16 c)
{
 unsigned char BitCnt;
 
 for(BitCnt=0;BitCnt<8;BitCnt++)  //要传送的数据长度为8位
    {
     if((c<<BitCnt)&0x80)SDA_H;   //判断发送位
       else  SDA_L;                
     _Nop();
     SCL_H;               //置时钟线为高，通知被控器开始接收数据位
      _Nop(); 
      _Nop();             //保证时钟高电平周期大于4μ
      _Nop();
      _Nop();
      _Nop();         
     SCL_L; 
    }
    
    _Nop();
    _Nop();
    SDA_H;               //8位发送完后释放数据线，准备接收应答位
    _Nop();
    _Nop();   
    SCL_H;
//    _Nop();
//    _Nop();
	 SDA_H;//读值之前先拉高
    _Nop();
    if(SDA_IN == 1)ack=0;     
       else ack=1;        //判断是否接收到应答信号
    SCL_L;
    _Nop();
    _Nop();
}







/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: unsigned char  RcvByte();
功能:  用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
     发完后请用应答函数。  
------------------------------------------------------------------*/	
unsigned char  RcvByte(void)
{
  unsigned char retc;
  unsigned char BitCnt;
  
  retc=0; 
  SDA_H;             //置数据线为输入方式
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        _Nop();           
        SCL_L;       //置时钟线为低，准备接收数据位
        _Nop();
        _Nop();      //时钟低电平周期大于4.7us
        _Nop();
        _Nop();
        _Nop();
        SCL_H;       //置时钟线为高使数据线上数据有效
        _Nop();
		  SDA_H;//读之前拉高
        _Nop();
        retc=retc<<1;
        if(SDA_IN == 1)retc=retc+1; //读数据位,接收的数据位放入retc中
        _Nop();
        _Nop(); 
      }
  SCL_L;    
  _Nop();
  _Nop();
  return(retc);
}



/*----------------------------------------------------------------
                     应答子函数
原型:  void Ack_I2c(void);
 
----------------------------------------------------------------*/
void Ack_I2c(void)
{
  
  SDA_L;     
  _Nop();
  _Nop();
  _Nop();      
  SCL_H;
  _Nop();
  _Nop();              //时钟低电平周期大于4μ
  _Nop();
  _Nop();
  _Nop();  
  SCL_L;               //清时钟线，钳住I2C总线以便继续接收
  _Nop();
  _Nop();    
}
/*----------------------------------------------------------------
                     非应答子函数
原型:  void NoAck_I2c(void);
 
----------------------------------------------------------------*/
void NoAck_I2c(void)
{
  
  SDA_H;
  _Nop();
  _Nop();
  _Nop();      
  SCL_H;
  _Nop();
  _Nop();              //时钟低电平周期大于4μ
  _Nop();
  _Nop();
  _Nop();  
  SCL_L;                //清时钟线，钳住I2C总线以便继续接收
  _Nop();
  _Nop();    
}



void EXT1_WriteCATData(u8 add, u8 subadd ,u16 dat)//16位的数，高有效
{
	dat = ~dat;//按位取反
   EXT1_Start_I2c();               //启动总线
   EXT1_SendByte(add);             //发送器件地址
     if(ack==0)return;
   EXT1_SendByte(subadd);            //发送器件子地址
     if(ack==0)return;
   EXT1_SendByte((u8)(dat&0x00ff));             //发送数据1
     if(ack==0)return;
   EXT1_SendByte((u8)((dat&0xff00)>>8));             //发送数据2
     if(ack==0)return;
   EXT1_Stop_I2c();  
}			 

u16 EXT1_ReadCATData(u8 add)
 {
   unsigned char Val1=0,Val2=0;
	u16 Val;
   EXT1_Start_I2c();               //启动总线
   EXT1_SendByte(add);             //发送器件地址
     if(ack==0)return(0);
   EXT1_SendByte(0);             //发送器件地址
     if(ack==0)return(0);

	EXT1_Start_I2c();               //启动总线
	EXT1_SendByte(add+1);             //发送器件地址
	  if(ack==0)return(0);
   Val1=EXT1_RcvByte();
   EXT1_Ack_I2c();                 //发送应答位

   Val2=EXT1_RcvByte();
   EXT1_NoAck_I2c();                 //发送非应答位
   EXT1_Stop_I2c();                  //结束总线

	Val = (u16)Val2*256 + (u16)Val1;
  return(Val);
 }	 

/*------------------------------------------------
                    启动总线
------------------------------------------------*/
void EXT1_Start_I2c(void)
{
  EXT1_SDA_H;   //发送起始条件的数据信号
  _Nop();
  EXT1_SCL_H;
  _Nop();    //起始条件建立时间大于4.7us,延时
  _Nop();
  _Nop();
  _Nop();
  _Nop();    
  EXT1_SDA_L;     //发送起始信号
  _Nop();    //起始条件锁定时间大于4μ
  _Nop();
  _Nop();
  _Nop();
  _Nop();       
  EXT1_SCL_L;    //钳住I2C总线，准备发送或接收数据
  _Nop();
  _Nop();
}
/*------------------------------------------------
                    结束总线
------------------------------------------------*/
void EXT1_Stop_I2c(void)
{
  EXT1_SDA_L;    //发送结束条件的数据信号
  _Nop();   //发送结束条件的时钟信号
  EXT1_SCL_H;    //结束条件建立时间大于4μ
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  EXT1_SDA_H;    //发送I2C总线结束信号
  _Nop();
  _Nop();
  _Nop();
  _Nop();
}




/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: void  EXT1_SendByte(unsigned char c);
功能:  将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
     此状态位进行操作.(不应答或非应答都使ack=0 假)     
     发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
------------------------------------------------------------------*/
void  EXT1_SendByte(u16 c)
{
 unsigned char BitCnt;
 
 for(BitCnt=0;BitCnt<8;BitCnt++)  //要传送的数据长度为8位
    {
     if((c<<BitCnt)&0x80)EXT1_SDA_H;   //判断发送位
       else  EXT1_SDA_L;                
     _Nop();
     EXT1_SCL_H;               //置时钟线为高，通知被控器开始接收数据位
      _Nop(); 
      _Nop();             //保证时钟高电平周期大于4μ
      _Nop();
      _Nop();
      _Nop();         
     EXT1_SCL_L; 
    }
    
    _Nop();
    _Nop();
    EXT1_SDA_H;               //8位发送完后释放数据线，准备接收应答位
    _Nop();
    _Nop();   
    EXT1_SCL_H;
//    _Nop();
//    _Nop();
	 EXT1_SDA_H;//读值之前先拉高
    _Nop();
    if(EXT1_SDA_IN == 1)ack=0;     
       else ack=1;        //判断是否接收到应答信号
    EXT1_SCL_L;
    _Nop();
    _Nop();
}







/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: unsigned char  EXT1_RcvByte();
功能:  用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
     发完后请用应答函数。  
------------------------------------------------------------------*/	
unsigned char  EXT1_RcvByte(void)
{
  unsigned char retc;
  unsigned char BitCnt;
  
  retc=0; 
  EXT1_SDA_H;             //置数据线为输入方式
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        _Nop();           
        EXT1_SCL_L;       //置时钟线为低，准备接收数据位
        _Nop();
        _Nop();      //时钟低电平周期大于4.7us
        _Nop();
        _Nop();
        _Nop();
        EXT1_SCL_H;       //置时钟线为高使数据线上数据有效
        _Nop();
		  EXT1_SDA_H;//读之前拉高
        _Nop();
        retc=retc<<1;
        if(EXT1_SDA_IN == 1)retc=retc+1; //读数据位,接收的数据位放入retc中
        _Nop();
        _Nop(); 
      }
  EXT1_SCL_L;    
  _Nop();
  _Nop();
  return(retc);
}



/*----------------------------------------------------------------
                     应答子函数
原型:  void EXT1_Ack_I2c(void);
 
----------------------------------------------------------------*/
void EXT1_Ack_I2c(void)
{
  
  EXT1_SDA_L;     
  _Nop();
  _Nop();
  _Nop();      
  EXT1_SCL_H;
  _Nop();
  _Nop();              //时钟低电平周期大于4μ
  _Nop();
  _Nop();
  _Nop();  
  EXT1_SCL_L;               //清时钟线，钳住I2C总线以便继续接收
  _Nop();
  _Nop();    
}
/*----------------------------------------------------------------
                     非应答子函数
原型:  void EXT1_NoAck_I2c(void);
 
----------------------------------------------------------------*/
void EXT1_NoAck_I2c(void)
{
  
  EXT1_SDA_H;
  _Nop();
  _Nop();
  _Nop();      
  EXT1_SCL_H;
  _Nop();
  _Nop();              //时钟低电平周期大于4μ
  _Nop();
  _Nop();
  _Nop();  
  EXT1_SCL_L;                //清时钟线，钳住I2C总线以便继续接收
  _Nop();
  _Nop();    
}

void EXT2_WriteCATData(u8 add, u8 subadd ,u16 dat)//16位的数，高有效
{
	dat = ~dat;//按位取反
   EXT2_Start_I2c();               //启动总线
   EXT2_SendByte(add);             //发送器件地址
     if(ack==0)return;
   EXT2_SendByte(subadd);            //发送器件子地址
     if(ack==0)return;
   EXT2_SendByte((u8)(dat&0x00ff));             //发送数据1
     if(ack==0)return;
   EXT2_SendByte((u8)((dat&0xff00)>>8));             //发送数据2
     if(ack==0)return;
   EXT2_Stop_I2c();  
}			 

u16 EXT2_ReadCATData(u8 add)
 {
   unsigned char Val1=0,Val2=0;
	u16 Val;
   EXT2_Start_I2c();               //启动总线
   EXT2_SendByte(add);             //发送器件地址
     if(ack==0)return(0);
   EXT2_SendByte(0);             //发送器件地址
     if(ack==0)return(0);

	EXT2_Start_I2c();               //启动总线
	EXT2_SendByte(add+1);             //发送器件地址
	  if(ack==0)return(0);
   Val1=EXT2_RcvByte();
   EXT2_Ack_I2c();                 //发送应答位

   Val2=EXT2_RcvByte();
   EXT2_NoAck_I2c();                 //发送非应答位
   EXT2_Stop_I2c();                  //结束总线

	Val = (u16)Val2*256 + (u16)Val1;
  return(Val);
 }	 
/*------------------------------------------------
                    启动总线
------------------------------------------------*/
void EXT2_Start_I2c(void)
{
  EXT2_SDA_H;   //发送起始条件的数据信号
  _Nop();
  EXT2_SCL_H;
  _Nop();    //起始条件建立时间大于4.7us,延时
  _Nop();
  _Nop();
  _Nop();
  _Nop();    
  EXT2_SDA_L;     //发送起始信号
  _Nop();    //起始条件锁定时间大于4μ
  _Nop();
  _Nop();
  _Nop();
  _Nop();       
  EXT2_SCL_L;    //钳住I2C总线，准备发送或接收数据
  _Nop();
  _Nop();
}
/*------------------------------------------------
                    结束总线
------------------------------------------------*/
void EXT2_Stop_I2c(void)
{
  EXT2_SDA_L;    //发送结束条件的数据信号
  _Nop();   //发送结束条件的时钟信号
  EXT2_SCL_H;    //结束条件建立时间大于4μ
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  EXT2_SDA_H;    //发送I2C总线结束信号
  _Nop();
  _Nop();
  _Nop();
  _Nop();
}




/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: void  EXT2_SendByte(unsigned char c);
功能:  将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
     此状态位进行操作.(不应答或非应答都使ack=0 假)     
     发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
------------------------------------------------------------------*/
void  EXT2_SendByte(u16 c)
{
 unsigned char BitCnt;
 
 for(BitCnt=0;BitCnt<8;BitCnt++)  //要传送的数据长度为8位
    {
     if((c<<BitCnt)&0x80)EXT2_SDA_H;   //判断发送位
       else  EXT2_SDA_L;                
     _Nop();
     EXT2_SCL_H;               //置时钟线为高，通知被控器开始接收数据位
      _Nop(); 
      _Nop();             //保证时钟高电平周期大于4μ
      _Nop();
      _Nop();
      _Nop();         
     EXT2_SCL_L; 
    }
    
    _Nop();
    _Nop();
    EXT2_SDA_H;               //8位发送完后释放数据线，准备接收应答位
    _Nop();
    _Nop();   
    EXT2_SCL_H;
//    _Nop();
//    _Nop();
	 EXT2_SDA_H;//读值之前先拉高
    _Nop();
    if(EXT2_SDA_IN == 1)ack=0;     
       else ack=1;        //判断是否接收到应答信号
    EXT2_SCL_L;
    _Nop();
    _Nop();
}







/*----------------------------------------------------------------
                 字节数据传送函数               
函数原型: unsigned char  EXT2_RcvByte();
功能:  用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
     发完后请用应答函数。  
------------------------------------------------------------------*/	
unsigned char  EXT2_RcvByte(void)
{
  unsigned char retc;
  unsigned char BitCnt;
  
  retc=0; 
  EXT2_SDA_H;             //置数据线为输入方式
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        _Nop();           
        EXT2_SCL_L;       //置时钟线为低，准备接收数据位
        _Nop();
        _Nop();      //时钟低电平周期大于4.7us
        _Nop();
        _Nop();
        _Nop();
        EXT2_SCL_H;       //置时钟线为高使数据线上数据有效
        _Nop();
		  EXT2_SDA_H;//读之前拉高
        _Nop();
        retc=retc<<1;
        if(EXT2_SDA_IN == 1)retc=retc+1; //读数据位,接收的数据位放入retc中
        _Nop();
        _Nop(); 
      }
  EXT2_SCL_L;    
  _Nop();
  _Nop();
  return(retc);
}



/*----------------------------------------------------------------
                     应答子函数
原型:  void EXT2_Ack_I2c(void);
 
----------------------------------------------------------------*/
void EXT2_Ack_I2c(void)
{
  
  EXT2_SDA_L;     
  _Nop();
  _Nop();
  _Nop();      
  EXT2_SCL_H;
  _Nop();
  _Nop();              //时钟低电平周期大于4μ
  _Nop();
  _Nop();
  _Nop();  
  EXT2_SCL_L;               //清时钟线，钳住I2C总线以便继续接收
  _Nop();
  _Nop();    
}
/*----------------------------------------------------------------
                     非应答子函数
原型:  void EXT2_NoAck_I2c(void);
 
----------------------------------------------------------------*/
void EXT2_NoAck_I2c(void)
{
  
  EXT2_SDA_H;
  _Nop();
  _Nop();
  _Nop();      
  EXT2_SCL_H;
  _Nop();
  _Nop();              //时钟低电平周期大于4μ
  _Nop();
  _Nop();
  _Nop();  
  EXT2_SCL_L;                //清时钟线，钳住I2C总线以便继续接收
  _Nop();
  _Nop();    
}





