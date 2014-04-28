

#include "stdafx.h"

#include "AlgoApi.h"

char _vsv_dll_path[VSV_MAX_STR_SIZE] = "/var/tmp/";//算法库用的默认路径

//config path
#define PATH_zone_vsd 		"\\algocfg\\par_ps1_zone_vsd.dat"
#define PATH_vana_vsd 		"\\algocfg\\par_ps1_vana_vsd.txt"
#define PATH_vsdet_conf		"\\algocfg\\par_vsdet_conf.txt"
#define PATH_class_1		 "\\algocfg\\par_vsd_class_1.dat"
#define PATH_class_2		 "\\algocfg\\par_vsd_class_2.dat"
#define PATH_class_3		 "\\algocfg\\par_vsd_class_3.dat"
#define PATH_class_4		 "\\algocfg\\par_vsd_class_4.dat"
#define PATH_class_5		 "\\algocfg\\par_vsd_class_5.dat"
#define PATH_class_6		 "\\algocfg\\par_vsd_class_6.dat"
#define PATH_class_7		 "\\algocfg\\par_vsd_class_7.dat"
#define PATH_class_8		 "\\algocfg\\par_vsd_class_8.dat"
#define PATH_class_9		 "\\algocfg\\par_vsd_class_9.dat"
#define PATH_class_10		 "\\algocfg\\par_vsd_class_10.dat"

static char parfil_ps_zone_vsd[VSV_MAX_STR_SIZE] = "\\algocfg\\par_ps1_zone_vsd.dat";
static char parfil_ps_vana_vsd[VSV_MAX_STR_SIZE] = "\\algocfg\\par_ps1_vana_vsd.txt";
static char parfil_vsdet_conf[VSV_MAX_STR_SIZE]	= "\\algocfg\\par_vsdet_conf.txt";
static char parfil_vsd_class_1[VSV_MAX_STR_SIZE] = "\\algocfg\\par_vsd_class_1.dat";
static char parfil_vsd_class_2[VSV_MAX_STR_SIZE] = "\\algocfg\\par_vsd_class_2.dat";
static char parfil_vsd_class_3[VSV_MAX_STR_SIZE] = "\\algocfg\\par_vsd_class_3.dat";
static char parfil_vsd_class_4[VSV_MAX_STR_SIZE] = "\\algocfg\\par_vsd_class_4.dat";
static char parfil_vsd_class_5[VSV_MAX_STR_SIZE] = "\\algocfg\\par_vsd_class_5.dat";
static char parfil_vsd_class_6[VSV_MAX_STR_SIZE] = "\\algocfg\\par_vsd_class_6.dat";
static char parfil_vsd_class_7[VSV_MAX_STR_SIZE] = "\\algocfg\\par_vsd_class_7.dat";
static char parfil_vsd_class_8[VSV_MAX_STR_SIZE] = "\\algocfg\\par_vsd_class_8.dat";
static char parfil_vsd_class_9[VSV_MAX_STR_SIZE] = "\\algocfg\\par_vsd_class_9.dat";
static char parfil_vsd_class_10[VSV_MAX_STR_SIZE] = "\\algocfg\\par_vsd_class_10.dat";

