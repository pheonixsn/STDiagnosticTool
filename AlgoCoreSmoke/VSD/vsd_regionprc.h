#ifndef __VSD_REGIONPRC_H__
#define __VSD_REGIONPRC_H__

#include <stdlib.h>
#include <math.h>
#include "vsd_datatype.h"
#include "vsd_list.h"
//#include "vsd_ifilter.h"
#ifdef __cplusplus
extern "C" {
#endif

#define REGION_COR_MAX		4



extern BOOL vsDelRegIncluded(vsLIST * list_region_temp);

extern BOOL vsOrderRegArea(vsLIST * list_region);


extern BOOL vsCalRegArea(vsLIST * list_region, UINT8 * RegMask, VSDET_SIZE * frame_size);

extern BOOL vsRegionCombine(vsLIST * list_region_temp);


extern void vsCpyRegionAware(VSD_REGION_TEMPORAL * cur_region, 
							 const UINT8 * RESTRICT srcmask, 
							 UINT8 * RESTRICT dstmask, 
							 VSDET_SIZE * frame_size);

extern void vsCpyRegionValue(VSD_REGION_TEMPORAL * cur_region, 
							 const UINT8 * RESTRICT srcmask, 
							 UINT8 * RESTRICT dstmask, 
							  UINT8 * RESTRICT sign,
							  INT8 add,
							  UINT8 value, 
							  VSDET_SIZE * frame_size);

extern BOOL vsUpdateRegSmoke(vsLIST * list_region_smoke, 
							 vsLIST * list_region_temp, 
							 VSDET_SIZE * frame_size);

extern void vsDelSmallRegion(vsLIST * list_region, int Area);
extern void vsDelMarkRegion(vsLIST * list_region, int Area);

extern void vsGetSmokeReg(vsLIST* listtemp, UINT8* initreg, UINT8* finReg, VSDET_SIZE * frame_size);

extern void vsRegConOut(vsLIST **track, int tracklength, int avgNetP);

extern void vsRegMatch(vsLIST* cur_list, vsLIST* pre_list, vsLIST **track);
extern int vsReg2Debug(vsLIST **track, UINT8* pDst, int tracklength, int avgNetP, int comdug, UINT32 curtime);
extern void vsAddEspReg(vsLIST * list_smoke, int num, int prepi, VSDET_SIZE * frame_size);
extern void vsSetTrack(vsLIST **track, int num);

#ifdef WIN32

extern void vsTulConOut(VSD_GLOBAL_VAR * vsd_var, BOOL outFile);
extern void vsIndConOut(VSD_GLOBAL_VAR * vsd_var, BOOL outFile);

#endif
void vsComOutPara(VSDET_PARA *para);

#ifdef __cplusplus
}
#endif

#endif	//__FS_FILTER_REGION_H__

