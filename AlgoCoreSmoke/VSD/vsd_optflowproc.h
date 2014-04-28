#ifndef __VSD_OPTFLOWPROC_H__
#define  __VSD_OPTFLOWPROC_H__

#ifdef __cplusplus
extern "C"
{
#endif


#include "vsd_common.h"

/*
 *	光流更新参数
 */
typedef struct
{
	UINT8 txAngle; //[1,90],40，角度一致性阈值

	UINT8 txCount; //[1,8],2, 统计光流一致性历史数据的阈值1
	UINT8 fxCount; //[1,8],5，统计光流一致性历史数据的阈值2

	UINT8 txAdd;    //[4,24],14，光流level的更新值
	UINT8 fxSub;	//[4,24],14，光流level的更新值
}SMOKE_OPTUPDATE;

extern  void vsCalOptFlow(
							short * frame_diff,         //输入
							short * pre_frame_diff,		//	
							short * vx,					//速度
							short * vy,
							short * dsx,				//梯度
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
