// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "STEvaluation.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// CDlgLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLogin::IDD, pParent)
	, m_mode_change(FALSE)
	, m_username(_T(""))
	, m_passwd(_T(""))
	, m_old_passwd(_T(""))
	, m_new_passwd(_T(""))
	, m_confirm(_T(""))
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_CHANGE, m_mode_change);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_passwd);
	DDX_Text(pDX, IDC_EDIT_OLDPASSWD, m_old_passwd);
	DDX_Text(pDX, IDC_EDIT_NEWPASSWD, m_new_passwd);
	DDX_Text(pDX, IDC_EDIT_CONFIRM, m_confirm);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_CHANGE, &CDlgLogin::OnBnClickedCheckChange)
	ON_BN_CLICKED(IDOK, &CDlgLogin::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLogin ��Ϣ�������


BOOL CDlgLogin::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_username = _T("admin");
	m_passwd = _T("");
	m_mode_change = 0;

	UpdateData(FALSE);

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


void CDlgLogin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	if (m_mode_change)
	{
		GetDlgItem(IDC_STATIC_LOGIN_PASSWD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PASSWD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LOGIN_NEWPASSWD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_NEWPASSWD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LOGIN_OLDPASSWD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_OLDPASSWD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LOGIN_CONFIRM)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CONFIRM)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_STATIC_LOGIN_PASSWD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PASSWD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LOGIN_NEWPASSWD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_NEWPASSWD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LOGIN_OLDPASSWD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_OLDPASSWD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LOGIN_CONFIRM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CONFIRM)->ShowWindow(SW_HIDE);
	}

}


void CDlgLogin::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}


void CDlgLogin::OnBnClickedCheckChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_mode_change;
	Invalidate();
}


void CDlgLogin::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CDialogEx::OnOK();
}
