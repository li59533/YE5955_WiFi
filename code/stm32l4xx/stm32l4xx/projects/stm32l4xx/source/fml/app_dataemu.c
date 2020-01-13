/**
 **************************************************************************************************
 * @file        app_dataemu.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_dataemu.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "system_param.h"
#include "bsp_ad7682.h"
#include "rtos_tools.h"
#include "app_datafilter.h"
#include "arm_math.h"
#include "double_integral.h"
#include "clog.h"
/**
 * @addtogroup    app_dataemu_Modules 
 * @{  
 */

/**
 * @defgroup      app_dataemu_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_dataemu_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_dataemu_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_dataemu_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_dataemu_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_dataemu_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_dataemu_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void app_dataemu_func(void);
/**
 * @}
 */

/**
 * @defgroup      app_dataemu_Functions 
 * @brief         
 * @{  
 */
void APP_DataEmu_Process(void)
{
	//WaritSignalCounter++;
	//if(WaritSignalCounter > g_SystemParam_Config.WaitforIEPEtime) //d等待信号滤波稳定开始发送数据
	{

		
		//BSP_AD7682_StopSample();
		//SystemParam_Save();

		app_dataemu_func();

		//Boardg_SystemParam_Param_withtime_forJUNYUE();

	}
}
#define numStages 2 /* 2阶IIR滤波的个数 */
float32_t testOutput[16384] ;//////输出结果
float32_t IIRStateF32[4*numStages]; /* 状态缓存，大小numTaps + blockSize - 1*/
/* 巴特沃斯低通滤波器系数 140Hz */
const float32_t IIRCoeffs16384_1600HP[5*numStages] = {
1 , 2 , 1 , 1.3399160934903298         ,  -0.63887106504007884        ,    
1 , 2 , 1 , 1.0673588418587563         ,  -0.30550228513217675            
};
const float sacle16384_1600HP=0.074738742887437259f*0.05953586081835513f;


const float32_t IIRCoeffs8192_1600HP[5*numStages] = {
1 , 2 , 1 , 0.49531214578230898        ,  -0.47024952160149391           ,    
1 , 2 , 1 , 0.36033441950676542        ,  -0.069591190944092607         
};
const float sacle8192_1600HP=0.24373434395479621f*0.17731419285933178f;


const float32_t IIRCoeffs4096_1600HP[5*numStages] = {
1 , 2 , 1 , -1.2440102900675862          , -0.60930590867938939          ,    
1 , 2 , 1 , -0.97472921694631054         , -0.26095218079659854           
};
const float sacle4096_1600HP=0.71332904968674393f*0.55892034943572722f;

const float IIRCoeffs16384_1000_6000BP[5*numStages] = {
1,  0,  -1,  1.461284132969656,       -0.59524384411993081, 
1,  0,  -1,  -0.83352188313723552,   -0.33796843110898939   
};
const float sacle16384_1000_6000BP= 0.63429186127528914f*0.63429186127528914f;

const float IIRCoeffs16384_1000LP[5*numStages] = {
1 , 2 , 1 , 1.6224170187429059        , - 0.74949598875049617          ,    
1 , 2 , 1 , 1.3782783266582523        , - 0.48623465854586218             
};
const float sacle16384_1000LP=0.031769742501897576f*0.026989082971902483f;

float emu_inter_data[16384];
arm_biquad_casd_df1_inst_f32 S_test;
float fft_data[4096];
float fft_inter_data[4096];

