/**
 **************************************************************************************************
 * @file        app_datasend.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_datasend.h"
#include "stm32_bsp_conf.h"
#include "FreeRTOS.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "bsp_lm78.h"
#include "system_param.h" 
#include "app_battery.h"
#include "app_conf.h"
#include "bsp_esp32.h"

#include "rtos_tools.h"
#include "app_datafilter.h"

#include "app_conf_net.h"
/**
 * @addtogroup    app_datasend_Modules 
 * @{  
 */

/**
 * @defgroup      app_datasend_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datasend_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_datasend_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datasend_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_datasend_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_datasend_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datasend_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datasend_Functions 
 * @brief         
 * @{  
 */

	
void APP_DataSend_NetConnected(void)
{
	
	
	
	APP_Report_ChannelKind(Current_Is_NET) ;  // 
	//RTOS_Delay_ms(10);
	APP_Report_ID(Current_Is_NET) ;  // 
	//RTOS_Delay_ms(10);
	APP_Report_Version(Current_Is_NET) ;  // 
	//RTOS_Delay_ms(10);
	APP_Report_ChannelCondition(Current_Is_NET); 
	//RTOS_Delay_ms(10);
	APP_Report_SampleParam(Current_Is_NET) ;
	//RTOS_Delay_ms(10);
	APP_Report_APinf(Current_Is_NET)  ;
	//RTOS_Delay_ms(10);
	APP_Report_TCPServer(Current_Is_NET) ;  
	//RTOS_Delay_ms(10);
	APP_Report_RunMode(Current_Is_NET)   ;
	//RTOS_Delay_ms(10);
	APP_Report_IPinf(Current_Is_NET)  ;
	//RTOS_Delay_ms(10);
	APP_Report_LowPower(Current_Is_NET)  ;
	//RTOS_Delay_ms(10);
	APP_Report_Scale(Current_Is_NET)  ;
	//RTOS_Delay_ms(10);
	APP_Report_AlarmValue(Current_Is_NET);
	//RTOS_Delay_ms(10);
	APP_Report_LowPowerValue(Current_Is_NET); 
}


int8_t APP_DataSend_SendCharacteristic(void)
{
	char app_databuf[200] = { 0 };

	char app_datastrbuf[200] = { 0 };
	uint16_t ptr = 0;
	uint8_t * app_databuf_ptr = 0;
	uint16_t len = 0 ;
	uint16_t battery_temp = 0;
	//app_datasend_test();
	
	int16_t temperature_temp = 0;
	struct
	{
		uint16_t EffectiveValue[4];
		uint16_t Vrms[4];
		uint16_t Drms[4];
		uint16_t KurtosisIndex[4];
		uint16_t Envelop[4];
	}character_buf;
	
	battery_temp = (uint16_t )g_SystemParam_Config.battery * 10;
	temperature_temp = (int16_t )g_SystemParam_Param.pdate * 10;
	for( uint8_t i = 0 ; i < 3 ; i ++)
	{
		if(g_SystemParam_Param.EffectiveValue[i] <= 6000.0f)
		{
			character_buf.EffectiveValue[i] = (uint16_t)(g_SystemParam_Param.EffectiveValue[i] * 10);
		}
		else
		{
			character_buf.EffectiveValue[i] = 60000;
		}
		
		if(g_SystemParam_Param.Vrms[i] <= 6000.0f)
		{
			character_buf.Vrms[i] = (uint16_t)(g_SystemParam_Param.Vrms[i] * 10);
		}
		else
		{
			character_buf.Vrms[i] = 60000;
		}
		
		if(g_SystemParam_Param.Drms[i] <= 6000.0f)
		{
			character_buf.Drms[i] = (uint16_t)(g_SystemParam_Param.Drms[i] * 10);
		}
		else
		{
			character_buf.Drms[i] = 60000;
		}

		if(g_SystemParam_Param.KurtosisIndex[i] <= 6000.0f)
		{
			character_buf.KurtosisIndex[i] = (uint16_t)(g_SystemParam_Param.KurtosisIndex[i] * 10);
		}
		else
		{
			character_buf.KurtosisIndex[i] = 60000;
		}
		
		if(g_SystemParam_Param.Envelop[i] <= 6000.0f)
		{
			character_buf.Envelop[i] = (uint16_t)(g_SystemParam_Param.Envelop[i] * 10);
		}
		else
		{
			character_buf.Envelop[i] = 60000;
		}		
	}
	
	// ------SN ----------------
	memcpy(app_databuf , g_SystemParam_Config.SNnumber , 8);
	
	// -------offset---------------
	app_databuf_ptr = (uint8_t *)&app_databuf[8];
	
	// ------charater ----------
	for(uint8_t i = 0 ; i < 3; i ++)
	{
		memcpy(app_databuf_ptr + 10*i + 0 , &character_buf.EffectiveValue[i] , 2 );
		memcpy(app_databuf_ptr + 10*i + 2, &character_buf.Vrms[i] , 2 );
		memcpy(app_databuf_ptr + 10*i + 4, &character_buf.Drms[i] , 2 );
		memcpy(app_databuf_ptr + 10*i + 6, &character_buf.KurtosisIndex[i] , 2 );
		memcpy(app_databuf_ptr + 10*i + 8, &character_buf.Envelop[i] , 2 );
		len = 10*i + 8 + 2;
	}
	// ------temperature -------
	memcpy(app_databuf_ptr + len, &temperature_temp , 2 );
	len += 2;
	
	// ------ battery ----------
	memcpy(app_databuf_ptr + len, &battery_temp , 2 );
	len += 2;
	
	// ------rtc ---------------
	uint32_t  timestamp = 0;
	RTC_T rtc_temp = BSP_RTC_Get();
	
	timestamp = RTC_ConvertDatetimeToSeconds(&rtc_temp);
	memcpy(app_databuf_ptr + len, &timestamp , 4 );
	len += 4;
	// -------------------------

	for(uint16_t i = 0 ; i < len + 8 ; i ++)
	{
		ptr += snprintf( app_datastrbuf + ptr , 200 - ptr , "%02X",app_databuf[i]);
	}
	
	//snprintf(app_datastrbuf, 200 , "%0.3f",g_SystemParam_Param.pdate);
	//memcpy(app_datastrbuf,(uint8_t * )&g_SystemParam_Param.pdate , 4);
	
	
	DEBUG("This Value will send:%s len:%d\r\n",app_datastrbuf,strlen((const char *)app_datastrbuf));
	
	//uint8_t test_buf[8] = {0x00 , 0x00, 0x34,0x12,0x00,0x00,0x38,0x00};
	
	//BSP_LM78_StartSend((uint8_t *)app_datastrbuf, strlen((const char *)app_datastrbuf));
	
	APP_Battery_Reduce();
	
	return 0 ; 
}





