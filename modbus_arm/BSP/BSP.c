#include "includes.h"
#include "UART485.h"

void CAT955Init(void);

/*
 * 函数名：BSP_Init
 * 描述  ：时钟初始化、硬件初始化、外围模块初始化
 * 输入  ：无
 * 输出  ：无
 */
void BSP_Init(void)
{
    SystemInit();		/* 配置系统时钟为72M */	
	 SysTick_init();		/* 初始化并使能SysTick定时器 */
	 NVIC_Configuration();
//	 TIME_Configuration();//定时器初始化

	 GPRS_UART485_init(57600);
	 ICcardInit();
	 BarCodeInit(9600);

	 LEDIOinit();

	 CAT955Init();
//	 TIM_Cmd(TIM2,ENABLE);//使能TIM2 
}

/*
 * 函数名：SysTick_init
 * 描述  ：配置SysTick定时器
 * 输入  ：无
 * 输出  ：无
 */
void SysTick_init(void)
{
    SysTick_Config(SystemFrequency/OS_TICKS_PER_SEC);//初始化并使能SysTick定时器
}

void InterruptConfig(void)
{   
  /* Set the Vector Table base address at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00000);

}

void NVIC_Configuration(void)
{
	/* Enable the TIME1 Interrupt */
	NVIC_InitTypeDef 	NVIC_InitStruct;//定义一个设置中断的结构体
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//抢断式优先级1、、、3

	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;	 //打开TIM2中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//主优先级0，最高
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;	 //子优先级1
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //中断使能
	NVIC_Init(&NVIC_InitStruct);

/*	Enable the USART3 Interrupt 条码扫描   */
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//打开该中断
	NVIC_Init(&NVIC_InitStruct);

/*	Enable the USART1 Interrupt  modbus中断初始化	*/
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//打开该中断
	NVIC_Init(&NVIC_InitStruct);

/*IC 卡中断初始化*/
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;	  	//通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;	  		//通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);	 
}

void TIME_Configuration(void)//定时器初始化
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;//定义一个设置TIME的结构体
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);//使能TIME2时钟
	TIM_DeInit(TIM2);//复位定时器
	TIM_TimeBaseStruct.TIM_Prescaler = (7200-1);//时钟预分频
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//上升模式
	TIM_TimeBaseStruct.TIM_Period = 200;	//周期200
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct); 

	TIM_ClearFlag(TIM2 , TIM_FLAG_Update);	//清除中断标志
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //使能中断
	TIM_Cmd(TIM2,DISABLE);//使能TIM2 
}

/*蜂鸣器IO初始化*/
void BuzzerIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);

	/* PA1,0 SCL and SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	#if OLD_NEW_BOARD
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置管脚为复用功能推挽输出
	#else
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //设置管脚为复用功能开漏输出
	#endif
	GPIO_Init(GPIOA, &GPIO_InitStructure);          //I2C接口使用的GPIO管脚初始化	

	BeepOFF;
}

void LEDIOinit(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG , ENABLE);//使能LED使用的GPIO时钟
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 + GPIO_Pin_12;//配置使能GPIO管脚
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//配置GPIO模式,开漏复用功能
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度

 GPIO_Init(GPIOG , &GPIO_InitStructure);//将使用LED灯相关的GPIO初始化
 GPIO_SetBits(GPIOG , GPIO_Pin_11 + GPIO_Pin_12);//关闭所有的ＬＥＤ指示灯

/*按键初始化*/
// RCC_APB2PeriphClockCmd(RCC_GPIO_KEY , ENABLE);//使能LED使用的GPIO时钟
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//配置使能GPIO管脚
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//配置GPIO模式,输入上拉
 //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度

 GPIO_Init(GPIOG , &GPIO_InitStructure);//复位按键初始化
}

/*条码扫描头初始化*/
void BarCodeInit(unsigned long ulBaud)
{
	USART_InitTypeDef USART_InitSturct;//定义串口的初始化结构体

	GPIO_InitTypeDef GPIO_InitStruct;//定义串口对应管脚的结构体

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);//时钟使能	RCC_APB1Periph_UART5 | 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC, ENABLE);//打开串口管脚时钟

	//USART3_Tx_Pin Configure
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10;//输出引脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//设置最高速度50MHz
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//推挽复用输出
	GPIO_Init(GPIOB , &GPIO_InitStruct);//将初始化好的结构体装入寄存器
//USART3_Rx_Pin Configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO模式悬浮输入
  GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_11;//输入引脚
  GPIO_Init(GPIOB, &GPIO_InitStruct);//将初始化好的结构体装入寄存器
  	
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART3 , ENABLE);//时钟使能
	USART_InitSturct.USART_BaudRate = ulBaud;//波特率9600
	USART_InitSturct.USART_WordLength = USART_WordLength_8b;//数据宽度8位
	USART_InitSturct.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitSturct.USART_Parity = USART_Parity_No;//无奇偶校验
	USART_InitSturct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitSturct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//使能发送与接收

//USART3 Configure
	USART_Init(USART3 , &USART_InitSturct);//将初始化好的结构体装入寄存器
	USART_ClearFlag(USART3 , USART_FLAG_TC);
	USART_ITConfig(USART3 , USART_IT_RXNE , ENABLE);//使能接收中断
	//	USART_ITConfig(USART3 , USART_IT_TXE , ENABLE);
	USART_Cmd(USART3 , ENABLE);//打开串口
}

void ICcardInit( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
/*GPIO init*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			   //Weigand26  D1中断
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//下拉输入
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			       //Weigand26  D0中断
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_Init(GPIOB, &GPIO_InitStructure);

/*EXIT init*/
	
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource0);	
	EXTI_ClearITPendingBit( EXTI_Line0 );
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init( &EXTI_InitStructure );

	GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource1);	
	EXTI_ClearITPendingBit( EXTI_Line1 );
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init( &EXTI_InitStructure );
}

/*使能IC读卡器中断*/
void ICcardEnable(void)
{
	NVIC_InitTypeDef 	NVIC_InitStruct;//定义一个设置中断的结构体

	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;	  	//通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;	  		//通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

/*禁能IC读卡器中断*/
void ICcardDisable(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;//定义一个设置中断的结构体

	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;	  	//通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;	  		//通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStruct);
}
