#ifndef __VSD_PARSE_PARA_H__
#define __VSD_PARSE_PARA_H__


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vsd_datatype.h"

#ifdef __cplusplus
extern "C" {
#endif

extern BOOL parse_vsd_parabuffer( char *para_buffer, int buffer_length, VSDET_PARA *vsdet_para );
extern BOOL parse_vsd_svmpara( VAPARA_ADVANCE adv_buffer, VSDET_PARA *vsdet_para);
extern void vsd_scene_get(VSD_SCENE * scene, VSDET_PARA * vsd_para);

#ifdef __cplusplus
}
#endif

#endif	


