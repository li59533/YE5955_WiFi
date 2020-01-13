/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_usart.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _stm32l4xx_bsp_usart_H_
#define _stm32l4xx_bsp_usart_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32l4xx_bsp_usart_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_Exported_Macros 
 * @{  
 */
#define BSP_USART1_TX_SIZE          300
#define BSP_USART1_RX_SIZE          300
#define BSP_USART2_TX_SIZE          300
#define BSP_USART2_RX_SIZE          300

    // -----DMA Conf Def ------
#define BSP_USART1_DMATX_ENABLE       1
#define BSP_USART1_DMARX_ENABLE       1
    // ------------------------

typedef enum
{
	BSP_UART_1 = 0,
	BSP_UART_2 ,
	BSP_UART_3 ,
}BSP_UsartX_e;


/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_usart_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_Exported_Functions 
 * @{  
 */
void BSP_Usart_Init(uint8_t  BSP_Uart_X);
void BSP_Usart_WriteBytes_Common(uint8_t BSP_Uart_X , uint8_t * buf , uint16_t len); // blocking mode
void BSP_Usart_WriteBytes_DMA(uint8_t BSP_Uart_X , uint8_t * buf , uint16_t len);
void BSP_Usart_RevOneByteIT_Conf(uint8_t BSP_Uart_X);
void BSP_Usart_RevDMA_Conf(uint8_t BSP_Uart_X);
void BSP_Usart1_IRQHandler(void);
void BSP_UART1_DMA1_IRQHandler(void);

void BSP_Usart2_IRQHandler(void);
void BSP_UART2_DMA1_IRQHandler(void);

void BSP_UART1_REV_Complete(void);

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