static void app_dataemu_func(void)
{
	uint32_t SAMPLEblock=(currentSAMPLEblock+1)%2;;
	float ScaleValue=1;
	float avage[4];
	uint32_t maxindex;
	float EnvelopMax[4];
	float inter_factor;
	
	uint8_t j = 0 ;
	
	
	for(j = 0 ; j < BSP_AD7682_ACC_REALCHS ; j ++)
	{
		inter_factor = g_SystemParam_Config.floatscale[j] * g_SystemParam_Config.floatadc[j] * 0.045776f  ;//3000 / 65535;
		switch(j)
		{
			case 0: 
				for(uint32_t i=0;i<g_SystemParam_Config.channel_freq[j];i++)
				emu_inter_data[i]=inter_factor * piz_emu_data[SAMPLEblock][i];
			break;
			default:
				for(uint32_t i=0;i<g_SystemParam_Config.channel_freq[j];i++)
				{
					emu_inter_data[i]=inter_factor*mems_emu_data[SAMPLEblock][j -1][i];
				}
			break;
		}

		/*
		for(uint32_t i=0;i<g_SystemParam_Config.channel_freq[j];i++)
			emu_inter_data[i] = test11[0]*arm_sin_f32(2*3.1415926f*test11[1]*i/g_SystemParam_Config.channel_freq[j]);
		*/
		
		switch(g_SystemParam_Config.channel_freq[j])
		{
			case 16384:
				{
					arm_biquad_cascade_df1_init_f32(&S_test, numStages, (float32_t *)&IIRCoeffs16384_1600HP[0], (float32_t
					*)&IIRStateF32[0]);
					/* IIR滤波 */
					arm_biquad_cascade_df1_f32(&S_test,emu_inter_data, testOutput, g_SystemParam_Config.channel_freq[j]);
					/*放缩系数 */
					ScaleValue = sacle16384_1600HP;
				}
				for(uint32_t i=0;i<4096;i++)
				{
					fft_data[i]=testOutput[4*i]*ScaleValue;
				}
			break;
			case 8192:
				arm_biquad_cascade_df1_init_f32(&S_test, numStages, (float32_t *)&IIRCoeffs8192_1600HP[0], (float32_t
				*)&IIRStateF32[0]);
				/* IIR滤波 */
				arm_biquad_cascade_df1_f32(&S_test,emu_inter_data, testOutput,  g_SystemParam_Config.channel_freq[j]);
				/*放缩系数 */
				ScaleValue = sacle8192_1600HP;
				for(uint32_t i=0;i<4096;i++)
				{
					fft_data[i]=testOutput[2*i]*ScaleValue;
				}
			break;
			case 4096:
				arm_biquad_cascade_df1_init_f32(&S_test, numStages, (float32_t *)&IIRCoeffs4096_1600HP[0], (float32_t
				*)&IIRStateF32[0]);
				/* IIR滤波 */
				arm_biquad_cascade_df1_f32(&S_test,emu_inter_data, testOutput, g_SystemParam_Config.channel_freq[j]);
				/*放缩系数 */
				ScaleValue = sacle4096_1600HP;
				for(uint32_t i=0;i<4096;i++)
				{
					fft_data[i]=testOutput[i]*ScaleValue;
				}   
			break;
			default:

			break;
		}         
		
		arm_rms_f32(fft_data, 4096, &g_SystemParam_Param.Arms[j]);
		integ_init(4096,4096,1000,1,4,1000);  //速度到4
		frq_domain_integral(fft_data,fft_inter_data);
		arm_rms_f32(fft_inter_data, 4096, &g_SystemParam_Param.Vrms[j]);
		integ_init(4096,4096,1000000,2,10,1000);//位移到10
		frq_domain_integral(fft_data,fft_inter_data);
		arm_rms_f32(fft_inter_data, 4096, &g_SystemParam_Param.Drms[j]);
		
		if(0)
		{
			integ_init(4096,4096,1,1,10,1000);//位移到10
			frq_envelop_integral(fft_data,fft_inter_data);
			arm_max_f32(fft_inter_data, 4096, &EnvelopMax[j],&maxindex);
			arm_sqrt_f32(EnvelopMax[j],&g_SystemParam_Param.Envelop[j]);
		}

		arm_mean_f32(emu_inter_data, g_SystemParam_Config.channel_freq[j], &avage[j]); //求均值

		for(uint32_t i=0;i<g_SystemParam_Config.channel_freq[j];i++)
		{
			emu_inter_data[i]=(emu_inter_data[i]-avage[j]); //去下均值
			testOutput[i]=emu_inter_data[i];
		}

		arm_rms_f32(emu_inter_data, g_SystemParam_Config.channel_freq[j], &g_SystemParam_Param.EffectiveValue[j]);	
		for(uint32_t i=0;i<g_SystemParam_Config.channel_freq[j];i++)
		{
			emu_inter_data[i]=emu_inter_data[i]*emu_inter_data[i]*emu_inter_data[i]*emu_inter_data[i];
		}
		arm_rms_f32(emu_inter_data, g_SystemParam_Config.channel_freq[j], &g_SystemParam_Param.Kurtosis[j]);
		g_SystemParam_Param.KurtosisIndex[j]=g_SystemParam_Param.Kurtosis[j]/(g_SystemParam_Param.EffectiveValue[j]*g_SystemParam_Param.EffectiveValue[j]*g_SystemParam_Param.EffectiveValue[j]*g_SystemParam_Param.EffectiveValue[j]);


		if((j==0)&&(g_SystemParam_Config.channel_freq[j]==16384)) //对主轴进行包络计算
		{
			arm_biquad_cascade_df1_init_f32(&S_test, numStages, (float32_t *)&IIRCoeffs16384_1000_6000BP[0], (float32_t
			*)&IIRStateF32[0]);
			/* IIR滤波 */
			arm_biquad_cascade_df1_f32(&S_test,testOutput, emu_inter_data, g_SystemParam_Config.channel_freq[j]);
			/*放缩系数 */
			ScaleValue = sacle16384_1000_6000BP;
			for(uint32_t i=0;i<16384;i++)
			{
				emu_inter_data[i]=emu_inter_data[i]*ScaleValue;
			}  
			arm_abs_f32(emu_inter_data,testOutput,16384);
			arm_biquad_cascade_df1_init_f32(&S_test, numStages, (float32_t *)&IIRCoeffs16384_1000LP[0], (float32_t
			*)&IIRStateF32[0]);
			/* IIR滤波 */
			arm_biquad_cascade_df1_f32(&S_test,testOutput, emu_inter_data, g_SystemParam_Config.channel_freq[j]);
			ScaleValue = sacle16384_1000LP;
			arm_max_f32(emu_inter_data, 16384, &EnvelopMax[j],&maxindex);  //换来换去，头都混了
			g_SystemParam_Param.Envelop[j]=EnvelopMax[j]*ScaleValue;
		}	
		
		
//		char debug[40];
//		snprintf(debug,40,"E:%0.2f,V:%0.2f,D:%0.2f,K:%0.2f,E:%0.2f",g_SystemParam_Param.EffectiveValue[j],\
//													g_SystemParam_Param.Vrms[j],\
//													g_SystemParam_Param.Drms[j],\
//													g_SystemParam_Param.KurtosisIndex[j],\
//													g_SystemParam_Param.Envelop[j]);
//		
//		DEBUG("%s\r\n",debug);
		if(g_SystemParam_Param.EffectiveValue[j] < 0.25f)//g_SystemParam_Param.Arms[j] < 0.25f || 
		{
//			g_SystemParam_Param.Vrms[j] = 0.0f;
//			g_SystemParam_Param.Drms[j] = 0.0f;
//			g_SystemParam_Param.KurtosisIndex[j] = 0.0f;
//			g_SystemParam_Param.Envelop[j] = 0.0f;
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

