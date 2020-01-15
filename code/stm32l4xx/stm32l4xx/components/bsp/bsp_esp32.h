/**
 **************************************************************************************************
 * @file        bsp_esp32.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_ESP32_H_
#define _BSP_ESP32_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_esp32_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_esp32_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_esp32_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_esp32_Exported_Types 
 * @{  
 */

 
typedef struct
{
	uint8_t next_cmd[5];
	uint8_t current_cmd;
	uint8_t in;
	uint8_t out;
	uint8_t count;
	uint8_t size;
}ESP32_Core_struct_t;

typedef enum
{
	ESP32_IDEL 			   = 0,
	ESP32_READY_TO_CONNECT = 1,
	ESP32_POWER_REST 	   = 2,
	ESP32_UP_STATUS_TO_CONNECTED = 3,
	ESP32_BUSY					 = 4,
}ESP32_Core_Cmd_e; 
 
typedef enum
{
	ESP32_READY = 0X01 ,
	ESP32_CONNECTED = 0X02,
	ESP32_DISCONNECTED = 0X03,
}ESP32_Module_status_e;

typedef enum 
{
	ESP32_Send_IDLE = 0x01,
	ESP32_Send_BUSY = 0X02,
}ESP32_DataSend_status_e;

typedef enum
{
	ESP32_MODULE_STATUS = 0X01,
	ESP32_SEND_STATUS   = 0X02,
}ESP32_StatusKind_e;

typedef enum
{
	Len_Is_Short = 1,
	InValid	     = 2,
	
	
}ESP32_Rev_status_e;



typedef struct
{
	ESP32_Module_status_e  Module_status ;
	ESP32_DataSend_status_e DataSend_status;
}ESP32_Inf_t;
/**
 * @}
 */

/**
 * @defgroup      bsp_esp32_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_esp32_Exported_Functions 
 * @{  
 */
void BSP_ESP32_Init(void); 
void BSP_ESP32_Rest(void);  // using rtos delay 1s  
void BSP_ESP32_Power_ON(void);
void BSP_ESP32_Power_OFF(void);
void BSP_ESP32_WriteBytes(uint8_t *buf , uint16_t len);
int8_t BSP_ESP32_SetIP(char * localIP , char * LocalMASK , char * LocalGW ,uint8_t DHCP_Flag);
int8_t BSP_ESP32_SetAP(char * APssid , char * APpassword);
int8_t BSP_ESP32_SetTCPServer(char *TcpServer_IP,char *TcpServer_Port);
uint8_t ESP32_ApplyNetSet(void); // back ip addr

void BSP_ESP32_RevProcess(void);
uint8_t ESP32_GetModule_Status(uint8_t status_kind) ;  // get esp32 module status 
void ESP32_Loop(void);  // esp32 core func
void ESP32_AddCMD(ESP32_Core_Cmd_e cmd);

uint8_t * ESP32_GetWorkSpace(void); // get sendbuf space

void BSP_ESP32_TX_Enqueue(uint8_t * buf, uint16_t len);


uint8_t * BSP_ESP32_TX_Dequeue(uint16_t * len);

void BSP_ESP32_Tx_Task(void);
void BSP_ESP32_TxCheck(void);

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