VSV_Handle ALGO_VSD_create(int img_w, int img_h, ST_AlgoConfig* cfg)
{
	VSV_Handle res = NULL;
	uint32_t ver;
	MODULE_VSD* algo_handle;
	VAMEM_SET algo_mem_req;
	char cfg_file_path[VSV_MAX_STR_SIZE];


	algo_handle = (MODULE_VSD*)malloc(sizeof(MODULE_VSD));
	if (!algo_handle)
	{
		return res;
	}

	if (img_w!= STE_IMAGE_WIDTH || img_h != STE_IMAGE_HEIGH)
	{
		printf("image size %d:%d is supported \r\n", img_w,img_h);
	}
#ifdef ALGO_HALFCIF

	printf("create algo @ haf-cif 352*144\r\n");
	img_h = img_h /2;
	//img_w = img_w/2;
#else
	#ifdef ALGO_HALFCIF176288 
		printf("create algo @ haf-cif 176*288\r\n");
		//img_h = img_h /2;
		img_w = img_w/2;
	#else
		printf("create algo @ cif\r\n");
	#endif
	
#endif



	//read vsd version
	VSD_GetVersion( algo_handle, &ver );
	printf("Algo Version: V%d.%d.%d \r\n", (ver&0x0f0000)>>16, (ver&0xf00000)>>20, (ver&0xff000000)>>24);


	//get algo mem requirement
	algo_mem_req.img_w = img_w;
	algo_mem_req.img_h = img_h;
	VSD_GetMemReq( algo_handle, &algo_mem_req );
	VAMEMS_alloc( &algo_mem_req );
	VSD_Initialize( algo_handle, &algo_mem_req );

	//read config files for debug
	{
		VAPARA *vapara = VAPARA_alloc( VAPARA_CLBR_BUFLEN, VAPARA_VANA_BUFLEN,
			VAPARA_ADVBUF_BUFCNT, VAPARA_ADVBUF_BUFLEN, NULL );

		VAPARA_STRARRAY fils_scene, fils_advance;
		memset( &fils_scene, 0, sizeof(VAPARA_STRARRAY) );
		memset( &fils_advance, 0, sizeof(VAPARA_STRARRAY) );

		//init temp str first
		strncpy_s(parfil_ps_vana_vsd,PATH_vana_vsd, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_ps_zone_vsd,PATH_zone_vsd, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsdet_conf,PATH_vsdet_conf, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_1,PATH_class_1, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_2,PATH_class_2, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_3,PATH_class_3, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_4,PATH_class_4, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_5,PATH_class_5, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_6,PATH_class_6, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_7,PATH_class_7, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_8,PATH_class_8, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_9,PATH_class_9, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_10,PATH_class_10, VSV_MAX_STR_SIZE);


		fils_scene.strings[VPARASCNBUFNUM_CLBR] = NULL;
		fils_scene.strings[VPARASCNBUFNUM_ZONE_CLBR] = NULL;
		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_ps_vana_vsd, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_ps_vana_vsd, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_scene.strings[VPARASCNBUFNUM_VANA] = parfil_ps_vana_vsd ;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_ps_zone_vsd, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_ps_zone_vsd, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_scene.strings[VPARASCNBUFNUM_ZONE_VANA] = parfil_ps_zone_vsd;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_vsdet_conf, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsdet_conf, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_advance.strings[VPARAADVBUFNUM_VSD] = parfil_vsdet_conf;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_vsd_class_1, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_1, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_advance.strings[VPARAADVBUFNUM_VSD_CLASS_1] = parfil_vsd_class_1;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_vsd_class_2, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_2, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_advance.strings[VPARAADVBUFNUM_VSD_CLASS_2] = parfil_vsd_class_2;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_vsd_class_3, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_3, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_advance.strings[VPARAADVBUFNUM_VSD_CLASS_3] = parfil_vsd_class_3;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_vsd_class_4, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_4, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_advance.strings[VPARAADVBUFNUM_VSD_CLASS_4] = parfil_vsd_class_4;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_vsd_class_5, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_5, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_advance.strings[VPARAADVBUFNUM_VSD_CLASS_5] = parfil_vsd_class_5;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_vsd_class_6, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_6, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_advance.strings[VPARAADVBUFNUM_VSD_CLASS_6] = parfil_vsd_class_6;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_vsd_class_7, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_7, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_advance.strings[VPARAADVBUFNUM_VSD_CLASS_7] = parfil_vsd_class_7;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_vsd_class_8, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_8, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_advance.strings[VPARAADVBUFNUM_VSD_CLASS_8] = parfil_vsd_class_8;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_vsd_class_9, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_9, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_advance.strings[VPARAADVBUFNUM_VSD_CLASS_9] = parfil_vsd_class_9;

		strncpy_s(cfg_file_path, _vsv_dll_path, VSV_MAX_STR_SIZE);
		strncat_s(cfg_file_path, parfil_vsd_class_10, VSV_MAX_STR_SIZE);
		strncpy_s(parfil_vsd_class_10, cfg_file_path, VSV_MAX_STR_SIZE);
		fils_advance.strings[VPARAADVBUFNUM_VSD_CLASS_10] = parfil_vsd_class_10;

		VSD_InitParaVAPARA( vapara, &fils_scene, &fils_advance, img_w, img_h, NULL );

		VSD_ConfigParameter( algo_handle, vapara );

		VAPARA_free( vapara, VAPARA_ADVBUF_BUFCNT, NULL );
	}
	res = algo_handle;
	return res;
}



