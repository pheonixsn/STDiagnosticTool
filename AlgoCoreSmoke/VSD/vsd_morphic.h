
#ifndef __VSD_MORPHIC_H__
#define __VSD_MORPHIC_H__
#include "vsd_common.h"
#include "vsd_datatype.h"


extern void		vsImageDilate(const UINT8 * RESTRICT data_src,
							  UINT8 * RESTRICT data_dst, 
							 UINT8 * RESTRICT bitbuf1, 
							 UINT8 * RESTRICT bitbuf2,
							const UINT8 * RESTRICT mask, 
							VSDET_SIZE * frame_size);

extern void		vsImageErode(const UINT8 * RESTRICT data_src, 
							 UINT8 * RESTRICT data_dst, 
							 UINT8 * RESTRICT bitbuf1,
							 UINT8 * RESTRICT bitbuf2,
							const UINT8 * RESTRICT mask, 
							VSDET_SIZE * frame_size);

extern	void	vsDelNoise(const UINT8 * RESTRICT SrcFrame, 
						   UINT8 * RESTRICT DstFrame, 
						   VSDET_SIZE * frame_size);
#endif
