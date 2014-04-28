
#ifndef _ALGOVSD_PARAM_H_
#define _ALGOVSD_PARAM_H_

#include "AlgoVA_Param.h"
#include "AlgoVSD_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// 参数配置相关数据类型

enum
{
	VPARAADVBUFNUM_VSD,
	VPARAADVBUFNUM_VSD_CLASS_1,
	VPARAADVBUFNUM_VSD_CLASS_2,
	VPARAADVBUFNUM_VSD_CLASS_3,
	VPARAADVBUFNUM_VSD_CLASS_4,
	VPARAADVBUFNUM_VSD_CLASS_5,
	VPARAADVBUFNUM_VSD_CLASS_6,
	VPARAADVBUFNUM_VSD_CLASS_7,
	VPARAADVBUFNUM_VSD_CLASS_8,
	VPARAADVBUFNUM_VSD_CLASS_9,
	VPARAADVBUFNUM_VSD_CLASS_10,
	VPARAADVBUFNUM_VSD_MAX
};

VSD_EXPORTS void VSD_InitParaAdvance( VAPARA_ADVANCE *para, VAPARA_STRARRAY *strarray, void *mmgr );
VSD_EXPORTS void VSD_InitParaScene( VAPARA_SCENE *para, 
								   VAPARA_STRARRAY *strarray,
									int32_t img_w, 
									int32_t img_h, 
									void *mmgr 
									);
VSD_EXPORTS void VSD_InitParaVAPARA( VAPARA *vapara,
									VAPARA_STRARRAY *scnfil,
									VAPARA_STRARRAY *advfil, 
									int32_t img_w, 
									int32_t img_h, 
									void *mmgr 
									);


// 参数配置相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
