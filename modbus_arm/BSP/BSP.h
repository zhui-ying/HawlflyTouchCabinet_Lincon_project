#ifndef __BSP_H
#define	__BSP_H

#if OLD_NEW_BOARD	//新
#define BeepOFF  GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define BeepON  GPIO_SetBits(GPIOA, GPIO_Pin_8)
#else			  //旧
#define BeepON  GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define BeepOFF  GPIO_SetBits(GPIOA, GPIO_Pin_8)
#endif

#define LED1ON 	 GPIO_ResetBits(GPIOG, GPIO_Pin_11)
#define LED1OFF 	 GPIO_SetBits(GPIOG, GPIO_Pin_11)
#define LED2ON 	 GPIO_ResetBits(GPIOG, GPIO_Pin_12)
#define LED2OFF 	 GPIO_SetBits(GPIOG, GPIO_Pin_12)

#define RESETKEY   GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_10)

void SysTick_init(void);
void BSP_Init(void);
void NVIC_Configuration(void);
void TIME_Configuration(void);//定时器初始化
void BuzzerIOInit(void);
void LEDIOinit(void);
void BarCodeInit(unsigned long ulBaud);
void ICcardInit( void );
void ICcardEnable(void);
void ICcardDisable(void);

void PCIntDisable(void);
void PCIntEnable(void);

#endif // __BSP_H
