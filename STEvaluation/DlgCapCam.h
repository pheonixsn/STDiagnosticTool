#pragma once

#include "opencv/cxcore.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "DlgAlgoCfg.h"
#include "afxwin.h"

#define  WM_MY_MESSAGE_CAP_CAM		(WM_USER+102)
#define  CAP_CAM_TYPE_QUIT			1
#define  CAP_CAM_TYPE_UPDATEIMAGE	2

// CDlgCapCam �Ի���

class CDlgCapCam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCapCam)

public:
	CDlgCapCam(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCapCam();
	CWnd * pWndParent;

// �Ի�������
	enum { IDD = IDD_DIALOG_CAPCAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnMyMsg(WPARAM, LPARAM);
	void Stop(void);
	void Start(void);

	void Active(void);
	void Deactive(void);
	void ScreenShot(int count, int inter_time);

	CString config_path;	//ϵͳ�����ļ�����Ŀ¼
	CString algo_cfg_path;	//ϵͳ���㷨�����ļ�����

	CString event_file_path;//��¼���¼�csv·��


	int m_flg_process;
	CImage m_img_show;
	CImage m_img_def;

	HANDLE	m_proc_handle;
	HANDLE	m_proc_flgexit;
	HANDLE	m_proc_flgscreenshot;
	HANDLE	m_proc_lock;

	CDlgAlgoCfg		m_dlg_cfg;
	ST_AlgoConfig	m_algo_cfg;//�㷨�����ò���
	STE_ImageBuf	m_proc_result_buf;//�㷨�������Ľ����ڴ�

	//��Ƶ�ļ�����Ϣ
	int video_file_info_frame;
	int video_file_info_fps;
	int video_file_info_fourcc;
	int video_file_info_width;
	int video_file_info_height;

	//�㷨�м���
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

	//ץ�Ŀ���
	unsigned int m_snatch_count;
	unsigned int m_snatch_intertime;
	unsigned int m_snatch_pretime;

	time_t m_trigger_snatch_time; //���һ���б����Ĵ���ʱ�䡣
	int    m_trigger_index;

	__time32_t m_start_time;
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonScreenshot();
	afx_msg void OnBnClickedButtonCfg();
};
