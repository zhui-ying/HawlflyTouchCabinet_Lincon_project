#include "SPI.h"

//串行外设接口SPI的初始化，SPI配置成主模式
void SPIx_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable SPI1 and GPIOA clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1|
														 RCC_APB2Periph_GPIOA
										//				 | RCC_APB2Periph_GPIOC
														 , ENABLE);
	
	/* Configure SPI1 pins: NSS, SCK, MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//SPI1 NSS 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_4);   

	/* SPI1 configuration */ 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //SPI1设置为两线全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	   //设置SPI1为主模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   //SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	 	  //串行时钟在不操作时，时钟为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;  //第二个时钟沿开始采样数据
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;	 //NSS信号由软件（使用SSI位）管理
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //定义波特率预分频的值:波特率预分频值为8
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	 //CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);
	/* Enable SPI1  */
	SPI_Cmd(SPI1, ENABLE); 											  //使能SPI1外设
}  

//SPIx 读写一个字节
//返回值:读取到的字节
u8 SPIx_ReadWriteByte(u8 TxData)
{		
	register u8 retry=0;				 
	while((SPI1->SR&1<<1)==0)//等待发送区空	
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI1->DR=TxData;	 	  //发送一个byte 
	retry=0;
	while((SPI1->SR&1<<0)==0) //等待接收完一个byte  
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI1->DR;          //返回收到的数据				    
}
 
