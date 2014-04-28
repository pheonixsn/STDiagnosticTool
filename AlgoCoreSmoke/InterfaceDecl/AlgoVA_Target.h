
#ifndef _ALGOVA_TARGET_H_
#define _ALGOVA_TARGET_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// 目标相关数据类型

#define MAX_VATGT_CNT			64

// 目标类型
enum
{
	VATGT_TYPE_UNKNOWN			= 0x00000000	// 未知类型
};

// 目标事件
enum
{
	VATGT_EVENT_UNKNOWN			= 0x00000000	// 未知事件
};

// 目标状态
enum
{
	VATGT_STATUS_UNKNOWN		= 0x00000000	// 未知状态
};

// 目标轨迹
#define MAX_VATRAJECT_LEN	40
typedef struct
{
	int32_t length;						// 轨迹长度
	ZPOINT	points[MAX_VATRAJECT_LEN];	// 轨迹点数组
} VATGT_TRAJECT;

// 目标数据
#define BUFLEN_VATGT_ITEM	256
#define BUFLEN_VATGT_DATA	(BUFLEN_VATGT_ITEM-(sizeof(uint32_t)*4+sizeof(ZPOINT)+sizeof(ZRECT)))
typedef struct
{
	uint32_t	id;						// ID
	uint32_t	status;					// 状态
	uint32_t	type;					// 类型
	uint32_t	event;					// 事件
	ZPOINT		point;					// 位置
	ZRECT		rect;					// 区域
	uint8_t		data[BUFLEN_VATGT_DATA];
} VATGT_ITEM;

// 目标集合
typedef struct
{
	int32_t	target_num;					// 目标数目
	VATGT_ITEM	targets[MAX_VATGT_CNT];	// 目标数据
} VATGT_SET;

// 目标相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
