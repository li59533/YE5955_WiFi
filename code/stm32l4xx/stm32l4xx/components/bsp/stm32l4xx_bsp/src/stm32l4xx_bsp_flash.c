/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_flash.c
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

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
/**
 * @addtogroup    stm32l4xx_bsp_flash_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_flash_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_flash_Private_Variables 
 * @brief         
 * @{  
 */
static uint8_t bsp_flash_writebuf_space[FLASH_PAGE_SIZE];
/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_flash_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static int8_t bsp_flash_writeinto_assignbuf(uint8_t * assignbuf , uint16_t assign_addr,uint8_t * buf,uint16_t len );

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Functions 
 * @brief         
 * @{  
 */
/*
00> FLASH_BANK_SIZE:0x100000
00> FLASH_SIZE:		0x200000
00> FLASH_PAGE_SIZE:0x1000
00> FLASH_BASE      0x08000000
*/ 
 


void BSP_Flash_Test(void)
{
	DEBUG("FLASH_BANK_SIZE:0x%X\r\n",FLASH_BANK_SIZE);
	DEBUG("FLASH_SIZE:0x%X\r\n",FLASH_SIZE);
	DEBUG("FLASH_PAGE_SIZE:0x%X\r\n",FLASH_PAGE_SIZE);
}

static int8_t bsp_flash_writeinto_assignbuf(uint8_t * assignbuf , uint16_t assign_addr,uint8_t * buf,uint16_t len )
{
	if((len + assign_addr) >  FLASH_PAGE_SIZE)
	{
		return -1;
	}
	
	memcpy(assignbuf + assign_addr , buf , len);
	return 0;
}

HAL_StatusTypeDef BSP_Flash_WriteBytes(uint32_t addr_start , uint8_t * buf , uint16_t len)
{
	FLASH_EraseInitTypeDef pEraseInit = { 0 };

	uint32_t PageError = 0;
	uint16_t real_write_len = 0 ;
	uint32_t real_write_startaddr = 0;
	HAL_StatusTypeDef hal_status ;
	uint8_t * buf_ptr = 0; 
	uint16_t i = 0;
	
	addr_start -=  FLASH_BASE;   //get real start addr
	buf_ptr = buf;
	
	while(1)
	{
		real_write_startaddr = addr_start % FLASH_PAGE_SIZE ; 				// real write start addr
		real_write_len = FLASH_PAGE_SIZE - real_write_startaddr;  	// real write in flash
		
		
		if(addr_start < FLASH_BANK_SIZE)
		{
			pEraseInit.Banks = FLASH_BANK_1;
			pEraseInit.Page = addr_start / FLASH_PAGE_SIZE;
			BSP_Flash_ReadBytes(bsp_flash_writebuf_space , pEraseInit.Page * FLASH_PAGE_SIZE + FLASH_BASE, FLASH_PAGE_SIZE);
		}
		else
		{
			pEraseInit.Banks = FLASH_BANK_2;
			pEraseInit.Page = (addr_start - FLASH_BANK_SIZE)/ FLASH_PAGE_SIZE;
			BSP_Flash_ReadBytes(bsp_flash_writebuf_space , pEraseInit.Page * FLASH_PAGE_SIZE + FLASH_BASE + FLASH_BANK_SIZE, FLASH_PAGE_SIZE);
		}
		
		pEraseInit.NbPages = 1;
		pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
		

		bsp_flash_writeinto_assignbuf(bsp_flash_writebuf_space , real_write_startaddr , buf_ptr , real_write_len);
		buf_ptr += real_write_len;
		
		
		HAL_FLASH_Unlock();
		
		hal_status = HAL_FLASHEx_Erase( &pEraseInit, &PageError);

		for( i = 0; i < FLASH_PAGE_SIZE ;)
		{
			if(pEraseInit.Banks == FLASH_BANK_1)
			{
				hal_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,pEraseInit.Page * FLASH_PAGE_SIZE + FLASH_BASE + i, *(uint64_t *)(bsp_flash_writebuf_space + i));
			}
			else
			{
				hal_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,pEraseInit.Page * FLASH_PAGE_SIZE + FLASH_BASE + FLASH_BANK_SIZE + i, *(uint64_t *)(bsp_flash_writebuf_space + i));
			}
			i += 8;
		}
		

		HAL_FLASH_Lock();
		
		addr_start += real_write_len;

		if((buf_ptr - buf) >= len )
		{
			break;
		}
	}

	return hal_status;
}

uint16_t BSP_Flash_ReadBytes(uint8_t *buf,uint32_t addr,uint16_t len)
{
	uint8_t * read_ptr = (uint8_t *)addr;
	for(uint16_t i = 0; i < len; i ++)
	{
		*(buf + i) = *(read_ptr + i);
	}
	return len;
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

