/**
 **************************************************************************************************
 * @file        bsp_ad7682.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_AD7682_H_
#define _BSP_AD7682_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "bsp_ad7682_port.h"
/**
 * @addtogroup    bsp_ad7682_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad7682_Exported_Macros 
 * @{  
 */
#define BSP_AD7682_ADCHS		        0X04
#define BSP_AD7682_SAMPLE_ADCH   		8
#define BSP_AD7682_SAMPLEPOINTS 		128
#define BSP_AD7682_ACC_REALCHS 			0x03  
/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Exported_Functions 
 * @{  
 */
void BSP_AD7682_Init(void);
void BSP_AD7682_StartGetValue_InConf(void);
void BSP_AD7682_GetValue(void);
void BSP_AD7682_ClearData(void);
uint16_t BSP_AD7682_Getcurvalue(uint8_t channel);
uint16_t * BSP_AD7682_GetDataBuf_Ptr(void);
uint8_t BSP_AD7682_GetRealCH(uint8_t location);
void BSP_AD7682_CheckFilterStatus(void);
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
