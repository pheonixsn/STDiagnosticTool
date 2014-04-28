
// STEvaluationDlg.cpp : implementation file
//

#include "stdafx.h"

#include "STEvaluation.h"

#include "STEvaluationDlg.h"
#include "afxdialogex.h"

#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SYSCONFIG_FILE_NAME _T("\\sysconfig.ini")
#define DETCONFIG_FILE_NAME _T("\\detconfig.ini")
#define LOG_FILE_NAME _T("\\log.csv")
#define CONFIG_PATH_NAME _T("\\config")

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSTEvaluationDlg dialog




CSTEvaluationDlg::CSTEvaluationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSTEvaluationDlg::IDD, pParent)
	, m_mode(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSTEvaluationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_mode);
	DDX_Control(pDX, IDC_LIST_EVEVT, m_list_event);
}

BEGIN_MESSAGE_MAP(CSTEvaluationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CSTEvaluationDlg::OnBnClickedRadio1)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_RADIO2, &CSTEvaluationDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CSTEvaluationDlg::OnBnClickedRadio3)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CSTEvaluationDlg::OnHdnItemclickListEvevt)
	ON_NOTIFY(NM_CLICK, IDC_LIST_EVEVT, &CSTEvaluationDlg::OnNMClickListEvevt)
END_MESSAGE_MAP()


// CSTEvaluationDlg message handlers

BOOL CSTEvaluationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

#ifdef	_DEBUG
	AllocConsole();
	freopen("CONOUT$","w+t",stdout);
	printf("SmokeTrace console\r\n");
#endif

	// TODO: Add extra initialization here
	m_mode = 0;
	//获得系统路径
	int len=GetModuleFileName(NULL,file_path, MAX_PATH);//得到应用程序路径
	*_tcsrchr(file_path,_T('\\')) = _T('\0');//去掉文件名
	_tcscpy_s(file_sysconfig_path, MAX_PATH,file_path);
	_tcscpy_s(file_log_path, MAX_PATH,file_path);
	_tcscpy_s(file_config_path, MAX_PATH,file_path);
	_tcscat_s(file_sysconfig_path,MAX_PATH-len-1,SYSCONFIG_FILE_NAME);
	_tcscat_s(file_log_path,MAX_PATH-len-1,LOG_FILE_NAME);

	len += _tcslen(CONFIG_PATH_NAME);
	_tcscat_s(file_config_path,MAX_PATH-len-1,CONFIG_PATH_NAME);


	//list event 
	m_list_event.SetExtendedStyle(LVS_EX_FULLROWSELECT);    
#ifdef DEBUG
	m_list_event.InsertColumn( 0, _T("Frame"), LVCFMT_LEFT, 50  );
#else
	m_list_event.InsertColumn( 0, _T("Frame"), LVCFMT_LEFT, 0  );
#endif
	m_list_event.InsertColumn( 1, _T("Time"), LVCFMT_LEFT, 140  );
	//m_list_event.InsertColumn( 2, _T("Type"), LVCFMT_LEFT, 60 );
	m_list_event.InsertColumn( 2, _T("Content"), LVCFMT_LEFT, 450 );

	//
	m_dlg_capfile.pWndParent = this;
	m_dlg_capcam.pWndParent = this;
	m_dlg_playback.pWndParent = this;
	m_dlg_capfile.config_path = file_config_path;
	m_dlg_capcam.config_path = file_config_path;

	
	m_dlg_capfile.Active();

	this->SetWindowTextA(_T("STDiagnostic Tool V1.3.0, ST core V2.3.0"));
	UpdateData(FALSE);

	//**********************open Login dlg**********************************************
