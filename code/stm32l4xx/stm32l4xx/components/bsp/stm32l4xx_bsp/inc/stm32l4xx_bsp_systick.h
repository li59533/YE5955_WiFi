/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_systick.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32L4XX_BSP_SYSTICK_H_
#define _STM32L4XX_BSP_SYSTICK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    stm32l4xx_bsp_systick_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_systick_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_systick_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_systick_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_systick_Exported_Variables 
 * @{  
 */
extern TIM_HandleTypeDef        htim7; 
/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_systick_Exported_Functions 
 * @{  
 */
void BSP_Systick_Init(void); // if using ths HAL ,please using the HAl_Init();
void BSP_Systick_Delayms(uint32_t delay); // block delay 


void HAL_SuspendTick(void);
void HAL_ResumeTick(void);


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


