/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.0.0
  * @date    04/06/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_it.h"
//#include  "ucos_ii.h" 
#include "includes.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t bitwiegand;
static uint8_t	bit_start;
static uint8_t	bit_end;
static uint8_t bit_count = 0;
static u32 IC_count = 0;

/* Private function prototypes -----------------------------------------------*/
extern void PCInt(u8 data);
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
    OSIntEnter();
	if(PACK_REC_OK == time_out_check_MODBUS()) 
	{
		//成功接收一帧数据,发送邮箱
		OSMboxPost(modbus_box , modbus_msgbuf);// 发送邮箱
	}	 

	IC_count++;
	if(IC_count > 300)
	{
		IC_count = 0;
		bit_count = 0;
	}
    OSTimeTick();
    OSIntExit(); 
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
/*void PPP_IRQHandler(void)
{
}*/
/*******************************************************************************
* Function Name  :  TIM2_IRQHandler
* Description    :  This function handles Time2 global interrupt request
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)//定时器中断函数20ms
{ 
 
 
 OSIntEnter();

	OSIntExit();    
 }
/**
  * @}
  */ 

/**
  * @brief  This function handles RTC global interrupt request.
  * @param  None
  * @retval None
  */

/*******************************************************************************
* Function Name  : 
* Description    :  This function handles USART3 global interrupt request
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/

void USART3_IRQHandler(void)//条码扫描串口中断
{
	static u8 uart3_RxCounter = 0; 
	OSIntEnter();
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
  		/* Clear the USART3 Receive interrupt */
    	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    	/* Read one byte from the receive data register */
    	barcode_msgbuf[uart3_RxCounter] = USART_ReceiveData(USART3);	 

		if( barcode_msgbuf[uart3_RxCounter - 1] == '\r' && barcode_msgbuf[uart3_RxCounter] == '\n'  )
		{
			barcode_msgbuf[uart3_RxCounter-1] = '\0';
			barcode_msgbuf[uart3_RxCounter] = '\0';
			uart3_RxCounter = 0;
//			uart3_recv_new = 1;		
//			OSMboxPost(barcode_box , barcode_msgbuf);// 发送邮箱
			memset(modbusAdd->send_id , 0 , 24);
			memcpy(modbusAdd->send_id , barcode_msgbuf , strlen(barcode_msgbuf));//复制数据到Modbus数据
			modbusAdd->send_id_flag_L = 1;
		}
		else
		{
				uart3_RxCounter++;									
		}	
  	}
	OSIntExit();
}

