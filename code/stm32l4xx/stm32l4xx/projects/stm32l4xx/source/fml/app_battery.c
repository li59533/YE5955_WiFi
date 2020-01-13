/**
 **************************************************************************************************
 * @file        app_battery.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_battery.h"
#include "stm32_bsp_conf.h"
#include "system_param.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
/**
 * @addtogroup    app_battery_Modules 
 * @{  
 */

/**
 * @defgroup      app_battery_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_battery_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_battery_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_battery_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_battery_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_battery_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_battery_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_battery_Functions 
 * @brief         
 * @{  
 */

void APP_Battery_Reduce(void)
{
	g_SystemParam_Config.battery=g_SystemParam_Config.battery - 0.02f;
	if(g_SystemParam_Config.battery <= 0 )
	{
		g_SystemParam_Config.battery = 0;
	}
}

void APP_Battery_Rest(void)
{
	if(g_SystemParam_Config.battery <= 10.0f)
	{
		g_SystemParam_Config.battery = 100.0f;
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