#ifndef DEBUG
	CDlgLogin m_dlg_login;
	int res;
	HKEY hSoftKey, hKey; //定义有关的hKey，在查询结束时要关闭。
	DWORD dw;
	LPCTSTR path=_T("Software\\STEvaluation");
	LONG return0;
	TCHAR username_Get[80];
	DWORD type_1=REG_SZ;
	DWORD cbData_1=80;

	m_username = _T("admim");
	m_passwd = _T("123456");
	m_dlg_login.m_username = m_username;
	memset(username_Get,0, 80*sizeof(TCHAR));

	//1:read passwd from ref
	res=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,path,0,KEY_READ,&hKey));
	if(res == ERROR_SUCCESS)
	{
		res=::RegQueryValueEx(hKey,_T("Defpasswd"),NULL,&type_1,(LPBYTE)username_Get,&cbData_1);

		if(res == ERROR_SUCCESS)
		{
			m_passwd = CString(username_Get);
		}
		else
		{
			;//
		}
		RegCloseKey(hKey);
	}

	while (1)
	{
		m_dlg_login.m_username = m_username;
		
		if (m_dlg_login.DoModal() == IDOK)
		{
			if (m_dlg_login.m_mode_change)
			{
				if (m_dlg_login.m_old_passwd == m_passwd &&
					m_dlg_login.m_new_passwd == m_dlg_login.m_confirm)
				{
					m_passwd = m_dlg_login.m_new_passwd;
					//save new passwd in reg
					if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, path, 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL, &hSoftKey, &dw) == ERROR_SUCCESS)
					{
						//添加一个子Key,并设置值 
						return0 = RegSetValueEx(hSoftKey, _T("Defpasswd"), 0, REG_SZ, (BYTE*)m_passwd.GetBuffer(), m_passwd.GetLength()*sizeof(TCHAR)); 
					}
					AfxMessageBox(_T("Change successfully! Login again!"));
				}
				else
				{
					AfxMessageBox(_T("Change failed!"));
				}
				m_dlg_login.m_mode_change = 0;
			}
			else
			{
				if (m_passwd == m_dlg_login.m_passwd)
				{
					break;
				}
				else
				{
					AfxMessageBox(_T("Password is incorrect! Try again!"));
				}
			}
		}
		else
		{
			exit(1);
		}
	}
