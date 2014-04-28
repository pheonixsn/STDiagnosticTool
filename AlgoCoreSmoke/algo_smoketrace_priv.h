/**********************************************************************************************
-----------------------------------------------------------------------------------------------
Name :                  algo_smoketrace_priv.h 
Description :          
Product Number :        
Revision :              V1.0.0          
Module :                global
System :                
Language :              ANSI C
Develop Environment :   SlickEdit V17.0.0
Running Environment :   Debian V6.0.6
------------------------------------------------------------------------------------------------
版权声明
------------------------------------------------------------------------------------------------
Creation Data :             <5/7/2013   15:47:00>
Chief Editor :              <sunnan>
Participant :               <参与者>
Audit :                     <检查者>
Edit Log :                  <编辑记录>

Release :                   <>

Copyright (C) 2013 BendWeaver - All Rights Reserved
------------------------------------------------------------------------------------------------
***********************************************************************************************/

#ifndef __ALGO_SMOKETRACE_PRIV_H_INCL__
#define __ALGO_SMOKETRACE_PRIV_H_INCL__

#include "./algo_smoketrace.h"
#include <pthread.h>

//***************************************************************************
//
//global definition for  algorithm
//
//***************************************************************************

#define VSV_VERSION	
#define VSV_VERSION_STR	"2.02.06"
#define VSV_VERSION_STATIC	{2,2,6,0}
//config for preset
typedef struct tagVSV_AlgoConfig
{
	int flg_used;
	int val_sense;	//Sensitivity	0~99,
	int val_delay;	//delay time seconds	0~99,
	int val_delay_alarm;				//
	int val_fov;	//field of view, 
	int val_static_det;
	int area_min;	//min area for detection;	0~99
	int flg_highsense;		//for prealarm only
	int val_preset_duration;	//duration at one preset; 1~3600 second, 0:don't leave
	unsigned int patrol_presurv_time;			//during 4s for prealarm
	unsigned int patrol_surv_time;			//during 20s at this preset
	unsigned int patrol_sleep_time;			//during 2s at this preset
	unsigned int patrol_stay_count;			//first time at the preset					//
	unsigned int patrol_sleep_count;		//first time at the preset					//
	int patrol_next;				//next preset id
	char description[VSV_MAX_STR_SIZE];
	char scene[VSV_MAX_SCENE_SIZE];		//scene mask data
}VSV_AlgoConfig;

//config for channel(including VSV_MAX_PRESETNUM presets)
typedef struct tagVSV_Channel
{
	int flg_used;
	int id_chan;			//Unique value in system
	int image_type;			//GRAY or YUV
	int image_width;		//cif, d1 ...
	int image_height;		//
	int image_interval;		//40 for PAL

	int preset_num;	//num of preset position. 0: fixed camera
	int pre_preset_id;	//preset used previous
	int pre_active_flg;	//use to decide act 0->1
	int flg_alarm;	//for pzt cam,if a alarm,the cam will stay at the preset,be reset when active 0-1
	int flg_prealarm;	//for pzt cam only,if a prealarm,the cam will start alarm detection,be reset when preset changed
	pthread_mutex_t mutex;	//the lock for channel
	VSV_AlgoConfig	preset[VSV_MAX_PRESETNUM];
	VSV_Handle algo_handle;
}VSV_Channel;

typedef struct tagVSV_Object
{
	int flg_initial;

	VSV_Version version;

	int val_chan_id;	//valid value of chan id now

	VSV_Channel chan[VSV_MAX_CHANNEL];
}VSV_Object;

//config for now image
typedef struct tagVSV_NewimageConfig
{
	VSV_Version fit_version;
	int image_id;	//0~999999
	unsigned int time_stamp_low;	//seconds from 1970-01-01 00:00	
	unsigned int time_stamp_high;	//millisecond
	int flg_active;	//0 for no useful
	int preset_num;	//0 : not a valid, ptz camera is running!
}VSV_NewimageConfig;


//image result 
typedef struct tagVSV_Target
{
	int target_x_min;	//top left coordinate
	int target_x_max;
	int target_y_min;
	int target_y_max;

	int alert;			//1:be alert; 0:otherwise
	int alert_type;		//1:build-up smoke; 2:moving smoke; 3:flame; 0:otherwise
}VSV_Target;

typedef struct tagVSV_ProcessResult
{
	VSV_Version fit_version;
	unsigned int time_stamp_low;	//seconds from 1970-01-01 00:00	
	unsigned int time_stamp_high;	//millisecond
	int next_preset;				//control ptz camera
	int target_num;					//0 for static camera
	VSV_Target	target[VSV_MAX_TARGET_NUM];	//targets
}VSV_ProcessResult;

//for a 32bit result
typedef struct tagVSV_DetResult
{
	unsigned int alert			:1	;//there is an alarm
	unsigned int bad_condition	:1	;//image is not good to do analysis
	unsigned int smoke_buildup	:1	;//alarm type
	unsigned int smoke_move		:1	;//alarm type

	unsigned int flame			:1	;//alarm type
	unsigned int reserved1		:1	;
	unsigned int reserved2		:1	;
	unsigned int reserved3		:1	;

	unsigned int working		:1	;//image has been used for analysis
	unsigned int activative		:1	;//flag active in new_image_param section
}VSV_DetResult;

typedef union tagVSV_DetResultL
{
	long val_result;
	VSV_DetResult data_result;
}VSV_DetResultL;


#define VSV_chanidPlus(id) ((id)>=VSV_CHANNEL_ID_MAX?VSV_CHANNEL_ID_MIN:(id)+1)


#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif  //__cplusplus

#endif // __ALGO_SMOKETRACE_PRIV_H_INCL__

