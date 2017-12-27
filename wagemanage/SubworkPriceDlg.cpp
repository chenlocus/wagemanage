// SubworkPriceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "wagemanage.h"
#include "SubworkPriceDlg.h"
#include ".\subworkpricedlg.h"
#include "SubWorkInfoEditDlg.h"

// CSubworkPriceDlg 对话框

IMPLEMENT_DYNAMIC(CSubworkPriceDlg, CDialog)
CSubworkPriceDlg::CSubworkPriceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubworkPriceDlg::IDD, pParent)
	, m_subwork(_T(""))
	, m_price(0)
{
}

CSubworkPriceDlg::~CSubworkPriceDlg()
{
}
BOOL CSubworkPriceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CStringArray strProjectlist;
	CStringArray strsubwklist;
	m_wagedealagt.GetProjectlist(&strProjectlist);
	for(int i=0;i<strProjectlist.GetCount();i++)
	{
		m_type.AddString(strProjectlist.GetAt(i));
	}
	m_type.SetCurSel(0);

	if (!m_wagedealagt.GetSubworkInfo(strProjectlist.GetAt(0),strsubwklist))
		return false;
	for(int i=0;i<strsubwklist.GetCount();i++)
	{
		m_list.AddString(strsubwklist.GetAt(i));
	}

	return true;
}
void CSubworkPriceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_type);
	DDX_Text(pDX, IDC_SUBWORK_EDIT, m_subwork);
	DDX_Control(pDX, IDC_ADDSUBWORK_LIST, m_addlist);
	DDX_Control(pDX, IDC_EXISTSUBWORKLIST, m_list);
	DDX_Text(pDX, IDC_PRICE_EDIT, m_price);
}


BEGIN_MESSAGE_MAP(CSubworkPriceDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD_BUTTON, OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_DEL_BUTTON, OnBnClickedDelButton)
	ON_BN_CLICKED(ID_SAVE, OnBnClickedSave)
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, OnCbnSelchangeTypeCombo)
	ON_BN_CLICKED(ID_EDIT, OnBnClickedEdit)
END_MESSAGE_MAP()


// CSubworkPriceDlg 消息处理程序

void CSubworkPriceDlg::OnBnClickedAddButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString strPrice;
	strPrice.Format("%f",m_price);
	if (0==m_subwork.CompareNoCase(""))
		return;
	m_addlist.AddString(m_subwork+"/"+strPrice);
	m_subwork ="";
	m_price =0.0;
	UpdateData(false);

}

void CSubworkPriceDlg::OnBnClickedDelButton()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwSel;
	dwSel =m_addlist.GetCurSel();
	if (-1==dwSel)
		return;
	m_addlist.DeleteString(dwSel);
}

void CSubworkPriceDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp;
	CString strType;
	CStringArray strSubworklist;
	int iCount;
	iCount = m_addlist.GetCount();
	if (0==iCount)
		return;
	if (-1==m_type.GetCurSel())
		return;

	for (int i=0;i<iCount;i++)
	{
		m_addlist.GetText(i,strTemp);
		m_list.AddString(strTemp);
		strSubworklist.Add(strTemp);
	}
	m_type.GetLBText(m_type.GetCurSel(),strType);
	m_wagedealagt.SaveSubworkInfo(strType,strSubworklist);

	for (int i=m_addlist.GetCount()-1;i>=0;i--)
	{
		m_addlist.DeleteString(i);

	}

}

void CSubworkPriceDlg::OnCbnSelchangeTypeCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strProject;
	CStringArray strsubwklist;
	
	if (-1==m_type.GetCurSel())
		return;

	for (int i=m_list.GetCount()-1;i>=0;i--)
		m_list.DeleteString(i);

	m_type.GetLBText(m_type.GetCurSel(),strProject);

	if (!m_wagedealagt.GetSubworkInfo(strProject,strsubwklist))
		return;
	for(int i=0;i<strsubwklist.GetCount();i++)
	{
		m_list.AddString(strsubwklist.GetAt(i));
	}
}

void CSubworkPriceDlg::OnBnClickedEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	int iSel;
	iSel = m_list.GetCurSel();
	if (-1 ==iSel)
		return;
	CString strT,strTmp1,strTmp2;
	CSubWorkInfoEditDlg dlg;
	CString strTmp;
	m_type.GetLBText(m_type.GetCurSel(),strT);
	m_list.GetText(iSel,strTmp);
	dlg.SetSubworkInfo(strT,strTmp,&m_wagedealagt);
	if (dlg.DoModal()==IDOK)
	{
		CString strName,strDep;
		strTmp1 = dlg.m_subwork;
		if (strTmp1.IsEmpty()) return;
		strTmp2.Format("%3.1f",dlg.m_price);
		if (strTmp2.IsEmpty()) return;
		m_list.DeleteString(iSel);
		m_list.InsertString(iSel,strTmp1+"/"+strTmp2);
	}
}
