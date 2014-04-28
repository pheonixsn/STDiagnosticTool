
#ifndef _VSD_COMMON_H_
#define _VSD_COMMON_H_

#include "AlgoVSD_IF.h"
#include "AlgoVSD_Scene.h"
#include "va_common.h"


#ifdef __cplusplus
extern "C"
{
#endif

//#define SUPPORT_SMOKE


//typedef VSD_VANALYSIS_PARA_FIRE				VANALYSIS_PARA_FIRE;
//typedef VSD_VANALYSIS_PARA_SMOKE			VANALYSIS_PARA_SMOKE;
typedef VSD_VANALYSIS_PARA					FVANALYSIS_PARA;
typedef VSD_VANALYSIS_ZONE					FVANALYSIS_ZONE;
typedef VSD_VANALYSIS_ZONES					FVANALYSIS_ZONES;
typedef VSD_VANALYSIS						FVANALYSIS;
typedef VSD_SCENE							FSCENE_MODEL;

//////////类型基本数据类型////////////////////////////////////////////

#ifndef _WINDEF_
typedef int8_t          INT8;
typedef int16_t         INT16;
typedef int32_t         INT32;
typedef uint8_t			UINT8;
typedef uint16_t		UINT16;
typedef uint32_t		UINT32;
typedef unsigned int   BOOL;
#undef	NULL
#define NULL			(void*)0
#endif
//////////////////////////////////////////////////////////////////////

/////////////////////基本类型结构/////////////////////////////////////
////灰度图像；点；框；
typedef	RGBIMAGE	VSDET_RGBIMAGE;
typedef	GRAYIMAGE	VSDET_GRAYIMAGE;
typedef	ZPOINT		VSDET_ZPOINT;
typedef	ZRECT		VSDET_ZRECT;

typedef struct 
{
	INT16 width, height;
} VSDET_SIZE;
//////////////////////////////////////////////////////////////////////


////////////////////////////////参量宏定义////////////////////////////
//#define	REGION_FIRE_NUM		16
#define	REGION_SMOKE_NUM	16
#define REGION_TEMP_NUM		32
#define TRACE_LENGTH_NUM	20

#define SVM_SV_NUM		190		//单分类器向量总数
#define SVM_NUM			10		//分类器数

#undef MAX_TARGET_CNT
#define MAX_TARGET_CNT		16
//#define MAX_VAEVT_CNT		(MAX_TARGET_CNT*2)


#define EVENT_ID_VSD_MIN	0x80000000
#define EVENT_ID_VSD_MAX	0x8FFFFFFF
#define EVENT_ID_ADD(id) ( (id)>=EVENT_ID_VSD_MAX ? EVENT_ID_VSD_MIN:(id+1) )
//////////////////////////////////////////////

////////////////////////////////////
//烟雾识别类型定义；
#define SMOKE_NODET		0			//不检测
#define SMOKE_TUNNEL	0x01		//保留
#define SMOKE_INDOOR	0x02		//室内版
// #define SMOKE_OUTDOOR	0x04	//室外版
// #define SMOKE_FOREST	0x08		//森林版
/////////////////////////////////////////////

//////////////高级参数定义////////////////////
typedef struct VSDET_PARA
{
	UINT32 interval;				//[1,10],处理间隔，interval帧处理1帧
	UINT8 det_type;					//[1,8],检测类型，SMOKE_INDOOR	0x02
	UINT8 sensitivity;				//[1,100],60,灵敏度
	UINT8 edgelength_min;			//[6,10000],20,最小长度
	UINT8 comdeg;					//串口调试
	UINT8 delay_time;		        //

	//indoor
	UINT8 ind_ortang;				//[1,90],40,同相角,在此范围内的光流方向被认为一致
	UINT8 ind_adddiff;				//50,增加与减小量的差是（diff-50）
	UINT8 ind_netoffset;			//100,
	UINT8 ind_opt_level;			//[100,250],170 光流level最终分割阈值
	UINT8 ind_opt_intensity;		//[0,100],2,低于此强度的光流不被计算

	UINT8 ind_blur_bk_inter;		//更新帧间隔 
	UINT8 ind_blur_bk_w;			//更新权重
	UINT8 ind_blur_bk_thrld;        //阈值
	UINT8 ind_blur_level_thrld;        //阈值

	BOOL  flg_enable_subprocess;	//enable sub process
	UINT8 flg_svm_noused;        //use svm

	//支持向量机部分
	INT32	*ind_svm_class,			//第几类的支持向量机
			*ind_svm_numsv;			//支持向量的个数
	float	*ind_svm_gramm,			//gramm
			*ind_svm_rho,			//偏移
		
			*ind_svm_coef[SVM_NUM],	//系数	
			*ind_svm_sv[SVM_NUM];	//支持向量


	//tunnel
	UINT8 tul_bakuprate;			//背景更新率
	UINT8 tul_cordisap;				//相关区域的消失速度
	UINT8 tul_nochgdisap;			//不变区域的消失速度
	UINT8 tul_adddiff1;
	UINT8 tul_adddiff2;

	UINT8 tul_prcheight;			//处理高度
	UINT8 tul_corcof;				//相关系数
	UINT8 tul_flat;					//平滑性
	UINT8 tul_contrast;				//对比度

}VSDET_PARA;
///////////////////////////////////////////////////



////烟类型定义////////////////////
typedef enum
{
	SMOKE_NONE			= 0,
	SMOKE_DEL,
	SMOKE_LIKE,
	SMOKE_IDENTITY	
}SMOKE_REGION_TYPE;
////////////////////////////////////


#define EDGE_LENGTH_MAX		2048
//用边缘点描述的边缘数据结构，pData中保存边缘每个点的坐标值
#define BLUR_BLOCK_SIZE 16

#define CAL_BLUR_BLOCK_SIZE(a)	(((a)+BLUR_BLOCK_SIZE-1)/BLUR_BLOCK_SIZE)
typedef struct vsdet_edge_line
{
	INT32	 nLengthUsed;	//边缘总点数
	UINT32	 edge_point[EDGE_LENGTH_MAX];	//low 16bit = cord x, high 16bit = cord y

} VSDET_EDGELINE;


////////////////////定义参数特征//////////////////////
typedef struct vsdet_region_character
{
	//仅用于轨迹
//#ifdef WIN32
	int				ind_NnetP;
	VSDET_ZRECT		region_rect;
//#endif
	
	//烟雾特性
	//室内
	int		ind_DiffStat;			//当前帧差在【0,20】范围与【0,255】范围的比例；
	int		ind_SuppressRate;		//梯度差在【20,255】范围占总面积的比例
	int		ind_Contrast;			//灰度值在80%范围内的像素点的灰度范围占总数255区间的比例
	int		ind_GradChgCon;			//前后两帧图像梯度都大于45的点中，梯度差小于10的点的比例，大梯度的一致性相关分析；
	int		ind_BigGrad;			//但前梯度在【30,255】范围内的比例

	int		ind_DiffGrad;			//当前帧差的梯度在【8,255】的比例
	int		ind_GradDirect;			//上下左右梯度一致的点与总点数的比例；
	int		ind_DirectPart;			//上下左右梯度一致的点与梯度有效（大于0）点数的比例；
	int		ind_PixIncreas;			//三帧图像符号变化一致性特性；
	
	int		ind_OptMax;				//光流方向的一致的点数的比例
	int		ind_OptZero;			//光流方向为0的点的比例

	int		ind_GdDirMax;			//梯度方向一致的点数的比例
	int		ind_GdDirZero;			//梯度方向为0的点的比例
	
	int		ind_SpotRate;			//计算帧差的2阶导在【4,20】范围的比例
	int		ind_OptGrade;			//计算光流方向的梯度大于0的点的比例
	int		ind_ChangeRate;			//帧差符号的梯度在【0xf，0xFF】范围内的比例
	int		ind_AddRate;			//帧差为正的像素比例


	 
	int		AreaRate;				//与4000像素点相比的比例*100%，上限是50

	//隧道

	int		tul_CorP;			//相关系数	
	int		tul_AvgDiff;		//平均值的差
	int		tul_Contrast;		//对比度
	int		tul_CoMat;
	int		tul_CurGrad;		//大梯度的比

	int		tul_gdinc;
	int		tul_gdred;
	int		tul_HTextRate;
	int		tul_LTextRate;
	int		tul_ChgRate;

} VSDET_REGION_CHARACTER;

typedef struct vsd_region_temporal
{
	SMOKE_REGION_TYPE type;

	INT32 Area;		//区域有效像素数，扩边2pixel
	INT32 rect_area;
	//轨迹处理
//#ifdef WIN32

	INT32 MatchNum;		//匹配记数,每无匹配减1
	INT32 TraceIndex;    //轨迹链表索引
	BOOL  bMatchCur;	//和当前是否匹配

//#endif
	//INT8 AddRate;

	VSDET_ZRECT			region_rect;
	VSDET_ZPOINT		center_everage;

	VSDET_REGION_CHARACTER		RegCharacter;	

} VSD_REGION_TEMPORAL;
////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif


#endif
