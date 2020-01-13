/**
 **************************************************************************************************
 * @file        app_datafilter.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_datafilter.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_ad7682.h"
#include "system_param.h"
#include "rtos_tools.h"
#include "clog.h"
#include "dataprocess_task.h"
#include "bsp_led.h"
#include "dataemu_task.h"
/**
 * @addtogroup    app_datafilter_Modules 
 * @{  
 */

/**
 * @defgroup      app_datafilter_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datafilter_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_datafilter_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datafilter_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_datafilter_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_datafilter_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datafilter_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datafilter_Functions 
 * @brief         
 * @{  
 */

int32_t AD_ZERO[BSP_AD7682_ADCHS];
int32_t AD_ZEROlowpass[BSP_AD7682_ADCHS];
int32_t AD_INTER[BSP_AD7682_ADCHS];
int32_t lastdata[BSP_AD7682_ADCHS];
int32_t filtercounter[BSP_AD7682_ADCHS];
uint8_t app_datafilter_checksum[12] = {0};
uint32_t sprase_counter[12];
uint32_t StoreDateIndex[12];
int32_t wave_jscope[BSP_AD7682_SAMPLE_ADCH];

int16_t piz_emu_data[2][32768];
int16_t  mems_emu_data[2][3][8192]; //3轴mems数据存放
uint8_t currentSAMPLEblock = 0;
uint32_t ActualIndex = 0;

const uint32_t ADfrequence[4]={16384,8192,8192,8192};


void APP_DataFilter_SpraseIndex(void)
{
	uint8_t i=0;
	uint8_t ch[4]={0,1,2,3};
	for(i = 0;i < BSP_AD7682_ADCHS ; i ++){  //某方面限制了基准采样率为51200，因为8通道必须同步采样，所以8个通道只能一个基准采样率
			
		  g_SystemParam_Param.sparse_index[i] = (uint32_t)(ADfrequence[i] / g_SystemParam_Config.channel_freq[ch[i]]);
		}
}


void APP_DataFilter_Init(void)
{
	uint8_t i = 0 ;
	for(i= 0 ;i < BSP_AD7682_ADCHS ; i++)
	{
		AD_ZERO[i]=(uint64_t)32768*4096;  // tao 10s 
		AD_ZEROlowpass[i]=0u;
		AD_INTER[i]=0;
		g_SystemParam_Param.vs[i] = 0;
		lastdata[i]=0;
		app_datafilter_checksum[i]=0;		
		filtercounter[i]=0;
		sprase_counter[i]=0;
		StoreDateIndex[i]=0;
	}
	RTOS_Delay_ms(50);//负载开关有个电压稳定时间，所以需要这部分

	BSP_AD7682_StartSample();
	//HAL_Delay(1);
	RTOS_Delay_ms(1);
	BSP_AD7682_StopSample();
	
	BSP_AD7682_ClearData();

	AD_ZERO[0]=32768*4096;   //压电有稳定时间，但基准电压是OK的，所以可以直接取值，省的等他稳定
	AD_ZERO[1]= BSP_AD7682_Getcurvalue(1) * 8192;   //如果是压电，这个很好去确定初值，可是mems跟重力方向有关，有必要重新采集确定初值
	AD_ZERO[2]= BSP_AD7682_Getcurvalue(3) * 8192;  //两个采样率不一样
	APP_DataFilter_SpraseIndex();
	BSP_AD7682_StartSample();
}

