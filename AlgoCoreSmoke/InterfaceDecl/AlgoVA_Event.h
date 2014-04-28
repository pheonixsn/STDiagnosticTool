
#ifndef _ALGOVA_EVENT_H_
#define _ALGOVA_EVENT_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// 事件相关数据类型

#define MAX_VAEVT_CNT	128

// 事件类型
enum
{
	VAEVT_TYPE_UNKNOWN		= 0x00000000,	// 未知类型

	VAEVT_TYPE_Armed		= 0x00002000,	// 警戒启动
	VAEVT_TYPE_Disarmed		= 0x00002001,	// 警戒解除
	VAEVT_TYPE_AlarmCleared	= 0x00002002	// 警报清除
};

// 事件状态
typedef enum
{
	VAEVT_STATUS_NOSTA	= 0,				// 无状态
	VAEVT_STATUS_START	= 1,				// 开始
	VAEVT_STATUS_END	= 2					// 结束
} VAEVT_STATUS;

#define BUFLEN_VAEVT_ITEM	64
#define BUFLEN_VAEVT_DATA	(BUFLEN_VAEVT_ITEM-sizeof(uint32_t)*5)
typedef struct 
{
	uint32_t	type;						// 事件类型
	uint32_t	id;							// 事件标识
	uint32_t	level;						// 事件警报级别
	uint32_t	status;						// 事件状态
	uint32_t	zone;						// 事件发生区域
	uint8_t		data[BUFLEN_VAEVT_DATA];
} VAEVT_ITEM;

typedef struct 
{
	int32_t	event_num;						// 事件数目
	VAEVT_ITEM	events[MAX_VAEVT_CNT];		// 事件数据
} VAEVT_SET;

// 事件相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
