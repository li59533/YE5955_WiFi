/**
 **************************************************************************************************
 * @file        app_conf.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_conf.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "bsp_queue.h"
#include "lnprotocol.h"
#include "system_param.h"
#include "version.h"
/**
 * @addtogroup    app_conf_Modules 
 * @{  
 */

/**
 * @defgroup      app_conf_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_Private_Variables 
 * @brief         
 * @{  
 */
#define APP_CONF_DATASPACE_SIZE		200 
static uint8_t  app_conf_dataspace[APP_CONF_DATASPACE_SIZE] = { 0 };
/**
 * @}
 */
 
/**
 * @defgroup      app_conf_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void app_conf_revprocess_ln(uint8_t * buf , uint16_t len);
static void app_lnswitch_cmd(uint8_t * buf,uint16_t len);
static void app_setconfreq_process(uint8_t *payload,uint16_t len);
static void app_getconfreq_process(uint8_t *payload,uint16_t len);
static void app_getversionreq_process(uint8_t *payload,uint16_t len);
/**
 * @}
 */

/**
 * @defgroup      app_conf_Functions 
 * @brief         
 * @{  
 */
 

void APP_Conf_TestUart(void)
{
	
}

void APP_Conf_SendBytes(uint8_t *buf , uint16_t len )
{
	BSP_Usart_WriteBytes_DMA(BSP_UART_2 , buf , len);
}

void APP_Conf_RevProcess(void)
{
	uint8_t * buf_ptr = 0;
	uint8_t len = 0;
	if(BSP_Queue_GetCount(BSP_QUEUE_UART2_REV) > 0)
	{
		buf_ptr = BSP_Queue_Dequeue(BSP_QUEUE_UART2_REV, &len);
		app_conf_revprocess_ln( buf_ptr , len);
		
	}
}


static void app_conf_revprocess_ln(uint8_t * buf , uint16_t len)
{
	ln_protocolintance_t *ln_protocolintance = (ln_protocolintance_t *)buf;
	if( ln_protocolintance->head == LNPROTOCOL_HEAD)
	{
		if(ln_protocolintance->len == len)
		{
			if(buf[len - 2] == LNPROTOCOL_FOOT)
			{
				if(LNprotocol_AddChecksum(buf,len - 1) == buf[len -1])
				{
					app_lnswitch_cmd(&ln_protocolintance->cmd,len - sizeof(ln_protocolintance) - 1);
				}
				else
				{
					DEBUG("APP_Rev Check sum is err");
				}
			}
			else
			{
				DEBUG("APP_Rev Foot is err\r\n");
			}
		}
		else
		{
			DEBUG("APP_Rev Len is err\r\n");
		}
	}
	else
	{
		DEBUG("APP_Rev Head is err\r\n");
	}	
}

static void app_lnswitch_cmd(uint8_t * buf,uint16_t len)
{
	uint8_t cmd = 0;
	cmd = buf[0];
	DEBUG("APP_REV CMD is %X\r\n",cmd);
	
	switch(cmd)
	{
		case CMD_SetConf_Req:app_setconfreq_process(buf + 1, len -1 );break;
		case CMD_GetConf_Req:app_getconfreq_process(buf + 1, len -1 ) ;break;
		case CMD_GetVersion_Req: app_getversionreq_process(buf + 1, len -1 );break;
		default:break;
	}
}

