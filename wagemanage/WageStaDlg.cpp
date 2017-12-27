// WageStaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "wagemanage.h"
#include "WageStaDlg.h"
#include ".\wagestadlg.h"


// CWageStaDlg �Ի���

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSalary;
	CStringArray strType,strNamelist;
	char chTemp[100];
	float fTotal=0;
	float fAll=0;
	UpdateData(1);
	CHeaderCtrl*   pHeaderCtrl   = m_list.GetHeaderCtrl();//m_list������б�ؼ���   
	int nColumnCount  =  pHeaderCtrl->GetItemCount();   //microsoft��bug
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
	m_list.InsertColumn(0,_T(" ����|��� "),LVCFMT_LEFT,80,-1);
	strCaption.Add(_T("����|���"));

	m_wagedealagt.GetProjectlist(&strType);
	for (int i=0; i<strType.GetCount(); i++)
	{
		m_list.InsertColumn(i+1,strType.GetAt(i),LVCFMT_LEFT,80,-1);
		strCaption.Add(strType.GetAt(i));
	}

	m_list.InsertColumn(strType.GetCount()+1,_T("  ���¹����ۼ�  "),LVCFMT_LEFT,150,-1);
	strCaption.Add(_T("�����ۼ�"));

	m_list.InsertColumn(strType.GetCount()+2,_T("  ����ʵ�ù���(Ԫ)  "),LVCFMT_LEFT,150,-1);
	strCaption.Add(_T("ʵ�ù���(Ԫ)"));

	m_wagedealagt.GetNameList(&strNamelist);
	int nCount = strNamelist.GetCount();

	LV_ITEM m_listItem;
	for (int i=0;i<nCount;i++)
	{
		//����
		//chTemp = strNamelist.GetAt(i);
		m_listItem.mask=LVIF_TEXT;
		m_listItem.iItem=i;//��
		m_listItem.iSubItem=0;//��
		m_listItem.pszText=(LPSTR)(LPCSTR)strNamelist.GetAt(i);//(LPSTR)strTemp.GetBuffer(100);
		m_list.InsertItem(&m_listItem);
		m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);
		//�����Ӧ������

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
		//���˹����ۼ�
		char chTotal[10];
		fAll += fTotal;
		sprintf(chTotal,"%8.2f",fTotal);
		m_listItem.iSubItem=j+1;
		m_listItem.pszText=chTotal;
		m_list.InsertItem(&m_listItem);
		m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);
		
		//���˹����ۼ�
		sprintf(chTotal,"%.2f",fTotal*0.045);
		m_listItem.iSubItem=j+2;
		m_listItem.pszText=chTotal;
		m_list.InsertItem(&m_listItem);
		m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);


		fTotal =0;
	}

	//���ӹ��ֺϼ�һ��
	m_listItem.iItem=nCount;//��
	m_listItem.iSubItem=0;//��
	m_listItem.pszText=_T("�ϼ�");//(LPSTR)strTemp.GetBuffer(100);
	m_list.InsertItem(&m_listItem);
	m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);


	char chAll[10];
	sprintf(chAll,"%.2f",fAll);
	m_listItem.iSubItem=strType.GetCount()+1;
	m_listItem.pszText=chAll;
	m_list.InsertItem(&m_listItem);
	m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);

	//���ӹ��ʺϼ�һ��
	sprintf(chAll,"%.2f",fAll*0.045);
	m_listItem.iSubItem=strType.GetCount()+2;
	m_listItem.pszText=chAll;
	m_list.InsertItem(&m_listItem);
	m_list.SetItemText(m_listItem.iItem,m_listItem.iSubItem,m_listItem.pszText);





}

void CWageStaDlg::OnBnClickedWageQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::EndDialog(0);
}

void CWageStaDlg::OnBnClickedWagetotalPrintpriview()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CwagemanageApp* app=(CwagemanageApp*)AfxGetApp();
	//app->SetPrntOrientation();
	app->m_pMiddle=this;
	app->m_pMainWnd->ShowWindow(SW_SHOW);
	app->m_pMainWnd->UpdateWindow();
	app->m_pMainWnd->SendMessage(WM_COMMAND, ID_FILE_PRINT_PREVIEW);
	//CDialog::EndDialog(1);

}
