
#ifndef _VA_MEMMGR_H_
#define _VA_MEMMGR_H_

#include "AlgoVA_Memory.h"


#ifdef __cplusplus
extern "C"
{
#endif


struct tagMEM_NODE
{
	struct tagMEM_NODE *pre, *next;
	int8_t *mem_start, *mem_end;
	int8_t used;
};
typedef struct tagMEM_NODE MEM_NODE_T;

typedef struct
{
	int8_t *mem_addr;
	int32_t mem_len;
	MEM_NODE_T *nodes;
	MEM_NODE_T **nodep;
	int32_t node_num, node_avail, node_min, mem_used, mem_max;
	MEM_NODE_T *p_mem_node_head;
} MEM_MGR_T;

typedef enum
{
	MEMBLK_TYPE_FAST = 0,
	MEMBLK_TYPE_SLOW,
	MEMBLK_TYPE_MMGR,
	MEMBLK_NUM = MEMBLK_TYPE_MMGR
} MEMBLK_TYPE;

typedef struct 
{
	uint32_t nodnum[MEMBLK_NUM];
	uint32_t nodsize;
	void *nodmem;
} ZMMGRREQ;

typedef struct 
{
	MEM_MGR_T memmgrs[MEMBLK_NUM];
} ZMEMMGR;

VA_EXPORTS void MM_GetMgrReq( ZMMGRREQ *req );
VA_EXPORTS void MM_Initialize( ZMEMMGR *mgr, ZMMGRREQ *nreq, VAMEM_SET *mreqs );
VA_EXPORTS void MM_Terminate( ZMEMMGR *mgr );
VA_EXPORTS void *MM_Alloc( ZMEMMGR *mgr, MEMBLK_TYPE memtyp, int32_t sz );
VA_EXPORTS void MM_Free( ZMEMMGR *mgr, MEMBLK_TYPE memtyp, void *p );


#ifdef __cplusplus
}
#endif


#endif
