#pragma once
#include "wagedealAgt.h"
#include "afxwin.h"

// CTypeInputDlg �Ի���

class CTypeInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CTypeInputDlg)

public:
	CTypeInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTypeInputDlg();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_TYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
