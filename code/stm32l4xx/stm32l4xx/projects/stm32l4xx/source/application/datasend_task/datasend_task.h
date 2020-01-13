/**
 **************************************************************************************************
 * @file        first_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _DATASEND_TASK_H_
#define _DATASEND_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    first_task_Modules 
 * @{  
 */

/**
 * @defgroup      first_task_Exported_Macros 
 * @{  
 */
#define DATASEND_TASK_SEND_EVENT 			(0X01 << 0)
#define DATASEND_TASK_SEND_DEVICE_INF_EVENT			(0X01 << 1)
/**
 * @}
 */

/**
 * @defgroup      first_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      first_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      first_task_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      first_task_Exported_Functions 
 * @{  
 */
uint32_t DataSend_Task_Init(void); 
void DataSend_Task(void * pvParameter);
void DataSend_Task_Event_Start(uint32_t events, uint8_t event_from);
void DataSend_Task_Tim_Init(void);
void DataSend_Task_StartTim(uint16_t time_count);

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


