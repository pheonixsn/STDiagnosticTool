#ifndef __VSD_CALCHARACT_H__
#define __VSD_CALCHARACT_H__

#include "vsd_frameprc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IndexCharacter
{
	UINT8 minValue;	//最小值
	UINT8 maxValue; //最大值
	UINT8 indS;		//第几个结构体
	UINT8 indN;		//第几个值
}IndexCharact;

typedef struct tulCht
{
	UINT8 contrast;
	UINT8 flat;
}tulCht;

extern BOOL vsCalCharacterIndoor(vsLIST			* list_region_temp,
								 VSD_GLOBAL_VAR * vsd_var, 
								 VSDET_SIZE		* frame_size
								 );
extern BOOL vsCalCharacterIndoor_sub(vsLIST			* list_region_temp,
								 VSD_GLOBAL_VAR * vsd_var, 
								 VSDET_SIZE		* frame_size
								 );

extern BOOL vsDelIndNoSmokeReg(vsLIST		* list_region_temp, 
							   UINT8		* hsv_mask, 
							   UINT8		* region_mask, 
							   UINT8		* sign,
							   INT8			  NNetOffset,
							   AWARE_PARA	  aware_para, 
							   VSDET_PARA	* vsd_para,
							   VSDET_SIZE	* frame_size
							   );


extern void vsCalCharacterTunnel(vsLIST			* list_temp, 
								 VSD_GLOBAL_VAR	* vsd_var, 
								 VSDET_SIZE		* frame_size
								 );

extern BOOL vsDelTulNoSmoke(vsLIST			* list_temp, 
							UINT8			* mask, 
							UINT8			* outobj, 
							UINT8			* updata,
							VSD_GLOBAL_VAR	* vsd_var,
							tulCht			  tul,
							VSDET_SIZE		* frame_size
							);

#ifdef __cplusplus
}
#endif

#endif	//__FS_SMOKE_CHARACT_H__

