
// STEvaluationDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "DlgCapCam.h"
#include "DlgCapFile.h"
#include "DlgPlayBack.h"

class MsgEvent
{
public:
	unsigned int frame;
	unsigned int type;
	__time32_t time;
	CString para;
	MsgEvent(void)
	{
	}

	virtual ~MsgEvent(void)
	{
	}
};



// CSTEvaluationDlg dialog
class CSTEvaluationDlg : public CDialogEx
{
// Construction
public:
	CSTEvaluationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_STEVALUATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	int m_mode;
	CDlgCapFile m_dlg_capfile;
	CDlgCapCam	m_dlg_capcam;
	CDlgPlayBack m_dlg_playback;

	//for login
	CString m_username;
	CString m_passwd;

	//�����ļ�·��
	TCHAR file_path[MAX_PATH];
	TCHAR file_config_path[MAX_PATH];
	TCHAR file_sysconfig_path[MAX_PATH];
	TCHAR file_log_path[MAX_PATH];
	CString video_file_path;//���ڴ������Ƶ�ļ�·��
	CString event_file_path;//��¼���¼�csv·��
	CString target_file_path;//��¼��Ŀ���ļ�·��

	CFile cf_event, cf_target;
	

	//
	CListCtrl m_list_event;
	CArray<MsgEvent, MsgEvent>	m_event_db;
	void UpdateEventList(void);
	void AddEvent(unsigned int frame, unsigned int time, unsigned int type);
	void AddTarget(IVFD_TargetSet *target_set);
	afx_msg void OnBnClickedRadio1();
//	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	void StopAProc(void);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void GenerateEventList(void);
	afx_msg void OnHdnItemclickListEvevt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListEvevt(NMHDR *pNMHDR, LRESULT *pResult);
};
