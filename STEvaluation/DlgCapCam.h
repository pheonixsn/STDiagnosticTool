#pragma once

#include "opencv/cxcore.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "DlgAlgoCfg.h"
#include "afxwin.h"

#define  WM_MY_MESSAGE_CAP_CAM		(WM_USER+102)
#define  CAP_CAM_TYPE_QUIT			1
#define  CAP_CAM_TYPE_UPDATEIMAGE	2

// CDlgCapCam 对话框

class CDlgCapCam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCapCam)

public:
	CDlgCapCam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCapCam();
	CWnd * pWndParent;

// 对话框数据
	enum { IDD = IDD_DIALOG_CAPCAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnMyMsg(WPARAM, LPARAM);
	void Stop(void);
	void Start(void);

	void Active(void);
	void Deactive(void);
	void ScreenShot(int count, int inter_time);

	CString config_path;	//系统配置文件所在目录
	CString algo_cfg_path;	//系统的算法配置文件所在

	CString event_file_path;//记录的事件csv路径


	int m_flg_process;
	CImage m_img_show;
	CImage m_img_def;

	HANDLE	m_proc_handle;
	HANDLE	m_proc_flgexit;
	HANDLE	m_proc_flgscreenshot;
	HANDLE	m_proc_lock;

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
	void UpdateImage(void);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	void Step(void);
	CComboBox m_combo_list_device;
	int m_index_device;

	//抓拍控制
	unsigned int m_snatch_count;
	unsigned int m_snatch_intertime;
	unsigned int m_snatch_pretime;

	time_t m_trigger_snatch_time; //最后一次有报警的触发时间。
	int    m_trigger_index;

	__time32_t m_start_time;
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonScreenshot();
	afx_msg void OnBnClickedButtonCfg();
};
