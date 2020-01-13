/**
 **************************************************************************************************
 * @file        bsp_led.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_LED_H_
#define _BSP_LED_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_led_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_led_Exported_Macros 
 * @{  
 */

#define BSP_COUNT       1
#define BSP_LED_0       0


 // --------User Define ---------
#define BSP_LED_TEST    BSP_LED_0
 // --------End User Define------
/**
 * @}
 */

/**
 * @defgroup      bsp_led_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_led_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_led_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_led_Exported_Functions 
 * @{  
 */

void Bsp_LedInit(void);
void Bsp_LedOpen(uint8_t bsp_ledx);
void Bsp_LedClose(uint8_t bsp_ledx);
void Bsp_LedToggle(uint8_t bsp_ledx);

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
