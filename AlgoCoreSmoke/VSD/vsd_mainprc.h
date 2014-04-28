#ifndef __VSD_MAINPRC_H__
#define __VSD_MAINPRC_H__

#include "vsd_datatype.h"
#include "vsd_list.h"
//#include "vsd_ifilter.h"
#include "vsd_regionprc.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _TIDSP

extern int ConPrintf(const char *format, ...);

#endif

extern BOOL VSDPrc_IndoorSmoke(VSDET_PARA * vsd_para, VSD_GLOBAL_VAR * vsd_var, YUVIMAGE422 * image_yuv);

extern BOOL VSDPrc_TunnelSmoke(VSDET_PARA * vsd_para, VSD_GLOBAL_VAR * vsd_var, YUVIMAGE422 * image_yuv);

#ifdef __cplusplus
}
#endif

#endif	//__FS_SMOKE_PROCESS_H__
