/**
 **************************************************************************************************
 * @file        app_conf_net.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_conf_net.h"
#include "stm32_bsp_conf.h"
#include "FreeRTOS.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
 
#include "clog.h"
#include "lnprotocol_std.h"
#include "app_conf.h"
#include "system_param.h"
#include "version.h"
#include "bsp_esp32.h"

#include "stm32l4_bsp_iap.h"
/**
 * @addtogroup    app_conf_net_Modules 
 * @{  
 */

/**
 * @defgroup      app_conf_net_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_net_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_net_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_net_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_net_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_net_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_net_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void app_confnet_esp32_status(uint8_t * value_buf , uint16_t value_len);
static void app_confnet_receive_beacon(uint8_t * buf , uint16_t len);
/**
 * @}
 */

/**
 * @defgroup      app_conf_net_Functions 
 * @brief         
 * @{  
 */
 
void APP_ConfNet_Process(uint8_t * buf , uint16_t len)   // deal with the cmd
{
	uint8_t  * conf_type = 0;
	uint16_t value_len = 0;
	
	conf_type = &buf[1];
	value_len = buf[2] + buf[3] * 256;
	
	DEBUG("NET Conf Type is 0x%02X\r\n" , *conf_type);
	
	switch(*conf_type)
	{
		case LN_P_ESP32_STATUS	: app_confnet_esp32_status(conf_type + 3, value_len);break;
		case LN_P_RECEIVE_BEACON: app_confnet_receive_beacon(buf , len);break;
		case LN_P_R_IAP_ERASE	: BSP_IAP_Erase_Cmd(conf_type + 3 , value_len);break;
		case LN_P_R_IAP_DATA 	: BSP_IAP_RevData(conf_type + 3 , value_len); break;
		default:
		{
			DEBUG("\r\n");
		}break;
	}
}


static void app_confnet_receive_beacon(uint8_t * buf , uint16_t len)
{
	DEBUG("app_confnet_receive_beacon\r\n");
	BSP_ESP32_TX_Enqueue(buf,  len);	
}

static void app_confnet_esp32_status(uint8_t * value_buf , uint16_t value_len)  // enter value buf things
{
	if(value_len == 1)
	{
		switch(value_buf[0])
		{
			case ESP32_READY: 
			{
				DEBUG("ESP32_READY\r\n");
				ESP32_AddCMD(ESP32_READY_TO_CONNECT);
				
			}break;
			case ESP32_CONNECTED: 
			{
				DEBUG("ESP32_CONNECTED\r\n");
				ESP32_AddCMD(ESP32_UP_STATUS_TO_CONNECTED);
				
			}break;
			case ESP32_DISCONNECTED: 
			{
				DEBUG("ESP32_DISCONNECTED\r\n");
				ESP32_AddCMD(ESP32_POWER_REST);
				
			}break;
			default : DEBUG("ESP32_STATUS is Err\r\n");break;
		}
		
	}
	else
	{
		DEBUG("CONF_NET value len is Err\r\n");
	}
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




void APP_Report_CharacterValue(void )
{
	uint8_t * sendbuf = 0;
	
	
	
	sendbuf = pvPortMalloc(300); //vPortFree()
	
	
	//uint32_t empty_Acceleration_ADCHS=0;   //未发送通道
	RTC_T rtc_data ;
	rtc_data = BSP_RTC_Get();
	
	sendbuf[0]=LNPROTOCOL_STD_HEAD;
	sendbuf[1]=LN_P_R_CHARACTER_VALUE;
	uint32_t 	iii=0;
	uint8_t * floatdata;
	sendbuf[4]=rtc_data.Year;
	sendbuf[5]=rtc_data.Year>>8;
	sendbuf[6]=rtc_data.Mon;
	sendbuf[7]=rtc_data.Day; //时间用32位表示
	sendbuf[8]=rtc_data.Hour;
	sendbuf[9]=rtc_data.Min;
	sendbuf[10]=rtc_data.Sec; //时间用32位表示

	//rule_check();	
	
	for(uint32_t ii = 0 ; ii < g_SystemParam_Param.acceleration_adchs ; ii ++)
	{
		floatdata=(uint8_t *)&g_SystemParam_Param.EffectiveValue[ii];//[0];
		sendbuf[11+25*iii]=*floatdata;
		sendbuf[12+25*iii]=*(floatdata+1);
		sendbuf[13+25*iii]=*(floatdata+2);
		sendbuf[14+25*iii]=*(floatdata+3);
		sendbuf[15+25*iii]=0; //5个参数		
		
		floatdata=(uint8_t *)&g_SystemParam_Param.Vrms[ii];
		sendbuf[16+25*iii]=*floatdata;
		sendbuf[17+25*iii]=*(floatdata+1);
		sendbuf[18+25*iii]=*(floatdata+2);
		sendbuf[19+25*iii]=*(floatdata+3);
		sendbuf[20+25*iii]=0;
		
		
		
		floatdata=(uint8_t *)&g_SystemParam_Param.Drms[ii];
		sendbuf[21+25*iii]=*floatdata;
		sendbuf[22+25*iii]=*(floatdata+1);
		sendbuf[23+25*iii]=*(floatdata+2);
		sendbuf[24+25*iii]=*(floatdata+3);
		sendbuf[25+25*iii]=0;
		
		
			
		floatdata=(uint8_t *)&g_SystemParam_Param.KurtosisIndex[ii];
		sendbuf[26+25*iii]=*floatdata;
		sendbuf[27+25*iii]=*(floatdata+1);
		sendbuf[28+25*iii]=*(floatdata+2);
		sendbuf[29+25*iii]=*(floatdata+3);
		sendbuf[30+25*iii]=0;
		
	
			
		floatdata=(uint8_t *)&g_SystemParam_Param.Envelop[ii];
		sendbuf[31+25*iii]=*floatdata;
		sendbuf[32+25*iii]=*(floatdata+1);
		sendbuf[33+25*iii]=*(floatdata+2);
		sendbuf[34+25*iii]=*(floatdata+3);
		sendbuf[35+25*iii]=0;
		iii++;
	} 
	iii--;
	

	floatdata=(uint8_t *)&g_SystemParam_Param.pdate;
	sendbuf[36+25*2]=*floatdata;
	sendbuf[37+25*2]=*(floatdata+1);
	sendbuf[38+25*2]=*(floatdata+2);
	sendbuf[39+25*2]=*(floatdata+3);
	sendbuf[40+25*2]=0;

	floatdata=(uint8_t *)&g_SystemParam_Config.battery;
	sendbuf[41+25*2]=*floatdata;
	sendbuf[42+25*2]=*(floatdata+1);
	sendbuf[43+25*2]=*(floatdata+2);
	sendbuf[44+25*2]=*(floatdata+3);
	sendbuf[45+25*2]=0;
	
	uint32_t length=85+7;
	sendbuf[2]=(uint8_t)length;
	sendbuf[3]=(uint8_t)(length>>8);
	sendbuf[46+25*2]=0;
	for(uint8_t i=1;i<(46+25*2);i++)
	sendbuf[46+25*2]+=sendbuf[i];
	sendbuf[47+25*2]=0x7e;

	BSP_ESP32_TX_Enqueue(sendbuf,(48+25*2));
	
	vPortFree(sendbuf);
	
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

