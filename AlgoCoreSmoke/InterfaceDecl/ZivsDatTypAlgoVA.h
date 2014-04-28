
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

// 状态码
typedef enum
{
	ZIVS_STATUS_SUCCESS				= 0x00000000,
	ZIVS_STATUS_COMMAND				= 0x00010000,
	ZIVS_STATUS_ERROR				= 0x00080000,
	ZIVS_STATUS_ERROR_NOT_FOUND		= 0x00080001,
	ZIVS_STATUS_ERROR_NOT_SUPPORTED	= 0x00080002
} ZIVS_STATUS;

// 操作通用数据
typedef struct
{
	uint32_t	size;							// 数据包长度
	uint32_t	type;							// 类型
	uint32_t	status;							// 状态
	uint32_t	channel;						// 通道号
	uint32_t	time;							// 时间
	uint32_t	date;							// 日期
	uint32_t	id;								// 标识
	uint32_t	level;							// 警报级别
} ZIVS_OPER_DATA;


///////////////////////////////////////////////////////////////////////////////////////////////////
// 控制相关数据类型

// 控制类型
typedef enum
{
	ZIVS_CONTROL_TYPE_BASE = 0x1000,

	ZIVS_CONTROL_TYPE_VDR_Arm			= 0x1000,	// 启动警戒
	ZIVS_CONTROL_TYPE_VDR_Disarm		= 0x1001,	// 解除警戒
	ZIVS_CONTROL_TYPE_VDR_ClearAlarm	= 0x1002,	// 清除警报

	ZIVS_CONTROL_TYPE_PTZ_EnterPTZMode	= 0x1100,	// 进入PTZ模式
	ZIVS_CONTROL_TYPE_PTZ_ExitPTZMode	= 0x1101,	// 退出PTZ模式
	ZIVS_CONTROL_TYPE_PTZ_Control		= 0x1102,	// PTZ相关控制
	
	ZIVS_CONTROL_TYPE_END
} ZIVS_CONTROL_TYPE;

typedef union
{
	uint8_t buffer[BUF_SIZE_CONTROL];
} ZIVS_CONTROL_DATA_INTERNAL;

typedef struct
{
	ZIVS_OPER_DATA head;						// 操作头
	ZIVS_CONTROL_DATA_INTERNAL data;			// 控制数据
} ZIVS_CONTROL_DATA;

// 控制操作相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// 事件相关数据类型

// 事件数据格式

typedef enum
{
	ZIVS_EVENT_TYPE_BASE = 0x2000,

	ZIVS_EVENT_TYPE_EVENT	= 0x2000,		// 事件集合
	
	ZIVS_EVENT_TYPE_END
} ZIVS_EVENT_TYPE;

typedef union
{
	uint8_t buffer[BUF_SIZE_EVENT];
	VAEVT_ITEM	data4Event;					// 事件集合
} ZIVS_EVENT_DATA_INTERNAL;

typedef struct
{
	ZIVS_OPER_DATA head;						// 操作头
	ZIVS_EVENT_DATA_INTERNAL data;				// 事件数据
} ZIVS_EVENT_DATA;

// 事件相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////
// 视频处理相关数据类型

// 视频处理类型
typedef enum
{
	ZIVS_VPRO_TYPE_BASE = 0x3000,

	ZIVS_VPRO_TYPE_TARGET_SET	= 0x3000,		// 视频分析目标

	ZIVS_VPRO_TYPE_END
} ZIVS_VPRO_TYPE;

// 视频处理数据格式

typedef union
{
	uint8_t buffer[BUF_SIZE_VPRO];
	VATGT_SET	data4Targets;					// 目标集合
} ZIVS_VPRO_DATA_INTERNAL;

typedef struct
{
	ZIVS_OPER_DATA head;						// 操作头
	ZIVS_VPRO_DATA_INTERNAL	data;				// 视频处理数据
} ZIVS_VPRO_DATA;

// 视频处理相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// 配置相关数据类型

typedef enum
{
	ZIVS_CONFIG_TYPE_BASE = 0x4000,

	ZIVS_CONFIG_TYPE_SetVideoSourceMode							= 0x4100,	// 视频输入制式
	ZIVS_CONFIG_TYPE_GetVideoSourceMode							= 0x4101,
	ZIVS_CONFIG_TYPE_SetSysTime									= 0x4102,	// 系统时间
	ZIVS_CONFIG_TYPE_GetSysTime									= 0x4103,
	ZIVS_CONFIG_TYPE_SetSecretCode								= 0x4104,	// 获取系统的加密芯片值
	ZIVS_CONFIG_TYPE_GetSecretCode								= 0x4105,

	ZIVS_CONFIG_TYPE_SetVideoAnalysisFuncode					= 0x4700,	// 算法功能码
	ZIVS_CONFIG_TYPE_GetVideoAnalysisFuncode					= 0x4701,
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVersionIVP					= 0x4703,	// 算法版本
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVersionFSD					= 0x4705,
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVersionCRD					= 0x4707,
	ZIVS_CONFIG_TYPE_SetVideoAnalysisCLBR						= 0x470E,	// 视频分析场景(CLBR)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisCLBR						= 0x470F, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisSceneIVP					= 0x4710,	// 视频分析场景(IVP)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisSceneIVP					= 0x4711, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisSceneFSD					= 0x4712,	// 视频分析场景(FSD)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisSceneFSD					= 0x4713, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisSceneCRD					= 0x4714,	// 视频分析场景(CRD)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisSceneCRD					= 0x4715, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceIVProcessor	= 0x4720,	// IVP高级参数(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceIVProcessor	= 0x4721, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceDetection		= 0x4722,	// 检测模块高级参数(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceDetection		= 0x4723, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceTrack			= 0x4724,	// 跟踪模块高级参数(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceTrack			= 0x4725,
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceClassfier		= 0x4726,	// 分类模块高级参数(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceClassfier		= 0x4727,
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceAnalyst		= 0x4728,	// 分析模块高级参数(ADV)     
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceAnalyst		= 0x4729,
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvancePTZ			= 0x472A,	// PTZ高级参数(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvancePTZ			= 0x472B, 
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceFire			= 0x4730,	// 烟火检测模块高级参数(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceFire			= 0x4731,               
	ZIVS_CONFIG_TYPE_SetVideoAnalysisVAParaAdvanceCRD			= 0x4740,	// CRD(ADV)
	ZIVS_CONFIG_TYPE_GetVideoAnalysisVAParaAdvanceCRD			= 0x4741,               

	ZIVS_CONFIG_TYPE_END
} ZIVS_CONFIG_TYPE;

// 配置数据格式

typedef union  
{
	uint8_t buffer[BUF_SIZE_CONFIG];
} ZIVS_CONFIG_DATA_INTERNAL;

typedef struct  
{
	ZIVS_OPER_DATA head;				// 操作头
	ZIVS_CONFIG_DATA_INTERNAL data;		// 配置数据
} ZIVS_CONFIG_DATA;


#ifdef __cplusplus
}
#endif


#endif


