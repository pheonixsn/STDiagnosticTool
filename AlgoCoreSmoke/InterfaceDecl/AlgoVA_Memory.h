
#ifndef _ALGOVA_MEMORY_H_
#define _ALGOVA_MEMORY_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// �ڴ���������������

#define VAMEM_ITEM_CNT	4

typedef enum
{
	VAMEM_TYPE_IRAM = 0,
	VAMEM_TYPE_ERAM
} VAMEM_TYPE;

typedef struct 
{
	uint32_t size;
	uint32_t type;
	void *mem;
} VAMEM_ITEM;

typedef struct 
{
	uint32_t funcode;
	uint32_t img_w, img_h;
	uint32_t mem_num;
	VAMEM_ITEM mems[VAMEM_ITEM_CNT];
} VAMEM_SET;

VA_EXPORTS void VAMEMS_alloc( VAMEM_SET *vamems );
VA_EXPORTS void VAMEMS_free( VAMEM_SET *vamems );


// �ڴ���������������
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
