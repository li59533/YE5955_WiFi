/**
 **************************************************************************************************
 * @file        app_conf.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_CONF_H_
#define _APP_CONF_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_conf_Modules 
 * @{  
 */

/**
 * @defgroup      app_conf_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_Exported_Types 
 * @{  
 */
typedef enum
{
	Current_Is_NET = 0x01,
	Current_Is_Serial = 0x02,
}APP_Conf_Channel_e;
/**
 * @}
 */

/**
 * @defgroup      app_conf_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Exported_Functions 
 * @{  
 */
void APP_Conf_RevProcess(void); 
void APP_Conf_SendBytes(uint8_t *buf , uint16_t len );
void APP_Conf_TestUart(void);

void APP_Conf_ReportData(void);

void APP_Conf_FromLora(uint8_t *buf , uint8_t len );
uint8_t APP_Conf_StrTo16(char buf1,char buf2); 

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