void ALGO_VSD_destroy(VSV_Handle handle, int img_w, int img_h)
{
	MODULE_VSD* algo_handle;
	VAMEM_SET algo_mem_req;

	algo_handle = (MODULE_VSD* )handle;

#ifdef ALGO_HALFCIF
	img_h = img_h/2;
	printf("destroy algo @ haf-cif 352*144\r\n");
	//img_w = img_w/2;
#else
	#ifdef ALGO_HALFCIF176288 
		printf("destroy algo @ haf-cif 176*288\r\n");
		img_w = img_w/2;
	#else
		printf("destroy algo @ cif\r\n");
	#endif
	
#endif

	//get algo mem requirement
	algo_mem_req.img_w = img_w;
	algo_mem_req.img_h = img_h;
	VSD_GetMemReq( algo_handle, &algo_mem_req );
	algo_mem_req.mems[0].mem = algo_handle->m_sHwRes.mem_mgr.memmgrs[0].mem_addr;
	algo_mem_req.mems[1].mem = algo_handle->m_sHwRes.mem_mgr.memmgrs[1].mem_addr;
	algo_mem_req.mems[2].mem = algo_handle->m_sHwRes.mem_mgr.memmgrs[0].nodes;

	VSD_Terminate( algo_handle );
	VAMEMS_free( &algo_mem_req );
	
}



