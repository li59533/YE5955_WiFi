/**
 **************************************************************************************************
 * @file        conf_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _CONF_TASK_H_
#define _CONF_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    conf_task_Modules 
 * @{  
 */

/**
 * @defgroup      conf_task_Exported_Macros 
 * @{  
 */
#define CONF_TASK_REV_EVENT 			(0X01 << 0)
#define CONF_TASK_TEST2_EVENT			(0X01 << 1)
/**
 * @}
 */

/**
 * @defgroup      conf_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      conf_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      conf_task_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      conf_task_Exported_Functions 
 * @{  
 */
uint32_t Conf_Task_Init(void); 
void Conf_Task(void * pvParameter);
void Conf_Task_Event_Start(uint32_t events, uint8_t event_from);
void Conf_Task_Tim_Init(void);
void Conf_Task_StartTim(uint16_t time_count);

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


