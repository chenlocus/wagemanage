#pragma once
#include "afxwin.h"
#include "wagedealAgt.h"

// CSubworkPriceDlg 对话框

class CSubworkPriceDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubworkPriceDlg)

public:
	CSubworkPriceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSubworkPriceDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_TYPE_SUBWORK_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_type;
	CString m_subwork;
	CListBox m_addlist;
	CListBox m_list;
private:
	CWagedealAgt m_wagedealagt;
public:
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDelButton();
	afx_msg void OnBnClickedSave();
	float m_price;
	afx_msg void OnCbnSelchangeTypeCombo();
	afx_msg void OnBnClickedEdit();
};
