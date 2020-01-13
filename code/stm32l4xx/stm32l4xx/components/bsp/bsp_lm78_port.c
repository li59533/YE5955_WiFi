/**
 **************************************************************************************************
 * @file        bsp_lm78_port.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "stm32_bsp_conf.h"
#include "bsp_lm78_port.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_lm78_port_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_lm78_port_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_port_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lm78_port_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_port_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lm78_port_Private_Variables 
 * @brief         
 * @{  
 */


/**
 * @}
 */
 
/**
 * @defgroup      bsp_lm78_port_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_port_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**s
 * @}
 */


/**
 * @defgroup      bsp_lm78_port_Functions 
 * @brief         
 * @{  
 */
void BSP_LM78_Port_Init(void)
{
	BSP_Usart_Init( BSP_UART_1);
	BSP_Usart_RevOneByteIT_Conf(BSP_UART_1);
}

void BSP_LM78_SendBytes(uint8_t * buf, uint16_t len )
{
	BSP_Usart_WriteBytes_DMA(BSP_UART_1 , buf , len);
	//BSP_Usart_WriteBytes_Common( 0 , buf , len); // blocking mode
}
void BSP_LM_78_Rest(void)
{
	
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

