/**
 **************************************************************************************************
 * @file        bsp_lm78.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "stm32_bsp_conf.h"
#include "bsp_lm78.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_lm78_port.h"
#include "clog.h"
#include "bsp_queue.h"
#include "net_task.h"
#include "hal_task.h"
#include "app_power.h"
#include "app_conf.h"
#include "rtos_tools.h"
/**
 * @addtogroup    bsp_lm78_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_lm78_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lm78_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
	uint8_t status_buf[3] ; 
	uint8_t in;
	uint8_t out;
	uint8_t count;
}LM78_StatusQueue_t;

LM78_StatusQueue_t LM78_StatusQueue = 
{
	.in = 0 ,
	.out = 0,
	.count = 0,
};

#define BSP_LM78_SENDBUF_LEN  	200

typedef struct 
{
	uint8_t sendbuf[BSP_LM78_SENDBUF_LEN];
	uint16_t len;
}LM78_Sendbuf_t;


typedef struct 
{
	LM78_Sendbuf_t sendbuf[5];
	uint8_t in ;
	uint8_t out;
	uint8_t count ;
	uint8_t size ;
}LM78_SendQueue_t;

LM78_SendQueue_t LM78_SendQueue = 
{
	.in = 0,
	.out = 0,
	.count = 0,
	.size = sizeof(LM78_SendQueue.sendbuf) / sizeof( LM78_SendQueue.sendbuf[0]),
};

LM78_Sendbuf_t lm78_sendbuf = 
{
	.len = 0,
};

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lm78_Private_Variables 
 * @brief         
 * @{  
 */