#endif
	ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED|SWP_DRAWFRAME);
	SetTimer(1,60000, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSTEvaluationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
#define  CLIENT_AREA_X	110
#define  CLIENT_AREA_Y	2
#define  CLIENT_AREA_W	710
#define  CLIENT_AREA_H	670
void CSTEvaluationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		CRect rect;

		switch(m_mode)
		{
		case STE_MODE_CAPFILE:
			m_dlg_capcam.ShowWindow(SW_HIDE);
			m_dlg_playback.ShowWindow(SW_HIDE);
			m_dlg_capfile.SetWindowPos(NULL, CLIENT_AREA_X,CLIENT_AREA_Y, CLIENT_AREA_W,CLIENT_AREA_H,SWP_NOZORDER );
			m_dlg_capfile.ShowWindow(SW_SHOW);
			break;
		case STE_MODE_CAPCAM:
			m_dlg_capfile.ShowWindow(SW_HIDE);
			m_dlg_playback.ShowWindow(SW_HIDE);
			m_dlg_capcam.SetWindowPos(NULL, CLIENT_AREA_X,CLIENT_AREA_Y, CLIENT_AREA_W,CLIENT_AREA_H,SWP_NOZORDER );
			m_dlg_capcam.ShowWindow(SW_SHOW);
			break;
		case STE_MODE_PLAYBACK:
			m_dlg_capcam.ShowWindow(SW_HIDE);
			m_dlg_capfile.ShowWindow(SW_HIDE);
			m_dlg_playback.SetWindowPos(NULL, CLIENT_AREA_X,CLIENT_AREA_Y, CLIENT_AREA_W,CLIENT_AREA_H,SWP_NOZORDER );
			m_dlg_playback.ShowWindow(SW_SHOW);
			break;
		default:
			break;
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSTEvaluationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSTEvaluationDlg::UpdateEventList(void)
{
	int i;
	CString	str;
	MsgEvent myevent;
	struct tm now_time;

	m_list_event.DeleteAllItems();

	for (i=0; i<m_event_db.GetCount(); i++)
	{
		myevent = m_event_db.GetAt(i);
		int nRow = m_list_event.InsertItem(0, _T(""));//插入行
		str.Format(_T("%lu"), myevent.frame);
		m_list_event.SetItemText(nRow, 0, str);//设置数据;

		if (myevent.frame >0)
		{
			str.Format(_T(" %02dm:%02ds"),myevent.time/60, myevent.time%60 );
			m_list_event.SetItemText(nRow, 1, str);//设置数据;
		}
		else
		{
			_localtime32_s(&now_time,(__time32_t *)&myevent.time) ;
			str.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"), now_time.tm_year+1900, now_time.tm_mon+1, now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
			m_list_event.SetItemText(nRow, 1, str);//设置数据;
		}
		
		//str.Format(_T("%lu"), myevent.type);
		//m_list_event.SetItemText(nRow, 2, str);//设置数据;
		
		m_list_event.SetItemText(nRow, 2, myevent.para);//设置数据;

	}
//	return 0;
}

#define  LIST_MAX 50
void CSTEvaluationDlg::AddEvent(unsigned int frame, unsigned int time, unsigned int type)
{
	int i;

	MsgEvent myevent;
	struct tm now_time;
	CString str, str_content;

	myevent.frame = frame;
	myevent.type = type;
	myevent.time = time;

	if (type == STE_SYSEVENT_FIRE_E || type == STE_SYSEVENT_SMOKE_E)
	{
		return;
	}

	if (frame >0)
	{
		//此事件由视频文件产生，时间是文件的秒数
		//str_content.Format(_T("@ %d Secs"),time);
	}
	else
	{
		//此事件是相机分析的结果，时间是绝对时间
		_localtime32_s(&now_time,(__time32_t *)&myevent.time) ;
		//str_content.Format(_T("@%04d%02d%02d-%02d%02d%02d"), now_time.tm_year+1900, now_time.tm_mon+1, now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
	}
	switch (type)
	{
		case STE_SYSEVENT_FIRE_S:
			myevent.para.Format(_T("FIRE START"));
			break;
		case STE_SYSEVENT_SMOKE_S:
			myevent.para.Format(_T("SMOKE START"));
			break;
		case STE_SYSEVENT_FIRE_E:
			myevent.para.Format(_T("FIRE END"));
			break;
		case STE_SYSEVENT_SMOKE_E:
			myevent.para.Format(_T("SMOKE END"));
			break;
	default:
		break;
	}
	str_content = myevent.para+str_content;

	//write to file
	if (m_mode == STE_MODE_CAPFILE || m_mode == STE_MODE_CAPCAM)
	{
		//写入事件文件
		if (cf_event.m_hFile == CFile::hFileNull)
		{			
			if (cf_event.Open(event_file_path, CFile::modeCreate|CFile::modeWrite))
			{
				//首先写入当前的算法配置参数
				if (m_mode == STE_MODE_CAPFILE)
				{
					str.Format(_T("sense:%d, ptz time:%d, FOV:%d, Saturation Det:%d\r\n"), m_dlg_capfile.m_algo_cfg.val_sense, m_dlg_capfile.m_algo_cfg.val_delay, m_dlg_capfile.m_algo_cfg.val_fov, m_dlg_capfile.m_algo_cfg.val_static_det);
				}
				if (m_mode == STE_MODE_CAPCAM)
				{
				}
				cf_event.Write(str.GetBuffer(0), str.GetLength()*sizeof(TCHAR));
				
				str.Format(_T("Frame, Time, Type, Content\r\n"));
				cf_event.Write(str.GetBuffer(0), str.GetLength()*sizeof(TCHAR));
				str.Format(_T("%d,%d,%d,"), frame, time, type);
				str+=str_content;
				str+=_T("\r\n");
				cf_event.Write(str.GetBuffer(0), str.GetLength()*sizeof(TCHAR));
			}
			else
			{
				printf("event file open error!\r\n" );
			}
		}
		else
		{
			str.Format(_T("%d,%d,%d,"), frame, time, type);
			str+=str_content;
			str+=_T("\r\n");
			cf_event.Write(str.GetBuffer(0), str.GetLength()*sizeof(TCHAR));
		}
	}

	//触发screen shot
	if (m_mode == STE_MODE_CAPFILE)
	{
		//m_dlg_capfile.ScreenShot(1, 0);
	}
	if (m_mode == STE_MODE_CAPCAM)
	{
		//m_dlg_capcam.ScreenShot(10, 5);
	}

	//检查list中的数据量
	if(m_event_db.GetCount() > LIST_MAX)
	{
		//防止数据过大
		for (i=0; i<m_event_db.GetCount()-LIST_MAX; i++)
		{
			m_event_db.RemoveAt(0);
		};
	}

	m_event_db.Add(myevent);


	UpdateEventList();
}


void CSTEvaluationDlg::AddTarget(IVFD_TargetSet *target_set)
{
	int i;
	if (m_mode == STE_MODE_CAPFILE)
	{
		//写入目标文件
		if (cf_target.m_hFile == CFile::hFileNull)
		{			
			if (cf_target.Open(target_file_path, CFile::typeBinary|CFile::modeCreate|CFile::modeWrite))
			{
				cf_target.Write(_T("targets__ste"), sizeof(TCHAR)*12);
				cf_target.Write(target_set, sizeof(IVFD_TargetSet));
			}
			else
			{
				printf("target file open error\r\n!" );
			}
		}
		else
		{
			cf_target.Write(target_set, sizeof(IVFD_TargetSet));
		};
	}
}


void CSTEvaluationDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	int old_v = m_mode;
	UpdateData();
	if (m_mode != old_v)
	{
		switch(m_mode)
		{
		case STE_MODE_CAPFILE:
			m_dlg_capfile.Active();
			m_dlg_capcam.Deactive();
			m_dlg_playback.Deactive();
			m_event_db.RemoveAll();
			break;
		case STE_MODE_CAPCAM:
			m_dlg_capcam.Active();
			m_dlg_capfile.Deactive();
			m_dlg_playback.Deactive();
			break;
		case STE_MODE_PLAYBACK:
			m_dlg_playback.Active();
			m_dlg_capcam.Deactive();
			m_dlg_capfile.Deactive();
			break;
		default:
			break; 
		}

		if (cf_event.m_hFile != CFile::hFileNull)
		{			cf_event.Close();		}
		if (cf_target.m_hFile != CFile::hFileNull)
		{			cf_target.Close();		}
	}
	UpdateEventList();
	Invalidate();
}
void CSTEvaluationDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	int old_v = m_mode;
	UpdateData();
	if (m_mode != old_v)
	{
		switch(m_mode)
		{
		case STE_MODE_CAPFILE:
			m_dlg_capfile.Active();
			m_dlg_capcam.Deactive();
			m_dlg_playback.Deactive();
			break;
		case STE_MODE_CAPCAM:
			m_dlg_capcam.Active();
			m_dlg_capfile.Deactive();
			m_dlg_playback.Deactive();
			m_event_db.RemoveAll();
			break;
		case STE_MODE_PLAYBACK:
			m_dlg_playback.Active();
			m_dlg_capcam.Deactive();
			m_dlg_capfile.Deactive();
			break;
		default:
			break; 
		}
		if (cf_event.m_hFile != CFile::hFileNull)
		{			cf_event.Close();		}
		if (cf_target.m_hFile != CFile::hFileNull)
		{			cf_target.Close();		}
	}
	UpdateEventList();
	Invalidate();
}


void CSTEvaluationDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	int old_v = m_mode;
	UpdateData();
	if (m_mode != old_v)
	{
		switch(m_mode)
		{
		case STE_MODE_CAPFILE:
			m_dlg_capfile.Active();
			m_dlg_capcam.Deactive();
			m_dlg_playback.Deactive();
			break;
		case STE_MODE_CAPCAM:
			m_dlg_capcam.Active();
			m_dlg_capfile.Deactive();
			m_dlg_playback.Deactive();
			break;
		case STE_MODE_PLAYBACK:
			m_dlg_playback.Active();
			m_dlg_capcam.Deactive();
			m_dlg_capfile.Deactive();
			m_event_db.RemoveAll();
			break;
		default:
			break; 
		}
	}
	UpdateEventList();
	Invalidate();
}




int CSTEvaluationDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_dlg_capfile.Create(IDD_DIALOG_CAPFILE, this);
	m_dlg_capfile.ShowWindow(SW_HIDE);

	m_dlg_capcam.Create(IDD_DIALOG_CAPCAM, this);
	m_dlg_capcam.ShowWindow(SW_HIDE);

	m_dlg_playback.Create(IDD_DIALOG_PLAYBACK, this);
	m_dlg_playback.ShowWindow(SW_HIDE);
	return 0;
}