/*******************************************************************************
* Function Name  : 
* Description    :  This function handles EXT GPIOA.0 interrupt request
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI0_IRQHandler (void)					  //TAMPER		   PC.13	    D1
{
	OSIntEnter();
	if ( EXTI_GetITStatus(EXTI_Line0) != RESET ) 
    {
	   	IC_count = 0;
	   	bitwiegand=0; 
	     
  		bit_count++ ;

		if( bit_count == 1 )    
		{
			bit_start = bitwiegand;//前校验 2014.2.17
//     		bit_start <<= 1;
//			bit_start |= bitwiegand;
		}
     	if( bit_count >= 2 && bit_count <= 9 )                
     	{
			IC_msgbuf[0] <<= 1; 
			IC_msgbuf[0] |= bitwiegand;
		}
		else if( bit_count >=10 && bit_count <= 17 )              
        {
			IC_msgbuf[1] <<= 1; 
			IC_msgbuf[1] |= bitwiegand;
		}
		else if( bit_count >= 18&& bit_count <= 25 )              
     	{
			IC_msgbuf[2] <<= 1; 
			IC_msgbuf[2] |= bitwiegand;
		}
		else if(bit_count >= 26&& bit_count <= 33)              
     	{
			IC_msgbuf[3] <<= 1;
			IC_msgbuf[3] |= bitwiegand;
		}      
		
		

		if ( bit_count == 34	)
		{
			u8 i,j;
			u8 check1=0;//前偶校验
			u8 check2=0;//后寄校验
			bit_count = 0;
			bit_end = bitwiegand;//后校验  2014.2.17
			
			for(i=0;i<2;i++)
			{
				for(j=0;j<8;j++)
				{
					check1 += IC_msgbuf[i]>>j;//右移
					check2 += IC_msgbuf[i+2]>>j;
				}
			}
			if((bit_start == (check1 & 0x01)) && (bit_end == ((check2+0x01) & 0x01)))
			{
				memcpy(modbusAdd->user_id , IC_msgbuf , 4);//直接更改modbus数据
				modbusAdd->user_id_flag_L = 1;//接收标志置1
			}
		}
		
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
 	OSIntExit();
} 

/*******************************************************************************
* Function Name  : 
* Description    :  This function handles EXT GPIOA.1 interrupt request
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
 void EXTI1_IRQHandler (void)		   				   // WAKEUP        PA.0		D0
{
	OSIntEnter();
	if ( EXTI_GetITStatus(EXTI_Line1) != RESET ) 
    {
		IC_count = 0;
		bitwiegand=1; 
		
		bit_count++ ;
		  
  		if( bit_count == 1 )    
		{
			bit_start = bitwiegand;//前校验 2014.2.17
//     		bit_start <<= 1;
//			bit_start |= bitwiegand;
		}
     	if( bit_count >= 2 && bit_count <= 9 )                
     	{
			IC_msgbuf[0] <<= 1; 
			IC_msgbuf[0] |= bitwiegand;
		}
		else if( bit_count >=10 && bit_count <= 17 )              
        {
			IC_msgbuf[1] <<= 1; 
			IC_msgbuf[1] |= bitwiegand;
		}
		else if( bit_count >= 18&& bit_count <= 25 )              
     	{
			IC_msgbuf[2] <<= 1; 
			IC_msgbuf[2] |= bitwiegand;
		}
		else if(bit_count >= 26&& bit_count <= 33)              
     	{
			IC_msgbuf[3] <<= 1;
			IC_msgbuf[3] |= bitwiegand;
		}      
		
		
		if ( bit_count == 34	)
		{
			u8 i,j;
			u8 check1=0;//偶校验
			u8 check2=0;//奇校验
			bit_count = 0;
			bit_end = bitwiegand;//后校验  2014.2.17
			
			for(i=0;i<2;i++)
			{
				for(j=0;j<8;j++)
				{
					check1 += IC_msgbuf[i]>>j;//右移
					check2 += IC_msgbuf[i+2]>>j;
				}
			}
			if((bit_start == (check1 & 0x01)) && (bit_end == ((check2+0x01) & 0x01)))
			{
				memcpy(modbusAdd->user_id , IC_msgbuf , 4);//直接更改modbus数据
				modbusAdd->user_id_flag_L = 1;//接收标志置1
			}
		}
	
		EXTI_ClearITPendingBit(EXTI_Line1);
   	}
 		OSIntExit();
}

/*******************************************************************************
* Function Name  : 
* Description    :  This function handles USART1 global interrupt request.
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_IRQHandler(void)	//modbus中断
{
	OSIntEnter();
   if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
  		u8 data;
		/* Clear the USART1 Receive interrupt */
    	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		data = USART_ReceiveData(USART1);
		rec_time_out = 0;//一旦接收到数据，清空超时计数
		switch(rec_stat)
		{
			case PACK_START:
				rec_num = 0;
				if(data == PACK_START)//默认刚开始检测第一个字节，检测是否为本站号
				{
					modbus_msgbuf[rec_num++] = data;
					rec_stat = PACK_REC_ING;
				}
				else
				{
					rec_stat = PACK_ADDR_ERR;
				}
				break;
	
			case PACK_REC_ING:	// 正常接收
	
				modbus_msgbuf[rec_num++] = data;
				break;
	
			case PACK_ADDR_ERR:	// 地址不符合 等待超时 帧结束
				break;
			default : break;
		}

	 }  
	 OSIntExit();	
}


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
