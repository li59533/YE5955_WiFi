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
#include "lnprotocol_std.h"
#include "version.h"
#include "rtos_tools.h"
#include "app_datafilter.h"
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
 
 
void app_datasend_test(void)
{
	float temp = 5.5;
	uint8_t float_temp[4];
	char buf[30];
	uint8_t ptr = 0;
	memcpy( float_temp, (uint8_t *)&temp , 4 );
	
	for(uint8_t i = 0; i < 4 ; i ++)
	{
		ptr += snprintf(buf + ptr , 30 - ptr , "%02X",float_temp[i]);
	}
	DEBUG("%s\r\n",buf);
}
	
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



int8_t APP_Report_ChannelKind(uint8_t channel_type)   // 
{
	
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_ChannelKind\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_CHANNELKIND;
			sendbuf_ptr[2] = 0x06;
			sendbuf_ptr[3] = 0x00;
			
			sendbuf_ptr[4] = g_SystemParam_Param.acceleration_adchs + g_SystemParam_Param.temp_adchs; //两个，一个温度一个加速度
			sendbuf_ptr[5] = 0x02;  //这一块，每种传感器手工添加
			sendbuf_ptr[6] = 0x01;
			sendbuf_ptr[7] = g_SystemParam_Param.acceleration_adchs;
			sendbuf_ptr[8] = 0x02;
			sendbuf_ptr[9] = g_SystemParam_Param.temp_adchs;
			sendbuf_ptr[10] = 0;
			for(uint16_t i = 1 ; i < 10 ;i ++)
			{
				sendbuf_ptr[10] += sendbuf_ptr[i];
			}
			
			sendbuf_ptr[11] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = 12;

			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
			
			
		}
		else
		{
			DEBUG("ESP32_GetWorkSpace is NULL\r\n");
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}


int8_t APP_Report_ID(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_ID\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_SNCODE;
			sendbuf_ptr[2] = 0x08;
			sendbuf_ptr[3] = 0x00;
			sendbuf_ptr[4] = g_SystemParam_Config.SNnumber[0];
			sendbuf_ptr[5] = g_SystemParam_Config.SNnumber[1];
			sendbuf_ptr[6] = g_SystemParam_Config.SNnumber[2];
			sendbuf_ptr[7] = g_SystemParam_Config.SNnumber[3];
			sendbuf_ptr[8] = g_SystemParam_Config.SNnumber[4];
			sendbuf_ptr[9] = g_SystemParam_Config.SNnumber[5];
			sendbuf_ptr[10] = g_SystemParam_Config.SNnumber[6];
			sendbuf_ptr[11] = g_SystemParam_Config.SNnumber[7];
			sendbuf_ptr[12] = 0;
			for(uint16_t i = 1;i < 12;i ++)
			{
				sendbuf_ptr[12] += sendbuf_ptr[i];
			}
			
			sendbuf_ptr[13] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = 14;

			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}



int8_t APP_Report_Version(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_Version\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			char * version_ptr = 0;
			
			version_ptr = Version_Get_Str();
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;	
			sendbuf_ptr[1] = LN_P_R_VERSION;	
			sendbuf_ptr[2] = 0x10;
			sendbuf_ptr[3] = 0x00;
			for(uint32_t i = 0;i < 16;i++) //strcpy
			{
				sendbuf_ptr[4+i] = version_ptr[i];
			}
			sendbuf_ptr[20] = 0;
			for(uint32_t i = 1;i < 20;i++) //strcpy
			{
				sendbuf_ptr[20] += sendbuf_ptr[i];
			}
			sendbuf_ptr[21] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = 22;

			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}

int8_t APP_Report_ChannelCondition(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_ChannelCondition\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
		
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_CHANNELCONDITION;
			sendbuf_ptr[2] = 0x02;
			sendbuf_ptr[3] = 0x00;
			sendbuf_ptr[4] = g_SystemParam_Config.DataToSendChannel; //两个，一个温度一个加速度

			sendbuf_ptr[5] = 0x00;//config.DataToSendChannel>>8;
			sendbuf_ptr[6] = 0;
			for(uint16_t i = 1;i < 6;i++)
			{
				sendbuf_ptr[6] += sendbuf_ptr[i];
			}


			sendbuf_ptr[7] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = 8;

			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}


