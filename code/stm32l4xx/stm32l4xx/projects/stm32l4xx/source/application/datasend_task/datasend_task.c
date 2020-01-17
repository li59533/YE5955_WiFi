/**
 **************************************************************************************************
 * @file        datasend_task.c
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
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "app_power.h"
#include "datasend_task.h"
#include "app_datasend.h"

/**
 * @addtogroup    datasend_task_Modules 
 * @{  
 */

/**
 * @defgroup      datasend_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      datasend_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      datasend_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      datasend_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      datasend_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t datasend_task_tim;
TaskHandle_t  DataSend_Task_Handle = NULL;

/**
 * @}
 */
 
/**
 * @defgroup      datasend_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      datasend_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void datasend_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      datasend_task_Functions 
 * @brief         
 * @{  
 */

uint32_t DataSend_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(DataSend_Task,\
							"DataSend Task",\
							256,
							NULL,
							3,
							&DataSend_Task_Handle);
	
	//DataSend_Task_Tim_Init();
	
	return basetype;
}


void DataSend_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	//DataSend_Task_StartTim(2000);
	DEBUG("DataSend Task Enter\r\n");

	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & DATASEND_TASK_SEND_EVENT) != 0x00)
		{
			DEBUG("DATASEND_TASK_SEND_EVENT\r\n");
			//APP_DataSend_SendCharacteristic();
			APP_Report_CharacterValue();

			UBaseType_t firsttask_ramainheap = 0;
			firsttask_ramainheap = uxTaskGetStackHighWaterMark(NULL);
			DEBUG("DataSend_Task ramain heap:%d \r\n",firsttask_ramainheap);	
			
		}
		if((event_flag & DATASEND_TASK_SEND_DEVICE_INF_EVENT) != 0x00)
		{
			DEBUG("DATASEND_TASK_SEND_DEVICE_INF_EVENT\r\n");
			
			
		}		
		
		

	}
}


void DataSend_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(DataSend_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(DataSend_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}

void DataSend_Task_Tim_Init(void)
{
	datasend_task_tim = xTimerCreate(	"DataSendTim",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									datasend_task_tim_callback );
}

void DataSend_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( datasend_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( datasend_task_tim,0);
}
static void datasend_task_tim_callback(TimerHandle_t xTimer)
{
	DataSend_Task_Event_Start(DATASEND_TASK_SEND_EVENT, EVENT_FROM_TASK);
	//DataSend_Task_Event_Start(DataSend_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
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