static void app_setconfreq_process(uint8_t *payload,uint16_t len)
{

	uint8_t * payload_ptr = 0;
	LN_Tlv_t * tlv_buf = 0;
	uint8_t result = CONF_SUCCESS;
	
	
	payload_ptr = payload;
	DEBUG("APP_Rev Payload LEN is %d\r\n",len);
	while(1)
	{
		tlv_buf = (LN_Tlv_t *) payload_ptr;
		DEBUG("APP_Rev Tag is %X\r\n",tlv_buf->Tag);
		switch(tlv_buf->Tag)
		{
			case TAG_CONF_SN:
			{
				if(tlv_buf->Len == 8)
				{
					memcpy(g_SystemParam_Config.SNnumber , tlv_buf->Value.Array , tlv_buf->Len);
				}
				else
				{
					result = CONF_ERROR;
					DEBUG("TAG_CONF_SN is False\r\n");
				}
				
			}
			break;
			case TAG_CONF_X_K:
			{
				if(tlv_buf->Len == 4)
				{
					g_SystemParam_Config.floatscale[1] = * (float *) tlv_buf->Value.Array;
				}
				else
				{
					result = CONF_ERROR;
					DEBUG("TAG_CONF_X_K is False\r\n");
				}
			}
			break;
			case TAG_CONF_Y_K:
			{
				if(tlv_buf->Len == 4)
				{
					g_SystemParam_Config.floatscale[2] = * (float *) tlv_buf->Value.Array;
				}
				else
				{
					result = CONF_ERROR;
					DEBUG("TAG_CONF_Y_K is False\r\n");
				}
			}
			break;
			case TAG_CONF_Z_K:
			{
				if(tlv_buf->Len == 4)
				{
					g_SystemParam_Config.floatscale[0] = * (float *) tlv_buf->Value.Array;
				}
				else
				{
					result = CONF_ERROR;
					DEBUG("TAG_CONF_Z_K is False\r\n");
				}
			}
			break;
			case TAG_CONF_X_ADC_K:
			{
				if(tlv_buf->Len == 4)
				{
					g_SystemParam_Config.floatadc[1] = * (float *) tlv_buf->Value.Array;
				}
				else
				{
					result = CONF_ERROR;
					DEBUG("TAG_CONF_X_ADC_K is False\r\n");
				}
			}
			break;
			case TAG_CONF_Y_ADC_K:
			{
				if(tlv_buf->Len == 4)
				{
					g_SystemParam_Config.floatadc[2] = * (float *) tlv_buf->Value.Array;
				}
				else
				{
					result = CONF_ERROR;
					DEBUG("TAG_CONF_Y_ADC_K is False\r\n");
				}
			}
			break;
			case TAG_CONF_Z_ADC_K:
			{
				if(tlv_buf->Len == 4)
				{
					g_SystemParam_Config.floatadc[0] = * (float *) tlv_buf->Value.Array;
				}
				else
				{
					result = CONF_ERROR;
					DEBUG("TAG_CONF_Z_ADC_K is False\r\n");
				}
			}
			break;
			case TAG_CONF_CUR_BATTERY:
			{
				if(tlv_buf->Len == 4)
				{
					g_SystemParam_Config.battery = * (float *) tlv_buf->Value.Array;
				}
				else
				{
					result = CONF_ERROR;
					DEBUG("TAG_CONF_CUR_BATTERY is False\r\n");
				}
			}
			break;
			case TAG_CONF_RTC:
			{
				if(tlv_buf->Len == 4)
				{
					RTC_T datetime ;
					RTC_ConvertSecondsToDatetime(tlv_buf->Value.BIT_32 , &datetime);
					BSP_RTC_WriteClock( datetime.Year , datetime.Mon, datetime.Day , datetime.Hour , datetime.Min ,datetime.Sec );
				}
				else
				{
					result = CONF_ERROR;
					DEBUG("TAG_CONF_RTC is False\r\n");
				}
			}
			break;
			case TAG_CONF_SLEEPTIME:
			{
				if((tlv_buf->Value.BIT_32 <= 86400)&&(tlv_buf->Value.BIT_32 >= 0))   // < 1 day (86400 s) and >= 0 s
				{
					g_SystemParam_Config.sleep_time = tlv_buf->Value.BIT_32;
				}
				else
				{
					result = CONF_ERROR;
					DEBUG("TAG_CONF_SLEEPTIME is False\r\n");
				}
			}
			break;
			default:
			{
				result = CONF_ERROR;
				DEBUG("APP_Conf Tag is miss\r\n");
			}
			break;
		}
		
		payload_ptr = payload_ptr + tlv_buf->Len + 2 ;
		
		if((payload_ptr - payload)>= (len - 2))
		{
			break;
		}
	}

	if(result == CONF_ERROR)
	{
		DEBUG("APP_Conf is Err\r\n");
	}
	else
	{
		DEBUG("APP_Conf is SUCCESS then save\r\n");
		SystemParam_Save();
	}
	
}

// head len cmd tlv foot sum

