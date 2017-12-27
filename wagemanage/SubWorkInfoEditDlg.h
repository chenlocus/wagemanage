#pragma once
#include "wagedealAgt.h"

// CSubWorkInfoEditDlg 对话框

class CSubWorkInfoEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubWorkInfoEditDlg)

public:
	CSubWorkInfoEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSubWorkInfoEditDlg();
	virtual BOOL OnInitDialog();
	CWagedealAgt * m_wagedealagt;

// 对话框数据
	enum { IDD = IDD_SUBWORK_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
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
