
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

//////////���ͻ�����������////////////////////////////////////////////

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

/////////////////////�������ͽṹ/////////////////////////////////////
////�Ҷ�ͼ�񣻵㣻��
typedef	RGBIMAGE	VSDET_RGBIMAGE;
typedef	GRAYIMAGE	VSDET_GRAYIMAGE;
typedef	ZPOINT		VSDET_ZPOINT;
typedef	ZRECT		VSDET_ZRECT;

typedef struct 
{
	INT16 width, height;
} VSDET_SIZE;
//////////////////////////////////////////////////////////////////////


////////////////////////////////�����궨��////////////////////////////
//#define	REGION_FIRE_NUM		16
#define	REGION_SMOKE_NUM	16
#define REGION_TEMP_NUM		32
#define TRACE_LENGTH_NUM	20

#define SVM_SV_NUM		190		//����������������
#define SVM_NUM			10		//��������

#undef MAX_TARGET_CNT
#define MAX_TARGET_CNT		16
//#define MAX_VAEVT_CNT		(MAX_TARGET_CNT*2)


#define EVENT_ID_VSD_MIN	0x80000000
#define EVENT_ID_VSD_MAX	0x8FFFFFFF
#define EVENT_ID_ADD(id) ( (id)>=EVENT_ID_VSD_MAX ? EVENT_ID_VSD_MIN:(id+1) )
//////////////////////////////////////////////

////////////////////////////////////
//����ʶ�����Ͷ��壻
#define SMOKE_NODET		0			//�����
#define SMOKE_TUNNEL	0x01		//����
#define SMOKE_INDOOR	0x02		//���ڰ�
// #define SMOKE_OUTDOOR	0x04	//�����
// #define SMOKE_FOREST	0x08		//ɭ�ְ�
/////////////////////////////////////////////

//////////////�߼���������////////////////////
typedef struct VSDET_PARA
{
	UINT32 interval;				//[1,10],��������interval֡����1֡
	UINT8 det_type;					//[1,8],������ͣ�SMOKE_INDOOR	0x02
	UINT8 sensitivity;				//[1,100],60,������
	UINT8 edgelength_min;			//[6,10000],20,��С����
	UINT8 comdeg;					//���ڵ���
	UINT8 delay_time;		        //

	//indoor
	UINT8 ind_ortang;				//[1,90],40,ͬ���,�ڴ˷�Χ�ڵĹ���������Ϊһ��
	UINT8 ind_adddiff;				//50,�������С���Ĳ��ǣ�diff-50��
	UINT8 ind_netoffset;			//100,
	UINT8 ind_opt_level;			//[100,250],170 ����level���շָ���ֵ
	UINT8 ind_opt_intensity;		//[0,100],2,���ڴ�ǿ�ȵĹ�����������

	UINT8 ind_blur_bk_inter;		//����֡��� 
	UINT8 ind_blur_bk_w;			//����Ȩ��
	UINT8 ind_blur_bk_thrld;        //��ֵ
	UINT8 ind_blur_level_thrld;        //��ֵ

	BOOL  flg_enable_subprocess;	//enable sub process
	UINT8 flg_svm_noused;        //use svm

	//֧������������
	INT32	*ind_svm_class,			//�ڼ����֧��������
			*ind_svm_numsv;			//֧�������ĸ���
	float	*ind_svm_gramm,			//gramm
			*ind_svm_rho,			//ƫ��
		
			*ind_svm_coef[SVM_NUM],	//ϵ��	
			*ind_svm_sv[SVM_NUM];	//֧������


	//tunnel
	UINT8 tul_bakuprate;			//����������
	UINT8 tul_cordisap;				//����������ʧ�ٶ�
	UINT8 tul_nochgdisap;			//�����������ʧ�ٶ�
	UINT8 tul_adddiff1;
	UINT8 tul_adddiff2;

	UINT8 tul_prcheight;			//����߶�
	UINT8 tul_corcof;				//���ϵ��
	UINT8 tul_flat;					//ƽ����
	UINT8 tul_contrast;				//�Աȶ�

}VSDET_PARA;
///////////////////////////////////////////////////



