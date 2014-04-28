
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
// 标定相关数据类型

#define SCENE_CLBR_VERSION	ZANB_MAKE_VERSION( 'R', 'C', 0x31, 0 )

#define MAX_NUM_FDEPTH_ZONE		8
#define MAX_NUM_FDEPTH_LINE		8
#define MIN_NUM_FDEPTH_LINE		4

// 景深相关数据类型

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
	FDZ_LINE_TYPE type;			// 线段类型
	ZLINE ref_line;				// 线段坐标(unit: pixel)
	int32_t ref_length;			// 线段长度(unit: cm)
} FDZ_LINE;
typedef struct
{
	uint32_t num_used;			// 样本数目
	FDZ_LINE lines[MAX_NUM_FDEPTH_LINE];
} FDZ_LINES;

// 景深平面标定数据
typedef struct
{
	FDZ_LINES fdlines;			// 标定线段
	int32_t lock_height;		// 锁定高度
	int32_t lock_vanish;		// 锁定消失线
	int32_t lock_tilt;			// 锁定俯仰角
} FDZ_MEASURE_GROUND;
typedef struct
{
	FDZ_LINES fdlines;			// 标定线段
} FDZ_MEASURE_AIR;
typedef struct
{
	ZLINE hori_line;			// 平面与地面交线(unit: pixel)
} FDZ_MEASURE_WALL;
typedef struct
{
	ZLINE vert_line;			// 平面与地面垂线(unit: pixel)
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
	FDZ_MEASURE_PLANE plane;	// 景深平面数据
} FDZ_MEASURE;

// 景深平面标定参数
typedef struct
{
	int32_t u0, v0;	
	int32_t flength;
	int32_t height;	
	int32_t angle;
	int32_t b_vanish;	
	int32_t v_vanish;	
	int32_t lamda;
	float sincita,coscita;		// 便于以后数据的计算
} FDZ_PARAMS_GROUND;
typedef struct
{
	float k_vanish;	 
    float b_vanish;			// 平面消失线不一定水平 y = k_vanish+b_vanish;
	float lamda;
	float yu,yv,yc;
	float cu,cv,cc;
} FDZ_PARAMS_AIR;
typedef struct
{
	float xa,xb,xc;
	float ya,yb,yc;
	float ca,cb,cc;			// 计算墙面上点在地面上的投影点的系数	
	float cosalfa;
	int32_t x_vanish,y_vanish;
} FDZ_PARAMS_WALL;
typedef struct
{
	int32_t h_p2g;				// 桌面相对于地面的高度
	int32_t h_c2p;				// 相机相对于桌面的高度
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
	float cx, cy, cf;			// resolv = cx * x + cy * y + cf, 分辨率(unit: pixel/cm)
} FDEPTH_COEF;
typedef struct
{
	FDZ_PARAMS_PLANE plane;		// 景深平面参数
	FDEPTH_COEF coef;
} FDZ_PARAMS;

// 景深平面参数
typedef struct
{
	int8_t name[NAME_BUF_SIZE];	// 名称
	uint32_t valid;				// 是否有效
	FDZ_PLANE_TYPE type;		// 景深平面类型
	FDZ_MEASURE measure;		// 标定数据
	FDZ_PARAMS params;			// 标定参数
} FDEPTH_ZONE;

// 景深平面
typedef struct
{
	FDEPTH_ZONE zone[MAX_NUM_FDEPTH_ZONE];// 景深平面参数
	GRAYIMAGE image_plane;		// 景深平面位图
	GRAYIMAGE image_resolution;	// 分辨率位图
} FDEPTH_ZONES;

// 景深参数
typedef struct
{
	uint32_t enacode;			// 使能标识
	uint32_t algcfg;			// 算法配置
	FDEPTH_ZONES zones;			// 景深平面
} FDEPTH;

// 环境参数
typedef struct
{
	int32_t reserved;
} SCONTEXT;

// 场景标定
typedef struct  
{
	FDEPTH	fdepth;				// 景深参数
	SCONTEXT context;			// 环境参数
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
	CLBR_SUCCESS			= 0,	// 调用成功
	CLBR_ERROR_UNKNOWN		= -1,	// 未知原因
	CLBR_ERROR_UNCONFIG		= -2,	// 算法未配置
	CLBR_ERROR_UNSUPPORTED	= -3,	// 不支持此操作
	CLBR_ERROR_DATAINVALID	= -10,	// 数据无效
	CLBR_ERROR_UNCERTAINTY	= -11,	// 数据存在不确定性
	CLBR_ERROR_TOOFAR		= -12	// 位置太远
};

#define FDEPTH_MIN_RESOLUTION	1	// mm/pixel
#define FDEPTH_MAX_RESOLUTION	254	// mm/pixel
#define FDEPTH_MAX_RESOLUTION2	500	// mm/pixel


// 标定相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif

