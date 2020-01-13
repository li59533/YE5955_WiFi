/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_tim.c
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
#include "main.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_led.h"
#include "bsp_ad7682.h"
/**
 * @addtogroup    stm32l4xx_bsp_tim_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_tim_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_tim_Macros_Defines 
 * @brief         
 * @{  
 */

 


/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_tim_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_tim_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_tim_Private_Variables 
 * @brief         
 * @{  
 */
TIM_HandleTypeDef  htim8 =
{
	.Instance = TIM8,
	.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,
	.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
	.Init.CounterMode = TIM_COUNTERMODE_UP,
	.Init.Period = 3661,//1831=120000000/65536的采样率;;
	.Init.Prescaler = 0,
	.Init.RepetitionCounter = 0,	
}; 
TIM_HandleTypeDef  htim3 =
{
	.Instance = TIM3,
	.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,
	.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
	.Init.CounterMode = TIM_COUNTERMODE_UP,
	.Init.Period = 499, //500us一次
	.Init.Prescaler = 119,
	.Init.RepetitionCounter = 0,	
};

TIM_HandleTypeDef  htim5 =
{
	.Instance = TIM5,
	.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,
	.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
	.Init.CounterMode = TIM_COUNTERMODE_UP,
	.Init.Period = 5, //1000us一次
	.Init.Prescaler = 120000,
	.Init.RepetitionCounter = 0,	
};
 
/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_tim_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_tim_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_tim_Functions 
 * @brief         
 * @{  
 */


void BSP_TIM_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	
	if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
	{
		Error_Handler();
	}	

	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}	
	
	if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
	{
		Error_Handler();
	}	
	
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}	
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}	
	if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}	
	
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}	
	
	
	BSP_TIM3_Start();
	DEBUG("TIM8 TIM3 TIM5 Init\r\n");
	
}	
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
	if(htim_base->Instance==TIM8)
	{
		__HAL_RCC_TIM8_CLK_ENABLE();
		__HAL_TIM_CLEAR_IT(&htim8, TIM_IT_UPDATE)  ;
		HAL_NVIC_SetPriority(TIM8_UP_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(TIM8_UP_IRQn);

	}else if(htim_base->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();
		__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE)  ;
		HAL_NVIC_SetPriority(TIM3_IRQn, 6, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);

	}else if(htim_base->Instance==TIM5)
	{
		__HAL_RCC_TIM5_CLK_ENABLE();
		__HAL_TIM_CLEAR_IT(&htim5, TIM_IT_UPDATE)  ;
		HAL_NVIC_SetPriority(TIM5_IRQn, 6, 0);
		HAL_NVIC_EnableIRQ(TIM5_IRQn);		
	}
}

void BSP_TIM8_Start(void)
{
	HAL_TIM_Base_Start_IT(&htim8);
}
void BSP_TIM8_Stop(void)
{
	HAL_TIM_Base_Stop_IT(&htim8);
}
void BSP_TIM3_Start(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
}
void BSP_TIM3_Stop(void)
{
	HAL_TIM_Base_Stop_IT(&htim3);
}

void BSP_TIM5_Start(void)
{
	HAL_TIM_Base_Start_IT(&htim5);
}
void BSP_TIM5_Stop(void)
{
	HAL_TIM_Base_Stop_IT(&htim5);
}


void BSP_TIM8_IRQHandler(void)
{
	
	if (TIM8->SR & TIM_IT_UPDATE) 
		{
			TIM8->SR &= (uint16_t)~TIM_IT_UPDATE;
			
		BSP_AD7682_StartGetValue_InConf();
		//DEBUG("TIM8 IRQ\r\n");
		}	
	
	
	
	//HAL_TIM_IRQHandler(&htim8);
	//HAL_TIM_Base_Stop_IT(&htim2);

}
void BSP_TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim3);
	BSP_AD7682_CheckFilterStatus();
	//HAL_TIM_Base_Stop_IT(&htim3);
	//DEBUG("TIM3 IRQ\r\n");
}


void BSP_TIM5_IRQHandler(void)
{
//	DEBUG("ENTER BSP_TIM5_IRQHandler\r\n");
//	HAL_TIM_IRQHandler(&htim5);
//	BSP_TIM5_Stop();
	
	if (TIM5->SR & TIM_IT_UPDATE) 
	{
		TIM5->SR &= (uint16_t)~TIM_IT_UPDATE;
		
		BSP_UART1_REV_Complete();
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

