/**
 **************************************************************************************************
 * @file        hal_task.c
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
#include "stm32_bsp_conf.h"
#include "system_param.h"
#include "bsp_led.h"
#include "app_power.h"
#include "hal_task.h"
#include "rtos_tools.h"
#include "app_battery.h"
/**
 * @addtogroup    hal_task_Modules 
 * @{  
 */

/**
 * @defgroup      hal_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      hal_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      hal_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t hal_task_tim;
TaskHandle_t  Hal_Task_Handle = NULL;

static uint8_t hal_pwr_flag = 0;


/**
 * @}
 */
 
/**
 * @defgroup      hal_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void hal_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      hal_task_Functions 
 * @brief         
 * @{  
 */

uint32_t Hal_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Hal_Task,\
							"hal Task",\
							256,
							NULL,
							3,
							&Hal_Task_Handle);
	return basetype;
}


void Hal_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	
	DEBUG("hal Task Enter\r\n");
	UBaseType_t haltask_ramainheap = 0;
	Hal_Task_Tim_Init();
	
	if(APP_Power_CurrentMode() == PWR_FROM_REST)
	{
		
		APP_Battery_Rest();
		SystemParam_Save();
		Hal_Task_StartTim(60000);
		hal_pwr_flag = 0;
	}
	else
	{
		Hal_Task_StartTim(20000);
		hal_pwr_flag = 1;
	}
	
	
	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & HAL_TASK_STANDBY_EVENT) != 0x00)
		{
			if(hal_pwr_flag == 1)
			{
				DEBUG("HAL_TASK_STANDBY_EVENT\r\n");
				SystemParam_Save();
				RTOS_Delay_ms(5000);
				APP_Power_EnterStandbyMode(g_SystemParam_Config.sleep_time);				
			}
			else
			{
				
			}
		}
	}
	
}


void Hal_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(Hal_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(Hal_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}




void Hal_Task_Tim_Init(void)
{
	hal_task_tim = xTimerCreate(	"HalTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdFALSE,   // pdTRUE is looping , pdFALSE is just one time 
									NULL,
									hal_task_tim_callback );
}

void Hal_Task_StartTim(uint32_t time_count)
{
	xTimerChangePeriod( hal_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( hal_task_tim,0);
}
static void hal_task_tim_callback(TimerHandle_t xTimer)
{
	
	DEBUG("HAL 2min timeout ,ENTER Standby Ready\r\n");
	hal_pwr_flag = 1;
	Hal_Task_Event_Start(HAL_TASK_STANDBY_EVENT, EVENT_FROM_TASK);
	
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

