#pragma once
#include "afxwin.h"


// CTypeEditDlg �Ի���

class CTypeEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CTypeEditDlg)

public:
	CTypeEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTypeEditDlg();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_EDIT_TYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_oldtype;
	CString m_olddes;
	CString m_newtype;
	afx_msg void OnBnClickedOk();
	CString m_newdes;
};
