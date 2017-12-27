#pragma once
#include "afxwin.h"
#include "wagedealAgt.h"

// CSubworkPriceDlg �Ի���

class CSubworkPriceDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubworkPriceDlg)

public:
	CSubworkPriceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSubworkPriceDlg();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_TYPE_SUBWORK_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
