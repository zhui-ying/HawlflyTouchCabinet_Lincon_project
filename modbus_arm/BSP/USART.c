#include "USART.h"

void USART1_Conf(u32 baudRate)
{
	USART_InitTypeDef USART_InitSturct;//定义串口1的初始化结构体

	GPIO_InitTypeDef GPIO_InitStruct;//定义串口对应管脚的结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA , ENABLE);//打开串口管脚时钟
	//USART1_Tx_Pin Configure
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;//输出引脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//设置最高速度50MHz
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//推挽复用输出
	GPIO_Init(GPIOA , &GPIO_InitStruct);//将初始化好的结构体装入寄存器
//USART1_Rx_Pin Configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO模式悬浮输入
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;//输入引脚
  GPIO_Init(GPIOA, &GPIO_InitStruct);//将初始化好的结构体装入寄存器

//USART1 Configure	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);//时钟使能
	USART_InitSturct.USART_BaudRate = baudRate;//波特率38400
	USART_InitSturct.USART_WordLength = USART_WordLength_8b;//数据宽度8位
	USART_InitSturct.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitSturct.USART_Parity = USART_Parity_No;//无奇偶校验
	USART_InitSturct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitSturct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//使能发送与接收
	USART_Init(USART1 , &USART_InitSturct);//将初始化好的结构体装入寄存器
	USART_ClearFlag(USART1 , USART_FLAG_TC);
	//USART1_INT Configure
//	USART_ITConfig(USART1 , USART_IT_RXNE , ENABLE);//使能接收中断
//	USART_ITConfig(USART1 , USART_IT_TXE , ENABLE);
	USART_Cmd(USART1 , ENABLE);//打开串口
}

void PutChar(u8 Data)
{
	USART_SendData(USART1 , Data);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//等待发送完毕
}
void PutStr(uint8_t *str)//发送一个字符串
{
	while(*str != '\0')
	{
		USART_SendData(USART1 , *str++);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//等待发送完毕
	}
}

void PutNChar(u8 *buf , u16 size)
{
  u8 i;
	for(i=0;i<size;i++)
	{
		 USART_SendData(USART1 , buf[i]);
		 while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//等待发送完毕
	}
}

int fputc(int ch, FILE *f)
{
	/* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
} 