void ALGO_VSD_setConfig(VSV_Handle handle, ST_AlgoConfig * cfg)
{
		MODULE_VSD* algo_handle;
	
	algo_handle = (MODULE_VSD* )handle;

	int i, j;
	
	switch (cfg->val_sense)
	{
		//change saturated detection at same time
	case 1://small fov
		algo_handle->vsdet_para->sensitivity = 60;

		algo_handle->vsdet_para->ind_blur_bk_inter = 50;
		algo_handle->vsdet_para->ind_blur_bk_thrld = 235;
		algo_handle->vsdet_para->ind_blur_level_thrld = 50;
		break;
	case 2:
		algo_handle->vsdet_para->sensitivity = 70;

		algo_handle->vsdet_para->ind_blur_bk_inter = 50;
		algo_handle->vsdet_para->ind_blur_bk_thrld = 210;
		algo_handle->vsdet_para->ind_blur_level_thrld = 40;
		break;
	case 3:
		algo_handle->vsdet_para->sensitivity = 80;

		algo_handle->vsdet_para->ind_blur_bk_inter = 50;
		algo_handle->vsdet_para->ind_blur_bk_thrld = 180;
		algo_handle->vsdet_para->ind_blur_level_thrld = 30;
		break;
	default:
		algo_handle->vsdet_para->sensitivity = 70; 
		algo_handle->vsdet_para->ind_blur_bk_inter = 50;
		algo_handle->vsdet_para->ind_blur_bk_thrld = 210;
		algo_handle->vsdet_para->ind_blur_level_thrld = 40;
		break;
	}

	algo_handle->vsdet_para->edgelength_min = cfg->area_min/3;
	if (algo_handle->vsdet_para->edgelength_min < 50)
	{
		algo_handle->vsdet_para->edgelength_min  = 50;
	}

#ifdef ALGO_HALFCIF
	algo_handle->vsdet_para->edgelength_min /=2;
#endif

#ifdef ALGO_HALFCIF176288
	algo_handle->vsdet_para->edgelength_min /=2;
#endif
	

	switch (cfg->val_fov)
	{
	case 1://small fov
		algo_handle->vsdet_para->interval = 4;
		break;
	case 2:
		algo_handle->vsdet_para->interval = 8;
		break;
	default:
		algo_handle->vsdet_para->interval = 4;  
		break;
	}

	switch (cfg->val_static_det)
	{
	case 0://disable
		algo_handle->vsdet_para->ind_blur_bk_inter = 0;
		algo_handle->vsdet_para->ind_blur_bk_thrld = 210;
		break;
/*
	case 1://low
		algo_handle->vsdet_para->ind_blur_bk_inter = 50;
		algo_handle->vsdet_para->ind_blur_bk_thrld = 225;
		break;
	case 2://high
		algo_handle->vsdet_para->ind_blur_bk_inter = 50;
		algo_handle->vsdet_para->ind_blur_bk_thrld = 180;
		break;
*/
	default:
//		algo_handle->vsdet_para->ind_blur_bk_inter = 0;
//		algo_handle->vsdet_para->ind_blur_bk_thrld = 210;
		break;
	}

		//alarm delay 
	algo_handle->vsdet_para->delay_time = cfg->alarm_delay;


	//set scene data
	//
	//memcpy(algo_handle->vsdet_buffer_var->zone_mask, cfg->scene, algo_handle->width*algo_handle->height);

	for (i=0; i<algo_handle->height;i++)
	{
		for (j=0; j<algo_handle->width; j++)
		{
#ifdef ALGO_HALFCIF

			algo_handle->vsdet_buffer_var->zone_mask[i*algo_handle->width  + j] = (unsigned char)(cfg->scene[i*algo_handle->width*2 + j])>0x00 ? 0xFF : 0x00;
#else
			algo_handle->vsdet_buffer_var->zone_mask[i*algo_handle->width  + j] = (unsigned char)(cfg->scene[i*algo_handle->width + j])>0x00 ? 0xFF : 0x00;

#endif

		}
		
	}
}


int ALGO_VSD_Process( VSV_Handle hModule, IVFD_YuvImage  *pImageYUV )
{
	YUVIMAGE422 image;
	memset(&image, 0, sizeof(image));
	image.dataY = pImageYUV->data_y;
	image.height = pImageYUV->height;
	image.width = pImageYUV->width;
	image.time = pImageYUV->time;
	return VSD_ProcessImage( hModule, &image );
}

int ALGO_VSD_GetResults(  VSV_Handle algo_handle, VARESULT *va_result )
{
	return VSD_GetResults( algo_handle, va_result );
}

void blend_row_Y32(unsigned int *dst, unsigned int *src, unsigned int w) 
{	
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned long long hi;
	unsigned long long lo;	
	unsigned int i;

	unsigned long long Mask1 = 0xfcfcfcfc;
	unsigned long long Mask2 = 0x03030303;
	const unsigned int *src2; 
	const unsigned int *src3; 

	src2 = src + w;
	src3= src2 + w;

	//#pragma MUST_ITERATE(44);

	for(i = 0; i< w; i++)
	{
		a = *src++;
		b = *src2++;
		c = *src3++;
		hi = (unsigned long long)(a & Mask1) + 2*(b & Mask1) + (c & Mask1);
		lo = (unsigned long long)(a & Mask2) + 2*(b & Mask2) + (c & Mask2) + Mask2;

		*dst++ = (unsigned int)((hi + (lo & 0x0c0c0c0c))>>2);
	}
}