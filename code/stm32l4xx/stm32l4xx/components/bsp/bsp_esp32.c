/**
 **************************************************************************************************
 * @file        bsp_esp32.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "bsp_esp32.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "stm32_bsp_conf.h"
#include "rtos_tools.h"
#include "app_power.h"
#include "bsp_queue.h"
#include "lnprotocol_std.h"
#include "app_conf_net.h"
#include "net_task.h"

#include "app_datasend.h"
/**
 * @addtogroup    bsp_esp32_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_esp32_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_esp32_Macros_Defines 
 * @brief         
 * @{  
 */
#define      macUser_Esp32_LocalID                        "192.168.100.88"                //连不上去时，备用的就是这个
#define      macUser_Esp32_LocalGATAWAY                   "192.168.100.1"           
#define      macUser_Esp32_LocalMASK                      "255.255.255.0"           

#define      macUser_Esp32_ApSsid                         "yec-test"   // "Tenda_4F7AC0"//"yec-test"                //要连接的热点的名称
#define      macUser_Esp32_ApPwd                          ""           //要连接的热点的密钥

#define      macUser_Esp32_TcpServer_IP                   "192.168.100.233"//"192.168.0.112"// //     //要连接的服务器的 IP
#define      macUser_Esp32_TcpServer_Port                 "8712"  			//"8712"//             //要连接的服务器的端口

/**
 * @}
 */
 
/**
 * @defgroup      bsp_esp32_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_esp32_Private_Types
 * @brief         
 * @{  
 */
 
#define BSP_ESP32_TX_BUF_LEN   600 
typedef struct
{
	uint8_t buf[BSP_ESP32_TX_BUF_LEN];
	uint16_t len;
}BSP_ESP32_Txbuf_t;

typedef struct
{
	BSP_ESP32_Txbuf_t txbuf[100];
	uint8_t in;
	uint8_t out;
	uint8_t count;
	uint8_t size;
}BSP_ESP32_TxQueue_t;
/**
 * @}
 */
 
/**
 * @defgroup      bsp_esp32_Private_Variables 
 * @brief         
 * @{  
 */
#define BSP_ESP32_WORKSPACE_LEN  1600
uint8_t BSP_ESP32_workspace[BSP_ESP32_WORKSPACE_LEN] = { 0 };
BSP_ESP32_TxQueue_t BSP_ESP32_TxQueue = 
{
	.in = 0,
	.out = 0,
	.count = 0,
	.size = 100,
};


static ESP32_Inf_t ESP32_Inf = 
{
	.Module_status = ESP32_DISCONNECTED,
	.DataSend_status = ESP32_Send_IDLE,
};
/**
 * @}
 */
 
/**
 * @defgroup      bsp_esp32_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_esp32_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static int8_t bsp_esp32_rev(uint8_t * buf , uint16_t len);
static void esp32_core_cmd_init(void);
static void esp32_setmodule_status(uint8_t status_kind , uint8_t status); // set esp32 module statusss
static void BSP_ESP32_TX_Queue_Init(void);
/**
 * @}
 */

/**
 * @defgroup      bsp_esp32_Functions 
 * @brief         
 * @{  
 */
void BSP_ESP32_Init(void)
{
	GPIO_InitTypeDef gpio_init_structure;

	__HAL_RCC_GPIOD_CLK_ENABLE();

	gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_structure.Pull = GPIO_PULLDOWN;
	gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	
	gpio_init_structure.Pin = GPIO_PIN_11;
	HAL_GPIO_Init(GPIOD, &gpio_init_structure);
	
	BSP_Usart_Init( BSP_UART_1);
	//BSP_Usart_RevDMA_Conf(BSP_UART_1);
	BSP_Usart_RevOneByteIT_Conf(BSP_UART_1);
	
	BSP_ESP32_Rest();
	
	esp32_core_cmd_init();
}


void BSP_ESP32_Rest(void)  // using rtos delay 1s 
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11,GPIO_PIN_SET);
	RTOS_Delay_ms(1000);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11,GPIO_PIN_RESET);
}

void BSP_ESP32_Power_ON(void)
{
	APP_Power_Net_ON();
}

