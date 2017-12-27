#pragma once
#include "afxwin.h"
#include "wagedealAgt.h"


// CEmployInfoEditDlg 对话框

class CEmployInfoEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CEmployInfoEditDlg)

public:
	CEmployInfoEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEmployInfoEditDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_MODIFY_EMPLOY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CComboBox m_departlist;
	CWagedealAgt * m_wagedealagt;
	CString m_Department;
private:
	CString strEmployeeInfo;
	CString strOldDepartment;
	CString strOldName;

public:
	void SetEmplyeeInfo(CString strInfo,CWagedealAgt *pDatabase);
	afx_msg void OnBnClickedOk();
};
