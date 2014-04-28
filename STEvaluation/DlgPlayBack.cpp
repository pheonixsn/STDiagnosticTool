// DlgPlayBack.cpp : 实现文件
//

#include "stdafx.h"
#include "STEvaluation.h"
#include "STEvaluationDlg.h"
#include "DlgPlayBack.h"
#include "afxdialogex.h"


// CDlgPlayBack 对话框
static DWORD WINAPI thread_proc(LPVOID lpParam);

IMPLEMENT_DYNAMIC(CDlgPlayBack, CDialogEx)

CDlgPlayBack::CDlgPlayBack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPlayBack::IDD, pParent)
	, m_file_video(_T(""))
{

}

CDlgPlayBack::~CDlgPlayBack()
{
}

void CDlgPlayBack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BROWSE, m_file_video);
	DDX_Control(pDX, IDC_SLIDER_PEOC, m_slider_progress);
}


BEGIN_MESSAGE_MAP(CDlgPlayBack, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CDlgPlayBack::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CDlgPlayBack::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STEP, &CDlgPlayBack::OnBnClickedButtonStep)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDlgPlayBack::OnBnClickedButtonStop)
	ON_MESSAGE(WM_MY_MESSAGE_PLAYBACK, OnMyMsg) 
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDlgPlayBack 消息处理程序
LRESULT CDlgPlayBack::OnMyMsg(WPARAM wParam, LPARAM lParam)
{
	UINT32 msg_type;
	int i, j;
	char * pdata;

	msg_type = (UINT32)wParam;

	switch(msg_type)
	{
	case PLAYBACK_TYPE_QUIT:
		Stop();
		break;
	case PLAYBACK_TYPE_UPDATEIMAGE:
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

			for (i=0;i<STE_IMAGE_HEIGH;i++)
			{
				memcpy(pdata + i*m_img_show.GetPitch(), (char*)m_proc_result_buf.image.data+i*STE_IMAGE_WIDTH*4, STE_IMAGE_WIDTH*3);
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

void CDlgPlayBack::Stop(void)
{
	printf("playback stop\r\n");

	m_slider_progress.SetPos(0);

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


void CDlgPlayBack::Start(void)
{
	printf("playback start\r\n");
	UpdateData();
	if (!m_flg_process)
	{
		ResetEvent(m_proc_flgexit);
		ResetEvent(m_proc_flgstep);
		ResetEvent(m_proc_flgsetpos);
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


void CDlgPlayBack::Active(void)
{
	printf("playback active\r\n");

	CString str;
	m_flg_process = 0;
	m_file_video = _T("");
	//init cfg para

	video_file_info_frame = 0;
	video_file_info_fps = 0;
	video_file_info_fourcc = 0;
	video_file_info_width = 0;
	video_file_info_height = 0;

	m_slider_progress.SetPos(0);

	pic_path = _T("");
	pic_name = _T("");

	UpdateData(FALSE);
	Invalidate();
}


void CDlgPlayBack::Deactive(void)
{
	printf("playback deactive\r\n");
	Stop();

	if (!m_img_show.IsNull())
	{
		m_img_show.Destroy();
	}

	video_file_path = _T("");
	target_file_path = _T("");
	((CSTEvaluationDlg*)pWndParent)->video_file_path = video_file_path;
	((CSTEvaluationDlg*)pWndParent)->target_file_path = target_file_path;

	if (m_target_set)
	{
		free(m_target_set);
		m_target_set = NULL;
	}
	m_target_set_num = 0;
	
	UpdateData(FALSE);

}


void CDlgPlayBack::OnBnClickedButtonBrowse()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CString file_path, source_path, str_tmp;
	CString szFilters;
	szFilters = "ST Event Files (*.csv)|*.csv||";
	CFileDialog fileDlg (TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if(fileDlg.DoModal() == IDOK)
	{
		((CSTEvaluationDlg*)pWndParent)->event_file_path = fileDlg.GetPathName();
		m_file_video = fileDlg.GetPathName();
		video_filename = fileDlg.GetFileTitle();

		//如果文件名是_CAM开头的，就认为camera模式的
		str_tmp = video_filename.Left(4);
		if (str_tmp.Compare(_T("_CAM")) == 0)
		{
			pic_path = ((CSTEvaluationDlg*)pWndParent)->file_path;
			pic_path += _T("\\Screenshot\\");
		}
		else
		{
			pic_path = m_file_video.Left(m_file_video.ReverseFind(_T('\\')));
			pic_path += _T("\\Screenshot\\");
			pic_path += video_filename;
		}
		//通知parent 更新event list
		((CSTEvaluationDlg*)pWndParent)->GenerateEventList();

		pic_name = _T("");
	}
	else
	{
		m_file_video= _T("");
	}
	video_file_path = m_file_video;
	//设置相关的其他文件路径
	UpdateData(FALSE);

	Invalidate();
}


void CDlgPlayBack::OnBnClickedButtonPlay()
{
	CFileFind find;
	CString str, str_str,str_pre;
	BOOL isfind;
	int flg_first = 1;

	str_str = pic_path+_T("*_alarm.jpg");
	if (find.FindFile(str_str))
	{
		isfind = 1;

		while(isfind)
		{
			isfind = find.FindNextFileA();

			if (find.IsDots())
				continue;

			// if it's a directory, recursively search it


			if (find.IsDirectory())
			{
				continue;
			}
			else
			{
				str_pre = str;

				str = find.GetFilePath();
				if (flg_first)
				{
					str_pre = str;
					flg_first = 0;
				}

				if (str == pic_name)
				{
					
					{
						if (!m_img_show.IsNull())
						{
							m_img_show.Destroy();
						}
						if(m_img_show.Load(str_pre)>=0)
						{
							UpdateImage();
							pic_name = str_pre;
						}
						else
						{
							str_pre += _T(" does not exist!");
							AfxMessageBox(str_pre);
						}
					}
					break;
				}

			}

		}

	}
	find.Close();
		
}


void CDlgPlayBack::OnBnClickedButtonStep()
{
	// TODO: 在此添加控件通知处理程序代码
	//Step();
}


void CDlgPlayBack::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	//Stop();
	CFileFind find;
	CString str, str_str;
	BOOL isfind;

	str_str = pic_path+_T("*_alarm.jpg");
	if (find.FindFile(str_str))
	{
		isfind = 1;

		while(isfind)
		{
			isfind = find.FindNextFileA();

			if (find.IsDots())
				continue;

			// if it's a directory, recursively search it


			if (find.IsDirectory())
			{
				continue;
			}
			else
			{
				str = find.GetFilePath();

				if (str == pic_name)
				{
					if (isfind)
					{
						find.FindNextFileA();
						str = find.GetFilePath();
						if (!m_img_show.IsNull())
						{
							m_img_show.Destroy();
						}
						if(m_img_show.Load(str)>=0)
						{
							UpdateImage();
							pic_name = str;
						}
						else
						{
							str += _T(" does not exist!");
							AfxMessageBox(str);
						}
					}
					break;
				}

			}
			
		}
		
	}
	find.Close();
	
}


int CDlgPlayBack::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_proc_flgexit =  CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(m_proc_flgexit);
	m_proc_flgstep =  CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(m_proc_flgstep);
	m_proc_flgsetpos =  CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(m_proc_flgsetpos);
	m_proc_lock = CreateMutex(NULL,0, NULL);
	assert(m_proc_lock);
	
	memset(&m_proc_result_buf, 0, sizeof(m_proc_result_buf));
	m_proc_result_buf.image.data = (unsigned char *)malloc(STE_IMAGE_HEIGH*STE_IMAGE_WIDTH*4);
	assert(m_proc_result_buf.image.data);

	return 0;
}


void CDlgPlayBack::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	Deactive();

	CloseHandle(m_proc_flgexit);
	CloseHandle(m_proc_flgstep);
	CloseHandle(m_proc_flgsetpos);
	CloseHandle(m_proc_lock);
}


BOOL CDlgPlayBack::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_flg_process = 0;
	m_set_pos = 0;
	m_img_def.LoadFromResource(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_DEF));

	m_slider_progress.SetRange(0,100);
	m_slider_progress.SetPageSize(10);
	m_slider_progress.SetLineSize(1);
	m_slider_progress.SetTicFreq(10);

	m_target_set = NULL;
	m_target_set_num = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgPlayBack::UpdateImage(void)
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
		IVFD_TargetSet *cur_target_set;

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

		cur_target_set = GetCurTargetSet(m_proc_result_buf.frame_index);
		if (cur_target_set)
		{
			for (i=0; i<cur_target_set->num; i++)
			{

				MemDC1.Rectangle(cur_target_set->targets[i].rect.left,
					cur_target_set->targets[i].rect.bottom,
					cur_target_set->targets[i].rect.right,
					cur_target_set->targets[i].rect.top);
			}

			cur_target_set = GetCurTargetSet(m_proc_result_buf.frame_index-1);
			{
				if (cur_target_set == NULL)
				{
					((CSTEvaluationDlg*)pWndParent)->AddEvent(m_proc_result_buf.frame_index,m_proc_result_buf.frame_index/video_file_info_fps,STE_SYSEVENT_SMOKE_S);
				}
			}
		}

		//if (!m_proc_result_buf.flg_used)
		//{
		//	if (m_proc_result_buf.target_set.num)
		//	{
		//		((CSTEvaluationDlg*)pWndParent)->AddTarget(&m_proc_result_buf.target_set);
		//	}
		//	//do event
		//	for (i=0; i<m_proc_result_buf.event_set.num; i++)
		//	{
		//		((CSTEvaluationDlg*)pWndParent)->AddEvent(m_proc_result_buf.event_set.events[i].frame,m_proc_result_buf.event_set.events[i].frame/video_file_info_fps,m_proc_result_buf.event_set.events[i].type);
		//	}

		//	//防止由于刷新，事件被触发两次
		//	m_proc_result_buf.flg_used = TRUE;
		//}



		//---------------------抓拍的操作-------------------
		//if (0)
		//{
		//	CImage img;
		//	img.Attach(MemBitmap1);
		//	img.Save(_T("e:\\1.jpg"));
		//	img.Detach();
		//}

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
		pimage->StretchBlt(pDC1->GetSafeHdc(),client_rect1, rect_image,SRCCOPY);

		pDis1->ReleaseDC(pDC1);
	}

	//因为帧数等信息和图像相关，所以也放在此处更新
	
	if (video_file_info_fps == 0)
	{
		video_file_info_fps = 1;
	}
	if (video_file_info_frame > 0)
	{
		m_slider_progress.SetPos(m_proc_result_buf.frame_index*100/video_file_info_frame);		
	}

	str_dis=pic_name;
	GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(str_dis);
}


