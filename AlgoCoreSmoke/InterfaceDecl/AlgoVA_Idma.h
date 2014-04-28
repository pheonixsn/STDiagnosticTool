
#ifndef _ALGOVA_IDMA_H_
#define _ALGOVA_IDMA_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// IDMA相关数据类型

#ifdef _TIDSP
#include <std.h>
#include <limits.h>
#include <idma2.h>
#include <acpy2.h>
#endif

enum
{
	IDMA_CHANNEL0 = 0,
	IDMA_CHANNEL1,
	IDMA_CHANNEL2,
	IDMA_CHANNEL3,
	NUM_LOGICAL_CH
};

typedef struct
{
	uint32_t ch_num;
#ifdef _TIDSP
    IDMA2_ChannelRec dma_ch_recs[NUM_LOGICAL_CH];
#endif
} IDMACHS;

// IDMA相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
