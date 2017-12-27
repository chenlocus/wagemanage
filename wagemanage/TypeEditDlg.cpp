// TypeEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "wagemanage.h"
#include "TypeEditDlg.h"
#include ".\typeeditdlg.h"


// CTypeEditDlg 对话框

IMPLEMENT_DYNAMIC(CTypeEditDlg, CDialog)
CTypeEditDlg::CTypeEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTypeEditDlg::IDD, pParent)
	, m_oldtype(_T(""))
	, m_olddes(_T(""))
	, m_newtype(_T(""))
	, m_newdes(_T(""))
{
}

CTypeEditDlg::~CTypeEditDlg()
{
}

void CTypeEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_oldtype);
	DDX_Text(pDX, IDC_EDIT_DESCRIPE, m_olddes);
	DDX_Text(pDX, IDC_EDIT_TYPE2, m_newtype);
	DDX_Text(pDX, IDC_EDIT_DESCRIPE2, m_newdes);
}

BOOL CTypeEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateData(true);

	return true;
}
BEGIN_MESSAGE_MAP(CTypeEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CTypeEditDlg 消息处理程序

void CTypeEditDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	
	OnOK();

}
