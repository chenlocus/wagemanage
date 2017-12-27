// DepartmentDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "wagemanage.h"
#include "DepartmentDlg.h"
#include ".\departmentdlg.h"
#include "departeditdlg.h"


// CDepartmentDlg �Ի���

IMPLEMENT_DYNAMIC(CDepartmentDlg, CDialog)
CDepartmentDlg::CDepartmentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDepartmentDlg::IDD, pParent)
	, m_name(_T(""))
{
}

CDepartmentDlg::~CDepartmentDlg()
{
}

void CDepartmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME_EDIT, m_name);
	DDX_Control(pDX, IDC_LIST_ADD, m_addlist);
	DDX_Control(pDX, IDC_LIST_SAVE, m_list);
}
BOOL CDepartmentDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CStringArray strDepartnmelist;
	if (false==m_wagedealagt.GetDepartmentInfo(strDepartnmelist))
		return false;
	for(int i=0;i<strDepartnmelist.GetCount();i++)
	{
		m_list.AddString(strDepartnmelist.GetAt(i));
	}

	return true;
}

BEGIN_MESSAGE_MAP(CDepartmentDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_SAVE, OnBnClickedSave)
	ON_BN_CLICKED(IDC_MODIFY, OnBnClickedModify)
END_MESSAGE_MAP()


// CDepartmentDlg ��Ϣ�������

void CDepartmentDlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (0==m_name.CompareNoCase(""))
		return;
	m_addlist.AddString(m_name);
	m_name="";
	UpdateData(false);
}

void CDepartmentDlg::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iSel;
	iSel = m_addlist.GetCurSel();
	if (-1==iSel)
		return;
	m_addlist.DeleteString(iSel);
}

void CDepartmentDlg::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	m_wagedealagt.SaveDepartmentList(strTypelist);

	for (int i=m_addlist.GetCount()-1;i>=0;i--)
	{
		m_addlist.DeleteString(i);

	}
}

void CDepartmentDlg::OnBnClickedModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iSel;
	CString strTemp;
	CString strNew;
	iSel = m_list.GetCurSel();
	if (-1 ==iSel)
		return;
	m_list.GetText(iSel,strTemp);
	if (strTemp.CompareNoCase("")==0)
		return;
	CDepartEditDlg dlg(this);
	dlg.m_oldname = strTemp;
	if ( dlg.DoModal()==IDOK)
	{
		strNew = dlg.m_newname;
		if (strNew.IsEmpty())
			return;
		m_wagedealagt.ModifyDepartName(strTemp,strNew);
		m_list.DeleteString(iSel);
		m_list.InsertString(iSel,strNew);
	}
}
