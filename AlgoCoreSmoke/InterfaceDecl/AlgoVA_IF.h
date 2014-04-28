
#ifndef _ALGOVA_IF_H_
#define _ALGOVA_IF_H_

#include "AlgoVA_Common.h"
#include "AlgoVA_Idma.h"
#include "AlgoVA_Memory.h"
#include "AlgoVA_Funcode.h"
#include "AlgoVA_Param.h"
#include "AlgoVA_Target.h"
#include "AlgoVA_Event.h"
#include "AlgoVA_Command.h"
#include "AlgoVA_Result.h"
#include "AlgoVA_DebugInfo.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// 接口相关数据类型

#define ALGIF_VA_VERSION	ZANB_MAKE_VERSION( 'R', 'V', 0x41, 0 )

typedef enum  
{
	VASTATUS_OK = 0,
	VASTATUS_SKIP,
	VASTATUS_FALSE,
	VASTATUS_UNSUPPORT
} VASTATUS;

typedef void *VAHANDLE;

#define VA_MODULE_DATLEN	256
typedef struct VA_OBJ
{
	uint8_t buffer[VA_MODULE_DATLEN];
} VA_OBJ;

typedef enum
{
	VAOPER_TYPE_GetVersion		= 0x0001,	// 获取版本信息
	VAOPER_TYPE_GetFuncode		= 0x0002,	// 获得功能码
	VAOPER_TYPE_GetMemReq		= 0x0008,	// 获得内存需求
	VAOPER_TYPE_GetDmaReq		= 0x0009,	// 获得DMA需求
	VAOPER_TYPE_CheckScene		= 0x000F,	// 检查场景数据包
	VAOPER_TYPE_Initialize		= 0x0010,	// 初始化模块
	VAOPER_TYPE_Terminate		= 0x0011,	// 终止模块
	VAOPER_TYPE_InitIdmaChs		= 0x0012,	// 设置DMA通道
	VAOPER_TYPE_ConfigParameter	= 0x0020,	// 配置参数
	VAOPER_TYPE_GetParameter	= 0x0021,	// 获取参数
	VAOPER_TYPE_GetEnacode		= 0x0022,	// 获得使能码
	VAOPER_TYPE_Start			= 0x0028,	// 启动模块
	VAOPER_TYPE_Stop			= 0x0029,	// 停止模块
	VAOPER_TYPE_ProcessImage	= 0x0030,	// 处理图像
	VAOPER_TYPE_GetResults		= 0x0034,	// 获取结果数据
	VAOPER_TYPE_GetDebugInfo	= 0x0040,	// 获取调试信息
	VAOPER_TYPE_DoSpecial		= 0x1000	// 模块特有操作
} VAOPER_TYPE;

typedef struct 
{
	uint32_t	type;						// 操作类型
	void		*data;						// 操作数据
} VAOPER;

VA_EXPORTS VASTATUS VA_GetVersion( VAHANDLE hModule, uint32_t *pVersion );
VA_EXPORTS VASTATUS VA_GetFuncode( VAHANDLE hModule, uint32_t *pFuncode );
VA_EXPORTS VASTATUS VA_GetMemReq( VAHANDLE hModule, VAMEM_SET *pVamems );
VA_EXPORTS VASTATUS VA_GetDmaReq( VAHANDLE hModule, IDMACHS *pIdmachs );
VA_EXPORTS VASTATUS VA_CheckScene( VAHANDLE hModule, VASCENE_CHK *pScnChk );
VA_EXPORTS VASTATUS VA_Initialize( VAHANDLE hModule, VAMEM_SET *pVamems );
VA_EXPORTS VASTATUS VA_Terminate( VAHANDLE hModule );
VA_EXPORTS VASTATUS VA_InitIdmaChs( VAHANDLE hModule, IDMACHS *pIdmachs );
VA_EXPORTS VASTATUS VA_ConfigParameter( VAHANDLE hModule, VAPARA *pVaparaE );
VA_EXPORTS VASTATUS VA_GetParameter( VAHANDLE hModule, VA_PARA **ppVaparaI );
VA_EXPORTS VASTATUS VA_GetEnacode( VAHANDLE hModule, uint32_t *pEnacode );
VA_EXPORTS VASTATUS VA_Start( VAHANDLE hModule );
VA_EXPORTS VASTATUS VA_Stop( VAHANDLE hModule, VARESULT *pVaresult );
VA_EXPORTS VASTATUS VA_ProcessImage( VAHANDLE hModule, YUVIMAGE422 *pImage );
VA_EXPORTS VASTATUS VA_GetResults( VAHANDLE hModule, VARESULT *pVaresult );
VA_EXPORTS VASTATUS VA_GetDebugInfo( VAHANDLE hModule, VADEBUGINFO *pVadbginfo );
VA_EXPORTS VASTATUS VA_DoSpecial( VAHANDLE hModule, VAOPER *pVaop );

typedef struct  
{
	char *mdlname;
	VASTATUS (*GetVersion)( VAHANDLE hModule, uint32_t *pVersion );
	VASTATUS (*GetFuncode)( VAHANDLE hModule, uint32_t *pFuncode );
	VASTATUS (*GetMemReq)( VAHANDLE hModule, VAMEM_SET *pVamems );
	VASTATUS (*GetDmaReq)( VAHANDLE hModule, IDMACHS *pIdmachs );
	VASTATUS (*CheckScene)( VAHANDLE hModule, VASCENE_CHK *pScnChk );
	VASTATUS (*Initialize)( VAHANDLE hModule, VAMEM_SET *pVamems );
	VASTATUS (*Terminate)( VAHANDLE hModule );
	VASTATUS (*InitIdmaChs)( VAHANDLE hModule, IDMACHS *pIdmachs );
	VASTATUS (*ConfigParameter)( VAHANDLE hModule, VAPARA *pVaparaE );
	VASTATUS (*GetParameter)( VAHANDLE hModule, VA_PARA **ppVaparaI );
	VASTATUS (*GetEnacode)( VAHANDLE hModule, uint32_t *pEnacode );
	VASTATUS (*Start)( VAHANDLE hModule );
	VASTATUS (*Stop)( VAHANDLE hModule, VARESULT *pVaresult );
	VASTATUS (*ProcessImage)( VAHANDLE hModule, YUVIMAGE422 *pImage );
	VASTATUS (*GetResults)( VAHANDLE hModule, VARESULT *pVaresult );
	VASTATUS (*GetDebugInfo)( VAHANDLE hModule, VADEBUGINFO *pVadbginfo );
	VASTATUS (*DoSpecial)( VAHANDLE hModule, VAOPER *pVaop );
} IVA_OBJ;

// 接口相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
