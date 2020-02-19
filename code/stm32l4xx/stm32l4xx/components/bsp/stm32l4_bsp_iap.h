/**
 **************************************************************************************************
 * @file        stm32l4_bsp_iap.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32L4_BSP_IAP_H_
#define _STM32L4_BSP_IAP_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    stm32l4_bsp_iap_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4_bsp_iap_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4_bsp_iap_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4_bsp_iap_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4_bsp_iap_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4_bsp_iap_Exported_Functions 
 * @{  
 */
void BSP_IAP_Erase_Cmd(uint8_t * buf , uint16_t len) ;
void BSP_IAP_RevData(uint8_t * buf , uint16_t len) ;
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
