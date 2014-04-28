
#ifndef _ZIVS_DATTYP_ALGOVA_H_
#define _ZIVS_DATTYP_ALGOVA_H_

#include "AlgoVA_IF.h"


#ifdef __cplusplus
extern "C"
{
#endif


#define BUF_SIZE_CONTROL	(64-32)
#define BUF_SIZE_EVENT		(64-32)
#define BUF_SIZE_VPRO		(16*1024-32)
#define BUF_SIZE_CONFIG		(128*1024-32)

#define EVENT_ID_SLAVE_MIN	0x10000000
#define EVENT_ID_SLAVE_MAX	0x1FFFFFFF

// ״̬��
typedef enum
{
	ZIVS_STATUS_SUCCESS				= 0x00000000,
	ZIVS_STATUS_COMMAND				= 0x00010000,
	ZIVS_STATUS_ERROR				= 0x00080000,
	ZIVS_STATUS_ERROR_NOT_FOUND		= 0x00080001,
	ZIVS_STATUS_ERROR_NOT_SUPPORTED	= 0x00080002
} ZIVS_STATUS;

// ����ͨ������
typedef struct
{
	uint32_t	size;							// ���ݰ�����
	uint32_t	type;							// ����
	uint32_t	status;							// ״̬
	uint32_t	channel;						// ͨ����
	uint32_t	time;							// ʱ��
	uint32_t	date;							// ����
	uint32_t	id;								// ��ʶ
	uint32_t	level;							// ��������
} ZIVS_OPER_DATA;


///////////////////////////////////////////////////////////////////////////////////////////////////
// ���������������

// ��������
typedef enum
{
	ZIVS_CONTROL_TYPE_BASE = 0x1000,

	ZIVS_CONTROL_TYPE_VDR_Arm			= 0x1000,	// ��������
	ZIVS_CONTROL_TYPE_VDR_Disarm		= 0x1001,	// �������
	ZIVS_CONTROL_TYPE_VDR_ClearAlarm	= 0x1002,	// �������

	ZIVS_CONTROL_TYPE_PTZ_EnterPTZMode	= 0x1100,	// ����PTZģʽ
	ZIVS_CONTROL_TYPE_PTZ_ExitPTZMode	= 0x1101,	// �˳�PTZģʽ
	ZIVS_CONTROL_TYPE_PTZ_Control		= 0x1102,	// PTZ��ؿ���
	
	ZIVS_CONTROL_TYPE_END
} ZIVS_CONTROL_TYPE;

typedef union
{
	uint8_t buffer[BUF_SIZE_CONTROL];
} ZIVS_CONTROL_DATA_INTERNAL;

typedef struct
{
	ZIVS_OPER_DATA head;						// ����ͷ
	ZIVS_CONTROL_DATA_INTERNAL data;			// ��������
} ZIVS_CONTROL_DATA;

// ���Ʋ��������������
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// �¼������������

// �¼����ݸ�ʽ

typedef enum
{
	ZIVS_EVENT_TYPE_BASE = 0x2000,

	ZIVS_EVENT_TYPE_EVENT	= 0x2000,		// �¼�����
	
	ZIVS_EVENT_TYPE_END
} ZIVS_EVENT_TYPE;

typedef union
{
	uint8_t buffer[BUF_SIZE_EVENT];
	VAEVT_ITEM	data4Event;					// �¼�����
} ZIVS_EVENT_DATA_INTERNAL;

typedef struct
{
	ZIVS_OPER_DATA head;						// ����ͷ
	ZIVS_EVENT_DATA_INTERNAL data;				// �¼�����
} ZIVS_EVENT_DATA;

// �¼������������
///////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ƶ���������������

// ��Ƶ��������
typedef enum
{
	ZIVS_VPRO_TYPE_BASE = 0x3000,

	ZIVS_VPRO_TYPE_TARGET_SET	= 0x3000,		// ��Ƶ����Ŀ��

	ZIVS_VPRO_TYPE_END
} ZIVS_VPRO_TYPE;

// ��Ƶ�������ݸ�ʽ

typedef union
{
	uint8_t buffer[BUF_SIZE_VPRO];
	VATGT_SET	data4Targets;					// Ŀ�꼯��
} ZIVS_VPRO_DATA_INTERNAL;

typedef struct
{
	ZIVS_OPER_DATA head;						// ����ͷ
	ZIVS_VPRO_DATA_INTERNAL	data;				// ��Ƶ��������
} ZIVS_VPRO_DATA;

// ��Ƶ���������������
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// ���������������

typedef enum
{
	ZIVS_CONFIG_TYPE_BASE = 0x4000,

	ZIVS_CONFIG_TYPE_SetVideoSourceMode							= 0x4100,	// ��Ƶ������ʽ
	ZIVS_CONFIG_TYPE_GetVideoSourceMode							= 0x4101,
	ZIVS_CONFIG_TYPE_SetSysTime									= 0x4102,	// ϵͳʱ��
	ZIVS_CONFIG_TYPE_GetSysTime									= 0x4103,
	ZIVS_CONFIG_TYPE_SetSecretCode								= 0x4104,	// ��ȡϵͳ�ļ���оƬֵ
	ZIVS_CONFIG_TYPE_GetSecretCode								= 0x4105,

	ZIVS_CONFIG_TYPE_SetVideoAnalysisFuncode					= 0x4700,	// �㷨������
	ZIVS_CONFIG_TYPE_GetVideoAnalysisFuncode					= 0x4701,
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVersionIVP					= 0x4703,	// �㷨�汾
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVersionFSD					= 0x4705,
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVersionCRD					= 0x4707,
	ZIVS_CONFIG_TYPE_SetVideoAnalysisCLBR						= 0x470E,	// ��Ƶ��������(CLBR)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisCLBR						= 0x470F, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisSceneIVP					= 0x4710,	// ��Ƶ��������(IVP)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisSceneIVP					= 0x4711, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisSceneFSD					= 0x4712,	// ��Ƶ��������(FSD)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisSceneFSD					= 0x4713, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisSceneCRD					= 0x4714,	// ��Ƶ��������(CRD)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisSceneCRD					= 0x4715, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceIVProcessor	= 0x4720,	// IVP�߼�����(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceIVProcessor	= 0x4721, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceDetection		= 0x4722,	// ���ģ��߼�����(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceDetection		= 0x4723, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceTrack			= 0x4724,	// ����ģ��߼�����(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceTrack			= 0x4725,
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceClassfier		= 0x4726,	// ����ģ��߼�����(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceClassfier		= 0x4727,
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceAnalyst		= 0x4728,	// ����ģ��߼�����(ADV)     
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceAnalyst		= 0x4729,
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvancePTZ			= 0x472A,	// PTZ�߼�����(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvancePTZ			= 0x472B, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceFire			= 0x4730,	// �̻���ģ��߼�����(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceFire			= 0x4731,               
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceCRD			= 0x4740,	// CRD(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceCRD			= 0x4741,               

	ZIVS_CONFIG_TYPE_END
} ZIVS_CONFIG_TYPE;

// �������ݸ�ʽ

typedef union  
{
	uint8_t buffer[BUF_SIZE_CONFIG];
} ZIVS_CONFIG_DATA_INTERNAL;

typedef struct  
{
	ZIVS_OPER_DATA head;				// ����ͷ
	ZIVS_CONFIG_DATA_INTERNAL data;		// ��������
} ZIVS_CONFIG_DATA;


#ifdef __cplusplus
}
#endif


#endif


