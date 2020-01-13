/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_spi.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stm32l4xx_bsp_conf.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_ad7682.h"
#include "bsp_led.h"
/**
 * @addtogroup    stm32l4xx_bsp_spi_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_spi_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_spi_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_spi_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_spi_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_spi_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_spi_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_spi_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_spi_Functions 
 * @brief         
 * @{  
 */
SPI_HandleTypeDef  hspi; 
 
/*
SPI _SCLK -> PA5
SPI _MISO -> PA6
SPI _MOSI -> PA7
SPI _CS   -> PB0
*/

void BSP_SPI_Init(void)
{
	hspi.Instance = SPI1;
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4 ;
	hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi.Init.CRCLength = SPI_CRC_LENGTH_8BIT;
	hspi.Init.CRCPolynomial = 7;
	hspi.Init.DataSize = SPI_DATASIZE_16BIT;
	hspi.Init.Direction = SPI_DIRECTION_2LINES ;
	hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi.Init.Mode = SPI_MODE_MASTER;
	hspi.Init.NSS = SPI_NSS_SOFT;
	hspi.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	hspi.Init.TIMode = SPI_TIMODE_DISABLE;
	
	if(HAL_SPI_Init(&hspi) == HAL_OK)
	{
		DEBUG("SPI 1 init ok\r\n");
	}
	else
	{
		DEBUG("SPI 1 init err\r\n");
	}
	
	
}



void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance == SPI1 )
	{
		// -------Clock -------------
		__HAL_RCC_SPI1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		
		// --------------------------
		// -------GPIO init----------
		GPIO_InitTypeDef  GPIO_Init;
		GPIO_Init.Mode = GPIO_MODE_AF_PP;
		GPIO_Init.Pin = GPIO_PIN_5 | GPIO_PIN_6 |GPIO_PIN_7;
		GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_Init.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init( GPIOA, &GPIO_Init);

		// --------------------------
		// --------NVIC configuration--------
		HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(SPI1_IRQn);
		// ----------------------------------
	}
	else
	{
		
	}
}



void BSP_SPI_Write_IT(uint8_t bsp_spix , uint8_t *buf, uint16_t len)
{
	HAL_SPI_Transmit_IT(&hspi, buf , len);
}

void BSP_SPI_Write(uint8_t bsp_spix , uint8_t *buf, uint16_t len)
{
	HAL_SPI_Transmit(&hspi, buf , len , 1);
}

void BSP_SPI_Read_IT(uint8_t bsp_spix,uint8_t *buf , uint16_t len)
{
	HAL_SPI_Receive_IT(&hspi, buf , len);
}

void BSP_SPI_WriteAndRead_Byte_IT(uint8_t bsp_spix,uint8_t *tbuf , uint8_t * rbuf)
{
	HAL_SPI_TransmitReceive_IT( &hspi , tbuf , rbuf , 1);
}


void BSP_SPI1_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&hspi); // clear some flag
	if(HAL_SPI_GetState(&hspi) == HAL_SPI_STATE_READY)
	{
		
		BSP_AD7682_GetValue();
	}		
	
	//DEBUG("SPI IRQ\r\n");
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

