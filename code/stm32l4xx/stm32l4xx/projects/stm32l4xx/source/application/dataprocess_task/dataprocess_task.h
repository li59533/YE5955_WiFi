/**
 **************************************************************************************************
 * @file        dataprocess_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _DATAPROCESS_TASK_H_
#define _DATAPROCESS_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    dataprocess_task_Modules 
 * @{  
 */

/**
 * @defgroup      dataprocess_task_Exported_Macros 
 * @{  
 */
#define DATAPEOCESS_TASK_FILTER_EVENT   (0X01 << 0)
#define DATAPEOCESS_TASK_CALC_EVENT   (0X01 << 1)

/**
 * @}
 */

/**
 * @defgroup      dataprocess_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dataprocess_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataprocess_task_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataprocess_task_Exported_Functions 
 * @{  
 */

uint32_t Dataprocess_Task_Init(void);
void Dataprocess_Task(void * pvParameter);
void Dataprocess_Task_Event_Start(uint32_t events, uint8_t event_from);
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
