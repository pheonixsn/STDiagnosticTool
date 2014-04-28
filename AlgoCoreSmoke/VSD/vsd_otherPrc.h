#ifndef	 __VSD_OTHERPRC_H__
#define  __VSD_OTHERPRC_H__

#include "vsd_common.h"
#include "vsd_list.h"
#include "vsd_datatype.h"
#include "vsd_regionprc.h"

#ifdef __cplusplus
extern "C" {
#endif

extern BOOL VsdProcess_initialize(VSDET_PARA * vsd_para, VSD_GLOBAL_VAR * vsd_var, YUVIMAGE422 * image_yuv , UINT8 * zone_mask);
extern BOOL VsdetFilterGetTarget( VSDET_PARA * vsd_para, VSD_GLOBAL_VAR * vsd_var, VATGT_SET * target_set);
extern BOOL VsdetFilterGetEvent( VSDET_PARA * vsd_para, VSD_GLOBAL_VAR * vsd_var, VAEVT_SET * event_set);
extern INT8 vsNetoffset(UINT32 avg, UINT32 color, UINT8 offset);
extern void vsIndDebugOut(VSDET_PARA * vsd_para, VSD_GLOBAL_VAR * vsd_var, VSDET_SIZE * frame_size);
extern void vsSetDebugInfo(VSD_GLOBAL_VAR * vsd_var, VSDET_PARA * vsd_para, VADEBUGINFO* debuginfo);
#ifdef __cplusplus
}
#endif

#endif
