// DlgCapFile.cpp : 实现文件
//

#include "stdafx.h"
#include "STEvaluation.h"


#include "STEvaluationDlg.h"

#include "DlgCapFile.h"
#include "afxdialogex.h"

#include "AlgoApi.h"

//处理thread
//信令线程
static DWORD WINAPI thread_proc(LPVOID lpParam);


// CDlgCapFile 对话框

IMPLEMENT_DYNAMIC(CDlgCapFile, CDialogEx)

CDlgCapFile::CDlgCapFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCapFile::IDD, pParent)
	, m_file_video(_T(""))
	, m_video_clip_start(0)
	, m_video_clip_end(0)
	, m_video_clip_enable(FALSE)
{
	;
}

CDlgCapFile::~CDlgCapFile()
{
}

void CDlgCapFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BROWSE, m_file_video);
	DDX_Text(pDX, IDC_EDIT_CLIPBEGIN, m_video_clip_start);
	DDV_MinMaxInt(pDX, m_video_clip_start, 0, 999999);
	DDX_Text(pDX, IDC_EDIT_CLIPEND, m_video_clip_end);
	DDV_MinMaxInt(pDX, m_video_clip_end, 0, 999999);
	DDX_Check(pDX, IDC_CHECK_CLIP_ENABLE, m_video_clip_enable);
}


BEGIN_MESSAGE_MAP(CDlgCapFile, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgCapFile::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CDlgCapFile::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CDlgCapFile::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDlgCapFile::OnBnClickedButtonStop)
	ON_WM_PAINT()
	ON_MESSAGE(WM_MY_MESSAGE_CAP_FILE, OnMyMsg) 
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_STEP, &CDlgCapFile::OnBnClickedButtonStep)
	ON_BN_CLICKED(IDC_BUTTON_CFG, &CDlgCapFile::OnBnClickedButtonCfg)
	ON_BN_CLICKED(IDC_BUTTON_SCREENSHOT, &CDlgCapFile::OnBnClickedButtonScreenshot)
END_MESSAGE_MAP()


// CDlgCapFile 消息处理程序
LRESULT CDlgCapFile::OnMyMsg(WPARAM wParam, LPARAM lParam)
{
	UINT32 msg_type;
	int i, j;
	char * pdata;

	msg_type = (UINT32)wParam;

	switch(msg_type)
	{
	case CAP_FILE_TYPE_QUIT:
		Stop();
		break;
	case CAP_FILE_TYPE_UPDATEIMAGE:
		//post result
		if (m_flg_process)
		{
			WaitForSingleObject(m_proc_lock, INFINITE);
			if (!m_img_show.IsNull())
			{
				m_img_show.Destroy();
			}
			m_img_show.Create(STE_IMAGE_WIDTH, -STE_IMAGE_HEIGH, 24);

			pdata=(char*)m_img_show.GetBits(); 

			//add deinterlace
			memcpy(pdata + 0*m_img_show.GetPitch(), (char*)m_proc_result_buf.image.data+0*STE_IMAGE_WIDTH*4, STE_IMAGE_WIDTH*3);
			memcpy(pdata + (STE_IMAGE_HEIGH-1)*m_img_show.GetPitch(), (char*)m_proc_result_buf.image.data+(STE_IMAGE_HEIGH-1)*STE_IMAGE_WIDTH*4, STE_IMAGE_WIDTH*3);
			for (i=1;i<STE_IMAGE_HEIGH-1;i++)
			{
				//memcpy(pdata + i*m_img_show.GetPitch(), (char*)m_proc_result_buf.image.data+i*STE_IMAGE_WIDTH*4, STE_IMAGE_WIDTH*3);

				blend_row_Y32((unsigned int*)(pdata + i*m_img_show.GetPitch()),(unsigned int*)(m_proc_result_buf.image.data+i*STE_IMAGE_WIDTH*4),STE_IMAGE_WIDTH) ;
			}

			//**********copy mid image**************************
			if (!m_img1.IsNull())
			{
				m_img1.Destroy();
			}
			m_img1.Create(STE_IMAGE_WIDTH, -STE_IMAGE_HEIGH, 24);

			pdata=(char*)m_img1.GetBits(); 
			for (i=0;i<STE_IMAGE_HEIGH;i++)
			{
				for (j=0; j<STE_IMAGE_WIDTH; j++)
				{
					pdata[i*3*STE_IMAGE_WIDTH +3*j] = m_img_mid1.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+1] = m_img_mid1.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+2] = m_img_mid1.data[i*STE_IMAGE_WIDTH+j];
				}
			}

			if (!m_img2.IsNull())
			{
				m_img2.Destroy();
			}
			m_img2.Create(STE_IMAGE_WIDTH, -STE_IMAGE_HEIGH, 24);

			pdata=(char*)m_img2.GetBits(); 
			for (i=0;i<STE_IMAGE_HEIGH;i++)
			{
				for (j=0; j<STE_IMAGE_WIDTH; j++)
				{
					pdata[i*3*STE_IMAGE_WIDTH +3*j] = m_img_mid2.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+1] = m_img_mid2.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+2] = m_img_mid2.data[i*STE_IMAGE_WIDTH+j];
				}
			}

			if (!m_img3.IsNull())
			{
				m_img3.Destroy();
			}
			m_img3.Create(STE_IMAGE_WIDTH, -STE_IMAGE_HEIGH, 24);

			pdata=(char*)m_img3.GetBits(); 
			for (i=0;i<STE_IMAGE_HEIGH;i++)
			{
				for (j=0; j<STE_IMAGE_WIDTH; j++)
				{
					pdata[i*3*STE_IMAGE_WIDTH +3*j] = m_img_mid3.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+1] = m_img_mid3.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+2] = m_img_mid3.data[i*STE_IMAGE_WIDTH+j];
				}
			}

			if (!m_img4.IsNull())
			{
				m_img4.Destroy();
			}
			m_img4.Create(STE_IMAGE_WIDTH, -STE_IMAGE_HEIGH, 24);

			pdata=(char*)m_img4.GetBits(); 
			for (i=0;i<STE_IMAGE_HEIGH;i++)
			{
				for (j=0; j<STE_IMAGE_WIDTH; j++)
				{
					pdata[i*3*STE_IMAGE_WIDTH +3*j] = m_img_mid4.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+1] = m_img_mid4.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+2] = m_img_mid4.data[i*STE_IMAGE_WIDTH+j];
				}
			}

			if (!m_img5.IsNull())
			{
				m_img5.Destroy();
			}
			m_img5.Create(STE_IMAGE_WIDTH, -STE_IMAGE_HEIGH, 24);

			pdata=(char*)m_img5.GetBits(); 
			for (i=0;i<STE_IMAGE_HEIGH;i++)
			{
				for (j=0; j<STE_IMAGE_WIDTH; j++)
				{
					pdata[i*3*STE_IMAGE_WIDTH +3*j] = m_img_mid5.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+1] = m_img_mid5.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+2] = m_img_mid5.data[i*STE_IMAGE_WIDTH+j];
				}
			}

			if (!m_img6.IsNull())
			{
				m_img6.Destroy();
			}
			m_img6.Create(STE_IMAGE_WIDTH, -STE_IMAGE_HEIGH, 24);

			pdata=(char*)m_img6.GetBits(); 
			for (i=0;i<STE_IMAGE_HEIGH;i++)
			{
				for (j=0; j<STE_IMAGE_WIDTH; j++)
				{
					pdata[i*3*STE_IMAGE_WIDTH +3*j] = m_img_mid6.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+1] = m_img_mid6.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+2] = m_img_mid6.data[i*STE_IMAGE_WIDTH+j];
				}
			}

			if (!m_img7.IsNull())
			{
				m_img7.Destroy();
			}
			m_img7.Create(STE_IMAGE_WIDTH, -STE_IMAGE_HEIGH, 24);

			pdata=(char*)m_img7.GetBits(); 
			for (i=0;i<STE_IMAGE_HEIGH;i++)
			{
				for (j=0; j<STE_IMAGE_WIDTH; j++)
				{
					pdata[i*3*STE_IMAGE_WIDTH +3*j] = m_img_mid7.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+1] = m_img_mid7.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+2] = m_img_mid7.data[i*STE_IMAGE_WIDTH+j];
				}
			}

			if (!m_img8.IsNull())
			{
				m_img8.Destroy();
			}
			m_img8.Create(STE_IMAGE_WIDTH, -STE_IMAGE_HEIGH, 24);

			pdata=(char*)m_img8.GetBits(); 
			for (i=0;i<STE_IMAGE_HEIGH;i++)
			{
				for (j=0; j<STE_IMAGE_WIDTH; j++)
				{
					pdata[i*3*STE_IMAGE_WIDTH +3*j] = m_img_mid8.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+1] = m_img_mid8.data[i*STE_IMAGE_WIDTH+j];
					pdata[i*3*STE_IMAGE_WIDTH +3*j+2] = m_img_mid8.data[i*STE_IMAGE_WIDTH+j];
				}
			}
			ReleaseMutex(m_proc_lock);

			UpdateImage();
		}


		break;
	default:
		break;
	}

	return 0;
}

