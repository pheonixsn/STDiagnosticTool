// DlgCapCam.cpp : 实现文件
//

#include "stdafx.h"
#include "STEvaluation.h"
#include "STEvaluationDlg.h"
#include "DlgCapCam.h"
#include "afxdialogex.h"
#include <vfw.h>

#include "AlgoApi.h"

//处理thread
//信令线程
static DWORD WINAPI thread_proc(LPVOID lpParam);


// CDlgCapCam 对话框
IMPLEMENT_DYNAMIC(CDlgCapCam, CDialogEx)

CDlgCapCam::CDlgCapCam(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCapCam::IDD, pParent)
{

}

CDlgCapCam::~CDlgCapCam()
{
}

void CDlgCapCam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo_list_device);
}


BEGIN_MESSAGE_MAP(CDlgCapCam, CDialogEx)
	ON_MESSAGE(WM_MY_MESSAGE_CAP_FILE, OnMyMsg) 
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CDlgCapCam::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDlgCapCam::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SCREENSHOT, &CDlgCapCam::OnBnClickedButtonScreenshot)
	ON_BN_CLICKED(IDC_BUTTON_CFG, &CDlgCapCam::OnBnClickedButtonCfg)
END_MESSAGE_MAP()


// CDlgCapCam 消息处理程序
LRESULT CDlgCapCam::OnMyMsg(WPARAM wParam, LPARAM lParam)
{
	UINT32 msg_type;
	int i, j;
	char * pdata;

	msg_type = (UINT32)wParam;

	switch(msg_type)
	{
	case CAP_CAM_TYPE_QUIT:
		Stop();
		break;
	case CAP_CAM_TYPE_UPDATEIMAGE:
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
			ReleaseMutex(m_proc_lock);

			UpdateImage();
		}


		break;
	default:
		break;
	}

	return 0;
}

