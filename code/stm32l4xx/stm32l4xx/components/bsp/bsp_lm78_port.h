/**
 **************************************************************************************************
 * @file        bsp_lm78_port.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_LM78_PORT_H_
#define _BSP_LM78_PORT_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_lm78_port_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_lm78_port_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_port_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lm78_port_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_port_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_port_Exported_Functions 
 * @{  
 */

void BSP_LM78_Port_Init(void);
void BSP_LM78_SendBytes(uint8_t * buf, uint16_t len );
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