int8_t APP_Report_SampleParam(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_SampleParam\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_SAMPLEPARAM;
			sendbuf_ptr[2] = 0x0B;
			sendbuf_ptr[3] = 0x00;
			sendbuf_ptr[4] = g_SystemParam_Config.ADfrequence; //两个，一个温度一个加速度

			sendbuf_ptr[5] = g_SystemParam_Config.ADfrequence >> 8;
			sendbuf_ptr[6] = g_SystemParam_Config.ADfrequence >> 16; //两个，一个温度一个加速度

			sendbuf_ptr[7] = g_SystemParam_Config.ADfrequence >> 24;
			sendbuf_ptr[8] = g_SystemParam_Config.ADtime;
			sendbuf_ptr[9] = g_SystemParam_Config.PeriodTransimissonCounter;
			sendbuf_ptr[10] = g_SystemParam_Config.PeriodTransimissonCounter >> 8;
			sendbuf_ptr[11] = (uint8_t)g_SystemParam_Config.PeriodTransimissonStatus;

			sendbuf_ptr[12] = g_SystemParam_Config.workcycleseconds;
			sendbuf_ptr[13] = g_SystemParam_Config.workcycleseconds>>8;
			sendbuf_ptr[14] = (uint8_t)g_SystemParam_Config.ParameterTransimissonStatus;
			sendbuf_ptr[15] = 0;
			for(uint16_t i = 1;i < 15;i++)
			{
				sendbuf_ptr[15] += sendbuf_ptr[i];
			}

			sendbuf_ptr[16] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = 17;

			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}


int8_t APP_Report_APinf(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_APinf\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
			uint8_t APSSIDlength = strlen(g_SystemParam_Config.APssid);
			uint8_t APPASSWORDlength = strlen(g_SystemParam_Config.APpassword);

			sendbuf_len = 10 + APSSIDlength+APPASSWORDlength;
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_APINF;   //T
			sendbuf_ptr[2] = sendbuf_len - 6;
			sendbuf_ptr[3] = (sendbuf_len - 6) >> 8;   //L
			sendbuf_ptr[4] = 0X00;   //V_IP
			sendbuf_ptr[5] = APSSIDlength;
			
			for(uint8_t i = 0;i < APSSIDlength;i ++)
			{
				sendbuf_ptr[6 + i] = g_SystemParam_Config.APssid[i];
			}

			sendbuf_ptr[6 + APSSIDlength] = 0X01;   //V_MASK
			sendbuf_ptr[7 + APSSIDlength] = APPASSWORDlength;
			
			for(uint8_t i = 0;i < APPASSWORDlength;i++)
			{
				sendbuf_ptr[8 + APSSIDlength+i] = g_SystemParam_Config.APpassword[i];
			}
			
			sendbuf_ptr[8 + APSSIDlength + APPASSWORDlength] = 0X00;   //校验和

			for(uint8_t i = 1;i < (8 + APSSIDlength + APPASSWORDlength);i ++)
			{
				sendbuf_ptr[8 + APSSIDlength + APPASSWORDlength] += sendbuf_ptr[i];//把AP字符串赋值给config
			}
			
			sendbuf_ptr[9 + APSSIDlength + APPASSWORDlength] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = 10 + APSSIDlength + APPASSWORDlength;			

			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}




int8_t APP_Report_TCPServer(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_TCPServer\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
			uint8_t TcpServer_IPlength=strlen(g_SystemParam_Config.TcpServer_IP);
			uint8_t TcpServer_Portlength=strlen(g_SystemParam_Config.TcpServer_Port);
			sendbuf_len = 10 + TcpServer_Portlength + TcpServer_IPlength;
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_TCPSERVER;   //T
			sendbuf_ptr[2] = sendbuf_len-6;
			sendbuf_ptr[3] = (sendbuf_len-6)>>8;   //L
			sendbuf_ptr[4] = 0X00;   //V_IP
			sendbuf_ptr[5] = TcpServer_IPlength;
			{
			for(uint8_t i = 0;i < TcpServer_IPlength;i ++)
			sendbuf_ptr[6 + i] = g_SystemParam_Config.TcpServer_IP[i];

			}
			sendbuf_ptr[6 + TcpServer_IPlength] = 0X01;   //V_MASK
			sendbuf_ptr[7 + TcpServer_IPlength] = TcpServer_Portlength;
			{
			for(uint8_t i = 0;i < TcpServer_Portlength;i ++)
			sendbuf_ptr[8 + TcpServer_IPlength + i] = g_SystemParam_Config.TcpServer_Port[i];

			}
			sendbuf_ptr[8 + TcpServer_IPlength + TcpServer_Portlength] = 0X00;   //校验和

			for(uint8_t i = 1;i < (8 + TcpServer_IPlength + TcpServer_Portlength);i ++)
			sendbuf_ptr[8 + TcpServer_IPlength + TcpServer_Portlength] += sendbuf_ptr[i];//把AP字符串赋值给config
			sendbuf_ptr[9 + TcpServer_IPlength + TcpServer_Portlength] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = 10 + TcpServer_IPlength + TcpServer_Portlength;			
			
			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}




