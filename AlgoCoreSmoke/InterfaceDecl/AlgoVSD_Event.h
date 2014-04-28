
#ifndef _ALGOVSD_EVENT_H_
#define _ALGOVSD_EVENT_H_

#include "AlgoVA_Event.h"
#include "AlgoVSD_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// �¼������������

#define VAEVT_ID_VSD_MIN		0x80000000
#define VAEVT_ID_VSD_MAX		0x80FFFFFF
	
enum
{

	VAEVT_TYPE_AlarmSmoke		= 0x00002281	// ����
};

typedef struct 
{
	int32_t	reserved;							// 
} VSDEVT_DATA_SMOKE;

typedef union 
{
	VSDEVT_DATA_SMOKE	smoke;
} VSDEVT_DATA;

// �¼������������
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
