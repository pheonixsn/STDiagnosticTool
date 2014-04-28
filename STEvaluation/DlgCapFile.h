#pragma once
//#include "STEvaluationDlg.h"
#include "opencv/cxcore.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "DlgAlgoCfg.h"


//data file directory
#define SERVER_LICENSE_FPATH		_T(".\\data\\VSV_license.xml")
#define SERVER_INIT_PARAM_FPATH		_T(".\\data\\VSV_init_param.xml")
#define SERVER_NEWIMAGE_PARAM_FPATH _T(".\\data\\VSV_newimage_param.xml")
#define SERVER_SCENE_FPATH			_T(".\\data\\VSV_scene.dat")

#define  WM_MY_MESSAGE_CAP_FILE		(WM_USER+101)
#define  CAP_FILE_TYPE_QUIT			1
#define  CAP_FILE_TYPE_UPDATEIMAGE	2



// CDlgCapFile 对话框
using namespace ATL;
class CDlgCapFile : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCapFile)

public:
	CDlgCapFile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCapFile();

// 对话框数据
	enum { IDD = IDD_DIALOG_CAPFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CWnd * pWndParent;
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnMyMsg(WPARAM, LPARAM);
	void Stop(void);
	void Start(void);

	CString config_path;	//系统配置文件所在目录
	CString algo_cfg_path;	//系统的算法配置文件所在
	CString video_file_path;//正在处理的视频文件路径
	CString video_filename;//正在处理的视频文件路径
	CString event_file_path;//记录的事件csv路径
	CString target_file_path;//记录的目标文件路径
	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	CString m_file_video;
	void Active(void);
	void Deactive(void);
	int m_flg_process;
	CImage m_img_show;
	CImage m_img_def;


	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void UpdateImage(void);
	//和处理进程相关的

	HANDLE	m_proc_handle;
	HANDLE	m_proc_flgexit;
	HANDLE	m_proc_flgstep;
	HANDLE	m_proc_flgscreenshot;
	HANDLE	m_proc_lock;

	int		m_proc_mode_step;

	CDlgAlgoCfg		m_dlg_cfg;
	ST_AlgoConfig	m_algo_cfg;//算法的配置参数
	STE_ImageBuf	m_proc_result_buf;//算法处理结果的交换内存

	//视频文件的信息
	int video_file_info_frame;
	int video_file_info_fps;
	int video_file_info_fourcc;
	int video_file_info_width;
	int video_file_info_height;

	//算法中间结果
	IVFD_Image m_img_mid1;
	IVFD_Image m_img_mid2;
	IVFD_Image m_img_mid3;
	IVFD_Image m_img_mid4;
	CImage	   m_img1;
	CImage	   m_img2;
	CImage	   m_img3;
	CImage	   m_img4;

	IVFD_Image m_img_mid5;
	IVFD_Image m_img_mid6;
	IVFD_Image m_img_mid7;
	IVFD_Image m_img_mid8;
	CImage	   m_img5;
	CImage	   m_img6;
	CImage	   m_img7;
	CImage	   m_img8;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonStep();
	void Step(void);
	afx_msg void OnBnClickedButtonCfg();
	int m_video_clip_start;
	int m_video_clip_end;
	BOOL m_video_clip_enable;
	afx_msg void OnBnClickedButtonScreenshot();
	void ScreenShot(int count, int inter_time);
	time_t m_trigger_snatch_time; //最后一次有报警的触发时间。
	int    m_trigger_index;
	int    m_firstalarm;
};
