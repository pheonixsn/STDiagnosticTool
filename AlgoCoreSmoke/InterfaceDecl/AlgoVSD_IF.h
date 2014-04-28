
#ifndef _ALGOVSD_IF_H_
#define _ALGOVSD_IF_H_

#include "AlgoVA_IF.h"
#include "AlgoVSD_Common.h"
#include "AlgoVSD_Funcode.h"
#include "AlgoVSD_Param.h"
#include "AlgoVSD_Target.h"
#include "AlgoVSD_Event.h"
#include "AlgoVSD_Command.h"
#include "AlgoVSD_Result.h"
#include "AlgoVSD_DebugInfo.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum
{
	VSD_GET_INTERVAL
};
typedef struct  
{
	int ifirst;
	int isecond;

}VSD_PRC_INTERVAL;


///////////////////////////////////////////////////////////////////////////////////////////////////
// 接口相关数据类型

VSD_EXPORTS VASTATUS VSD_GetVersion( VAHANDLE hModule, uint32_t *pVersion );
VSD_EXPORTS VASTATUS VSD_GetFuncode( VAHANDLE hModule, uint32_t *pFuncode );
VSD_EXPORTS VASTATUS VSD_GetMemReq( VAHANDLE hModule, VAMEM_SET *pVamems );
VSD_EXPORTS VASTATUS VSD_GetDmaReq( VAHANDLE hModule, IDMACHS *pIdmachs );
VSD_EXPORTS VASTATUS VSD_CheckScene( VAHANDLE hModule, VASCENE_CHK *pScnChk );
VSD_EXPORTS VASTATUS VSD_Initialize( VAHANDLE hModule, VAMEM_SET *pVamems );
VSD_EXPORTS VASTATUS VSD_Terminate( VAHANDLE hModule );
VSD_EXPORTS VASTATUS VSD_InitIdmaChs( VAHANDLE hModule, IDMACHS *pIdmachs );
VSD_EXPORTS VASTATUS VSD_ConfigParameter( VAHANDLE hModule, VAPARA *pVaparaE );
VSD_EXPORTS VASTATUS VSD_GetParameter( VAHANDLE hModule, VA_PARA **ppVaparaI );
VSD_EXPORTS VASTATUS VSD_GetEnacode( VAHANDLE hModule, uint32_t *pEnacode );
VSD_EXPORTS VASTATUS VSD_Start( VAHANDLE hModule );
VSD_EXPORTS VASTATUS VSD_Stop( VAHANDLE hModule, VARESULT *pVaresult );
VSD_EXPORTS VASTATUS VSD_ProcessImage( VAHANDLE hModule, YUVIMAGE422 *pImage );
VSD_EXPORTS VASTATUS VSD_GetResults( VAHANDLE hModule, VARESULT *pVaresult );
VSD_EXPORTS VASTATUS VSD_GetDebugInfo( VAHANDLE hModule, VADEBUGINFO *pVadbginfo );
VSD_EXPORTS VASTATUS VSD_DoSpecial( VAHANDLE hModule, VAOPER *pVaop );

VSD_EXPORTS IVA_OBJ iva_obj_vsd;

// 接口相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
