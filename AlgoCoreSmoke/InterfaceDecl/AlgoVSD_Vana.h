
#ifndef _ALGOVSD_VANA_H_
#define _ALGOVSD_VANA_H_

#include "AlgoVA_Vana.h"
#include "AlgoVSD_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


#if defined(VSDSAPI_EXPORTS)
#define VSDS_EXPORTS __declspec(dllexport)
#elif defined(VSDSAPI_IMPORTS)
#define VSDS_EXPORTS __declspec(dllimport)
#else
#define VSDS_EXPORTS extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// 分析相关数据类型

#define SCENE_VSD_VERSION	ZANB_MAKE_VERSION( 'R', 'F', 0x41, 0 )

// 分析参数
// 烟雾检测参数
typedef struct
{
	uint8_t smoke_sens;					// 检测的灵敏度			
	uint8_t smoke_min_region;			// 最小烟雾区域
} VSD_VANALYSIS_PARA;

// 分析区域
typedef struct  
{
	int8_t name[NAME_BUF_SIZE];			// 区域名称
	uint32_t valid;						// 是否有效
	uint32_t enable;					// 是否使能
	uint32_t level;						// 警戒级别
	uint32_t mode;						// 分析模式
	VSD_VANALYSIS_PARA	para;			// 分析参数
} VSD_VANALYSIS_ZONE;
typedef struct  
{
	// 区域属性
	VSD_VANALYSIS_ZONE zone[MAX_NUM_VANALYSIS_ZONE]; 
	GRAYIMAGE image;					// 区域位图
} VSD_VANALYSIS_ZONES;

// 分析配置
typedef struct  
{
	uint32_t enacode;					// 使能标识
	int8_t name[NAME_BUF_SIZE];			// 场景名称
	VSD_VANALYSIS_ZONES zones;			// 分析区域
} VSD_VANALYSIS;

VSDS_EXPORTS VSD_VANALYSIS* VSDVANA_alloc( int32_t nImgW, int32_t nImgH, void *pMMgr );
VSDS_EXPORTS void VSDVANA_free( VSD_VANALYSIS *pVana, void *pMMgr );
VSDS_EXPORTS void VSDVANA_clone( VSD_VANALYSIS *pSrc, VSD_VANALYSIS *pDst );
VSDS_EXPORTS void VSDVANA_clear( VSD_VANALYSIS *pVana );
VSDS_EXPORTS int32_t VSDVANA_calculate( VSD_VANALYSIS *pVana, uint32_t flag );

VSDS_EXPORTS void VSDZONE_alloc( VSD_VANALYSIS_ZONE *pZone, int32_t nImgW, int32_t nImgH, void *pMMgr );
VSDS_EXPORTS void VSDZONE_free( VSD_VANALYSIS_ZONE *pZone, void *pMMgr );
VSDS_EXPORTS void VSDZONE_clear( VSD_VANALYSIS_ZONE *pZone );
VSDS_EXPORTS void VSDZONE_clone( VSD_VANALYSIS_ZONE *pSrc, VSD_VANALYSIS_ZONE *pDst );

// 分析相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif

