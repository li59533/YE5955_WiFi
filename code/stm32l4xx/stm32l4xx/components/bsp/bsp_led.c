/**
 **************************************************************************************************
 * @file        bsp_led.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "stm32_bsp_conf.h"
#include "bsp_led.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_led_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_led_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_led_Macros_Defines 
 * @brief         
 * @{  
 */
#define LED_ON      GPIO_PIN_SET
#define LED_OFF     GPIO_PIN_RESET
/**
 * @}
 */
 
/**
 * @defgroup      bsp_led_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_led_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_led_Private_Variables 
 * @brief         
 * @{  
 */

static BSP_GPIO_Instance_t bsp_led_instance[BSP_COUNT] =
{
    {
        .GPIOx = GPIOC,
        .GPIO_Init.Pin = GPIO_PIN_6,
        .GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP,
        .GPIO_Init.Pull = GPIO_PULLDOWN,
        .GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
        // .GPIO_Init.Alternate = ,
        .Begin_status = GPIO_PIN_SET,
    }
};
/**
 * @}
 */
 
/**
 * @defgroup      bsp_led_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_led_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**s
 * @}
 */


/**
 * @defgroup      bsp_led_Functions 
 * @brief         
 * @{  
 */

void Bsp_LedInit(void)
{
    uint8_t i = 0 ;

    __HAL_RCC_GPIOC_CLK_ENABLE();

    for( i = 0 ; i < BSP_COUNT ; i ++ )
    {
        HAL_GPIO_Init(bsp_led_instance[i].GPIOx , &bsp_led_instance[i].GPIO_Init);
    }
    
    for( i = 0 ; i < BSP_COUNT ; i ++ )
    {
        HAL_GPIO_WritePin(bsp_led_instance[i].GPIOx , bsp_led_instance[i].GPIO_Init.Pin , bsp_led_instance[i].Begin_status);            
    }
}

void Bsp_LedOpen(uint8_t bsp_ledx)
{
    HAL_GPIO_WritePin(bsp_led_instance[bsp_ledx].GPIOx , bsp_led_instance[bsp_ledx].GPIO_Init.Pin , LED_ON); 
}

void Bsp_LedClose(uint8_t bsp_ledx)
{
    HAL_GPIO_WritePin(bsp_led_instance[bsp_ledx].GPIOx , bsp_led_instance[bsp_ledx].GPIO_Init.Pin , LED_OFF); 
}


void Bsp_LedToggle(uint8_t bsp_ledx)
{
    HAL_GPIO_TogglePin(bsp_led_instance[bsp_ledx].GPIOx , bsp_led_instance[bsp_ledx].GPIO_Init.Pin);
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

