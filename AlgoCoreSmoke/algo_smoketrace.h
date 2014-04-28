/**********************************************************************************************
-----------------------------------------------------------------------------------------------
Name :                  algo_smoketrace.h 
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
Creation Data :             <5/3/2013   21:21:06>
Chief Editor :              <sunnan>
Participant :               <参与者>
Audit :                     <检查者>
Edit Log :                  <编辑记录>

Release :                   <>

Copyright (C) 2013 BendWeaver - All Rights Reserved
------------------------------------------------------------------------------------------------
***********************************************************************************************/

#ifndef __ALGO_SMOKETRACE_H_INCL__
#define __ALGO_SMOKETRACE_H_INCL__

//define result code, 0 is OK
#define VSV_RESULT_OK					0
#define VSV_RESULT_OK_SKIP				1
#define VSV_RESULT_ERROR				-1
#define VSV_RESULT_ERROR_MEMORY			-11
#define VSV_RESULT_ERROR_LICENSE		-12
#define VSV_RESULT_ERROR_CHANNEL_FULL	-13
#define VSV_RESULT_ERROR_PPRESET_FULL	-14
#define VSV_RESULT_ERROR_PRESET_NOSET	-15
#define VSV_RESULT_ERROR_NOINITIAL		-16
#define VSV_RESULT_ERROR_PARAM			-17
#define VSV_RESULT_ERROR_BADIMAGE		-101

//range of channel id
#define VSV_CHANNEL_ID_MAX	0x70000000
#define VSV_CHANNEL_ID_MIN	0x00000400

//define image Type
#define VSV_TYPE_IMAGE_GRAY			0x01
#define VSV_TYPE_IMAGE_YUV420		0x02

//define image size
#define VSV_CIF_IMAGE_WIDTH		352
#define VSV_CIF_IMAGE_HEIGHT	288

#define VSV_D1_IMAGE_WIDTH		704
#define VSV_D1_IMAGE_HEIGHT		576
#define VSV_MAX_IMAGE_WIDTH		VSV_CIF_IMAGE_WIDTH
#define VSV_MAX_IMAGE_HEIGHT	VSV_CIF_IMAGE_HEIGHT


//define alert type
#define VSV_ALERT_OTHER					0x00
#define VSV_ALERT_SMOKE_BUILDUP			0x01
#define VSV_ALERT_SMOKE_MOVE			0x02
#define VSV_ALERT_FLAME					0x03


//channel & preset
#define VSV_MAX_PRESETNUM		(4)
#define VSV_MAX_CHANNEL			(1)
#define VSV_MAX_TARGET_NUM					(20)

//advanced parameter num
#define VSV_MAX_ADPARAMNUM		(25)


//memory limitation
#define VSV_MAX_STR_SIZE					(256)
#define VSV_MAX_LICENSE_PARAM_SIZE			(1024*1)
#define VSV_MAX_INIT_PARAM_SIZE          	(1024*32)
#define VSV_MAX_NEWIMAGE_PARAM_SIZE        (1024*1)
#define VSV_MAX_TEST_RESULT_SIZE            (1024*5)		
#define VSV_MAX_IMAGE_SIZE               	(VSV_MAX_IMAGE_WIDTH*VSV_MAX_IMAGE_HEIGHT*2)
#define VSV_MAX_SCENE_SIZE               	(VSV_MAX_IMAGE_WIDTH*VSV_MAX_IMAGE_HEIGHT)
#define VSV_MAX_VERSION_SIZE				VSV_MAX_STR_SIZE



//lib file name
#define VSV_DLL_NAME "libvgt_VSV.so"

//lib xport func name
#define VSV_FNAME_GETVERSION "vgt_get_version"
#define VSV_FNAME_INIT "vgt_VSV_init"
#define VSV_FNAME_NEWIMAGE "vgt_VSV_new_image"
#define VSV_FNAME_DEST "vgt_VSV_dest"
#define VSV_FNAME_LICENSE "vgt_VSV_licence"
#define VSV_FNAME_GETERROR "vgt_get_ret_err_msg"


/*Ptr to export functions*/
typedef long (*ptr_VSV_get_version) (char* version,unsigned int *size);
typedef long (*ptr_VSV_licence) (const char *VSV_licence_param,int VSV_licence_param_size);
typedef long (*ptr_VSV_init) (const char *pVSV_init_param,int VSV_init_param_size ,const char *scene_img_data,int scene_img_data_size,int *VSV_id);
typedef long (*ptr_VSV_new_image) (int VSV_id,const char *pVSV_new_image_param,int VSV_new_image_param_size,const char *img_data,int img_data_size,
					char *VSV_test_results,int *VSV_test_results_size,long *VSV_detect_results);
typedef long (*ptr_VSV_dest) (int VSV_id);
typedef char* (*ptr_VSV_get_err) (long ret_code);


//version struction
typedef struct tagVSV_Version
{
	unsigned char major : 8;         
    unsigned char minor : 8;         
    unsigned char little : 8;        
	unsigned char reserved : 8;     
}VSV_Version;

typedef void* VSV_Handle;


#ifdef __cplusplus
extern "C"
{
#endif
/*export functions*/

long vgt_get_version (char* version, unsigned int *size);

long vgt_VSV_licence (const char *VSV_licence_param,int VSV_licence_param_size);

long vgt_VSV_init (const char *pVSV_init_param,int VSV_init_param_size ,const char *scene_img_data,int scene_img_data_size,int *VSV_id);

long vgt_VSV_new_image (int VSV_id,const char *pVSV_new_image_param,int VSV_new_image_param_size,const char *img_data,int img_data_size,
					char *VSV_test_results,int *VSV_test_results_size,long *VSV_detect_results);

long vgt_VSV_dest (int VSV_id);

char* vgt_get_ret_err_msg (long ret_code);


#ifdef __cplusplus
}
#endif  

#endif 