void BSP_ESP32_Power_OFF(void)
{
	APP_Power_Net_OFF();
}


void BSP_ESP32_RevProcess(void)
{
	uint8_t * buf_ptr = 0;
	uint8_t len = 0;
	if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
	{
		buf_ptr = BSP_Queue_Dequeue(BSP_QUEUE_UART1_REV, &len);
		bsp_esp32_rev( buf_ptr , len);
		if(BSP_Queue_GetCount(BSP_QUEUE_UART1_REV) > 0)
		{
			Net_Task_Event_Start(NET_TASK_REV_EVENT, EVENT_FROM_TASK);
		}
		
	}
}

void BSP_ESP32_WriteBytes(uint8_t *buf , uint16_t len)
{
	BSP_Usart_WriteBytes_DMA(BSP_UART_1 , buf , len);
}

typedef struct
{
	uint8_t buf[300];
	uint8_t len;
}rev_data_t;

rev_data_t break_buf = { 0 };
rev_data_t temp_buf = { 0 };
rev_data_t full_buf = { 0 };


static int8_t bsp_esp32_rev(uint8_t * buf , uint16_t len)
{
	uint16_t i = 0; 
	
	memcpy( &temp_buf.buf[temp_buf.len] , buf, len );
	temp_buf.len += len;
	while(1)
	{
		if(temp_buf.buf[i] == LNPROTOCOL_STD_HEAD)   // check head 
		{
			if(temp_buf.buf[i + 1] == LNPROTOCOL_STD_HEAD)
			{
				i++;
				temp_buf.len--;
			}
			memcpy( &temp_buf.buf[0] , &temp_buf.buf[i], temp_buf.len); // offset
			i = 0;
			
//			if(temp_buf.len < 4)
//			{
//				break;
//			}
//			else
			{
				if((temp_buf.buf[ 2] + temp_buf.buf[3] * 256) == (temp_buf.len - 6) ) // check inf len 
				{
					if(LNprotocol_STD_Checksum( &temp_buf.buf[0] , temp_buf.len) == 1) // check sum
					{
						APP_ConfNet_Process(&temp_buf.buf[0] , temp_buf.len);   // deal with the cmd
					}					
					temp_buf.len = 0;
				}
				else
				{
					if((temp_buf.buf[ 2] + temp_buf.buf[3] * 256) > (temp_buf.len - 6) && (temp_buf.buf[ 2] + temp_buf.buf[3] * 256) < 300)
					{
						break;
					}
					else if((temp_buf.buf[ 2] + temp_buf.buf[3] * 256) < (temp_buf.len - 6))
					{
						memcpy( &full_buf.buf[0] , &temp_buf.buf[0] , (temp_buf.buf[ 2] + temp_buf.buf[3] * 256) + 6 );
						full_buf.len = (temp_buf.buf[ 2] + temp_buf.buf[3] * 256) + 6;
						
						temp_buf.len = temp_buf.len - (temp_buf.buf[ 2] + temp_buf.buf[3] * 256) - 6;
						memcpy( &temp_buf.buf[0] , &temp_buf.buf[(temp_buf.buf[ 2] + temp_buf.buf[3] * 256) + 6], temp_buf.len); // offset
						
						if(LNprotocol_STD_Checksum( &full_buf.buf[0] , full_buf.len) == 1) // check sum
						{
							APP_ConfNet_Process(&full_buf.buf[0] , full_buf.len);   // deal with the cmd
						}
					}
					else
					{
						temp_buf.len = 0;
					}
				}
			}
			
		}
		else
		{
			i ++;
			temp_buf.len --;

		}
		
		if(temp_buf.len <= 0)
		{
			break;
		}		
		
	}

	return 0;
}

