/**
 **************************************************************************************************
 * @file        task_list.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "task_list.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "FreeRTOS.h"
#include "task.h"

#include "first_task.h"
#include "second_task.h"
#include "net_task.h"
#include "bsp_led.h"
#include "stm32l4xx_hal.h"
#include "clog.h"
#include "dataprocess_task.h"
#include "semphr.h"
#include "dataemu_task.h"
#include "temperature_task.h"
#include "datasend_task.h"
#include "hal_task.h"
#include "conf_task.h"
/**
 * @addtogroup    task_list_Modules 
 * @{  
 */

/**
 * @defgroup      task_list_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      task_list_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      task_list_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      task_list_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      task_list_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      task_list_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      task_list_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      task_list_Functions 
 * @brief         
 * @{  
 */

void RTOS_Init(void)
{
	BaseType_t basetype = { 0 };
	
	//basetype = First_Task_Init();
	//basetype = Second_Task_Init();
	basetype = Dataprocess_Task_Init();
	basetype = Net_Task_Init();
	basetype = DataEmu_Task_Init();
	basetype = Temperature_Task_Init();
	basetype = DataSend_Task_Init();
	basetype = Hal_Task_Init();
	basetype = Conf_Task_Init();
	
	
	if(pdPASS == basetype)
	{
		vTaskStartScheduler();
	}
	else
	{
		while(1)
		{
			HAL_Delay(30);
			Bsp_LedToggle(BSP_LED_TEST);
			DEBUG("RTOS is not start\r\n");
		}
	}
	
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

