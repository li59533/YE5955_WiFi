/**
 **************************************************************************************************
 * @file        dataprocess_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "limits.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "FreeRTOS.h"
#include "task.h"
#include "clog.h"
#include "dataprocess_task.h"
#include "app_datafilter.h"
#include "bsp_ad7682.h"
#include "app_power.h"
#include "app_dataemu.h"
#include "bsp_led.h"
/**
 * @addtogroup    dataprocess_task_Modules 
 * @{  
 */

/**
 * @defgroup      dataprocess_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataprocess_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dataprocess_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataprocess_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dataprocess_task_Private_Variables 
 * @brief         
 * @{  
 */
TaskHandle_t  Dataprocess_Task_Handle = NULL;
/**
 * @}
 */
 
/**
 * @defgroup      dataprocess_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataprocess_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataprocess_task_Functions 
 * @brief         
 * @{  
 */


uint32_t Dataprocess_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Dataprocess_Task,\
							"Dataprocess_Task",\
							1024,
							NULL,
							5,
							&Dataprocess_Task_Handle);
	return basetype;
}


void Dataprocess_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	UBaseType_t dataprocess_ramainheap = 0;
	
	DEBUG("Dataprocess_Task Enter\r\n");
	APP_Power_AV3_3_ON();
	BSP_AD7682_Init();
	APP_DataFilter_Init();
	

//	
	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);

		if((event_flag & DATAPEOCESS_TASK_CALC_EVENT) != 0x00)
		{
			dataprocess_ramainheap = uxTaskGetStackHighWaterMark(NULL);
			DEBUG("Dataprocess_Task ramain heap:%d %%\r\n",dataprocess_ramainheap);
			DEBUG("DATAPEOCESS_TASK_CALC_EVENT\r\n");
			//
			//vTaskDelay(pdMS_TO_TICKS(10000));			
		}
		
		if((event_flag & DATAPEOCESS_TASK_FILTER_EVENT) != 0x00)
		{
			Bsp_LedToggle(BSP_LED_TEST);
			//DEBUG("DATAPEOCESS_TASK_FILTER_EVENT\r\n");
			APP_DataFilter_Process();
			//vTaskDelay(pdMS_TO_TICKS(10000));			
		}
	}
	
}


void Dataprocess_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	BaseType_t HigherPriorityTaskWoken = pdFALSE;
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(Dataprocess_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(Dataprocess_Task_Handle, events, eSetBits , &HigherPriorityTaskWoken);
		}
		break;
		default:break;
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