void CDlgCapFile::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	((CSTEvaluationDlg*)pWndParent)->AddEvent(1,1,STE_SYSEVENT_FIRE_S);
	CDialogEx::OnOK();
}


void CDlgCapFile::Stop(void)
{
	printf("capfile stop\r\n");
	if (m_flg_process)
	{
		if (m_proc_mode_step)
		{
			m_proc_mode_step = FALSE;
			Sleep(500);
			SetEvent(m_proc_flgstep);
		}
		SetEvent(m_proc_flgexit);
		
		WaitForSingleObject(m_proc_handle, INFINITE);
		CloseHandle(m_proc_handle);

		m_img_show.Destroy();
		Sleep(200);
		//结束父窗口的记录文件
		((CSTEvaluationDlg*)pWndParent)->StopAProc();
		m_flg_process = FALSE;

		//清空交换内存
		m_proc_result_buf.target_set.num = 0;
		m_proc_result_buf.event_set.num = 0;
		m_proc_result_buf.frame_index = 0;
		Invalidate();
	}
}


void CDlgCapFile::Start(void)
{
	printf("capfile start\r\n");
	UpdateData();
	
	m_trigger_snatch_time = 0; 
    m_trigger_index = 0;
	m_firstalarm = 0;
	if (!m_flg_process)
	{
		ResetEvent(m_proc_flgexit);
		ResetEvent(m_proc_flgstep);
		m_proc_mode_step = 0;
		m_proc_handle = CreateThread( 
			NULL,              // default security attributes
			0,                 // use default stack size  
			thread_proc,          // thread function 
			this,             // argument to thread function 
			0,                 // use default creation flags 
			NULL);   // returns the thread identifier 
		if (m_proc_handle)
		{
			m_flg_process = TRUE;
		}
		else
		{
			printf("create proc thread failed!\r\n");
		}

		Invalidate();
	}
	else
	{
		if (m_proc_mode_step)
		{
			m_proc_mode_step = FALSE;
			SetEvent(m_proc_flgstep);
		}
	}
}

