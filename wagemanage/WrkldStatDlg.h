#pragma once
#include "afxwin.h"
#include "atltime.h"
#include "afxcmn.h"
#include "wagedealAgt.h"

// CWrkldStatDlg �Ի���

class CWrkldStatDlg : public CDialog
{
	DECLARE_DYNAMIC(CWrkldStatDlg)

public:
	CWrkldStatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWrkldStatDlg();

// �Ի�������
	enum { IDD = IDD_TOTAL_PRDUCTION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_type;
	CTime m_date;
	CListCtrl m_list;
	CStringArray m_strCaption;
	afx_msg void OnBnClickedQuery();
	virtual BOOL OnInitDialog();
private:
	CWagedealAgt m_wagedealagt;
public:
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedPersonStatisticsPrintpriview();
};