int8_t BSP_ESP32_SetIP(char * localIP , char * LocalMASK , char * LocalGW ,uint8_t DHCP_Flag)
{
	uint8_t localIPlength = 0;
	uint8_t LocalMASKlength = 0;
	uint8_t LocalGATEWAYlength = 0;
	uint16_t sendbuf_len = 0;
	
	localIPlength = strlen(localIP);
	LocalMASKlength = strlen(LocalMASK);
	LocalGATEWAYlength = strlen(LocalGW);
	
	sendbuf_len = 15 + localIPlength + LocalMASKlength + LocalGATEWAYlength;	
	
	 
	BSP_ESP32_workspace[0] = LNPROTOCOL_STD_HEAD;
	BSP_ESP32_workspace[1] = LN_P_ESP32_SET_IP;   //T
	BSP_ESP32_workspace[2] = sendbuf_len - 6;
	BSP_ESP32_workspace[3] = (sendbuf_len-6) >> 8;   //L
	BSP_ESP32_workspace[4] = 0X00;   //V_IP
	BSP_ESP32_workspace[5] = localIPlength;

	for(uint8_t i = 0 ; i < localIPlength ; i ++)
	{
		BSP_ESP32_workspace[6+i]=localIP[i];
	}

	BSP_ESP32_workspace[6+localIPlength]=0X01;   //V_MASK
	BSP_ESP32_workspace[7+localIPlength]=LocalMASKlength;

	for(uint8_t i=0;i<LocalMASKlength;i++)
	{
		BSP_ESP32_workspace[8+localIPlength+i]=LocalMASK[i];	
	}


	BSP_ESP32_workspace[8+localIPlength+LocalMASKlength]=0X02;   //V_GATEWAY
	BSP_ESP32_workspace[9+localIPlength+LocalMASKlength]=LocalGATEWAYlength;
	
	for(uint8_t i=0;i<LocalGATEWAYlength;i++)
	{
		BSP_ESP32_workspace[10+localIPlength+LocalMASKlength+i]=LocalGW[i];
	}

	BSP_ESP32_workspace[10+localIPlength + LocalMASKlength + LocalGATEWAYlength]=0X03;
	BSP_ESP32_workspace[11+localIPlength + LocalMASKlength + LocalGATEWAYlength]=0X01;
	BSP_ESP32_workspace[12+localIPlength + LocalMASKlength + LocalGATEWAYlength]=DHCP_Flag;
	BSP_ESP32_workspace[13+localIPlength + LocalMASKlength + LocalGATEWAYlength]=0;
	for(uint8_t i=1;i<(13+localIPlength + LocalMASKlength + LocalGATEWAYlength);i++)
	{
		BSP_ESP32_workspace[13+localIPlength + LocalMASKlength + LocalGATEWAYlength]+=BSP_ESP32_workspace[i];//把AP字符串赋值给config
	}
	BSP_ESP32_workspace[14+localIPlength + LocalMASKlength + LocalGATEWAYlength]=LNPROTOCOL_STD_FOOT;
	sendbuf_len = 15 + localIPlength + LocalMASKlength + LocalGATEWAYlength;
	BSP_ESP32_WriteBytes(BSP_ESP32_workspace,sendbuf_len);

	return 1;	
	
}


int8_t BSP_ESP32_SetAP(char * APssid , char * APpassword)
{
	//这边要判断是否工厂设置
	uint8_t APSSIDlength = strlen(APssid);
	uint8_t APPASSWORDlength = strlen(APpassword);
	uint16_t sendbuf_len = 0;

	sendbuf_len = 10 + APSSIDlength + APPASSWORDlength;
	BSP_ESP32_workspace[0] = LNPROTOCOL_STD_HEAD;
	BSP_ESP32_workspace[1] = LN_P_ESP32_SET_AP;   //T
	BSP_ESP32_workspace[2] = sendbuf_len - 6;
	BSP_ESP32_workspace[3] = (sendbuf_len - 6) >> 8;   //L
	BSP_ESP32_workspace[4] = 0X00;   //V_IP
	BSP_ESP32_workspace[5] = APSSIDlength;
	{
	for(uint8_t i = 0 ; i < APSSIDlength ; i++)
	BSP_ESP32_workspace[ 6 + i]=APssid[i];

	}
	BSP_ESP32_workspace[6 + APSSIDlength] = 0X01;   //V_MASK
	BSP_ESP32_workspace[7 + APSSIDlength] = APPASSWORDlength;
	{
	for(uint8_t i = 0 ; i < APPASSWORDlength ; i++)
	BSP_ESP32_workspace[ 8 + APSSIDlength + i] = APpassword[ i ];

	}
	BSP_ESP32_workspace[ 8 + APSSIDlength + APPASSWORDlength] = 0X00;   //校验和

	for(uint8_t i = 1 ;i < (8 + APSSIDlength + APPASSWORDlength);i++)
	BSP_ESP32_workspace[8 + APSSIDlength + APPASSWORDlength] += BSP_ESP32_workspace[i];//把AP字符串赋值给config
	BSP_ESP32_workspace[9 + APSSIDlength + APPASSWORDlength] = LNPROTOCOL_STD_FOOT;
	sendbuf_len = 10 + APSSIDlength+APPASSWORDlength;
	BSP_ESP32_WriteBytes(BSP_ESP32_workspace , sendbuf_len);

	return 1;	
}

