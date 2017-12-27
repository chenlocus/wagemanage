// NameInputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "wagemanage.h"
#include "NameInputDlg.h"
#include ".\nameinputdlg.h"
#include "EmployInfoEditDlg.h"
// CNameInputDlg 对话框

IMPLEMENT_DYNAMIC(CNameInputDlg, CDialog)
CNameInputDlg::CNameInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNameInputDlg::IDD, pParent)
	, m_name(_T(""))
{
}

CNameInputDlg::~CNameInputDlg()
{
}
BOOL CNameInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CStringArray strNamelist;
	DWORD dwCount=0;
	m_wagedealagt.GetNameAndDepartList(strNamelist);
	dwCount = strNamelist.GetCount();
	for(int i=0;i<dwCount;i++)
	{
		m_namelist.AddString(strNamelist.GetAt(i));
	}
	if (false ==m_wagedealagt.GetDepartmentInfo(strNamelist))
	{
		AfxMessageBox("请先输入部门信息！");
		return false;
	}
	dwCount = strNamelist.GetCount();
	if (dwCount<=0)
		return false;
	for(int i=0;i<dwCount;i++)
	{
		m_departlist.AddString(strNamelist.GetAt(i));
	}
	m_departlist.SetCurSel(0);


	return true;
}

void CNameInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME_EDIT, m_name);
	DDX_Control(pDX, IDC_NAMEADD_LIST, m_addnames);
	DDX_Control(pDX, IDC_NAME_LIST, m_namelist);
	DDX_Control(pDX, IDC_DEPART_COMBO, m_departlist);
}


BEGIN_MESSAGE_MAP(CNameInputDlg, CDialog)
	ON_BN_CLICKED(ID_ADD_NAME, OnBnClickedAddName)
	ON_BN_CLICKED(ID_DEL_NAME, OnBnClickedDelName)
	ON_BN_CLICKED(ID_SAVE_NAME, OnBnClickedSaveName)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(ID_MODIFY_NAME, OnBnClickedModifyName)
	ON_BN_CLICKED(ID_DEL_SAVE, OnBnClickedDelSave)
END_MESSAGE_MAP()


// CNameInputDlg 消息处理程序

void CNameInputDlg::OnBnClickedAddName()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTmp;
	UpdateData(true);
	if (0==m_name.CompareNoCase(""))
		return;
	m_departlist.GetLBText(m_departlist.GetCurSel(),strTmp);
	m_addnames.AddString(m_name+"-"+strTmp);
	m_name="";
	UpdateData(false);

}

void CNameInputDlg::OnBnClickedDelName()
{
	// TODO: 在此添加控件通知处理程序代码
	if (-1 ==m_addnames.GetCurSel())
		return;
	m_addnames.DeleteString(m_addnames.GetCurSel());
}

void CNameInputDlg::OnBnClickedSaveName()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp;
	CStringArray strNamelist;
	DWORD dwCount;
	dwCount = m_addnames.GetCount();
	if (0==dwCount)
		return;
	for (int i=0;i<dwCount;i++)
	{
		m_addnames.GetText(i,strTemp);
		strNamelist.Add(strTemp);
		m_namelist.AddString(strTemp);
	}
	m_wagedealagt.SaveNameList(strNamelist);

	for (int i=m_addnames.GetCount()-1;i>=0;i--)
	{
		m_addnames.DeleteString(i);

	}


}

void CNameInputDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CNameInputDlg::OnBnClickedModifyName()
{
	// TODO: 在此添加控件通知处理程序代码
	int iSel;
	iSel = m_namelist.GetCurSel();
	if (-1 ==iSel)
		return;
	CEmployInfoEditDlg dlg;
	CString strTmp;

	m_namelist.GetText(iSel,strTmp);
	dlg.SetEmplyeeInfo(strTmp,&m_wagedealagt);
	if ( dlg.DoModal()==IDOK)
	{
		CString strName,strDep;
		strName = dlg.m_name;
		strDep = dlg.m_Department;
		if ((strName.IsEmpty())||( strDep.IsEmpty()))
			return;
		m_namelist.DeleteString(iSel);
		m_namelist.InsertString(iSel,strName+"-"+strDep);
	}


}

void CNameInputDlg::OnBnClickedDelSave()
{
	// TODO: 在此添加控件通知处理程序代码
	int iSel;
	CString strTmp;
	iSel = m_namelist.GetCurSel();
	if (-1 ==iSel)
		return;
	m_namelist.GetText(iSel,strTmp);
	m_wagedealagt.DeleteEmplyee(strTmp);
	m_namelist.DeleteString(iSel);

}
