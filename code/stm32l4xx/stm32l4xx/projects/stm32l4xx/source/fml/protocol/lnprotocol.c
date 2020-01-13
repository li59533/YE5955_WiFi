/**
 **************************************************************************************************
 * @file        lnprotocol.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "lnprotocol.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    lnprotocol_Modules 
 * @{  
 */

/**
 * @defgroup      lnprotocol_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      lnprotocol_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      lnprotocol_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      lnprotocol_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_Functions 
 * @brief         
 * @{  
 */



uint8_t * LNprotocol_AddHead(uint8_t * targetspace_ptr) // return the value ptr
{
	*targetspace_ptr = LNPROTOCOL_HEAD;
	return targetspace_ptr + 2;
}

uint8_t * LNprotocol_AddValue(uint8_t * targetspace_ptr , uint8_t *buf,uint8_t len)
{
	memcpy(targetspace_ptr , buf , len);
	return targetspace_ptr + len;
}

uint8_t * LNprotocol_AddFoot(uint8_t * targetspace_ptr)
{
	*targetspace_ptr = LNPROTOCOL_FOOT;
	return targetspace_ptr + 1;
}

void LNprotocol_Addlen(uint8_t *buf, uint16_t len)
{
	memcpy(buf + 1,(uint8_t *)&len,2);
}


uint8_t LNprotocol_AddChecksum(uint8_t * buf,uint16_t len)
{
	uint8_t checksum = 0;
	while(len --)
	{
		checksum += *(buf++);
	}
	return checksum;
}



uint8_t LN_AddTlv(uint8_t * disaddr,LN_Tlv_t * tlv_value)
{
	disaddr[0] = tlv_value->Tag;
	disaddr[1] = tlv_value->Len;
	memcpy(&disaddr[2],tlv_value->Value.Array,tlv_value->Len);
	return tlv_value->Len + 2;
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

