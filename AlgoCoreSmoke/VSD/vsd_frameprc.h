#ifndef __VSD_FRAMEPRC_H__
#define __VSD_FRAMEPRC_H__

#include <stdlib.h>
#include <math.h>
#include "vsd_common.h"
#include "vsd_datatype.h"
#include "vsd_list.h"
#include "vsd_regionprc.h"
#ifdef __cplusplus
extern "C" {
#endif


#define HI_LL(long) ( (long)>>32 )
#define LO_LL(long) ( (unsigned int)(long) )

//累加
typedef struct {
	UINT8 thrld_diff_v;
	UINT8 thrld_aware;
	UINT8 thrld_step_add;
	UINT8 thrld_step_sub;
	UINT8 thrld_aware_max;
} AWARE_PARA;

//检测区域不变参数
typedef struct NOCHANGE_PARA 
{
	int DiffTh;
	float ChangeRate;
	UINT8 Step;

}NOCHANGE_PARA;

extern BOOL vsFrameMask(UINT8 *	src_frame, 
						UINT8 *	mask_frame, 
						UINT8		*	RESTRICT dst_frame, 
						VSDET_SIZE	*	frame_size
						);

extern void vsFrameBinary(const UINT8 * RESTRICT frame_diff, 
						  UINT8 * RESTRICT frame_result, 
						  UINT8 thred, 
						  VSDET_SIZE * frame_size
						  );

extern BOOL VsZoneShieldY(YUVIMAGE422	* image_yuv, 
						  YUVIMAGE422 * image_yuv_buffer,
						  const UINT8 * zones_mask
						  );

extern BOOL vsFrameDiff16(const UINT8 * cur_frame, 
						  const UINT8 * pre_frame, 
						  INT16 * dst_frame, 
						  int subTh, 
						  VSDET_SIZE * frame_size 
						  );
						 
extern BOOL vsFrameDiff(const UINT8 * data_cur_frame, 
						const UINT8 * data_pre_frame, 
						UINT8 * diff_abs, 
						UINT8 * diff_signed, 
						VSDET_SIZE* frame_size
						);

extern BOOL vsIndRegUpdate(const UINT8 * cur_aware, 
						   UINT8 * aware_level, 
						   UINT8 * aware_mask, 
						   UINT8 * optlevel,
						 VSDET_SIZE * frame_size, 
						 AWARE_PARA * aware_para
						 );

extern BOOL vsIndRegUpdate2(const UINT8 * RESTRICT addsubv, 
							UINT8 * RESTRICT finlevel, 
							UINT8 * RESTRICT outmask, 
							UINT8* RESTRICT optlevel, 
							UINT8* sign, 
							VSDET_SIZE * frame_size, 
							UINT8 thred
							);

extern void vsAbsFrame(const UINT8 * RESTRICT frame1, 
					   const UINT8 * RESTRICT frame2, 
					   UINT8 * RESTRICT edge, 
					   VSDET_SIZE * frame_size
					   );

extern void vsUpdataBakCount(UINT8 * BakCount,  
							 UINT8* regmask, 
							 UINT8 BakValue1, 
							 UINT8 BakValue2, 
							 VSDET_SIZE* frame_size
							 );

extern void vsGetCorReg(vsLIST * list_temp, 
						UINT8* CorReg, 
						INT32 CorValue, 
						UINT8* mask, 
						VSDET_SIZE* frame_size
						);

extern void  vsUpdataCount(UINT8 * count, 
						   UINT8* cormask, 
						   UINT8 addValue, 
						   VSDET_SIZE* frame_size
						   );

extern void vsTulLevel(UINT8* srcmask, 
					   UINT8* level, 
					   AWARE_PARA *para, 
					   VSDET_SIZE* frame_size
					   );
extern void vsRefBakCount(UINT8 * count,  
						  UINT8 addValue, 
						  VSDET_SIZE* frame_size
						  );

extern void vsCalNoChgLevel(vsLIST * list_temp, 
							UINT8* cur, 
							UINT8* refimg,
							UINT8* nochglevel, 
							UINT8* mask,
							NOCHANGE_PARA pam,
							VSDET_SIZE* frame_size);


extern void vsDoubleFrameBin(UINT8* src, 
							 UINT8* bin1, 
							 UINT8* bin2, 
							 UINT8 th1, 
							 UINT8 th2, 
							 int* area1, 
							 int* area2, 
							 VSDET_SIZE * frame_size
							 );

extern void vsReduce(INT16* src, 
					 INT16* det, 
					 VSDET_SIZE* frame_size
					 );

extern void vsExpend(INT16* src, 
					 INT16* det, 
					 VSDET_SIZE* frame_size
					 );

extern BOOL vsFrameNot(	const UINT8 * RESTRICT src_frame, 
						UINT8 * RESTRICT dst_frame, 
						VSDET_SIZE * frame_size
						);
extern UINT32 vsFrameAvgValue(const UINT8 * RESTRICT src_frame, VSDET_SIZE * frame_size);
UINT32 vsFrameColor(const UINT8 * RESTRICT srcu, const UINT8 * RESTRICT srcv, VSDET_SIZE * frame_size);

int vsBlurBkKeepRatio(UINT8* RESTRICT cur_grad, UINT8* RESTRICT bk_grad, VSDET_SIZE* frame_size);
int vsBlurBkChangedRatio(UINT8* RESTRICT cur_grad, UINT8* RESTRICT bk_grad, VSDET_SIZE* frame_size, VSDET_ZPOINT lt_point, VSDET_SIZE reg_size);

int vsBlurHistEst(UINT8* RESTRICT cur_img, VSDET_SIZE* frame_size, VSDET_ZPOINT lt_point, VSDET_SIZE reg_size);

int vsBlurEst(VSDET_PARA * vsd_para, VSD_GLOBAL_VAR * vsd_var, VSDET_SIZE frame_size,int *reg_count);
#ifdef __cplusplus
}
#endif

#endif
