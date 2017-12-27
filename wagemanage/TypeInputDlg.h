#pragma once
#include "wagedealAgt.h"
#include "afxwin.h"

// CTypeInputDlg 对话框

class CTypeInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CTypeInputDlg)

public:
	CTypeInputDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTypeInputDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_TYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CWagedealAgt m_wagedealagt;
public:
	CString m_type;
	CListBox m_addlist;
	CListBox m_list;
	afx_msg void OnBnClickedAddType();
	afx_msg void OnBnClickedDelType();
	afx_msg void OnBnClickedSaveType();
	CString m_description;
	afx_msg void OnBnClickedEditType();
};
