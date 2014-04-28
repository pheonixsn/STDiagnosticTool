
#ifndef _VSD_PROCESSOR_I_H_
#define _VSD_PROCESSOR_I_H_

#include "vsd_common.h"
#include "vsd_datatype.h"

 
#ifdef __cplusplus
extern "C"
{
#endif


typedef struct
{
	uint32_t			width;
	uint32_t			height;
	HWRESOURCE			m_sHwRes;			//通道；
	VA_PARA				*m_pVapara;			//全局参数；
    VSD_GLOBAL_VAR		*vsdet_buffer_var;	/* buffer used in algorithm */
	VSDET_PARA			*vsdet_para;
#ifdef DEBUG_VSD
	VATGT_SET			*pVatgts;			//							
#endif
} MODULE_VSD;




#ifdef __cplusplus
}
#endif


#endif

