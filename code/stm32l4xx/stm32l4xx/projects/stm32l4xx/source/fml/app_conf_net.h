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



int8_t APP_Report_ChannelKind(uint8_t channel_type) ;  // 
int8_t APP_Report_ID(uint8_t channel_type) ;  // 
int8_t APP_Report_Version(uint8_t channel_type) ;  // 
int8_t APP_Report_ChannelCondition(uint8_t channel_type); 
int8_t APP_Report_SampleParam(uint8_t channel_type) ;
int8_t APP_Report_APinf(uint8_t channel_type)  ;
int8_t APP_Report_TCPServer(uint8_t channel_type) ;  
int8_t APP_Report_RunMode(uint8_t channel_type)   ;
int8_t APP_Report_IPinf(uint8_t channel_type)  ;
int8_t APP_Report_LowPower(uint8_t channel_type)  ;
int8_t APP_Report_Scale(uint8_t channel_type)  ;
int8_t APP_Report_AlarmValue(uint8_t channel_type);
int8_t APP_Report_LowPowerValue(uint8_t channel_type); 

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
