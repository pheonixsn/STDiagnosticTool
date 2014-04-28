
#ifndef _ALGOVA_ALGP_PACKET_H_
#define _ALGOVA_ALGP_PACKET_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


typedef int32_t (*FUNC_PKGALGP)( void *pAlgp, uint8_t *pData );
typedef int32_t (*FUNC_UPKALGP)( uint8_t *pData, void *pAlgp );

typedef int32_t (*FUNC_PKGALGPV)( void *algp, char *pardat, int32_t *parlen );
typedef int32_t (*FUNC_UPKALGPV)( char *pardat, int32_t parlen, void *algp );
typedef int32_t (*FUNC_PKGALGPZ)( void *algp, char *pardat, int32_t *parlen );
typedef int32_t (*FUNC_UPKALGPZ)( char *pardat, int32_t parlen, void *algp );

typedef int32_t (*FUNC_DFTALGPZ)( void *algp );

VA_EXPORTS int32_t VA_CheckSceneValid( ZDATBUF *pBuf, uint32_t version, uint32_t *penacode );

VA_EXPORTS int32_t VA_PackAlgp( void *pAlgp, ZDATBUF *pBuf, FUNC_PKGALGP func_pkg, uint32_t version );
VA_EXPORTS int32_t VA_UnpackAlgp( ZDATBUF *pBuf, void *pAlgp, FUNC_UPKALGP func_upk, uint32_t version );

VA_EXPORTS int32_t VA_PackAlgpBuffer( void *algp, ZDATBUF *buf_v, ZDATBUF *buf_z,
						  FUNC_PKGALGPV func_pkgv, FUNC_PKGALGPZ func_pkgz );
VA_EXPORTS int32_t VA_UnpackAlgpBuffer( ZDATBUF *buf_v, ZDATBUF *buf_z, void *algp,
							FUNC_UPKALGPV func_upkv, FUNC_UPKALGPZ func_upkz );

VA_EXPORTS int32_t VA_PackAlgpFile( void *algp, char *fil_v, char *fil_z, void *mmgr,
						  FUNC_PKGALGPV func_pkgv, FUNC_PKGALGPZ func_pkgz );
VA_EXPORTS int32_t VA_UnpackAlgpFile( char *fil_v, char *fil_z, void *algp, void *mmgr,
							FUNC_UPKALGPV func_upkv, FUNC_UPKALGPZ func_upkz );

VA_EXPORTS int32_t VA_DefaultAlgp( char *str_v, void *algp, void *mmgr, FUNC_UPKALGPV func_upkv, FUNC_DFTALGPZ func_dftz );

#define FIND_LINE_START(data) {data = strstr( data, "\n" ); data += 1;}

typedef struct  
{
	char *str_vana;
	char *filnam_vana;
	char *filnam_zone;
	char *filnam_bin;
	char iflag, oflag;
} SCENE_FILES;
typedef struct  
{
	int32_t img_w, img_h;
	void *mmgr;
	SCENE_FILES scnfils;

	void* (*alloc)( int32_t nImgW, int32_t nImgH, void *pMMgr );
	void (*free)( void *pScene, void *pMMgr );
	void (*clone)( void *pSrc, void *pDst );
	void (*clear)( void *pScene );
	int32_t (*calculate)( void *pScene, uint32_t flag );
	
	int32_t (*PackScene)( void *pScene, ZDATBUF *pBuf );
	int32_t (*UnpackScene)( ZDATBUF *pBuf, void *pScene );
	int32_t (*PackSceneBuffer)( void *scene, ZDATBUF *buf_v, ZDATBUF *buf_z );
	int32_t (*UnpackSceneBuffer)( ZDATBUF *buf_v, ZDATBUF *buf_z, void *scene );
	int32_t (*PackSceneFile)( void *scene, char *fil_v, char *fil_z, void *mmgr );
	int32_t (*UnpackSceneFile)( char *fil_v, char *fil_z, void *scene, void *mmgr );
	int32_t (*DefaultScene)( char *str_v, void *scene, void *mmgr );

} SCENE_PACK_OBJ;

VA_EXPORTS void VA_MakeSceneFile( SCENE_PACK_OBJ *obj );


#ifdef __cplusplus
}
#endif


#endif

