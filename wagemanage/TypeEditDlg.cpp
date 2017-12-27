// TypeEditDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "wagemanage.h"
#include "TypeEditDlg.h"
#include ".\typeeditdlg.h"


// CTypeEditDlg �Ի���

IMPLEMENT_DYNAMIC(CTypeEditDlg, CDialog)
CTypeEditDlg::CTypeEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTypeEditDlg::IDD, pParent)
	, m_oldtype(_T(""))
	, m_olddes(_T(""))
	, m_newtype(_T(""))
	, m_newdes(_T(""))
{
}

CTypeEditDlg::~CTypeEditDlg()
{
}

void CTypeEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_oldtype);
	DDX_Text(pDX, IDC_EDIT_DESCRIPE, m_olddes);
	DDX_Text(pDX, IDC_EDIT_TYPE2, m_newtype);
	DDX_Text(pDX, IDC_EDIT_DESCRIPE2, m_newdes);
}

BOOL CTypeEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateData(true);

	return true;
}
BEGIN_MESSAGE_MAP(CTypeEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CTypeEditDlg ��Ϣ�������

void CTypeEditDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	
	OnOK();

}
