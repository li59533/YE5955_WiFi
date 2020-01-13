/**
 **************************************************************************************************
 * @file        bsp_ad7682_port.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_ad7682_port.h"
#include "stm32_bsp_conf.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_ad7682_port_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad7682_port_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_port_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_port_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_port_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_port_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_port_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_port_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_port_Functions 
 * @brief         
 * @{  
 */
void BSP_AD7682_Pin_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	// -------GPIO init----------
	GPIO_InitTypeDef  GPIO_Init;
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pin = GPIO_PIN_0;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init( GPIOB, &GPIO_Init);
	// -------SPI Init ----------
	BSP_SPI_Init();
}
void BSP_AD7682_Tim_Init(void)
{
	BSP_TIM_Init();
}


void BSP_AD7682_StopSample(void)
{
	BSP_TIM8_Stop();
}

void BSP_AD7682_StartSample(void)
{
	BSP_TIM8_Start();
}

void BSP_AD7682_StartCONV(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}
void BSP_AD7682_StopCONV(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

void BSP_AD7682_Get(uint16_t cfg , uint16_t *value)
{
	BSP_SPI_WriteAndRead_Byte_IT( BSP_SPI_1, (uint8_t *)&cfg , (uint8_t *) value );
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

