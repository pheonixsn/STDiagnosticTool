#ifndef __VSD_EDGE2RECT_H__
#define __VSD_EDGE2RECT_H__

#include <stdlib.h>
#include <math.h>
#include "vsd_datatype.h"
#include "vsd_list.h"
#ifdef __cplusplus
extern "C" {
#endif
	

extern BOOL vsEdgeLink(
					vsLIST 	* list_region, 
					UINT8 		* pImageEdge, 
					VSDET_SIZE 	* frame_size, 
					int			nMiniLength
					);

#ifdef __cplusplus
}
#endif

#endif