int8_t BSP_ESP32_SetTCPServer(char *TcpServer_IP,char *TcpServer_Port)
{
	uint8_t TcpServer_IPlength = strlen(TcpServer_IP);
	uint8_t TcpServer_Portlength = strlen(TcpServer_Port);
	uint16_t sendbuf_len = 0; 
	
	sendbuf_len = 10 + TcpServer_Portlength + TcpServer_IPlength;
	BSP_ESP32_workspace[0] = LNPROTOCOL_STD_HEAD;
	BSP_ESP32_workspace[1] = LN_P_ESP32_SET_TCPSERVER;   //T
	BSP_ESP32_workspace[2] = sendbuf_len - 6;
	BSP_ESP32_workspace[3] = (sendbuf_len - 6) >> 8;   //L
	BSP_ESP32_workspace[4] = 0X00;   //V_IP
	BSP_ESP32_workspace[5] = TcpServer_IPlength;

	for(uint8_t i = 0;i < TcpServer_IPlength ; i ++)
	{
		BSP_ESP32_workspace[6 + i] = TcpServer_IP[i];
	}

	BSP_ESP32_workspace[6 + TcpServer_IPlength] = 0X01;   //V_MASK
	BSP_ESP32_workspace[7 + TcpServer_IPlength] = TcpServer_Portlength;
	
	for(uint8_t i = 0 ; i < TcpServer_Portlength ; i ++)
	{
		BSP_ESP32_workspace[8 + TcpServer_IPlength +i ] = TcpServer_Port[i];
	}
	
	BSP_ESP32_workspace[8 + TcpServer_IPlength + TcpServer_Portlength] = 0X00;   //校验和

	for(uint8_t i = 1 ; i < (8 + TcpServer_IPlength + TcpServer_Portlength) ; i++)
	{
		BSP_ESP32_workspace[8 + TcpServer_IPlength + TcpServer_Portlength] += BSP_ESP32_workspace[i];//把AP字符串赋值给config
	}
	
	BSP_ESP32_workspace[9 + TcpServer_IPlength + TcpServer_Portlength] = LNPROTOCOL_STD_FOOT;
	sendbuf_len = 10 + TcpServer_IPlength + TcpServer_Portlength;
	BSP_ESP32_WriteBytes(BSP_ESP32_workspace , sendbuf_len);

	return 1;	
}

uint8_t ESP32_ApplyNetSet(void) // back ip addr
{
	uint16_t sendbuf_len = 0;
	BSP_ESP32_workspace[0] = LNPROTOCOL_STD_HEAD;
	BSP_ESP32_workspace[1] = 0xff;
	BSP_ESP32_workspace[2] = 0x00;
	BSP_ESP32_workspace[3] = 0x00;
	BSP_ESP32_workspace[4] = 0xff;
	BSP_ESP32_workspace[5] = LNPROTOCOL_STD_FOOT;
	sendbuf_len = 6;
	BSP_ESP32_WriteBytes(BSP_ESP32_workspace , sendbuf_len);
//	return Esp32_wait_response( "connectserver", NULL, 400);
	return 1;
}


ESP32_Core_struct_t ESP32_Core_struct;

static void esp32_core_cmd_init(void)
{
	memset(ESP32_Core_struct.next_cmd , 0 , sizeof(ESP32_Core_struct.next_cmd));
	ESP32_Core_struct.current_cmd = 0;
	ESP32_Core_struct.in = 0;
	ESP32_Core_struct.out = 0;
	ESP32_Core_struct.count = 0;
	ESP32_Core_struct.size = sizeof(ESP32_Core_struct.next_cmd) / sizeof(ESP32_Core_struct.next_cmd[0]);
}

