
#ifndef _ALGOVA_IF_H_
#define _ALGOVA_IF_H_

#include "AlgoVA_Common.h"
#include "AlgoVA_Idma.h"
#include "AlgoVA_Memory.h"
#include "AlgoVA_Funcode.h"
#include "AlgoVA_Param.h"
#include "AlgoVA_Target.h"
#include "AlgoVA_Event.h"
#include "AlgoVA_Command.h"
#include "AlgoVA_Result.h"
#include "AlgoVA_DebugInfo.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// �ӿ������������

#define ALGIF_VA_VERSION	ZANB_MAKE_VERSION( 'R', 'V', 0x41, 0 )

typedef enum  
{
	VASTATUS_OK = 0,
	VASTATUS_SKIP,
	VASTATUS_FALSE,
	VASTATUS_UNSUPPORT
} VASTATUS;

typedef void *VAHANDLE;

#define VA_MODULE_DATLEN	256
typedef struct VA_OBJ
{
	uint8_t buffer[VA_MODULE_DATLEN];
} VA_OBJ;

typedef enum
{
	VAOPER_TYPE_GetVersion		= 0x0001,	// ��ȡ�汾��Ϣ
	VAOPER_TYPE_GetFuncode		= 0x0002,	// ��ù�����
	VAOPER_TYPE_GetMemReq		= 0x0008,	// ����ڴ�����
	VAOPER_TYPE_GetDmaReq		= 0x0009,	// ���DMA����
	VAOPER_TYPE_CheckScene		= 0x000F,	// ��鳡�����ݰ�
	VAOPER_TYPE_Initialize		= 0x0010,	// ��ʼ��ģ��
	VAOPER_TYPE_Terminate		= 0x0011,	// ��ֹģ��
	VAOPER_TYPE_InitIdmaChs		= 0x0012,	// ����DMAͨ��
	VAOPER_TYPE_ConfigParameter	= 0x0020,	// ���ò���
	VAOPER_TYPE_GetParameter	= 0x0021,	// ��ȡ����
	VAOPER_TYPE_GetEnacode		= 0x0022,	// ���ʹ����
	VAOPER_TYPE_Start			= 0x0028,	// ����ģ��
	VAOPER_TYPE_Stop			= 0x0029,	// ֹͣģ��
	VAOPER_TYPE_ProcessImage	= 0x0030,	// ����ͼ��
	VAOPER_TYPE_GetResults		= 0x0034,	// ��ȡ�������
	VAOPER_TYPE_GetDebugInfo	= 0x0040,	// ��ȡ������Ϣ
	VAOPER_TYPE_DoSpecial		= 0x1000	// ģ�����в���
} VAOPER_TYPE;

typedef struct 
{
	uint32_t	type;						// ��������
	void		*data;						// ��������
} VAOPER;

VA_EXPORTS VASTATUS VA_GetVersion( VAHANDLE hModule, uint32_t *pVersion );
VA_EXPORTS VASTATUS VA_GetFuncode( VAHANDLE hModule, uint32_t *pFuncode );
VA_EXPORTS VASTATUS VA_GetMemReq( VAHANDLE hModule, VAMEM_SET *pVamems );
VA_EXPORTS VASTATUS VA_GetDmaReq( VAHANDLE hModule, IDMACHS *pIdmachs );
VA_EXPORTS VASTATUS VA_CheckScene( VAHANDLE hModule, VASCENE_CHK *pScnChk );
VA_EXPORTS VASTATUS VA_Initialize( VAHANDLE hModule, VAMEM_SET *pVamems );
VA_EXPORTS VASTATUS VA_Terminate( VAHANDLE hModule );
VA_EXPORTS VASTATUS VA_InitIdmaChs( VAHANDLE hModule, IDMACHS *pIdmachs );
VA_EXPORTS VASTATUS VA_ConfigParameter( VAHANDLE hModule, VAPARA *pVaparaE );
VA_EXPORTS VASTATUS VA_GetParameter( VAHANDLE hModule, VA_PARA **ppVaparaI );
VA_EXPORTS VASTATUS VA_GetEnacode( VAHANDLE hModule, uint32_t *pEnacode );
VA_EXPORTS VASTATUS VA_Start( VAHANDLE hModule );
VA_EXPORTS VASTATUS VA_Stop( VAHANDLE hModule, VARESULT *pVaresult );
VA_EXPORTS VASTATUS VA_ProcessImage( VAHANDLE hModule, YUVIMAGE422 *pImage );
VA_EXPORTS VASTATUS VA_GetResults( VAHANDLE hModule, VARESULT *pVaresult );
VA_EXPORTS VASTATUS VA_GetDebugInfo( VAHANDLE hModule, VADEBUGINFO *pVadbginfo );
VA_EXPORTS VASTATUS VA_DoSpecial( VAHANDLE hModule, VAOPER *pVaop );

typedef struct  
{
	char *mdlname;
	VASTATUS (*GetVersion)( VAHANDLE hModule, uint32_t *pVersion );
	VASTATUS (*GetFuncode)( VAHANDLE hModule, uint32_t *pFuncode );
	VASTATUS (*GetMemReq)( VAHANDLE hModule, VAMEM_SET *pVamems );
	VASTATUS (*GetDmaReq)( VAHANDLE hModule, IDMACHS *pIdmachs );
	VASTATUS (*CheckScene)( VAHANDLE hModule, VASCENE_CHK *pScnChk );
	VASTATUS (*Initialize)( VAHANDLE hModule, VAMEM_SET *pVamems );
	VASTATUS (*Terminate)( VAHANDLE hModule );
	VASTATUS (*InitIdmaChs)( VAHANDLE hModule, IDMACHS *pIdmachs );
	VASTATUS (*ConfigParameter)( VAHANDLE hModule, VAPARA *pVaparaE );
	VASTATUS (*GetParameter)( VAHANDLE hModule, VA_PARA **ppVaparaI );
	VASTATUS (*GetEnacode)( VAHANDLE hModule, uint32_t *pEnacode );
	VASTATUS (*Start)( VAHANDLE hModule );
	VASTATUS (*Stop)( VAHANDLE hModule, VARESULT *pVaresult );
	VASTATUS (*ProcessImage)( VAHANDLE hModule, YUVIMAGE422 *pImage );
	VASTATUS (*GetResults)( VAHANDLE hModule, VARESULT *pVaresult );
	VASTATUS (*GetDebugInfo)( VAHANDLE hModule, VADEBUGINFO *pVadbginfo );
	VASTATUS (*DoSpecial)( VAHANDLE hModule, VAOPER *pVaop );
} IVA_OBJ;

// �ӿ������������
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
