
#ifndef _ALGOVA_PARAM_H_
#define _ALGOVA_PARAM_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// �������������������

// ȫ�ֲ���
typedef struct 
{
	uint32_t time_unit;					// ͼ��ʱ�䵥λ
	uint32_t func_code;					// ������
} VAPARA_GLOBAL;

// ��������
#define VAPARA_CLBR_BUFLEN		(1024*64)
#define VAPARA_VANA_BUFLEN		(1024*64)
typedef struct 
{
	ZDATBUF	clbrdat;
	ZDATBUF	vanadat;
} VAPARA_SCENE;

// �߼�����
#define VAPARA_ADVBUF_BUFCNT	32
#define VAPARA_ADVBUF_BUFLEN	(1024*4)
typedef struct 
{
	ZDATBUF advdats[VAPARA_ADVBUF_BUFCNT];
} VAPARA_ADVANCE;

enum
{
	VPARASCNBUFNUM_CLBR = 0,
	VPARASCNBUFNUM_ZONE_CLBR,
	VPARASCNBUFNUM_VANA,
	VPARASCNBUFNUM_ZONE_VANA,
	VPARASCNBUFNUM_MAX
};

#define VAPARA_STRARRAY_ELEMCNT	32
typedef struct 
{
	char *strings[VAPARA_STRARRAY_ELEMCNT];
} VAPARA_STRARRAY;

typedef enum
{
	VAPARA_TYPE_GLOBAL = 0x01,
	VAPARA_TYPE_SCENE = 0x02,
	VAPARA_TYPE_ADVANCE = 0x04
} VAPARA_TYPE;

// ��Ƶ��������
typedef struct 
{
	uint32_t type;
	VAPARA_GLOBAL	global;				// ȫ�ֲ���
	VAPARA_SCENE	scene;				// ��������
	VAPARA_ADVANCE	advance;			// �߼���������������Ա�����ã�
} VAPARA;

typedef struct 
{
	void			*scene;				// ��������
	VAPARA_GLOBAL	global;				// ȫ�ֲ���
	VAPARA_ADVANCE	advance;			// �߼���������������Ա�����ã�
} VA_PARA;

typedef enum
{
	VASCENE_TYPE_VANA = 0,
	VASCENE_TYPE_CLBR
} VASCENE_TYPE;
typedef struct 
{
	uint32_t type;
	ZDATBUF	scndat;
	uint32_t enacode;
} VASCENE_CHK;

VA_EXPORTS void ADVPARA_alloc( VAPARA_ADVANCE *para, int32_t buf_num, int32_t buf_len, void *mmgr );
VA_EXPORTS void ADVPARA_free( VAPARA_ADVANCE *para, int32_t buf_num, void *mmgr );
VA_EXPORTS void ADVPARA_clear( VAPARA_ADVANCE *para, int32_t num );
VA_EXPORTS void ADVPARA_clone( VAPARA_ADVANCE *src, VAPARA_ADVANCE *dst, int32_t buf_num, int32_t buf_len );

VA_EXPORTS VAPARA* VAPARA_alloc( int32_t clbr_buf_len, int32_t vana_buf_len,
					 int32_t adv_buf_num, int32_t adv_buf_len,
					 void *mmgr );
VA_EXPORTS void VAPARA_free( VAPARA *para, int32_t adv_buf_num, void *mmgr );
VA_EXPORTS void VAPARA_clear( VAPARA *para, int32_t adv_buf_num );


// �������������������
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
