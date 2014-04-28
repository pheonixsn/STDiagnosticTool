
#ifndef _ALGOVA_COMMAND_H_
#define _ALGOVA_COMMAND_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// 命令相关数据类型

#define MAX_VACMD_CNT			4

enum
{
	VACMD_TYPE_UNKNOWN			= 0x00000000// 未知类型
};

#define BUFLEN_VACMD_ITEM		64
#define BUFLEN_VACMD_DATA		(BUFLEN_VACMD_ITEM-sizeof(uint32_t)*1)
typedef struct 
{
	uint32_t	type;						// 命令类型
	uint8_t		data[BUFLEN_VACMD_DATA];
} VACMD_ITEM;

typedef struct 
{
	int32_t	cmd_num;						// 命令数目
	VACMD_ITEM	commands[MAX_VACMD_CNT];	// 命令数据
} VACMD_SET;

// 命令相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
