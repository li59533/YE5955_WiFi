/**
 **************************************************************************************************
 * @file        bsp_ad7682_port.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_AD7682_PORT_H_
#define _BSP_AD7682_PORT_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_ad7682_port_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad7682_port_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_port_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_port_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_port_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_port_Exported_Functions 
 * @{  
 */
 // --------- this is NOT user use func -------------
void BSP_AD7682_Pin_Init(void);
void BSP_AD7682_StartCONV(void);
void BSP_AD7682_StopCONV(void);
void BSP_AD7682_Get(uint16_t cfg , uint16_t *value);
void BSP_AD7682_Tim_Init(void);

// --------------------------------------------------

void BSP_AD7682_StopSample(void);
void BSP_AD7682_StartSample(void);


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