//线程处理函数
static DWORD WINAPI thread_proc(LPVOID lpParam)
{
	int i, j, res;
	char *pdata;
	CDlgCapFile * p_cap_file;
	IplImage * image;// = cvLoadImage(path_image1,1);
	IplImage * image_cvt_rgb;
	IplImage * image_cvt_gray;
	IplImage * image_optlevel;
	IplImage * image_finallevel;
	IplImage * image_initreg;
	IplImage * image_finalreg;

	CvCapture * cap; 
	VSV_Handle algo_handle = NULL;
	IVFD_YuvImage img_src;
	VARESULT *va_result;
	int video_fps;
	int frame_num;
	int frame_index;

	CvSize sz;

	p_cap_file = (CDlgCapFile *)lpParam;

	sz.width= STE_IMAGE_WIDTH;
	sz.height = STE_IMAGE_HEIGH;
	image_optlevel = cvCreateImageHeader( sz, 8, 1);
	image_finallevel = cvCreateImageHeader( sz, 8, 1);
	image_initreg = cvCreateImageHeader( sz, 8, 1);
	image_finalreg = cvCreateImageHeader( sz, 8, 1);

	cap = cvCreateFileCapture(p_cap_file->video_file_path.GetBuffer(0));

	if (cap)
	{	

		//create algo
		algo_handle = ALGO_VSD_create(STE_IMAGE_WIDTH, STE_IMAGE_HEIGH, &p_cap_file->m_algo_cfg);
		assert(algo_handle);
		va_result = (VARESULT*)malloc(sizeof(VARESULT));
		assert(va_result);
		memset(va_result, 0, sizeof(VARESULT));

		//set algo
		ALGO_VSD_setConfig(algo_handle, &p_cap_file->m_algo_cfg);
		VSD_Start(algo_handle);
		img_src.width = STE_IMAGE_WIDTH;
		img_src.height = STE_IMAGE_HEIGH;

		frame_num = cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_COUNT);
		video_fps = cvGetCaptureProperty(cap, CV_CAP_PROP_FPS);
		p_cap_file->m_proc_result_buf.fps = video_fps;
		//是否是片段分析
		if (p_cap_file->m_video_clip_enable)
		{
			cvSetCaptureProperty(cap, CV_CAP_PROP_POS_FRAMES, (p_cap_file->m_video_clip_start)*p_cap_file->video_file_info_fps*60);
		}
		printf("begin video process!\r\n");
#ifdef DEBUG
		while (WaitForSingleObject(p_cap_file->m_proc_flgexit, 10) != WAIT_OBJECT_0 )
#else
		while (WaitForSingleObject(p_cap_file->m_proc_flgexit, 1000/video_fps) != WAIT_OBJECT_0 )
#endif
		
		{
			if (p_cap_file->m_proc_mode_step)
			{
				WaitForSingleObject(p_cap_file->m_proc_flgstep, INFINITE);
			}
			//get frame
			frame_index = cvGetCaptureProperty(cap, CV_CAP_PROP_POS_FRAMES);
			image = cvQueryFrame(cap);
			if	(image &&(!p_cap_file->m_video_clip_enable || frame_index <=p_cap_file->video_file_info_fps*(p_cap_file->m_video_clip_end)*60))
			{
				//将图像的分辨率归一化到cif
				image_cvt_rgb = cvCreateImage(sz, image->depth, image->nChannels);
				image_cvt_gray = cvCreateImage(sz, image->depth, 1);

				
				cvResize(image, image_cvt_rgb, CV_INTER_LINEAR );

				if (image_cvt_rgb->nChannels ==1)
				{
					cvCopy(image_cvt_rgb, image_cvt_gray, NULL);
				}
				else
				{
					cvCvtColor(image_cvt_rgb, image_cvt_gray, CV_RGB2GRAY);
				}
		
//*************process image****************************************************************
				img_src.time = frame_index*25/video_fps;
				img_src.data_u = NULL;
				img_src.data_v = NULL;
				img_src.data_y = (unsigned char*)image_cvt_gray->imageData;
				img_src.width = STE_IMAGE_WIDTH;
				img_src.height = STE_IMAGE_HEIGH;
				//img_src.flag = 0;
#ifdef ALGO_HALFCIF
				img_src.height = img_src.height/2;
				//img_src.width = img_src.width/2;

				img_src.data_y = (uint8_t*)malloc(img_src.width*img_src.height);
				assert(img_src.data_y);
				if (img_src.data_y)
				{
					for (i=0; i<img_src.height; i++)
					{
						//memcpy(img_src.dataY+i*img_src.width, pdate+i*img_src.width*2, img_src.width);
						for (j=0; j<img_src.width; j++)
						{
							//img_src.dataY[i*img_src.width+j] = (pdate[(i*img_src.width+j)*2]+pdate[(i*img_src.width+j)*2+1])/2;

							img_src.data_y[i*img_src.width+j] = (((unsigned char*)image_cvt_gray->imageData)[i*img_src.width*2+j]+((unsigned char*)image_cvt_gray->imageData)[(i+1)*img_src.width*2+j])/2;
						}

					}
				}

#endif
#ifdef ALGO_HALFCIF176288
				//img_src.height = img_src.height/2;
				img_src.width = img_src.width/2;

				img_src.data_y = (uint8_t*)malloc(img_src.width*img_src.height);
				assert(img_src.data_y);
				if (img_src.data_y)
				{
					for (i=0; i<img_src.height; i++)
					{
						//memcpy(img_src.dataY+i*img_src.width, pdate+i*img_src.width*2, img_src.width);
						for (j=0; j<img_src.width; j++)
						{
							img_src.data_y[i*img_src.width+j] = (((unsigned char*)image_cvt_gray->imageData)[(i*img_src.width+j)*2]+((unsigned char*)image_cvt_gray->imageData)[(i*img_src.width+j)*2])/2;
						}

					}
				}

#endif
				res = ALGO_VSD_Process( algo_handle, &img_src );

				//get results

				if (res == VASTATUS_OK)
				{
					memset(va_result, 0, sizeof(VARESULT));
					//5 get result from algo
					ALGO_VSD_GetResults( algo_handle, va_result );
					//只有当处理过图像时，才说明result有更新
					p_cap_file->m_proc_result_buf.flg_used = FALSE;
				}

				//post result
				WaitForSingleObject(p_cap_file->m_proc_lock, INFINITE);
				// save result 
				p_cap_file->m_proc_result_buf.image.width = STE_IMAGE_WIDTH;
				p_cap_file->m_proc_result_buf.image.height = STE_IMAGE_HEIGH;
				p_cap_file->m_proc_result_buf.frame_num = frame_num;
				p_cap_file->m_proc_result_buf.frame_index = frame_index;
				
				//save target
				if (va_result->target_set.target_num > STE_TARGET_MAX_NUM)
				{
					va_result->target_set.target_num = STE_TARGET_MAX_NUM;
				}
				p_cap_file->m_proc_result_buf.target_set.num = va_result->target_set.target_num;
				p_cap_file->m_proc_result_buf.target_set.frame = frame_index;
				
				for (i=0; i<va_result->target_set.target_num; i++)
				{
					p_cap_file->m_proc_result_buf.target_set.targets[i].type = STE_SYSEVENT_SMOKE_S;	
					p_cap_file->m_proc_result_buf.target_set.targets[i].rect.left = va_result->target_set.targets[i].rect.lb_x;
					p_cap_file->m_proc_result_buf.target_set.targets[i].rect.bottom = va_result->target_set.targets[i].rect.lb_y;
					p_cap_file->m_proc_result_buf.target_set.targets[i].rect.right = va_result->target_set.targets[i].rect.ru_x;
					p_cap_file->m_proc_result_buf.target_set.targets[i].rect.top = va_result->target_set.targets[i].rect.ru_y;
#ifdef ALGO_HALFCIF
					p_cap_file->m_proc_result_buf.target_set.targets[i].rect.bottom *=2;
					p_cap_file->m_proc_result_buf.target_set.targets[i].rect.top *=2;
#endif

#ifdef ALGO_HALFCIF176288
					p_cap_file->m_proc_result_buf.target_set.targets[i].rect.left *=2;
					p_cap_file->m_proc_result_buf.target_set.targets[i].rect.right *=2;
#endif
				}
				//save event
				if (va_result->event_set.event_num > STE_EVENT_MAX_NUM)
				{
					va_result->event_set.event_num = STE_EVENT_MAX_NUM;
				}
				p_cap_file->m_proc_result_buf.event_set.num = va_result->event_set.event_num;
				for (i=0; i<va_result->event_set.event_num; i++)
				{
					if (va_result->event_set.events[i].type == VAEVT_TYPE_AlarmSmoke)
					{
						p_cap_file->m_proc_result_buf.event_set.events[i].type = STE_SYSEVENT_SMOKE_S;	
					}
					if (va_result->event_set.events[i].status == 2)
					{
						p_cap_file->m_proc_result_buf.event_set.events[i].type += 30;
					}
					p_cap_file->m_proc_result_buf.event_set.events[i].frame = frame_index;
					
				}
				//save image;
				for (i=0; i<image_cvt_rgb->height; i++)
				{
					memcpy(p_cap_file->m_proc_result_buf.image.data+i*STE_IMAGE_WIDTH*4, 
						image_cvt_rgb->imageData+i*image_cvt_rgb->widthStep, STE_IMAGE_WIDTH*image_cvt_rgb->nChannels);
				}			
				//-----------------------------copy middle image------------------------------------
				pdata = (char*)((MODULE_VSD*)algo_handle)->vsdet_buffer_var->ind_optlevel;
				//pdata = (char*)img_src.dataY;
				for (i=0; i<img_src.height; i++)
				{
					memcpy(p_cap_file->m_img_mid1.data+i*STE_IMAGE_WIDTH, 
						pdata+i*STE_IMAGE_WIDTH, STE_IMAGE_WIDTH);
				}
				pdata = (char*)((MODULE_VSD*)algo_handle)->vsdet_buffer_var->ind_initreg;
				for (i=0; i<img_src.height; i++)
				{
					memcpy(p_cap_file->m_img_mid2.data+i*STE_IMAGE_WIDTH, 
						pdata+i*STE_IMAGE_WIDTH, STE_IMAGE_WIDTH);
				}	
				pdata = (char*)((MODULE_VSD*)algo_handle)->vsdet_buffer_var->ind_finlevel;
				//pdata = (char*)image_cvt_gray->imageData;
				for (i=0; i<img_src.height; i++)
				{
					memcpy(p_cap_file->m_img_mid3.data+i*STE_IMAGE_WIDTH, 
						pdata+i*STE_IMAGE_WIDTH, STE_IMAGE_WIDTH);
				}	
				pdata = (char*)((MODULE_VSD*)algo_handle)->vsdet_buffer_var->ind_finreg;
				for (i=0; i<img_src.height; i++)
				{
					memcpy(p_cap_file->m_img_mid4.data+i*STE_IMAGE_WIDTH, 
						pdata+i*STE_IMAGE_WIDTH, STE_IMAGE_WIDTH);
				}	

				pdata = (char*)((MODULE_VSD*)algo_handle)->vsdet_buffer_var->ind_optlevel_sub;
				for (i=0; i<img_src.height; i++)
				{
					memcpy(p_cap_file->m_img_mid5.data+i*STE_IMAGE_WIDTH, 
						pdata+i*STE_IMAGE_WIDTH, STE_IMAGE_WIDTH);
				}
				pdata = (char*)((MODULE_VSD*)algo_handle)->vsdet_buffer_var->ind_initreg_sub;
				//pdata = (char*)img_src.dataY;
				for (i=0; i<img_src.height; i++)
				{
					memcpy(p_cap_file->m_img_mid6.data+i*STE_IMAGE_WIDTH, 
						pdata+i*STE_IMAGE_WIDTH, STE_IMAGE_WIDTH);
				}	
				pdata = (char*)((MODULE_VSD*)algo_handle)->vsdet_buffer_var->ind_finlevel_sub;
				//pdata = (char*)image_cvt_gray->imageData;
				for (i=0; i<img_src.height; i++)
				{
					memcpy(p_cap_file->m_img_mid7.data+i*STE_IMAGE_WIDTH, 
						pdata+i*STE_IMAGE_WIDTH, STE_IMAGE_WIDTH);
				}	
				pdata = (char*)((MODULE_VSD*)algo_handle)->vsdet_buffer_var->ind_blur_trend;
				for (i=0; i<img_src.height; i++)
				{
					memcpy(p_cap_file->m_img_mid8.data+i*STE_IMAGE_WIDTH, 
						pdata+i*STE_IMAGE_WIDTH, STE_IMAGE_WIDTH);
				}

#ifdef ALGO_HALFCIF
				if (img_src.data_y)
				{
					free(img_src.data_y);
				}
#endif

#ifdef ALGO_HALFCIF176288
				if (img_src.data_y)
				{
					free(img_src.data_y);
				}
#endif

				ReleaseMutex(p_cap_file->m_proc_lock);
				
				PostMessage(p_cap_file->GetSafeHwnd(), WM_MY_MESSAGE_CAP_FILE, CAP_FILE_TYPE_UPDATEIMAGE, 0);
			
				cvReleaseImage(&image_cvt_rgb);
				cvReleaseImage(&image_cvt_gray);
			
			}
			else
			{
				break;
			}
		}
		printf("destroy algo\r\n");
		ALGO_VSD_destroy(algo_handle,STE_IMAGE_WIDTH, STE_IMAGE_HEIGH);
		cvReleaseCapture(&cap);
	}
	else
	{
		AfxMessageBox(_T("Video file format is not supported!"));
		printf("open video file failed!\r\n");
	}


	printf("thread proc exit!\r\n");

	PostMessage(p_cap_file->GetSafeHwnd(), WM_MY_MESSAGE_CAP_FILE, CAP_FILE_TYPE_QUIT, 0);

	return 0;
}


