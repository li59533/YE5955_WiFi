/**
 **************************************************************************************************
 * @file        app_power.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_power.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
/**
 * @addtogroup    app_power_Modules 
 * @{  
 */

/**
 * @defgroup      app_power_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_power_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_power_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_power_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_power_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_power_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_power_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_power_Functions 
 * @brief         
 * @{  
 */
// AVCC 3.3 -> PE12   ON 
 
void APP_Power_Init(void)
{
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	// -------GPIO init----------
	GPIO_InitTypeDef  GPIO_Init;
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pin = GPIO_PIN_12;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init( GPIOE, &GPIO_Init);
	
	GPIO_Init.Pin = GPIO_PIN_13;
	HAL_GPIO_Init( GPIOB, &GPIO_Init);
	
	APP_Power_AV3_3_OFF();
	APP_Power_LM78_OFF();
}

void APP_Power_AV3_3_ON(void)
{
	DEBUG("APP_Power AV3.3V ON\r\n");
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
}

void APP_Power_AV3_3_OFF(void)
{
	DEBUG("APP_Power AV3.3V ON\r\n");
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
}

void APP_Power_LM78_ON(void)
{
	DEBUG("APP_Power_LM78_ON\r\n");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
}
void APP_Power_LM78_OFF(void)
{
	DEBUG("APP_Power_LM78_OFF\r\n");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
}

void APP_Power_Net_ON(void)
{
	DEBUG("APP_Power_Net_ON\r\n");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);	
}

void APP_Power_Net_OFF(void)
{
	DEBUG("APP_Power_Net_OFF\r\n");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
}


void APP_Power_LMT01_PowerEnable(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0,GPIO_PIN_SET);
}

void APP_Power_LMT01_PowerDisable(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0,GPIO_PIN_RESET);
}

void APP_Power_EnterStandbyMode(uint32_t WakeUpCounter)
{
	if(WakeUpCounter > 0)
	{
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
		BSP_RTC_SetWakeTime( WakeUpCounter,  RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
		HAL_PWR_EnterSTANDBYMode();
	}
	else
	{
		
	}
}



uint8_t APP_Power_CurrentMode(void)
{
	if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
	{
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
		
		return PWR_FROM_SB;
	}
	
	return PWR_FROM_REST;
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

