/**
 **************************************************************************************************
 * @file        bsp_ad7682.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_ad7682.h"
#include "stm32_bsp_conf.h"
#include "bsp_ad7682_port.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "dataprocess_task.h"
/**
 * @addtogroup    bsp_ad7682_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad7682_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Macros_Defines 
 * @brief         
 * @{  
 */
#define BSP_AD7682_SAMPLE_CFG 		0x3A71
/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Constants_Defines 
 * @brief         
 * @{  
 */
#define BSP_AD7682_CH_QUEUE_LEN 		12
const uint8_t bsp_ad7682_ch_queue[BSP_AD7682_CH_QUEUE_LEN] = {2 ,3, 2, 1, 2, 3, 2, 1} ; //{2 ,3, 2, 1, 2, 3, 2, 1} ;  // real sample fre is 32768 ,so this ch can be 16384 ,8192
const uint8_t bsp_ad7682_ch_data_queue[12]={0,1,0,2,0,1,0,2};


/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Private_Variables 
 * @brief         
 * @{  
 */

uint16_t bsp_ad7682_rec[8] = { 0 };
uint16_t bsp_ad7682_data[BSP_AD7682_SAMPLE_ADCH * BSP_AD7682_SAMPLEPOINTS*2] = { 0 };
uint16_t bsp_ad7982_cur_ad_index = 0;
uint16_t bsp_ad7682_cur_ad_ch = 0;
uint16_t bsp_ad7682_CurrentAD7682DataCounter = 0;
uint8_t  bsp_ad7682_datareadyprocess = 0 ;

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Functions 
 * @brief         
 * @{  
 */
void BSP_AD7682_Init(void)
{
	BSP_AD7682_Pin_Init();
	BSP_AD7682_Tim_Init();
	DEBUG("BSP_AD7682 is Init\r\n");
}



void BSP_AD7682_StartGetValue_InConf(void)
{
	uint8_t next_ad_ch = 0;
	uint16_t ad7682_cfg = 0 ; 
	next_ad_ch = bsp_ad7682_ch_queue[bsp_ad7682_cur_ad_ch];

	ad7682_cfg = (uint16_t)BSP_AD7682_SAMPLE_CFG | ( next_ad_ch << 7 );
	ad7682_cfg=ad7682_cfg << 2;
	BSP_AD7682_StartCONV();
	BSP_AD7682_Get( ad7682_cfg , &bsp_ad7682_rec[bsp_ad7682_cur_ad_ch]);
}

void BSP_AD7682_GetValue(void)
{   
	BSP_AD7682_StopCONV();
		
	bsp_ad7682_data[bsp_ad7982_cur_ad_index ++ ] = bsp_ad7682_rec[bsp_ad7682_cur_ad_ch];
	if(bsp_ad7982_cur_ad_index == BSP_AD7682_SAMPLE_ADCH * BSP_AD7682_SAMPLEPOINTS)	
	{

		bsp_ad7682_CurrentAD7682DataCounter = 0;
		bsp_ad7682_datareadyprocess = 1;
		
		//Dataprocess_Task_Event_Start(DATAPEOCESS_TASK_FILTER_EVENT, EVENT_FROM_ISR);
	}
	else if(bsp_ad7982_cur_ad_index >= BSP_AD7682_SAMPLE_ADCH * BSP_AD7682_SAMPLEPOINTS * 2)
	{
		bsp_ad7982_cur_ad_index = 0;			
		bsp_ad7682_CurrentAD7682DataCounter = BSP_AD7682_SAMPLE_ADCH * BSP_AD7682_SAMPLEPOINTS;
		bsp_ad7682_datareadyprocess = 1;
		//Dataprocess_Task_Event_Start(DATAPEOCESS_TASK_FILTER_EVENT, EVENT_FROM_ISR);
	}

	bsp_ad7682_cur_ad_ch ++;
	bsp_ad7682_cur_ad_ch = bsp_ad7682_cur_ad_ch % BSP_AD7682_SAMPLE_ADCH;
	if(((bsp_ad7982_cur_ad_index - bsp_ad7682_cur_ad_ch) % BSP_AD7682_SAMPLE_ADCH)!=0)  //串包的话，这包丢掉
	{
		bsp_ad7682_cur_ad_ch = 0;
		bsp_ad7982_cur_ad_index = 0;
	} 
}
void BSP_AD7682_CheckFilterStatus(void)
{
	if(bsp_ad7682_datareadyprocess == 1)
	{
		Dataprocess_Task_Event_Start(DATAPEOCESS_TASK_FILTER_EVENT, EVENT_FROM_ISR);
		bsp_ad7682_datareadyprocess = 0;
	}
}

void BSP_AD7682_ClearData(void)
{
	bsp_ad7982_cur_ad_index = 0;
	bsp_ad7682_cur_ad_ch = 0;
	bsp_ad7682_CurrentAD7682DataCounter = 0;
	bsp_ad7682_datareadyprocess = 0 ;
}


uint16_t BSP_AD7682_Getcurvalue(uint8_t channel)
{
	return bsp_ad7682_rec[channel];
}
	
uint16_t * BSP_AD7682_GetDataBuf_Ptr(void)
{
	return &bsp_ad7682_data[bsp_ad7682_CurrentAD7682DataCounter];
}
uint8_t BSP_AD7682_GetRealCH(uint8_t location)
{
	return bsp_ad7682_ch_data_queue[location];
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