void CDlgCapFile::OnBnClickedButtonBrowse()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CString file_path, source_path;
	CString szFilters;
	szFilters = "video Files (*.avi)|*.avi||";
	CFileDialog fileDlg (TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if(fileDlg.DoModal() == IDOK)
	{
		m_file_video = fileDlg.GetPathName();
		video_filename = fileDlg.GetFileTitle();
			video_file_path = m_file_video;
		//设置相关的其他文件路径
		event_file_path = video_file_path;
		i = event_file_path.ReverseFind(_T('.'));
		file_path = event_file_path.Left(i);
		event_file_path = file_path + _T(".csv");
		target_file_path = file_path + _T(".dat");
		((CSTEvaluationDlg*)pWndParent)->video_file_path = video_file_path;
		((CSTEvaluationDlg*)pWndParent)->event_file_path = event_file_path;
		((CSTEvaluationDlg*)pWndParent)->target_file_path = target_file_path;

		//尝试打开此文件并获取相关信息
		CvCapture * cap; 
		cap = cvCreateFileCapture(m_file_video.GetBuffer(0));
		if (cap)
		{
			video_file_info_frame = cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_COUNT);
			video_file_info_fps = cvGetCaptureProperty(cap, CV_CAP_PROP_FPS);
			video_file_info_fourcc = cvGetCaptureProperty(cap, CV_CAP_PROP_FOURCC);
			video_file_info_width = cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_WIDTH);
			video_file_info_height = cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_HEIGHT);

			cvReleaseCapture(&cap);
		}
		else
		{
			video_file_info_frame = 0;
			video_file_info_fps = 25;
			video_file_info_fourcc = 0;
			video_file_info_width = 0;
			video_file_info_height = 0;
			AfxMessageBox(_T("Open video file failed!"));
		}
	}
	else
	{
		m_file_video= _T("");
	}
	video_file_path = m_file_video;
	//设置相关的其他文件路径
	m_video_clip_start = 0;
	m_video_clip_end = (video_file_info_frame/video_file_info_fps +59)/60;
	UpdateData(FALSE);

	Invalidate();
}


