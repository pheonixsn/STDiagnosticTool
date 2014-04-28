
#ifndef __VSD_DATADEF_H__
#define  __VSD_DATADEF_H__

#include "vsd_common.h"
#include "vsd_list.h"
#ifdef __cplusplus
extern "C" {
#endif

/*
 *	���ڼ�¼�仯���������
 */
typedef struct  
{
	UINT32 LastArea;	//��һ�����
	UINT32 MoveTime;	//�������ϴ��ʱ��
	UINT32 NoObjTime;	//û�м�⵽�����ʱ��
	UINT32 BakGetNum;	//
	UINT32 NoSmokeTime;
}TUNNEL_RECORE;


/*
 *	ȫ�ֽṹ��Ķ��壬ֻ�������ڲ��ֵĿռ�
 */
typedef struct
{
	UINT32 pretime;	//��һ�δ���ͼ���֡��
	UINT32 pretime_blur;	//��һ�δ���ͼ���֡��
	int	   flg_blur_bk_valid;	//
	int		count_blur_bk_update;

	INT8   ind_NetPOffset;		//�����ĸ���ƫ����
	int	   OutControl;

	int	ind_firstinter;			//֡��
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

	UINT8	//����ͼ��
			*scur_h,
			*scur_s, 
			*scur_v,
			*zone_mask;

			//��������			
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


			//���ڲ���
	UINT8	*ind_cursm,				//�˲���
			*ind_presm,				//��һ֡
			*ind_presm_sub,

			*ind_curgd,				//��ǰ�ݶ�
			*ind_pregd,				//��һ֡
			*ind_pregd_sub,
			*ind_gddiff,			//�ݶȲ�
			*ind_gddir,				//�ݶȷ���0�����ޣ�����Ϊ45��105��185��254

			*ind_curdiff,			//֡��
			*ind_diffsign,			//֡��ķ��ţ����ڣ�ff�����ڣ�f��С�ڣ�0
			*ind_diffsign_sub,			//֡��ķ��ţ����ڣ�ff�����ڣ�f��С�ڣ�0
			*ind_presign,			//��һ��֡��ķ���
			*ind_prepresign,		//����һ��֡��ķ���
			*ind_presign_sub,			//��һ��֡��ķ���
			*ind_prepresign_sub,		//����һ��֡��ķ���
			*ind_signgd,			//��ǰ֡����ŵ��ݶ�

			*ind_optort,			//��ǰ����
			*ind_bakort,			//��������
			*ind_bakort_sub,			//��������
			*ind_orthist,			//�����¼
			*ind_ortcount0,			//����Ϊ��ļ���
			*ind_orthist_sub,			//�����¼
			*ind_ortcount0_sub,			//����Ϊ��ļ���
			*ind_optlevel,		    //��һ��level	
			*ind_optlevel_sub,		    //��һ��level	

			*ind_initreg,			//��ʼ���򣬲��������������
			*ind_initreg_sub,			//��ʼ���򣬲��������������
			*ind_finreg,			//����������
			*ind_finreg_sub,			//����������
			*ind_finlevel,			//�ڶ���level
			*ind_finlevel_sub;		//�ڶ���level

	UINT8	*ind_gd_bk;				//�ݶȱ���
	UINT16	*ind_gd_bk16;				//�ݶȱ���
	UINT8	*ind_blur_trend;		//ģ������
	UINT8   *ind_blur_hist;
	UINT8	*ind_blur_hist_level;	//BLUR_BLOCK_SIZE��֮һ
	UINT8	*ind_blur_level;				//

			//16λ	
	INT16	*ind_curdiff16,			//֡��
			*ind_curdiff16_sub,			//֡��
			*ind_prediff16,			//��һ֡��
			*ind_prediff16_sub,
			*ind_curdiff16half,
			*ind_curdiff16half_sub,
			*ind_prediff16half,
			*ind_prediff16half_sub;

	
	/////////  ���²��ֲ�����ռ�  //////////////////////////////////////

	//  ���
	UINT8	
			*tul_cursm,				//����ͼ��
			*tul_bak,				//����
			*tul_refbak,			//�ο�����
			*tul_bakuplevel,		//�������¼���
			*tul_bakdiff,			//������

			*tul_refdiff,			//��ο��ı�����
			*tul_initreg,			//��ʼ����
			*tul_presm,				//��һ֡
			*tul_finreg,			//�������
			*tul_finlevel,			//����level

			*tul_curgd,				//�����ݶ�
			*tul_bakgd,				//�����ݶ�
			*tul_refimg,			//�ο�ͼ�����ڼ�¼��ʱ�䲻�������		
			*tul_nochglevel,		//û�иı�ļ���	

			*tul_initlevel,
			*tul_bakhtext,			//�����ĸ���������
			*tul_gddiffval,			//�ݶȲ�	
			*tul_gddiffsign;			//��ķ���

//	INT16	*tul_gddiff16;			//�ݶȲ�

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

//���Ʊ�����Χ
#define  VS_setRangeMax(a, b) ((a)=(a)>(b) ? (b):(a))
#define  VS_setRangeMin(a, b) ((a)=(a)<(b) ? (b):(a))
#define  VS_setRange(a, _min, _max)  ((a)=(a)>(_max) ? (_max):(a)); ((a)=(a)<(_min) ? (_min):(a));

#define  VS_abs(a) ((a)>0 ? (a):-(a))


#ifdef __cplusplus
}
#endif

#endif //__FS_DATADEF_H__
