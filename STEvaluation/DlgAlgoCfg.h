#pragma once


// CDlgAlgoCfg �Ի���

class CDlgAlgoCfg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAlgoCfg)

public:
	CDlgAlgoCfg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAlgoCfg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ALGO_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_cfg_para1;
	int m_cfg_para2;
	int m_cfg_para3;
	int m_cfg_para4;
	afx_msg void OnBnClickedOk();
	int m_cfg_para5;
};
