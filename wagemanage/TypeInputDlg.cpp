// TypeInputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "wagemanage.h"
#include "TypeInputDlg.h"
#include ".\typeinputdlg.h"
#include "TypeEditDlg.h"

// CTypeInputDlg 对话框

IMPLEMENT_DYNAMIC(CTypeInputDlg, CDialog)
CTypeInputDlg::CTypeInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTypeInputDlg::IDD, pParent)
	, m_type(_T(""))
	, m_description(_T(""))
{
}

CTypeInputDlg::~CTypeInputDlg()
{
}

void CTypeInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TYPE_EDIT, m_type);
	DDX_Control(pDX, IDC_ADDTYPE_LIST, m_addlist);
	DDX_Control(pDX, IDC_EXISTTYPE_LIST, m_list);
	DDX_Text(pDX, IDC_TYPE_DESCRIPT_EDIT, m_description);
}
BOOL CTypeInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CStringArray strProjectlist;
	if (false==m_wagedealagt.GetProjectlist(&strProjectlist,true))
		return false;
	for(int i=0;i<strProjectlist.GetCount();i++)
	{
		m_list.AddString(strProjectlist.GetAt(i));
	}



	return true;
}

BEGIN_MESSAGE_MAP(CTypeInputDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD_TYPE, OnBnClickedAddType)
	ON_BN_CLICKED(IDC_DEL_TYPE, OnBnClickedDelType)
	ON_BN_CLICKED(IDC_SAVE_TYPE, OnBnClickedSaveType)
	ON_BN_CLICKED(IDC_EDIT_TYPE, OnBnClickedEditType)
END_MESSAGE_MAP()


// CTypeInputDlg 消息处理程序

void CTypeInputDlg::OnBnClickedAddType()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (0==m_type.CompareNoCase(""))
		return;
	m_addlist.AddString(m_type+"-"+m_description);
	m_type="";
	m_description ="";
	UpdateData(false);
}

void CTypeInputDlg::OnBnClickedDelType()
{
	// TODO: 在此添加控件通知处理程序代码
	int iSel;
	iSel = m_addlist.GetCurSel();
	if (-1==iSel)
		return;
	m_addlist.DeleteString(iSel);

}

void CTypeInputDlg::OnBnClickedSaveType()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp;
	CStringArray strTypelist;
	int iCount;
	iCount = m_addlist.GetCount();
	if (0==iCount)
		return;
	for (int i=0;i<iCount;i++)
	{
		m_addlist.GetText(i,strTemp);
		strTypelist.Add(strTemp);
		m_list.AddString(strTemp);
	}
	m_wagedealagt.SaveProjectList(strTypelist);

	for (int i=m_addlist.GetCount()-1;i>=0;i--)
	{
		m_addlist.DeleteString(i);

	}
}

void CTypeInputDlg::OnBnClickedEditType()
{
	// TODO: 在此添加控件通知处理程序代码
	int iSel;
	CString strTemp;
	CStringArray strTempAray;
	CString strNew;
	iSel = m_list.GetCurSel();
	if (-1 ==iSel)
		return;
	m_list.GetText(iSel,strTemp);
	if (strTemp.CompareNoCase("")==0)
		return;
	m_wagedealagt.StringTranslation(strTemp,'-',strTempAray);
	CTypeEditDlg dlg(this);
	dlg.m_oldtype = strTempAray.GetAt(0);
	dlg.m_olddes = strTempAray.GetAt(1);
	dlg.m_newtype = strTempAray.GetAt(0);
	dlg.m_newdes = strTempAray.GetAt(1);
	if ( dlg.DoModal()==IDOK)
	{
		strNew = dlg.m_newtype+"-"+dlg.m_newdes;
		if (strNew.IsEmpty())
			return;
		m_wagedealagt.ModifyTypeInfo(strTemp,strNew);
		m_list.DeleteString(iSel);
		m_list.InsertString(iSel,strNew);
	}

}
