/**
 **************************************************************************************************
 * @file        main.c
 * @author
 * @version
 * @date        4/25/2017
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "string.h"
#include "system_init.h"
#include "main.h"
#include "stm32l4xx_hal.h"
#include "bsp_init.h"
#include "SEGGER_RTT.h"
#include "task_list.h"
#include "bsp_led.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**	
 * @addtogroup    main_Modules 
 * @{  
 */

/**
 * @defgroup      main_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       main_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      main_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       main_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      main_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      main_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      main_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      main_Functions 
 * @brief         
 * @{  
 */
int main(void)
{
	Board_Init(); // init systick and system clock
    
    __enable_irq(); // open irq
    
    System_Load();  // init bsp peripheral and load system param
    
	RTOS_Init();

    while(1)
	{
		HAL_Delay(1000);
		Bsp_LedToggle(BSP_LED_TEST);
	}
	return 0;
}


void Error_Handler(void)
{
	while(1)
	{
		DEBUG(0,"Error_Handler\r\n");
	};
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