void CDlgCapFile::OnBnClickedButtonPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	Start();
}


void CDlgCapFile::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	Stop();
}


void CDlgCapFile::Active(void)
{
	printf("capfile active\r\n");
	CString str;
	m_flg_process = 0;
	m_file_video = _T("");
	//init cfg para
	algo_cfg_path = config_path + _T("\\advanced_parameters_default.ini");
	strncpy_s(_vsv_dll_path, config_path.GetBuffer(), 256);

	memset(&m_algo_cfg, 0, sizeof(m_algo_cfg));
	memset(m_algo_cfg.scene, 0xFF, STE_IMAGE_HEIGH*STE_IMAGE_WIDTH);
	m_algo_cfg.val_sense = GetPrivateProfileInt(_T("SMOKETRACE"), _T("sensitivity"), 2, algo_cfg_path);
	m_algo_cfg.val_delay = GetPrivateProfileInt(_T("SMOKETRACE"), _T("delay"), 2, algo_cfg_path);
	m_algo_cfg.val_fov = GetPrivateProfileInt(_T("SMOKETRACE"), _T("fov"), 1, algo_cfg_path);
	m_algo_cfg.val_static_det = GetPrivateProfileInt(_T("SMOKETRACE"), _T("sdet"), 1, algo_cfg_path);
	m_algo_cfg.alarm_delay = GetPrivateProfileInt(_T("SMOKETRACE"), _T("alarmdelay"), 1, algo_cfg_path);

	video_file_info_frame = 0;
	video_file_info_fps = 25;
	video_file_info_fourcc = 0;
	video_file_info_width = 0;
	video_file_info_height = 0;


	//清空交换内存
	m_proc_result_buf.target_set.num = 0;
	m_proc_result_buf.event_set.num = 0;
	m_proc_result_buf.frame_index = 0;
	m_proc_result_buf.fps = 0;

	m_trigger_snatch_time = 0;
	m_trigger_index  = 0;
	m_video_clip_enable = TRUE;
	UpdateData(FALSE);
	Invalidate();
}