int8_t APP_Report_RunMode(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_RunMode\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_RUNMODE;
			sendbuf_ptr[2] = 0x01;
			sendbuf_ptr[3] = 0x00;
			sendbuf_ptr[4] = g_SystemParam_Config.DataToBoardMode; //两个，一个温度一个加速度

			sendbuf_ptr[5] = 0;
			for(uint16_t i = 1;i < 5;i++)
			{
				sendbuf_ptr[5] += sendbuf_ptr[i];	
			}
				 
			sendbuf_ptr[6] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = 7;
			
			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}


int8_t APP_Report_IPinf(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_IPinf\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
			uint8_t localIPlength = strlen(g_SystemParam_Config.LocalIP);
			uint8_t LocalMASKlength = strlen(g_SystemParam_Config.LocalMASK);
			uint8_t LocalGATEWAYlength = strlen(g_SystemParam_Config.LocalGATEWAY);
			sendbuf_len = 15 + localIPlength + LocalMASKlength + LocalGATEWAYlength;
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_IPINF;   //T
			sendbuf_ptr[2] = sendbuf_len - 6;
			sendbuf_ptr[3] = (sendbuf_len - 6) >> 8;   //L
			sendbuf_ptr[4] = 0X00;   //V_IP
			sendbuf_ptr[5] = localIPlength;
			
			for(uint8_t i=0;i<localIPlength;i++)
			{
				sendbuf_ptr[6+i] = g_SystemParam_Config.LocalIP[i];
			}
			
			sendbuf_ptr[6 + localIPlength] = 0X01;   //V_MASK
			sendbuf_ptr[7 + localIPlength] = LocalMASKlength;
			
			for(uint8_t i = 0;i < LocalMASKlength;i++)
			{
				sendbuf_ptr[8 + localIPlength + i] = g_SystemParam_Config.LocalMASK[i];
			}
			
			sendbuf_ptr[8 + localIPlength + LocalMASKlength] = 0X02;   //V_GATEWAY
			sendbuf_ptr[9 + localIPlength + LocalMASKlength] = LocalGATEWAYlength;
			
			for(uint8_t i = 0;i < LocalGATEWAYlength;i ++)
			{
				sendbuf_ptr[10 + localIPlength + LocalMASKlength + i] = g_SystemParam_Config.LocalGATEWAY[i];
			}
			
			sendbuf_ptr[10 + localIPlength + LocalMASKlength + LocalGATEWAYlength] = 0X03;
			sendbuf_ptr[11 + localIPlength + LocalMASKlength + LocalGATEWAYlength] = 0X01;
			sendbuf_ptr[12 + localIPlength + LocalMASKlength + LocalGATEWAYlength] = g_SystemParam_Config.DHCP;
			sendbuf_ptr[13 + localIPlength + LocalMASKlength + LocalGATEWAYlength] = 0;
			for(uint8_t i = 1;i < (13 + localIPlength + LocalMASKlength + LocalGATEWAYlength);i ++)
			{
				sendbuf_ptr[13 + localIPlength + LocalMASKlength + LocalGATEWAYlength] += sendbuf_ptr[i];//把AP字符串赋值给config
			}
			
			sendbuf_ptr[14 + localIPlength + LocalMASKlength + LocalGATEWAYlength] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = 15 + localIPlength + LocalMASKlength + LocalGATEWAYlength;			
			
			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}


