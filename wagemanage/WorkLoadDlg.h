#pragma once
#include "atltime.h"
#include "afxwin.h"
#include "WagedealAgt.h"


// CWorkLoadDlg 对话框

class CWorkLoadDlg : public CDialog
{
	DECLARE_DYNAMIC(CWorkLoadDlg)

public:
	CWorkLoadDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkLoadDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_WORKLOAD_DIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTime m_date;
	CComboBox m_name;
	CComboBox m_type;
	int m_wkld;
	CListBox m_wklist;

private:
	CWagedealAgt m_wagedealagt;
public:
	CComboBox m_subwklist;
	afx_msg void OnCbnSelchangeComboTypeWkld();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnCbnSelchangeComboNameWkld();
	afx_msg void OnBnClickedSave();
	CListBox m_savelist;
	afx_msg void OnDtnDatetimechangeDateWkld(NMHDR *pNMHDR, LRESULT *pResult);
	void UpdateSavedList(void);
	afx_msg void OnBnClickedDelSave();
	afx_msg void OnBnClickedDelete();
	CComboBox m_departlist;
	afx_msg void OnCbnSelchangeComboNameWkld2();
};
