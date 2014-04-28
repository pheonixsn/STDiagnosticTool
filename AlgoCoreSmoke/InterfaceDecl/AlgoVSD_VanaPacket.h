
#ifndef _ALGOVSD_VANALYSIS_PACKET_H_
#define _ALGOVSD_VANALYSIS_PACKET_H_

#include "AlgoVSD_Vana.h"
#include "AlgoVA_VanaPacket.h"


#ifdef __cplusplus
extern "C"
{
#endif


VSDS_EXPORTS int32_t VSD_CheckVanaValid( ZDATBUF *pBuf, uint32_t *penacode );

VSDS_EXPORTS int32_t VSD_PackVana( VSD_VANALYSIS *pVana, ZDATBUF *pBuf );
VSDS_EXPORTS int32_t VSD_UnpackVana( ZDATBUF *pBuf, VSD_VANALYSIS *pVana );

VSDS_EXPORTS int32_t VSD_PackVanaBuffer( VSD_VANALYSIS *vana, ZDATBUF *buf_v, ZDATBUF *buf_z );
VSDS_EXPORTS int32_t VSD_UnpackVanaBuffer( ZDATBUF *buf_v, ZDATBUF *buf_z, VSD_VANALYSIS *vana );

VSDS_EXPORTS int32_t VSD_PackVanaFile( VSD_VANALYSIS *vana, char *fil_v, char *fil_z, void *mmgr );
VSDS_EXPORTS int32_t VSD_UnpackVanaFile( char *fil_v, char *fil_z, VSD_VANALYSIS *vana, void *mmgr );

VSDS_EXPORTS int32_t VSD_DefaultVana( char *str_v, VSD_VANALYSIS *vana, void *mmgr );

VSDS_EXPORTS char *par_vana_vsd;


#ifdef __cplusplus
}
#endif


#endif

