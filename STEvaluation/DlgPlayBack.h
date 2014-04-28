#pragma once

#include "opencv/cxcore.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "afxcmn.h"
// CDlgPlayBack 对话框

#define  WM_MY_MESSAGE_PLAYBACK		(WM_USER+101)
#define  PLAYBACK_TYPE_QUIT			1
#define  PLAYBACK_TYPE_UPDATEIMAGE	2

class CDlgPlayBack : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPlayBack)

public:
	CDlgPlayBack(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPlayBack();
	CWnd * pWndParent;

// 对话框数据
	enum { IDD = IDD_DIALOG_PLAYBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void Stop(void);
	void Start(void);
	void Active(void);
	void Deactive(void);
	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStep();
	afx_msg void OnBnClickedButtonStop();
	afx_msg LRESULT OnMyMsg(WPARAM, LPARAM);
	//和处理进程相关的
	HANDLE	m_proc_handle;
	HANDLE	m_proc_flgexit;
	HANDLE	m_proc_flgstep;
	HANDLE	m_proc_flgsetpos;
	HANDLE	m_proc_lock;
	int		m_proc_mode_step;

	//视频文件的信息
	int video_file_info_frame;
	int video_file_info_fps;
	int video_file_info_fourcc;
	int video_file_info_width;
	int video_file_info_height;

	CString video_file_path;//正在处理的视频文件路径
	CString target_file_path;//记录的目标文件路径
	CString m_file_video;
	CString video_filename;
	CString pic_path;
	CString pic_name;

	int m_flg_process;
	CImage m_img_show;
	CImage m_img_def;

	//目标数据缓冲
	IVFD_TargetSet	*m_target_set;
	int				m_target_set_num;
	
	STE_ImageBuf	m_proc_result_buf;//算法处理结果的交换内存
	int m_set_pos;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	void UpdateImage(void);
	afx_msg void OnPaint();
	CSliderCtrl m_slider_progress;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void Step(void);
	IVFD_TargetSet* GetCurTargetSet(int frame_index);
	void ShowImage(CString name_time);
};