//为了在结束时，能够将记录文件flush
void CSTEvaluationDlg::StopAProc(void)
{
	if (cf_event.m_hFile != CFile::hFileNull)
	{			cf_event.Close();		}
	if (cf_target.m_hFile != CFile::hFileNull)
	{			cf_target.Close();		}
}


void CSTEvaluationDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	StopAProc();
}

//24小时退出
static int g_time_count = 24*60;
void CSTEvaluationDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (g_time_count-- <=0)
	{
		exit(1);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CSTEvaluationDlg::OnSize(UINT nType, int cx, int cy)
{
	//CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}

#define EVENT_FILE_MAX	1024*1024*4

void CSTEvaluationDlg::GenerateEventList(void)
{
	//打开csv文件，更新事件列表
	CFile cf;
	char * buf;
	CString str_file;
	int pos_start;
	int pos_line_s, pos_line_e;
	int pos_dot;
	MsgEvent myevent;
	CString str;
	if(m_mode == STE_MODE_PLAYBACK && !event_file_path.IsEmpty())
	{
		if (cf.Open(event_file_path, CFile::modeRead))
		{
			m_event_db.RemoveAll();
			buf = (char*)malloc(EVENT_FILE_MAX);
			assert(buf);
			cf.Read(buf, EVENT_FILE_MAX);
			str_file = buf;
			pos_start = str_file.Find(_T("Frame, Time, Type, Content"));
			if (pos_start == -1)
			{
				cf.Close();
				free(buf);
				AfxMessageBox(_T("Event file format error!"));
				return;
			}
			pos_line_s = str_file.Find(_T("\r\n"), pos_start);
			pos_line_e = str_file.Find(_T("\r\n"), pos_line_s+2);
			while (pos_line_s >0 && pos_line_e > 0)
			{
				pos_line_s+=2;

				pos_dot = str_file.Find(_T(","), pos_line_s);
				str = str_file.Mid(pos_line_s, pos_dot-pos_line_s);
				myevent.frame = StrToInt(str);

				pos_line_s = pos_dot+1;
				pos_dot = str_file.Find(_T(","), pos_line_s);
				str = str_file.Mid(pos_line_s, pos_dot-pos_line_s);
				myevent.time = StrToInt(str);

				pos_line_s = pos_dot+1;
				pos_dot = str_file.Find(_T(","), pos_line_s);
				str = str_file.Mid(pos_line_s, pos_dot-pos_line_s);
				myevent.type = StrToInt(str);

				pos_line_s = pos_dot+1;
				pos_dot = str_file.Find(_T("\r\n"), pos_line_s);
				str = str_file.Mid(pos_line_s, pos_dot-pos_line_s);
				myevent.para = str;

				m_event_db.Add(myevent);

				pos_line_s = pos_dot;
				pos_line_e = pos_line_e = str_file.Find(_T("\r\n"), pos_line_s+2);
			}


			free(buf);
			cf.Close();
			UpdateEventList();
		}
		else
		{
			AfxMessageBox(_T("Event open failed!"));
		}
		;
	}
}


void CSTEvaluationDlg::OnHdnItemclickListEvevt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

}


void CSTEvaluationDlg::OnNMClickListEvevt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;

	CString tmp_filename;
	MsgEvent myevent;

	*pResult = 0;

	if(m_mode != STE_MODE_PLAYBACK)
	{
		return;
	}
	if(pNMListView->iItem!=-1)
	{
		myevent = m_event_db.GetAt(m_event_db.GetCount() -1 - pNMListView->iItem);
		
		if (myevent.frame)
		{
			tmp_filename.Format(_T("_%012d_alarm"), myevent.time);
			m_dlg_playback.ShowImage(tmp_filename);
		}
		else
		{
			tmp_filename.Format(_T("_%012d_alarm"), myevent.time);
			m_dlg_playback.ShowImage(tmp_filename);
		}

	}

	*pResult = 0;

}
