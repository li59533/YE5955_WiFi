/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_spi.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32L4XX_BSP_SPI_H_
#define _STM32L4XX_BSP_SPI_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32l4xx_bsp_spi_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_spi_Exported_Macros 
 * @{  
 */
#define  	BSP_SPI_COUNT   1 
#define 	BSP_SPI_1       0
/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_spi_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_spi_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_spi_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_spi_Exported_Functions 
 * @{  
 */
 
void BSP_SPI_Init(void);
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);
void BSP_SPI_Write_IT(uint8_t bsp_spix , uint8_t *buf, uint16_t len);
void BSP_SPI_Write(uint8_t bsp_spix , uint8_t *buf, uint16_t len);
void BSP_SPI_Read_IT(uint8_t bsp_spix,uint8_t *buf , uint16_t len);
void BSP_SPI_WriteAndRead_Byte_IT(uint8_t bsp_spix,uint8_t *tbuf , uint8_t * rbuf);
void BSP_SPI1_IRQHandler(void);
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
