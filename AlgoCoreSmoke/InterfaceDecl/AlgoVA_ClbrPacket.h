
#ifndef _ALGOVA_CLBR_PACKET_H_
#define _ALGOVA_CLBR_PACKET_H_

#include "AlgoVA_Calibration.h"


#ifdef __cplusplus
extern "C"
{
#endif


CLBRS_EXPORTS int32_t VA_CheckClbrValid( ZDATBUF *pBuf, uint32_t *penacode );

CLBRS_EXPORTS int32_t VA_PackClbr( CALIBRATION *pClbr, ZDATBUF *pBuf );
CLBRS_EXPORTS int32_t VA_UnpackClbr( ZDATBUF *pBuf, CALIBRATION *pClbr );

CLBRS_EXPORTS int32_t VA_PackClbrBuffer( CALIBRATION *clbr, ZDATBUF *buf_v, ZDATBUF *buf_z );
CLBRS_EXPORTS int32_t VA_UnpackClbrBuffer( ZDATBUF *buf_v, ZDATBUF *buf_z, CALIBRATION *clbr );

CLBRS_EXPORTS int32_t VA_PackClbrFile( CALIBRATION *clbr, char *fil_v, char *fil_z, void *mmgr );
CLBRS_EXPORTS int32_t VA_UnpackClbrFile( char *fil_v, char *fil_z, CALIBRATION *clbr, void *mmgr );

CLBRS_EXPORTS int32_t VA_DefaultClbr( char *str_v, CALIBRATION *clbr, void *mmgr );

CLBRS_EXPORTS char *par_clbr_ps1;


#ifdef __cplusplus
}
#endif


#endif