void CDlgCapFile::Deactive(void)
{
	printf("capfile deactive\r\n");
	
	Stop();

	video_file_path = _T("");
	event_file_path = _T("");
	target_file_path = _T("");
	((CSTEvaluationDlg*)pWndParent)->video_file_path = video_file_path;
	((CSTEvaluationDlg*)pWndParent)->event_file_path = event_file_path;
	((CSTEvaluationDlg*)pWndParent)->target_file_path = target_file_path;
	UpdateData(FALSE);
}


BOOL CDlgCapFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_flg_process = 0;
	m_img_def.LoadFromResource(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_DEF));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgCapFile::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	if (m_flg_process)
	{
		GetDlgItem(IDC_CHECK_CLIP_ENABLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CFG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SCREENSHOT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STEP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_CFG)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_CLIP_ENABLE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STEP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SCREENSHOT)->EnableWindow(FALSE);
	}

	UpdateImage();
}


void CDlgCapFile::UpdateImage(void)
{
	int i;
	CPen cur_pen, *old_pen=NULL;
	CBrush cur_brush,*old_brush = NULL;
	CPoint point;
	CSize size;
	CRect rect_image;
	CImage * pimage;
	CString str_dis;
	CRect client_rect1;
	CSize paint_size1;

	if (!m_img_show.IsNull())
	{
		pimage = &m_img_show;

		CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = pDis1->GetDC();
		CDC MemDC1;
		CBitmap MemBitmap1;
		CPen pen_target;
		
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
		pDis1->GetClientRect(&client_rect1);
		MemDC1.CreateCompatibleDC(pDC1);
		MemBitmap1.CreateCompatibleBitmap(pDC1,rect_image.Width(),rect_image.Height());
		MemDC1.SelectObject(&MemBitmap1);

		MemDC1.SetStretchBltMode(COLORONCOLOR);
		pDC1->SetStretchBltMode(COLORONCOLOR);

		pimage->BitBlt(MemDC1.GetSafeHdc(),rect_image, CPoint(0,0),SRCCOPY);

		//draw other osd targets
		pen_target.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		MemDC1.SelectStockObject(NULL_BRUSH);
		MemDC1.SelectObject(&pen_target);
		for (i=0; i<m_proc_result_buf.target_set.num; i++)
		{

			MemDC1.Rectangle(m_proc_result_buf.target_set.targets[i].rect.left,
				m_proc_result_buf.target_set.targets[i].rect.bottom,
				m_proc_result_buf.target_set.targets[i].rect.right,
				m_proc_result_buf.target_set.targets[i].rect.top);

		}
		//修改事件抓拍为每10秒钟1次
#define SNATCH_TIME_INTER 10
#define SNATCH_TIME_LATE	120
		if (m_proc_result_buf.target_set.num > 0)
		{
			CImage img;
			CString str_name;
			time_t cur_time;
			struct tm * now_time;
			int i;

			time(&cur_time);
			now_time = localtime(&cur_time);

			if (m_firstalarm == 0)				
			{
				//first snatch
				str_name = ((CSTEvaluationDlg*)pWndParent)->video_file_path;
				str_name = str_name.Left(str_name.ReverseFind(_T('\\')));
				str_name += +_T("\\ScreenShot\\");

				if (CreateDirectory(str_name, NULL) == ERROR_PATH_NOT_FOUND) 
				{ 
					AfxMessageBox("Create Screenshot Path Error!");
				} 
				else
				{
					str_name += video_filename;
					str_name.AppendFormat(_T("_%012d_alarm.jpg"), m_proc_result_buf.frame_index/m_proc_result_buf.fps);
					img.Attach(MemBitmap1);
					img.Save(str_name);
					img.Detach();
				}
				
				m_trigger_index = m_proc_result_buf.frame_index;
				m_firstalarm = 1;
			}
			else if (m_proc_result_buf.frame_index - m_trigger_index >= SNATCH_TIME_INTER*m_proc_result_buf.fps)				
			{
				//超过10s间隔
				str_name = ((CSTEvaluationDlg*)pWndParent)->video_file_path;
				str_name = str_name.Left(str_name.ReverseFind(_T('\\')));
				str_name += +_T("\\ScreenShot\\");

				if (CreateDirectory(str_name, NULL) == ERROR_PATH_NOT_FOUND) 
				{ 
					AfxMessageBox("Create Screenshot Path Error!");
				} 
				else
				{
					str_name += video_filename;
					str_name.AppendFormat(_T("_%012d_alarm.jpg"), m_proc_result_buf.frame_index/m_proc_result_buf.fps);
					img.Attach(MemBitmap1);
					img.Save(str_name);
					img.Detach();
				}

				m_trigger_index = m_proc_result_buf.frame_index;
			}
		}

		//延续120秒
		else if(m_trigger_index > 0 && m_proc_result_buf.frame_index - m_trigger_index <=SNATCH_TIME_LATE*m_proc_result_buf.fps )
		{
			CImage img;
			CString str_name;
			time_t cur_time;
			struct tm * now_time;
			int i;

			time(&cur_time);
			now_time = localtime(&cur_time);

			m_firstalarm = 0;
			if ((m_proc_result_buf.frame_index - m_trigger_index) % (SNATCH_TIME_INTER*m_proc_result_buf.fps) == 0)			
			{
				//超过10s间隔
				str_name = ((CSTEvaluationDlg*)pWndParent)->video_file_path;
				str_name = str_name.Left(str_name.ReverseFind(_T('\\')));
				str_name += +_T("\\ScreenShot\\");

				if (CreateDirectory(str_name, NULL) == ERROR_PATH_NOT_FOUND) 
				{ 
					AfxMessageBox("Create Screenshot Path Error!");
				} 
				else
				{
					str_name += video_filename;
					str_name.AppendFormat(_T("_%012d_alarm.jpg"), m_proc_result_buf.frame_index/m_proc_result_buf.fps);
					img.Attach(MemBitmap1);
					img.Save(str_name);
					img.Detach();
				}

			}
		}

		if (!m_proc_result_buf.flg_used)
		{
			if (m_proc_result_buf.target_set.num)
			{
				((CSTEvaluationDlg*)pWndParent)->AddTarget(&m_proc_result_buf.target_set);
			}
			//do event
			for (i=0; i<m_proc_result_buf.event_set.num; i++)
			{
				((CSTEvaluationDlg*)pWndParent)->AddEvent(m_proc_result_buf.event_set.events[i].frame,m_proc_result_buf.event_set.events[i].frame/video_file_info_fps,m_proc_result_buf.event_set.events[i].type);
			}

			//防止由于刷新，事件被触发两次
			m_proc_result_buf.flg_used = TRUE;
		}
			
	

		//---------------------抓拍的操作-------------------
		if (WaitForSingleObject(m_proc_flgscreenshot, 0) == WAIT_OBJECT_0)
		{
			CImage img;
			CString str_name;
			time_t cur_time;
			struct tm * now_time;

			str_name = ((CSTEvaluationDlg*)pWndParent)->video_file_path;
			str_name = str_name.Left(str_name.ReverseFind(_T('\\')));
			str_name += +_T("\\ScreenShot\\");

			if (CreateDirectory(str_name, NULL) == ERROR_PATH_NOT_FOUND) 
			{ 
				AfxMessageBox("Create Screenshot Path Error!");
			} 
			else
			{

				time(&cur_time);
				now_time = localtime(&cur_time);
				str_name += video_filename;
				str_name.AppendFormat(_T("_%012d_manual.jpg"), m_proc_result_buf.frame_index/m_proc_result_buf.fps);
				//str_name.AppendFormat(_T("_%04d%02d%02d-%02d%02d%02d_manual.jpg"), now_time->tm_year+1900, now_time->tm_mon+1, now_time->tm_mday, now_time->tm_hour, now_time->tm_min, now_time->tm_sec);
				img.Attach(MemBitmap1);
				img.Save(str_name);
				img.Detach();
			}
		}
		int dis_w, dis_h;
#ifdef DEBUG
		dis_w = STE_IMAGE_WIDTH;
		dis_h = STE_IMAGE_HEIGH;
#else
		dis_w = STE_IMAGE_WIDTH*2;
		dis_h = STE_IMAGE_HEIGH*2;
#endif
		pDC1->StretchBlt(0,0,dis_w-1,dis_h-1,&MemDC1,0,0,rect_image.Width()-1, rect_image.Height()-1, SRCCOPY);

		pDis1->ReleaseDC(pDC1);

	}
	else
	{
		pimage = &m_img_def;
		
		CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = pDis1->GetDC();
		pDis1->GetClientRect(&client_rect1);
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
#ifdef DEBUG
		client_rect1.right = client_rect1.left+(client_rect1.right-client_rect1.left)/2;
		client_rect1.bottom = client_rect1.top-(client_rect1.top-client_rect1.bottom)/2;
#endif
		pimage->StretchBlt(pDC1->GetSafeHdc(),client_rect1, rect_image, SRCCOPY);

		pDis1->ReleaseDC(pDC1);
	}

#ifdef _DEBUG
#define midimg_w 175
#define midimg_h 143

	if (!m_img1.IsNull())
	{
		pimage = &m_img1;

		//CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = GetDC();
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
		GetClientRect(&client_rect1);
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(355,30, 355+midimg_w, 30+midimg_h), rect_image);
		ReleaseDC(pDC1);
	}
	if (!m_img2.IsNull())
	{
		pimage = &m_img2;

		//CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = GetDC();
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
		GetClientRect(&client_rect1);
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(355,174, 355+midimg_w, 174+midimg_h), rect_image);
		//pimage->BitBlt(pDC1->GetSafeHdc(), 500,0,352,288, 0,0,SRCCOPY);
		ReleaseDC(pDC1);
	}
	if (!m_img3.IsNull())
	{
		pimage = &m_img3;

		//CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = GetDC();
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
		GetClientRect(&client_rect1);
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(355,318, 355+midimg_w, 318+midimg_h), rect_image);
		//pimage->BitBlt(pDC1->GetSafeHdc(), 500,0,352,288, 0,0,SRCCOPY);
		ReleaseDC(pDC1);
	}
	if (!m_img4.IsNull())
	{
		pimage = &m_img4;

		//CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = GetDC();
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
		GetClientRect(&client_rect1);
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(355,462, 355+midimg_w, 462+midimg_h), rect_image);
		//pimage->BitBlt(pDC1->GetSafeHdc(), 500,0,352,288, 0,0,SRCCOPY);
		ReleaseDC(pDC1);
	}


	if (!m_img5.IsNull())
	{
		pimage = &m_img5;

		//CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = GetDC();
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
		GetClientRect(&client_rect1);
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(532,30, 532+midimg_w, 30+midimg_h), rect_image);
		ReleaseDC(pDC1);
	}
	if (!m_img6.IsNull())
	{
		pimage = &m_img6;

		//CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = GetDC();
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
		GetClientRect(&client_rect1);
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(532,174, 532+midimg_w, 174+midimg_h), rect_image);
		//pimage->BitBlt(pDC1->GetSafeHdc(), 500,0,352,288, 0,0,SRCCOPY);
		ReleaseDC(pDC1);
	}
	if (!m_img7.IsNull())
	{
		pimage = &m_img7;

		//CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = GetDC();
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
		GetClientRect(&client_rect1);
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(532,318, 532+midimg_w, 318+midimg_h), rect_image);
		//pimage->BitBlt(pDC1->GetSafeHdc(), 500,0,352,288, 0,0,SRCCOPY);
		ReleaseDC(pDC1);
	}
	if (!m_img8.IsNull())
	{
		pimage = &m_img8;

		//CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = GetDC();
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
		GetClientRect(&client_rect1);
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(532,462, 532+midimg_w, 462+midimg_h), rect_image);
		//pimage->BitBlt(pDC1->GetSafeHdc(), 500,0,352,288, 0,0,SRCCOPY);
		ReleaseDC(pDC1);
	}

