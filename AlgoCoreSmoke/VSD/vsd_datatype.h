
#ifndef __VSD_DATADEF_H__
#define  __VSD_DATADEF_H__

#include "vsd_common.h"
#include "vsd_list.h"
#ifdef __cplusplus
extern "C" {
#endif

/*
 *	用于记录变化的隧道变量
 */
typedef struct  
{
	UINT32 LastArea;	//上一次面积
	UINT32 MoveTime;	//检测面积较大的时间
	UINT32 NoObjTime;	//没有检测到物体的时间
	UINT32 BakGetNum;	//
	UINT32 NoSmokeTime;
}TUNNEL_RECORE;


/*
 *	全局结构体的定义，只分配室内部分的空间
 */
typedef struct
{
	UINT32 pretime;	//上一次处理图像的帧号
	UINT32 pretime_blur;	//上一次处理图像的帧号
	int	   flg_blur_bk_valid;	//
	int		count_blur_bk_update;

	INT8   ind_NetPOffset;		//计算后的概率偏移量
	int	   OutControl;

	int	ind_firstinter;			//帧率
	int	ind_thirdinter;	
	int	ind_secondinter;		//

	UINT32 event_id, status_smoke;
	INT32 smokestart_id;
	INT32 iBakGetNum;

	UINT32 delay_alrm_count;  
	
	BOOL Isbackget;
	BOOL bState_Is1stFrame;	//not used
	//BOOL bDebugData;
	BOOL flg_skip_subprocess;	
	
	TUNNEL_RECORE tul_record;

	vsLIST *list_smoke, *list_temp;
	vsLIST *list_mid;
	vsLIST *list_trace[REGION_TEMP_NUM];

	UINT8	//输入图像
			*scur_h,
			*scur_s, 
			*scur_v,
			*zone_mask;

			//公共缓存			
	UINT8	*tmp_buf1,
			*tmp_buf2,
			*tmp_bitbuf1,
			*tmp_bitbuf2;
	
	
	INT16	*tmp_buf161,			//dst
			*tmp_buf162,			//dsx
			*tmp_buf163,			//dsy
			*tmp_buf164,			//vx
			*tmp_buf165,			//vy
			*tmp_buf166,			//vxavg
			*tmp_buf167,			//vyavg
			*tmp_buf168;			//vx^2


			//室内部分
	UINT8	*ind_cursm,				//滤波后
			*ind_presm,				//上一帧
			*ind_presm_sub,

			*ind_curgd,				//当前梯度
			*ind_pregd,				//上一帧
			*ind_pregd_sub,
			*ind_gddiff,			//梯度差
			*ind_gddir,				//梯度方向，0代表无，其余为45、105、185、254

			*ind_curdiff,			//帧差
			*ind_diffsign,			//帧差的符号，大于：ff，等于：f，小于：0
			*ind_diffsign_sub,			//帧差的符号，大于：ff，等于：f，小于：0
			*ind_presign,			//上一次帧差的符号
			*ind_prepresign,		//上上一次帧差的符号
			*ind_presign_sub,			//上一次帧差的符号
			*ind_prepresign_sub,		//上上一次帧差的符号
			*ind_signgd,			//当前帧差符号的梯度

			*ind_optort,			//当前方向
			*ind_bakort,			//背景方向
			*ind_bakort_sub,			//背景方向
			*ind_orthist,			//方向记录
			*ind_ortcount0,			//方向为零的计数
			*ind_orthist_sub,			//方向记录
			*ind_ortcount0_sub,			//方向为零的计数
			*ind_optlevel,		    //第一级level	
			*ind_optlevel_sub,		    //第一级level	

			*ind_initreg,			//初始区域，并作最终输出区域
			*ind_initreg_sub,			//初始区域，并作最终输出区域
			*ind_finreg,			//特征后区域
			*ind_finreg_sub,			//特征后区域
			*ind_finlevel,			//第二级level
			*ind_finlevel_sub;		//第二级level

	UINT8	*ind_gd_bk;				//梯度背景
	UINT16	*ind_gd_bk16;				//梯度背景
	UINT8	*ind_blur_trend;		//模糊趋势
	UINT8   *ind_blur_hist;
	UINT8	*ind_blur_hist_level;	//BLUR_BLOCK_SIZE分之一
	UINT8	*ind_blur_level;				//

			//16位	
	INT16	*ind_curdiff16,			//帧差
			*ind_curdiff16_sub,			//帧差
			*ind_prediff16,			//上一帧差
			*ind_prediff16_sub,
			*ind_curdiff16half,
			*ind_curdiff16half_sub,
			*ind_prediff16half,
			*ind_prediff16half_sub;

	
	/////////  以下部分不分配空间  //////////////////////////////////////

	//  隧道
	UINT8	
			*tul_cursm,				//输入图像
			*tul_bak,				//背景
			*tul_refbak,			//参考背景
			*tul_bakuplevel,		//背景更新记数
			*tul_bakdiff,			//背景差

			*tul_refdiff,			//与参考的背景差
			*tul_initreg,			//初始区域
			*tul_presm,				//上一帧
			*tul_finreg,			//最后区域
			*tul_finlevel,			//区域level

			*tul_curgd,				//输入梯度
			*tul_bakgd,				//背景梯度
			*tul_refimg,			//参考图像，用于记录长时间不变的区域		
			*tul_nochglevel,		//没有改变的记数	

			*tul_initlevel,
			*tul_bakhtext,			//背景的高纹理区域
			*tul_gddiffval,			//梯度差	
			*tul_gddiffsign;			//差的符号

//	INT16	*tul_gddiff16;			//梯度差

}VSD_GLOBAL_VAR;
/////------------------------------------------------------------

#undef max
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#undef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))

#undef	PTR_EXCHANGE
#define PTR_EXCHANGE(a, b, c)	(c) = (a); (a) = (b); (b) = (c);



#ifndef SAFE_FREE
#define SAFE_FREE(ptr) if(ptr) {free(ptr); (ptr)=NULL;} 
#endif

#ifdef PI
#undef PI
#define PI 3.1415926f
#endif

//限制变量范围
#define  VS_setRangeMax(a, b) ((a)=(a)>(b) ? (b):(a))
#define  VS_setRangeMin(a, b) ((a)=(a)<(b) ? (b):(a))
#define  VS_setRange(a, _min, _max)  ((a)=(a)>(_max) ? (_max):(a)); ((a)=(a)<(_min) ? (_min):(a));

#define  VS_abs(a) ((a)>0 ? (a):-(a))


#ifdef __cplusplus
}
#endif

#endif //__FS_DATADEF_H__
