
#ifndef _ZIVS_PACKET_COMMON_H_
#define _ZIVS_PACKET_COMMON_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


#define EDITION_ONE 1
// #define SUBSAMPLE_GRAYIMAGE_PACKET

int32_t COM_PacketInteger( uint32_t nVal, void *pData );
int32_t COM_UnPacketInteger( void *pData, uint32_t *pVal );

int32_t COM_PacketZDatBuf( ZDATBUF *pDB, void *pData );
int32_t COM_UnPacketZDatBuf( void *pData, ZDATBUF *pDB );


#ifdef __cplusplus
}
#endif


#endif

