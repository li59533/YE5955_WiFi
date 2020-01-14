/**
 **************************************************************************************************
 * @file        system_param.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *             
 **************************************************************************************************
 */
#include "self_def.h"
#include "system_param.h"
#include "stm32_bsp_conf.h"
#include "crc.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    system_param_Modules 
 * @{  
 */

/**
 * @defgroup      system_param_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Variables 
 * @brief         
 * @{  
 */
const SystemParam_Config_t SystemParam_Config_Default = 
{
    .vaildsign = 0xAA55, //	uint16_t vaildsign;
	.baundrate =  1,//uint8_t baundrate;    
	.addr = 1,//uint8_t addr; 
	.SNnumber ={'G',100,0,0,0x31,0x00,0x11,0x00},//0x6275110032120001,//0x6275110032120003,//0x5955125011120002, 03 yec-test 101
	.parity = 0, //uint8_t parity;		// =0 : n,8,1   =1: o,8,1  =2: e,8,1  
	.floatscale = {0.3333f,0.075756f,0.075756f,1,1,1,1,1,1,1,1,1},
	.DisplayMode = 0, //uint8_t DisplayMode;  // ???? = 0 ?? =1 ??
	.interface_type = {TYPE_IEPE,TYPE_IEPE,TYPE_IEPE,TYPE_IEPE,TYPE_NONE,TYPE_IEPE,TYPE_IEPE,TYPE_IEPE,TYPE_IEPE,1,1,1}, //uint8_t interface_type[12]; // 
	.unit = {UNIT_M_S2,UNIT_TEMP,UNIT_M_S2,UNIT_M_S2,UNIT_M_S2,UNIT_M_S2,1,1,1,1,1,1},//uint8_t unit[12];  // 
	.floatrange = {3000,3000,3000,3000,1000,1000,1000,1000,10000,10000,10000,10000},//uint32_t scale[12]; // 
	.floatadjust = {0.0f,0.0f,0.0f,0.0f,1250.f,0,0,0,8192,8192,8192,8192},//uint32_t adjust[12]; // 
	//	{0,1,2,~0,~0,~0,~0,~0,3,4,5,6},//uint16_t interface_addr[12]; // modbus  
	.alarmgate = {100,100,100,100,100,100},//	float alarmgate[12]; // float 
	.floatadc =  {1.01f,1.0f,1.0f,1.0f,1.0f,1.0f},
	.means = 0,//uint8_t means	;// 
	.means_times =  1,//uint16_t means_times; // 
	.freq = 20000,//uint16_t freq;  //  Hz
	.avr_count = 4096,//uint16_t avr_count;
	.reflash = 2, // uint8_t reflash; // 
	.din_addr = ~0, //	uint16_t din_addr;  // 
	.dout_addr = ~0, // uint16_t dout_addr; //  
	.force_gate =  300,  // 
	.force_backlash =  30, // uint32_t force_gate,force_backlash,   // 
	.max_addr0 = ~0,
	.max_addr1 = ~0, 	//	uint16_t max_addr0,max_addr1; 
	.vlpsseconds = 300,
	.vlprseconds = 300,
	.runseconds =  300,
	.pga = 0x4a,                          //PGA
	.workcycleseconds =  30,              
	.fangda = 0x0100,                     
	.boardset = 0x11,                     // 
	.ADtime = 0x01,                       //AD
	.ADfrequence = 8192,                  //AD
	.alarmminutetime = 0x58B6A4C3,        //
	.FLASH_WRADDR = 0,                    //
	.DataToBoardMode = PARAMETERMODE,
	.DataToSendChannel =  0x1F,           //
	.DHCP = 1, //DHCP
	.APssid =   "TP-LINK_2.4G_CB10",//"TP-LINK_FF18E4",//"Tenda_4F7AC0",//"yec-test",//"wifi-sensor",//"Tenda_1E6760",//"TP-LINK-SCZZB",//"yec-test",//"wifi-sensor",//"TP-LINK-sczzb2",//"hold-704",//"wifi-test1",//"yec-test",//"wifi-test",//"yec-test",//"zl_sensor",/////"yec-test",//"test3",//"qiangang2", //"qiangang1", //"qiangang1", /////
	.APpassword = "",//"",//"china-yec",//"",//"wifi-sensor",//"18051061462",//"wifi-test",//"zl_sensor",///"china-yec",//"",////"",//"zl_sensor",/"lft13852578307",//"",//"",//"123456789",//"china-yec.com",// //
	.TcpServer_IP = "192.168.1.233",// "218.91.149.114",//"192.168.0.234",//"192.168.0.233",//"192.168.0.233",//"192.168.0.141",// "192.168.0.112",//
	.TcpServer_Port = "8712", //
	.LocalIP = "192.168.99.45",  //LocalIP
	.LocalGATEWAY =  "192.168.99.1",  //LocalGATEWAY
	.LocalMASK = "255.255.255.0",	//LocalMASK
	.PeriodTransimissonCounter = 1,
	.PeriodTransimissonStatus = 1,
	.ParameterTransimissonStatus = 1,
	.RequirePeriodChannel = 0x1f,
	.RESETTIME = 1,
	.Enable_active_beacon = 0,  //
	.Iap_flag = 0,
	.Iap_datalength = 0,
	.channel_freq = {16384,8192,8192,8192,51200,51200,51200,51200,51200,51200,12800,12800},
	.BeaconInterval = 5, //
	.server_address = "www.av.com",
	.DNS_SERVERIP = "192.168.120.120",
	.Lowpower_Mode = 0,  //Lowpower_Mode 1
	.scan_channel = 6,  //scan_channel
	.Waitforsleeptime = 12, //Waitforsleeptime
	.WaitforIEPEtime = 2,//WaitforIEPEtime
	.filterMean = { 0.25f,0.25f,0.25f,0.25f,0.25f,0.25f},
	.WaitToPeriodTransmissonCounter = 0,//WaitToPeriodTransmissonCounter
	.Alarm_value_junyue = 	{10000.0f,10000.0f,10000.0f,10000.0f,10000.0f,10000.0f,10000.0f,10000.0f,
		10000.0f,10000.0f,10000.0f,10000.0f,10000.0f,10000.0f,10000.0f,10000.0f,10000.0f,10000.0f,
	 10000.0f,10000.0f},
	.battery = 100 ,
	.workcycleseconds_inAlarmStatue = 20,
	.tempCompensation = -5 ,
	//.Alarm_source_number = ,
	//.Alarm_source = 
	.sleep_time = 0, // default 1 min 
};

/**
 * @}
 */

/**
 * @defgroup      system_param_Public_Variables 
 * @brief         
 * @{  
 */
SystemParam_Config_t g_SystemParam_Config;
SystemParam_Param_t g_SystemParam_Param;
/**
 * @}
 */

/**
 * @defgroup      system_param_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Functions 
 * @brief         
 * @{  
 */
void SystemParam_Init(void)
{
	DEBUG("SystemParam_Init\r\n");
    SystemParam_Read();
	g_SystemParam_Param.sample_adch = 8;
	g_SystemParam_Param.ad7682_adchs = 0x04;
	g_SystemParam_Param.acceleration_adchs = 0x03;
	g_SystemParam_Param.temp_adchs = 1;
	g_SystemParam_Param.samplepoints = 128;
	g_SystemParam_Param.boardpoints = g_SystemParam_Param.samplepoints * g_SystemParam_Param.ad7682_adchs * sizeof(int16_t);
	g_SystemParam_Param.periodboardpoints = g_SystemParam_Param.samplepoints * sizeof(int16_t) * 2;
	
}

int16_t SystemParam_Read(void)
{
	BSP_Flash_ReadBytes((uint8_t *)&g_SystemParam_Config , SYSTEMPARAM_SAVE_FIRST_ADDR , sizeof(g_SystemParam_Config));
	if(CRC16_Modbus((uint8_t *)&g_SystemParam_Config , sizeof(g_SystemParam_Config)) != 0)
	{
		BSP_Flash_ReadBytes((uint8_t *)&g_SystemParam_Config , SYSTEMPARAM_SAVE_SECOND_ADDR , sizeof(g_SystemParam_Config));
		if(CRC16_Modbus((uint8_t *)&g_SystemParam_Config , sizeof(g_SystemParam_Config)) != 0)
		{
			memcpy((uint8_t *)&g_SystemParam_Config ,(uint8_t *)&SystemParam_Config_Default,sizeof(g_SystemParam_Config) );
			SystemParam_Save();
		}
	}
    return 0;
}

void SystemParam_Save(void)
{
	g_SystemParam_Config.crc = CRC16_Modbus((uint8_t *)&g_SystemParam_Config , sizeof(g_SystemParam_Config) - sizeof(g_SystemParam_Config.crc));
	BSP_Flash_WriteBytes(SYSTEMPARAM_SAVE_FIRST_ADDR , (uint8_t *)&g_SystemParam_Config , sizeof(g_SystemParam_Config));
	BSP_Flash_WriteBytes(SYSTEMPARAM_SAVE_SECOND_ADDR , (uint8_t *)&g_SystemParam_Config , sizeof(g_SystemParam_Config));
	DEBUG("SystemParam_Save\r\n");
}

void SystemParam_Reset(void)
{
}

void SystemParam_Apply(void)
{

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

