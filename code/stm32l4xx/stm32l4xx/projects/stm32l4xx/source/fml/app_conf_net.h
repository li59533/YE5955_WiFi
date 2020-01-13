/**
 **************************************************************************************************
 * @file        app_conf_net.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_CONF_NET_H_
#define _APP_CONF_NET_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_conf_net_Modules 
 * @{  
 */

/**
 * @defgroup      app_conf_net_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_net_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_net_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_net_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_net_Exported_Functions 
 * @{  
 */
void APP_ConfNet_Process(uint8_t * buf , uint16_t len);   // deal with the cmd

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
