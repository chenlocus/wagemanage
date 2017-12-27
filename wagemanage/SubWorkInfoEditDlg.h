#pragma once
#include "wagedealAgt.h"

// CSubWorkInfoEditDlg �Ի���

class CSubWorkInfoEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubWorkInfoEditDlg)

public:
	CSubWorkInfoEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSubWorkInfoEditDlg();
	virtual BOOL OnInitDialog();
	CWagedealAgt * m_wagedealagt;

// �Ի�������
	enum { IDD = IDD_SUBWORK_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
private:
	private:
	CString strSubworkInfo;
	CString strOldSubWork;
	CString strOldPrice;

	DECLARE_MESSAGE_MAP()
public:
	void SetSubworkInfo(CString strT,CString strInfo, CWagedealAgt * pDatabase);
	CString strType;
	CString m_subwork;
	CString strPrice;
	afx_msg void OnBnClickedOk();
	float m_price;
};