static void app_getconfreq_process(uint8_t *payload,uint16_t len)
{
	ln_protocolintance_t *ln_protocolintance = (ln_protocolintance_t * )app_conf_dataspace;
	LN_Tlv_t tlv_value = { 0 };
	uint8_t  * payload_ptr = 0;

	
	ln_protocolintance->head = LNPROTOCOL_HEAD;
	//ln_protocolintance->len = sizeof(ln_protocolintance_t);
	ln_protocolintance->inf = 0x00;
	ln_protocolintance->cmd = CMD_GetConf_Resp;
	
	payload_ptr = &ln_protocolintance->cmd + 1;
	
	// ------- TAG_CONF_SN---------------
	tlv_value.Tag = TAG_CONF_SN;
	tlv_value.Len = 8;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Config.SNnumber , 8);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);	
	// --------------------------------
	// ------- TAG_CONF_X_K---------------
	tlv_value.Tag = TAG_CONF_X_K;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Config.floatscale[1] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);	
	// --------------------------------	
	// ------- TAG_CONF_Y_K---------------
	tlv_value.Tag = TAG_CONF_Y_K;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Config.floatscale[2] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);	
	// --------------------------------		
	// ------- TAG_CONF_Z_K---------------
	tlv_value.Tag = TAG_CONF_Z_K;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Config.floatscale[0] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);	
	// --------------------------------		
	// ------- TAG_CONF_X_ADC_K---------------
	tlv_value.Tag = TAG_CONF_X_ADC_K;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Config.floatadc[1] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);	
	// --------------------------------		
	// ------- TAG_CONF_Y_ADC_K---------------
	tlv_value.Tag = TAG_CONF_Y_ADC_K;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Config.floatadc[2] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);	
	// --------------------------------		
	// ------- TAG_CONF_Z_ADC_K---------------
	tlv_value.Tag = TAG_CONF_Z_ADC_K;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Config.floatadc[0] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);	
	// --------------------------------		
	// ------- TAG_CONF_CUR_BATTERY---------------
	tlv_value.Tag = TAG_CONF_CUR_BATTERY;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Config.battery , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);	
	// --------------------------------	
	// ------- TAG_CONF_RTC---------------
	tlv_value.Tag = TAG_CONF_RTC;
	tlv_value.Len = 4;
	
	uint32_t  timestamp = 0;
	RTC_T rtc_temp = BSP_RTC_Get();
	
	timestamp = RTC_ConvertDatetimeToSeconds(&rtc_temp);
	tlv_value.Value.BIT_32 = timestamp;
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);	
	
	// --------------------------------			
	// ------- TAG_CONF_SLEEPTIME---------------
	tlv_value.Tag = TAG_CONF_SLEEPTIME;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Config.sleep_time , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);	
	// --------------------------------		
		
	ln_protocolintance->len = (payload_ptr - &ln_protocolintance->head) + 1;
	*payload_ptr = LNPROTOCOL_FOOT;
	*(payload_ptr + 1) =  LNprotocol_AddChecksum((uint8_t * )&ln_protocolintance,ln_protocolintance->len - 1);
	
	APP_Conf_SendBytes(app_conf_dataspace,ln_protocolintance->len);
	
}




static void app_getversionreq_process(uint8_t *payload,uint16_t len)
{
	ln_protocolintance_t *ln_protocolintance = (ln_protocolintance_t * )app_conf_dataspace;
	uint8_t  * payload_ptr = 0;
	uint32_t version = 0 ;
	
	version = Version_Get_Bin();
	
	ln_protocolintance->head = LNPROTOCOL_HEAD;
	//ln_protocolintance->len = sizeof(ln_protocolintance_t);
	ln_protocolintance->inf = 0x00;
	ln_protocolintance->cmd = CMD_GetVersion_Resp;
	
	payload_ptr = &ln_protocolintance->cmd + 1;
	// -------version---------------
	memcpy(payload_ptr,&version,4);
	payload_ptr += 4;
	// --------------------------------
	ln_protocolintance->len = (payload_ptr - &ln_protocolintance->head) + 1;
	*payload_ptr = LNPROTOCOL_FOOT;
	*(payload_ptr + 1) =  LNprotocol_AddChecksum((uint8_t * )&ln_protocolintance,ln_protocolintance->len - 1);
	
	APP_Conf_SendBytes(app_conf_dataspace,ln_protocolintance->len);
}