typedef enum
{
	LM78_STATUS_IDLE = 0,
	LM78_STATUS_AT_REQ ,
	LM78_STATUS_AT_RESP ,
	LM78_STATUS_GET_VERSION_REQ ,
	LM78_STATUS_GET_VERSION_RESP ,
	LM78_STATUS_GET_ADDR_REQ ,
	LM78_STATUS_GET_ADDR_RESP ,
	LM78_STATUS_SEND_BYTES_REQ ,
	LM78_STATUS_SEND_BYTES_RESP ,
	LM78_STATUS_REVB_REQ,
	LM78_STATUS_REVB_RESP,
	LM78_STATUS_REST ,
	LM78_STATUS_OK ,
}LM78_AT_CMD_e;

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lm78_Public_Variables 
 * @brief         
 * @{  
 */

const char LM78_AT_AT[] 				= "\r\nAT\r\n";
const char LM78_AT_GetVersion[] 		= "\r\nAT+VER=?\r\n";
const char LM78_AT_GetAddr[] 			= "\r\nAT+DADDR=?\r\n";
const char LM78_AT_SendOriginalData[] 	= "\r\nAT+SENDB=2:";
const char LM78_AT_SendstrData[] 		= "\r\nAT+SEND=2:";
const char LM78_AT_Rest[] 				= "\r\nATZ\r\n";
const char LM78_AT_REVB[]				= "\r\nAT+RECVB=?\r\n";


/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void bsp_lm78_statusEnqueue(uint8_t status );
static uint8_t bsp_lm78_statusDequeue(void);
static uint8_t bsp_lm78_getqueueCount(void);
static uint8_t bsp_lm78_getCurStatus(void);
static void bsp_lm78_statusQueueInit(void);
/**s
 * @}
 */


/**
 * @defgroup      bsp_lm78_Functions 
 * @brief         
 * @{  
 */
void BSP_LM78_Init(void)
{
	BSP_LM78_Port_Init();
	bsp_lm78_statusEnqueue(LM78_STATUS_AT_REQ);
}



void BSP_LM78_RespProcess(void)
{
	uint8_t * rev_buf = 0;
	uint8_t len = 0;
	rev_buf = BSP_Queue_Dequeue( BSP_QUEUE_UART1_REV , &len);
	DEBUG("BSP_Queue_Dequeue Count:%d\r\n",BSP_Queue_GetCount(BSP_QUEUE_UART1_REV));
	
	switch(bsp_lm78_getCurStatus())
	{
		case LM78_STATUS_AT_REQ:
		{
			if(strstr((const char *)rev_buf,"OK") != 0 )
			{
				bsp_lm78_statusDequeue();
				if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
				{
					Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
				}
				else
				{
					bsp_lm78_statusEnqueue(LM78_STATUS_GET_VERSION_REQ);
				}
			}
			else
			{
				if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
				{
					Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
				}
			}
			DEBUG("AT_RESP:%s\r\n",rev_buf);
		}
		break;	
		case LM78_STATUS_GET_VERSION_REQ :
		{
			if(strstr((const char *)rev_buf,"OK") != 0 )
			{
				bsp_lm78_statusDequeue();
				if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
				{
					Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
				}
				else
				{
					bsp_lm78_statusEnqueue(LM78_STATUS_GET_ADDR_REQ);
				}				
				
				
			}
			else
			{
				if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
				{
					Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
				}
			}
			DEBUG("AT_VERSION RESP:%s\r\n",rev_buf);			
		}
		break;
		case LM78_STATUS_GET_ADDR_REQ:
		{
			if(strstr((const char *)rev_buf,"OK") != 0 )
			{
				bsp_lm78_statusDequeue();
				if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
				{
					Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
				}
				else
				{
					bsp_lm78_statusEnqueue(LM78_STATUS_OK);
				
				}				
				
				
			}
			else
			{
				if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
				{
					Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
				}				
			}
			DEBUG("AT ADDR RESP:%s\r\n",rev_buf);				
		}
		break;
		case LM78_STATUS_SEND_BYTES_REQ:
		{
			if(strstr((const char *)rev_buf,"OK") != 0 )
			{
				bsp_lm78_statusDequeue();
				
				if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
				{
					Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
				}
				else
				{
					RTOS_Delay_ms(1000);
					bsp_lm78_statusEnqueue(LM78_STATUS_REVB_REQ);
					Hal_Task_Event_Start(HAL_TASK_STANDBY_EVENT, EVENT_FROM_TASK);
				}

			}
			else
			{
				if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
				{
					Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
				}
				else
				{
					bsp_lm78_statusDequeue();
				bsp_lm78_statusEnqueue(LM78_STATUS_REST);
				}
				//bsp_lm78_statusEnqueue(LM78_STATUS_OK);
			}
			DEBUG("AT SEND B RESP:%s len :%d\r\n",rev_buf , len);				
		}
		break;
		case LM78_STATUS_REVB_REQ:
		{
			bsp_lm78_statusDequeue();
			
			char *conf_buf_head = 0;
			conf_buf_head = strstr((const char *)rev_buf,":7e");
			DEBUG("LM78_STATUS_REVB_REQ:%s len :%d\r\n",rev_buf , len);	
			if(conf_buf_head != NULL)
			{
				DEBUG("ENTER Lora CONF\r\n");
				APP_Conf_FromLora((uint8_t *)(conf_buf_head + 1 ), strlen((const char *)(conf_buf_head + 1)) );
				
				if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
				{
					Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
				}
				else
				{
					bsp_lm78_statusEnqueue(LM78_STATUS_OK);
				}
				
				
			}
			else
			{
				if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
				{
					Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
				}
				else
				{
					RTOS_Delay_ms(200);
					bsp_lm78_statusEnqueue(LM78_STATUS_REVB_REQ);
				}
				
			}
		}
		break;
		case LM78_STATUS_OK:
		{
			if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
			{
				Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
			}
			DEBUG("LM78_STATUS_OK:%s len :%d\r\n",rev_buf , len);		
		}
		break;
		default :break;
	}
	
	if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
	{
		Net_Task_Event_Start(NET_TASK_AT_PROCESS_EVENT, EVENT_FROM_TASK);
	}
}

int8_t BSP_LM78_StartSend(uint8_t *buf, uint16_t len)
{	
	memcpy(lm78_sendbuf.sendbuf , LM78_AT_SendOriginalData , sizeof(LM78_AT_SendOriginalData) );
	memcpy(lm78_sendbuf.sendbuf + sizeof(LM78_AT_SendOriginalData) - 1, buf , len);
	*(lm78_sendbuf.sendbuf + sizeof(LM78_AT_SendOriginalData) - 1 + len )= '\r';
	*(lm78_sendbuf.sendbuf + sizeof(LM78_AT_SendOriginalData) - 1 + len  + 1) = '\n';
	*(lm78_sendbuf.sendbuf + sizeof(LM78_AT_SendOriginalData) - 1 + len  + 2) = 0;

	lm78_sendbuf.len =  sizeof(LM78_AT_SendOriginalData) - 1 + len  + 2 ;//strlen((const char *)lm78_sendbuf.sendbuf);
	bsp_lm78_statusEnqueue(LM78_STATUS_SEND_BYTES_REQ);
	
	return 0 ;
}

void BSP_LM78_ReqProcess(void)
{
	static uint8_t status = 0;
	if(bsp_lm78_getqueueCount() > 0)
	{
		if(status == bsp_lm78_getCurStatus())
		{
			status = 0; 
			bsp_lm78_statusDequeue();
			Net_Task_Event_Start(NET_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
			return;
		}
		else
		{
			status = bsp_lm78_getCurStatus();
		}
		
		DEBUG("BSP_LM78_ReqProcess Status :%d\r\n",status);
		
		switch(status )
		{
			case LM78_STATUS_IDLE:
			{
				bsp_lm78_statusDequeue();
				DEBUG("REQ IDLE\r\n");
			}
			break;
			case LM78_STATUS_AT_REQ:
			{
				BSP_LM78_SendBytes((uint8_t *)LM78_AT_AT,strlen(LM78_AT_AT));
				DEBUG("REQ AT\r\n");
			}
			break;
			case LM78_STATUS_GET_VERSION_REQ :
			{
				BSP_LM78_SendBytes((uint8_t *)LM78_AT_GetVersion,strlen(LM78_AT_GetVersion));
				DEBUG("REQ AT+VER=?\r\n");
			}
			break;
			case LM78_STATUS_GET_ADDR_REQ:
			{
				BSP_LM78_SendBytes((uint8_t *)LM78_AT_GetAddr,strlen(LM78_AT_GetAddr));
				DEBUG("REQ AT+DADDR=?\r\n");
			}
			break;
			case LM78_STATUS_SEND_BYTES_REQ:
			{
//				char test_lorabuf[] = "\r\nAT+SENDB=2:12345678123456781234567812345678123456781234567812345678123456781234567812341234567812345678123456178123FF\r\n";
//				BSP_LM78_SendBytes((uint8_t *)test_lorabuf,sizeof(test_lorabuf));
		
				
				BSP_LM78_SendBytes(lm78_sendbuf.sendbuf , lm78_sendbuf.len );
				DEBUG("REQ AT+SENDB=%s %d\r\n", lm78_sendbuf.sendbuf ,lm78_sendbuf.len);
			}
			break;
			case LM78_STATUS_REST:
			{
				BSP_LM78_SendBytes((uint8_t *)LM78_AT_Rest,strlen(LM78_AT_Rest));
				bsp_lm78_statusQueueInit();
				BSP_Queue_Init(BSP_QUEUE_UART1_REV);
				DEBUG("REQ ATZ\r\n");
			}
			break;
			case LM78_STATUS_REVB_REQ:
			{
				status = 0;
				BSP_LM78_SendBytes((uint8_t *)LM78_AT_REVB,strlen(LM78_AT_REVB));
				DEBUG("REQ AT+RECVB=?\r\n");
			}
			break;
			case LM78_STATUS_OK:
			{
				//APP_Power_LM78_OFF();
				bsp_lm78_statusDequeue();
				//bsp_lm78_statusEnqueue(LM78_STATUS_OK);
			}
			
			default :break;
		}
	}
	else
	{
		//bsp_lm78_statusEnqueue(LM78_STATUS_AT_REQ);
		//BSP_LM78_SendBytes((uint8_t *)LM78_AT_AT,sizeof(LM78_AT_AT));
		//DEBUG("REQ AT\r\n");
	}
}



static void bsp_lm78_statusQueueInit(void)
{
	LM78_StatusQueue.count = 0;
	LM78_StatusQueue.in = 0;
	LM78_StatusQueue.out = 0;
}

static void bsp_lm78_statusEnqueue(uint8_t status )
{
	LM78_StatusQueue.status_buf[LM78_StatusQueue.in] = status;
	LM78_StatusQueue.in ++ ;
	LM78_StatusQueue.count ++;
	LM78_StatusQueue.in %= (sizeof(LM78_StatusQueue.status_buf)/sizeof(LM78_StatusQueue.status_buf[0]));
	
	Net_Task_Event_Start(NET_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
}

static uint8_t bsp_lm78_getCurStatus(void)
{
	if(bsp_lm78_getqueueCount > 0)
	{
		return LM78_StatusQueue.status_buf[LM78_StatusQueue.out];
	}
	else
	{
		return LM78_STATUS_IDLE;
	}
	
}
static uint8_t bsp_lm78_statusDequeue(void)
{
	uint8_t status = 0;
	if(LM78_StatusQueue.count > 0 )
	{
		status = LM78_StatusQueue.status_buf[LM78_StatusQueue.out];
		LM78_StatusQueue.count -- ;
		LM78_StatusQueue.out ++;
		LM78_StatusQueue.out %= (sizeof(LM78_StatusQueue.status_buf)/sizeof(LM78_StatusQueue.status_buf[0]));
	}
	else
	{
		status = 0;
	}
	return status;
}

static uint8_t bsp_lm78_getqueueCount(void)
{
	return LM78_StatusQueue.count;
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

