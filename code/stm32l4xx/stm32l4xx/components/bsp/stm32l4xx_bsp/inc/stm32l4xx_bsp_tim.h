/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_tim.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32L4XX_BSP_TIM_H_
#define _STM32L4XX_BSP_TIM_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32l4xx_bsp_tim_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_tim_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_tim_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_tim_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_tim_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_tim_Exported_Functions 
 * @{  
 */
void BSP_TIM_Init(void);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base);
void BSP_TIM8_IRQHandler(void);
void BSP_TIM3_IRQHandler(void);
void BSP_TIM5_IRQHandler(void);
void BSP_TIM8_Start(void);
void BSP_TIM8_Stop(void);
void BSP_TIM3_Start(void);
void BSP_TIM3_Stop(void);
void BSP_TIM5_Start(void);
void BSP_TIM5_Stop(void);

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