void APP_Conf_ReportData(void) // Report Data in Uart2
{
	ln_protocolintance_t *ln_protocolintance = (ln_protocolintance_t * )app_conf_dataspace;
	LN_Tlv_t tlv_value = { 0 };
	uint8_t  * payload_ptr = 0;


	ln_protocolintance->head = LNPROTOCOL_HEAD;
	//ln_protocolintance->len = sizeof(ln_protocolintance_t);
	ln_protocolintance->inf = 0x00;
	ln_protocolintance->cmd = CMD_ReportData;

	payload_ptr = &ln_protocolintance->cmd + 1;

	// ------- TAG_X_ACC_VALUE---------------
	tlv_value.Tag = TAG_X_ACC_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.EffectiveValue[1] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------
	// ------- TAG_X_SPEED_VALUE---------------
	tlv_value.Tag = TAG_X_SPEED_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.Vrms[1] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------	
	// ------- TAG_X_DISPLACE_VALUE---------------
	tlv_value.Tag = TAG_X_DISPLACE_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.Drms[1] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------		
	// ------- TAG_X_KURTOSIS_VALUE---------------
	tlv_value.Tag = TAG_X_KURTOSIS_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.KurtosisIndex[1] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------			
	// ------- TAG_X_ENVELOPE_VALUE---------------
	tlv_value.Tag = TAG_X_ENVELOPE_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.Envelop[1] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------				
	// ------- TAG_Y_ACC_VALUE---------------
	tlv_value.Tag = TAG_Y_ACC_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.EffectiveValue[2] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------
	// ------- TAG_Y_SPEED_VALUE---------------
	tlv_value.Tag = TAG_Y_SPEED_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.Vrms[2] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------	
	// ------- TAG_Y_DISPLACE_VALUE---------------
	tlv_value.Tag = TAG_Y_DISPLACE_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.Drms[2] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------		
	// ------- TAG_Y_KURTOSIS_VALUE---------------
	tlv_value.Tag = TAG_Y_KURTOSIS_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.KurtosisIndex[2] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------			
	// ------- TAG_Y_ENVELOPE_VALUE---------------
	tlv_value.Tag = TAG_Y_ENVELOPE_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.Envelop[2] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------				
		// ------- TAG_Z_ACC_VALUE---------------
	tlv_value.Tag = TAG_Z_ACC_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.EffectiveValue[0] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------
	// ------- TAG_Z_SPEED_VALUE---------------
	tlv_value.Tag = TAG_Z_SPEED_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.Vrms[0] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------	
	// ------- TAG_Z_DISPLACE_VALUE---------------
	tlv_value.Tag = TAG_Z_DISPLACE_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.Drms[0] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------		
	// ------- TAG_Z_KURTOSIS_VALUE---------------
	tlv_value.Tag = TAG_Z_KURTOSIS_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.KurtosisIndex[0] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------			
	// ------- TAG_Z_ENVELOPE_VALUE---------------
	tlv_value.Tag = TAG_Z_ENVELOPE_VALUE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.Envelop[0] , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------				
	// ------- TAG_TEMPERATURE---------------
	tlv_value.Tag = TAG_TEMPERATURE;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Param.pdate , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------		
		// ------- TAG_BATTERY---------------
	tlv_value.Tag = TAG_BATTERY;
	tlv_value.Len = 4;
	memcpy(tlv_value.Value.Array , (uint8_t *)&g_SystemParam_Config.battery , 4);
	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------		
	
	
	
	ln_protocolintance->len = (payload_ptr - &ln_protocolintance->head) + 1;
	*payload_ptr = LNPROTOCOL_FOOT;
	*(payload_ptr + 1) =  LNprotocol_AddChecksum((uint8_t * )&ln_protocolintance,ln_protocolintance->len - 1);

	APP_Conf_SendBytes(app_conf_dataspace,ln_protocolintance->len);

}

void APP_Conf_FromLora(uint8_t *buf , uint8_t len )
{
	uint8_t conf_buf[50] = { 0 };
	uint8_t i = 0;
	if(len > 0)
	{
		for( i = 0 ; i < ( len /2) ; i ++)
		{
			conf_buf[i] = APP_Conf_StrTo16(buf[i * 2],buf[i * 2+1]);
		}
		
		if(conf_buf[0] == 0x7e)
		{
			if(conf_buf[5] == 0x7e)
			{
				uint32_t sleeptime_temp = (uint32_t)(conf_buf[1] << 24 | conf_buf[2] << 16 | conf_buf[3] << 8 | conf_buf[4]);// 
				DEBUG("APP_CONF Lora sleepTime:%d s\r\n" , sleeptime_temp);
				if((sleeptime_temp <= 86400)&&(sleeptime_temp >= 0))   // < 1 day (86400 s) and >= 0 s
				{
					g_SystemParam_Config.sleep_time = sleeptime_temp;
					SystemParam_Save();
				}
				
			}

		}
		
	}
	else
	{
		DEBUG("APP Conf From Lora is NONE\r\n");
	}
}

uint8_t APP_Conf_StrTo16(char buf1,char buf2)
{
	uint8_t high = 0;
	uint8_t low = 0;
	if(buf1 >= '0'&& buf1 <= '9')
	{
		high = (buf1 - '0') * 16;
	}
	else if (buf1 >= 'a' && buf1 <= 'f')
	{
		high = ((buf1 - 'a') + 10) * 16;
	}
	else
	{
		high = ((buf1 - 'A') + 10) * 16;
	}
	
	if(buf2 >= '0'&& buf2 <= '9')
	{
		low = (buf2 - '0') ;
	}
	else if (buf2 >= 'a' && buf2 <= 'f')
	{
		low = ((buf2 - 'a') + 10) ;
	}
	else
	{
		low = ((buf2 - 'A') + 10) ;
	}
	
	return high + low;
	
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

