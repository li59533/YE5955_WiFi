/**
 **************************************************************************************************
 * @file        system_init.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "self_def.h"
#include "system_param.h"
#include "system_init.h"
#include "bsp_init.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    system_init_Modules 
 * @{  
 */

/**
 * @defgroup      system_init_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       system_init_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_init_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       system_init_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_init_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_init_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_init_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_init_Functions 
 * @brief         
 * @{  
 */


void System_Load()
{
	SystemParam_Init();
	BSP_Init();
    /* init param module,read and apply params */
    
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

