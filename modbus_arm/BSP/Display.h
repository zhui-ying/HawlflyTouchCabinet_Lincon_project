#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include "stm32f10x.h"

extern u8 LCDbuf[8][128];//œ‘ æ”≥…‰ª∫≥Â«¯
void LCDinit(void);
void Delay(u32 z);
void RefreshLCD(void);
void RefreshOneLine(u8 x_start , u8 x_end , u8 y);
void Display1Line(u8 x , u8 y ,const u8 *buf);
void LCDPutChar(u8 x , u8 y , u8 *data);

#define RCC_GPIO_RS   RCC_APB2Periph_GPIOB
#define GPIO_RS       GPIOB
#define RS_PIN        GPIO_Pin_13

#define RCC_GPIO_RW   RCC_APB2Periph_GPIOB
#define GPIO_RW       GPIOB
#define RW_PIN        GPIO_Pin_15

#define RCC_GPIO_EN   RCC_APB2Periph_GPIOC
#define GPIO_EN       GPIOC
#define EN_PIN        GPIO_Pin_8

#define RCC_GPIO_CS1   RCC_APB2Periph_GPIOC
#define GPIO_CS1       GPIOC
#define CS1_PIN        GPIO_Pin_9

#define RCC_GPIO_CS2   RCC_APB2Periph_GPIOB
#define GPIO_CS2       GPIOB
#define CS2_PIN        GPIO_Pin_14

#define RCC_GPIO_DATA   RCC_APB2Periph_GPIOC
#define GPIO_DATA       GPIOC
#define DATA_PIN        0x00ff
 
#define RSH  GPIO_SetBits(GPIO_RS,RS_PIN) 
#define RSL  GPIO_ResetBits(GPIO_RS,RS_PIN) 
#define RWH  GPIO_SetBits(GPIO_RW,RW_PIN) 
#define RWL  GPIO_ResetBits(GPIO_RW,RW_PIN) 
#define ENH  GPIO_SetBits(GPIO_EN,EN_PIN)  
#define ENL  GPIO_ResetBits(GPIO_EN,EN_PIN) 
#define CS1H  GPIO_SetBits(GPIO_CS1,CS1_PIN ) 
#define CS1L  GPIO_ResetBits(GPIO_CS1,CS1_PIN ) 
#define CS2H  GPIO_SetBits(GPIO_CS2,CS2_PIN) 
#define CS2L  GPIO_ResetBits(GPIO_CS2,CS2_PIN)






#endif

