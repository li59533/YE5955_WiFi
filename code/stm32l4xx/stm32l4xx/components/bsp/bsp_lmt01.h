/**
 **************************************************************************************************
 * @file        bsp_lmt01.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_LMT01_H_
#define _BSP_LMT01_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    bsp_lmt01_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_lmt01_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lmt01_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Exported_Functions 
 * @{  
 */
void BSP_LMT01_Init(void);
void BSP_LMT01_StartGetValue(void);
void BSP_LMT01_PowerEnable(void);
void BSP_LMT01_PowerDisable(void);
void BSP_LMT01_EXTI_IRQHandler(void);
void BSP_LMT01_TIM4_IRQHandler(void);
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