#endif


	//因为帧数等信息和图像相关，所以也放在此处更新
	if (video_file_info_fps == 0)
	{
		video_file_info_fps = 1;
	}
	str_dis.Format(_T("Frame:%06d/%06d;   Time: %02dm:%02ds / %02dm:%02ds"), m_proc_result_buf.frame_index, video_file_info_frame-1,
		m_proc_result_buf.frame_index/video_file_info_fps/60, 
		m_proc_result_buf.frame_index/video_file_info_fps%60,
		((video_file_info_frame)/video_file_info_fps)/60,
	((video_file_info_frame)/video_file_info_fps)%60);
	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(str_dis);
}


int CDlgCapFile::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_proc_flgexit =  CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(m_proc_flgexit);
	m_proc_flgstep =  CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(m_proc_flgstep);
	m_proc_flgscreenshot =  CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(m_proc_flgscreenshot);
	m_proc_lock = CreateMutex(NULL,0, NULL);
	assert(m_proc_lock);

	memset(&m_proc_result_buf, 0, sizeof(m_proc_result_buf));
	m_proc_result_buf.image.data = (unsigned char *)malloc(STE_IMAGE_HEIGH*STE_IMAGE_WIDTH*4);
	assert(m_proc_result_buf.image.data);

	m_img_mid1.data = (unsigned char*)malloc(STE_IMAGE_HEIGH*STE_IMAGE_WIDTH*4);
	m_img_mid2.data = (unsigned char*)malloc(STE_IMAGE_HEIGH*STE_IMAGE_WIDTH*4);
	m_img_mid3.data = (unsigned char*)malloc(STE_IMAGE_HEIGH*STE_IMAGE_WIDTH*4);
	m_img_mid4.data = (unsigned char*)malloc(STE_IMAGE_HEIGH*STE_IMAGE_WIDTH*4);
	m_img_mid5.data = (unsigned char*)malloc(STE_IMAGE_HEIGH*STE_IMAGE_WIDTH*4);
	m_img_mid6.data = (unsigned char*)malloc(STE_IMAGE_HEIGH*STE_IMAGE_WIDTH*4);
	m_img_mid7.data = (unsigned char*)malloc(STE_IMAGE_HEIGH*STE_IMAGE_WIDTH*4);
	m_img_mid8.data = (unsigned char*)malloc(STE_IMAGE_HEIGH*STE_IMAGE_WIDTH*4);

	return 0;
}


