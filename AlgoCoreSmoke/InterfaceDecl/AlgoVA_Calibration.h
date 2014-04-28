
#ifndef _ALGOVA_CALIBRATION_H_
#define _ALGOVA_CALIBRATION_H_

#include "AlgoVA_Common.h"


#ifdef __cplusplus
extern "C"
{
#endif


#if defined(CLBRSAPI_EXPORTS)
#define CLBRS_EXPORTS __declspec(dllexport)
#elif defined(CLBRSAPI_IMPORTS)
#define CLBRS_EXPORTS __declspec(dllimport)
#else
#define CLBRS_EXPORTS extern
#endif

#if defined(CLBRAPI_EXPORTS)
#define CLBR_EXPORTS __declspec(dllexport)
#elif defined(CLBRAPI_IMPORTS)
#define CLBR_EXPORTS __declspec(dllimport)
#else
#define CLBR_EXPORTS extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// �궨�����������

#define SCENE_CLBR_VERSION	ZANB_MAKE_VERSION( 'R', 'C', 0x31, 0 )

#define MAX_NUM_FDEPTH_ZONE		8
#define MAX_NUM_FDEPTH_LINE		8
#define MIN_NUM_FDEPTH_LINE		4

// ���������������

typedef enum
{
	FDZ_LINE_HORI = 0,
	FDZ_LINE_VERT
} FDZ_LINE_TYPE;

typedef enum
{
	FDZ_PLANE_GROUND = 0,
	FDZ_PLANE_AIR,
	FDZ_PLANE_WALL,
	FDZ_PLANE_PLATE
// 	FDZ_PLANE_INCLINE,
} FDZ_PLANE_TYPE;

typedef struct
{
	FDZ_LINE_TYPE type;			// �߶�����
	ZLINE ref_line;				// �߶�����(unit: pixel)
	int32_t ref_length;			// �߶γ���(unit: cm)
} FDZ_LINE;
typedef struct
{
	uint32_t num_used;			// ������Ŀ
	FDZ_LINE lines[MAX_NUM_FDEPTH_LINE];
} FDZ_LINES;

// ����ƽ��궨����
typedef struct
{
	FDZ_LINES fdlines;			// �궨�߶�
	int32_t lock_height;		// �����߶�
	int32_t lock_vanish;		// ������ʧ��
	int32_t lock_tilt;			// ����������
} FDZ_MEASURE_GROUND;
typedef struct
{
	FDZ_LINES fdlines;			// �궨�߶�
} FDZ_MEASURE_AIR;
typedef struct
{
	ZLINE hori_line;			// ƽ������潻��(unit: pixel)
} FDZ_MEASURE_WALL;
typedef struct
{
	ZLINE vert_line;			// ƽ������洹��(unit: pixel)
} FDZ_MEASURE_PLATE;
typedef union
{
	FDZ_MEASURE_GROUND ground;
	FDZ_MEASURE_AIR air;
	FDZ_MEASURE_WALL wall;
	FDZ_MEASURE_PLATE plate;
} FDZ_MEASURE_PLANE;
typedef struct
{
	FDZ_MEASURE_PLANE plane;	// ����ƽ������
} FDZ_MEASURE;

// ����ƽ��궨����
typedef struct
{
	int32_t u0, v0;	
	int32_t flength;
	int32_t height;	
	int32_t angle;
	int32_t b_vanish;	
	int32_t v_vanish;	
	int32_t lamda;
	float sincita,coscita;		// �����Ժ����ݵļ���
} FDZ_PARAMS_GROUND;
typedef struct
{
	float k_vanish;	 
    float b_vanish;			// ƽ����ʧ�߲�һ��ˮƽ y = k_vanish+b_vanish;
	float lamda;
	float yu,yv,yc;
	float cu,cv,cc;
} FDZ_PARAMS_AIR;
typedef struct
{
	float xa,xb,xc;
	float ya,yb,yc;
	float ca,cb,cc;			// ����ǽ���ϵ��ڵ����ϵ�ͶӰ���ϵ��	
	float cosalfa;
	int32_t x_vanish,y_vanish;
} FDZ_PARAMS_WALL;
typedef struct
{
	int32_t h_p2g;				// ��������ڵ���ĸ߶�
	int32_t h_c2p;				// ������������ĸ߶�
	int32_t lamda;
} FDZ_PARAMS_PLATE;
typedef union
{
	FDZ_PARAMS_GROUND ground;
	FDZ_PARAMS_AIR air;
	FDZ_PARAMS_WALL wall;
	FDZ_PARAMS_PLATE plate;
} FDZ_PARAMS_PLANE;
typedef struct
{
	float cx, cy, cf;			// resolv = cx * x + cy * y + cf, �ֱ���(unit: pixel/cm)
} FDEPTH_COEF;
typedef struct
{
	FDZ_PARAMS_PLANE plane;		// ����ƽ�����
	FDEPTH_COEF coef;
} FDZ_PARAMS;

// ����ƽ�����
typedef struct
{
	int8_t name[NAME_BUF_SIZE];	// ����
	uint32_t valid;				// �Ƿ���Ч
	FDZ_PLANE_TYPE type;		// ����ƽ������
	FDZ_MEASURE measure;		// �궨����
	FDZ_PARAMS params;			// �궨����
} FDEPTH_ZONE;

// ����ƽ��
typedef struct
{
	FDEPTH_ZONE zone[MAX_NUM_FDEPTH_ZONE];// ����ƽ�����
	GRAYIMAGE image_plane;		// ����ƽ��λͼ
	GRAYIMAGE image_resolution;	// �ֱ���λͼ
} FDEPTH_ZONES;

// �������
typedef struct
{
	uint32_t enacode;			// ʹ�ܱ�ʶ
	uint32_t algcfg;			// �㷨����
	FDEPTH_ZONES zones;			// ����ƽ��
} FDEPTH;

// ��������
typedef struct
{
	int32_t reserved;
} SCONTEXT;

// �����궨
typedef struct  
{
	FDEPTH	fdepth;				// �������
	SCONTEXT context;			// ��������
} CALIBRATION;

CLBRS_EXPORTS CALIBRATION* CLBR_alloc( int32_t nImgW, int32_t nImgH, void *pMMgr );
CLBRS_EXPORTS void CLBR_free( CALIBRATION *pCLBR, void *pMMgr );
CLBRS_EXPORTS void CLBR_clone( CALIBRATION *pSrc, CALIBRATION *pDst );
CLBRS_EXPORTS void CLBR_clear( CALIBRATION *pCLBR );

CLBR_EXPORTS void CLBR_getversion( CALIBRATION *pCLBR, uint32_t *algver );
CLBR_EXPORTS void CLBR_configure( CALIBRATION *pCLBR, uint32_t algcfg );
CLBR_EXPORTS void CLBR_getconfig( CALIBRATION *pCLBR, uint32_t *algcfg );
CLBR_EXPORTS int32_t CLBR_calculate( CALIBRATION *pCLBR, uint32_t flag );

CLBR_EXPORTS int32_t FDEPTH_get_point_resolution( FDEPTH *fdepth, int32_t x, int32_t y, double *res_x, double *res_y );
CLBR_EXPORTS int32_t FDEPTH_get_point_position( FDEPTH *fdepth, ZPOINT *point, ZPOINT3D *position );
CLBR_EXPORTS int32_t FDEPTH_get_line_length( FDEPTH *fdepth, ZLINE *line, FDZ_LINE_TYPE type, int32_t *length );
CLBR_EXPORTS int32_t FDEPTH_get_line_coordinate( FDEPTH *fdepth, ZLINE *line, FDZ_LINE_TYPE type, int32_t length );
CLBR_EXPORTS int32_t FDEPTH_get_rect_dimension( FDEPTH *fdepth, FDZ_LINE_TYPE type, ZPOINT *bpos, double area,
											   double ratio, int32_t *pwidth, int32_t *pheight );

enum
{
	CLBR_CFG_ALG_CV1 = 0x0000,
	CLBR_CFG_ALG_CV2 = 0x0001
};

enum
{
	CLBR_SUCCESS			= 0,	// ���óɹ�
	CLBR_ERROR_UNKNOWN		= -1,	// δ֪ԭ��
	CLBR_ERROR_UNCONFIG		= -2,	// �㷨δ����
	CLBR_ERROR_UNSUPPORTED	= -3,	// ��֧�ִ˲���
	CLBR_ERROR_DATAINVALID	= -10,	// ������Ч
	CLBR_ERROR_UNCERTAINTY	= -11,	// ���ݴ��ڲ�ȷ����
	CLBR_ERROR_TOOFAR		= -12	// λ��̫Զ
};

#define FDEPTH_MIN_RESOLUTION	1	// mm/pixel
#define FDEPTH_MAX_RESOLUTION	254	// mm/pixel
#define FDEPTH_MAX_RESOLUTION2	500	// mm/pixel


// �궨�����������
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif

