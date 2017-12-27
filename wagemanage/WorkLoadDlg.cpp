// WorkLoadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "wagemanage.h"
#include "WorkLoadDlg.h"
#include ".\workloaddlg.h"


// CWorkLoadDlg 对话框

IMPLEMENT_DYNAMIC(CWorkLoadDlg, CDialog)
CWorkLoadDlg::CWorkLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkLoadDlg::IDD, pParent)
	, m_date(0)
	, m_wkld(0)
{
}

CWorkLoadDlg::~CWorkLoadDlg()
{
}

void CWorkLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATE_WKLD, m_date);
	DDX_Control(pDX, IDC_COMBO_NAME_WKLD, m_name);
	DDX_Control(pDX, IDC_COMBO_TYPE_WKLD, m_type);
	DDX_Text(pDX, IDC_EDIT_WKLD, m_wkld);
	DDV_MinMaxInt(pDX, m_wkld, 0, 100000);
	DDX_Control(pDX, IDC_LIST_WKLD, m_wklist);
	DDX_Control(pDX, IDC_COMBO_SUB_WKLD, m_subwklist);
	DDX_Control(pDX, IDC_LIST_WKLD_SAVE, m_savelist);
	DDX_Control(pDX, IDC_COMBO_NAME_WKLD2, m_departlist);
}


BOOL CWorkLoadDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CStringArray strNamelist;
	CStringArray strTypelist;
	CStringArray strsubwklist;
	CStringArray strDepartlist;

	CDateTimeCtrl *pDate;
	pDate = (CDateTimeCtrl*)GetDlgItem(IDC_DATE_WKLD);
	CTime timeTmp=CTime::GetCurrentTime();
	pDate->SetTime(&timeTmp);

	m_wagedealagt.GetProjectlist(&strTypelist);

	for(int i=0;i<strTypelist.GetCount();i++)
	{
		m_type.AddString(strTypelist.GetAt(i));
	}
	m_type.SetCurSel(0);

	m_wagedealagt.GetsubworkList(strTypelist.GetAt(0),&strsubwklist);
	for(int i=0;i<strsubwklist.GetCount();i++)
	{
		m_subwklist.AddString(strsubwklist.GetAt(i));
	}
	m_subwklist.SetCurSel(0);

	m_departlist.AddString(_T("全部人员"));
	m_wagedealagt.GetDepartmentInfo(strDepartlist);
    for (int i=0;i<strDepartlist.GetCount();i++)
	{
		m_departlist.AddString(strDepartlist.GetAt(i));
	}

	m_departlist.SetCurSel(0);

	m_wagedealagt.GetNameList(&strNamelist);
	for(int i=0;i<strNamelist.GetCount();i++)
	{
		m_name.AddString(strNamelist.GetAt(i));
	}
	m_name.SetCurSel(0);
	
	return true;

}

BEGIN_MESSAGE_MAP(CWorkLoadDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE_WKLD, OnCbnSelchangeComboTypeWkld)
	ON_BN_CLICKED(ID_ADD, OnBnClickedAdd)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_WKLD, OnCbnSelchangeComboNameWkld)
	ON_BN_CLICKED(ID_SAVE, OnBnClickedSave)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_WKLD, OnDtnDatetimechangeDateWkld)
	ON_BN_CLICKED(ID_DEL_SAVE, OnBnClickedDelSave)
	ON_BN_CLICKED(ID_DELETE, OnBnClickedDelete)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_WKLD2, OnCbnSelchangeComboNameWkld2)
END_MESSAGE_MAP()


// CWorkLoadDlg 消息处理程序
void CWorkLoadDlg::OnCbnSelchangeComboTypeWkld()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp;
	CStringArray strsubwklist;
	for (int i=0; i<m_subwklist.GetCount();)
	{
		m_subwklist.DeleteString(i);
	}

	m_type.GetLBText(m_type.GetCurSel(),strTemp);
	m_wagedealagt.GetsubworkList(strTemp,&strsubwklist);
	for(int i=0;i<strsubwklist.GetCount();i++)
	{
		m_subwklist.AddString(strsubwklist.GetAt(i));
	}

}

