
#ifndef _ALGOVA_DEBUGINFO_H_
#define _ALGOVA_DEBUGINFO_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif

enum
{
	DBGINFO_DATETYPE_TXT=0x40000000,
	DBGINFO_DATETYPE_BIN=0x80000000
};

// ������Ϣ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
#define VADBGTXT_BUFLEN	(1024*4)

typedef struct 
{
	int8_t 		dbgtxt[VADBGTXT_BUFLEN];
	GRAYIMAGE 	*image_out;
	int32_t		type;		//������
	int32_t		length;		//dbgtxt����
	int32_t		mode;		//log��������
	int32_t		reserve; 	//��չ��
} VADEBUGINFO;

#ifdef __cplusplus
}
#endif


#endif
