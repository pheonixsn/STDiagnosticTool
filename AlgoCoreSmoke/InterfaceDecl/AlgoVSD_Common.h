
#ifndef _ALGOVSD_COMMON_H_
#define _ALGOVSD_COMMON_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


#if defined(VSDAPI_EXPORTS)
#define VSD_EXPORTS __declspec(dllexport)
#elif defined(VSDAPI_IMPORTS)
#define VSD_EXPORTS __declspec(dllimport)
#else
#define VSD_EXPORTS extern
#endif
/*
// 图像标识位
enum
{
	IMGFLG_USED4ALL		= 0x00,		// 用于所有
	IMGFLG_USED4FIRE	= 0x01,		// 用于火
	IMGFLG_USED4SMOKE	= 0x02		// 用于烟
};

*/
#ifdef __cplusplus
}
#endif


#endif