void CWorkLoadDlg::OnBnClickedAdd()
{
	CString strType;
	CString strSubwork;
	CString strWkld;
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	if (0==m_wkld) return;
	m_type.GetLBText(m_type.GetCurSel(),strType);
	m_subwklist.GetLBText(m_subwklist.GetCurSel(),strSubwork);
	strWkld.Format("%d",m_wkld);
	m_wklist.AddString(strType+"-"+strSubwork+"-"+strWkld);


	
}

void CWorkLoadDlg::OnCbnSelchangeComboNameWkld()
{
	// TODO: 刷新列表
	UpdateSavedList();
}

void CWorkLoadDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName;
	CStringArray strSubList;
	CString strDate;
	CString strTemp;
	strDate=m_date.Format("%y-%m-%d");

	for (int i=0;i<m_wklist.GetCount();i++)
	{
		m_wklist.GetText(i,strTemp);
		strSubList.Add(strTemp);
		m_savelist.AddString(strTemp);
	}
	for (int j= m_wklist.GetCount()-1;j>=0;j--)
	{
		m_wklist.DeleteString(j);
	}
	
	m_name.GetLBText(m_name.GetCurSel(),strName);
	m_wagedealagt.SaveWorkLoadData(strDate,strName,strSubList);

}

void CWorkLoadDlg::OnDtnDatetimechangeDateWkld(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateSavedList();
	/*m_wkld =0;
	UpdateData(false);*/

}

//更新保存列表的内容
void CWorkLoadDlg::UpdateSavedList(void)
{
	CString strName;
	CStringArray strList;
	UpdateData(true);

	for (int i =m_savelist.GetCount()-1;i>=0;i--)
		m_savelist.DeleteString(i);

	m_name.GetLBText(m_name.GetCurSel(),strName);
	if (0==strName.CompareNoCase("") )
		return;
	if ( m_wagedealagt.GetPersonWorkLoadList(m_date,strName,strList) )
	{
		for (int i=0;i<strList.GetCount();i++)
			m_savelist.AddString(strList.GetAt(i));
	}


}

void CWorkLoadDlg::OnBnClickedDelSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName,strDate,strWorkload;
	int iSel;

	iSel = m_savelist.GetCurSel();
	if (-1== iSel)
		return;

	strDate=m_date.Format("%Y-%m-%d");
	m_name.GetLBText(m_name.GetCurSel(),strName);

	m_savelist.GetText(iSel,strWorkload);
	if ( m_wagedealagt.DeleteWorkLoadData(strDate,strName,strWorkload))
	{
		m_savelist.DeleteString(iSel);
	}

}

void CWorkLoadDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	m_wklist.DeleteString(m_wklist.GetCurSel());

}

void CWorkLoadDlg::OnCbnSelchangeComboNameWkld2()
{

	// TODO: 在此添加控件通知处理程序代码
	int iSel;
	iSel = m_departlist.GetCurSel();
	if (-1 ==iSel)
		return;
	CString strDepartName;
	CStringArray strNameArray;

	m_departlist.GetLBText(iSel,strDepartName);
	if (strDepartName.CompareNoCase(_T("全部人员"))==0)
		m_wagedealagt.GetNameList(&strNameArray);
	else
		m_wagedealagt.GetNameList(&strNameArray,strDepartName);

	for (int i=0; i<m_name.GetCount();)
	{
		m_name.DeleteString(i);
	}
	int iCount = strNameArray.GetCount();
	if (iCount<=0)
		return;

	for (int i=0;i<iCount;i++)
	{
		m_name.AddString(strNameArray.GetAt(i));
	}
	m_name.SetCurSel(0);

}
