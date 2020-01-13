/**
 **************************************************************************************************
 * @file        bsp_queue.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_queue.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "net_task.h"
#include "conf_task.h"
/**
 * @addtogroup    bsp_queue_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_queue_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_queue_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_queue_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_queue_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_queue_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_queue_Public_Variables 
 * @brief         
 * @{  
 */
queue_instance_t usart1_rev =
{
	.in = 0,
	.out = 0,
	.count = 0,
	.size = 3,
};

queue_instance_t usart2_rev =
{
	.in = 0,
	.out = 0,
	.count = 0,
	.size = 3,
};


/**
 * @}
 */

/**
 * @defgroup      bsp_queue_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_queue_Functions 
 * @brief         
 * @{  
 */
 
void BSP_Queue_Init(uint8_t queue_num)
{
	switch(queue_num)
	{
		case BSP_QUEUE_UART1_REV:
		{
			usart1_rev.in = 0 ;
			usart1_rev.count = 0;			
			usart1_rev.out  = 0;	
		}
		break;
		case BSP_QUEUE_UART2_REV:
		{
			usart2_rev.in = 0 ;
			usart2_rev.count = 0;			
			usart2_rev.out  = 0;	
		}
		break;
		default:break;
	}
}

void BSP_Queue_Enqueue(uint8_t queue_num, uint8_t * buf, uint16_t len)
{
	switch(queue_num)
	{
		case BSP_QUEUE_UART1_REV:
		{
			if(len <= 100 && len > 0)
			{
				memset(usart1_rev.queue[usart1_rev.in].buf , 0 , sizeof(usart1_rev.queue[usart1_rev.in].buf ));
				memcpy(usart1_rev.queue[usart1_rev.in].buf , buf, len);
				usart1_rev.queue[usart1_rev.in].len = len;
				usart1_rev.in ++;
				usart1_rev.count ++;			
				usart1_rev.in %= 3;	
				Net_Task_Event_Start(NET_TASK_REV_EVENT, EVENT_FROM_ISR);
				DEBUG("BSP_Queue_Enqueue Len :%d\r\n" , len);
			}
			else
			{
				DEBUG("Queue %d is over len %d\r\n",queue_num , len);
			}

		}
		break;
		case BSP_QUEUE_UART2_REV:
		{
			if(len <= 100 && len > 0)
			{
				memset(usart2_rev.queue[usart2_rev.in].buf , 0 , sizeof(usart2_rev.queue[usart2_rev.in].buf ));
				memcpy(usart2_rev.queue[usart2_rev.in].buf , buf, len);
				usart2_rev.queue[usart2_rev.in].len = len;
				usart2_rev.in ++;
				usart2_rev.count ++;			
				usart2_rev.in %= 3;	
				Conf_Task_Event_Start( CONF_TASK_REV_EVENT , EVENT_FROM_ISR);
			}
			else
			{
				DEBUG("Queue %d is over len %d\r\n",queue_num , len );
			}

			
		}
		break;
		default:break;
	}
}

uint8_t BSP_Queue_GetCount(uint8_t queue_num)
{
	uint8_t return_temp = 0;
	switch(queue_num)
	{
		case BSP_QUEUE_UART1_REV: return_temp = usart1_rev.count ; break;
		case BSP_QUEUE_UART2_REV: return_temp = usart2_rev.count ; break;
		default:break;
	}
	return return_temp;
}


uint8_t * BSP_Queue_Dequeue(uint8_t queue_num , uint8_t * len)
{
	uint8_t * buf_ptr = 0; 
	switch(queue_num)
	{
		case BSP_QUEUE_UART1_REV:
		{
			if(usart1_rev.count > 0 )
			{
				buf_ptr = usart1_rev.queue[usart1_rev.out].buf;
				*len = usart1_rev.queue[usart1_rev.out].len;
				usart1_rev.out ++;
				usart1_rev.out %= usart1_rev.size;
				usart1_rev.count --;
				
				return buf_ptr;
			}
			else
			{
				DEBUG("Queue %d is Empty\r\n" , queue_num);
			}
		}
		break;
		case BSP_QUEUE_UART2_REV:
		{
			if(usart2_rev.count > 0 )
			{
				buf_ptr = usart2_rev.queue[usart2_rev.out].buf;
				*len = usart2_rev.queue[usart2_rev.out].len;
				usart2_rev.out ++;
				usart2_rev.out %= usart2_rev.size;
				usart2_rev.count --;
				
				return buf_ptr;
			}
			else
			{
				DEBUG("Queue %d is Empty\r\n" , queue_num);
			}
		}
		break;
		default:break;
	}
	return 0;
}


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

