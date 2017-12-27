#pragma once
#include "wagedealAgt.h"
#include "afxwin.h"

// CDepartmentDlg 对话框

class CDepartmentDlg : public CDialog
{
	DECLARE_DYNAMIC(CDepartmentDlg)

public:
	CDepartmentDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDepartmentDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DEPARTMENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CWagedealAgt m_wagedealagt;
	DECLARE_MESSAGE_MAP()
public:
	// 部门名称
	CString m_name;
	// 增加部门
	CListBox m_addlist;
	// 已经有的部门
	CListBox m_list;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedModify();
};