void APP_DataFilter_Process(void)
{
	static uint8_t app_datafilter_firsttime = 1;
	
	uint16_t * app_data_ptr = 0;
	uint8_t j = 0;
	uint8_t i = 0;
	int32_t app_real_data = 0;
	uint8_t app_actual_sampleCH = 0;
	
	app_data_ptr = BSP_AD7682_GetDataBuf_Ptr();
	if(app_datafilter_firsttime == 1)  //为了能快速收敛，加快滤波稳定
	{
		
		app_data_ptr[0]=32768;
		app_data_ptr[1]=AD_ZERO[1]>>13;
		app_data_ptr[2]=32768;
		app_data_ptr[3]=AD_ZERO[2]>>13;
		app_data_ptr[4]=32768;
		app_data_ptr[5]=AD_ZERO[1]>>13;
		app_data_ptr[6]=32768;
		app_data_ptr[7]=AD_ZERO[2]>>13;
		app_datafilter_firsttime = 0;
	}


	for(j = 0 ; j < BSP_AD7682_SAMPLEPOINTS ; j ++)
	{	
		for(i=0;i<BSP_AD7682_SAMPLE_ADCH;i++)
		{

			app_real_data = (int32_t)((*(uint16_t*)app_data_ptr));
			app_actual_sampleCH = BSP_AD7682_GetRealCH( i ); //转换为实际ADC通道
			
			wave_jscope[app_actual_sampleCH]= app_real_data ;
			
			if(g_SystemParam_Config.interface_type[app_actual_sampleCH] == TYPE_IEPE)
			{

				switch(app_actual_sampleCH)
				{
					case 0:
					{
						AD_ZERO[app_actual_sampleCH] = app_real_data + (((int64_t)AD_ZERO[app_actual_sampleCH]*4095)>>12); // >> 16 /65536  >> 15 /32768  >> 14 / 16384  >> 13 / 8192
						app_real_data = app_real_data - (int32_t)(AD_ZERO[app_actual_sampleCH] >> 12); //AD_ZEROlowpass[i]

						if(g_SystemParam_Config.channel_freq[app_actual_sampleCH]==16384)
						{
							// 6000Hz
							AD_ZEROlowpass[app_actual_sampleCH] = ((int64_t)app_real_data+lastdata[app_actual_sampleCH])*45292 - AD_ZEROlowpass[app_actual_sampleCH]*25049; //5
							AD_ZEROlowpass[app_actual_sampleCH] = AD_ZEROlowpass[app_actual_sampleCH]>>16;			
							lastdata[app_actual_sampleCH] = app_real_data;
							app_real_data = AD_ZEROlowpass[app_actual_sampleCH];

						}
						else if(g_SystemParam_Config.channel_freq[app_actual_sampleCH] == 8192)
						{
							/***********************?ù×?2é?ù?ê32768￡?êμ?ê3é?ù8192￡?μíí¨2500 0.19638846199800786 -0.60722307600398429*******/			
							//				?ù×?2é?ù?ê16384￡?êμ?ê3é?ù8192￡?μíí¨2500			0.34202261737325917       -0.31595476525348171      
							//								AD_ZEROlowpass[app_actual_sampleCH]=((int64_t)y+lastdata[app_actual_sampleCH])*15767+AD_ZEROlowpass[app_actual_sampleCH]*34002;
							//							AD_ZEROlowpass[app_actual_sampleCH] = ((int64_t)y + lastdata[app_actual_sampleCH]) * 22414 + AD_ZEROlowpass[app_actual_sampleCH] * 20706;
							//							AD_ZEROlowpass[app_actual_sampleCH] = AD_ZEROlowpass[app_actual_sampleCH]>>16;			
							//							lastdata[app_actual_sampleCH] = y;
							//							y = AD_ZEROlowpass[app_actual_sampleCH];
						}
						else if(g_SystemParam_Config.channel_freq[app_actual_sampleCH]==2048)
						{
							/*********************?ù×?2é?ù?ê32768￡?êμ?ê3é?ù2048￡?μíí¨625 0.056597493815809335      -0.88680501236838138      *******/			  													
							//	*?ù×?2é?ù?ê16384￡?êμ?ê3é?ù2048￡?μíí¨625 		0.1074769920231831        -0.78504601595363377      
							//								AD_ZEROlowpass[app_actual_sampleCH]=((int64_t)y+lastdata[app_actual_sampleCH])*10286+AD_ZEROlowpass[app_actual_sampleCH]*45648;
							AD_ZEROlowpass[app_actual_sampleCH] = ((int64_t)app_real_data+lastdata[app_actual_sampleCH])*7043+AD_ZEROlowpass[app_actual_sampleCH]*51448;
							AD_ZEROlowpass[app_actual_sampleCH] = AD_ZEROlowpass[app_actual_sampleCH]>>16;	
							lastdata[app_actual_sampleCH] = app_real_data;
							app_real_data = AD_ZEROlowpass[app_actual_sampleCH];
						}					
					}
					break;
					default :
					{
						AD_ZERO[app_actual_sampleCH] = app_real_data + (((int64_t)AD_ZERO[app_actual_sampleCH] * 8191) >> 13);
						app_real_data = app_real_data - (int32_t)(AD_ZERO[app_actual_sampleCH] >> 13);

						if(g_SystemParam_Config.channel_freq[app_actual_sampleCH] == 8192)
						{
							//								/************************?ù×?2é?ù?ê8192￡?êμ?ê3é?ù8192￡?μíí¨2500 0.58754852395358581       0.17509704790717162       *************/			
							AD_ZEROlowpass[app_actual_sampleCH]=((int64_t)app_real_data+lastdata[app_actual_sampleCH])*38505-AD_ZEROlowpass[app_actual_sampleCH]*11475; //6.2K
							AD_ZEROlowpass[app_actual_sampleCH]=AD_ZEROlowpass[app_actual_sampleCH]>>16;			
							lastdata[app_actual_sampleCH]=app_real_data;
							app_real_data=AD_ZEROlowpass[app_actual_sampleCH];

						}
						else if(g_SystemParam_Config.channel_freq[app_actual_sampleCH]==2048)
						{
						/***********************?ù×?2é?ù?ê8192￡?êμ?ê3é?ù2048￡?μíí¨625 0.19638846199800786        -0.60722307600398429      *******/			

							AD_ZEROlowpass[app_actual_sampleCH]=((int64_t)app_real_data+lastdata[app_actual_sampleCH])*12870+AD_ZEROlowpass[app_actual_sampleCH]*39794;
							AD_ZEROlowpass[app_actual_sampleCH]=AD_ZEROlowpass[i]>>16;			
							lastdata[app_actual_sampleCH] = app_real_data;
							app_real_data=AD_ZEROlowpass[app_actual_sampleCH];
						}	
					}
			
					break;
				}

				/**************************抽样部分************************/

				sprase_counter[app_actual_sampleCH]++;
				if(sprase_counter[app_actual_sampleCH] >= g_SystemParam_Param.sparse_index[app_actual_sampleCH]) 
				{
				sprase_counter[app_actual_sampleCH] = 0;
				//用来记录储存数据的下标
				//						y=((float)y*0.30517578f-config.floatadjust[app_actual_sampleCH])*config.floatadc[app_actual_sampleCH]*config.floatscale[app_actual_sampleCH];//*0.1f;//-config.floatscale[i];//-500.0f; // mv???0.038146f						
				APP_DataFilter_UpdateAccData((int16_t)app_real_data,app_actual_sampleCH,StoreDateIndex[app_actual_sampleCH]);
				StoreDateIndex[app_actual_sampleCH]++;
				}
			}
			else if(g_SystemParam_Config.interface_type[app_actual_sampleCH]==TYPE_NONE)
			{
				//halfref=y;
			}


			app_data_ptr ++;
			ActualIndex++;   //原则上应该加个中断锁的，特别是当特征值模式下，写这个下标参数为0时，后来改了一个方案				

		}



		if(ActualIndex>=32768)
		{ 
			//RTC_ReadClock();	/* 读时钟，结果在 g_tRTC */
			for(i=0;i<BSP_AD7682_ADCHS;i++)
			{
				StoreDateIndex[i]=0;
				sprase_counter[i]=0; //全部归0
			}
			ActualIndex=0;
			currentSAMPLEblock=(currentSAMPLEblock+1)%2;
			//osSemaphoreRelease(seconds_sample_data_readyHandle);
			//Dataprocess_Task_Event_Start( DATAPEOCESS_TASK_CALC_EVENT, EVENT_FROM_TASK);
			
			DataEmu_Task_Event_Start(DATAEMU_TASK_EMU_EVENT , EVENT_FROM_TASK);
			DEBUG("Sample Complete\r\n");
		}
	}
	//			bsp_LedStatue(1,1);

}
//int16_t test_wave[4] = {0};
void APP_DataFilter_UpdateAccData(int16_t data , uint8_t channel , uint32_t DataIndex)
{
	switch(channel){
		case 0:
			piz_emu_data[currentSAMPLEblock][DataIndex] = data;
			//test_wave[0] = data;
			//test_wave = data;
		break;
		case 1:
			mems_emu_data[currentSAMPLEblock][0][DataIndex] = data;
			//test_wave[1] = data;
		break;
		case 2:
			mems_emu_data[currentSAMPLEblock][1][DataIndex] = data;
			//test_wave[2] = data;
		break;
		case 3:
			mems_emu_data[currentSAMPLEblock][2][DataIndex] = data;
			//test_wave[3] = data;
		break;
		default:
			break;
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

