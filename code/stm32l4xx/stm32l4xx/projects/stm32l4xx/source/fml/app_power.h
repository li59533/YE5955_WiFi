/**
 **************************************************************************************************
 * @file        app_power.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_POWER_H_
#define _APP_POWER_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_power_Modules 
 * @{  
 */

/**
 * @defgroup      app_power_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_power_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_power_Exported_Types 
 * @{  
 */
typedef enum
{
	PWR_FROM_REST = 1,
	PWR_FROM_SB = 2,
}App_Power_CurMode_e;

/**
 * @}
 */

/**
 * @defgroup      app_power_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_power_Exported_Functions 
 * @{  
 */
void APP_Power_Init(void);
void APP_Power_AV3_3_ON(void);
void APP_Power_AV3_3_OFF(void);
void APP_Power_LM78_ON(void);
void APP_Power_LM78_OFF(void);
void APP_Power_Net_ON(void);
void APP_Power_Net_OFF(void);
void APP_Power_EnterStandbyMode(uint32_t WakeUpCounter);
uint8_t APP_Power_CurrentMode(void);

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