int8_t APP_Report_LowPower(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_LowPower\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_LOWPOWER;
			sendbuf_ptr[2] = 0x08;  //8个字节长度
			sendbuf_ptr[3] = 0x00;
			sendbuf_ptr[4] = g_SystemParam_Config.Lowpower_Mode; //两个，一个温度一个加速度	
			sendbuf_ptr[5] = g_SystemParam_Config.scan_channel;
			sendbuf_ptr[6] = g_SystemParam_Config.Waitforsleeptime;
			sendbuf_ptr[7] = g_SystemParam_Config.WaitforIEPEtime;
			sendbuf_ptr[8] = 0;
			sendbuf_ptr[9] = 0;
			sendbuf_ptr[10] = 0;
			sendbuf_ptr[11] = 0;
			sendbuf_ptr[12] = 0;
			for(uint16_t i = 1;i < 12;i ++)
			{
				sendbuf_ptr[12] += sendbuf_ptr[i];
			}
			
			sendbuf_ptr[13] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = 14;
			
			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}


int8_t APP_Report_Scale(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_Scale\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
			
			float interscale = 0;
			unsigned char *floatCdata;
			
			uint16_t channelnum = g_SystemParam_Param.acceleration_adchs;  //这边限制通道个数
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_SCALE;   
			sendbuf_ptr[2] = channelnum*17;
			sendbuf_ptr[3] = (channelnum*17) >> 8;   //L
			for(uint8_t i = 0;i < channelnum;i ++)
			{
				sendbuf_ptr[4 + 17 * i] = i;   //V_IP

				sendbuf_ptr[5 + 17 * i] = g_SystemParam_Config.channel_freq[i];
				sendbuf_ptr[6 + 17 * i] = g_SystemParam_Config.channel_freq[i] >> 8; 
				sendbuf_ptr[7 + 17 * i] = g_SystemParam_Config.channel_freq[i] >> 16; 
				sendbuf_ptr[8 + 17 * i] = g_SystemParam_Config.channel_freq[i] >> 24; 		 
				interscale=1.0f / g_SystemParam_Config.floatscale[i];  

				floatCdata = (unsigned char *)&interscale;
				sendbuf_ptr[9 + 17 * i] = *floatCdata;
				sendbuf_ptr[10 + 17 * i] = *(floatCdata + 1);;
				sendbuf_ptr[11 + 17 * i] = *(floatCdata + 2);
				sendbuf_ptr[12 + 17 * i] = *(floatCdata + 3);
				floatCdata = (unsigned char *)&g_SystemParam_Config.alarmgate[i];
				sendbuf_ptr[13 + 17 * i] = *floatCdata;
				sendbuf_ptr[14 + 17 * i] = *(floatCdata + 1);;
				sendbuf_ptr[15 + 17 * i] = *(floatCdata + 2);
				sendbuf_ptr[16 + 17 * i] = *(floatCdata + 3);
				floatCdata = (unsigned char *)&g_SystemParam_Config.floatrange[i];
				sendbuf_ptr[17 + 17 * i] = *floatCdata;
				sendbuf_ptr[18 + 17 * i] = *(floatCdata + 1);;
				sendbuf_ptr[19 + 17 * i] = *(floatCdata + 2);
				sendbuf_ptr[20 + 17 * i] = *(floatCdata + 3);

			}

			sendbuf_ptr[channelnum * 17 + 4] = 0;
			for(uint16_t j = 1;j < (channelnum * 17 + 4);j ++)
			{
				sendbuf_ptr[channelnum * 17 + 4] += sendbuf_ptr[j];
			}
			sendbuf_ptr[channelnum * 17 + 5] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = channelnum * 17 + 6;			
			
			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}


int8_t APP_Report_AlarmValue(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_AlarmValue\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
			unsigned char *floatCdata;
			uint16_t channelnum = 17;  //这边限制通道个数
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_ALARMVALUE;   
			sendbuf_ptr[2] = channelnum*4;
			sendbuf_ptr[3] = (channelnum*4)>>8;   //L
			for(uint8_t i = 0;i < channelnum;i ++)
			{
				floatCdata = (unsigned char *)&g_SystemParam_Config.Alarm_value_junyue[i];
				sendbuf_ptr[4 + 4 * i] = *floatCdata;
				sendbuf_ptr[5 + 4 * i] = *(floatCdata+1);
				sendbuf_ptr[6 + 4 * i] = *(floatCdata+2);
				sendbuf_ptr[7 + 4 * i] = *(floatCdata+3);	 
			}

			sendbuf_ptr[channelnum * 4 + 4] = 0;
			for(uint16_t j = 1;j < (channelnum * 4 + 4);j++)
			{
				sendbuf_ptr[channelnum * 4 + 4] += sendbuf_ptr[j];
			}
			sendbuf_ptr[channelnum * 4 + 5] = LNPROTOCOL_STD_FOOT;
			sendbuf_len = channelnum * 4 + 6;
			
			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}






