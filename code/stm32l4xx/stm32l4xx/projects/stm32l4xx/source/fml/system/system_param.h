/**
 **************************************************************************************************
 * @file        system_param.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _SYSTEM_PARAM_H_
#define _SYSTEM_PARAM_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    system_param_Modules 
 * @{  
 */

/**
 * @defgroup      system_param_Exported_Macros 
 * @{  
 */
#define SYSTEMPARAM_CONFIG     0

#define SYSTEMPARAM_SAVE_SPACE_LEN   0x1000
#define SYSTEMPARAM_SAVE_FIRST_ADDR   0x081FE000
#define SYSTEMPARAM_SAVE_SECOND_ADDR  0x081FF000

/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Types 
 * @{  
 */
#pragma pack(1)
typedef enum 
{
	PARAMETERMODE = 1,
	WAVEMODE = 2,
	FFTWAVEMODE = 3,
	FFTPARAMETERMODE = 4,
	IDLEMODE = 5,
	LITEWAVEMODE = 6
}DataToBoard_TYPE;


typedef enum 
{
	TYPE_NONE = 0,
	TYPE_MA = 1,
	TYPE_V = 2, 
	TYPE_IEPE = 3,
	TYPE_PT = 4,
	TYPE_HBR = 5,
	TYPE_AC_V = 6,
}INTERFACE_TYPE;
typedef enum 
{
	UNIT_NONE = 0,
	UNIT_V = 1,
	UNIT_A = 2,
	UNIT_KV = 3,
	UNIT_TEMP = 4,
	UNIT_M = 5,
	UNIT_M_S = 6,
	UNIT_M_S2 = 7,
	UNIT_G = 8,
	UNIT_MA = 9,
	UNIT_DB = 10,
	UNIT_MM_S = 11,
}INTERFACE_UNIT;

typedef enum 
{
	Greater=0,
	Equal=1,
	Less=2
}Equality_relation;

typedef enum 
{
	AND=0,
	OR
}Logical_relation;

typedef enum 
{
	daois=0,
	sdaOR
}Parameter_name;

typedef struct
{
	bool 	End_statue;  //�Ƿ�Ϊ��ͨ�������һ������Դ
	uint8_t channel_number;
	Parameter_name parameter_NAME;
 	Logical_relation logical; //����Դ�߼���ϵ
	Equality_relation relationship; //����Դ����ֵ��ʽ��ϵ
	float gatedata;
}RULE;

typedef struct
{
	uint16_t vaildsign;
	uint8_t baundrate;    /* =0:600    =1:1200 		=2:2400 		=3:4800 		=4:9600 */
	uint8_t addr; 
	uint8_t SNnumber[8]; 
	uint8_t parity;		// =0 : n,8,1   =1: o,8,1  =2: e,8,1	 ���ݸ�ʽ
	float floatscale[12];
	//float floatrange[12];
	uint8_t DisplayMode;  // ��ʾģʽ��=0���̶���=1 ѭ��
	uint8_t interface_type[12]; // ��������
	uint8_t unit[12];  // ��λ
	float floatrange[12]; // ת��ϵ��
	float floatadjust[12]; // ����ֵ
	//uint16_t interface_addr[12]; // modbus ��ַ �ϴ�
	float alarmgate[6]; // ����ֵ
	float floatadc[6]; // ����ֵ
	uint8_t means	;// ��ֵ����
	uint16_t means_times; // ��ֵ��������
	uint16_t freq;  // ����Ƶ�� Hz
	uint16_t avr_count;
	uint8_t reflash; // ˢ��ʱ�� 
	uint16_t din_addr;  //  ����������Ĵ�����ַ
	uint16_t dout_addr; //  ����������Ĵ�����ַ
	uint32_t force_gate,force_backlash;  // Ӧ��������ֵ�� �ز
	uint16_t max_addr0,max_addr1;        //
	uint16_t vlpsseconds;            //  
	uint16_t vlprseconds;           //
	uint16_t runseconds;           //
	uint16_t pga;                 //
	uint16_t workcycleseconds;   //  ��������
	uint16_t fangda;            //  �Ŵ���
	uint16_t boardset;         // ���书������
	uint16_t ADtime;          //AD���β���ʱ��
	uint16_t ADfrequence;    //AD����Ƶ��
	  
	uint64_t alarmminutetime;  //��ʼ����ʱ��
	uint32_t FLASH_WRADDR;    //flash��ʼ��ַ
	uint8_t  DataToBoardMode; 
	uint16_t  DataToSendChannel;
	uint8_t  DHCP;
	char APssid[20];
	char APpassword[20];
	char TcpServer_IP[20];
	char TcpServer_Port[10];
	char LocalIP[20];
	char LocalGATEWAY[20];
	char LocalMASK[20];
	uint32_t PeriodTransimissonCounter;
	uint8_t PeriodTransimissonStatus;
	uint8_t ParameterTransimissonStatus;
	uint8_t RequirePeriodChannel; //������Щ���β��ε�ͨ��
	uint8_t RESETTIME;
	uint8_t Enable_active_beacon;
	uint8_t Iap_flag;
	uint32_t Iap_datalength;
	uint32_t channel_freq[12];
	uint32_t BeaconInterval;
	char server_address[20];
	char DNS_SERVERIP[20];
	uint8_t Lowpower_Mode;
	uint8_t scan_channel;
	uint8_t Waitforsleeptime;
	uint8_t WaitforIEPEtime;
	float  filterMean[6];
	uint32_t WaitToPeriodTransmissonCounter;
	float Alarm_value_junyue[20];//�����õ�20������ֵ
	float battery;//�����õ�20������ֵ
	uint16_t workcycleseconds_inAlarmStatue;
	int16_t tempCompensation; 
	uint8_t Alarm_source_number[10];//10������ÿ������ı���Դ��Ŀ��Ϊ0�򲻱�����
	RULE Alarm_source[10][20]; //��ά���飬���10������ÿ���������20������Դ
	
	/* Bigym use param*/
	uint32_t sleep_time;
	
    uint16_t crc;           /*!< ���еĲ����ṹ����밴�ֽڶ��䡣�����һ�������
                                 ��һ��uint16_t���͵����ݣ������������ڲ��洢ʱ��
                                 crcУ��ʹ洢���û��ڱ������ʱ���ù��ĸ�ֵ��ֵ��*/
}SystemParam_Config_t;
#pragma pack()

// --------------Param
typedef  struct 
{
	uint16_t vaildsign;
	int32_t int_v[12];
	int32_t int_av[12];
	int64_t s[12]; // �ۻ�
	int64_t as[12]; // �ۻ�
	uint32_t sparse_index[12];
	float v[12];
	float fv[12];
	float vs[12];  //�ٶ��ۼӺͣ�������
	float av[12];
	float adate;                //���ٶ�
	float vdate;                 //�ٶ�
	float xdate;                  //λ��
	float pdate;                   //�¶�
	float scale_v[12];
	int32_t gate[12];
	int32_t backlash[12];
	uint8_t alarm[12]; // ������־
	uint16_t din;  // ��8λ��Ӧ 8��ͨ������
	uint16_t dout; // ��4λ��Ӧ 4�����ͨ�� 
	uint32_t status;
	int32_t ch1_int_max,ch2_int_max;
	int32_t ch1_int_max1,ch2_int_max2;
	float ch1_max,ch2_max;
	int32_t vibrate_gate1,vibrate_gate2,vibrate_backlash1,vibrate_backlash2;
	int32_t force_gate,force_backlash;
	int16_t selfpgaallow;
	uint16_t daytime;
	uint16_t minutetime;
	uint16_t selffangda;
	uint16_t alarmminutetime;
	uint8_t Esp32TransmissionMode;
	uint32_t sleeptime;
	uint8_t wakeupsourec;
	float Abs_average[12];
	float ReciprocalofADfrequence[16];
	float Inter_Skew[12]; //���
	float InterIIMarginIndex[12];//ԣ��ָ���м����
	float InterMAX[12];
	float InterMIN[12];
	float S_sum[12];
	float SS_sum[12];
	float SSS_sum[12];
	float SSSS_sum[12];
	float Abs_S_average[12];
	float PeakValue[12];  //���ֵ
	float EffectiveValue[12]; //��Чֵ
	float Skew[12]; //���
	float MaxValue[12]; //��ֵ
	float Kurtosis[12]; //�Ͷ�
	float Mean[12]; //��ֵ
	float WaveformIndex[12]; //����ָ��
	float PeakIndex[12];//��ֵָ��
	float PulseIndex[12];//����ָ��
	float MarginIndex[12];//ԣ��ָ��
	float KurtosisIndex[12];//�Ͷ�ָ��
	float Inter_MarginIndex[12]; //�Ͷ�
	float S_average[12]; //ƽ��ֵ��ֵ
	float average[12]; //ƽ��ֵ
	float ReciprocalofEMUnumber[16]; //����Ƶ�ʵĵ�������������
	float ReciprocalofRange[16];//���̵ĵ���
	float Arms[12];
	float Vrms[12];
	float Drms[12];
	float Envelop[12];
	//
	float F_sum[12];     //s(k)֮��
	float FS_sum[12];   //f(k)s(k)�ĺ�
	float FFS_sum[12];  //F(K)F(K)S(K)
	float FFFFS_sum[12];  //F(K)F(K)S(K)
	float F2_sum[12];     //feature2���м��
	float F3_sum[12];     //feature3���м��
	float F4_sum[12];     //feature4���м��
	float F6_sum[12];     //feature6���м��
	float F11_sum[12];     //feature11���м��
	float F12_sum[12];     //feature12���м��
	float F13_sum[12];     //feature12���м��
	float F_feature1[12];
	float F_feature2[12];
	float F_feature3[12];
	float F_feature4[12];
	float F_feature5[12];
	float F_feature6[12];
	float F_feature7[12];
	float F_feature8[12];
	float F_feature9[12];
	float F_feature10[12];
	float F_feature11[12];
	float F_feature12[12];
	float F_feature13[12];
	uint32_t IapDataLength;
	uint32_t PeroidWaveTransmissionCounter;
	uint32_t AutoPeriodTransmissonCounter;
	uint64_t DeviceKey;
	
	uint8_t sample_adch;
	uint8_t ad7682_adchs ;
	uint8_t acceleration_adchs ;
	uint8_t temp_adchs;
	uint8_t samplepoints;
	uint16_t boardpoints;
	uint16_t periodboardpoints;
	
}SystemParam_Param_t;

/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Variables 
 * @{  
 */
extern SystemParam_Config_t g_SystemParam_Config;
extern SystemParam_Param_t g_SystemParam_Param;
/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Functions 
 * @{  
 */
void SystemParam_Init(void);
int16_t SystemParam_Read(void);
void SystemParam_Save(void);
void SystemParam_Reset(void);
void SystemParam_Apply(void);
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