void CDlgPlayBack::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	UpdateImage();
}


void CDlgPlayBack::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CDlgPlayBack::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (&m_slider_progress == (CSliderCtrl*)pScrollBar)
	{
		m_set_pos = m_slider_progress.GetPos();

		SetEvent(m_proc_flgsetpos);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


//线程处理函数
static DWORD WINAPI thread_proc(LPVOID lpParam)
{
	int i, res;
	char *pdata;
	CDlgPlayBack * p_cap_file;
	IplImage * image;// = cvLoadImage(path_image1,1);
	IplImage * image_cvt_rgb;

	CvCapture * cap; 

	int frame_num;
	int frame_index;
	int video_fps;

	CvSize sz;

	p_cap_file = (CDlgPlayBack *)lpParam;

	sz.width= STE_IMAGE_WIDTH;
	sz.height = STE_IMAGE_HEIGH;

	cap = cvCreateFileCapture(p_cap_file->video_file_path.GetBuffer(0));

	if (cap)
	{	
		frame_num = cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_COUNT);
		video_fps = cvGetCaptureProperty(cap, CV_CAP_PROP_FPS);

		printf("begin video playback!\r\n");
		while (WaitForSingleObject(p_cap_file->m_proc_flgexit, 1000/video_fps) != WAIT_OBJECT_0 )
		{
			if (p_cap_file->m_proc_mode_step)
			{
				WaitForSingleObject(p_cap_file->m_proc_flgstep, INFINITE);
			}
			if (WaitForSingleObject(p_cap_file->m_proc_flgsetpos, 0) == WAIT_OBJECT_0)
			{
				cvSetCaptureProperty(cap, CV_CAP_PROP_POS_FRAMES, p_cap_file->m_set_pos*frame_num/100);
			}
			//get frame
			frame_index = cvGetCaptureProperty(cap, CV_CAP_PROP_POS_FRAMES);
			image = cvQueryFrame(cap);
			if	(image)
			{
				//将图像的分辨率归一化到cif
				image_cvt_rgb = cvCreateImage(sz, image->depth, image->nChannels);
				
				cvResize(image, image_cvt_rgb, CV_INTER_LINEAR );

				//post result
				WaitForSingleObject(p_cap_file->m_proc_lock, INFINITE);
				// save result 
				p_cap_file->m_proc_result_buf.image.width = STE_IMAGE_WIDTH;
				p_cap_file->m_proc_result_buf.image.height = STE_IMAGE_HEIGH;
				p_cap_file->m_proc_result_buf.frame_num = frame_num;
				p_cap_file->m_proc_result_buf.frame_index = frame_index;
				
				//save image;
				for (i=0; i<image_cvt_rgb->height; i++)
				{
					memcpy(p_cap_file->m_proc_result_buf.image.data+i*STE_IMAGE_WIDTH*4, 
						image_cvt_rgb->imageData+i*image_cvt_rgb->widthStep, STE_IMAGE_WIDTH*image_cvt_rgb->nChannels);
				}			
				ReleaseMutex(p_cap_file->m_proc_lock);
				
				PostMessage(p_cap_file->GetSafeHwnd(), WM_MY_MESSAGE_CAP_FILE, CAP_FILE_TYPE_UPDATEIMAGE, 0);
			
				cvReleaseImage(&image_cvt_rgb);
			}
			else
			{
				break;
			}
		}
		printf("playback exit\r\n");

		cvReleaseCapture(&cap);
	}
	else
	{
		AfxMessageBox(_T("Video file format is not supported!"));
		printf("open video file failed!\r\n");
	}


	printf("thread proc exit!\r\n");

	PostMessage(p_cap_file->GetSafeHwnd(), WM_MY_MESSAGE_PLAYBACK, PLAYBACK_TYPE_QUIT, 0);

	return 0;
}


void CDlgPlayBack::Step(void)
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


IVFD_TargetSet* CDlgPlayBack::GetCurTargetSet(int frame_index)
{
	IVFD_TargetSet * cur_target_set = NULL;
	int i;


	if (m_target_set_num && m_target_set)
	{
		for (i=0; i<m_target_set_num; i++)
		{
			if (m_target_set[i].frame <= frame_index && frame_index < m_target_set[i].frame+5)
			{
				cur_target_set = m_target_set+i;
			}
		}
	}
	
	return cur_target_set;
}


void CDlgPlayBack::ShowImage(CString name_time)
{
	CString str_name;
	HRESULT h_res;

	str_name = pic_path;
	str_name += name_time;
	str_name += _T(".jpg");
	
	if (!m_img_show.IsNull())
	{
		m_img_show.Destroy();
	}
	h_res = m_img_show.Load(str_name);
	if (SUCCEEDED(h_res))
	{
		
		pic_name = str_name;
		UpdateImage();
	}
	else
	{
		str_name += _T(" does not exist!");
		AfxMessageBox(str_name);
	}


}
