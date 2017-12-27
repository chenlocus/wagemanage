// WrkldStatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "wagemanage.h"
#include "WrkldStatDlg.h"
#include ".\wrkldstatdlg.h"
#include <afxtempl.h>

// CWrkldStatDlg 对话框

IMPLEMENT_DYNAMIC(CWrkldStatDlg, CDialog)
CWrkldStatDlg::CWrkldStatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWrkldStatDlg::IDD, pParent)
	, m_date(0)
{
}

CWrkldStatDlg::~CWrkldStatDlg()
{
}

BOOL CWrkldStatDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CDateTimeCtrl *pMonth;
	pMonth = (CDateTimeCtrl*)GetDlgItem(IDC_DATE);
	pMonth->SetFormat("yyyy-MM"); 
	CTime timeTmp=CTime::GetCurrentTime();
	pMonth->SetTime(&timeTmp);

	CStringArray strTypelist;
	m_wagedealagt.GetProjectlist(&strTypelist);

	for(int i=0;i<strTypelist.GetCount();i++)
	{
		m_type.AddString(strTypelist.GetAt(i));
	}
	m_type.SetCurSel(0);
	return true;

}
//SendMessage(DTM_SETFORMAT,0,(LPARAM)("'Today  is:  'hh':'m':'s  ddddMMMdd',  'yyy"));
void CWrkldStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_type);
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_date);
	DDX_Control(pDX, IDC_LIST_TOTAL, m_list);
}


BEGIN_MESSAGE_MAP(CWrkldStatDlg, CDialog)
	ON_BN_CLICKED(ID_QUERY, OnBnClickedQuery)
	ON_BN_CLICKED(ID_QUIT, OnBnClickedQuit)
	ON_BN_CLICKED(ID_PERSON_STATISTICS_PRINTPRIVIEW, OnBnClickedPersonStatisticsPrintpriview)
END_MESSAGE_MAP()


// CWrkldStatDlg 消息处理程序

void CWrkldStatDlg::OnBnClickedQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CRect rect;
	GetClientRect(rect);
	m_listctrl.MoveWindow(0,rect.Height()/2, rect.Width(), rect.Height()/2, TRUE);*/
	CString strWorkload,strPrice;
	CStringArray strSubwork,strNamelist;
	CString strType;
	char chTemp[100];
	m_type.GetLBText(m_type.GetCurSel(),strType);
	float fTotal=0;
	float fAll=0;
	UpdateData(1);
	
	
	CHeaderCtrl*   pHeaderCtrl   = m_list.GetHeaderCtrl();//m_list是你的列表控件；   
	int nColumnCount  =  pHeaderCtrl->GetItemCount();   //microsoft的bug
	for (int i=nColumnCount-1;i>=0;i--)
		m_list.DeleteColumn(i);
	m_list.DeleteAllItems();

	m_strCaption.RemoveAll();
	CString strMonth=m_date.Format("%Y-%m");
	DWORD dwStyle = m_list.GetStyle();
	dwStyle |= LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS ;
	m_list.SetExtendedStyle(dwStyle);
	m_list.SetBkColor(RGB(240,247,233));
	m_list.SetTextBkColor(RGB(240,247,233));
	m_list.InsertColumn(0,_T(" 姓名 "),LVCFMT_LEFT,80,-1);

	m_type.GetWindowText(strType);
	m_wagedealagt.GetsubworkList(strType,&strSubwork);
	for (int i=0; i<strSubwork.GetCount(); i++)
	{
		m_list.InsertColumn(i+1,strSubwork.GetAt(i),LVCFMT_LEFT,80,-1);
		m_strCaption.Add(strSubwork.GetAt(i));
	}

	m_list.InsertColumn(strSubwork.GetCount()+1,_T("  工分累计  "),LVCFMT_LEFT,100,-1);

	m_wagedealagt.GetNameList(&strNamelist);
	int nCount = strNamelist.GetCount();

	LV_ITEM m_listItem;
	CArray<float,float> fSubTotal;
	fSubTotal.SetSize(strSubwork.GetCount());
	for (int j=0;j<fSubTotal.GetSize();j++)
	{
		fSubTotal.SetAt(j,0);
	}
	for (int i=0;i<nCount;i++)
	{
		//姓名
		//chTemp = strNamelist.GetAt(i);
		m_listItem.mask=LVIF_TEXT;
		m_listItem.iItem=i;//行
		m_listItem.iSubItem=0;//列
		m_listItem.pszText=(LPSTR)(LPCSTR)strNamelist.GetAt(i);//(LPSTR)strTemp.GetBuffer(100);
		m_list.InsertItem(&m_listItem);
		m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);
		//工序对应工作量

		for (int j=0;j<strSubwork.GetCount();j++)
		{
			m_wagedealagt.GetWorkload(strMonth,strNamelist.GetAt(i),strType,strSubwork.GetAt(j),&strWorkload,&strPrice);
			float tmpPrice;
			tmpPrice=atof(strPrice);
			int tmpLoad = atoi(strWorkload);
			fTotal = fTotal + tmpLoad*tmpPrice;
			
			//按照单项工序进行工分累计
			float fTemp;
			fTemp = fSubTotal.GetAt(j);
			fSubTotal.SetAt(j,tmpLoad*tmpPrice+fTemp);


			m_listItem.mask=LVIF_TEXT;
			m_listItem.iItem=i;
			m_listItem.iSubItem=j+1;
			m_listItem.pszText=strWorkload.GetBuffer(200);
			m_list.InsertItem(&m_listItem);
			m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);
		}
		//个人按款号工资累计
		char chTotal[10];
		sprintf(chTotal,"%.2f",fTotal);
		fAll +=fTotal;
		m_listItem.iSubItem=j+1;
		m_listItem.pszText=chTotal;
		m_list.InsertItem(&m_listItem);
		m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);
		fTotal =0;
	}
	//增加工资合计一项
	m_listItem.iItem=nCount;//行
	m_listItem.iSubItem=0;//列
	m_listItem.pszText=_T("合计");//(LPSTR)strTemp.GetBuffer(100);
	m_list.InsertItem(&m_listItem);
	m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);

	char chAll[10];

	//增加单项工序进行工分累计
	for (int i=0;i<fSubTotal.GetSize();i++)
	{
		sprintf(chAll,"%.2f",fSubTotal.GetAt(i));
		m_listItem.iSubItem=i+1;
		m_listItem.pszText=chAll;
		m_list.InsertItem(&m_listItem);
		m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);

	}

	sprintf(chAll,"%.2f",fAll);
	m_listItem.iSubItem=strSubwork.GetCount()+1;
	m_listItem.pszText=chAll;
	m_list.InsertItem(&m_listItem);
	m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);



	

}

void CWrkldStatDlg::OnBnClickedQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::EndDialog(0);
}

void CWrkldStatDlg::OnBnClickedPersonStatisticsPrintpriview()
{
	// TODO: 在此添加控件通知处理程序代码
	CwagemanageApp* app=(CwagemanageApp*)AfxGetApp();
	//app->SetPrntOrientation();
	app->m_pMiddle=this;
	app->m_pMainWnd->ShowWindow(SW_SHOW);
	app->m_pMainWnd->UpdateWindow();
	app->m_pMainWnd->SendMessage(WM_COMMAND, ID_FILE_PRINT_PREVIEW);
}
