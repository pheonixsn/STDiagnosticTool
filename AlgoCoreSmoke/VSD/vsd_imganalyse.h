#ifndef __VSD_IMGANALYSE_H__
#define __VSD_IMGANALYSE_H__

#include <stdlib.h>
#include <math.h>
#include "vsd_datatype.h"
#include "vsd_list.h"

#ifdef __cplusplus
extern "C" {
#endif
	


extern BOOL vsFrameGradDirect(UINT8 * cur_v_buffer, 
							  VSDET_SIZE * frame_size, 
							  UINT8 * smoke_grad, 
							  UINT8 * smoke_grad_direct);

extern BOOL vsImgGrad(UINT8 * cur_v_buffer, 
					  VSDET_SIZE * frame_size, 
					  UINT8 * smoke_grad
					  );



extern void vsAvgSmooth(UINT8 * dst, 
						UINT8 * src, 
						VSDET_SIZE * frame_size
						);

extern void vsGaussSmooth(UINT8 * dst, 
						  UINT8 * src, 
						  VSDET_SIZE * frame_size
						  );

extern void vsGaussSmooth16(INT16 *dst, 
							INT16 *src, 
							VSDET_SIZE * frame_size
							);

extern void vsLawsGrad(UINT8* src, UINT8* dst, VSDET_SIZE* frame_size);

extern void vsLawsWave(UINT8* src, UINT8* dst, VSDET_SIZE* frame_size);

extern void vsCalLawsRip(UINT8* src, UINT8* dst, VSDET_SIZE* frame_size);
	
extern void vsCalHeightText(UINT8 * img_gd, UINT8 * img_htext, VSDET_SIZE * frame_size);


#ifdef __cplusplus
}
#endif

#endif


