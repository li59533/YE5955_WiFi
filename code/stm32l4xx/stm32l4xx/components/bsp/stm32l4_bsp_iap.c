/**
 **************************************************************************************************
 * @file        stm32l4_bsp_iap.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stm32l4_bsp_iap.h"
#include "stm32_bsp_conf.h"
#include "lnprotocol_std.h"
#include "FreeRTOS.h"
#include "bsp_esp32.h"
#include "system_param.h"
#include "system_init.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
/**
 * @addtogroup    stm32l4_bsp_iap_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4_bsp_iap_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4_bsp_iap_Macros_Defines 
 * @brief         
 * @{  
 */
#define IAP_ADDRESS 0x08053000
/**
 * @}
 */
 
/**
 * @defgroup      stm32l4_bsp_iap_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4_bsp_iap_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4_bsp_iap_Private_Variables 
 * @brief         
 * @{  
 */
static uint8_t receive_iap_pack_index = 0 ;
static uint32_t receive_iap_data_length = 0;
/**
 * @}
 */
 
/**
 * @defgroup      stm32l4_bsp_iap_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4_bsp_iap_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void bsp_iap_continue_resp(void );
static void bsp_iap_shut_resp(void );
static void bsp_iap_complete_resp(void);
static void bsp_iap_data_countinue_resp(void);
static void bsp_iap_data_stop_resp(void);
/**
 * @}
 */
uint32_t iap_erase_len = 0;
uint32_t iap_data_len = 0;

/**
 * @defgroup      stm32l4_bsp_iap_Functions 
 * @brief         
 * @{  
 */
void BSP_IAP_Erase_Cmd(uint8_t * buf , uint16_t len) 
{
	uint8_t iap_status = 0;
	

	iap_status = buf[0];
	if(iap_status == 0x01 )
	{
		iap_data_len = *(uint32_t *)(buf + 1);

		if((iap_data_len % 64) != 0)
		{
			iap_erase_len = ( iap_data_len / 64 + 1) * 64 ;
		}
		else
		{
			iap_erase_len = iap_data_len;
		}
		receive_iap_pack_index = 0;
		receive_iap_data_length = 0;
		bsp_iap_continue_resp();
	}
	else if(iap_status == 0x03 )
	{
		receive_iap_pack_index = 0;
		receive_iap_data_length = 0;
		bsp_iap_shut_resp();
	}
}
 
static void bsp_iap_continue_resp(void )
{
	uint8_t sendbuf[11] = { 0 };
	uint8_t len = 0;
	sendbuf[0] = LNPROTOCOL_STD_HEAD;	
	sendbuf[1] = LN_P_R_IAP_ERASE;	
	sendbuf[2] = 0x05;	
	sendbuf[3] = 0x00;	
	sendbuf[4] = 0x02;	
	sendbuf[5] = 0x00;	
	sendbuf[6] = 0x00;	
	sendbuf[7] = 0x00;	
	sendbuf[8] = 0x00;	
	sendbuf[9] = 0x00;	
	sendbuf[9] = LN_P_R_IAP_ERASE+0X07;	
	sendbuf[10] = LNPROTOCOL_STD_FOOT;
	len = 11;
	BSP_ESP32_TX_Enqueue(sendbuf,  len);
}

static void bsp_iap_shut_resp(void )
{
	uint8_t sendbuf[11] = { 0 };
	uint8_t len = 0;
	sendbuf[0] = LNPROTOCOL_STD_HEAD;	
	sendbuf[1] = LN_P_R_IAP_ERASE;	
	sendbuf[2] = 0x05;	
	sendbuf[3] = 0x00;	
	sendbuf[4] = 0x04;	
	sendbuf[5] = 0x00;	
	sendbuf[6] = 0x00;	
	sendbuf[7] = 0x00;	
	sendbuf[8] = 0x00;	
	sendbuf[9] = 0x00;
	sendbuf[9] = LN_P_R_IAP_ERASE+0X09;	
	sendbuf[10] = LNPROTOCOL_STD_FOOT;
	len = 11;
	BSP_ESP32_TX_Enqueue(sendbuf,  len);
	
}

