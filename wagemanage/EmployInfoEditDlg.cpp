// EmployInfoEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "wagemanage.h"
#include "EmployInfoEditDlg.h"
#include ".\employinfoeditdlg.h"


// CEmployInfoEditDlg 对话框

IMPLEMENT_DYNAMIC(CEmployInfoEditDlg, CDialog)
CEmployInfoEditDlg::CEmployInfoEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmployInfoEditDlg::IDD, pParent)
	, m_name(_T(""))
{
}

CEmployInfoEditDlg::~CEmployInfoEditDlg()
{
}

BOOL CEmployInfoEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CStringArray strNamelist;
	UpdateData(false);
	DWORD dwCount=0;
	m_wagedealagt->GetDepartmentInfo(strNamelist);
	dwCount = strNamelist.GetCount();
	if (dwCount<=0)
		return false;
	for(int i=0;i<dwCount;i++)
	{
		m_departlist.AddString(strNamelist.GetAt(i));
	}
	int iSel =m_departlist.FindString(0,strOldDepartment);
	
	m_departlist.SetCurSel(iSel);


	return true;
}

void CEmployInfoEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME_EDIT, m_name);
	DDX_Control(pDX, IDC_DEPART_COMBO, m_departlist);
}


BEGIN_MESSAGE_MAP(CEmployInfoEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CEmployInfoEditDlg 消息处理程序

void CEmployInfoEditDlg::SetEmplyeeInfo(CString strInfo,CWagedealAgt *pDatabase)
{
	CStringArray strArray;
	m_wagedealagt = pDatabase;
	m_wagedealagt->StringTranslation(strInfo,'-',strArray);
	m_name = strArray.GetAt(0);
	strOldName = m_name;
	strOldDepartment = strArray.GetAt(1);
	
}

void CEmployInfoEditDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_departlist.GetLBText(m_departlist.GetCurSel(),m_Department);
	m_wagedealagt->ModifyEmployeeInfo(strOldName,m_name,m_Department);

	OnOK();
}
