/**
 **************************************************************************************************
 * @file        bsp_lm78.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_LM78_H_
#define _BSP_LM78_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "bsp_lm78_port.h"
/**
 * @addtogroup    bsp_lm78_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_lm78_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_Exported_Constants
 * @{  
 */
extern const char LM78_AT_AT[]; 
extern const char LM78_AT_GetVersion[];
extern const char LM78_AT_GetAddr[] ;
extern const char LM78_AT_SendOriginalData[] ;
extern const char LM78_AT_SendstrData[];
extern const char LM78_AT_Rest[];
/**
 * @}
 */
 
/**
 * @defgroup      bsp_lm78_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_Exported_Functions 
 * @{  
 */
void BSP_LM78_Init(void);
void BSP_LM78_RespProcess(void);
void BSP_LM78_ReqProcess(void);
int8_t BSP_LM78_StartSend(uint8_t *buf, uint16_t len);
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