void BSP_IAP_RevData(uint8_t * buf , uint16_t len)   
{
	uint8_t * rece_iap_data = 0;
	uint8_t * write_32_Byte = 0;
	rece_iap_data = pvPortMalloc(0x1000); //vPortFree()
	write_32_Byte = pvPortMalloc(64); //vPortFree()
	
	static uint32_t iap_ptr = 0;
	static uint16_t flash_page = 0;
	
	if(receive_iap_pack_index==buf[3])
	{
		receive_iap_pack_index++;
		uint32_t current_iap_pack_length = len - 4;
		if( iap_data_len >= (receive_iap_data_length + current_iap_pack_length))
		{
		
			if(iap_data_len == (receive_iap_data_length + current_iap_pack_length))
			{
				memcpy(&rece_iap_data[iap_ptr], &buf[4],current_iap_pack_length);
				iap_ptr += current_iap_pack_length;
				
				BSP_Flash_WriteBytes(IAP_ADDRESS + flash_page * 0x1000 ,(uint8_t *)rece_iap_data,0x1000);
				flash_page ++;
				iap_ptr = 0;
				memset(rece_iap_data , 0 ,0x1000 );

			}
			else
			{

				memcpy(&rece_iap_data[iap_ptr], &buf[4] ,current_iap_pack_length);
				iap_ptr += current_iap_pack_length;
				
				if(iap_ptr >= 0x1000)
				{
					BSP_Flash_WriteBytes(IAP_ADDRESS + flash_page * 0x1000 ,(uint8_t *)rece_iap_data,0x1000);
					flash_page ++;
					iap_ptr = 0;
					memset(rece_iap_data , 0 ,0x1000 );
				}
				
			}
			
			receive_iap_data_length += current_iap_pack_length;
			
			if(iap_data_len == receive_iap_data_length)
			{
				flash_page = 0;
				bsp_iap_complete_resp();
				g_SystemParam_Config.Iap_datalength = iap_erase_len;
				g_SystemParam_Config.Iap_flag=0x01;
				SystemParam_Save();
				System_Rest();
			}
			else 
			{
				bsp_iap_data_countinue_resp();
			}
					
		}
		else
		{
			receive_iap_data_length=0;	
			receive_iap_pack_index=0;	
			bsp_iap_data_stop_resp();
		}
	}else
	{
		bsp_iap_data_stop_resp();	
	}
//	 saveConfig();
	
	vPortFree(rece_iap_data);
	vPortFree(write_32_Byte);
	
}

static void bsp_iap_complete_resp(void)
{
	uint8_t sendbuf[11] = { 0 };
	uint8_t len = 0;
	sendbuf[0] = LNPROTOCOL_STD_HEAD;	
	sendbuf[1] = LN_P_R_IAP_ERASE;	
	sendbuf[2]=0x05;	
	sendbuf[3]=0x00;	
	sendbuf[4]=0x03;	
	sendbuf[5]=0x00;	
	sendbuf[6]=0x00;	
	sendbuf[7]=0x00;	
	sendbuf[8]=0x00;	
	sendbuf[9]=0x00;	
	sendbuf[9] = LN_P_R_IAP_ERASE+0X07;	
	sendbuf[10] = LNPROTOCOL_STD_FOOT;
	len = 11;
	BSP_ESP32_TX_Enqueue(sendbuf,  len);
}

static void bsp_iap_data_countinue_resp(void)
{
	uint8_t sendbuf[7] = { 0 };
	uint8_t len = 0;
	sendbuf[0] = LNPROTOCOL_STD_HEAD;	
	sendbuf[1] = LN_P_R_IAP_DATA;	
	sendbuf[2] = 0x01;	
	sendbuf[3] = 0x00;	
	sendbuf[4] = 0x01;	
	sendbuf[5] = 0x00;	
	sendbuf[5] = LN_P_R_IAP_DATA+0X02;	
	sendbuf[6] = LNPROTOCOL_STD_FOOT;
	len = 7;	
	BSP_ESP32_TX_Enqueue(sendbuf,  len);
}

static void bsp_iap_data_stop_resp(void)
{
	uint8_t sendbuf[7] = { 0 };
	uint8_t len = 0;
	sendbuf[0] = LNPROTOCOL_STD_HEAD;	
	sendbuf[1] = LN_P_R_IAP_DATA;	
	sendbuf[2] = 0x01;	
	sendbuf[3] = 0x00;	
	sendbuf[4] = 0x00;	
	sendbuf[5] = 0x00;	
	sendbuf[5] = LN_P_R_IAP_DATA+0X01;
	sendbuf[6] = LNPROTOCOL_STD_FOOT;
	len = 7;	
	BSP_ESP32_TX_Enqueue(sendbuf,  len);
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

