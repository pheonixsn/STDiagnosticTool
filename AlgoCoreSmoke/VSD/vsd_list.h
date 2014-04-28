#ifndef __VSD_LIST_H__
#define __VSD_LIST_H__

#include "vsd_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vs_List
{
	INT32	uint_used, uint_size, uint_alloc;
	void 	**uint_data_p;
	UINT8 	*uint_data;
}vsLIST, *vf_LPLIST;


vsLIST * vsListCreate( UINT8 *buffer, INT32 uint_num, INT32 uint_size);

void *vsListGetItem(vsLIST* list, INT32 uint_index);

void *vsListAddItem(vsLIST* list, int * index_item);

BOOL vsListDelItem(vsLIST *list, INT32 uint_index);

BOOL vsListExchange(vf_LPLIST LPLIST, int index1, int index2);

//Çå¿ÕÁ´±í
void vsListDelAll(vsLIST *list);

#ifdef __cplusplus
}
#endif

#endif