void ESP32_AddCMD(ESP32_Core_Cmd_e cmd)
{
	ESP32_Core_struct.next_cmd[ESP32_Core_struct.in] = cmd;
	ESP32_Core_struct.in ++;
	ESP32_Core_struct.count ++;
	
	ESP32_Core_struct.in %= ESP32_Core_struct.size;
	
	Net_Task_Event_Start(NET_TASK_LOOP_EVENT, EVENT_FROM_TASK);
}


uint8_t ESP32_GetModule_Status(uint8_t status_kind)   // get esp32 module status 
{
	switch(status_kind)
	{
		case ESP32_MODULE_STATUS: return ESP32_Inf.Module_status;break;
		case ESP32_SEND_STATUS : return ESP32_Inf.DataSend_status;break;
		default : return 0;break;
	}
	
}
uint8_t * ESP32_GetWorkSpace(void)
{
//	if(ESP32_GetModule_Status(ESP32_SEND_STATUS) == ESP32_Send_BUSY)
//	{
//		return NULL;
//	}
//	else if(ESP32_GetModule_Status(ESP32_SEND_STATUS) == ESP32_Send_IDLE)
//	{
//		return BSP_ESP32_workspace;
//	}
//	return NULL;


	return BSP_ESP32_workspace;
}

static void esp32_setmodule_status(uint8_t status_kind , uint8_t status) // set esp32 module statusss
{
	switch(status_kind)
	{
		case ESP32_MODULE_STATUS : ESP32_Inf.Module_status = status;break;
		case ESP32_SEND_STATUS   : ESP32_Inf.DataSend_status = status;break;
		default:break;
	}
}

void ESP32_Loop(void)  // esp32 core func
{
	if(ESP32_Core_struct.count > 0)
	{
		DEBUG("ESP32_Core Count : %d\r\n",ESP32_Core_struct.count);
		if(ESP32_Core_struct.current_cmd == ESP32_Core_struct.next_cmd[ESP32_Core_struct.out]) // check cmd is same
		{
			ESP32_Core_struct.out ++;
			ESP32_Core_struct.count --;
			ESP32_Core_struct.out %= ESP32_Core_struct.size;
			ESP32_Core_struct.current_cmd = 0;
			return ;
		}
		ESP32_Core_struct.current_cmd = ESP32_Core_struct.next_cmd[ESP32_Core_struct.out];
		switch(ESP32_Core_struct.current_cmd)
		{
			case ESP32_IDEL:
			{
				DEBUG("ENTER ESP32_IDEL \r\n");
			}
			break;
			case ESP32_READY_TO_CONNECT:
			{
				BSP_ESP32_SetIP( macUser_Esp32_LocalID , macUser_Esp32_LocalGATAWAY , macUser_Esp32_LocalMASK,1); //设置IP地址
				RTOS_Delay_ms(10);
				BSP_ESP32_SetAP(macUser_Esp32_ApSsid , macUser_Esp32_ApPwd);  //返回IP地址
				RTOS_Delay_ms(10);
				BSP_ESP32_SetTCPServer(macUser_Esp32_TcpServer_IP , macUser_Esp32_TcpServer_Port);  //返回IP地址
				RTOS_Delay_ms(10);
				ESP32_ApplyNetSet(); // back ip addr

				DEBUG("ENTER ESP32_READY_TO_CONNECT \r\n");
			}
			break;
			case ESP32_POWER_REST:
			{
				DEBUG("ENTER ESP32_POWER_REST \r\n");
			}
			break;
			case ESP32_UP_STATUS_TO_CONNECTED:
			{
				
				DEBUG("ENTER ESP32_UP_STATUS_TO_CONNECTED \r\n");
				esp32_setmodule_status(ESP32_MODULE_STATUS , ESP32_CONNECTED);
				APP_DataSend_NetConnected();

			}
			break; 
			case ESP32_BUSY:
			{
				DEBUG("ESP32_BUSY \r\n");
			}
			break;
			default:break;
		}
		
		ESP32_Core_struct.out ++;
		ESP32_Core_struct.count --;
		ESP32_Core_struct.out %= ESP32_Core_struct.size;
		
		if(ESP32_Core_struct.count > 0)
		{
			Net_Task_Event_Start(NET_TASK_LOOP_EVENT, EVENT_FROM_TASK);
		}
	}
	else
	{
		
	}
}



