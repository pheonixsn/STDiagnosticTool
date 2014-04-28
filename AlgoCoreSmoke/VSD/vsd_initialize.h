

#ifndef __VSD_INITIALIZE_H__
#define __VSD_INITIALIZE_H__

#include "vsd_common.h"
#include "vsd_processor_i.h"
#include "vsd_list.h"
#include "vsd_datatype.h"
//#include "fs_filter_block.h"

#ifdef __cplusplus
extern "C" {
#endif
	

extern void initialize_gloablvar_vsd(VSD_GLOBAL_VAR * global_var, uint32_t image_width, uint32_t image_height, ZMEMMGR * mgr);

extern BOOL VsdetFilterClear(VSD_GLOBAL_VAR * global_var, INT32 img_width, INT32 img_height);

extern BOOL	vsd_globalvar_Terminate(VSD_GLOBAL_VAR * global_var, uint32_t img_width, uint32_t img_height, ZMEMMGR * mgr);

extern void init_advance_vsd(VSDET_PARA * adv_para,  ZMEMMGR * mgr);
extern BOOL vsd_advance_Terminate(VSDET_PARA * adv_para,  ZMEMMGR * mgr);


#ifdef __cplusplus
}
#endif

#endif

