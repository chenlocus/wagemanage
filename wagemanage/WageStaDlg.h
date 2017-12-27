#pragma once
#include "atltime.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "wagedealAgt.h"


// CWageStaDlg �Ի���

class CWageStaDlg : public CDialog
{
	DECLARE_DYNAMIC(CWageStaDlg)

public:
	CWageStaDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWageStaDlg();

// �Ի�������
	enum { IDD = IDD_WAGE_TOTAL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedWagetotal();
	CTime m_date;
	CStringArray strCaption;
private:
	CWagedealAgt m_wagedealagt;
public:
	afx_msg void OnBnClickedWageQuit();
	afx_msg void OnBnClickedWagetotalPrintpriview();
};
