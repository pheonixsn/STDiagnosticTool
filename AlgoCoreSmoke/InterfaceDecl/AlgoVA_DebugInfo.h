
#ifndef _ALGOVA_DEBUGINFO_H_
#define _ALGOVA_DEBUGINFO_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif

enum
{
	DBGINFO_DATETYPE_TXT=0x40000000,
	DBGINFO_DATETYPE_BIN=0x80000000
};

// 调试信息数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////
#define VADBGTXT_BUFLEN	(1024*4)

typedef struct 
{
	int8_t 		dbgtxt[VADBGTXT_BUFLEN];
	GRAYIMAGE 	*image_out;
	int32_t		type;		//功能码
	int32_t		length;		//dbgtxt长度
	int32_t		mode;		//log保存类型
	int32_t		reserve; 	//扩展用
} VADEBUGINFO;

#ifdef __cplusplus
}
#endif


#endif
