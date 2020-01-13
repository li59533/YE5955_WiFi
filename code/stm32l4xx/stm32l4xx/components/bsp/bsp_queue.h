/**
 **************************************************************************************************
 * @file        bsp_queue.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_QUEUE_H_
#define _BSP_QUEUE_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_queue_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_queue_Exported_Macros 
 * @{  
 */
#define BSP_QUEUE_UART1_REV      0
#define BSP_QUEUE_UART2_REV		 1	

#define BSP_QUEUE_REVBUF_LEN	 150
/**
 * @}
 */

/**
 * @defgroup      bsp_queue_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_queue_Exported_Types 
 * @{  
 */
typedef struct
{
	uint8_t buf[BSP_QUEUE_REVBUF_LEN];
	uint8_t len;
}queue_value_t ;
 
typedef struct
{
	queue_value_t queue[3];
	uint8_t in;
	uint8_t out;
	uint8_t count;
	uint8_t size;
}queue_instance_t;



/**
 * @}
 */

/**
 * @defgroup      bsp_queue_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_queue_Exported_Functions 
 * @{  
 */
void BSP_Queue_Init(uint8_t queue_num);
void BSP_Queue_Enqueue(uint8_t queue_num, uint8_t * buf, uint16_t len);
uint8_t * BSP_Queue_Dequeue(uint8_t queue_num , uint8_t * len);
uint8_t BSP_Queue_GetCount(uint8_t queue_num);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif
