/**
 **************************************************************************************************
 * @file        app_datafilter.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_DATAFILTER_H_
#define _APP_DATAFILTER_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_datafilter_Modules 
 * @{  
 */

/**
 * @defgroup      app_datafilter_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datafilter_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_datafilter_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datafilter_Exported_Variables 
 * @{  
 */
extern int32_t AD_ZERO[];
extern int32_t AD_ZEROlowpass[];
extern int32_t AD_INTER[];
extern int32_t lastdata[];
extern int32_t filtercounter[];
extern uint8_t app_datafilter_checksum[] ;
extern uint32_t sprase_counter[];
extern uint32_t StoreDateIndex[];
extern int32_t wave_jscope[];

extern int16_t piz_emu_data[2][32768];
extern int16_t  mems_emu_data[2][3][8192]; //3ÖámemsÊý¾Ý´æ·Å
extern uint8_t currentSAMPLEblock ;
extern uint32_t ActualIndex ;
/**
 * @}
 */

/**
 * @defgroup      app_datafilter_Exported_Functions 
 * @{  
 */
void APP_DataFilter_Process(void);
void APP_DataFilter_SpraseIndex(void);
void APP_DataFilter_Init(void);
void APP_DataFilter_UpdateAccData(int16_t data , uint8_t channel , uint32_t DataIndex);
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
