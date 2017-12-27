// WageStaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "wagemanage.h"
#include "WageStaDlg.h"
#include ".\wagestadlg.h"


// CWageStaDlg 对话框

IMPLEMENT_DYNAMIC(CWageStaDlg, CDialog)
CWageStaDlg::CWageStaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWageStaDlg::IDD, pParent)
	, m_date(0)
{
}

CWageStaDlg::~CWageStaDlg()
{
}

void CWageStaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WAGE, m_list);
	DDX_DateTimeCtrl(pDX, IDC_DATE_WAGETOTAL, m_date);
}


BEGIN_MESSAGE_MAP(CWageStaDlg, CDialog)
	ON_BN_CLICKED(ID_WAGETOTAL, OnBnClickedWagetotal)
	ON_BN_CLICKED(ID_WAGE_QUIT, OnBnClickedWageQuit)
	ON_BN_CLICKED(ID_WAGETOTAL_PRINTPRIVIEW, OnBnClickedWagetotalPrintpriview)
END_MESSAGE_MAP()



BOOL CWageStaDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	CDateTimeCtrl *pMonth;
	pMonth = (CDateTimeCtrl*)GetDlgItem(IDC_DATE_WAGETOTAL);
	pMonth->SetFormat("yyyy-MM"); 
	CTime timeTmp=CTime::GetCurrentTime();
	pMonth->SetTime(&timeTmp);
	return false;
}

void CWageStaDlg::OnBnClickedWagetotal()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSalary;
	CStringArray strType,strNamelist;
	char chTemp[100];
	float fTotal=0;
	float fAll=0;
	UpdateData(1);
	CHeaderCtrl*   pHeaderCtrl   = m_list.GetHeaderCtrl();//m_list是你的列表控件；   
	int nColumnCount  =  pHeaderCtrl->GetItemCount();   //microsoft的bug
	for (int i=nColumnCount-1;i>=0;i--)
		m_list.DeleteColumn(i);
	m_list.DeleteAllItems();
	strCaption.RemoveAll();
	CString strMonth=m_date.Format("%Y-%m");
	DWORD dwStyle = m_list.GetStyle();
	dwStyle |= LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS ;
	m_list.SetExtendedStyle(dwStyle);
	m_list.SetBkColor(RGB(240,247,233));
	m_list.SetTextBkColor(RGB(240,247,233));
	m_list.InsertColumn(0,_T(" 姓名|款号 "),LVCFMT_LEFT,80,-1);
	strCaption.Add(_T("姓名|款号"));

	m_wagedealagt.GetProjectlist(&strType);
	for (int i=0; i<strType.GetCount(); i++)
	{
		m_list.InsertColumn(i+1,strType.GetAt(i),LVCFMT_LEFT,80,-1);
		strCaption.Add(strType.GetAt(i));
	}

	m_list.InsertColumn(strType.GetCount()+1,_T("  当月工分累计  "),LVCFMT_LEFT,150,-1);
	strCaption.Add(_T("工分累计"));

	m_list.InsertColumn(strType.GetCount()+2,_T("  当月实得工资(元)  "),LVCFMT_LEFT,150,-1);
	strCaption.Add(_T("实得工资(元)"));

	m_wagedealagt.GetNameList(&strNamelist);
	int nCount = strNamelist.GetCount();

	LV_ITEM m_listItem;
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

		for (int j=0;j<strType.GetCount();j++)
		{
			m_wagedealagt.GetMonthSalary(strMonth,strNamelist.GetAt(i),strType.GetAt(j),&strSalary);
			float tmpPrice;
			tmpPrice=atof(strSalary);
			fTotal = fTotal + tmpPrice;
			strSalary.Format("%.2f",tmpPrice);
			m_listItem.mask=LVIF_TEXT;
			m_listItem.iItem=i;
			m_listItem.iSubItem=j+1;
			m_listItem.pszText=strSalary.GetBuffer(200);
			m_list.InsertItem(&m_listItem);
			m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);
		}
		//个人工分累计
		char chTotal[10];
		fAll += fTotal;
		sprintf(chTotal,"%8.2f",fTotal);
		m_listItem.iSubItem=j+1;
		m_listItem.pszText=chTotal;
		m_list.InsertItem(&m_listItem);
		m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);
		
		//个人工资累计
		sprintf(chTotal,"%.2f",fTotal*0.045);
		m_listItem.iSubItem=j+2;
		m_listItem.pszText=chTotal;
		m_list.InsertItem(&m_listItem);
		m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);


		fTotal =0;
	}

	//增加工分合计一项
	m_listItem.iItem=nCount;//行
	m_listItem.iSubItem=0;//列
	m_listItem.pszText=_T("合计");//(LPSTR)strTemp.GetBuffer(100);
	m_list.InsertItem(&m_listItem);
	m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);


	char chAll[10];
	sprintf(chAll,"%.2f",fAll);
	m_listItem.iSubItem=strType.GetCount()+1;
	m_listItem.pszText=chAll;
	m_list.InsertItem(&m_listItem);
	m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);

	//增加工资合计一项
	sprintf(chAll,"%.2f",fAll*0.045);
	m_listItem.iSubItem=strType.GetCount()+2;
	m_listItem.pszText=chAll;
	m_list.InsertItem(&m_listItem);
	m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);





}

void CWageStaDlg::OnBnClickedWageQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::EndDialog(0);
}

void CWageStaDlg::OnBnClickedWagetotalPrintpriview()
{
	// TODO: 在此添加控件通知处理程序代码
	CwagemanageApp* app=(CwagemanageApp*)AfxGetApp();
	//app->SetPrntOrientation();
	app->m_pMiddle=this;
	app->m_pMainWnd->ShowWindow(SW_SHOW);
	app->m_pMainWnd->UpdateWindow();
	app->m_pMainWnd->SendMessage(WM_COMMAND, ID_FILE_PRINT_PREVIEW);
	//CDialog::EndDialog(1);

}
