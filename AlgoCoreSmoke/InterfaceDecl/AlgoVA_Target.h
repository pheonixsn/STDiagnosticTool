
#ifndef _ALGOVA_TARGET_H_
#define _ALGOVA_TARGET_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// Ŀ�������������

#define MAX_VATGT_CNT			64

// Ŀ������
enum
{
	VATGT_TYPE_UNKNOWN			= 0x00000000	// δ֪����
};

// Ŀ���¼�
enum
{
	VATGT_EVENT_UNKNOWN			= 0x00000000	// δ֪�¼�
};

// Ŀ��״̬
enum
{
	VATGT_STATUS_UNKNOWN		= 0x00000000	// δ֪״̬
};

// Ŀ��켣
#define MAX_VATRAJECT_LEN	40
typedef struct
{
	int32_t length;						// �켣����
	ZPOINT	points[MAX_VATRAJECT_LEN];	// �켣������
} VATGT_TRAJECT;

// Ŀ������
#define BUFLEN_VATGT_ITEM	256
#define BUFLEN_VATGT_DATA	(BUFLEN_VATGT_ITEM-(sizeof(uint32_t)*4+sizeof(ZPOINT)+sizeof(ZRECT)))
typedef struct
{
	uint32_t	id;						// ID
	uint32_t	status;					// ״̬
	uint32_t	type;					// ����
	uint32_t	event;					// �¼�
	ZPOINT		point;					// λ��
	ZRECT		rect;					// ����
	uint8_t		data[BUFLEN_VATGT_DATA];
} VATGT_ITEM;

// Ŀ�꼯��
typedef struct
{
	int32_t	target_num;					// Ŀ����Ŀ
	VATGT_ITEM	targets[MAX_VATGT_CNT];	// Ŀ������
} VATGT_SET;

// Ŀ�������������
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