void CDlgCapCam::Stop(void)
{
	printf("capcam stop\r\n");
	if (m_flg_process)
	{
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

void CDlgCapCam::Start(void)
{
	int i;
	printf("capcam start\r\n");	
	UpdateData();

	m_trigger_snatch_time = 0;
	m_trigger_index  = 0;

	//抓拍参数
	m_snatch_count =0 ;
	m_snatch_intertime = 0;
	m_snatch_pretime = 0;

	if (!m_flg_process)
	{
		//使用的设备序号
		m_index_device = m_combo_list_device.GetCurSel();
		//每次start，都生成一个新的事件记录文件
		//设置相关的其他文件路径
		__time32_t cur_time;
		struct tm * now_time;

		_time32(&cur_time);
		now_time = _localtime32(&cur_time);

		i=config_path.ReverseFind(_T('\\'));
		event_file_path = config_path.Left(i) + _T("\\event\\");
		event_file_path.AppendFormat(_T("_CAM%04d%02d%02d-%02d%02d%02d.csv"), now_time->tm_year+1900, now_time->tm_mon+1, now_time->tm_mday, now_time->tm_hour, now_time->tm_min, now_time->tm_sec);

		((CSTEvaluationDlg*)pWndParent)->event_file_path = event_file_path;
		//记录开始时间
		m_start_time = cur_time;
		//抓拍参数
		m_snatch_count =0 ;
		m_snatch_intertime = 0;
		m_snatch_pretime = 0;
		ResetEvent(m_proc_flgexit);
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
		;
	}

}


void CDlgCapCam::Active(void)
{
	printf("capcam active\r\n");
	CString str;
	m_flg_process = 0;

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

	//抓拍参数
	m_snatch_count =0 ;
	m_snatch_intertime = 0;
	m_snatch_pretime = 0;

	m_start_time = 0;

	//枚举所有有效地摄像机
	//m_combo_list_device.ResetContent();

	TCHAR szDeviceName[80];
	TCHAR szDeviceVersion[80];
	for (int wIndex = 0; wIndex < 10; wIndex++)
	{
		if (capGetDriverDescription (wIndex, szDeviceName,
			sizeof (szDeviceName), szDeviceVersion,
			sizeof (szDeviceVersion)))
		{
			m_combo_list_device.AddString(szDeviceName);
		}
	}
	if (m_combo_list_device.GetCount()>0)
	{
		m_combo_list_device.SetCurSel(0);
	}
	else
	{
		AfxMessageBox(_T("Error!You have no installed video capture device!"));
	}


	Invalidate();

}


void CDlgCapCam::Deactive(void)
{
	printf("capcam deactive\r\n");
	Stop();

	event_file_path = _T("");
	
	((CSTEvaluationDlg*)pWndParent)->event_file_path = event_file_path;
	
	UpdateData(FALSE);
}


void CDlgCapCam::ScreenShot(int count, int inter_time)
{
	m_snatch_count = count;
	m_snatch_intertime = inter_time;
	m_snatch_pretime = 0;
}


void CDlgCapCam::UpdateImage(void)
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
	__time32_t l_time;

	if (!m_img_show.IsNull())
	{
		pimage = &m_img_show;
		_time32(&l_time);

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

		time_t cur_time;
		struct tm * now_time;

		time(&cur_time);
		now_time = localtime(&cur_time);

		if (m_proc_result_buf.target_set.num > 0)
		{
			if (cur_time - m_trigger_snatch_time >= SNATCH_TIME_INTER)				
			{
				//超过10s间隔
				ScreenShot(1, SNATCH_TIME_INTER);

				m_trigger_snatch_time = cur_time;
			}
		}

		//延续120秒
		else if(m_trigger_snatch_time > 0 && cur_time - m_trigger_snatch_time <=SNATCH_TIME_LATE)
		{
			ScreenShot(SNATCH_TIME_LATE/SNATCH_TIME_INTER, SNATCH_TIME_INTER);
			m_trigger_snatch_time = 0;
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
				//摄像头采集的，帧数置零
				((CSTEvaluationDlg*)pWndParent)->AddEvent(0,l_time,m_proc_result_buf.event_set.events[i].type);
				//同时触发抓拍
				//ScreenShot(12, 10);
			}

			//防止由于刷新，事件被触发两次
			m_proc_result_buf.flg_used = TRUE;
		}



		//---------------------抓拍的操作-------------------
		//if (WaitForSingleObject(m_proc_flgscreenshot, 0) == WAIT_OBJECT_0)
		if (m_snatch_count>0 && l_time - m_snatch_pretime>=m_snatch_intertime)
		{
			CImage img;
			CString str_name;
			time_t cur_time;
			struct tm * now_time;
			str_name = ((CSTEvaluationDlg*)pWndParent)->file_path;
			str_name += +_T("\\screenshot\\");
			time(&cur_time);
			now_time = localtime(&cur_time);
			str_name.AppendFormat(_T("_%012d_alarm.jpg"), cur_time);
			img.Attach(MemBitmap1);
			img.Save(str_name);
			img.Detach();

			m_snatch_count--;
			m_snatch_pretime = l_time;
		}

		pDC1->StretchBlt(0,0,STE_IMAGE_WIDTH*2-1,STE_IMAGE_HEIGH*2-1,&MemDC1,0,0,rect_image.Width()-1, rect_image.Height()-1, SRCCOPY);

		pDis1->ReleaseDC(pDC1);

	}
	else
	{
		pimage = &m_img_def;

		CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = pDis1->GetDC();
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);	
		pDis1->GetClientRect(&client_rect1);
		pimage->StretchBlt(pDC1->GetSafeHdc(),client_rect1, rect_image, SRCCOPY);

		pDis1->ReleaseDC(pDC1);
	}

#ifdef _DEBUG
	if (!m_img1.IsNull())
	{
		pimage = &m_img1;

		//CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = GetDC();
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
		GetClientRect(&client_rect1);
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(380,20, 380+175, 20+143), rect_image);
		//pimage->BitBlt(pDC1->GetSafeHdc(), 500,0,352,288, 0,0,SRCCOPY);
		ReleaseDC(pDC1);
	}
	if (!m_img2.IsNull())
	{
		pimage = &m_img2;

		//CWnd * pDis1 = GetDlgItem(IDC_STATIC_IMGSHOW);
		CDC* pDC1 = GetDC();
		rect_image = CRect(0,0,pimage->GetWidth()-1, pimage->GetHeight()-1);
		GetClientRect(&client_rect1);
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(380,170, 380+175, 170+143), rect_image);
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
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(560,20, 560+175, 20+143), rect_image);
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
		pimage->StretchBlt(pDC1->GetSafeHdc(),CRect(560,170, 560+175, 170+143), rect_image);
		//pimage->BitBlt(pDC1->GetSafeHdc(), 500,0,352,288, 0,0,SRCCOPY);
		ReleaseDC(pDC1);
	}	

#endif
	

	//因为帧数等信息和图像相关，所以也放在此处更新
	__time32_t n_time = 0;
	if (m_flg_process)
	{
		_time32(&n_time);
	}


	//str_dis.Format(_T("Frame:%06d;   Time(s):%06d"), m_proc_result_buf.frame_index, n_time-m_start_time);
	str_dis.Format(_T("Frame:%02d;   Time: %02dm:%02ds"), m_proc_result_buf.frame_index,
		(n_time-m_start_time)/60, 
		(n_time-m_start_time)%60);
	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(str_dis);
}


