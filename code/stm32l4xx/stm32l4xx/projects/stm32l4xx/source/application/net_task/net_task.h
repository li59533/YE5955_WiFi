/**
 **************************************************************************************************
 * @file        net_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _NET_TASK_H_
#define _NET_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    net_task_Modules 
 * @{  
 */

/**
 * @defgroup      net_task_Exported_Macros 
 * @{  
 */

#define NET_TASK_REV_EVENT			(0X01 << 1)
#define NET_TASK_POWER_REST_EVENT 	(0X01 << 2)
#define NET_TASK_LOOP_EVENT			(0x01 << 3)
#define NET_TASK_SEND_EVENT			(0x01 << 4)
/*
 * @}
 */

/**
 * @defgroup      net_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      net_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      net_task_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      net_task_Exported_Functions 
 * @{  
 */

void Net_Task(void * pvParameter);	
uint32_t Net_Task_Init(void);
void NET_Task_Tim_Init(void);
void NET_Task_StartTim(uint16_t time_count);
void Net_Task_Event_Start(uint32_t events, uint8_t event_from);
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


