
#ifndef _ALGOVSD_VANA_H_
#define _ALGOVSD_VANA_H_

#include "AlgoVA_Vana.h"
#include "AlgoVSD_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


#if defined(VSDSAPI_EXPORTS)
#define VSDS_EXPORTS __declspec(dllexport)
#elif defined(VSDSAPI_IMPORTS)
#define VSDS_EXPORTS __declspec(dllimport)
#else
#define VSDS_EXPORTS extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// ���������������

#define SCENE_VSD_VERSION	ZANB_MAKE_VERSION( 'R', 'F', 0x41, 0 )

// ��������
// ���������
typedef struct
{
	uint8_t smoke_sens;					// ����������			
	uint8_t smoke_min_region;			// ��С��������
} VSD_VANALYSIS_PARA;

// ��������
typedef struct  
{
	int8_t name[NAME_BUF_SIZE];			// ��������
	uint32_t valid;						// �Ƿ���Ч
	uint32_t enable;					// �Ƿ�ʹ��
	uint32_t level;						// ���伶��
	uint32_t mode;						// ����ģʽ
	VSD_VANALYSIS_PARA	para;			// ��������
} VSD_VANALYSIS_ZONE;
typedef struct  
{
	// ��������
	VSD_VANALYSIS_ZONE zone[MAX_NUM_VANALYSIS_ZONE]; 
	GRAYIMAGE image;					// ����λͼ
} VSD_VANALYSIS_ZONES;

// ��������
typedef struct  
{
	uint32_t enacode;					// ʹ�ܱ�ʶ
	int8_t name[NAME_BUF_SIZE];			// ��������
	VSD_VANALYSIS_ZONES zones;			// ��������
} VSD_VANALYSIS;

VSDS_EXPORTS VSD_VANALYSIS* VSDVANA_alloc( int32_t nImgW, int32_t nImgH, void *pMMgr );
VSDS_EXPORTS void VSDVANA_free( VSD_VANALYSIS *pVana, void *pMMgr );
VSDS_EXPORTS void VSDVANA_clone( VSD_VANALYSIS *pSrc, VSD_VANALYSIS *pDst );
VSDS_EXPORTS void VSDVANA_clear( VSD_VANALYSIS *pVana );
VSDS_EXPORTS int32_t VSDVANA_calculate( VSD_VANALYSIS *pVana, uint32_t flag );

VSDS_EXPORTS void VSDZONE_alloc( VSD_VANALYSIS_ZONE *pZone, int32_t nImgW, int32_t nImgH, void *pMMgr );
VSDS_EXPORTS void VSDZONE_free( VSD_VANALYSIS_ZONE *pZone, void *pMMgr );
VSDS_EXPORTS void VSDZONE_clear( VSD_VANALYSIS_ZONE *pZone );
VSDS_EXPORTS void VSDZONE_clone( VSD_VANALYSIS_ZONE *pSrc, VSD_VANALYSIS_ZONE *pDst );

// ���������������
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif

