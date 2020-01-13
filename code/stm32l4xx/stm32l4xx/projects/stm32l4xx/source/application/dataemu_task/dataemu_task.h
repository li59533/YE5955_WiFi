/**
 **************************************************************************************************
 * @file        dataemu_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _DATAEMU_TASK_H_
#define _DATAEMU_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    dataemu_task_Modules 
 * @{  
 */

/**
 * @defgroup      dataemu_task_Exported_Macros 
 * @{  
 */

#define DATAEMU_TASK_EMU_EVENT    	(0X01 << 0)

/**
 * @}
 */

/**
 * @defgroup      dataemu_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dataemu_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataemu_task_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataemu_task_Exported_Functions 
 * @{  
 */

void DataEmu_Task(void * pvParameter);	
uint32_t DataEmu_Task_Init(void);
void DATAEMU_Task_Tim_Init(void);
void DATAEMU_Task_StartTim(uint16_t time_count);
void DataEmu_Task_Event_Start(uint32_t events, uint8_t event_from);
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


