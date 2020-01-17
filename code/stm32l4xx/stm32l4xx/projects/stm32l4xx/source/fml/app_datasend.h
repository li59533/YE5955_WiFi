/**
 **************************************************************************************************
 * @file        app_datasend.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_DATASEND_H_
#define _APP_DATASEND_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_datasend_Modules 
 * @{  
 */

/**
 * @defgroup      app_datasend_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datasend_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_datasend_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datasend_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datasend_Exported_Functions 
 * @{  
 */
 
int8_t APP_DataSend_SendCharacteristic(void);
void APP_DataSend_NetConnected(void);
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
void BoardAutoPeroidWave(void);


void APP_Report_CharacterValue(void );

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