////�����Ͷ���////////////////////
typedef enum
{
	SMOKE_NONE			= 0,
	SMOKE_DEL,
	SMOKE_LIKE,
	SMOKE_IDENTITY	
}SMOKE_REGION_TYPE;
////////////////////////////////////


#define EDGE_LENGTH_MAX		2048
//�ñ�Ե�������ı�Ե���ݽṹ��pData�б����Եÿ���������ֵ
#define BLUR_BLOCK_SIZE 16

#define CAL_BLUR_BLOCK_SIZE(a)	(((a)+BLUR_BLOCK_SIZE-1)/BLUR_BLOCK_SIZE)
typedef struct vsdet_edge_line
{
	INT32	 nLengthUsed;	//��Ե�ܵ���
	UINT32	 edge_point[EDGE_LENGTH_MAX];	//low 16bit = cord x, high 16bit = cord y

} VSDET_EDGELINE;


////////////////////�����������//////////////////////
typedef struct vsdet_region_character
{
	//�����ڹ켣
//#ifdef WIN32
	int				ind_NnetP;
	VSDET_ZRECT		region_rect;
//#endif
	
	//��������
	//����
	int		ind_DiffStat;			//��ǰ֡���ڡ�0,20����Χ�롾0,255����Χ�ı�����
	int		ind_SuppressRate;		//�ݶȲ��ڡ�20,255����Χռ������ı���
	int		ind_Contrast;			//�Ҷ�ֵ��80%��Χ�ڵ����ص�ĻҶȷ�Χռ����255����ı���
	int		ind_GradChgCon;			//ǰ����֡ͼ���ݶȶ�����45�ĵ��У��ݶȲ�С��10�ĵ�ı��������ݶȵ�һ������ط�����
	int		ind_BigGrad;			//��ǰ�ݶ��ڡ�30,255����Χ�ڵı���

	int		ind_DiffGrad;			//��ǰ֡����ݶ��ڡ�8,255���ı���
	int		ind_GradDirect;			//���������ݶ�һ�µĵ����ܵ����ı�����
	int		ind_DirectPart;			//���������ݶ�һ�µĵ����ݶ���Ч������0�������ı�����
	int		ind_PixIncreas;			//��֡ͼ����ű仯һ�������ԣ�
	
	int		ind_OptMax;				//���������һ�µĵ����ı���
	int		ind_OptZero;			//��������Ϊ0�ĵ�ı���

	int		ind_GdDirMax;			//�ݶȷ���һ�µĵ����ı���
	int		ind_GdDirZero;			//�ݶȷ���Ϊ0�ĵ�ı���
	
	int		ind_SpotRate;			//����֡���2�׵��ڡ�4,20����Χ�ı���
	int		ind_OptGrade;			//�������������ݶȴ���0�ĵ�ı���
	int		ind_ChangeRate;			//֡����ŵ��ݶ��ڡ�0xf��0xFF����Χ�ڵı���
	int		ind_AddRate;			//֡��Ϊ�������ر���


	 
	int		AreaRate;				//��4000���ص���ȵı���*100%��������50

	//���

	int		tul_CorP;			//���ϵ��	
	int		tul_AvgDiff;		//ƽ��ֵ�Ĳ�
	int		tul_Contrast;		//�Աȶ�
	int		tul_CoMat;
	int		tul_CurGrad;		//���ݶȵı�

	int		tul_gdinc;
	int		tul_gdred;
	int		tul_HTextRate;
	int		tul_LTextRate;
	int		tul_ChgRate;

} VSDET_REGION_CHARACTER;

typedef struct vsd_region_temporal
{
	SMOKE_REGION_TYPE type;

	INT32 Area;		//������Ч������������2pixel
	INT32 rect_area;
	//�켣����
//#ifdef WIN32

	INT32 MatchNum;		//ƥ�����,ÿ��ƥ���1
	INT32 TraceIndex;    //�켣��������
	BOOL  bMatchCur;	//�͵�ǰ�Ƿ�ƥ��

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
