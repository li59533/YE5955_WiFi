/**
 **************************************************************************************************
 * @file        app_conf_net.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_conf_net.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "lnprotocol_std.h"
#include "bsp_esp32.h"
/**
 * @addtogroup    app_conf_net_Modules 
 * @{  
 */

/**
 * @defgroup      app_conf_net_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_net_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_net_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_net_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_net_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_net_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_net_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void app_confnet_esp32_status(uint8_t * value_buf , uint16_t value_len);
static void app_confnet_receive_beacon(uint8_t * buf , uint16_t len);
/**
 * @}
 */

/**
 * @defgroup      app_conf_net_Functions 
 * @brief         
 * @{  
 */
 
void APP_ConfNet_Process(uint8_t * buf , uint16_t len)   // deal with the cmd
{
	uint8_t  * conf_type = 0;
	uint16_t value_len = 0;
	
	conf_type = &buf[1];
	value_len = buf[2] + buf[3] * 256;
	
	DEBUG("NET Conf Type is 0x%02X\r\n" , *conf_type);
	
	switch(*conf_type)
	{
		case LN_P_ESP32_STATUS: app_confnet_esp32_status(conf_type + 3, value_len);break;
		case LN_P_RECEIVE_BEACON: app_confnet_receive_beacon(buf , len);break;
	}
}


static void app_confnet_receive_beacon(uint8_t * buf , uint16_t len)
{
	DEBUG("app_confnet_receive_beacon\r\n");
	BSP_ESP32_TX_Enqueue(buf,  len);	
}

static void app_confnet_esp32_status(uint8_t * value_buf , uint16_t value_len)  // enter value buf things
{
	if(value_len == 1)
	{
		switch(value_buf[0])
		{
			case ESP32_READY: 
			{
				DEBUG("ESP32_READY\r\n");
				ESP32_AddCMD(ESP32_READY_TO_CONNECT);
				
			}break;
			case ESP32_CONNECTED: 
			{
				DEBUG("ESP32_CONNECTED\r\n");
				ESP32_AddCMD(ESP32_UP_STATUS_TO_CONNECTED);
				
			}break;
			case ESP32_DISCONNECTED: 
			{
				DEBUG("ESP32_DISCONNECTED\r\n");
				ESP32_AddCMD(ESP32_POWER_REST);
				
			}break;
			default : DEBUG("ESP32_STATUS is Err\r\n");break;
		}
		
	}
	else
	{
		DEBUG("CONF_NET value len is Err\r\n");
	}
}


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

