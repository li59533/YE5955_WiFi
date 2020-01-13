/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_rtc.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32L4XX_BSP_RTC_H_
#define _STM32L4XX_BSP_RTC_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    stm32l4xx_bsp_rtc_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_rtc_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_rtc_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_rtc_Exported_Types 
 * @{  
 */
typedef struct
{
	uint16_t Year;
	uint8_t Mon;
	uint8_t Day;	
	uint8_t Hour;		
	uint8_t Min;				
	uint8_t Sec;					
	uint8_t Week;	
}RTC_T;
/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_rtc_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_rtc_Exported_Functions 
 * @{  
 */
void BSP_RTC_Init(void);
uint8_t BSP_RTC_WriteClock(uint16_t _year, uint8_t _mon, uint8_t _day, uint8_t _hour, uint8_t _min, uint8_t _sec);
uint8_t BSP_RTC_CalcWeek(uint16_t _year, uint8_t _mon, uint8_t _day);

void RTC_ReadClock(void);
void RTC_ConvertSecondsToDatetime(uint32_t seconds, RTC_T *datetime);
uint32_t RTC_ConvertDatetimeToSeconds(const RTC_T *datetime);




RTC_T BSP_RTC_Get(void); // Get Current RTC Value
void BSP_RTC_SetWakeTime(uint32_t WakeUpCounter, uint32_t WakeUpClock);   // Set Wake time IT

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
