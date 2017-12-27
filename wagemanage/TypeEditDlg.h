#pragma once
#include "afxwin.h"


// CTypeEditDlg 对话框

class CTypeEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CTypeEditDlg)

public:
	CTypeEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTypeEditDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_EDIT_TYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_oldtype;
	CString m_olddes;
	CString m_newtype;
	afx_msg void OnBnClickedOk();
	CString m_newdes;
};
