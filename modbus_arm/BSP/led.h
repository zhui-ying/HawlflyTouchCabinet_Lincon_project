#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1

#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOF,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOF,GPIO_Pin_6)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOF,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOF,GPIO_Pin_7)

#define LED3(a)	if (a)	\
					GPIO_SetBits(GPIOF,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOF,GPIO_Pin_8)

void LED_GPIO_Config(void);

#endif /* __LED_H */
