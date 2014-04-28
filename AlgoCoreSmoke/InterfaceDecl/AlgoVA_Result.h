
#ifndef _ALGOVA_RESULT_H_
#define _ALGOVA_RESULT_H_

#include "AlgoVA_Common.h"
#include "AlgoVA_Target.h"
#include "AlgoVA_Event.h"
#include "AlgoVA_Command.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// �����������������

typedef struct 
{
	VATGT_SET	target_set;		// Ŀ��
	VAEVT_SET	event_set;		// �¼�
	VACMD_SET	command_set;	// ����
	ZSTRING		privacy;		// �ض��㷨ģ��˽������
} VARESULT;

typedef struct  
{
	uint32_t evtid_count, evtid_min, evtid_max;
} VAEVTMGR;

VA_EXPORTS void VAEVTMGR_Initialize( VAEVTMGR *mgr, uint32_t evtid_min, uint32_t evtid_max );
VA_EXPORTS void VAEVTMGR_Terminate( VAEVTMGR *mgr );
VA_EXPORTS uint32_t VAEVTMGR_AllocID( VAEVTMGR *mgr );

VA_EXPORTS void VARESULT_clear( VARESULT *varesult );
VA_EXPORTS VACMD_ITEM* VACMDSET_AddCommand( VACMD_SET *cmds, uint32_t type );
VA_EXPORTS VATGT_ITEM* VATGTSET_AddTarget( VATGT_SET *tgts,
				uint32_t id, uint32_t status, uint32_t type, uint32_t event, ZPOINT point, ZRECT rect );
VA_EXPORTS VAEVT_ITEM* VAEVTSET_AddEvent( VAEVT_SET *evts,
				uint32_t type, uint32_t id, uint32_t level, uint32_t status, uint32_t zone );
VA_EXPORTS VAEVT_ITEM* VAEVTSET_AddEventNoID( VAEVTMGR *mgr, VAEVT_SET *evts,
				uint32_t type, uint32_t *pid, uint32_t level, uint32_t status, uint32_t zone );

// �����������������
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
