/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_flash.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32L4XX_BSP_FLASH_H_
#define _STM32L4XX_BSP_FLASH_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    stm32l4xx_bsp_flash_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Exported_Macros 
 * @{  
 */
#define BSP_FLASH_HEAD_ADDR 		0X08000000
#define BSP_FLASH_SECTOR_SIZE		0X07FF   //2k
#define BSP_FALSH_PAGE_COUNT		512
/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_flash_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Exported_Functions 
 * @{  
 */
uint16_t BSP_Flash_ReadBytes(uint8_t *buf,uint32_t addr,uint16_t len);
HAL_StatusTypeDef BSP_Flash_WriteBytes(uint32_t addr_start,uint8_t * buf,uint16_t len);
void BSP_Flash_Test(void);
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
