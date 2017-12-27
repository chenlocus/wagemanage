// SubWorkInfoEditDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "wagemanage.h"
#include "SubWorkInfoEditDlg.h"
#include ".\subworkinfoeditdlg.h"


// CSubWorkInfoEditDlg �Ի���

IMPLEMENT_DYNAMIC(CSubWorkInfoEditDlg, CDialog)
CSubWorkInfoEditDlg::CSubWorkInfoEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubWorkInfoEditDlg::IDD, pParent)
	, m_subwork(_T(""))
	, m_price(0)
{
}

CSubWorkInfoEditDlg::~CSubWorkInfoEditDlg()
{
}


BOOL CSubWorkInfoEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateData(false);
	return true;
}
void CSubWorkInfoEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SUBWORK_EDIT, m_subwork);
	DDX_Text(pDX, IDC_PRICE_EDIT, m_price);
}


BEGIN_MESSAGE_MAP(CSubWorkInfoEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CSubWorkInfoEditDlg ��Ϣ�������

void CSubWorkInfoEditDlg::SetSubworkInfo(CString strT,CString strInfo, CWagedealAgt * pDatabase)
{
	CStringArray strArray;
	m_wagedealagt = pDatabase;
	m_wagedealagt->StringTranslation(strInfo,'/',strArray);
	m_subwork = strArray.GetAt(0);
	strPrice = strArray.GetAt(1);
	m_price = atof(strPrice);
	strOldSubWork = m_subwork;
	strOldPrice = strPrice;
	strType = strT;

}

void CSubWorkInfoEditDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	strPrice.Format("%3.1f",m_price);
	m_wagedealagt->ModifySubworkInfo(strType,strOldSubWork,m_subwork,strPrice);
	OnOK();
}