int8_t APP_Report_LowPowerValue(uint8_t channel_type)   // 
{
	if(channel_type == Current_Is_NET)
	{
		if(ESP32_GetWorkSpace() != NULL)
		{
			DEBUG("APP_Report_LowPowerValue\r\n");
			uint8_t * sendbuf_ptr = 0;
			uint16_t sendbuf_len = 0;
			sendbuf_ptr = ESP32_GetWorkSpace();
			
			sendbuf_ptr[0] = LNPROTOCOL_STD_HEAD;
			sendbuf_ptr[1] = LN_P_R_LOWPOWER_VALUE;
			sendbuf_ptr[2] = 0x08;  //8个字节长度
			sendbuf_ptr[3] = 0x00;
			sendbuf_ptr[4] = g_SystemParam_Config.workcycleseconds_inAlarmStatue;
			sendbuf_ptr[5] = g_SystemParam_Config.workcycleseconds_inAlarmStatue>>8;
			sendbuf_ptr[6] = (short)g_SystemParam_Config.tempCompensation;
			sendbuf_ptr[7] = (short)g_SystemParam_Config.tempCompensation>>8;
			sendbuf_ptr[8] = 0;
			sendbuf_ptr[9] = 0;
			sendbuf_ptr[10] = 0;
			sendbuf_ptr[11] = 0;
			sendbuf_ptr[12] = 0;
			for(uint16_t i = 1;i < 12;i++)
			{
				sendbuf_ptr[12] += sendbuf_ptr[i];
			}
			
			sendbuf_ptr[13] = LNPROTOCOL_STD_FOOT;
			sendbuf_len=14;
			
			BSP_ESP32_TX_Enqueue(sendbuf_ptr,  sendbuf_len);
						
		}
		else
		{
			return -1;
		}
	}
	else
	{
		
	}

	return 1;
		
}


void BoardAutoPeroidWave(void)
{ 
	if(ESP32_GetModule_Status(ESP32_MODULE_STATUS) != ESP32_CONNECTED)
	{
		return;
		
	}
	uint8_t checksum = 0;
	uint32_t wpp = 0;
	int16_t sendperioddata = 0;
	uint32_t beforeSAMPLEblock = (currentSAMPLEblock + 1) % 2;;
	float yy;
	int16_t *p;
	uint16_t packege_flag = 0;
	uint16_t buflength = g_SystemParam_Param.periodboardpoints + 1 + 7 + 2;//1个字节通道号 7个字节时间，2个字节包号
	uint8_t PeriodWaveToSend[600] = { 0 };
	float inter_factor = 0;
	RTC_T rtc_data ;
	
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
			case 3:
			p=&mems_emu_data[beforeSAMPLEblock][2][0];
			break;
			default:
			break;
		}
		inter_factor=g_SystemParam_Config.floatadc[ii]*g_SystemParam_Config.floatscale[ii]*1500.0f/g_SystemParam_Config.floatrange[ii];
		
		for(uint32_t i=0;i<g_SystemParam_Config.channel_freq[ii];i++) //*config.ADtime
		{
			yy = *p;
			p ++;
			sendperioddata = yy * inter_factor;//(int16_t)(yy*Parameter.ReciprocalofRange[ii]);

			PeriodWaveToSend[wpp + 14] = sendperioddata;
			PeriodWaveToSend[wpp + 15] = sendperioddata >>8;
			checksum += (PeriodWaveToSend[wpp + 14] + PeriodWaveToSend[wpp + 15]);			 
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
				for(uint32_t ii=1;ii<14;ii++)
					checksum+=PeriodWaveToSend[ii];  //adch是从1开始的
				
				PeriodWaveToSend[14+g_SystemParam_Param.periodboardpoints]=checksum;  //2,3????????482??
				PeriodWaveToSend[15+g_SystemParam_Param.periodboardpoints]=0x7e; 
				packege_flag++;
				BSP_ESP32_TX_Enqueue(PeriodWaveToSend,g_SystemParam_Param.periodboardpoints+16);	
				wpp=0;
				checksum=0;
				RTOS_Delay_ms(2);
			}	 
		}
	}


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