void BSP_ESP32_TX_Enqueue(uint8_t * buf, uint16_t len)
{
	if(len >BSP_ESP32_TX_BUF_LEN || len == 0)
	{
		DEBUG("BSP_ESP32_TX_Enqueue Len :%d\r\n",len);
		return;
	}
	else
	{
		memcpy(BSP_ESP32_TxQueue.txbuf[BSP_ESP32_TxQueue.in].buf , buf , len);
		BSP_ESP32_TxQueue.txbuf[BSP_ESP32_TxQueue.in].len = len;
		BSP_ESP32_TxQueue.in ++ ; 
		BSP_ESP32_TxQueue.count ++;
		
		BSP_ESP32_TxQueue.in %= BSP_ESP32_TxQueue.size;
		DEBUG("BSP_ESP32_TX_Enqueue count:%d ,len:%d\r\n",BSP_ESP32_TxQueue.count ,len );
		Net_Task_Event_Start(NET_TASK_SEND_EVENT, EVENT_FROM_TASK);		
	}
}


uint8_t * BSP_ESP32_TX_Dequeue(uint16_t * len)
{
	uint8_t * buf_ptr = 0;
	
	buf_ptr = BSP_ESP32_TxQueue.txbuf[BSP_ESP32_TxQueue.out].buf ; 
	* len = BSP_ESP32_TxQueue.txbuf[BSP_ESP32_TxQueue.out].len;
	BSP_ESP32_TxQueue.out ++;
	
	
	
	
	//BSP_ESP32_TxQueue.count -- ;
	
	BSP_ESP32_TxQueue.out %= BSP_ESP32_TxQueue.size;
	
	if(BSP_ESP32_TxQueue.out <= BSP_ESP32_TxQueue.in)
	{
		BSP_ESP32_TxQueue.count = BSP_ESP32_TxQueue.in - BSP_ESP32_TxQueue.out;
	}
	else
	{
		BSP_ESP32_TxQueue.count = BSP_ESP32_TxQueue.in + BSP_ESP32_TxQueue.size - BSP_ESP32_TxQueue.out;
	}
	
	
	
	return buf_ptr;
}

void BSP_ESP32_Tx_Task(void)
{
	if(ESP32_Inf.DataSend_status == ESP32_Send_IDLE)
	{
		if(BSP_ESP32_TxQueue.count > 0)
		{
			
			uint8_t * buf_ptr = 0;
			uint16_t len = 0;
			
			ESP32_Inf.DataSend_status = ESP32_Send_BUSY;
			buf_ptr = BSP_ESP32_TX_Dequeue(& len);
			
			BSP_ESP32_WriteBytes(buf_ptr , len);
		}
		else
		{

		}
	}
	else
	{
		DEBUG("ESP32_Send BUSY\r\n");
	}
}

void BSP_ESP32_TxCheck(void)
{
	if(BSP_ESP32_TxQueue.count > 0 )
	{
		uint8_t * buf_ptr = 0;
		uint16_t len = 0;

		buf_ptr = BSP_ESP32_TX_Dequeue(& len);

		BSP_ESP32_WriteBytes(buf_ptr , len);
	}
	else
	{
		BSP_ESP32_TX_Queue_Init();
		ESP32_Inf.DataSend_status = ESP32_Send_IDLE;
		DEBUG("ESP32_Send_IDLE & TxQueue.count :%d\r\n",BSP_ESP32_TxQueue.count);
	}
}

static void BSP_ESP32_TX_Queue_Init(void)
{
	if(BSP_ESP32_TxQueue.count == 0)
	{
		if(BSP_ESP32_TxQueue.in != BSP_ESP32_TxQueue.out)
		{
			
			DEBUG("WHY in unequl out ,and the count is 0\r\n");
			BSP_ESP32_TxQueue.out = BSP_ESP32_TxQueue.in;
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

