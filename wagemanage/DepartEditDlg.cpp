// DepartEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "wagemanage.h"
#include "DepartEditDlg.h"
#include ".\departeditdlg.h"


// CDepartEditDlg 对话框

IMPLEMENT_DYNAMIC(CDepartEditDlg, CDialog)
CDepartEditDlg::CDepartEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDepartEditDlg::IDD, pParent)
	, m_oldname(_T(""))
	, m_newname(_T(""))
{
}
CDepartEditDlg::CDepartEditDlg(CString & strOld)
{
	m_oldname = strOld;
}
CDepartEditDlg::~CDepartEditDlg()
{
}
BOOL CDepartEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateData(true);

	return true;
}

void CDepartEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_oldname);
	DDX_Text(pDX, IDC_EDIT2, m_newname);
}


BEGIN_MESSAGE_MAP(CDepartEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDepartEditDlg 消息处理程序

void CDepartEditDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString strtemp=m_newname;
	OnOK();
}
