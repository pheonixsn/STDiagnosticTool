#pragma once


// CDlgAlgoCfg 对话框

class CDlgAlgoCfg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAlgoCfg)

public:
	CDlgAlgoCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAlgoCfg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ALGO_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_cfg_para1;
	int m_cfg_para2;
	int m_cfg_para3;
	int m_cfg_para4;
	afx_msg void OnBnClickedOk();
	int m_cfg_para5;
};
