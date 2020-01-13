/**
 **************************************************************************************************
 * @file        lnprotocol_std.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _LNPROTOCOL_STD_H_
#define _LNPROTOCOL_STD_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    lnprotocol_std_Modules 
 * @{  
 */

/**
 * @defgroup      lnprotocol_std_Exported_Macros 
 * @{  
 */
#define LNPROTOCOL_STD_HEAD			0X7E
#define LNPROTOCOL_STD_FOOT			0X7E



#define LN_P_ESP32_STATUS  				0xEA
#define LN_P_ESP32_SET_IP  				0xE4
#define LN_P_ESP32_SET_AP  				0xE5
#define LN_P_ESP32_SET_TCPSERVER 		0xe7
#define LN_P_ESP32_NETSET 				0XFF
#define LN_P_ESP32_R_CHANNELKIND 		0X03



/**
 * @}
 */

/**
 * @defgroup      lnprotocol_std_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      lnprotocol_std_Exported_Types 
 * @{  
 */
 

 

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_std_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_std_Exported_Functions 
 * @{  
 */
int8_t LNprotocol_STD_Checksum(uint8_t * buf,uint16_t len);  // enter a complete buf
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
