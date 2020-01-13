/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_conf.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32L4XX_BSP_CONF_H_
#define _STM32L4XX_BSP_CONF_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32l4xx_bsp_conf_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_conf_Exported_Macros 
 * @{  
 */

// -----------Lib Active list --------------------
#define USING_STM32_HAL_LIB 			1
// -----------------------------------------------
// -----------BSP Module Active list -------------
#define BSP_ADC_MODULE_ENABLE			0
#define BSP_CAN_MODULE_ENABLE 			0
#define BSP_DAC_MODULE_ENABLE			0
#define BSP_DMA_MODULE_ENABLE			0
#define BSP_EXTI_MODULE_ENABLE 			0
#define BSP_FLASH_MODULE_ENABLE			1
#define BSP_GPIO_MODULE_ENABLE			1
#define BSP_IIC_MODULE_ENABLE			0
#define BSP_RTC_MODULE_ENABLE			1
#define BSP_SPI_MODULE_ENABLE			1
#define BSP_TIM_MODULE_ENABLE			1
#define BSP_USART_MODULE_ENABLE			1
#define BSP_WDG_MODULE_ENABLE			0
#define BSP_SYSTICK_MODULE_ENABLE		1
// -----------------------------------------------

#if USING_STM32_HAL_LIB == 1
	#include "stm32l4xx_hal.h"
#endif

#if BSP_ADC_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_adc.h"
#endif

#if BSP_CAN_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_can.h"
#endif

#if BSP_DAC_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_dac.h"
#endif

#if BSP_DMA_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_dma.h"
#endif

#if BSP_EXTI_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_exti.h"
#endif

#if BSP_FLASH_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_flash.h"
#endif

#if BSP_GPIO_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_gpio.h"
#endif

#if BSP_IIC_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_iic.h"
#endif

#if BSP_RTC_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_rtc.h"
#endif

#if BSP_SPI_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_spi.h"
#endif

#if BSP_TIM_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_tim.h"
#endif

#if BSP_USART_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_usart.h"
#endif

#if BSP_WDG_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_wdg.h"
#endif

#if BSP_SYSTICK_MODULE_ENABLE == 1
	#include "stm32l4xx_bsp_systick.h"
#endif



/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_conf_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_conf_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_conf_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_conf_Exported_Functions 
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
