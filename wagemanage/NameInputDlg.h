#pragma once
#include "afxwin.h"
#include "wagedealAgt.h"

// CNameInputDlg �Ի���

class CNameInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CNameInputDlg)

public:
	CNameInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNameInputDlg();

// �Ի�������
	enum { IDD = IDD_NAME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CListBox m_addnames;
	CListBox m_namelist;
	afx_msg void OnBnClickedAddName();
	afx_msg void OnBnClickedDelName();
	afx_msg void OnBnClickedSaveName();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
private:
	CWagedealAgt m_wagedealagt;
public:
	CComboBox m_departlist;
	afx_msg void OnBnClickedModifyName();
	afx_msg void OnBnClickedDelSave();
};
