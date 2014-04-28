
#ifndef _ALGOVA_EVENT_H_
#define _ALGOVA_EVENT_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// �¼������������

#define MAX_VAEVT_CNT	128

// �¼�����
enum
{
	VAEVT_TYPE_UNKNOWN		= 0x00000000,	// δ֪����

	VAEVT_TYPE_Armed		= 0x00002000,	// ��������
	VAEVT_TYPE_Disarmed		= 0x00002001,	// ������
	VAEVT_TYPE_AlarmCleared	= 0x00002002	// �������
};

// �¼�״̬
typedef enum
{
	VAEVT_STATUS_NOSTA	= 0,				// ��״̬
	VAEVT_STATUS_START	= 1,				// ��ʼ
	VAEVT_STATUS_END	= 2					// ����
} VAEVT_STATUS;

#define BUFLEN_VAEVT_ITEM	64
#define BUFLEN_VAEVT_DATA	(BUFLEN_VAEVT_ITEM-sizeof(uint32_t)*5)
typedef struct 
{
	uint32_t	type;						// �¼�����
	uint32_t	id;							// �¼���ʶ
	uint32_t	level;						// �¼���������
	uint32_t	status;						// �¼�״̬
	uint32_t	zone;						// �¼���������
	uint8_t		data[BUFLEN_VAEVT_DATA];
} VAEVT_ITEM;

typedef struct 
{
	int32_t	event_num;						// �¼���Ŀ
	VAEVT_ITEM	events[MAX_VAEVT_CNT];		// �¼�����
} VAEVT_SET;

// �¼������������
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
