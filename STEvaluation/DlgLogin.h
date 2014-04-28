#pragma once


// CDlgLogin 对话框

class CDlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLogin();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_mode_change;
	CString m_username;
	CString m_passwd;
	CString m_old_passwd;
	CString m_new_passwd;
	CString m_confirm;
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCheckChange();
	afx_msg void OnBnClickedOk();
};