void BoardAutoPeroidWave(void)
{ 
	if(ESP32_GetModule_Status(ESP32_MODULE_STATUS) != ESP32_CONNECTED)
	{
		return;
	}

	
	uint8_t checksum = 0;
	uint16_t wpp = 0;
	int16_t sendperioddata = 0;
	uint32_t beforeSAMPLEblock = (currentSAMPLEblock + 1) % 2;;
	int16_t yy;
	int16_t *p;
	uint16_t packege_flag = 0;
	uint16_t buflength = g_SystemParam_Param.periodboardpoints + 1 + 7 + 2;//1个字节通道号 7个字节时间，2个字节包号
	uint8_t * PeriodWaveToSend;
	float inter_factor = 0;
	
	RTC_T rtc_data ;
	
	PeriodWaveToSend = pvPortMalloc(600); //vPortFree()
	rtc_data = BSP_RTC_Get();
	
	for(uint32_t ii = 0;ii < g_SystemParam_Param.acceleration_adchs ; ii ++)
	{
		if(((g_SystemParam_Config.DataToSendChannel >> ii) & 0x01) == 0)  //未使能的通道不发送
		{
			continue;
		}

		switch(ii)
		{
			case 0:
				p=&piz_emu_data[beforeSAMPLEblock][0];
				break;
			case 1:
				p=&mems_emu_data[beforeSAMPLEblock][0][0];
				break;
			case 2:
				p=&mems_emu_data[beforeSAMPLEblock][1][0];
				break;
			default:
			break;
		}
		
		inter_factor = g_SystemParam_Config.floatadc[ii] * g_SystemParam_Config.floatscale[ii] * 1250.0f / g_SystemParam_Config.floatrange[ii];
		
		for(uint32_t i = 0 ; i < g_SystemParam_Config.channel_freq[ii] ; i ++) //*config.ADtime
		{
			yy = *p;
			p ++;
			sendperioddata = (int16_t)(yy * inter_factor);//(int16_t)(yy*Parameter.ReciprocalofRange[ii]);

			PeriodWaveToSend[wpp + 14] = sendperioddata;
			PeriodWaveToSend[wpp + 15] = sendperioddata >>8;
//			checksum += (PeriodWaveToSend[wpp + 14] + PeriodWaveToSend[wpp + 15]);			 
			wpp = wpp + 2;			
			
			if(wpp > (g_SystemParam_Param.periodboardpoints - 1)) 
			{	
				PeriodWaveToSend[0] = 0x7e;//TELid;
				PeriodWaveToSend[1] = 0x70;//TELid>>8;	
				PeriodWaveToSend[2] = buflength;//TELid>>16;
				PeriodWaveToSend[3] = (uint8_t)(buflength>>8);// TELid>>24; //2,3????????482??
				PeriodWaveToSend[4] = ii+1;// TELid>>24;
				PeriodWaveToSend[5] = rtc_data.Year;
				PeriodWaveToSend[6] = rtc_data.Year>>8;
				PeriodWaveToSend[7] = rtc_data.Mon;
				PeriodWaveToSend[8] = rtc_data.Day; //时间用32位表示
				PeriodWaveToSend[9] = rtc_data.Hour;
				PeriodWaveToSend[10] = rtc_data.Min;
				PeriodWaveToSend[11] = rtc_data.Sec; //时间用32位表示		
				PeriodWaveToSend[12] = packege_flag; //时间用32位表示
				PeriodWaveToSend[13] = packege_flag >> 8; //时间用32位表示

				for(uint16_t j = 1; j < g_SystemParam_Param.periodboardpoints + 14 ; j ++)
				{
					checksum += PeriodWaveToSend[j];
				}
				
				PeriodWaveToSend[14 + g_SystemParam_Param.periodboardpoints] = checksum;//checksum;  //2,3????????482??
				PeriodWaveToSend[15 + g_SystemParam_Param.periodboardpoints] = 0x7e; 
				packege_flag ++;
				
				if(packege_flag > 127)
				{
					DEBUG("packege_flag > 127 \r\n");
				}
				
				BSP_ESP32_TX_Enqueue(PeriodWaveToSend,g_SystemParam_Param.periodboardpoints+16);	

				DEBUG("packege_No %d checksum : 0x%02X\r\n",packege_flag,checksum);
				wpp = 0;
				checksum = 0;
				
			}
		}
		
		RTOS_Delay_ms(30);
	}
	vPortFree(PeriodWaveToSend);
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

