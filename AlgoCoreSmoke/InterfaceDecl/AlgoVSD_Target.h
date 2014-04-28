
#ifndef _ALGOVSD_TARGET_H_
#define _ALGOVSD_TARGET_H_

#include "AlgoVA_Target.h"
#include "AlgoVSD_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// Ŀ�������������

#define VATGT_ID_VSD_MIN		0x80000000
#define VATGT_ID_VSD_MAX		0x8FFFFFFF
	
// Ŀ������
enum
{
//	VATGT_TYPE_FIRE				= 0x00000011,	// ��
	VATGT_TYPE_SMOKE			= 0x00000012	// ��
};

// Ŀ���¼�
enum
{
//	VATGT_EVENT_FIRE			= 0x10000000,	// ����
	VATGT_EVENT_SMOKE			= 0x20000000	// ����
};
/*
typedef struct 
{
	int32_t	reserved;							// 
} FSDTGT_DATA_FIRE;
*/
typedef struct 
{
	int32_t	reserved;							// 
} VSDTGT_DATA_SMOKE;

typedef union 
{
//	FSDTGT_DATA_FIRE	fire;
	VSDTGT_DATA_SMOKE	smoke;
} VSDTGT_DATA;

// Ŀ�������������
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
