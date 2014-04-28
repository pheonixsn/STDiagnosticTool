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



// CDlgCapFile �Ի���
using namespace ATL;
class CDlgCapFile : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCapFile)

public:
	CDlgCapFile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCapFile();

// �Ի�������
	enum { IDD = IDD_DIALOG_CAPFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CWnd * pWndParent;
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnMyMsg(WPARAM, LPARAM);
	void Stop(void);
	void Start(void);

	CString config_path;	//ϵͳ�����ļ�����Ŀ¼
	CString algo_cfg_path;	//ϵͳ���㷨�����ļ�����
	CString video_file_path;//���ڴ������Ƶ�ļ�·��
	CString video_filename;//���ڴ������Ƶ�ļ�·��
	CString event_file_path;//��¼���¼�csv·��
	CString target_file_path;//��¼��Ŀ���ļ�·��
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
	//�ʹ��������ص�

	HANDLE	m_proc_handle;
	HANDLE	m_proc_flgexit;
	HANDLE	m_proc_flgstep;
	HANDLE	m_proc_flgscreenshot;
	HANDLE	m_proc_lock;

	int		m_proc_mode_step;

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
	time_t m_trigger_snatch_time; //���һ���б����Ĵ���ʱ�䡣
	int    m_trigger_index;
	int    m_firstalarm;
};
