
#ifndef _ALGOVSD_SCENE_H_
#define _ALGOVSD_SCENE_H_

#include "AlgoVA_Scene.h"
#include "AlgoVSD_Vana.h"
#include "AlgoVSD_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// 场景相关数据类型

// 场景模型
typedef struct
{
	VSD_VANALYSIS *vanalysis;			// 分析配置
} VSD_SCENE;

VSD_EXPORTS VSD_SCENE* VSDSCN_alloc( int32_t nImgW, int32_t nImgH, void *pMMgr );
VSD_EXPORTS void VSDSCN_free( VSD_SCENE *pScnModl, void *pMMgr );
VSD_EXPORTS void VSDSCN_clone( VSD_SCENE *pSrc, VSD_SCENE *pDst );

// 场景相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif

