/**
 **************************************************************************************************
 * @file        bsp_lmt01.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_lmt01.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "system_param.h"
/**
 * @addtogroup    bsp_lmt01_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_lmt01_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lmt01_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lmt01_Private_Variables 
 * @brief         
 * @{  
 */
TIM_HandleTypeDef htim4;
/**
 * @}
 */
 
/**
 * @defgroup      bsp_lmt01_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void lmt01_gpio_init(void);
static void lmt01_tim_init(void);
/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Functions 
 * @brief         
 * @{  
 */
 

uint32_t LMT01_RUN_COUNTER=0; //该变量用来计时LMT01运行时间，正常是54ms conv 50ms data ,所以放104ms一次转换
#define LMT01_LIFE_TIME 106 //10600*1ms=106ms
uint32_t LMT01_TEMP_CNT=0;
uint32_t LMT01_TEMP_VALUE=0;
uint32_t LMT01_PULSE_WIDTH=0;
typedef enum {LMT01_ERR=0,LMT01_OK=1,} LMT01_Condition;
LMT01_Condition LMT01_CURRENT_CONDITION;

 
 
void BSP_LMT01_Init(void)
{
	lmt01_gpio_init();
	lmt01_tim_init();
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);  //外部中断使能
	HAL_NVIC_EnableIRQ(TIM4_IRQn);           //TPM中断使能
}

static void lmt01_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();


	/*Configure GPIO pin : PC5 */
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : PE0 */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
	//  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}


static void lmt01_tim_init(void)
{

	/* USER CODE BEGIN TIM15_Init 0 */
	__HAL_RCC_TIM4_CLK_ENABLE();
	/* TIM4 interrupt Init */
	HAL_NVIC_SetPriority(TIM4_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
	//	HAL_NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);
	/* USER CODE END TIM15_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* USER CODE BEGIN TIM4_Init 1 */

	/* USER CODE END TIM4_Init 1 */
	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 119;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 999;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
	{

	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
	{

	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
	{

	}

}





void BSP_LMT01_EXTI_IRQHandler(void)
{
	/* USER CODE BEGIN EXTI9_5_IRQn 0 */

	/* USER CODE END EXTI9_5_IRQn 0 */
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
	/* USER CODE BEGIN EXTI9_5_IRQn 1 */
	LMT01_TEMP_CNT++;

	/* USER CODE END EXTI9_5_IRQn 1 */
}
void BSP_LMT01_TIM4_IRQHandler(void)
{
	/* USER CODE BEGIN TIM4_IRQn 0 */

	/* USER CODE END TIM4_IRQn 0 */
	HAL_TIM_IRQHandler(&htim4);
	/* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 1 */
	//	bsp_LedToggle(1);
	/* USER CODE END TIM1_BRK_TIM15_IRQn 1 */

	LMT01_RUN_COUNTER++;//
	if(LMT01_RUN_COUNTER>LMT01_LIFE_TIME)
	{
		LMT01_TEMP_VALUE=LMT01_TEMP_CNT;
		g_SystemParam_Param.pdate=((float)LMT01_TEMP_VALUE*0.0625f - 50) + g_SystemParam_Config.tempCompensation*0.1f; //补偿值
		LMT01_RUN_COUNTER=0;
		BSP_LMT01_PowerDisable();
		HAL_TIM_Base_Stop_IT(&htim4);
	}
	
}

void  Init_temp_parameter(void)
{
	LMT01_TEMP_CNT=0;
	LMT01_RUN_COUNTER=0;
	LMT01_PULSE_WIDTH=0;	
}


void BSP_LMT01_StartGetValue(void)
{
	Init_temp_parameter();
	BSP_LMT01_PowerEnable();     //打开电源		
	HAL_TIM_Base_Start_IT(&htim4);
}


void BSP_LMT01_PowerEnable(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0,GPIO_PIN_SET);
}

void BSP_LMT01_PowerDisable(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0,GPIO_PIN_RESET);
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

