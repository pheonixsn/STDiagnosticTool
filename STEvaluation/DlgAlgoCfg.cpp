// DlgAlgoCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "STEvaluation.h"
#include "DlgAlgoCfg.h"
#include "afxdialogex.h"


// CDlgAlgoCfg 对话框

IMPLEMENT_DYNAMIC(CDlgAlgoCfg, CDialogEx)

CDlgAlgoCfg::CDlgAlgoCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAlgoCfg::IDD, pParent)
	, m_cfg_para1(0)
	, m_cfg_para2(0)
	, m_cfg_para3(0)
	, m_cfg_para4(0)
	, m_cfg_para5(0)
{

}

CDlgAlgoCfg::~CDlgAlgoCfg()
{
}

void CDlgAlgoCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cfg_para1);
	DDV_MinMaxInt(pDX, m_cfg_para1, 1, 3);
	DDX_Text(pDX, IDC_EDIT2, m_cfg_para2);
	DDV_MinMaxInt(pDX, m_cfg_para2, 1, 10);
	DDX_Text(pDX, IDC_EDIT3, m_cfg_para3);
	DDV_MinMaxInt(pDX, m_cfg_para3, 1, 2);
	DDX_Text(pDX, IDC_EDIT4, m_cfg_para4);
	DDV_MinMaxInt(pDX, m_cfg_para4, 0, 1);
	DDX_Text(pDX, IDC_EDIT5, m_cfg_para5);
	DDV_MinMaxInt(pDX, m_cfg_para5, 0, 9);
}


BEGIN_MESSAGE_MAP(CDlgAlgoCfg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgAlgoCfg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgAlgoCfg 消息处理程序


void CDlgAlgoCfg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CDialogEx::OnOK();
}
