#ifndef __VSD_OPTFLOWPROC_H__
#define  __VSD_OPTFLOWPROC_H__

#ifdef __cplusplus
extern "C"
{
#endif


#include "vsd_common.h"

/*
 *	�������²���
 */
typedef struct
{
	UINT8 txAngle; //[1,90],40���Ƕ�һ������ֵ

	UINT8 txCount; //[1,8],2, ͳ�ƹ���һ������ʷ���ݵ���ֵ1
	UINT8 fxCount; //[1,8],5��ͳ�ƹ���һ������ʷ���ݵ���ֵ2

	UINT8 txAdd;    //[4,24],14������level�ĸ���ֵ
	UINT8 fxSub;	//[4,24],14������level�ĸ���ֵ
}SMOKE_OPTUPDATE;

extern  void vsCalOptFlow(
							short * frame_diff,         //����
							short * pre_frame_diff,		//	
							short * vx,					//�ٶ�
							short * vy,
							short * dsx,				//�ݶ�
							short * dsy,				//
							short * dst,		
							short * vxavg,
							short * vyavg,
							short * powtemp,
							int interval,
							VSDET_SIZE * frame_size		//
					);


extern void vsCalOrt(INT16 * vx, 
					 INT16 * vy, 
					 UINT8 * ort, 
					 UINT32 minValue,  
					 VSDET_SIZE * frame_size);

extern void vsOptUpdateLevel(UINT8* curort, 
							 UINT8* bkort, 
							 UINT8 * orthist, 
							 UINT8 * count0, 
							 UINT8* level, 
							 SMOKE_OPTUPDATE * pOptUpdate, 
							 VSDET_SIZE* frame_size
							 );

#ifdef __cplusplus
}
#endif

#endif
