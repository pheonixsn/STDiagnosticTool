
#ifndef _ALGOVSD_TARGET_H_
#define _ALGOVSD_TARGET_H_

#include "AlgoVA_Target.h"
#include "AlgoVSD_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// 目标相关数据类型

#define VATGT_ID_VSD_MIN		0x80000000
#define VATGT_ID_VSD_MAX		0x8FFFFFFF
	
// 目标类型
enum
{
//	VATGT_TYPE_FIRE				= 0x00000011,	// 火
	VATGT_TYPE_SMOKE			= 0x00000012	// 烟
};

// 目标事件
enum
{
//	VATGT_EVENT_FIRE			= 0x10000000,	// 火情
	VATGT_EVENT_SMOKE			= 0x20000000	// 烟雾
};
/*
typedef struct 
{
	int32_t	reserved;							// 
} FSDTGT_DATA_FIRE;
*/
typedef struct 
{
	int32_t	reserved;							// 
} VSDTGT_DATA_SMOKE;

typedef union 
{
//	FSDTGT_DATA_FIRE	fire;
	VSDTGT_DATA_SMOKE	smoke;
} VSDTGT_DATA;

// 目标相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
