
#ifndef _VA_COMMON_H_
#define _VA_COMMON_H_

#include "AlgoVA_IF.h"
#include "va_memmgr.h"


#ifdef __cplusplus
extern "C"
{
#endif


#ifdef _TIDSP
#define VA_ASSERT(x)
#define RESTRICT restrict
#else
#define VA_ASSERT(x) ( assert(x) )
#define RESTRICT
#endif

typedef struct  
{
	ZMEMMGR mem_mgr;
	IDMACHS idma_chs;
} HWRESOURCE;


#ifdef __cplusplus
}
#endif


#endif
