/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_gpio.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32L4XX_BSP_GPIO_H_
#define _STM32L4XX_BSP_GPIO_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "stm32l4xx_bsp_conf.h"
/**
 * @addtogroup    stm32l4xx_bsp_gpio_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_gpio_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_gpio_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_gpio_Exported_Types 
 * @{  
 */
typedef struct 
{
    GPIO_TypeDef * GPIOx;
    GPIO_InitTypeDef GPIO_Init;
    GPIO_PinState Begin_status;
    /* data */
}BSP_GPIO_Instance_t;
/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_gpio_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_gpio_Exported_Functions 
 * @{  
 */

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
