/********************************************************************
	created:	2014/01/30
	created:	30:1:2014   11:49
	filename: 	D:\work\project\VSV\STEvaluation\STEvaluation\STE_Typedef.h
	file path:	D:\work\project\VSV\STEvaluation\STEvaluation
	file base:	STE_Typedef
	file ext:	h
	author:		SUNNAN
	
	purpose:	
*********************************************************************/
#ifndef __STE_TYPEDEF_H__
#define __STE_TYPEDEF_H__






//定义返回类型
#define STE_RES_OK				0
#define STE_RES_ERROR			1		//通用错误

#define STE_MODE_CAPFILE		0
#define STE_MODE_CAPCAM			1
#define STE_MODE_PLAYBACK		2


#define STE_IMAGE_WIDTH			352
#define STE_IMAGE_HEIGH			288


//警报：火情	　	0x2280
#define STE_SYSEVENT_FIRE_S                          233
//警报：烟雾	　	0x2281
#define STE_SYSEVENT_SMOKE_S							234

#define STE_SYSEVENT_FIRE_E                          263
//警报：烟雾	　	0x2281
#define STE_SYSEVENT_SMOKE_E							264

//定义RGB图像结构
typedef struct  tagIVFD_RgbImage
{
	int        width;                           //  图像宽度
	int        height;                         //  图像高度
	unsigned int  frame_mun;        //  图像序号，0起始
	unsigned int  time;                  //  
	unsigned char * data_r;            //  数据指针
	unsigned char * data_g;           //  数据指针
	unsigned char * data_b;           //  数据指针
} IVFD_RgbImage;

//定义YUV图像结构
typedef struct  tagIVFD_YuvImage
{
	int       width;    //  图像宽度
	int       height;   //  图像高度
	unsigned int  frame_mun;  //  图像序号，0起始
	unsigned int  time;   //  
	unsigned char * data_y;   //  数据指针
	unsigned char * data_u;   //  数据指针
	unsigned char * data_v;   //  数据指针
} IVFD_YuvImage;

//定义灰度图象结构
typedef struct  tagIVFD_Image
{
	int       width;    //  图像宽度
	int       height;   //  图像高度
	unsigned int	time;
	unsigned int	frame;
	unsigned char * data;   //  数据指针
} IVFD_Image;

//定义点结构
typedef struct  tagIVFD_Point
{
	short   x;      //水平坐标
	short   y;      //垂直坐标
} IVFD_Point;

//定义线段结构
typedef struct  tagIVFD_Line
{
	IVFD_Point  point_start;    //线段起始点
	IVFD_Point  point_end;      //线段终止点
} IVFD_Line;

//定义矩形结构，默认左下为坐标原点，即assert(top>bottom) && assert(right>left)
typedef struct  tagIVFD_Rect
{
	short   left;
	short   bottom;
	short   right;
	short   top;
} IVFD_Rect; 

typedef struct  tagIVFD_Target
{
	unsigned int type;
	IVFD_Rect rect;
} IVFD_Target; 

#define STE_TARGET_MAX_NUM		8
typedef struct  tagIVFD_TargetSet
{
	unsigned int frame;
	unsigned int time;
	int num;
	IVFD_Target targets[STE_TARGET_MAX_NUM];
} IVFD_TargetSet; 

typedef struct  tagIVFD_Event
{
	unsigned int type;
	unsigned int time;
	unsigned int frame;
	unsigned int status;
} IVFD_Event; 

#define STE_EVENT_MAX_NUM		8
typedef struct  tagIVFD_EventSet
{
	int num;
	IVFD_Event events[STE_EVENT_MAX_NUM];
} IVFD_EventSet; 
//config for preset
typedef struct tagST_AlgoConfig
{
	int val_sense;	//Sensitivity	0~99,
	int val_delay;	//delay time seconds	0~99,
	int val_fov;	//field of view, 
	int val_static_det;
	int alarm_delay;	// 1~9
	int area_min;	//min area for detection;	0~99
	char scene[STE_IMAGE_WIDTH*STE_IMAGE_HEIGH];
}ST_AlgoConfig;

typedef struct  
{	
	int frame_index;
	int frame_num;
	int fps;
	int flg_used;	//标识该数据已经被用过一次了
	IVFD_Image image;
	IVFD_TargetSet target_set;
	IVFD_EventSet  event_set;
}STE_ImageBuf;

#ifdef __cplusplus
extern "C"	{
#endif




	//declare




#ifdef __cplusplus
	}
#endif






#endif //__STE_TYPEDEF_H__

