#ifndef __VSD_BACKGROUND_H__
#define __VSD_BACKGROUND_H__

#include "vsd_common.h"
#include "vsd_datatype.h"
//#include "vsd_ifilter.h"
#include "vsd_regionprc.h"
#include "vsd_frameprc.h"
#include "vsd_imganalyse.h"

#ifdef __cplusplus
extern "C" {
#endif


extern  void	vsTulBakUpdata(UINT8* Bak,
							   UINT8* CurH, 
							   UINT8* BakCount, 
							   UINT8 CountTh,
							   BOOL set, 
							   VSDET_SIZE* frame_size
							   );

extern  void	vsTulBakUpdataAll(UINT8* Bak,
								  UINT8* CurH,
								  VSDET_SIZE* frame_size
								  );

extern  BOOL	vsTulBakFinish(VSD_GLOBAL_VAR *vsd_var, 
							   UINT8 numFrame,
							   VSDET_SIZE *frame_size
							   );

#ifdef __cplusplus
}
#endif

#endif