void CDlgCapFile::OnDestroy()
{
	CDialogEx::OnDestroy();
	Deactive();

	// TODO: 在此处添加消息处理程序代码
	CloseHandle(m_proc_flgexit);
	CloseHandle(m_proc_flgstep);
	CloseHandle(m_proc_flgscreenshot);
	CloseHandle(m_proc_lock);
	free(m_proc_result_buf.image.data);
	free(m_img_mid1.data);
	free(m_img_mid2.data);
	free(m_img_mid3.data);
	free(m_img_mid4.data);
	free(m_img_mid5.data);
	free(m_img_mid6.data);
	free(m_img_mid7.data);
	free(m_img_mid8.data);

}


void CDlgCapFile::OnBnClickedButtonStep()
{
	// TODO: 在此添加控件通知处理程序代码
	Step();
}


void CDlgCapFile::Step(void)
{
	if (!m_proc_mode_step)
	{
		m_proc_mode_step = TRUE;
	}
	else
	{
		SetEvent(m_proc_flgstep);
	}
}


void CDlgCapFile::OnBnClickedButtonCfg()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_dlg_cfg.m_cfg_para1 = m_algo_cfg.val_sense;
	m_dlg_cfg.m_cfg_para2 = m_algo_cfg.val_delay;
	m_dlg_cfg.m_cfg_para3 = m_algo_cfg.val_fov;
	m_dlg_cfg.m_cfg_para4 = m_algo_cfg.val_static_det;
	m_dlg_cfg.m_cfg_para5 = m_algo_cfg.alarm_delay;

	if (m_dlg_cfg.DoModal() == IDOK)
	{
		m_algo_cfg.val_sense = m_dlg_cfg.m_cfg_para1;
		m_algo_cfg.val_delay = m_dlg_cfg.m_cfg_para2;
		m_algo_cfg.val_fov = m_dlg_cfg.m_cfg_para3;
		m_algo_cfg.val_static_det = m_dlg_cfg.m_cfg_para4;
		m_algo_cfg.alarm_delay = m_dlg_cfg.m_cfg_para5;

		str.Format(_T("%d"), m_algo_cfg.val_sense);
		WritePrivateProfileString(_T("SMOKETRACE"), _T("sensitivity"), str, algo_cfg_path);
		str.Format(_T("%d"), m_algo_cfg.val_delay);
		WritePrivateProfileString(_T("SMOKETRACE"), _T("delay"), str, algo_cfg_path);
		str.Format(_T("%d"), m_algo_cfg.val_fov);
		WritePrivateProfileString(_T("SMOKETRACE"), _T("fov"), str, algo_cfg_path);
		str.Format(_T("%d"), m_algo_cfg.val_static_det);
		WritePrivateProfileString(_T("SMOKETRACE"), _T("sdet"), str, algo_cfg_path);
		str.Format(_T("%d"), m_algo_cfg.alarm_delay);
		WritePrivateProfileString(_T("SMOKETRACE"), _T("alarmdelay"), str, algo_cfg_path);
	}
}


void CDlgCapFile::OnBnClickedButtonScreenshot()
{
	// TODO: 在此添加控件通知处理程序代码
	ScreenShot(1,0);
}


void CDlgCapFile::ScreenShot(int count, int inter_time)
{
	SetEvent(m_proc_flgscreenshot);
}
