/**
 **************************************************************************************************
 * @file        dataemu_task.c
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
#include "dataemu_task.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32_bsp_conf.h"
#include "system_param.h"
#include "rtos_tools.h"

#include "bsp_led.h"
#include "timers.h"
#include "app_dataemu.h"
/**
 * @addtogroup    dataemu_task_Modules 
 * @{  
 */

/**
 * @defgroup      dataemu_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataemu_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dataemu_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataemu_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dataemu_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t dataemu_task_timout;
/**
 * @}
 */
 
/**
 * @defgroup      dataemu_task_Public_Variables 
 * @brief         
 * @{  
 */
TaskHandle_t  DataEmu_Task_Handle = NULL;
/**
 * @}
 */

/**
 * @defgroup      dataemu_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void dataemu_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      dataemu_task_Functions 
 * @brief         
 * @{  
 */


uint32_t DataEmu_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(DataEmu_Task,\
							"DataEmu_Task",\
							1024,
							NULL,
							3,
							&DataEmu_Task_Handle);
	return basetype;
}
void DataEmu_Task(void * pvParameter)
{
	uint32_t event_flag = 0;	
	DEBUG("DataEmu Task Enter\r\n");
	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & DATAEMU_TASK_EMU_EVENT) != 0x00)
		{
			DEBUG("DATAEMU_TASK_EMU_EVENT\r\n");
			APP_DataEmu_Process();
		}

	}
	
}
	

void DataEmu_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	BaseType_t HigherPriorityTaskWoken = pdFALSE;
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(DataEmu_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(DataEmu_Task_Handle, events, eSetBits , &HigherPriorityTaskWoken);
		}
		break;
		default:break;
	}
}
		


void DATAEMU_Task_Tim_Init(void)
{
	dataemu_task_timout = xTimerCreate(	"DataEmuTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									dataemu_task_tim_callback );
}

void DATAEMU_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( dataemu_task_timout,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( dataemu_task_timout,0);
}
static void dataemu_task_tim_callback(TimerHandle_t xTimer)
{
	
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