int CDlgCapCam::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_proc_flgexit =  CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(m_proc_flgexit);
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

	return 0;
}


void CDlgCapCam::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	Deactive();

	CloseHandle(m_proc_flgexit);
	CloseHandle(m_proc_flgscreenshot);
	CloseHandle(m_proc_lock);
	free(m_proc_result_buf.image.data);
	free(m_img_mid1.data);
	free(m_img_mid2.data);
	free(m_img_mid3.data);
	free(m_img_mid4.data);

}


void CDlgCapCam::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	if (m_combo_list_device.GetCount())
	{
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CFG)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SCREENSHOT)->EnableWindow(TRUE);
		if (m_flg_process)
		{
			GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_CFG)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SCREENSHOT)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_CFG)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SCREENSHOT)->EnableWindow(FALSE);
		}
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CFG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SCREENSHOT)->EnableWindow(FALSE);
	}

	UpdateImage();
}


BOOL CDlgCapCam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_flg_process = 0;
	m_index_device = 0;
	m_start_time = 0;
	m_img_def.LoadFromResource(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_DEF));
	return TRUE;  // return TRUE unless you set the focus to a control

	// 异常: OCX 属性页应返回 FALSE
}


void CDlgCapCam::Step(void)
{
}


void CDlgCapCam::OnBnClickedButtonPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	Start();
}


void CDlgCapCam::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	Stop();
}


void CDlgCapCam::OnBnClickedButtonScreenshot()
{
	// TODO: 在此添加控件通知处理程序代码
	ScreenShot(1,0);
}


void CDlgCapCam::OnBnClickedButtonCfg()
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




//线程处理函数
static DWORD WINAPI thread_proc(LPVOID lpParam)
{
	int i, j, res;
	char *pdata;
	CDlgCapCam * p_cap_file;
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

	int frame_index = 0;

	CvSize sz;

	p_cap_file = (CDlgCapCam *)lpParam;

	sz.width= STE_IMAGE_WIDTH;
	sz.height = STE_IMAGE_HEIGH;
	image_optlevel = cvCreateImageHeader( sz, 8, 1);
	image_finallevel = cvCreateImageHeader( sz, 8, 1);
	image_initreg = cvCreateImageHeader( sz, 8, 1);
	image_finalreg = cvCreateImageHeader( sz, 8, 1);

	cap = cvCreateCameraCapture(p_cap_file->m_index_device);

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


		printf("begin video process!\r\n");
		while (WaitForSingleObject(p_cap_file->m_proc_flgexit, 10) != WAIT_OBJECT_0 )
		{
			//get frame
			image = cvQueryFrame(cap);
			if	(image)
			{
				frame_index++;
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
				img_src.time = frame_index;
				img_src.data_u = NULL;
				img_src.data_v = NULL;
				img_src.data_y = (unsigned char*)image_cvt_gray->imageData;
				img_src.width = STE_IMAGE_WIDTH;
				img_src.height = STE_IMAGE_HEIGH;
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
				//pdata = (char*)((MODULE_VSD*)algo_handle)->vsdet_buffer_var->ind_presm;
				//pdata = (char*)image_cvt_gray->imageData;
				for (i=0; i<img_src.height; i++)
				{
					memcpy(p_cap_file->m_img_mid1.data+i*STE_IMAGE_WIDTH, 
						pdata+i*STE_IMAGE_WIDTH, STE_IMAGE_WIDTH);
				}
				pdata = (char*)((MODULE_VSD*)algo_handle)->vsdet_buffer_var->ind_finlevel;
				//pdata = (char*)img_src.dataY;
				for (i=0; i<img_src.height; i++)
				{
					memcpy(p_cap_file->m_img_mid2.data+i*STE_IMAGE_WIDTH, 
						pdata+i*STE_IMAGE_WIDTH, STE_IMAGE_WIDTH);
				}	
				pdata = (char*)((MODULE_VSD*)algo_handle)->vsdet_buffer_var->ind_initreg;
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
		AfxMessageBox(_T("Open Capture device failed!"));
		printf("Open Capture device failed!");
	}


	printf("thread proc exit!\r\n");

	PostMessage(p_cap_file->GetSafeHwnd(), WM_MY_MESSAGE_CAP_CAM, CAP_CAM_TYPE_QUIT, 0);

	return 0;
}

